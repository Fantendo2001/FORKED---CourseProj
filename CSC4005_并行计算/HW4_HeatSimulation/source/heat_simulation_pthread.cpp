#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <sys/time.h>
using namespace std;

int NUM_THREADS = 1;
int SIZE = 200;             // the size of the window is SIZE*SIZE
int ITERATIONS = 20000;       // number of iterations to simulate

typedef struct _thread_data{
    int thread_id;
    double *room;
    double *temp_table;
}thread_data;

unsigned long get_cpixel(double temperature){
    unsigned long c_pixel = 3014865;
    int temp = (int)temperature;
    int r = (temp - 20) / 5;
    // c_pixel += 786420 * r;
    c_pixel += 786420 * r;
    return c_pixel;
}

void *cal_func(void *arg) {
    
    int tid;
    double *ROOM;
    double *temp_table;
    
    // decode the delivered data
    thread_data *input_data = (thread_data *) arg;
    tid = input_data->thread_id;
    ROOM = input_data->room;
    temp_table = input_data->temp_table;
    
    int start, end, num, remain;
    
    // specify the target rows
    num = SIZE / NUM_THREADS;
    remain = SIZE % NUM_THREADS;
    if (tid < remain){
        num ++;
        start = num * tid;
    }else{
        start = num * tid + remain;
    }
    end = start + num;

    // compute for target rows
    for (int i = start; i < end; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (i == 0 || j == 0 || i == SIZE-1 || j == SIZE-1){
                temp_table[i*SIZE + j] = ROOM[i*SIZE + j];
            }else{
                temp_table[i*SIZE + j] = 0.25 * (ROOM[(i-1)*SIZE + j] + ROOM[(i+1)*SIZE + j] + ROOM[i*SIZE + j-1] + ROOM[i*SIZE + j+1]);
            }
        }
    }

    pthread_exit(NULL);
} // end cal_func

