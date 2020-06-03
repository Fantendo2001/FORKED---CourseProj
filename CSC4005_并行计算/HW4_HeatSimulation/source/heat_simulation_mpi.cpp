#include <iostream>
#include <mpi.h>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <sys/time.h>
using namespace std;



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
    int SIZE = 200;             // the size of the window is SIZE*SIZE
    int ITERATIONS = 20000;       // number of iterations to simulate
    
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

    // ******** start of MPI ********
    MPI_Init(&argc, &argv);
    int taskid,
    numtasks;
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    
    if (argc > 1) SIZE = atoi(argv[1]);

    int X_RESN=SIZE;
    int Y_RESN=SIZE;
    struct timeval timeStart, timeEnd, timeSystemStart;
    double runTime=0, systemRunTime;
    
    if (taskid == 0){

        /* set window size */
        
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
        color.red=60000; //range from 0~65535
        color.green=60000;
        color.blue=60000;
        
        Status rc1=XAllocColor(display,DefaultColormap(display, screen),&color);
        //set the color and attribute of the graphics content
        XSetForeground (display, gc, color.pixel);
        XSetBackground (display, gc, BlackPixel (display, screen));
        XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);
        
        gettimeofday(&timeStart, NULL );

    }

    // initialize the room
    double *ROOM = (double *) malloc(sizeof(double)*(X_RESN*Y_RESN));

    int count[numtasks], disp[numtasks];    // for gatherv use
    double * local_data;
    
    disp[0] = 0;
    int quotient = SIZE / numtasks;
    int remainder = SIZE % numtasks;
    
    for (int i = 0; i < numtasks; ++ i) {
        if (i < remainder) {
            count[i] = (quotient + 1) * SIZE;
        }else{
            count[i] = quotient * SIZE;
        }
        if (i > 0) disp[i] = disp[i-1] + count[i-1];
    }

    // the array that stores the result of computation
    local_data = (double *)malloc(sizeof(double) * count[taskid]);

    // the index of the first data of the first target body
    int start_row = disp[taskid] / SIZE;
    // the index of the first data of the body after the last target body
    int end_row = start_row + count[taskid] / SIZE;

    // initialize the temperature
    if (taskid == 0){
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
    }   // end if

    // start iteration
    int iter = 0;
    while (iter++ < ITERATIONS){

        // Broadcast the updated ROOM to every node
        MPI_Bcast(ROOM, SIZE*SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // compute and store the result to local data
        for (int i = start_row; i < end_row; ++ i){
            for (int j = 0; j < SIZE; ++j){
                if (i == 0 || j == 0 || i == SIZE-1 || j == SIZE-1){
                    local_data[(i-start_row)*SIZE + j] = ROOM[i*SIZE + j];
                }else{
                    local_data[(i-start_row)*SIZE + j] = 0.25 * (ROOM[(i-1)*SIZE + j] + ROOM[(i+1)*SIZE + j] + ROOM[i*SIZE + j-1] + ROOM[i*SIZE + j+1]);
                }
            }
        } // end for i

        // Gather the results
        MPI_Gatherv(local_data, count[taskid], MPI_DOUBLE, ROOM, count, disp, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        // The root process plot the figure
        if (iter % 100 != 0 || taskid != 0) continue;
        double temperature;
        for (int i = 0; i < X_RESN; ++i){
            for (int j = 0; j < Y_RESN; ++j){

                temperature = ROOM[i*X_RESN + j];
                
                // color.red=(int)600*temperature; //range from 0~65535
                // color.green=0;
                // color.blue=65535 - (int)600*temperature;

                long unsigned c_pixel;
                c_pixel = get_cpixel(temperature);
                // XAllocColor(display,DefaultColormap(display, screen),&color);
                XSetForeground (display, gc, c_pixel);
                
                XDrawPoint (display, win, gc, i, j);
            }
        }

        XFlush (display);

    }// end iteration

    free(ROOM);
    free(local_data);
    MPI_Finalize();
    
    if (taskid == 0){
        gettimeofday( &timeEnd, NULL );
        runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;
        // display information
        printf("Name: Hongpeng Yi\nStudent ID: 117020343\nAssignment 4, Heat Simulation, MPI implementation.\nRunTime is %lfs, with %d processes.\nWindow size is %d*%d; total %d iterations.\n", runTime, numtasks, SIZE, SIZE, ITERATIONS);
        sleep(10);
    }
    return 0;
}