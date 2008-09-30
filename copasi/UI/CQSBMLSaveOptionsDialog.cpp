// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSBMLSaveOptionsDialog.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/30 15:13:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSBMLSaveOptionsDialog.h"

#include <qlayout.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qtooltip.h>

/**
 * Constructor.
 */
CQSBMLSaveOptionsDialog::CQSBMLSaveOptionsDialog(QWidget * pParent , const char * name): QDialog(pParent, name, true)
    , mCompressionType(CQSBMLSaveOptionsDialog::NONE)
    , mSaveCOPASIMIRIAM(true)
    , mpLayout(new QVBoxLayout(this))
    , mpVersionBox(new QComboBox(false, this))
    , mpMIRIAMCheckbox(new QCheckBox("Save COPASI MIRIAM annotation", this))
    , mpCompressionGroup(new QButtonGroup(2, Qt::Horizontal, "Compression", this))
    , mpOKButton(new QPushButton("Export", this))
    , mpCancelButton(new QPushButton("Cancel", this))
{
  // add the widgets to the layout
  std::vector<std::pair<unsigned C_INT32, unsigned C_INT32> > levelsAndVersions;
  levelsAndVersions.push_back(std::pair<unsigned C_INT32, unsigned C_INT32>(1, 2));
  levelsAndVersions.push_back(std::pair<unsigned C_INT32, unsigned C_INT32>(2, 1));
  levelsAndVersions.push_back(std::pair<unsigned C_INT32, unsigned C_INT32>(2, 2));
  levelsAndVersions.push_back(std::pair<unsigned C_INT32, unsigned C_INT32>(2, 3));
  this->setLevelsAndVersions(levelsAndVersions);
  this->setLevelAndVersion(std::pair<unsigned C_INT32, unsigned C_INT32>(2, 3));
  // that the widget has a fixed size determined by it's elements
  this->mpLayout->setResizeMode(QLayout::Fixed);
  this->mpLayout->addSpacing(5);
  QHBoxLayout* pLayout = new QHBoxLayout();
  this->mpLayout->addLayout(pLayout);
  pLayout->addSpacing(5);
  pLayout->addWidget(new QLabel("SBML Version:", this));
  pLayout->addSpacing(5);
  pLayout->addWidget(this->mpVersionBox);
  pLayout->addSpacing(5);
  // the compression feature is disabled for now since the libsbml we use
  // does not have the dependencies
  //this->mpLayout->addWidget(this->mpCompressionGroup);
  // add the buttons to the compression group
  this->mpCompressionGroup->setRadioButtonExclusive(true);
  new QRadioButton("none", this->mpCompressionGroup);
  new QRadioButton("zip", this->mpCompressionGroup);
  new QRadioButton("gzip", this->mpCompressionGroup);
  new QRadioButton("bzip2", this->mpCompressionGroup);
  this->mpCompressionGroup->setButton(this->mCompressionType);
  this->mpCompressionGroup->hide();
  pLayout = new QHBoxLayout();
  this->mpLayout->addLayout(pLayout);
  QToolTip::add(this->mpMIRIAMCheckbox, "Export additional MIRIAM annotation in the COPASI namespace.");
  this->mpMIRIAMCheckbox->setChecked(this->mSaveCOPASIMIRIAM);
  pLayout->addStretch();
  pLayout->addWidget(this->mpMIRIAMCheckbox);
  pLayout->addStretch();
  pLayout = new QHBoxLayout();
  this->mpLayout->addLayout(pLayout);
  // make OK button the default
  // add some space between the buttons and before and after them
  pLayout->addStretch();
  pLayout->addWidget(this->mpOKButton);
  pLayout->addStretch();
  pLayout->addWidget(this->mpCancelButton);
  pLayout->addStretch();
  this->mpOKButton->setDefault(true);
  // set the tab order
  this->setTabOrder(this->mpVersionBox, this->mpCompressionGroup);
  this->setTabOrder(this->mpCompressionGroup, this->mpMIRIAMCheckbox);
  this->setTabOrder(this->mpMIRIAMCheckbox, this->mpOKButton);
  this->setTabOrder(this->mpOKButton, this->mpCancelButton);

  // connect the signals and slots
  connect(this->mpMIRIAMCheckbox, SIGNAL(toggled(bool)), this, SLOT(miriam_toggled(bool)));
  connect(this->mpCompressionGroup, SIGNAL(clicked(int)), this, SLOT(compression_clicked(int)));
  connect(this->mpOKButton, SIGNAL(clicked()), this, SLOT(ok_clicked()));
  connect(this->mpCancelButton, SIGNAL(clicked()), this, SLOT(cancel_clicked()));
}

