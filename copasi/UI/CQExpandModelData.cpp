// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpandModelData.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2010/02/01 11:39:09 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModelExpansion.h"
#include "report/CCopasiRootContainer.h"
#include "UI/CCopasiSelectionDialog.h"
#include "CQMessageBox.h"

#include "UI/qtUtilities.h"
#include <qsignalmapper.h>
#include <qcombobox.h>
#include <qapplication.h>

#include <QHeaderView>
#include <QString>
#include "CQExpandModelData.h"

/*
 *  Constructs a CQExpandModelData which is a child of 'parent', with the
 *  name 'name'.'
 */

CQExpandModelData::CQExpandModelData(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setupUi(this);

  load();
}
/*
 *  Destroys the object and frees any allocated resources
 */
CQExpandModelData::~CQExpandModelData()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
//void CQexpandModelData::languageChange()
//{
//  retranslateUi(this);
//}

void CQExpandModelData::load()
{

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  mpComboMap = NULL;

  pdelete(mpComboMap);
  mpComboMap = new QSignalMapper(this);
  connect(mpComboMap, SIGNAL(mapped(int)), this, SLOT(slotCompartmentChanged(/* int */)));
  connect(mpCheckDiffusion, SIGNAL(toggled(bool)), this, SLOT(slotApplyDiffusion(bool)));

  pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  unsigned C_INT32 i, imax = pModel->getCompartments().size();

  mCompartmentName.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      const CCompartment* comp = pModel->getCompartments()[i];
      mCompartmentName[i] =  comp->getObjectName();
    }

  for (i = 0; i < imax; ++i)
    mpBoxCompartmentName->insertItem(FROM_UTF8(mCompartmentName[i]));

  for (i = 0; i < imax; i++)
    {

      mpBoxCompartmentName->setEditable(false);

      mpComboMap->setMapping(mpBoxCompartmentName, i);
      connect(mpBoxCompartmentName, SIGNAL(activated(int)), mpComboMap, SLOT(map()));
    }

  mpEditNumber->setText(QString::number(1));
  mpEditNumber->setEnabled(true);

  mpCheckDiffusion->setChecked(false);
  slotApplyDiffusion(false);

  if (mpCheckDiffusion->isChecked()) slotApplyDiffusion(true);
}
void CQExpandModelData::slotOK()
{
  std::string name =  static_cast<std::string >(mpBoxCompartmentName->currentText().toUtf8());     //toStdString();

  unsigned C_INT32 i, imax = pModel->getCompartments().size();

  std::string key;

  const CCompartment* source;

  for (i = 0; i < imax; ++i)
    if (mCompartmentName[i] ==  name) source =  pModel->getCompartments()[i];

  int mult =  mpEditNumber->text().toInt();

  if (mult < 0)
    {

      CQMessageBox::critical(this, QString("Error"),
                             QString("The choise of the Number of copies is incorect  ! "),
                             QMessageBox::Ok, QMessageBox::Ok);

      return;
    }

  std::string metabname;
  const CMetab* metab;
  bool diff = mpCheckDiffusion->isChecked();

  if (diff)
    {

      metabname =  static_cast<std::string >(mpBoxMetaboliteName->currentText().toUtf8());
      imax = source->getMetabolites().size();

      for (i = 0; i < imax; ++i)
        if (mMetaboliteName[i] ==  metabname) metab  =  source->getMetabolites()[i];
    }

  CModelExpansion me(pModel);
  //me.simpleCall(source, mult);
  me.simpleCall(source, metab, mult, diff);

  accept();
}

void CQExpandModelData::slotCancel()
{
  reject();
}

void CQExpandModelData::slotCompartmentChanged(/* int row */)
{

  mpEditNumber->setText(QString::number(1));

  std::string name =  static_cast<std::string >(mpBoxCompartmentName->currentText().toUtf8());     //toStdString();

  unsigned C_INT32 i, imax = pModel->getCompartments().size();

  std::string key;

  const CCompartment* source;

  for (i = 0; i < imax; ++i)
    if (mCompartmentName[i] ==  name) source =  pModel->getCompartments()[i];

  if (mpCheckDiffusion->isChecked())
    slotApplyDiffusion(true);
  else
    slotApplyDiffusion(false);

  return;
}

void CQExpandModelData::slotApplyDiffusion(bool show)
{

  mpBoxMetaboliteName->clear();

  if (show)
    {
      mpLblMetaboliteName->show();
      mpBoxMetaboliteName->show();

      std::string name =  static_cast<std::string >(mpBoxCompartmentName->currentText().toUtf8());     //toStdString();

      unsigned C_INT32 i, imax = pModel->getCompartments().size();

      const CCompartment* comp;

      for (i = 0; i < imax; ++i)
        if (mCompartmentName[i] ==  name) comp =  pModel->getCompartments()[i];

      imax = comp->getMetabolites().size();
      mMetaboliteName.resize(imax);

      for (i = 0; i < imax; ++i)
        {
          const CMetab* metab = comp->getMetabolites()[i];
          mMetaboliteName[i] = metab->getObjectName();
        }

      for (i = 0; i < imax; ++i)
        mpBoxMetaboliteName->insertItem(FROM_UTF8(mMetaboliteName[i]));

      for (i = 0; i < imax; i++)
        {

          mpBoxMetaboliteName->setEditable(false);

          //mpComboMap->setMapping(mpBoxMetaboliteName, i);
          //connect(mpBoxMetaboliteName, SIGNAL(activated(int)), mpComboMap, SLOT(map()));
        }
    }

  else
    {
      mpLblMetaboliteName->hide();
      mpBoxMetaboliteName->hide();
    }
}
