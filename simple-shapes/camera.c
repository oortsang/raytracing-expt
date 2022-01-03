/* Olivia Tsang, 2022 */
/* camera.c: store camera information */

#include <stdio.h>

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
