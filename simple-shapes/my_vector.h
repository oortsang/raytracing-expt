/* Olivia Tsang, 2022 */
/* my_vector.h: header file for custom vector types */
/* Includes Homogeneous and Inhomogeneous representations and helper functions  */

#ifndef _MY_VECTOR_H_
#define _MY_VECTOR_H_
/* Inhomogeneous 3D vector */
typedef struct {
    double x, y, z;
} VecI;

/* Homogeneous 3D vector */
typedef struct {
    /* w should be normalized to 1 */
    double x, y, z, w;
} VecH;

/* Holds the the 4x4 block matrix */
/* [ mat shift] */
/* [   0     1] */
/* For basis transforms with shifts */
typedef struct {
    double mat[9];
    double shift[3];
} BasisTransform;

/* Printing */
void printVecH(VecH v);
void printVecI(VecI v);

/* Conversion functions */
VecI vecHtoI(VecH v);
VecH vecItoH(VecI v, int is_point);

/* Addition and multiplication */
VecH vecH_normalize(VecH v);
/* VecI vecI_add(VecI u, VecI v); */
/* VecI vecI_smul(double a, VecI v); */

VecH vecH_add(VecH u, VecH v);
VecH vecH_smul(double a, VecH v);

/* VecI vec_mul_add(VecI u, double a, VecH v); /\* To help compute points on a ray *\/ */

#endif
