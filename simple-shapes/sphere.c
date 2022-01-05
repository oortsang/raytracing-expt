/* Olivia Tsang, 2022 */
/* Render a sphere via ray-tracing with simple Blinn-Phong shading */
/* Note that this does not involve explicitly modeling reflection by more ray tracing */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "my_vector.h"
#include "png_interface.h"
#include "sphere.h"

/* Returns the (positive) distance from the ray to the intersection with the sphere
 * or 0 if there is no such intersection
 * Outparameter for the color if there is an intersection
 */
double ray_sphere_intersection(Ray *ray, Sphere *sphere, DoubleColor *color) {
    /* Determine whether the ray intersects with the sphere */

    /* Equations taken from Raytracing in a Weekend */
    /* Intersection between a ray of form A+tb and sphere with radius r and center C */
    /* where A is the start point, t is the distance, and b is the direction of the ray */
    /* Want t such that ||P-C||^2=r^2, where P=A+tb */
    /* (P-C) . (P-C) = (A-C+tb) . (A-C+tb) */
    /* = (A-C) . (A-C) + 2*b . (A-C) t + (b . b) t^2 = r^2 */
    /* a0 + a1 * t^1 + a2 * t^2 = 0 */
    /* A ~= ray->start */
    /* b ~= ray->dir */
    /* C ~= sphere->center */
    VecH AtoC = vech_sub(ray->start, sphere->center);
    double a0 = vech_norm_squared(AtoC) - sphere->r*sphere->r;
    double a1 = 2 * vech_dot(ray->dir, AtoC);
    double a2 = vech_norm_squared(ray->dir);

    /* Look for roots using the quadratic formula */
    /* But we only care about the lower */
    double disc = a1*a1 - 4*a0*a2;
    double dist = 0;
    if (disc >= 0) {
        double r1 = (-a1-sqrt(disc))/2/a2;
        double r2 = (-a1+sqrt(disc))/2/a2;
        if (r1 > 0)
            dist = r1;
        else if (r2 > 0)
            dist = r2;

        /* No real shading so far */
        *color = col_smul(1.5-dist, sphere->col);
        /* *color = sphere->col; /\* no shading at all *\/  */
    }
    
    return dist;
}
