/* Olivia Tsang, 2022 */
/* my_vector.c: file for custom vector types */
/* Includes Homogeneous and Inhomogeneous representations and helper functions  */

#include <stdio.h>
#include <math.h>

#include <assert.h>
#include "my_vector.h"

/* Printing */
void printVecH(VecH v) {
    printf("VecH(%f %f %f %f)", v.x, v.y, v.z, v.w);
}

void printVecI(VecI v) {
    printf("VecI(%f %f %f)", v.x, v.y, v.z);
}

/* Conversion functions */
VecI vecHtoI(VecH v) {
    double div = v.w ? v.w : 1;
    /* Don't attempt to divide by zero; w=0 means it's a (math) vector rather than point */
    return (VecI) {.x=v.x/div, .y=v.y/div, .z=v.z/div};
}

VecH vecItoH(VecI v, int is_point) {
    return (VecH) {.x = v.x, .y = v.y, .z = v.z, .w = !!is_point};
}

VecH vech_divbyw(VecH v) {
    /* Sets the last entry to 1 and divides by it */
    /* Unless the last entry was 0 in which case do nothing */
    double div = v.w ? v.w : 1;
    return (VecH) {.x=v.x/div, .y=v.y/div, .z=v.z/div, .w=!!v.w};
}

VecH vech_unit(VecH v) {
    /* Sets the length to 1 after dividing by v.w (if it's nonzero) */
    if (v.w)
        v = (VecH) {.x=v.x/v.w, .y=v.y/v.w, .z=v.z/v.w, .w=1};
    double length = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    return (VecH) {.x=v.x/length, .y=v.y/length, .z=v.z/length, .w=v.w};
}

/* Addition and multiplication */
VecH vech_add(VecH u, VecH v) {
    /* Homog. Vector addition; should be between a math vector and a point */
    VecH res = {.x=u.x+v.x, .y=u.y+v.y, .z=u.z+v.z, .w=u.w+v.w};
    assert (res.w == 0 || res.w == 1); /* For safety */
    return res;
}

VecH vech_sub(VecH u, VecH v) {
    /* u-v */
    /* Homog. Vector subtraction; should be between two points or two math vectors */
    VecH res = {.x=u.x-v.x, .y=u.y-v.y, .z=u.z-v.z, .w=u.w-v.w};
    assert (res.w == 0 || res.w == 1); /* For safety */
    return res;
}

VecH vech_smul(double a, VecH v) {
    return (VecH) {.x=a*v.x, .y=a*v.y, .z=a*v.z, .w=v.w};
}

VecH vech_flip(VecH v) {
    return vech_smul(-1., v);
}

/* Ray */
void printRay(Ray r) {
    printf("Ray {start: (%f %f %f), dir: (%f %f %f %f)",
           r.start.x, r.start.y, r.start.z,
           r.dir.x, r.dir.y, r.dir.z, r.dir.w
        );
}

Ray ray_fr_at(VecH fr, VecH at) {
    /* Makes a ray starting at point fr ending at point at */
    assert(fr.w==1 && at.w==1);  /* should both be points */
    VecH dir = vech_sub(at, fr); /* at-fr */
    return (Ray) {.start=fr, .dir=dir};
}
