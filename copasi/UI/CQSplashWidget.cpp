// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQSplashWidget.h"

#include "qtUtilities.h"
#include "AboutDialog.h"

#include "copasi/utilities/CVersion.h"
#include "copasi/core/CRootContainer.h"

/*
 *  Constructs a CQSplashWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSplashWidget::CQSplashWidget(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

  mpPixmap->setObjectName(QString::fromUtf8("mpPixmap"));
  mpPixmap->setPixmap(QPixmap((const char**)image0_data));

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSplashWidget::~CQSplashWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQSplashWidget::init()
{
  mpLblVersion->setText(mpLblVersion->text().arg(FROM_UTF8(CVersion::VERSION.getVersion())));

  return;
}

void CQSplashWidget::slotViewLicense()
{
  QString FixedTitle = "COPASI ";
  FixedTitle += FROM_UTF8(CVersion::VERSION.getVersion());

  AboutDialog* aboutDialog = new AboutDialog(this, CRootContainer::getLicenseHTML(), 76, 30);
  aboutDialog->setWindowTitle(FixedTitle);
  aboutDialog->exec();
}
