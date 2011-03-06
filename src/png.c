
#include <stdlib.h>
#include <png.h>
#include "layer.h"
#include "png.h"

int read_png_data(char *file_name,
                  png_uint_32 *p_width,
                  png_uint_32 *p_height,
                  png_byte **p_image);

int write_png_data(char *file_name,
                   png_uint_32 width,
                   png_uint_32 height,
                   png_byte *image);

int png_load(char *inFile, tLayerF *image)
{
  int err, x, y;
  png_byte *pngimage;
  png_uint_32 width, height;

  err = read_png_data(inFile, &width, &height, &pngimage);
  if (err != 0)
  {
    free(pngimage);
    return(err);
  }

  *image = layerF(height, width);

  for (y = 0; y < height; y++)
  {
    for (x = 0; x < width; x++)
    {
      ((*image).ch[0][y])[x]  = pngimage[y*width*4 + x*4 + 0];
      ((*image).ch[1][y])[x] = pngimage[y*width*4 + x*4 + 1];
      ((*image).ch[2][y])[x]   = pngimage[y*width*4 + x*4 + 2];
      ((*image).ch[3][y])[x] = pngimage[y*width*4 + x*4 + 3];
    }
  }

  free(pngimage);

  return(0);
}

int png_save(char *outFile, tLayerF *image)
{
  int err, x, y;
  png_byte *pngimage;
  png_uint_32 width, height;

  width  = (*image).w;
  height = (*image).h;
  pngimage = malloc( (height) * (width) * 4 );

  if (NULL == pngimage) return(1);

  for (y = 0; y < height; y++)
  {
    for (x = 0; x < width; x++)
    {
      pngimage[y*width*4 + x*4+0] = ((*image).ch[0][y])[x];
      pngimage[y*width*4 + x*4+1] = ((*image).ch[1][y])[x];
      pngimage[y*width*4 + x*4+2] = ((*image).ch[2][y])[x];
      pngimage[y*width*4 + x*4+3] = ((*image).ch[3][y])[x];
    }
  }

  err = write_png_data(outFile, width, height, pngimage);
  free(pngimage);
  if (err != 0) return(err);

  return(0);
}


int read_png_data(char *file_name,
                  png_uint_32 *p_width,
                  png_uint_32 *p_height,
                  png_byte **p_image)
{
   png_structp png_ptr;
   png_infop info_ptr;
   unsigned int sig_read = 0;
   int bit_depth, color_type, interlace_type, row;
   FILE *fp;

   if ((fp = fopen(file_name, "rb")) == NULL)
      return (1);

   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);

   if (png_ptr == NULL)
   {
      fclose(fp);
      return (2);
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
   {
      fclose(fp);
      png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
      return (3);
   }

   if (setjmp(png_jmpbuf(png_ptr)))
   {
      png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
      fclose(fp);
      return (4);
   }

   png_init_io(png_ptr, fp);

   png_set_sig_bytes(png_ptr, sig_read);

   png_read_info(png_ptr, info_ptr);

   png_get_IHDR(png_ptr, info_ptr, p_width, p_height, &bit_depth, &color_type,
       &interlace_type, int_p_NULL, int_p_NULL);

   if (bit_depth != 8) return (5);
   if (color_type != PNG_COLOR_TYPE_RGB_ALPHA) return (6);

   png_bytep row_pointers[*p_height];

   (*p_image) = malloc( (*p_height) * (*p_width) * 4 );

   for (row = 0; row < (*p_height); row++)
      row_pointers[row] = NULL;

   for (row = 0; row < (*p_height); row++)
   {
      row_pointers[row] = png_malloc(png_ptr, png_get_rowbytes(png_ptr,
         info_ptr));
   }

   for (row = 0; row < (*p_height); row++)
   {
      png_read_rows(png_ptr, &row_pointers[row], png_bytepp_NULL, 1);
      memcpy( (*p_image)+row*4*(*p_width), row_pointers[row], 4*(*p_width));
   }

   png_read_end(png_ptr, info_ptr);

   png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

   fclose(fp);

   return (0);
}


/* write a png file */
int write_png_data(char *file_name,
                   png_uint_32 width,
                   png_uint_32 height,
                   png_byte *image)
{
   FILE *fp;
   png_structp png_ptr;
   png_infop info_ptr;

   fp = fopen(file_name, "wb");
   if (fp == NULL)
      return (1);

   png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);

   if (png_ptr == NULL)
   {
      fclose(fp);
      return (2);
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
   {
      fclose(fp);
      png_destroy_write_struct(&png_ptr,  png_infopp_NULL);
      return (3);
   }

   if (setjmp(png_jmpbuf(png_ptr)))
   {
      fclose(fp);
      png_destroy_write_struct(&png_ptr, &info_ptr);
      return (4);
   }

   png_init_io(png_ptr, fp);

   png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
      PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

   png_write_info(png_ptr, info_ptr);

   png_uint_32 k;
   png_bytep row_pointers[height];

   if (height > PNG_UINT_32_MAX/png_sizeof(png_bytep))
     png_error (png_ptr, "Image is too tall to process in memory");

   for (k = 0; k < height; k++)
   {
     row_pointers[k] = image + k * width * sizeof(png_uint_32);
   }

   png_write_image(png_ptr, row_pointers);

   png_write_end(png_ptr, info_ptr);

   png_destroy_write_struct(&png_ptr, &info_ptr);

   fclose(fp);

   return (0);
}

