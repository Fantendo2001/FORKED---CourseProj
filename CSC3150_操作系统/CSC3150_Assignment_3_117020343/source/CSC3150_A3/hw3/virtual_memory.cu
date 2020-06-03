#include "virtual_memory.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>




__device__ void init_invert_page_table(VirtualMemory *vm) {

  for (int i = 0; i < vm->PAGE_ENTRIES; i++) {
    vm->invert_page_table[i] = 0x80000000; // invalid := MSB is 1
	vm->invert_page_table[i + vm->PAGE_ENTRIES] = 0;//valid bit 0 means can be used
	vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] = -2;	// -2 indicates that this line has not been used yet
	vm->invert_page_table[i + 3 * vm->PAGE_ENTRIES] = -2;	// -2 indicates that this line has not been used yet
  }
}


__device__ void vm_init(VirtualMemory *vm, uchar *buffer, uchar *storage,
                        u32 *invert_page_table, int *pagefault_num_ptr,
                        int PAGESIZE, int INVERT_PAGE_TABLE_SIZE,
                        int PHYSICAL_MEM_SIZE, int STORAGE_SIZE,
                        int PAGE_ENTRIES) {
  // init variables
  vm->buffer = buffer;
  vm->storage = storage;
  vm->invert_page_table = invert_page_table;
  vm->pagefault_num_ptr = pagefault_num_ptr;
  vm->currenTime = 0;
  vm->storageCounter = 0;


  // init constants
  vm->PAGESIZE = PAGESIZE;
  vm->INVERT_PAGE_TABLE_SIZE = INVERT_PAGE_TABLE_SIZE;
  vm->PHYSICAL_MEM_SIZE = PHYSICAL_MEM_SIZE;
  vm->STORAGE_SIZE = STORAGE_SIZE;
  vm->PAGE_ENTRIES = PAGE_ENTRIES;

  // before first vm_write or vm_read
  init_invert_page_table(vm);
}

__device__ uchar vm_read(VirtualMemory *vm, u32 addr) {
  /* Complete vm_read function to read single element from data buffer */
	int offset = addr % 32;
	int base = addr >> 5;
	int target_index, head_index, tail_index;
	target_index = head_index = tail_index = -1;
	int left, right;
	for (int i = 0; i <vm->PAGE_ENTRIES; ++i){
		if (target_index < 0 && vm->invert_page_table[i] == base) target_index = i;	// find the corresponding index
		if (head_index < 0 && vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] == -1) head_index = i;	// find the most recent index
		if (tail_index < 0 && vm->invert_page_table[i + 3 * vm->PAGE_ENTRIES] == -1) tail_index = i;	// find the least recent index
		if (target_index >= 0 && head_index >= 0) break;	// break if the necessary indexes have been found
	}
	if (target_index >= 0) {
		// change the linked-list to refresh the priority
		left = vm->invert_page_table[target_index + 2 * vm->PAGE_ENTRIES];
		right = vm->invert_page_table[target_index + 3 * vm->PAGE_ENTRIES];
		if (left != -1) {		// target_index is not the head_index
			vm->invert_page_table[left + 3 * vm->PAGE_ENTRIES] = right;	// left.next = right
			vm->invert_page_table[target_index + 2 * vm->PAGE_ENTRIES] = -1;	// target.previous = -1
			if (right != -1) 		// target_index is not the last 
				vm->invert_page_table[right + 2 * vm->PAGE_ENTRIES] = left;	// right.previous = left
			vm->invert_page_table[head_index + 2 * vm->PAGE_ENTRIES] = target_index;	// head.previous = target
			vm->invert_page_table[target_index + 3 * vm->PAGE_ENTRIES] = head_index;	// target.next = head
		}
		printf("Read: %d; page faults: %d\n", (int)addr, vm->pagefault_num_ptr[0]);
		return vm->buffer[target_index * vm->PAGESIZE + offset];
	}
	else {	// page fault happens
		vm->pagefault_num_ptr[0] += 1;	// count the page fault
		// page swap
		int new_tail = vm->invert_page_table[tail_index + 2 * vm->PAGE_ENTRIES];
		// swap out
		for (int i = 0; i < vm->PAGESIZE; ++ i) {
			vm->storage[vm->invert_page_table[tail_index] * vm->PAGESIZE + i] = vm->buffer[tail_index * vm->PAGESIZE + i]; 
		}
		// swap in
		for (int i = 0; i < vm->PAGESIZE; ++ i) {
			vm->buffer[tail_index * vm->PAGESIZE + i] =  vm->storage[base * vm->PAGESIZE + i];
		}
		
		vm->invert_page_table[tail_index] = base;	// edit the new index of the page table
		vm->invert_page_table[new_tail + 3 * vm->PAGE_ENTRIES] = -1;	// new_tail.next = -1
		vm->invert_page_table[tail_index + 2 * vm->PAGE_ENTRIES] = -1;
		vm->invert_page_table[tail_index + 3 * vm->PAGE_ENTRIES] = head_index;
		vm->invert_page_table[head_index + 2 * vm->PAGE_ENTRIES] = tail_index;
		printf("Read: %d; page faults: %d\n", (int)addr, vm->pagefault_num_ptr[0]);
		return vm->buffer[tail_index * vm->PAGESIZE + offset];
	}

  return 123; //TODO
}


