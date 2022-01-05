/* Olivia Tsang, 2022 */
/* png_interface.h */
/* Header file for my interface with libpng */
/* Getting situated by writing a simple array to a png */
/* structs based on https://www.lemoda.net/c/write-png/ */

#ifndef _PNG_INTERFACE_H_
#define _PNG_INTERFACE_H_
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color;

typedef struct {
    double red;
    double green;
    double blue;
} DoubleColor;

typedef struct {
    size_t   width;
    size_t   height;
    Color *pixels;
} bitmap_t;

DoubleColor col_smul(double a, DoubleColor c);
DoubleColor col_add(DoubleColor b, DoubleColor c);
DoubleColor col_fma(DoubleColor c, double a, DoubleColor b); /* C + a*B */
Color col_from_double(DoubleColor c);


/* Returns -1 if there was an error, otherwise returns 0 */
int write_to_png(char *filename, bitmap_t *bm, char *title);
#endif
