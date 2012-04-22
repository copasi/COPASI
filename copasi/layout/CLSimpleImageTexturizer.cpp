// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLSimpleImageTexturizer.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2012/04/22 14:51:16 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <fstream>
// libjpeg
#include <jpeglib.h>
#include <jerror.h>

#include <cmath>

// opengl includes
#ifdef _WIN32
#include "windows.h"
#endif // _WIN32

#ifdef __APPLE__
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#else
#include "GL/gl.h"
#include "GL/glu.h"
#endif // __APPLE__

#include "CLSimpleImageTexturizer.h"
#include "utility_classes.h"

CLTextureSpec* CLSimpleImageTexturizer::operator()(const std::string& filename, const std::string& basedir)
{
  return this->create_texture_for_image(filename, basedir);
}

/**
 * This method creates a texture from a given image file.
 * It is up to the caller to free the texture space once it is no longer needed.
 * If no texture could be created, NULL is returned.
 */
CLTextureSpec* CLSimpleImageTexturizer::create_texture_for_image(const std::string& filename, const std::string& basedir)
{
  std::string reference = to_absolute_path(filename, basedir);
  CLTextureSpec* pTexture = NULL;
  // test if the filename ends in "JPG","JPEG","jpeg" or "jpg"
  std::string::size_type pos = reference.rfind(".");
  std::string ending;

  if (pos != std::string::npos)
    {
      ++pos;
      ending = reference.substr(pos);
      std::transform(ending.begin(), ending.end(), ending.begin(), (int(*)(int))std::tolower);
    }

  if (!ending.empty())
    {
      if (ending == "jpeg" || ending == "jpg")
        {
          pTexture = create_texture_for_jpeg_image(reference);
        }
      else if (ending == "png") // test if the filename ends in "PNG" or "png"
        {
          pTexture = create_texture_for_png_image(reference);
        }
    }

  return pTexture;
}

/**
 * This method creates a texture from a given JPEG image file.
 * It is up to the caller to free the texture space once it is no longer needed.
 * If no texture could be created, NULL is returned.
 */