int main(int argc, char* argv[])
{
    if (argc > 1) SIZE = atoi(argv[1]);
    if (argc > 2) NUM_THREADS = atoi(argv[2]);
    
    // ---------- Initialization for plotting ----------
    Window          win;
    char            *window_name = "test", *display_name = NULL;                     /* initialization for a window */
    Display         *display;
    GC              gc;   //this is a graphic content, it could be a pixel color
    unsigned long            valuemask = 0;
    XGCValues       values; //value of the graphics content
    XSizeHints      size_hints;
    Pixmap          bitmap;
    XSetWindowAttributes attr[1];
    int             width, height,  /* window size */
    x, y,                           /* window position */
    border_width,                   /*border width in pixels */
    display_width, display_height,  /* size of screen */
    screen;                         /* which screen */
    
    if (  (display = XOpenDisplay (display_name)) == NULL ) {
        fprintf (stderr, "drawon: cannot connect to X server %s\n",
                 XDisplayName (display_name) );
        exit (-1);
    }
    
    /* get screen size */
    screen = DefaultScreen (display);
    display_width = DisplayWidth (display, screen);
    display_height = DisplayHeight (display, screen);
    
    /* set window size */
    int X_RESN=SIZE;
    int Y_RESN=SIZE;
    width = X_RESN;
    height = Y_RESN;
    
    /* set window position */
    
    x = 0;
    y = 0;
    
    /* create opaque window */
    
    border_width = 4;
    win = XCreateSimpleWindow (display, RootWindow (display, screen),
                               x, y, width, height, border_width,
                               BlackPixel (display, screen), BlackPixel (display, screen)); //Change to WhitePixel (display, screen) if you want a white background
    
    size_hints.flags = USPosition|USSize;
    size_hints.x = x;
    size_hints.y = y;
    size_hints.width = width;
    size_hints.height = height;
    size_hints.min_width = 300;
    size_hints.min_height = 300;
    
    XSetNormalHints (display, win, &size_hints);
    XStoreName(display, win, window_name);
    
    /* create graphics context */
    gc = XCreateGC (display, win, valuemask, &values);
    XSetBackground (display, gc, BlackPixel (display, screen));
    XSetForeground (display, gc, BlackPixel (display, screen));
    XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);
    
    attr[0].backing_store = Always;
    attr[0].backing_planes = 1;
    attr[0].backing_pixel = BlackPixel (display, screen);
    
    XChangeWindowAttributes(display, win, CWBackingStore | CWBackingPlanes | CWBackingPixel, attr);
    
    XMapWindow (display, win);
    XSync(display, 0);
    
    XFlush (display);
    
    XColor color;
    color.red=0; //range from 0~65535
    color.green=0;
    color.blue=65535;
    
    Status rc1=XAllocColor(display,DefaultColormap(display, screen),&color);
    //set the color and attribute of the graphics content
    XSetForeground (display, gc, color.pixel);
    XSetBackground (display, gc, color.pixel);
    XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);

    // ---------- end initialization for plotting ----------
    
    struct timeval timeStart, timeEnd, timeSystemStart;
    double runTime=0, systemRunTime;
    gettimeofday(&timeStart, NULL );

    // ========== Start Simulation =========== 

    

    // initialize the room and temperature
    double *ROOM = (double *) malloc(sizeof(double)*(X_RESN*Y_RESN));

    for (int i = 0; i < X_RESN; ++i){
        for (int j = 0; j < Y_RESN; ++j){
            // initialize temperature of room and walls
            ROOM[i*X_RESN + j] = 20;
            // initialize temperature of fire place
            if (i == 0 && j > X_RESN*2/5 && j < X_RESN*3/5){
                ROOM[i*X_RESN + j] = 100;
            }
        }
    }
    
    // prepare a table to temperarily store the results
    double *temp_table = (double *) malloc(sizeof(double)*(X_RESN*Y_RESN));

    // start pthread

    int rc;
    int i, j;
    void *return_data;
    pthread_t thread[NUM_THREADS];
    thread_data input_data[NUM_THREADS];
    
    for (i = 0; i < NUM_THREADS; ++ i){
        input_data[i].thread_id = i;
        input_data[i].room = ROOM;
        input_data[i].temp_table = temp_table;
    }

    // start iteration
    int count = 0;
    while (count++ < ITERATIONS){

        // distribute the computation work
        for (i = 0; i < NUM_THREADS; ++ i){
            rc = pthread_create(&thread[i], NULL, cal_func, &input_data[i]);
            if (rc) {
                fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
                return EXIT_FAILURE;
            }
        }
        // gather the threads
        for (i = 0; i < NUM_THREADS; ++i) {
            pthread_join(thread[i], &return_data);
            // printf("the return data is %d\n", return_data);
        }
        

        // update the ROOM and plot the result
        double temperature;
        for (int i = 0; i < X_RESN; ++i){
            for (int j = 0; j < Y_RESN; ++j){

                ROOM[i*X_RESN + j] = temp_table[i*X_RESN + j];
                temperature = ROOM[i*X_RESN + j];
                
                if (count % 10 != 0) continue;
                // color.red=65535; //range from 0~65535
                // color.green=0;
                // color.blue=65535 - (int)600*(temperature-20);

                
                long unsigned c_pixel;
                c_pixel = get_cpixel(temperature);
                // XAllocColor(display,DefaultColormap(display, screen),&color);
                // c_pixel = color.pixel;
                XSetForeground (display, gc, c_pixel);
                
                XDrawPoint (display, win, gc, i, j);

            }
        }

        if (count % 10 != 0) continue;
        XFlush (display);
        usleep(1000);

    } // end while
    // ========== End Simulation ===========

    gettimeofday( &timeEnd, NULL );
    runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;
    // display information
    printf("Name: Hongpeng Yi\nStudent ID: 117020343\nAssignment 4, Heat Simulation, Pthread implementation.\nRunTime is %lfs.\nWindow size is %d*%d; total %d iterations.\n", runTime, SIZE, SIZE, ITERATIONS);

    sleep(10);
    return 0;
}