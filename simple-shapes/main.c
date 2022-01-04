/* Olivia Tsang, 2022 */
/* Render a sphere via ray-tracing with simple Blinn-Phong shading */
/* Note that this does not involve explicitly modeling reflection by more ray tracing */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "png_interface.h"
#include "my_vector.h"
#include "camera.h"

int main(int argc, char **argv) {
    char *filename = "test.png";
    printf("Preparing a picture (%s)!\n", filename);

    bitmap_t pic;
    pic.width  = 128;
    pic.height = 128;
    pic.pixels = (pixel_t *) malloc(pic.width*pic.height*sizeof(pixel_t));

    /* Set as a diagonal gradient */
    for (int i = 0; i < pic.height; i++) {
        for (int j = 0; j < pic.width; j++) {
            pixel_t *pixel = pic.pixels + i*pic.height + j;
            pixel->red   = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width));
            pixel->green = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width));
            pixel->blue  = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width));
        }
    }
    /* Write to test.png */
    write_to_png(filename, &pic, "Olivia's test png :P");

    /* Clean up */
    if (pic.pixels) free(pic.pixels);

    /* Check vector printing functionality */
    VecI u = {.x=1, .y=2, .z=3};
    printVecI(u);
    printf("\n");
    printVecH(vecItoH(u, 1));
    printf("\n");
    printVecH(vecItoH(u, 0));
    printf("\n");

    /* Check camera info printing functionality */
    VecH obj = {0, 0, 0, 1};
    Camera cam = {.fr=(VecH){0,0,-1,1}, .n=(VecH){0,0,-1,0}, .v=(VecH){0,1,0,0}, .u=(VecH){1,0,0,0},
                  .d=1., .nc=0.5, .fc=1.5, .fov=90, .px=40, .py=30, .ar=4./3};
    printCamera(&cam);

    /* Check ray printing functionality */
    Ray r = ray_fr_at(cam.fr, obj);
    printRay(r);
    printf("\n");

    /* Check camera ray output */
    srand(0);
    int rc;
    PixelRay *rays = getRays(&cam, 1, &rc);
    for (int i = 0; i < 10; i++) {
        printf("Pixel (%d, %d) Ray %d: ", rays[i].i, rays[i].j, i+1);
        printRay(rays[i].ray);
        printf("\n");
    }

    return 0;
}
