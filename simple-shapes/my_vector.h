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

typedef struct {
    VecH start, dir;
} Ray;

/* Printing */
void printVecH(VecH v);
void printVecI(VecI v);

/* Conversion functions */
VecI vecHtoI(VecH v);
VecH vecItoH(VecI v, int is_point);

/* Addition and multiplication */
VecH vech_divbyw(VecH v);
/* VecI vecI_add(VecI u, VecI v); */
/* VecI vecI_smul(double a, VecI v); */
VecH vech_unit(VecH v);

VecH vech_add(VecH u, VecH v);    /* u+v */
VecH vech_sub(VecH u, VecH v);    /* u-v */
VecH vech_smul(double a, VecH v); /* scalar multiplication */
VecH vech_flip(VecH v); /* multiply by x/y/z -1 but leave the trailing 1 intact */
double vech_dot(VecH u, VecH v);  /* dot product of the 3d representations of the vectors */
double vech_norm_squared(VecH v); /* square of l2 norm of the 3d-representation of the vector */
double vech_norm(VecH v); /* l2 norm of the 3d-representation of the vector */

/* VecI vec_mul_add(VecI u, double a, VecH v); /\* To help compute points on a ray *\/ */
void printRay(Ray r);
Ray ray_fr_at(VecH fr, VecH at);

#endif
