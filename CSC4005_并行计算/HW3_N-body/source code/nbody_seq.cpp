#include <iostream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <time.h>
#include <math.h>
using namespace std;


int SIZE = 200;             // the size of the window
int NUM_BODIES = 200;       // number of bodies simulated
double BODY_RADIUS = 0.001;     // Assume all the bodies have the same radius
int ITERATIONS = 5000;       // number of iterations to simulate
double G = 0.0000001;        // not real G, it is adjusted by testing to show something appropriate


typedef struct _body
{
    double mass;
    double x, y;     // coordinate
    double vx, vy;   // velocity
}body;


int main (int argc, char* argv[]){
    
    if (argc > 1) NUM_BODIES = atoi(argv[1]);
    
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
    color.red=60000; //range from 0~65535
    color.green=60000;
    color.blue=60000;
    
    Status rc1=XAllocColor(display,DefaultColormap(display, screen),&color);
    //set the color and attribute of the graphics content
    XSetForeground (display, gc, color.pixel);
    XSetBackground (display, gc, BlackPixel (display, screen));
    XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);
    
    struct timeval timeStart, timeEnd, timeSystemStart;
    double runTime=0, systemRunTime;
    gettimeofday(&timeStart, NULL );
    
    
    // ************************* start ***************************
    srand((int)time(NULL));
    body bodies[NUM_BODIES];
    int i, j;
    double dx, dy, r, a, ax, ay, v1, v2;
    
    // initialization
    for (i = 0; i < NUM_BODIES; ++i){
        
        // One body with large mass and 0 initial velocity.
        if (i == 0) {
            bodies[i].mass = 999999999;
            bodies[i].x = SIZE /3 + (rand()/(double)RAND_MAX) * SIZE / 3;
            bodies[i].y = SIZE /3 + (rand()/(double)RAND_MAX) * SIZE / 3;
            bodies[i].vx = 0;
            bodies[i].vy = 0;
        }else{
            // randomize mass
            bodies[i].mass = 1000 + rand() % 10000;
            // randomize position
            bodies[i].x = (rand()/(double)RAND_MAX) * SIZE;
            bodies[i].y = (rand()/(double)RAND_MAX) * SIZE;
            // randomize velocity
            bodies[i].vx = rand() % 10 - 5;
            bodies[i].vy = rand() % 10 - 5;
        }
    }
    
    int count = 0;
    while (count < ITERATIONS){
        count += 1;
        
        // compute total acceleration and change velocity for each body
        for (i = 0; i < NUM_BODIES; ++i){
            for (j = 0; j < NUM_BODIES; ++j){
                if (i == j) continue;
                dx = bodies[j].x - bodies[i].x;
                dy = bodies[j].y - bodies[i].y;
                r = sqrt(dx * dx + dy * dy);    // distance
                
                // determine whether collision happens
                if (r < 2 * BODY_RADIUS){
                    
                    // elastic
                    if (i < j){         // avoid repetitive computation
                        // horizontal
                        v1 = ((bodies[i].mass-bodies[j].mass)*bodies[i].vx + 2*bodies[j].mass*bodies[j].vx)/(bodies[i].mass+bodies[j].mass);
                        v2 = ((bodies[j].mass-bodies[i].mass)*bodies[j].vx + 2*bodies[i].mass*bodies[i].vx)/(bodies[i].mass+bodies[j].mass);
                        bodies[i].vx = v1;
                        bodies[j].vx = v2;
                        // vertical
                        v1 = ((bodies[i].mass-bodies[j].mass)*bodies[i].vy + 2*bodies[j].mass*bodies[j].vy)/(bodies[i].mass+bodies[j].mass);
                        v2 = ((bodies[j].mass-bodies[i].mass)*bodies[j].vy + 2*bodies[i].mass*bodies[i].vy)/(bodies[i].mass+bodies[j].mass);
                        bodies[i].vy = v1;
                        bodies[j].vy = v2;
                    }
                    
                    // inelastic
//                    v1 = (bodies[i].mass*bodies[i].vx + bodies[j].mass*bodies[j].vx)/(bodies[i].mass+bodies[j].mass);
//                    v2 = (bodies[i].mass*bodies[i].vy + bodies[j].mass*bodies[j].vy)/(bodies[i].mass+bodies[j].mass);
//                    bodies[i].vx = v1;
//                    bodies[j].vx = v1;
//                    bodies[i].vy = v2;
//                    bodies[j].vy = v2;
                    
                    // compute accerlaration between two bodies
                    a = G * bodies[j].mass / (4 * BODY_RADIUS * BODY_RADIUS);
                    ax = a * dx / (2 * BODY_RADIUS);
                    ay = a * dy / (2 * BODY_RADIUS);
                }else {
                    // compute accerlaration between two bodies
                    a = G * bodies[j].mass / (r * r);   // universal gravitation
                    ax = a * dx / r;
                    ay = a * dy / r;
                }
                // acceleration changes velocity
                bodies[i].vx += ax;
                bodies[i].vy += ay;
            }
        }
        
        // refresh every 10 iterations
        if (count % 10 == 0)
            XClearWindow(display, win);
        
        // bouncing at boundary and draw
        for (i = 0; i < NUM_BODIES; ++i){
            // displacement made by velocity
            bodies[i].x += bodies[i].vx;
            bodies[i].y += bodies[i].vy;
            
            // left boundary
            if (bodies[i].x < 0){
                bodies[i].x = -bodies[i].x;
                bodies[i].vx = -bodies[i].vx/999;   // 99.9% energy loss
            }
            // right boundary
            if (bodies[i].x > SIZE){
                bodies[i].x = 2 * SIZE - bodies[i].x;
                bodies[i].vx = -bodies[i].vx/999;   // 99.9% energy loss
            }
            // down boundary
            if (bodies[i].y < 0){
                bodies[i].y = -bodies[i].y;
                bodies[i].vy = -bodies[i].vy/999;   // 99.9% energy loss
            }
            // up boundary
            if (bodies[i].y > SIZE){
                bodies[i].y = 2 * SIZE - bodies[i].y;
                bodies[i].vy = -bodies[i].vy/999;   // 99.9% energy loss
            }
            // refresh every 10 iterations
            if (count % 10 == 0) {
                XDrawPoint (display, win, gc, bodies[i].x, bodies[i].y);
                usleep(10);
            }
        }
        XFlush (display);
        usleep(100);
        
    }   // end while
    
    gettimeofday( &timeEnd, NULL );
    runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;
    // display information
    printf("Name: Hongpeng Yi\nStudent ID: 117020343\nAssignment 3, N-body Simulation, Sequential implementation.\nRunTime is %lfs, with %d bodies.\nWindow size is %d*%d; total %d iterations; refresh every 10 iterations.\n", runTime, NUM_BODIES, SIZE, SIZE, ITERATIONS);

    sleep(1);
    return 0;
}
