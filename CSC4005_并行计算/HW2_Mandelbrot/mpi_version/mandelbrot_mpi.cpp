#include <iostream>
#include <mpi.h>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <time.h>
using namespace std;

typedef struct complextype
{
    float real, imag;
} Compl;

int main (int argc, char* argv[]){
    
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
    
    int SIZE = 200;
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
                                   WhitePixel (display, screen), WhitePixel (display, screen)); //Change to WhitePixel (display, screen) if you want a white background
        
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
        XSetForeground (display, gc, WhitePixel (display, screen));
        XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);
        
        attr[0].backing_store = Always;
        attr[0].backing_planes = 1;
        attr[0].backing_pixel = BlackPixel (display, screen);
        
        XChangeWindowAttributes(display, win, CWBackingStore | CWBackingPlanes | CWBackingPixel, attr);
        
        XMapWindow (display, win);
        XSync(display, 0);
        
        XFlush (display);
        
        XColor color;
        color.red=10000; //range from 0~65535
        color.green=10000;
        color.blue=10000;
        
        Status rc1=XAllocColor(display,DefaultColormap(display, screen),&color);
        //set the color and attribute of the graphics content
        XSetForeground (display, gc, color.pixel);
        XSetBackground (display, gc, BlackPixel (display, screen));
        XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);
        
        gettimeofday(&timeStart, NULL );

    }
    int *output=(int *)malloc(sizeof(int) * (X_RESN * Y_RESN));
    Compl   z, c;
    int i, j, k, quotient, remainder;
    double  lengthsq, temp;
    
    int count[numtasks], disp[numtasks];
    int * local_data;
    
    disp[0] = 0;
    quotient = SIZE / numtasks;
    remainder = SIZE % numtasks;
    
    for (i = 0; i < numtasks; ++ i) {
        if (i < remainder) {
            count[i] = (quotient + 1) * SIZE;
        }else{
            count[i] = quotient * SIZE;
        }
        if (i > 0) disp[i] = disp[i-1] + count[i-1];
        if (taskid == i) local_data = (int *)malloc(sizeof(int) * count[i]);
    }
    
    int start_row = disp[taskid] / SIZE;
    int end_row = start_row + count[taskid] / SIZE;
    for(i=start_row; i < end_row; i++){
        for(j=0; j < SIZE; j++) {
            z.real = z.imag = 0.0;
            c.real = ((float) j - SIZE/2)/(SIZE/4);                //scale factors for 800 x 800 window
            c.imag = ((float) i - SIZE/2)/(SIZE/4);
            k = 0;
            
            do  {                                             // iterate for pixel color
                
                temp = z.real*z.real - z.imag*z.imag + c.real;
                z.imag = 2.0*z.real*z.imag + c.imag;
                z.real = temp;
                lengthsq = z.real*z.real+z.imag*z.imag;
                k++;
            } while (lengthsq < 12 && k < 100); //lengthsq and k are the threshold
            if (k >= 100) {
                local_data[(i-start_row)*SIZE+j]=1;
            }
        }
    }
    

    MPI_Gatherv(local_data, count[taskid], MPI_INT, output, count, disp, MPI_INT, 0, MPI_COMM_WORLD);
    free(local_data);
    
    if (taskid == 0) {
        gettimeofday( &timeEnd, NULL );
        runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;
//        printf("runTime is %lf\n", runTime);
        printf("Name: Hongpeng Yi\nStudent ID: 117020343\nAssignment 2, Mandelbrot Set, MPI implementation.\nRunTime is %lfs, with %d processes and size of %d*%d.\n", runTime, numtasks, SIZE, SIZE);
    
        for (i=0;i<X_RESN;i++){
            for (int j=0;j<Y_RESN;j++){
                if(output[i*X_RESN+j]==1){
                    XDrawPoint (display, win, gc, j, i);
                    usleep(1);
                    //XDrawPoint cannot draw too fast, otherwise the image cannot be drawn
                    //normally you could try to not use the usleep(1), it only black images are shown, try to use this
                }
            }
        }
        
        //usleep(250000);
        XFlush (display);
        sleep(10);
        return 0;
    }
    free(output);
    MPI_Finalize();
}