/**
 * Returns the selected SBML level.
 * This method just calls the corresponding method in
 * CQSBMLVersionFrame.
 */
unsigned C_INT32 CQSBMLSaveOptionsDialog::getLevel() const
  {
    unsigned int selectedIndex = this->mpVersionBox->currentItem();
    assert(selectedIndex < this->mLevelsAndVersions.size());
    std::pair<unsigned C_INT32, unsigned C_INT32> pair = this->mLevelsAndVersions[this->mLevelsAndVersions.size() - 1 - selectedIndex];
    return pair.first;
  }

/**
 * Returns the selected SBML versions.
 * This method just calls the corresponding method in
 * CQSBMLVersionFrame.
 */
unsigned C_INT32 CQSBMLSaveOptionsDialog::getVersion() const
  {
    unsigned int selectedIndex = this->mpVersionBox->currentItem();
    assert(selectedIndex < this->mLevelsAndVersions.size());
    std::pair<unsigned C_INT32, unsigned C_INT32> pair = this->mLevelsAndVersions[this->mLevelsAndVersions.size() - 1 - selectedIndex];
    return pair.second;
  }

/**
 * Returns which kind of compression should be used when saving the
 * SBML file.
 */
CQSBMLSaveOptionsDialog::COMPRESSION_TYPE CQSBMLSaveOptionsDialog::getCompressionType() const
  {
    return this->mCompressionType;
  }

/**
 * Sets the compression type for the SBML file.
 * The default is to use no compression.
 */
void CQSBMLSaveOptionsDialog::setCompressionType(CQSBMLSaveOptionsDialog::COMPRESSION_TYPE type)
{
  this->mCompressionType = type;
  // set the corresponding button
  this->mpCompressionGroup->setButton(type);
}

/**
 * Returns whether the COPASI MIRIAM annotation should be saved.
 */
bool CQSBMLSaveOptionsDialog::isSetSaveCOPASIMIRIAM() const
  {
    return this->mSaveCOPASIMIRIAM;
  }

/**
 * Sets whether the COPASI MIRIAM annotation should be saved.
 * The default is to save it.
 */
void CQSBMLSaveOptionsDialog::setSaveCOPASIMIRIAM(bool save)
{
  this->mSaveCOPASIMIRIAM = save;
  // update the checkbox
  this->mpMIRIAMCheckbox->setChecked(save);
}

// slot if the compression type changes
void CQSBMLSaveOptionsDialog::compression_clicked(int type)
{
  this->mCompressionType = (CQSBMLSaveOptionsDialog::COMPRESSION_TYPE)type;
}

// slot if saving COPASI MIRIAM is changed
void CQSBMLSaveOptionsDialog::miriam_toggled(bool checked)
{
  this->mSaveCOPASIMIRIAM = checked;
}

// slot if OK button is clicked
void CQSBMLSaveOptionsDialog::ok_clicked()
{
  this->accept();
}

// slot if cancel button is clicked
void CQSBMLSaveOptionsDialog::cancel_clicked()
{
  this->reject();
}

void CQSBMLSaveOptionsDialog::setLevelsAndVersions(const std::vector<std::pair<unsigned C_INT32, unsigned C_INT32> >& levelsAndVersions)
{
  this->mLevelsAndVersions = levelsAndVersions;
  // clear the combo box and add the new elements
  this->mpVersionBox->clear();
  // insert the items in reverse order
  std::vector<std::pair<unsigned C_INT32, unsigned C_INT32> >::reverse_iterator it = this->mLevelsAndVersions.rbegin(), endit = this->mLevelsAndVersions.rend();
  QString s;
  while (it != endit)
    {
      s = QString("Level %1 Version %2").arg(it->first).arg(it->second);
      this->mpVersionBox->insertItem(s);
      ++it;
    }
  // make the first item the current item
  if (!this->mLevelsAndVersions.empty())
    {
      this->mpVersionBox->setCurrentItem(0);
    }
}

void CQSBMLSaveOptionsDialog::setLevelAndVersion(const std::pair<unsigned C_INT32, unsigned C_INT32>& levelAndVersion)
{
  unsigned int i, iMax = this->mLevelsAndVersions.size();
  while (i < iMax)
    {
      if (this->mLevelsAndVersions[i] == levelAndVersion)
        {
          break;
        }
      ++i;
    }
  if (i != iMax)
    {
      this->mpVersionBox->setCurrentItem(i);
    }
}
