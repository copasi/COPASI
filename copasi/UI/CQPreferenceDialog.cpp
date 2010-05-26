// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPreferenceDialog.cpp,v $
//   $Revision: 1.5.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/05/26 13:54:23 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQPreferenceDialog.h"

#include "CQMessageBox.h"

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
    : QDialog(parent, name, modal, fl)
{
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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQPreferenceDialog::languageChange()
{
  retranslateUi(this);
}

void CQPreferenceDialog::init()
{
  mpTreeWidget->setColumnWidth(COL_NAME, 150);
  mpTreeWidget->setColumnWidth(COL_VALUE, 100);
  unsigned C_INT32 maxFiles = 0;

  CConfigurationFile * configFile = CCopasiRootContainer::getConfiguration();

  CCopasiParameter * par = configFile->getRecentFiles().getParameter("MaxFiles");
  maxFiles = *par->getValue().pUINT;

  if (maxFiles > 0)
    {
      QStringList Values;
      Values.append("Max Last Visited Files");
      Values.append(QString::number(maxFiles));

      new QTreeWidgetItem(mpTreeWidget, Values);
    }

  par = configFile->getRecentSBMLFiles().getParameter("MaxFiles");
  maxFiles = *par->getValue().pUINT;

  if (maxFiles > 0)
    {
      QStringList Values;
      Values.append("Max Last Visited SBML Files");
      Values.append(QString::number(maxFiles));

      new QTreeWidgetItem(mpTreeWidget, Values);
    }
}

void CQPreferenceDialog::slotBtnOk()
{
  unsigned C_INT32 newMaxFiles = 0;
  CCopasiParameter * par;

  CConfigurationFile * configFile = CCopasiRootContainer::getConfiguration();

  QString parName = "Max Last Visited Files";
  QList< QTreeWidgetItem *> Items = mpTreeWidget->findItems(parName, 0, 0);

  if (Items.size() > 0)
    {
      newMaxFiles = Items[0]->text(COL_VALUE).toUInt();
      par = configFile->getRecentFiles().getParameter("MaxFiles");
      unsigned C_INT32 maxFiles = *par->getValue().pUINT;

      if (newMaxFiles > 0 && newMaxFiles <= 20)
        par->setValue(newMaxFiles);
      else
        {
          CQMessageBox::critical(this, "Incorrect Setting",
                                 "Max Last Visited Files should be a number between 1 and 20.",
                                 QMessageBox::Ok, QMessageBox::Ok);
          Items[0]->setText(COL_VALUE, QString::number(maxFiles));

          return;
        }
    }

  parName = "Max Last Visited SBML Files";
  Items = mpTreeWidget->findItems(parName, 0, 0);

  if (Items.size() > 0)
    {
      newMaxFiles = Items[0]->text(COL_VALUE).toUInt();
      par = configFile->getRecentSBMLFiles().getParameter("MaxFiles");
      unsigned C_INT32 maxFiles = *par->getValue().pUINT;

      if (newMaxFiles > 0 && newMaxFiles <= 20)
        par->setValue(newMaxFiles);
      else
        {
          CQMessageBox::critical(this, "Incorrect Setting", "Max Last Visited SBML Files should be a number between 1 and 20.",
                                 QMessageBox::Ok, QMessageBox::Ok);

          Items[0]->setText(COL_VALUE, QString::number(maxFiles));

          return;
        }
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