__device__ void vm_write(VirtualMemory *vm, u32 addr, uchar value) {
  /* Complete vm_write function to write value into data buffer */
	// vm: virtual memory
	// addr: the order of the input value, the last 5-bit is the offset and the remain 27-bit is the base
	int offset = addr % 32;
	int base = addr >> 5;
	int target_index, head_index, empty_index, tail_index;
	int left, right;
	target_index = head_index = empty_index = tail_index = -1;

	// get the index needed
	for (int i = 0; i < vm->PAGE_ENTRIES; i++) {
		if (target_index < 0 && vm->invert_page_table[i] == base && vm->invert_page_table[i + vm->PAGE_ENTRIES] == 1)
			target_index = i;		// find the corresponding index
		if (head_index < 0 && vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] == -1) head_index = i;	// find the most recent index
		if (tail_index < 0 && vm->invert_page_table[i + 3 * vm->PAGE_ENTRIES] == -1) tail_index = i;	// find the least recent index
		if (empty_index < 0 && vm->invert_page_table[i] == 0x80000000) empty_index = i;	// find the empty index
		if (target_index >= 0 && head_index >= 0) break;	// break if the necessary indexes have been found
	}

	if (target_index >= 0) {
		vm->buffer[target_index * vm->PAGESIZE + offset] = value;
		// change the linked-list to refresh the priority
		left = vm->invert_page_table[target_index + 2 * vm->PAGE_ENTRIES];
		right = vm->invert_page_table[target_index + 3 * vm->PAGE_ENTRIES];
		if (left != -1) {		// target_index is not the head_index
			vm->invert_page_table[left + 3 * vm->PAGE_ENTRIES] = right;	// left.next = right
			vm->invert_page_table[target_index + 2 * vm->PAGE_ENTRIES] = -1;	// target.previous = -1
			if (right != -1) 		// target_index is not the last 
				vm->invert_page_table[right + 2 * vm->PAGE_ENTRIES] = left;	// right.previous = left
			vm->invert_page_table[head_index + 2 * vm->PAGE_ENTRIES] = target_index;	// head.previous = target
			vm->invert_page_table[target_index + 3 * vm->PAGE_ENTRIES] = head_index;	// target.next = head
		}
		printf("write: %d; page faults: %d\n", (int)addr, vm->pagefault_num_ptr[0]);
	}
	else {	// page fault happens
		vm->pagefault_num_ptr[0] += 1;	// count the page fault
		if (empty_index >= 0) {		// the page table is not empty
			vm->invert_page_table[empty_index] = base;	// edit the new index of the page table
			vm->invert_page_table[empty_index + vm->PAGE_ENTRIES] = 1;	// change the status
			vm->buffer[empty_index * vm->PAGESIZE + offset] = value;	// write into buffer
			printf("write: %d; page faults: %d\n", (int)addr, vm->pagefault_num_ptr[0]);
			if (head_index >= 0) {
				vm->invert_page_table[head_index + 2 * vm->PAGE_ENTRIES] = empty_index;
				vm->invert_page_table[empty_index + 2 * vm->PAGE_ENTRIES] = -1;
				vm->invert_page_table[empty_index + 3 * vm->PAGE_ENTRIES] = head_index;
			}
			else {
				vm->invert_page_table[empty_index + 2 * vm->PAGE_ENTRIES] = -1;
				vm->invert_page_table[empty_index + 3 * vm->PAGE_ENTRIES] = -1;
			}
		}
		else {						// the page table is full -- page swap
			int new_tail = vm->invert_page_table[tail_index + 2 * vm->PAGE_ENTRIES];
			// swap out
			for (int i = 0; i < vm->PAGESIZE; ++ i) {
				vm->storage[vm->invert_page_table[tail_index] * vm->PAGESIZE + i] = vm->buffer[tail_index * vm->PAGESIZE + i]; 
			}
			vm->buffer[tail_index * vm->PAGESIZE + offset] = value;
			printf("write: %d; page faults: %d\n", (int)addr, vm->pagefault_num_ptr[0]);
			vm->invert_page_table[tail_index] = base;	// edit the new index of the page table
			vm->invert_page_table[new_tail + 3 * vm->PAGE_ENTRIES] = -1;	// new_tail.next = -1
			vm->invert_page_table[tail_index + 2 * vm->PAGE_ENTRIES] = -1;
			vm->invert_page_table[tail_index + 3 * vm->PAGE_ENTRIES] = head_index;
			vm->invert_page_table[head_index + 2 * vm->PAGE_ENTRIES] = tail_index;
		}
	}
}


__device__ void vm_snapshot(VirtualMemory *vm, uchar *results, int offset,
                            int input_size) {
  /* Complete snapshot function togther with vm_read to load elements from data
   * to result buffer */
	printf("Start of snapshot:\n");
   for (int i = 0; i < input_size; ++i){
	   results[i] = vm_read(vm, i);
	   printf("In snapshot - ");
   }
}

