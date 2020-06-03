#include "file_system.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__device__ __managed__ u32 gtime = 0;


__device__ void fs_init(FileSystem *fs, uchar *volume, int SUPERBLOCK_SIZE,
							int FCB_SIZE, int FCB_ENTRIES, int VOLUME_SIZE,
							int STORAGE_BLOCK_SIZE, int MAX_FILENAME_SIZE, 
							int MAX_FILE_NUM, int MAX_FILE_SIZE, int FILE_BASE_ADDRESS)
{
  // init variables
  fs->volume = volume;  

  // init constants
  fs->SUPERBLOCK_SIZE = SUPERBLOCK_SIZE;        // 4096 volume[0-4095]
  fs->FCB_SIZE = FCB_SIZE;                      // 32, name-20, created-4, modified-4, start-2, size-2
  fs->FCB_ENTRIES = FCB_ENTRIES;                // 1024, total size 32768, volume[4096-36863]
  fs->STORAGE_SIZE = VOLUME_SIZE;               // 1085440
  fs->STORAGE_BLOCK_SIZE = STORAGE_BLOCK_SIZE;  // 32, total 2^15 blocks, volume[36864-1085440]
  fs->MAX_FILENAME_SIZE = MAX_FILENAME_SIZE;    // 20
  fs->MAX_FILE_NUM = MAX_FILE_NUM;              // 1024
  fs->MAX_FILE_SIZE = MAX_FILE_SIZE;            // 1048576
  fs->FILE_BASE_ADDRESS = FILE_BASE_ADDRESS;    // 36864

  // initialize the Super Block
  for (int i = 0; i < SUPERBLOCK_SIZE; ++ i){
    volume[i] = 255;  // 255 means 1111 1111, each uchar represents 8-blocks bit map 
  }
}



__device__ u32 fs_open(FileSystem *fs, char *s, int op)
{ 
	//printf("fs_open was called\n");
  gtime += 1; // increment the timeing



  /* Implement open operation here */
  int i, j;
  int index = -1;
  bool is_match = true;
  u32 base;

  // serch the file info in FCB
  for (i = fs->SUPERBLOCK_SIZE; i < fs->FILE_BASE_ADDRESS; i += fs->FCB_SIZE){
	  is_match = true;
	  for (j = 0; j < fs->MAX_FILENAME_SIZE; ++j) {
		  if (s[j] != fs->volume[i + j]) {
			  is_match = false;
			  break;
		  }
	  }
	if (is_match) {
      index = i;
      break;
    }
  }
  if (index != -1) {    // the file exists

    // update the modified time
    fs->volume[index + 31] = gtime % 256;
    fs->volume[index + 30] = (gtime >> 8) % 256;
    u32 address = fs->volume[index+23] + (fs->volume[index+22]<<8) + (fs->volume[index+21]<<16) + (fs->volume[index+20]<<24);
    return address;

  }else{                // the file does not exist

    // create a new zero byte file
    if (op == 1) {      
      // serch for free blocks in the Super Block
      for (i = 0; i < fs->SUPERBLOCK_SIZE; i += 4){
        if (fs->volume[i] == 255){  // every uchar represents 8 bits(block)
          fs->volume[i] = 127;
          index = i * 8;    // #start block of the file
          break;
        }
      } // end for

      // add the info of new file into FCB
      base;     // start physical address of the target FCB 
      u32 created, modified, start, size;   // the file infomation

      base = fs->SUPERBLOCK_SIZE + index;  // 4096 + (index / 32) * 32
      start = fs->FILE_BASE_ADDRESS + index * (fs->STORAGE_BLOCK_SIZE);  // the physical address of the file in byte
      size = 0;           // the size of the file in in byte
      created = gtime;    // get current time as created time
      modified = gtime;   // get current time as modified time
      

      // store the file name
	  for (j = 0; j < fs->MAX_FILENAME_SIZE; ++j) {
		  fs->volume[base + j] = s[j];
		  if (s[j] == '\0')
			  break;
	  }

      // store the physical start address of the file (4B)
      fs->volume[base + 23] = start % 256;
      fs->volume[base + 22] = (start >> 8) % 256;
      fs->volume[base + 21] = (start >> 16) % 256;
      fs->volume[base + 20] = (start >> 24) % 256;

      // store the size of the file (4B)
      fs->volume[base + 27] = size % 256;
      fs->volume[base + 26] = (size >> 8) % 256;
      fs->volume[base + 25] = (size >> 16) % 256;
      fs->volume[base + 24] = (size >> 24) % 256;

      // store the created time 
      fs->volume[base + 29] = created % 256;
      fs->volume[base + 28] = (created >> 8) % 256;

      // store the modified time
      fs->volume[base + 31] = modified % 256;
      fs->volume[base + 30] = (modified >> 8) % 256;

      return start;
    } // end if

  } // end else
  
}


__device__ void fs_read(FileSystem *fs, uchar *output, u32 size, u32 fp)
{
  /* Implement read operation here */
  // gtime += 1;
	//printf("fs_read was called\n");
  for (int i = 0; i < size; ++ i) {
    output[i] = (char)fs->volume[fp++];
  }

}