CLTextureSpec* CLSimpleImageTexturizer::create_texture_for_jpeg_image(const std::string& filename)
{
  CLTextureSpec* pTexture = NULL;
  FILE *fp = fopen(filename.c_str(), "rb");

  if (fp)
    {
      struct jpeg_decompress_struct cinfo;
      struct jpeg_error_mgr jerr;
      cinfo.err = jpeg_std_error(&jerr);
      jpeg_create_decompress(&cinfo);
      jpeg_stdio_src(&cinfo, fp);
      jpeg_read_header(&cinfo, true);
      cinfo.out_color_space = JCS_RGB;
      jpeg_start_decompress(&cinfo);
      // read the size and allocate the memory needed
      unsigned int width = cinfo.output_width;
      assert(cinfo.output_components == 3);
      unsigned int row_stride = width * cinfo.output_components;
      unsigned int height = cinfo.output_height;
      pTexture = new CLTextureSpec();
      pTexture->mTextureWidth = width;
      pTexture->mTextureHeight = height;
      pTexture->mTextureName = 0;
      pTexture->mNumComponents = 3;
      GLubyte* pData = new GLubyte[3*width*height];
      JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
                          ((j_common_ptr) & cinfo, JPOOL_IMAGE, row_stride, 1);

      while (cinfo.output_scanline < cinfo.output_height)
        {
          jpeg_read_scanlines(&cinfo, buffer, 1);
          memcpy(pData + (cinfo.output_scanline - 1)*row_stride, buffer[0], row_stride);
        }

      jpeg_finish_decompress(&cinfo);
      jpeg_destroy_decompress(&cinfo);
      fclose(fp);

      // right now the texture is not a power of two, but it has the same size as the image
      // we need to scale it to a power of two, for this we check which size of the texture
      // supported by the OpenGL implementation and rescale it
      GLint w = 0;
      width = (unsigned int)ceil(log(pTexture->mTextureWidth) / log(2.0));
      height = (unsigned int)ceil(log(pTexture->mTextureHeight) / log(2.0));
      width = (1 << width);
      height = (1 << height);
      GLenum format = GL_RGB;
      GLint internalFormat = GL_RGB;
      glTexImage2D(GL_PROXY_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
      glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);

      while (w == 0 && width > 0 && height > 0)
        {
          // divide the size by two in each direction
          width = width >> 1;
          height = height >> 1;
          glTexImage2D(GL_PROXY_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
          glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
        }

      if (w == 0)
        {
          // delete the texture since we can not draw it anyway
          delete pTexture;
          pTexture = NULL;
        }
      else if (w != pTexture->mTextureWidth)
        {
          if (w < pTexture->mTextureWidth)
            {
              // create a warning that the texture had to be scaled down
              std::cerr << "Image texture to large. Scaling down to size that is supported by current OpenGL implementation." << std::endl;
            }

          // rescale the texture
          GLubyte* newData = new GLubyte[pTexture->mNumComponents * width * height];

          if (gluScaleImage(format, (GLint)pTexture->mTextureWidth, (GLint)pTexture->mTextureHeight, GL_UNSIGNED_BYTE, pData, width, height, GL_UNSIGNED_BYTE, newData) == 0)
            {
              delete[] pData;
              pData = newData;
              pTexture->mTextureWidth = width;
              pTexture->mTextureHeight = height;
              pTexture->mTextWidth = pTexture->mTextureWidth;
              pTexture->mTextHeight = pTexture->mTextureHeight;
            }
          else
            {
              // an error has occured
              delete[] newData;
              delete pTexture;
              pTexture = NULL;
            }

          if (pTexture != NULL)
            {
              glGenTextures(1, &pTexture->mTextureName);
              assert(pTexture->mTextureName != 0);
              glBindTexture(GL_TEXTURE_2D, pTexture->mTextureName);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
              glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)pTexture->mTextureWidth, (GLsizei)pTexture->mTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
            }
        }

      delete[] pData;
    }

  return pTexture;
}

/**
 * This method creates a texture from a given PNG image file.
 * It is up to the caller to free the texture space once it is no longer needed.
 * If no texture could be created, NULL is returned.
 */
