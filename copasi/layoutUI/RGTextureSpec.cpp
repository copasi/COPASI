// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/RGTextureSpec.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/11 12:41:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "RGTextureSpec.h"

#ifdef COPASI_DEBUG
#include <fstream>

bool RGTextureSpec::save(const std::string& filename)
{
  bool success = false;
  std::ofstream ofs(filename.c_str());
  if (ofs.good())
    {
      /**
       * RGB header
      char header[18]={0,0,2,0,0,0,
          0,0,0,0,0,0,
          (char)this->textureWidth,(char)(((unsigned int)this->textureWidth) >> 8),
          (char)this->textureHeight,(char)(((unsigned int)this->textureHeight) >> 8),
          24,32
      };
      */
      // grayscale header
      char header[18] = {0, 0, 3, 0, 0, 0,
                         0, 0, 0, 0, 0, 0,
                         (char)this->textureWidth, (char)(((unsigned int)this->textureWidth) >> 8),
                         (char)this->textureHeight, (char)(((unsigned int)this->textureHeight) >> 8),
                         8, 32
                        };

      ofs.write(header, 18);
      ofs.write((char*)this->textureData, this->textureWidth * this->textureHeight);
      ofs.close();
      success = true;
    }
  return success;
}
#endif // COPASI_DEBUG
