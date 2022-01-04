/* Olivia Tsang, 2022 */
/* camera.c: store camera information */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "my_vector.h"
#include "camera.h"

void printCamera(Camera *cam) {
    printf("Camera:\n");
    printf("Position: ");
    printVecH(cam->fr);
    printf("\nd=%f (nc=%f, fc=%f)\nfov=%f\nResolution: %d x %d\n",
           cam->d, cam->nc, cam->fc,
           cam->fov, cam->px, cam->py);
}

PixelRay *getRays(Camera *cam, int rays_per_pixel, int *ray_count_outparam) {
    /* Returns an array of rays for the given camera that need to be processed
       ray_count_outparam is an outparameter for the length of the ray array
     */
    int raycount = cam->px * cam->py * rays_per_pixel;
    PixelRay *rays = malloc(raycount*sizeof(PixelRay));
    assert (rays);

    /* For safety, re-normalize */
    VecH n = vech_unit(cam->n);
    VecH v = vech_unit(cam->v);
    VecH u = vech_unit(cam->u);

    /* Calculate the view boundaries at the  */
    double half_hght = cam->d * tan(cam->fov/2 * M_PI/180);
    double half_wdth = cam->d * tan(cam->ar*cam->fov/2 * M_PI/180);
    VecH cam_dir = vech_flip(n);

    /* Center and upper-left-hand corner of the view rectangle on the image plane */
    /* fr - d*n */
    VecH view_center = vech_add(cam->fr, vech_smul(cam->d, cam_dir));
    /* ul = vc + hh*v - hw*u */
    VecH view_ul = vech_add(vech_add(view_center, vech_smul(half_hght, cam->v)),
                            vech_smul(-half_wdth, cam->u));
    /* Pixel width/height in world space */
    double pix_wdth = (2*half_wdth) / cam->px;
    double pix_hght = (2*half_hght) / cam->py;

    /* Calculate the rays.. */
    for (int xi = 0; xi < cam->px; xi++) {
        for (int yi = 0; yi < cam->py; yi++) {
            /* upper-left-hand corner of the pixel */
            /* Get the rest using pix_hght and pix_width and -v, u unit vectors */
            VecH pix_ul = vech_add(vech_add(view_ul, vech_smul(xi*pix_wdth, u)),
                                   vech_smul(-yi*pix_hght, v));
            for (int ri = 0; ri < rays_per_pixel; ri++) {
                PixelRay *curr = rays + rays_per_pixel*(cam->py*xi+yi) + ri;
                curr->ray.start = cam->fr;
                /* Random position within the pixel to try to avoid aliasing */
                double xpp = pix_wdth*rand(); /* x position in the pixel */
                double ypp = pix_hght*rand(); /* y position in the pixel */
                /* dst = pix_ul + xpp*u - ypp*v */
                VecH dst = vech_add(pix_ul, vech_add(vech_smul(xpp, u), vech_smul(-ypp, v)));

                /* Image coordinates are typically row then column */
                curr->i = yi;
                curr->j = xi;
                curr->ray.dir = vech_unit(vech_sub(dst, cam->fr));
                /* printVecH(dst); printf("\n"); */
            }
        }
    }

    /* Set the outparameter */
    if (ray_count_outparam)
        *ray_count_outparam = raycount;
    return rays;
}
