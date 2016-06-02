#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "includes.h"

// 'global' variables to store screen info
char *fbp = NULL;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
int screenwidth;
int screenheight;
int gamewidth;
int gameheight;

/*
 * Initialise screenwidth, height and open frame buffer device
 */ 
void initialise_graphics() {
    int fd = open("/dev/fb0", O_RDWR);
    if(!fd) {
        fprintf(stderr, "Error cannot open framebuffer");
        exit(EXIT_FAILURE);
    }
    if(ioctl(fd, FBIOGET_FSCREENINFO, &finfo)) {       
        printf("Error reading screen information");
        exit(EXIT_FAILURE);
    }
    long int screensize = finfo.smem_len; //vinfo.xres * vinfo.yres;
    fbp = (char*)mmap(0,
              screensize,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              fd,
              0);
    if ((int) *fbp == -1) {
        fprintf(stderr, "Failed to mmap.\n");
        exit(EXIT_FAILURE);
    }
    screenwidth = vinfo.xres;  
    screenheight = vinfo.yres;     
    gamewidth = screenwidth / 2;
    gameheight = screenheight;
}

/*
 * Draw screen when winning the game
 */ 
void draw_win_screen() {

}

/*
 * Draw the game over screen
 */ 
void draw_gameover_screen() {

}


/*
 * Color pixel (x, y) with color c 
 */ 
void put_pixel(int x, int y, int c)
{
    unsigned int pixel_offset = x + y * finfo.line_length;
    // fbp[pix_offset] = value
    *(fbp + pixel_offset) = c;
}

/*
 * x and y are the center coordinates of the rectangle
 */ 
void draw_rect(int center_x, int center_y, int width, int height, int32_t colour) {
    int x = center_x - width / 2; 
    int y = center_y - height / 2;
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            put_pixel(i + x, y + j, colour);
        }
    }
}

/*
 * Draw a filled circle using the 
 * Midpoint circle algorithm
 */ 
void draw_cirle(int x0, int y0, int radius) {
    int32_t colour = BALL_COLOUR;
    int x = 0, y = radius;
    int error = 1 - radius;
    while(x < y) {
        if(error < 0) {
            x++;
            error += 2 * x + 3;
        } else {
            x++;
            y--;
            error += 2 * x - 2 * y + 5;
        }
        //45 degree quadrants
        put_pixel(x0 + x, y0 + y, colour);
        put_pixel(x0 - x, y0 + y, colour);
        put_pixel(x0 + x, y0 - y, colour);
        put_pixel(x0 - x, y0 - y, colour);
        put_pixel(x0 + y, y0 + x, colour);
        put_pixel(x0 - y, y0 + x, colour);
        put_pixel(x0 + y, y0 - x, colour);
        put_pixel(x0 - y, y0 - x, colour);
    }
}

void draw_background(int32_t colour) {
    draw_rect(screenwidth / 2, screenheight / 2, screenwidth, screenheight, colour);
}

void draw_game(bar_t *bar, ball_t *ball, int32_t *bricks) {
    draw_rect(bar->position.x, bar->position.y, bar->width, bar->height, BAR_COLOUR); //bar
    for(int i = 0; i < MAX_BRICKS_PER_LEVEL; i++) {
        vector2D_t center = center_of_brick(i);
        draw_rect(center.x, center.y, BRICK_WIDTH, BRICK_HEIGHT, bricks_level[bar->level][i]);
    }
    draw_cirle(ball->position.x, ball->position.y, ball->radius); // ball
}


/*******************************/

// default framebuffer palette
typedef enum {
    BLACK        =  0, /*   0,   0,   0 */
    BLUE         =  1, /*   0,   0, 172 */
    GREEN        =  2, /*   0, 172,   0 */
    CYAN         =  3, /*   0, 172, 172 */
    RED          =  4, /* 172,   0,   0 */
    PURPLE       =  5, /* 172,   0, 172 */
    ORANGE       =  6, /* 172,  84,   0 */
    LTGREY       =  7, /* 172, 172, 172 */
    GREY         =  8, /*  84,  84,  84 */
    LIGHT_BLUE   =  9, /*  84,  84, 255 */
    LIGHT_GREEN  = 10, /*  84, 255,  84 */
    LIGHT_CYAN   = 11, /*  84, 255, 255 */
    LIGHT_RED    = 12, /* 255,  84,  84 */
    LIGHT_PURPLE = 13, /* 255,  84, 255 */
    YELLOW       = 14, /* 255, 255,  84 */
    WHITE        = 15  /* 255, 255, 255 */
} COLOR_INDEX_T;

/*
static unsigned short def_r[] =
    { 0,   0,   0,   0, 172, 172, 172, 168,
     84,  84,  84,  84, 255, 255, 255, 255};
static unsigned short def_g[] =
    { 0,   0, 168, 168,   0,   0,  84, 168,
     84,  84, 255, 255,  84,  84, 255, 255};
static unsigned short def_b[] =
    { 0, 172,   0, 168,   0, 172,   0, 168,
     84, 255,  84, 255,  84, 255,  84, 255};
*/