CLTextureSpec* CLSimpleImageTexturizer::create_texture_for_png_image(const std::string& filename)
{
  CLTextureSpec* pTexture = NULL;
  FILE *fp = fopen(filename.c_str(), "rb");

  if (fp)
    {
      png_byte header[8];
      fread(header, 1, 8, fp);

      if (!png_sig_cmp(header, 0, 8))
        {
          png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

          if (png_ptr)
            {
              png_infop info_ptr = png_create_info_struct(png_ptr);
              png_infop end_info = NULL;

              if (info_ptr)
                {
                  end_info = png_create_info_struct(png_ptr);

                  if (end_info)
                    {
                      png_init_io(png_ptr, fp);
                      png_set_sig_bytes(png_ptr, 8);
                      png_read_info(png_ptr, info_ptr);
                      unsigned int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
                      unsigned int color_type = png_get_color_type(png_ptr, info_ptr);

                      // convert a palette to an RGB image
                      if (color_type == PNG_COLOR_TYPE_PALETTE)
                        {
                          png_set_palette_to_rgb(png_ptr);
                        }

                      // convert low bit_depth grayscale images to 8 Bit
                      if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
                        {
                          png_set_gray_1_2_4_to_8(png_ptr);
                        }

                      // add an alpha channel from info
                      if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
                        {
                          png_set_tRNS_to_alpha(png_ptr);
                        }

                      // convert 16Bit images to 8 Bit
                      if (bit_depth == 16)
                        {
                          png_set_strip_16(png_ptr);
                        }

                      // convert low bit_depth images to 8 Bit
                      if (bit_depth < 8)
                        {
                          png_set_packing(png_ptr);
                        }

                      // convert grayscale to RGB
                      if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                        {
                          png_set_gray_to_rgb(png_ptr);
                        }

                      // add an alpha channel to RGB images
                      if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY)
                        {
                          png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
                        }

                      // enable interlace handling to expand the image if it
                      // is interlaced
                      /*unsigned int num_passes=*/png_set_interlace_handling(png_ptr);
                      // now we reread the info and get the width and height
                      // in order to allocate enough memory
                      png_read_update_info(png_ptr, info_ptr);
                      unsigned int width = png_get_image_width(png_ptr, info_ptr);
                      unsigned int height = png_get_image_height(png_ptr, info_ptr);

                      if (height > 0)
                        {
                          // create the texture object
                          pTexture = new CLTextureSpec();
                          // we have to reserve enough memory for a width*height
                          // RGBA image
                          GLubyte* pData = new GLubyte[4*width*height];
                          pTexture->mTextureWidth = width;
                          pTexture->mTextureHeight = height;
                          pTexture->mNumComponents = 4;
                          pTexture->mTextureName = 0;
                          // create an array with pointers to the rows
                          png_bytepp pRow_pointers = new png_bytep[height];
                          unsigned int i;

                          for (i = 0; i < height; ++i)
                            {
                              pRow_pointers[i] = (&(pData[4*width*i]));
                            }

                          png_read_image(png_ptr, pRow_pointers);
                          png_read_end(png_ptr, end_info);
                          fclose(fp);
                          // right now the texture is not a power of two, but it has the same size as the image
                          // we need to scale it to a power of two, for this we check which size of the texture
                          // supported by the OpenGL implementation and rescale it
                          GLint w = 0;
                          width = (unsigned int)ceil(log(pTexture->mTextureWidth) / log(2.0));
                          height = (unsigned int)ceil(log(pTexture->mTextureHeight) / log(2.0));
                          width = (1 << width);
                          height = (1 << height);
                          GLenum format = GL_RGBA;
                          GLint internalFormat = GL_RGBA;
                          glTexImage2D(GL_PROXY_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
                          glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);

                          while (w == 0 && width > 0 && height > 0)
                            {
                              // divide the size by two in each direction
                              width = width >> 1;
                              height = height >> 1;
                              glTexImage2D(GL_PROXY_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
                              glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
                            }

                          if (w == 0)
                            {
                              // delete the texture since we can not draw it anyway
                              delete pTexture;
                              pTexture = NULL;
                            }
                          else if (w != pTexture->mTextureWidth)
                            {
                              if (w < pTexture->mTextureWidth)
                                {
                                  // create a warning that the texture had to be scaled down
                                  std::cerr << "Image texture to large. Scaling down to size that is supported by current OpenGL implementation." << std::endl;
                                }

                              // rescale the texture
                              GLubyte* newData = new GLubyte[pTexture->mNumComponents * width * height];

                              if (gluScaleImage(format, (GLint)pTexture->mTextureWidth, (GLint)pTexture->mTextureHeight, GL_UNSIGNED_BYTE, pData, width, height, GL_UNSIGNED_BYTE, newData) == 0)
                                {
                                  delete[] pData;
                                  pData = newData;
                                  pTexture->mTextureWidth = width;
                                  pTexture->mTextureHeight = height;
                                  pTexture->mTextWidth = pTexture->mTextureWidth;
                                  pTexture->mTextHeight = pTexture->mTextureHeight;
                                }
                              else
                                {
                                  // an error has occured
                                  delete[] newData;
                                  delete pTexture;
                                  pTexture = NULL;
                                }

                              if (pTexture != NULL)
                                {
                                  glGenTextures(1, &pTexture->mTextureName);
                                  assert(pTexture->mTextureName != 0);
                                  glBindTexture(GL_TEXTURE_2D, pTexture->mTextureName);
                                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                                  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                                  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)pTexture->mTextureWidth, (GLsizei)pTexture->mTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
                                }
                            }

                          delete[] pData;
                          delete[] pRow_pointers;
                        }
                    }
                }

              // delete the png structures again
              png_destroy_read_struct(&png_ptr, (png_infopp)&info_ptr, (png_infopp)&end_info);
            }
        }
    }

  return pTexture;
}
