// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQSplashWidget.ui.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:47:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
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

#include "qtUtilities.h"
#include "AboutDialog.h"

#include "utilities/CVersion.h"

extern const char * CopasiLicense;

void CQSplashWidget::init()
{
  mpLblVersion->setText(mpLblVersion->text().arg(FROM_UTF8(CVersion::VERSION.getVersion())));

  return;
}

void CQSplashWidget::slotViewLicense()
{
  QString FixedTitle = "COPASI ";
#ifdef COPASI_LICENSE_COM
  FixedTitle += "(commercial) ";
#endif // COPASI_LICENSE_COM
  FixedTitle += FROM_UTF8(CVersion::VERSION.getVersion());

  AboutDialog* aboutDialog = new AboutDialog(this, CopasiLicense, 76, 30);
  aboutDialog->setCaption(FixedTitle);
  aboutDialog->exec();
}
