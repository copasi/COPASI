// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include "qtUtilities.h"

#include "commandline/CConfigurationFile.h"
#include "copasi/core/CRootContainer.h"

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
  CConfigurationFile * configFile = CRootContainer::getConfiguration();
  mpTreeView->setAdvanced(false);
  mpTreeView->pushGroup(configFile);

  CCopasiParameter * pParameter = configFile->getRecentFiles().getParameter("MaxFiles");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Max Last Visited Files");
      Values.append(QString::number(pParameter->getValue< unsigned C_INT32 >()));

      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getRecentSBMLFiles().getParameter("MaxFiles");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Max Last Visited SBML Files");
      Values.append(QString::number(pParameter->getValue< unsigned C_INT32 >()));

      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Application for opening URLs");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Application for opening URLs");
      Values.append(FROM_UTF8(pParameter->getValue< std::string >()));

      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Validate Units");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Validate Units");
      Values.append((pParameter->getValue< bool >() ? "YES" : "NO"));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Use OpenGL");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Use OpenGL");
      Values.append((pParameter->getValue< bool >() ? "YES" : "NO"));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Use Advanced Sliders");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Use Advanced Sliders");
      Values.append((pParameter->getValue< bool >() ? "YES" : "NO"));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Use Advanced Editing");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Use Advanced Editing");
      Values.append((pParameter->getValue< bool >() ? "YES" : "NO"));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Normalize Weights per Experiment");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Normalize Weights per Experiment");
      Values.append((pParameter->getValue< bool >() ? "YES" : "NO"));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Display Populations during Optimization");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Display Populations during Optimization");
      Values.append((pParameter->getValue< bool >() ? "YES" : "NO"));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Proxy Server");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Proxy Server");
      Values.append(FROM_UTF8(pParameter->getValue< std::string >()));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Proxy Port");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Proxy Port");
      Values.append(QString::number(pParameter->getValue< C_INT32 >()));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Proxy User");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Proxy User");
      Values.append(FROM_UTF8(pParameter->getValue< std::string >()));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Proxy Password");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Proxy Password");
      Values.append(FROM_UTF8(pParameter->getValue< std::string >()));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  // Adding current author information
  pParameter = configFile->getParameter("Given Name");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Given Name");
      Values.append(FROM_UTF8(pParameter->getValue< std::string >()));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Famliy Name");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Famliy Name");
      Values.append(FROM_UTF8(pParameter->getValue< std::string >()));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Organization");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Organization");
      Values.append(FROM_UTF8(pParameter->getValue< std::string >()));
      // new QTreeWidgetItem(mpTreeView, Values);
    }

  pParameter = configFile->getParameter("Email");

  if (pParameter != NULL)
    {
      QStringList Values;
      Values.append("Email");
      Values.append(FROM_UTF8(pParameter->getValue< std::string >()));
      // new QTreeWidgetItem(mpTreeView, Values);
    }
}

void CQPreferenceDialog::slotBtnOk()
{
  // We need to commit the changes
  unsigned C_INT32 newMaxFiles = 0;
  CConfigurationFile * configFile = CRootContainer::getConfiguration();

  /*
  QList< QTreeWidgetItem *> Items = mpTreeView->findItems("Max Last Visited Files", 0, 0);
  CCopasiParameter * pParameter = configFile->getRecentFiles().getParameter("MaxFiles");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      newMaxFiles = Items[0]->text(COL_VALUE).toUInt();
      unsigned C_INT32 maxFiles = pParameter->getValue< unsigned C_INT32 >();

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

  Items = mpTreeView->findItems("Max Last Visited SBML Files", 0, 0);
  pParameter = configFile->getRecentSBMLFiles().getParameter("MaxFiles");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      newMaxFiles = Items[0]->text(COL_VALUE).toUInt();
      unsigned C_INT32 maxFiles = pParameter->getValue< unsigned C_INT32 >();

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

  Items = mpTreeView->findItems("Application for opening URLs", 0, 0);
  pParameter = configFile->getParameter("Application for opening URLs");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {

      if (Items[0]->text(COL_VALUE) != FROM_UTF8(pParameter->getValue< std::string >()))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }

  Items = mpTreeView->findItems("Validate Units", 0, 0);
  pParameter = configFile->getParameter("Validate Units");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeView->findItems("Use OpenGL", 0, 0);
  pParameter = configFile->getParameter("Use OpenGL");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeView->findItems("Use Advanced Sliders", 0, 0);
  pParameter = configFile->getParameter("Use Advanced Sliders");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeView->findItems("Use Advanced Editing", 0, 0);
  pParameter = configFile->getParameter("Use Advanced Editing");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeView->findItems("Normalize Weights per Experiment", 0, 0);
  pParameter = configFile->getParameter("Normalize Weights per Experiment");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeView->findItems("Display Populations during Optimization", 0, 0);
  pParameter = configFile->getParameter("Display Populations during Optimization");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      pParameter->setValue(Items[0]->text(COL_VALUE).toUpper() == "YES");
    }

  Items = mpTreeView->findItems("Proxy Server", 0, 0);
  pParameter = configFile->getParameter("Proxy Server");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {

      if (Items[0]->text(COL_VALUE) != FROM_UTF8(pParameter->getValue< std::string >()))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }

  Items = mpTreeView->findItems("Proxy Port", 0, 0);
  pParameter = configFile->getParameter("Proxy Port");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      C_INT32 port = Items[0]->text(COL_VALUE).toInt();
      pParameter->setValue(port);
    }

  Items = mpTreeView->findItems("Proxy User", 0, 0);
  pParameter = configFile->getParameter("Proxy User");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {

      if (Items[0]->text(COL_VALUE) != FROM_UTF8(pParameter->getValue< std::string >()))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }

  Items = mpTreeView->findItems("Proxy Password", 0, 0);
  pParameter = configFile->getParameter("Proxy Password");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {

      if (Items[0]->text(COL_VALUE) != FROM_UTF8(pParameter->getValue< std::string >()))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }

  Items = mpTreeView->findItems("Given Name", 0, 0);
  pParameter = configFile->getParameter("Given Name");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      if (Items[0]->text(COL_VALUE) != FROM_UTF8(pParameter->getValue< std::string >()))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }

  Items = mpTreeView->findItems("Famliy Name", 0, 0);
  pParameter = configFile->getParameter("Famliy Name");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      if (Items[0]->text(COL_VALUE) != FROM_UTF8(pParameter->getValue< std::string >()))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }

  Items = mpTreeView->findItems("Organization", 0, 0);
  pParameter = configFile->getParameter("Organization");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      if (Items[0]->text(COL_VALUE) != FROM_UTF8(pParameter->getValue< std::string >()))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }

  Items = mpTreeView->findItems("Email", 0, 0);
  pParameter = configFile->getParameter("Email");

  if (Items.size() > 0 &&
      pParameter != NULL)
    {
      if (Items[0]->text(COL_VALUE) != FROM_UTF8(pParameter->getValue< std::string >()))
        pParameter->setValue(std::string(TO_UTF8(Items[0]->text(COL_VALUE))));
    }
  */
  done(1);
}

// virtual
void CQPreferenceDialog::slotBtnCancel()
{
  done(0);
}
