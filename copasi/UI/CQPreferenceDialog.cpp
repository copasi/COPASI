// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

  pParameter = configFile->getParameter("Use OpenGL");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Use OpenGL");
      Values.append((*pParameter->getValue().pBOOL ? "YES" : "NO"));
      new QTreeWidgetItem(mpTreeWidget, Values);
    }

  pParameter = configFile->getParameter("Use Advanced Sliders");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Use Advanced Sliders");
      Values.append((*pParameter->getValue().pBOOL ? "YES" : "NO"));
      new QTreeWidgetItem(mpTreeWidget, Values);
    }

  pParameter = configFile->getParameter("Use Advanced Editing");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Use Advanced Editing");
      Values.append((*pParameter->getValue().pBOOL ? "YES" : "NO"));
      new QTreeWidgetItem(mpTreeWidget, Values);
    }

  pParameter = configFile->getParameter("Normalize Weights per Experiment");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Normalize Weights per Experiment");
      Values.append((*pParameter->getValue().pBOOL ? "YES" : "NO"));
      new QTreeWidgetItem(mpTreeWidget, Values);
    }

  pParameter = configFile->getParameter("Allow Simultaneous Event Assignments");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Allow Simultaneous Event Assignments");
      Values.append((*pParameter->getValue().pBOOL ? "YES" : "NO"));
      new QTreeWidgetItem(mpTreeWidget, Values);
    }
}

void CQPreferenceDialog::slotBtnOk()
{
  // We need to commit the changes
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

  Items = mpTreeWidget->findItems("Use OpenGL", 0, 0);
  pParameter = configFile->getParameter("Use OpenGL");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeWidget->findItems("Use Advanced Sliders", 0, 0);
  pParameter = configFile->getParameter("Use Advanced Sliders");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeWidget->findItems("Use Advanced Editing", 0, 0);
  pParameter = configFile->getParameter("Use Advanced Editing");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeWidget->findItems("Normalize Weights per Experiment", 0, 0);
  pParameter = configFile->getParameter("Normalize Weights per Experiment");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeWidget->findItems("Allow Simultaneous Event Assignments", 0, 0);
  pParameter = configFile->getParameter("Allow Simultaneous Event Assignments");

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
