/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQRegistrationDialog.ui.h,v $
 $Revision: 1.3 $
 $Name:  $
 $Author: gauges $
 $Date: 2009/02/18 20:47:31 $
 End CVS Header */

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

#include "commercial/CRegistration.h"
#include "commandline/CConfigurationFile.h"
#include "utilities/CCopasiMessage.h"
#include "report/CCopasiRootContainer.h"

void CQRegistrationDialog::init()
{
  mpRegistration = NULL;

  CCopasiParameterGroup * pRegistration =
    CCopasiRootContainer::Root->getConfiguration()->getGroup("Registration");

  if (pRegistration == NULL)
    mpRegistration = new CRegistration;
  else
    mpRegistration = new CRegistration(*pRegistration);

  mpEditName->setText(FROM_UTF8(mpRegistration->getRegisteredUser()));
  mpEditEmail->setText(FROM_UTF8(mpRegistration->getRegisteredEmail()));
  mpEditCode->setText(FROM_UTF8(mpRegistration->getRegistrationCode()));

  slotBtnValidate();
}

void CQRegistrationDialog::destroy()
{
  pdelete(mpRegistration);
}

void CQRegistrationDialog::slotBtnValidate()
{
  mpRegistration->setRegisteredUser(TO_UTF8(mpEditName->text()));
  mpRegistration->setRegisteredEmail(TO_UTF8(mpEditEmail->text()));
  mpRegistration->setRegistrationCode(TO_UTF8(mpEditCode->text()));

  if (!mpRegistration->isValidRegistration())
    mpEditStatus->setText(FROM_UTF8(CCopasiMessage::getLastMessage().getText()));
  else
    mpEditStatus->setText("Valid");

  mpEditDate->setText(FROM_UTF8(mpRegistration->getExpirationDate()));
}

void CQRegistrationDialog::slotBtnOk()
{
  slotBtnValidate();

  CRegistration * pRegistration =
    elevate< CRegistration, CCopasiParameterGroup >(CCopasiRootContainer::Root->getConfiguration()->assertGroup("Registration"));

  pRegistration->setRegisteredUser(mpRegistration->getRegisteredUser());
  pRegistration->setRegisteredEmail(mpRegistration->getRegisteredEmail());
  pRegistration->setRegistrationCode(mpRegistration->getRegistrationCode());

  if (pRegistration->isValidRegistration())
    accept();
  else
    reject();

  CCopasiMessage::clearDeque();
}

void CQRegistrationDialog::slotBtnCancel()
{
  reject();
}
