#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define ROW 10
#define COLUMN 50 
//#define LOG_SIZE 15

pthread_mutex_t mutex;

int state = 0;  // on-going:0 ; win:1 ; lose:2 ; quit:3
char buf = '|';     // used for frog movement

struct Node{
	int x , y; 
	Node( int _x , int _y ) : x( _x ) , y( _y ) {}; 
	Node(){} ; 
} frog ; 

char map[ROW+10][COLUMN];

// Determine a keyboard is hit or not. If yes, return 1. If not, return 0. 
int kbhit(void){
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}


void *logs_move( void *t ){
    
    long tid = (long)t;
    int lx = rand() % (COLUMN - 1);
    int LOG_SIZE;
    LOG_SIZE = (COLUMN / 8) + (rand() % (COLUMN / 4));
    int frog_on_log;
    int i;
    
    while (state == 0){
        usleep(100000); // the value is proportional to the speed of movements
        
        /*  Move the logs  */
        frog_on_log = 0;
        if (tid % 2 == 0){
            if (frog.x == tid + 1) frog.y += 1;
            map[tid + 1][lx] = ' ';
            for (i = lx + 1; i < lx + 1 + LOG_SIZE; ++ i){
                map[tid + 1][i % (COLUMN-1)] = '=';
                if (frog.x == tid + 1 && i % (COLUMN-1) == frog.y) frog_on_log = 1;
            }
            lx = (lx + 1) % (COLUMN - 1);
        }else{
            if (frog.x == tid + 1) frog.y -= 1;
            map[tid + 1][(lx + LOG_SIZE) % (COLUMN - 1)] = ' ';
            for (i = lx; i < lx + LOG_SIZE; ++ i){
                map[tid + 1][i % (COLUMN - 1)] = '=';
                if (frog.x == tid + 1 && i % (COLUMN-1) == frog.y) frog_on_log = 1;
            }
            lx = (lx + COLUMN - 2) % (COLUMN - 1);
        }
        if (frog.x != tid + 1) frog_on_log = 1;
        map[frog.x][frog.y] = '0' ;
        
        pthread_mutex_lock(&mutex);
        /*  Check keyboard hits, to change frog's position or quit the game. */
        if (kbhit()){
            char dir = getchar();
            map[frog.x][frog.y] = buf;
            
            if ((dir == 'w' || dir == 'W') && frog.x > 0)
                frog.x -= 1;
            if ((dir == 's' || dir == 'S') && frog.x < ROW)
                frog.x += 1;
            if ((dir == 'a' || dir == 'A') && frog.y > 0)
                frog.y -= 1;
            if ((dir == 'd' || dir == 'D') && frog.y < COLUMN - 2)
                frog.y += 1;
            if (dir == 'q' || dir == 'Q')
                state = 3;
            buf = map[frog.x][frog.y];
            map[frog.x][frog.y] = '0' ;
        }
        
        /*  Check game's status  */
        // win if frog arrive the upper bank
        if (frog.x == 0) state = 1;
        // lose if frog reach the left side or right side or if frog steps into the river
        if (frog.y == -1 || frog.y == COLUMN - 1 || !frog_on_log) state =  2;
        
        /*  Print the map on the screen  */
        printf("\033[H\033[2J");
        for(i = 0; i <= ROW; ++i)
            puts( map[i] );
        if (state == 1) printf("\033[H\033[2JYou win the game!!\n");
        if (state == 2) printf("\033[H\033[2JYou lose the game!!\n");
        if (state == 3) printf("\033[H\033[2JYou exit the game.\n");
        pthread_mutex_unlock(&mutex);
    }
    

    
    pthread_exit(NULL);
}

int main( int argc, char *argv[] ){

	// Initialize the river map and frog's starting position
	memset( map , 0, sizeof( map ) ) ;
	int i , j ; 
	for( i = 1; i < ROW; ++i ){	
		for( j = 0; j < COLUMN - 1; ++j )	
			map[i][j] = ' ' ;
	}	

	for( j = 0; j < COLUMN - 1; ++j )	
		map[ROW][j] = map[0][j] = '|' ;

//    for( j = 0; j < COLUMN - 1; ++j )
//        map[0][j] = map[0][j] = '|' ;

	frog = Node( ROW, (COLUMN-1) / 2 ) ; 
	map[frog.x][frog.y] = '0' ; 

	//Print the map into screen
	for( i = 0; i <= ROW; ++i)	
		puts( map[i] );


	/*  Create pthreads for wood move and frog control.  */
    pthread_t threads[ROW - 1];
    long tids[ROW - 1];
    for (i = 0; i < ROW - 1; ++ i){
        tids[i] = i;
    }
    
    int rc;
    srand(time(0)); // used to avoid pseudo-random
    pthread_mutex_init(&mutex, NULL);
    printf("\033[H\033[2J");
    for (i = 0; i < ROW - 1; ++ i){
        rc = pthread_create(&threads[i], NULL, logs_move, (void*)tids[i]);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d", rc);
            exit(1);
        }
    }
    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);
	

	return 0;

}