__device__ u32 fs_write(FileSystem *fs, uchar* input, u32 size, u32 fp)
{	
	gtime++;

  /* Implement write operation here */
  u32 index, base, file_size;
  index = (fp - fs->FILE_BASE_ADDRESS) >> 10;   // the index of the entry of FCB
  base = fs->SUPERBLOCK_SIZE + index * fs->FCB_SIZE;

  // update the modified time
  fs->volume[base+31] = gtime % 256;
  fs->volume[base+30] = (gtime >> 8) % 256;

  // get the size of older file
  file_size = fs->volume[base+27] + (fs->volume[base+26]<<8) + (fs->volume[base+25]<<16) + (fs->volume[base+24]<<24);

  // update the size of file
  fs->volume[base + 27] = size % 256;
  fs->volume[base + 26] = (size >> 8) % 256;

  // write the physical storage
  for (int i = 0; i < size; ++ i){

    // update the super block everytime writing a new block
    if (i % 32 == 0) {
      int block_order = i / 32;
      uchar target = fs->volume[index * 4 + block_order / 8];
	  if (target / (1 << (7 - (block_order % 8))) % 2 == 1)
		target -= (1 << (7 - (block_order % 8)));         // target block: 1 -> 0
      fs->volume[index * 4 + block_order / 8] = target;
    }
    // write
    fs->volume[fp++] = input[i]; 
  }

  // cleanup the older contents left
  if (file_size > size) {
    for (int i = fp; i < fp + file_size - size; ++i){
      fs->volume[i] = '\0';
    }
  }

  return fp;

}
__device__ void fs_gsys(FileSystem *fs, int op)
{
  /* Implement LS_D and LS_S operation here */

  // data structure to sort the modified time
  // the element of sort_arr is 4 bytes 
  // the first two bytes represent the FCB entry
  // the last two bytes represent the modified time
  u32 sort_arr[1024];
  int arr_size = 0;                                   // track the size of array

  u32 base, modified, size, entry;
  // LS_D: file name, order by modified time
  if (op == 0) {
    for (int i = 0; i < fs->FCB_ENTRIES; ++ i){
      base = fs->SUPERBLOCK_SIZE + i * fs->FCB_SIZE;
      // FCB entry is not empty
      if (fs->volume[base] != '\0'){
        entry = i;
        modified = fs->volume[base+31] + (fs->volume[base+30] << 8);
		    int ptr = arr_size - 1;
        sort_arr[arr_size++] = (entry << 16) + modified; // add to the sort array
        // insertion sort
        while (ptr >= 0 && modified < sort_arr[ptr] % (1 << 16)) {
          sort_arr[ptr + 1] = sort_arr[ptr];
          sort_arr[ptr] = (entry << 16) + modified;
          ptr--;
        }	// end while
      }	// end if
    } // end for

	// print information
	printf("===sort by modified time===\n");
	while (--arr_size >= 0) {
		entry = sort_arr[arr_size] >> 16; 
		printf("%s\n", &fs->volume[fs->SUPERBLOCK_SIZE + entry * fs->FCB_SIZE]);
	}

  }	// end if

  // LS_S: file name and size, order by size
  if (op == 1) {
	  for (int i = 0; i < fs->FCB_ENTRIES; ++i) {
		  base = fs->SUPERBLOCK_SIZE + i * fs->FCB_SIZE;
		  // FCB entry is not empty
		  if (fs->volume[base] != '\0') {
			  entry = i;
			  size = fs->volume[base + 27] + (fs->volume[base + 26] << 8);
			  int ptr = arr_size - 1;
			  sort_arr[arr_size++] = (entry << 16) + size; // add to the sort array
			  // insertion sort
			  while (ptr >= 0 && size <= sort_arr[ptr] % (1 << 16)) {
				  sort_arr[ptr + 1] = sort_arr[ptr];
				  sort_arr[ptr] = (entry << 16) + size;
				  ptr--;
			  }	// end while
		  }	// end if
	  } // end for

	  // print information
	  printf("===sort by file size===\n");
	  while (--arr_size >= 0) {
		  entry = sort_arr[arr_size] >> 16;
		  base = fs->SUPERBLOCK_SIZE + entry * fs->FCB_SIZE;
		  size = sort_arr[arr_size] % (1 << 16);
		  printf("%s %d\n", &fs->volume[base], size);
	  }

  }	// end if
}

__device__ void fs_gsys(FileSystem *fs, int op, char *s)
{
	/* Implement rm operation here */
	int i, j;
	int index = -1;
	bool is_match;
	if (op == 2) {
		for (i = fs->SUPERBLOCK_SIZE; i < fs->FILE_BASE_ADDRESS; i += fs->FCB_SIZE) {
			is_match = true;
			for (j = 0; j < fs->MAX_FILENAME_SIZE; ++j) {
				if (s[j] != fs->volume[i + j]) {
					is_match = false;
					break;
				}
			}
			if (is_match) {
				index = i;
				break;
			}
		} // end for
		if (index == -1) {
			printf("Cannot find file %s, please check!\n", s);
		}
		else {
			u32 address = fs->volume[index + 23] + (fs->volume[index + 22] << 8) + (fs->volume[index + 21] << 16) + (fs->volume[index + 20] << 24);
			u32 size = fs->volume[index + 27] + (fs->volume[index + 26] << 8);

			// release the file space
			for (i = 0; i < size; ++i) {
				fs->volume[address + i] = '\0';
			}
			// release the corresponding FCB
			for (i = 0; i < fs->FCB_SIZE; ++i) {
				fs->volume[index + i] = '\0';
			}
			// update the super block
			index = (index - fs->SUPERBLOCK_SIZE) / fs->FCB_SIZE;
			for (i = 0; i < 4; ++i) {
				fs->volume[index * 4 + i] = 255;
			}
		}
	}


}
