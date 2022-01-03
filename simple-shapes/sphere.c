/* Olivia Tsang, 2022 */
/* Render a sphere via ray-tracing with simple Blinn-Phong shading */
/* Note that this does not involve explicitly modeling reflection by more ray tracing */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "my_vector.h"
/* #include "png_interface.h" */


/* Camera information */
/* Follows the conventions from Foundations of Scientific Visualization */
/* from Prof. Gordon Kindlmann */
typedef struct {
    VecI fr;      /* from/position vector */
    VecH n, v, u; /* ON basis for camera coords; n is toward the camera, v is up, u is right */
    double d;     /* distance from the viewing plane */
    double nc;    /* Near clipping distance */
    double fc;    /* Far  clipping distance */
    double fov;   /* field of view, in degrees */
} Camera;
