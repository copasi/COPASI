// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQCopasiLayoutWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/18 23:07:45 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include <qpushbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
//#include <qtable.h>

#include "copasi.h"

#include "CQCopasiLayoutWidget.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
//#include "utilities/CCopasiVector.h"

#include "model/CModel.h"

#include <qtabwidget.h>

/**
 *  Constructs a CQCopasiLayoutWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQCopasiLayoutWidget::CQCopasiLayoutWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("CQCopasiLayoutWidget");
  setCaption("CQCopasiLayoutWidget");

  mWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "CQCopasiLayoutWidgetLayout");

  // **********  Label **************
  mLabelTitle = new QLabel(this, "SensLabel");
  mLabelTitle->setText("Sensitivities");
  mLabelTitle->setAlignment(int(QLabel::AlignVCenter
                                | QLabel::AlignLeft));
  mLabelTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mWidgetLayout->addWidget(mLabelTitle, 0, 0);

  // tab widget
  mpTab = new QTabWidget(this, "TabWidget");
  mWidgetLayout->addMultiCellWidget(mpTab, 1, 2, 0, 2);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQCopasiLayoutWidget::~CQCopasiLayoutWidget()
{}

void CQCopasiLayoutWidget::loadFromBackend()
{

  const CModel* pModel = CCopasiDataModel::Global->getModel();
}

//*************************************

bool CQCopasiLayoutWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                  C_UNUSED(action), const std::string & C_UNUSED(key))
{
  /*  if (this->isShown())
      return loadFromBackend();
    else
      return true;*/
  return true;
}

bool CQCopasiLayoutWidget::leave()
{
  return true;
}

bool CQCopasiLayoutWidget::enter(const std::string & C_UNUSED(key))
{
  loadFromBackend();

  return true;
}
