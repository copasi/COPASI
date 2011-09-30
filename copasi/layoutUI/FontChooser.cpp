// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/FontChooser.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:56 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Qt headers
#include <QString>

// global headers
#include <assert.h>

// global copasi headers
#include "copasi/copasi.h"

// local copasi headers
#include "FontChooser.h"
#include "CQLayoutMainWindow.h"
#include "CQGLNetworkPainter.h"

FontChooser::FontChooser(QWidget* parent , bool modal , Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);
  this->setModal(modal);
  QString className = QString(parentWidget()->metaObject()->className());

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
      assert(tmp);

      if (tmp)
        {
          C_INT32 currentFontSize = (C_INT32)(tmp->getFontSize());
          spinBox1->setValue(currentFontSize);
        }
    }
}

void FontChooser::changeFontSize()
{
  QString className = QString(parentWidget()->metaObject()->className());
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
      assert(tmp);

      if (tmp)
        tmp->setFontSizeForLabels((unsigned int) val);
    }
}

void FontChooser::cancel()
{
  close();
}
