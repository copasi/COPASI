// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/Attic/FontChooser.ui.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/05/27 10:53:45 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/
#include "copasi.h"
#include "copasi/layoutUI/CQLayoutMainWindow.h"
#include "copasi/layoutUI/CQGLNetworkPainter.h"

void FontChooser::changeFontSize()
{
  QString className = QString(parentWidget()->className());
  C_INT32 val = spinBox1->value();

  if (className == "CQLayoutMainWindow")
    {
      CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget());
      assert(tmp);

      if (tmp)
        tmp->setFontSizeForLabels(val);
    }
  else if (className == "CQGLNetworkPainter") // check for another possible parent window
    {
      CQGLNetworkPainter * tmp = dynamic_cast<CQGLNetworkPainter *>(parentWidget());
      assert (tmp);

      if (tmp)
        tmp->setFontSizeForLabels((unsigned int) val);
    }
}

void FontChooser::cancel()
{
  close();
}

void FontChooser::init()
{
  QString className = QString(parentWidget()->className());

  if (className == "CQLayoutMainWindow")
    {
      CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget());
      assert(tmp);
      if (tmp)
        {
          C_INT32 currentFontSize = (C_INT32)(tmp->getFontSize());
          spinBox1->setValue(currentFontSize);
        }
    }
  else if (className == "CQGLNetworkPainter")
    {
      CQGLNetworkPainter * tmp = dynamic_cast<CQGLNetworkPainter *>(parentWidget());
      assert (tmp);

      if (tmp)
        {
          C_INT32 currentFontSize = (C_INT32)(tmp->getFontSize());
          spinBox1->setValue(currentFontSize);
        }
    }
}