void draw_line(int x0, int y0, int x1, int y1, int colour) {
    int dx = x1 - x0;
    if (dx < 0) {
        dx = -dx;
    }
    int dy = y1 - y0;
    if (dy < 0) {
        dy = -dy;
    }
    int sx = 0;
    int sy = 0;
    if(x0 < x1) {
        sx = 1;
    } else {
        sx = -1;
    }
    int err = dx - dy;
    int e2;
    int done = 0;
    while (!done) {
        put_pixel(x0, y0, colour);
        if ((x0 == x1) && (y0 == y1)) {
            done = 1;
        } else {
            e2 = 2 * err;
            if (e2 > -dy) {
                err = err - dy;
                x0 = x0 + sx;
            }
            if (e2 < dx) {
                err = err + dx;
                y0 = sy;
            }
        }
    }
}
   

// helper function for drawing
void draw() {

    int x, y;
    int t = 20;

    // t x t pix black and blue checkerboard
    for (y = 0; y < vinfo.yres; y++) {
        int xoffset = y / t % 2;
        for (x = 0; x < vinfo.xres; x++) {

            // color based on the tile
            int c = (x / t + xoffset) % 2;

            // draw pixel
            put_pixel(x, y, c);

        }
    }
    // colored blocks
    for (y = 0; y < vinfo.yres; y += t) {
        int xoffset = y / t % 2;
        for (x = t * xoffset; x < vinfo.xres; x += t * 2) {
            int x2, y2;
            for (y2 = 0; y2 < t; y2++) {
                for (x2 = 0; x2 < t; x2++) {

                    // color based on y2 value
                    // using the custom colors (16+)
                    int c = 0xAA;

                    // draw pixel
                    put_pixel(x + x2, y + y2, c);

                }
            }
        }
    }
}

/*
// application entry point
int main(int argc, char* argv[])
{

    int fbfd = 0;
    struct fb_var_screeninfo orig_vinfo;
    long int screensize = 0;


    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
      printf("Error: cannot open framebuffer device.\n");
      return(1);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) != 0) {
      printf("Error reading variable information.\n");
    }

    // Store for reset (copy vinfo to vinfo_orig)
    memcpy(&orig_vinfo, &vinfo, sizeof(struct fb_var_screeninfo));

    // Change variable info
    vinfo.bits_per_pixel = 8; // 8-bit mode
    // drop resolution
    while (vinfo.xres > 800) {
        vinfo.xres /= 2;
        vinfo.yres /= 2;
    }
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo) != 0) {
      printf("Error setting variable information.\n");
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) != 0) {
      printf("Error reading fixed information.\n");
    }

    // Set palette
    unsigned short r[256];
    unsigned short g[256];
    unsigned short b[256];
    memset(r, 0, 256); // initialise with zeros
    memset(g, 0, 256);
    memset(b, 0, 256);
    int i;
    for(i = 0; i < 16; i++) {
        // red-yellow gradient
        // note that Linux provides more precision (0-65535),
        // so we multiply ours (0-255) by 256
        r[i] = 255 << 8;
        g[i] = ((15 - i) * 16) << 8;
        b[i] = 0;
    }
    struct fb_cmap pal;
    pal.start = 16; // start our colors after the default 16
    pal.len = 256; // kludge to force bcm fb drv to commit palette...
    pal.red = r;
    pal.green = g;
    pal.blue = b;
    pal.transp = 0; // we want all colors non-transparent == null
    if (ioctl(fbfd, FBIOPUTCMAP, &pal)) {
        printf("Error setting palette.\n");
    }

    // map fb to user mem
    screensize = finfo.smem_len; //vinfo.xres * vinfo.yres;
    fbp = (char*)mmap(0,
              screensize,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              fbfd,
              0);

    if ((int)*fbp == -1) {
        printf("Failed to mmap.\n");
    }
    else {
        // DRAW HERE
        //put_pixel(vinfo.xres/2, vinfo.yres/2, 0xAA);
        draw_line(vinfo.xres/2, vinfo.yres/2, 
            vinfo.xres/4, vinfo.yres/4, 0xAA);
        sleep(1);

        // rotate palette to create visual effect
        int j;
        int fps = 30; // frames per second
        int d = 5; // duration in seconds
        // repeat for given time
        for(j = 0; j < fps * d; j++) {
            // store color 0 in temp variables
            int rt = r[0];
            int gt = g[0];
            int bt = b[0];
            // replace colors by copying the next
            for(i = 0; i < 15; i++) {
                r[i] = r[i+1];
                g[i] = g[i+1];
                b[i] = b[i+1];
            }
            // restore last one from temp
            r[15] = rt;
            g[15] = gt;
            b[15] = bt;
            // Note that we set up the 'pal' structure earlier
            // and it still points to the r, g, b arrays,
            // so we can just reuse 'pal' here
            if (ioctl(fbfd, FBIOPUTCMAP, &pal) != 0) {
                printf("Error setting palette.\n");
            }
            usleep(1000000 / fps);
        }

    }

    // cleanup
    // NOTE: should probably reset the palette too...
    // unmap fb file from memory
    munmap(fbp, screensize);
    // reset the display mode
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo) != 0) {
        printf("Error re-setting variable information.\n");
    }
    // close fb file
    close(fbfd);

    return 0;

}*/
