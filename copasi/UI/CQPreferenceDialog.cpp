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


#include <QApplication>

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

#include <copasi/commandline/COptions.h>
#include <copasi/utilities/CDirEntry.h>

#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QFile>
#include <QFormLayout>


void CQPreferenceDialog::slotPropertyChanged()
{
  auto widget = dynamic_cast<QWidget*>(sender());
  if (widget == nullptr)
    return;

  auto parameter = mWidgetToParameter[widget];
  if (parameter == nullptr)
    return;

  if (auto edit = dynamic_cast<QLineEdit*>(widget))
  {
    parameter->setValue(edit->text().toStdString());    
  }
  else if (auto edit = dynamic_cast<QCheckBox*>(widget))
  {
    parameter->setValue(edit->isChecked());
  }
  else if (auto edit = dynamic_cast<QSpinBox*>(widget))
  {
    parameter->setValue(parameter->getType() == CCopasiParameter::Type::UINT ? (unsigned int) edit->value() : edit->value());
  }
}

void CQPreferenceDialog::initTabsFromSettings(QSettings& settings)
{
  // the ini file will have groups for each tab, each tab should 
  // have a form layout with the name of the setting as the key
  // and the value as the value

  // first we create all the tabs
  QStringList groups = settings.childGroups();

  mWidgetToParameter.clear();

  for (auto mainGroup : groups)
  {
    settings.beginGroup(mainGroup);
    auto tab = new QWidget();
    auto layout = new QFormLayout(tab);
    tab->setLayout(layout);
    tabWidget->insertTab(0, tab, mainGroup);

    // each group has child elements with keys: 
    // - name: the name of the setting
    // - type: the type of the setting
    // - parameter: the parameter of the COPASI setting to change
    // - tooltip: the tooltip of the setting
    // - value: the value of the setting

    QStringList childGroups = settings.childGroups();
    for (auto group : childGroups)
    {
      settings.beginGroup(group);
      auto name = settings.value("name").toString();
      auto type = settings.value("type").toString();
      auto parameter = settings.value("parameter").toString();
      auto value = settings.value("value");
      
      auto param_path = parameter.split(".");
      CCopasiParameter * pNode = mpConfiguration;
      for (auto paramName : param_path)
        if (pNode && dynamic_cast< CCopasiParameterGroup * >(pNode))
          pNode = dynamic_cast< CCopasiParameterGroup * >(pNode)->getParameter(paramName.toStdString());
      
      auto tooltip = settings.value("tooltip").toString();
      if (!tooltip.isEmpty())
        std::cout << tooltip.toStdString();

      if (type == "string")
      {
        auto edit = new QLineEdit(value.toString());
        edit->setToolTip(tooltip);
        
        if (pNode)
          edit->setText(FROM_UTF8(pNode->getValue<std::string>()));
        layout->addRow(name, edit);
        connect(edit, &QLineEdit::textChanged, this, &CQPreferenceDialog::slotPropertyChanged);
        mWidgetToParameter[edit] = pNode;
      }
      else if (type == "bool")
      {
        auto edit = new QCheckBox(name);
        edit->setChecked(value.toBool());
        if (pNode)
          edit->setChecked(pNode->getValue< bool >());
        edit->setToolTip(tooltip);
        layout->addRow(edit);

        connect(edit, &QCheckBox::stateChanged, this, &CQPreferenceDialog::slotPropertyChanged);
        mWidgetToParameter[edit] = pNode;
      }
      else if (type == "int")
      {
        auto edit = new QSpinBox();
        edit->setToolTip(tooltip);
        edit->setValue(value.toInt());
        if (pNode)
          edit->setValue(pNode->getValue< int >());
        layout->addRow(name, edit);

        connect(edit, QOverload<int>::of(&QSpinBox::valueChanged), this, &CQPreferenceDialog::slotPropertyChanged);
        mWidgetToParameter[edit] = pNode;
      }      
      else
      {
        CQMessageBox::warning(this, "Error", "Unknown type: " + type);
      }

      settings.endGroup();
    }

    settings.endGroup();
  }

  tabWidget->setCurrentIndex(0);
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


  // initialize other tabs from config file
  auto copasiDir = COptions::getConfigDir();
  auto preferenceConfigFile = copasiDir + "/preferences.ini";
  if (!CDirEntry::exist(preferenceConfigFile))
  {
    // load default preference.ini from resource
    Q_INIT_RESOURCE(copasi);

    QFile file(":/preferences.ini");
    if (file.open(QIODevice::ReadOnly))
      {
        QFile outFile(FROM_UTF8(preferenceConfigFile));
        if (outFile.open(QIODevice::WriteOnly))
          {
            outFile.write(file.readAll());
            outFile.close();
          }
        file.close();        
      }
  }


  QSettings settings(preferenceConfigFile.c_str(), QSettings::IniFormat, this);
  initTabsFromSettings(settings);
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
