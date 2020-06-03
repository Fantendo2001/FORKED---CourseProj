#include <omp.h>
#include <iostream>
#include <mpi.h>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <time.h>
#include <math.h>
using namespace std;

int main (int argc, char* argv[]){
    
    int SIZE = 200;             // the size of the window
    int NUM_BODIES = 200;       // number of bodies simulated
    double BODY_RADIUS = 0.001;     // Assume all the bodies have the same radius
    int ITERATIONS = 500;       // number of iterations to simulate
    double G = 0.0000001;        // not real G, it is adjusted by testing to show the proper body movement
    int NUM_THREADS = 2;
    
    Window          win;
    char            *window_name = "test", *display_name = NULL;                     /* initialization for a window */
    Display         *display;
    GC              gc;   //this is a graphic content, it could be a pixel color
    unsigned long            valuemask = 0;
    XGCValues       values; //value of the graphics content
    XSizeHints      size_hints;
    Pixmap          bitmap;
    XSetWindowAttributes attr[1];
    int             width, height,                  /* window size */
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
    
    if (argc > 1) NUM_BODIES = atoi(argv[1]);
    if (argc > 2) NUM_THREADS = atoi(argv[2]);
    
    omp_set_num_threads(NUM_THREADS);
    
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
    
    /*
        A big array that stores the information of all the bodies
            {mass, x, y, vx, vy} in order
        Every 5 data represents one body,
            so total 5 * NUM_BODIES data in the array
        Relationship:
            bodies[5*i]   -- bodies[i].mass
            bodies[5*i+1] -- bodies[i].x
            bodies[5*i+2] -- bodies[i].y
            bodies[5*i+3] -- bodies[i].vx
            bodies[5*i+4] -- bodies[i].vy
     */
    double *bodies=(double *)malloc(sizeof(double) * (5 * NUM_BODIES));
    int i, j, k, quotient, remainder;
    double dx, dy, r, a, ax, ay, v1, v2;
    
    int count[numtasks], disp[numtasks];    // for gatherv use
    double * local_data;
    
    disp[0] = 0;
    quotient = NUM_BODIES / numtasks;
    remainder = NUM_BODIES % numtasks;
    
    for (i = 0; i < numtasks; ++ i) {
        if (i < remainder) {
            count[i] = (quotient + 1) * 5;
        }else{
            count[i] = quotient * 5;
        }
        if (i > 0) disp[i] = disp[i-1] + count[i-1];
    }
    
    // the array that stores the result of computation
    local_data = (double *)malloc(sizeof(double) * count[taskid]);
    
    // the index of the first data of the first target body
    int start_body = disp[taskid] / 5;
    // the index of the first data of the body after the last target body
    int end_body = start_body + count[taskid] / 5;
    
    if (taskid == 0) {
        srand((int)time(NULL));
        // initialization of the bodies
#pragma omp parallel for
        for (i = 0; i < NUM_BODIES; ++i){
            if (i == 0) {
                bodies[5*i] = 999999999;
                bodies[5*i+1] = SIZE /3 + (rand()/(double)RAND_MAX) * SIZE / 3;
                bodies[5*i+2] = SIZE /3 + (rand()/(double)RAND_MAX) * SIZE / 3;
                bodies[5*i+3] = 0;
                bodies[5*i+4] = 0;
            }else{
                bodies[5*i] = 1000 + rand() % 10000;                // mass
                bodies[5*i+1] = (rand()/(double)RAND_MAX) * SIZE;   // x
                bodies[5*i+2] = (rand()/(double)RAND_MAX) * SIZE;   // y
//                bodies[5*i+3] = rand() % 10 - 5;                    // vx
                bodies[5*i+3] = rand() % 10 - 5;
                bodies[5*i+4] = rand() % 10 - 5;                    // vy
            }
        } // end for
        
    } // end if (taskid == 0)
    
    int iter = 0;
    while (iter < ITERATIONS){
        
        // Broadcast the updated info of bodies to every node
        MPI_Bcast(bodies, 5*NUM_BODIES, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        
        // Compute acceleration and change the velocity for target bodies
#pragma omp parallel for private(dx, dy, r, a, ax, ay, j) shared(local_data)
        for(i=start_body; i < end_body; i++){
            
            // copy the updated data to local data
            for(j=0; j < 5; ++j){
                local_data[5*(i-start_body)] = bodies[5*i];
                local_data[5*(i-start_body)+1] = bodies[5*i+1];
                local_data[5*(i-start_body)+2] = bodies[5*i+2];
                local_data[5*(i-start_body)+3] = bodies[5*i+3];
                local_data[5*(i-start_body)+4] = bodies[5*i+4];
            }
            
            // start computing
            for(j=0; j < NUM_BODIES; j++) {
                if (i == j) continue;
                dx = bodies[5*j+1] - bodies[5*i+1];
                dy = bodies[5*j+2] - bodies[5*i+2];
                r = sqrt(dx * dx + dy * dy);    // distance
                
                // determine whether collision happens
                if (r < 2 * BODY_RADIUS){
                    // elastic collision
                    // horisontal
                    local_data[5*(i-start_body)+3] = ((bodies[5*i]-bodies[5*j])*bodies[5*i+3] + 2*bodies[5*j]*bodies[5*j+3])/(bodies[5*i]+bodies[5*j]);
                    // vertical
                    local_data[5*(i-start_body)+4] = ((bodies[5*i]-bodies[5*j])*bodies[5*i+4] + 2*bodies[5*j]*bodies[5*j+4])/(bodies[5*i]+bodies[5*j]);
                    
                    // compute accerlaration between two bodies
                    a = G * bodies[5*j] / (4 * BODY_RADIUS * BODY_RADIUS);
                    ax = a * dx / (2 * BODY_RADIUS);
                    ay = a * dy / (2 * BODY_RADIUS);
                }else {
                    // compute accerlaration between two bodies
                    a = G * bodies[5*j] / (r * r);  // universal gravitation
                    ax = a * dx / r;
                    ay = a * dy / r;
                }
                // acceleration changes velocity
                local_data[5*(i-start_body)+3] += ax;   // vx
                local_data[5*(i-start_body)+4] += ay;   // vy
                
            } // end j
        } // end i ( end of computation )
        
        // Gather the results
        MPI_Gatherv(local_data, count[taskid], MPI_DOUBLE, bodies, count, disp, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        
        // the root process draw the updated results
        if (taskid == 0){
            
            // refresh every 10 iterations
            if (iter % 10 == 0)
                XClearWindow(display, win);
            
            
            // bouncing at boundary and draw
            for (i = 0; i < NUM_BODIES; ++i){
                // displacement made by velocity
                bodies[5*i+1] += bodies[5*i+3];
                bodies[5*i+2] += bodies[5*i+4];
                
                // left boundary
                if (bodies[5*i+1] < 0){
                    bodies[5*i+1] = -bodies[5*i+1];
                    bodies[5*i+3] = -bodies[5*i+3]/999;   // 99.9% energy loss
                }
                // right boundary
                if (bodies[5*i+1] > SIZE){
                    bodies[5*i+1] = 2 * SIZE - bodies[5*i+1];
                    bodies[5*i+3] = -bodies[5*i+3]/999;   // 99.9% energy loss
                }
                // down boundary
                if (bodies[5*i+2] < 0){
                    bodies[5*i+2] = -bodies[5*i+2];
                    bodies[5*i+4] = -bodies[5*i+4]/999;   // 99.9% energy loss
                }
                // up boundary
                if (bodies[5*i+2] > SIZE){
                    bodies[5*i+2] = 2 * SIZE - bodies[5*i+2];
                    bodies[5*i+4] = -bodies[5*i+4]/999;   // 99.9% energy loss
                }
                // refresh every 10 iterations
                if (iter % 10 == 0) {
                    
                    XDrawPoint (display, win, gc, bodies[5*i+1], bodies[5*i+2]);
                    usleep(10);
                    
                }
            } // end for
            
            if (iter % 10 == 0) {
                XFlush(display);
                usleep(100);
            }
        }
        iter ++;
    } // end iteration
    
    free(bodies);
    free(local_data);
    
    if (taskid == 0) {
        gettimeofday( &timeEnd, NULL );
        runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;
        // display information
        printf("Name: Hongpeng Yi\nStudent ID: 117020343\nAssignment 3, N-body Simulation, MPI + OpenMP implementation.\nRunTime is %lfs, with %d bodies, %d processes and %d threads.\nWindow size is %d*%d; total %d iterations; refresh every 10 iterations.\n", runTime, NUM_BODIES, numtasks, NUM_THREADS, SIZE, SIZE, ITERATIONS);
        sleep(10);
        return 0;
    }
    
    MPI_Finalize();
}
