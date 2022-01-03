/* Olivia Tsang, 2022 */
/* Getting situated by writing a simple array to a png */
/* structs based on https://www.lemoda.net/c/write-png/ */
/* also the main documentation: http://www.libpng.org/pub/png/libpng-1.4.0-manual.pdf */
/* helpful page: http://www.labbookpages.co.uk/software/imgProc/libPNG.html */


#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "png_interface.h"

/* Returns -1 if there was an error, otherwise returns 0 */
int write_to_png(char *filename, bitmap_t *bm, char *title) {
    /* Grab the file to write to */
    FILE *fp = fopen(filename, "wb");
    if (!fp) return -1;

    /* Make png_struct and png_info */
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) return -1;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, NULL);
    }

    /* Set up error-handling */
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return -1;
    }

    /* Set info struct */
    png_set_IHDR(png_ptr, info_ptr, bm->width, bm->height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    /* Copy the data to the struct */
    png_byte **row_pointers = png_malloc(png_ptr, bm->height*sizeof(png_byte *));
    /* i for row number, j for column number */
    for (int i = 0; i < bm->height; i++) {
        row_pointers[i] = png_malloc(png_ptr, bm->width*sizeof(pixel_t));
        for (int j = 0; j < bm->width; j++) {
            pixel_t *pixel = bm->pixels+i*bm->width+j;
            row_pointers[i][3*j+0] = pixel->red;
            row_pointers[i][3*j+1] = pixel->green;
            row_pointers[i][3*j+2] = pixel->blue;
        }
    }

    /* Set title */
    png_text title_text;
    title_text.compression = PNG_TEXT_COMPRESSION_NONE;
    title_text.key = "Title";
    if (title)
        title_text.text = title;
    else
        title_text.text = "Pic by Olivia :)";
    png_set_text(png_ptr, info_ptr, &title_text, 1);


    /* Perform the write */
    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);


    png_write_end(png_ptr, info_ptr);

    /* Clean up */
    if (fp) fclose(fp);
    for (int i = 0; i < bm->height; i++) {
        png_free(png_ptr, row_pointers[i]);
    }
    png_free(png_ptr, row_pointers);
    if (info_ptr) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr) png_destroy_write_struct(&png_ptr, &info_ptr);
    return 0;
}


/* int main(int argc, char **argv) { */
/*     char *filename = "test.png"; */
/*     printf("Preparing a picture (%s)!\n", filename); */

/*     bitmap_t pic; */
/*     pic.width  = 128; */
/*     pic.height = 128; */
/*     pic.pixels = (pixel_t *) malloc(pic.width*pic.height*sizeof(pixel_t)); */

/*     /\* Set as a diagonal gradient *\/ */
/*     for (int i = 0; i < pic.height; i++) { */
/*         for (int j = 0; j < pic.width; j++) { */
/*             pixel_t *pixel = pic.pixels + i*pic.height + j; */
/*             pixel->red   = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width)); */
/*             pixel->green = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width)); */
/*             pixel->blue  = (uint8_t) ((double)(i+j)*256/(pic.height+pic.width)); */
/*         } */
/*     } */
/*     /\* Write to test.png *\/ */
/*     write_to_png(filename, &pic, "Olivia's test png :P"); */

/*     /\* Clean up *\/ */
/*     if (pic.pixels) free(pic.pixels); */
/*     return 0; */
/* } */
