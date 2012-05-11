// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPreferenceDialog.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: bergmann $
//   $Date: 2012/05/11 12:51:39 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQPreferenceDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "commandline/CConfigurationFile.h"
#include "report/CCopasiRootContainer.h"

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
  // no need to delete child widgets, Qt does it all for us
}

void CQPreferenceDialog::init()
{
  mpTreeWidget->setColumnWidth(COL_NAME, 150);
  mpTreeWidget->setColumnWidth(COL_VALUE, 100);

  CConfigurationFile * configFile = CCopasiRootContainer::getConfiguration();

  CCopasiParameter * pParameter = configFile->getRecentFiles().getParameter("MaxFiles");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Max Last Visited Files");
      Values.append(QString::number(*pParameter->getValue().pUINT));

      new QTreeWidgetItem(mpTreeWidget, Values);
    }

  pParameter = configFile->getRecentSBMLFiles().getParameter("MaxFiles");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Max Last Visited SBML Files");
      Values.append(QString::number(*pParameter->getValue().pUINT));

      new QTreeWidgetItem(mpTreeWidget, Values);
    }

  pParameter = configFile->getParameter("Application for opening URLs");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Application for opening URLs");
      Values.append(FROM_UTF8(*pParameter->getValue().pSTRING));

      new QTreeWidgetItem(mpTreeWidget, Values);
    }

  pParameter = configFile->getParameter("Validate Units");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Validate Units");
      Values.append((*pParameter->getValue().pBOOL ? "YES" : "NO"));
      new QTreeWidgetItem(mpTreeWidget, Values);
    }

}

void CQPreferenceDialog::slotBtnOk()
{
  // We need to commit the changes
  mpBtnOk->setFocus();

  unsigned C_INT32 newMaxFiles = 0;
  CConfigurationFile * configFile = CCopasiRootContainer::getConfiguration();

  QList< QTreeWidgetItem *> Items = mpTreeWidget->findItems("Max Last Visited Files", 0, 0);
  CCopasiParameter * pParameter = configFile->getRecentFiles().getParameter("MaxFiles");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      newMaxFiles = Items[0]->text(COL_VALUE).toUInt();
      unsigned C_INT32 maxFiles = *pParameter->getValue().pUINT;

      if (newMaxFiles > 0 && newMaxFiles <= 20)
        pParameter->setValue(newMaxFiles);
      else
        {
          CQMessageBox::critical(this, "Incorrect Setting",
                                 "Max Last Visited Files should be a number between 1 and 20.",
                                 QMessageBox::Ok, QMessageBox::Ok);
          Items[0]->setText(COL_VALUE, QString::number(maxFiles));

          return;
        }
    }

  Items = mpTreeWidget->findItems("Max Last Visited SBML Files", 0, 0);
  pParameter = configFile->getRecentSBMLFiles().getParameter("MaxFiles");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      newMaxFiles = Items[0]->text(COL_VALUE).toUInt();
      unsigned C_INT32 maxFiles = *pParameter->getValue().pUINT;

      if (newMaxFiles > 0 && newMaxFiles <= 20)
        pParameter->setValue(newMaxFiles);
      else
        {
          CQMessageBox::critical(this, "Incorrect Setting", "Max Last Visited SBML Files should be a number between 1 and 20.",
                                 QMessageBox::Ok, QMessageBox::Ok);

          Items[0]->setText(COL_VALUE, QString::number(maxFiles));

          return;
        }
    }

  Items = mpTreeWidget->findItems("Application for opening URLs", 0, 0);
  pParameter = configFile->getParameter("Application for opening URLs");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {

      if (Items[0]->text(COL_VALUE) != FROM_UTF8(*pParameter->getValue().pSTRING))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }

  Items = mpTreeWidget->findItems("Validate Units", 0, 0);
  pParameter = configFile->getParameter("Validate Units");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  done(1);
}

// virtual
void CQPreferenceDialog::slotBtnCancel()
{
  done(0);
}

// virtual
void CQPreferenceDialog::slotItemDoubleClicked(QTreeWidgetItem* pItem, int column)
{
  if (column == COL_VALUE)
    {
      Qt::ItemFlags Flags = pItem->flags();
      pItem->setFlags(Flags | Qt::ItemIsEditable);

      mpTreeWidget->editItem(pItem, column);

      pItem->setFlags(Flags);
    }
}
