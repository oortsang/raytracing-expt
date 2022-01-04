/* Olivia Tsang, 2022 */
/* Render a sphere via ray-tracing with simple Blinn-Phong shading */
/* Note that this does not involve explicitly modeling reflection by more ray tracing */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "png_interface.h"
#include "my_vector.h"
#include "camera.h"
#include "sphere.h"

bitmap_t *sphere_render(Camera *cam, Sphere *sphere, int rpp) {
    /* Render a sphere to a bitmap image
     * rpp: (number of) rays per pixel
     * Note: allocates memory for the image */
    bitmap_t *bm  = malloc(sizeof(bitmap_t));
    bm->width  = cam->px;
    bm->height = cam->py;

    /* Color *pixels = calloc(bm->width*bm->height, sizeof(Color)); */
    Color *pixels = malloc(bm->width*bm->height*sizeof(Color));
    bm->pixels=pixels;

    /* Fill in the bitmap */
    int rc;
    PixelRay *rays = getRays(cam, rpp, &rc);
    /* Iterate through the requested rays */
    for (int i = 0; i < rc; i++) {
        /* printf("Pixel %d %d\n", rays[i].i, rays[i].j); */
        Ray *curr_ray = &(rays[i].ray);
        Color *curr_pix = pixels + rays[i].i*bm->width + rays[i].j;
        printf("Pixel %02d %02d Ray: ", rays[i].i, rays[i].j); printRay(*curr_ray); printf("\n");
        /* printf("Pixel %02d %02d: %p\n", rays[i].i, rays[i].j, curr_pix); */
        Color col_contr = {120, 120, 120}; /* color contribution */
        double dist = ray_sphere_intersection(curr_ray, sphere, &col_contr);

        *curr_pix = col_fma(*curr_pix, (double)1/rpp, col_contr);
        /* if (dist>0) { */
        /*     /\* mix in the new color contribution *\/ */
        /*     *curr_pix = col_fma(*curr_pix, (double)1/rpp, col_contr); */
        /*     /\* *curr_pix = col_contr; *\/ */
        /*     /\* *curr_pix = (Color) {128, 0, 0}; *\/ */
        /* } else { */
        /*     /\* white background *\/ */
        /*     *curr_pix = (Color) {255, 255, 255}; */
        /* } */
    }

    if (rays) free(rays);
    return bm;
}


int main(int argc, char **argv) {
    /* char *filename = "test.png"; */
    /* printf("Preparing a picture (%s)!\n", filename); */

    /* bitmap_t pic; */
    /* pic.width  = 128; */
    /* pic.height = 128; */
    /* pic.pixels = (Color *) malloc(pic.width*pic.height*sizeof(Color)); */

    /* /\* Set as a diagonal gradient *\/ */
    /* for (int i = 0; i < pic.height; i++) { */
    /*     for (int j = 0; j < pic.width; j++) { */
    /*         Color *pixel = pic.pixels + i*pic.height + j; */
    /*         pixel->red   = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width)); */
    /*         pixel->green = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width)); */
    /*         pixel->blue  = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width)); */
    /*     } */
    /* } */
    /* /\* Write to test.png *\/ */
    /* write_to_png(filename, &pic, "Olivia's test png :P"); */

    /* /\* Clean up *\/ */
    /* if (pic.pixels) free(pic.pixels); */

    /* /\* Check vector printing functionality *\/ */
    /* VecI u = {.x=1, .y=2, .z=3}; */
    /* printVecI(u); */
    /* printf("\n"); */
    /* printVecH(vecItoH(u, 1)); */
    /* printf("\n"); */
    /* printVecH(vecItoH(u, 0)); */
    /* printf("\n"); */

    /* Check camera info printing functionality */
    /* VecH obj = {0, 0, 0, 1}; */
    Camera cam = {.fr=(VecH){0,0,-1,1}, .n=(VecH){0,0,-1,0}, .v=(VecH){0,1,0,0}, .u=(VecH){1,0,0,0},
                  .d=1., .nc=0.5, .fc=1.5, .fov=90, .px=40, .py=30, .ar=4./3};
    printCamera(&cam);

    /* /\* Check ray printing functionality *\/ */
    /* Ray r = ray_fr_at(cam.fr, obj); */
    /* printRay(r); */
    /* printf("\n"); */

    /* /\* Check camera ray output *\/ */
    /* srand(0); */
    /* int rc; */
    /* PixelRay *rays = getRays(&cam, 1, &rc); */
    /* printf("rc=%d\n", rc); */
    /* for (int i = 0; i < 10; i++) { */
    /*     printf("Pixel (%d, %d) Ray %d: ", rays[i].i, rays[i].j, i+1); */
    /*     printRay(rays[i].ray); */
    /*     printf("\n"); */
    /* } */

    /* Check ray-sphere intersection */
    Sphere sphere = {.center={0,0,0,1}, .col=(Color){128,0,0}, .r=0.5};
    /* Color col; */
    /* double dist = ray_sphere_intersection(&r, &sphere, &col); */
    /* printf("Ray-sphere intersection?\n"); */
    /* printf("dist = %f\n", dist); */

    /* Draw sphere */
    char *sphere_filename = "simple_sphere.png";
    bitmap_t *bm = sphere_render(&cam, &sphere, 5);
    printf("bm->pixels=%p\n", bm->pixels);
    for (int pi = 600; pi < 640; pi++) {
        printf("bm->pixels[%d]=%u %u %u\n", pi, bm->pixels[pi].red, bm->pixels[pi].green, bm->pixels[pi].blue);
    }

    printf("Writing a picture (%s)!\n", sphere_filename);
    write_to_png(sphere_filename, bm, "Simple sphere :P");
    if (bm->pixels) free(bm->pixels);
    if (bm) free(bm);

    return 0;
}
