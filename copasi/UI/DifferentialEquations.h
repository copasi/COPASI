// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DifferentialEquations.h,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/04 21:44:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H

#include <sstream>

#include <qpushbutton.h>

#include "copasi.h"
#include "UI/copasiWidget.h"
class CModel;
class CMetab;
class CModelEntity;
class CReaction;
class QtMmlWidget;
class QScrollView;

class DifferentialEquations : public CopasiWidget
  {
    Q_OBJECT

  protected:
    //QTextBrowser *textBrowser;
    QScrollView* mScrollView;
    QtMmlWidget* mMmlWidget;

    QPushButton *btnSaveToFile;
    //QPushButton *btnOK;
    //QPushButton *btnCancel;

  public:
    DifferentialEquations(QWidget *parent, const char * name = 0, WFlags f = 0);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void saveToFileClicked();
    //virtual void slotBtnOKClicked();
    //virtual void slotBtnCancelClicked();

  private:
    void loadDifferentialEquations(CModel * model);

    std::ostringstream mml;
  };

#endif
