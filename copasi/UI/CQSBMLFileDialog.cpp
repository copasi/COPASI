// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSBMLFileDialog.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/11/15 21:42:24 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQSBMLFileDialog.h"
#include <qcombobox.h>
#include <qlabel.h>

CQSBMLFileDialog::CQSBMLFileDialog(QWidget * parent ,
                                   const char * name ,
                                   bool modal)
    : CopasiFileDialog(parent , name , modal)
{
  this->mSBMLVersions.push_back(std::make_pair(2, 3));
  this->mSBMLVersions.push_back(std::make_pair(2, 2));
  this->mSBMLVersions.push_back(std::make_pair(2, 1));
  this->mSBMLVersions.push_back(std::make_pair(1, 2));
  this->mSBMLVersions.push_back(std::make_pair(1, 1));
  this->mpSBMLVersionBox = new QComboBox(this);
  this->mpSBMLVersionBox->setEditable(false);
  std::vector<std::pair<unsigned C_INT32, unsigned C_INT32> >::const_iterator it = this->mSBMLVersions.begin();
  std::vector<std::pair<unsigned C_INT32, unsigned C_INT32> >::const_iterator endit = this->mSBMLVersions.end();
  while (it != endit)
    {
      this->mpSBMLVersionBox->insertItem(QString("Level %1 Version %2").arg((*it).first, (*it).second));
      ++it;
    }
  this->mpSBMLVersionBox->setCurrentItem(2);
  this->mpSBMLVersionBox->hide();
  this->mpSBMLVersionLabel = new QLabel(this, "SBML Version: ");
  this->mpSBMLVersionLabel->hide();
  this->addWidgets(this->mpSBMLVersionLabel, this->mpSBMLVersionBox, NULL);
}

std::pair<QString, std::pair<unsigned C_INT32, unsigned C_INT32> >
CQSBMLFileDialog::getOpenFileName(const QString & startWith ,
                                  const QString & filter ,
                                  const QString & caption ,
                                  QString selectedFilter)
{
  this->mpSBMLVersionLabel->show();
  this->mpSBMLVersionBox->show();
  QString filename = CopasiFileDialog::getOpenFileName(startWith, filter, caption, selectedFilter);
  this->mpSBMLVersionLabel->hide();
  this->mpSBMLVersionBox->hide();
  return std::make_pair(filename, this->mSBMLVersions.at(this->mpSBMLVersionBox->currentItem()));
}
