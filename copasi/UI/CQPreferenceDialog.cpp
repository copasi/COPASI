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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQPreferenceDialog.h"
#include "CQMessageBox.h"

#include "copasi/copasi.h"
#include "qtUtilities.h"

#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/core/CRootContainer.h"

#include <copasi/MIRIAM/CConstants.h>

#define COL_NAME 0
#define COL_VALUE 1

/*
 *  Constructs a CQPreferenceDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQPreferenceDialog::CQPreferenceDialog(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
  : QDialog(parent, fl)
  , mpConfiguration(NULL)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQPreferenceDialog::~CQPreferenceDialog()
{
  if (mpConfiguration != NULL)
    {
      delete mpConfiguration;
      mpConfiguration = NULL;
      // restore pointer to miriam resources
      CMIRIAMResourceObject::setMIRIAMResources(&CRootContainer::getConfiguration()->getRecentMIRIAMResources());
    }
}

void CQPreferenceDialog::init()
{
  CConfigurationFile * pConfigFile = CRootContainer::getConfiguration();

  if (pConfigFile != NULL)
    {
      mpConfiguration = new CConfigurationFile(*pConfigFile, NO_PARENT);
    }

  mpTreeView->setAdvanced(false);
  mpTreeView->pushGroup(mpConfiguration);
}

void CQPreferenceDialog::slotBtnOk()
{
  if (mpConfiguration != NULL)
    {
      *CRootContainer::getConfiguration() = *mpConfiguration;

      // remove items from tree, otherwise node pointers will become invalid
      mpTreeView->clearGroups();

      delete mpConfiguration;
      mpConfiguration = NULL;
    }

  done(1);
}

// virtual
void CQPreferenceDialog::slotBtnCancel()
{
  if (mpConfiguration != NULL)
    {
      // remove items from tree, otherwise node pointers will become invalid
      mpTreeView->clearGroups();

      delete mpConfiguration;
      mpConfiguration = NULL;
      // restore pointer to miriam resources
      CMIRIAMResourceObject::setMIRIAMResources(&CRootContainer::getConfiguration()->getRecentMIRIAMResources());
    }

  done(0);
}
