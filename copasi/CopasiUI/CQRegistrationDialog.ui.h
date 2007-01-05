/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQRegistrationDialog.ui.h,v $
   $Revision: 1.1.2.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2007/01/05 15:37:16 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
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
#include "CopasiDataModel/CCopasiDataModel.h"
#include "commandline/CConfigurationFile.h"
#include "utilities/CCopasiMessage.h"

void CQRegistrationDialog::init()
{
  mpRegistration = NULL;

  CCopasiParameterGroup * pRegistration =
    CCopasiDataModel::Global->getConfiguration()->getGroup("Registration");

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
  mpRegistration->setRegisteredUser((const char *) mpEditName->text().utf8());
  mpRegistration->setRegisteredEmail((const char *) mpEditEmail->text().utf8());
  mpRegistration->setRegistrationCode((const char *) mpEditCode->text().utf8());

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
    elevate< CRegistration, CCopasiParameterGroup >(CCopasiDataModel::Global->getConfiguration()->assertGroup("Registration"));

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
