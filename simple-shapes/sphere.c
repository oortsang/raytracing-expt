/* Olivia Tsang, 2022 */
/* Render a sphere via ray-tracing with simple Blinn-Phong shading */
/* Note that this does not involve explicitly modeling reflection by more ray tracing */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "my_vector.h"
/* #include "png_interface.h" */

typedef struct Sphere {
    VecI center;
    double r;
} Sphere;
