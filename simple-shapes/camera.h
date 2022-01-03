/* Olivia Tsang, 2022 */
/* camera.h: store camera information */

#include "my_vector.h"

#ifndef _CAMERA_H_
#define _CAMERA_H_
/* Camera information */
/* Follows the conventions from Foundations of Scientific Visualization */
/* from Prof. Gordon Kindlmann */
typedef struct Camera {
    VecH fr;      /* from/position vector (homog or non homog?) */
    VecH n, v, u; /* ON basis for camera coords; n is toward the camera, v is up, u is right */
    double d;     /* distance from the viewing plane */
    double nc;    /* Near clipping distance */
    double fc;    /* Far  clipping distance */
    double fov;   /* field of view in the x direction, in degrees */

    int px, py;   /* Number of pixels in the x and y directions (camera coords) */
    /* Let aspect ratio be px/py */
    double ar;
} Camera;

/* Printing */
void printCamera(Camera *c);

/* Generating rays */

#endif
