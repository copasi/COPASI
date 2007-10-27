// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMIRIAMModelWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/27 01:57:08 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CMIRIAMMODELWIDGET
#define COPASI_CMIRIAMMODELWIDGET

#include "CopasiWidget.h"

class CAuthorsWidget;

class CMIRIAMModelWidget : public CopasiWidget
  {
    Q_OBJECT
  public:
    CMIRIAMModelWidget(QWidget *parent, const char * name = 0, WFlags f = 0);

  private:
    CAuthorsWidget *mAuthorsWidget;
  };

#endif // COPASI_CMIRIAMMODELWIDGET
