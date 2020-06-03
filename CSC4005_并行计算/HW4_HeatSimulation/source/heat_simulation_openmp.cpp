#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <sys/time.h>
using namespace std;

int NUM_THREADS = 2;
int SIZE = 200;             // the size of the window is SIZE*SIZE
int ITERATIONS = 20000;       // number of iterations to simulate

// preset color.pixel based on temperature
unsigned long get_cpixel(double temperature){
    unsigned long c_pixel = 3014865;
    int temp = (int)temperature;
    int r = (temp - 20) / 5;
    c_pixel += 786420 * r;
    return c_pixel;
}


int main(int argc, char* argv[])
{
    if (argc > 1) SIZE = atoi(argv[1]);
    if (argc > 2) NUM_THREADS = atoi(argv[2]);

    omp_set_num_threads(NUM_THREADS);
    
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
                               3014865, 3014865); //Change to WhitePixel (display, screen) if you want a white background
    
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
    XSetBackground (display, gc, 3014865);
    XSetForeground (display, gc, 3014865);
    XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);
    
    attr[0].backing_store = Always;
    attr[0].backing_planes = 1;
    attr[0].backing_pixel = 3014865;
    
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

    XFlush (display);

    // ---------- end initialization for plotting ----------
    
    struct timeval timeStart, timeEnd, timeSystemStart;
    double runTime=0, systemRunTime;
    gettimeofday(&timeStart, NULL );

    // ========== Start Simulation =========== 

    // initialize the room and temperature
    double *ROOM = (double *) malloc(sizeof(double)*(X_RESN*Y_RESN));
    int i, j;
#pragma omp parallel for private(j) shared(ROOM)
    for (i = 0; i < X_RESN; ++i){
        for (j = 0; j < Y_RESN; ++j){
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

    // start iteration
    int count = 0;
    while (count++ < ITERATIONS){

#pragma omp parallel for private(j) shared(temp_table, ROOM)
        // computing the temperature
        for (i = 0; i < X_RESN; ++i){
            for (j = 0; j < Y_RESN; ++j){
                if (i == 0 || j == 0 || i == SIZE-1 || j == SIZE-1){
                    temp_table[i*SIZE + j] = ROOM[i*SIZE + j];
                }else{
                    temp_table[i*SIZE + j] = 0.25 * (ROOM[(i-1)*SIZE + j] + ROOM[(i+1)*SIZE + j] + ROOM[i*SIZE + j-1] + ROOM[i*SIZE + j+1]);
                }
            }
        }

        double temperature;
        long unsigned c_pixel;
        // update the ROOM
        for (i = 0; i < X_RESN; ++i){
            for (j = 0; j < Y_RESN; ++j){

                ROOM[i*X_RESN + j] = temp_table[i*X_RESN + j];
                temperature = ROOM[i*X_RESN + j];
                
                if (count % 100 != 0) continue;
                // color.red=(int)600*temperature; //range from 0~65535
                // color.green=0;
                // color.blue=65535 - (int)600*temperature;

                c_pixel = get_cpixel(temperature);
                // XAllocColor(display,DefaultColormap(display, screen),&color);
                XSetForeground (display, gc, c_pixel);
                
                XDrawPoint (display, win, gc, i, j);

            }
        }
        if (count % 100 != 0) continue;
        XFlush (display);
    }
    // ========== End Simulation ===========

    gettimeofday( &timeEnd, NULL );
    runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;
    // display information
    printf("Name: Hongpeng Yi\nStudent ID: 117020343\nAssignment 4, Heat Simulation, OpenMP implementation.\nRunTime is %lfs, with %d threads.\nWindow size is %d*%d; total %d iterations.\n", runTime, NUM_THREADS, SIZE, SIZE, ITERATIONS);
    free(ROOM);
    free(temp_table);
    sleep(10);
    return 0;
}