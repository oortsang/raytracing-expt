/* Olivia Tsang, 2022 */
/* camera.h: store camera information */

#include "my_vector.h"

#ifndef _CAMERA_H_
#define _CAMERA_H_
/* Camera information */
/* Follows the conventions from Foundations of Scientific Visualization */
/* from Prof. Gordon Kindlmann */
typedef struct {
    VecH fr;      /* from/position vector (homog or non homog?) */
    VecH n, v, u; /* ON basis for camera coords; n is toward the camera, v is up, u is right */
    double d;     /* distance from the viewing plane */
    double nc;    /* Near clipping distance */
    double fc;    /* Far  clipping distance */
    double fov;   /* field of view in the vertical direction, in degrees */

    int px, py;   /* Number of pixels in the x and y directions (camera coords) */
    /* Let aspect ratio be px/py */
    double ar;

    BasisTransform VtoW; /* currently unused */
} Camera;

/* a ray that also knows which pixel it corresponds to */
/* in fancier sampling methods, this could still be used
 * to update neighboring pixel values */
typedef struct {
    int i, j;
    Ray ray;
} PixelRay;


/* Printing */
void printCamera(Camera *c);

/* Generating rays */
PixelRay *getRays(Camera *cam, int rays_per_pixel, int *ray_count_outparam);
#endif
