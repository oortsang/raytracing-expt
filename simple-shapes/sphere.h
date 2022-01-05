/* Olivia Tsang, 2022 */
/* Render a sphere via ray-tracing with simple Blinn-Phong shading */
/* Note that this does not involve explicitly modeling reflection by more ray tracing */

/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <stdint.h> */

#include "my_vector.h"
#include "png_interface.h"

#ifndef _SPHERE_H_
#define _SPHERE_H_
typedef struct Sphere {
    VecH   center;
    DoubleColor  col;
    double r;
} Sphere;


/* Returns the (positive) distance from the ray to the intersection with the sphere
 * or 0 if there is no such intersection
 * and as an outparameter the color
 */
double ray_sphere_intersection(Ray *ray, Sphere *sphere, DoubleColor *color);

#endif
