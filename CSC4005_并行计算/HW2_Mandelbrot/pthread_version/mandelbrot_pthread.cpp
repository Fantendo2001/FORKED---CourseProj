#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <time.h>
using namespace std;

int NUM_THREADS = 1;
int SIZE = 200;

typedef struct _thread_data{
    int thread_id;
    int *data;
}thread_data;

typedef struct complextype
{
    float real, imag;
} Compl;

void *cal_func(void *arg) {
    int start_row, end_row, num_rows, remain;
    thread_data *input_data = (thread_data *) arg;
    
    num_rows = SIZE / NUM_THREADS;
    remain = SIZE % NUM_THREADS;
    if (input_data->thread_id < remain) {
        num_rows ++;
        start_row = num_rows * input_data->thread_id;
    }else {
        start_row = num_rows * input_data->thread_id + remain;
    }
    end_row = start_row + num_rows;
    
    Compl   z, c;
    int i, j, k;
    double  lengthsq, temp;
    
    for (i = start_row; i < end_row; ++i){
        for (j = 0; j < SIZE; ++j){
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
                input_data->data[i*SIZE+j]=1;
            }
        }
    }
    pthread_exit(NULL);
}

int main (int argc, char* argv[]){
    
    if (argc > 1) SIZE = atoi(argv[1]);
    if (argc > 2) NUM_THREADS = atoi(argv[2]);
    
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
    
    struct timeval timeStart, timeEnd, timeSystemStart;
    double runTime=0, systemRunTime;
    gettimeofday(&timeStart, NULL );
    
    // start pthread
    int i, rc;
    pthread_t thread[NUM_THREADS];
    thread_data input_data[NUM_THREADS];
    int *output=(int *)malloc(sizeof(int) * (X_RESN * Y_RESN));
    
    for (i = 0; i < NUM_THREADS; ++ i) {
        input_data[i].thread_id = i;
        input_data[i].data = output;
        rc = pthread_create(&thread[i], NULL, cal_func, &input_data[i]);
        if (rc) {
            fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            return EXIT_FAILURE;
        }
    }
    
    for (i = 0; i < NUM_THREADS; ++i) {
        void *return_data;
        pthread_join(thread[i], &return_data);
//        printf("the return data is %d\n", return_data);
    }
    
    // end pthread
    
    gettimeofday( &timeEnd, NULL );
    runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;
    printf("Name: Hongpeng Yi\nStudent ID: 117020343\nAssignment 2, Mandelbrot Set, Pthread implementation.\nRunTime is %lfs, with %d threads and size of %d*%d.\n", runTime, NUM_THREADS, SIZE, SIZE);
    
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
