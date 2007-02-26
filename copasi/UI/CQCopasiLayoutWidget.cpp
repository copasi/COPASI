// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQCopasiLayoutWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/02/26 10:31:08 $
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

  mWidgetLayout = new QGridLayout(this, 1, 2, 11, 6, "CQCopasiLayoutWidgetLayout");

  // **********  Label **************
  mLabelTitle = new QLabel(this, "ShowNetLabel");
  mLabelTitle->setText("Reaction network");
  mLabelTitle->setAlignment(int(QLabel::AlignVCenter
                                | QLabel::AlignLeft));
  mLabelTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mWidgetLayout->addWidget(mLabelTitle, 0, 0);

  // ********** Button ***************

  mShowNetworkButton = new QPushButton("show", this);
  mDisplayNetwork = new QAction("displayNetwork",
                                "Show reaction network",
                                CTRL + Key_D,
                                this);
  //mShowNetworkButton->setStatusTip("Show reaction network as graph");
  connect(mShowNetworkButton, SIGNAL(clicked()), this, SLOT(displayNetworkWidget()));
  mWidgetLayout->addWidget(mShowNetworkButton, 0, 1);

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

void CQCopasiLayoutWidget::displayNetworkWidget()
{
  //QApplication app(argc,argv);
  //mWin(this, "Reaction Network");
  pWin = new CQLayoutMainWindow(this, "Reaction Network");
  //mWin((QWidget *)this,"Reaction Network");
  //app.setMainWidget(&gui);
  pWin->resize(400, 230);
  pWin->show();
}

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
