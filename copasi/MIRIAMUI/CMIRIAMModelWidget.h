// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CMIRIAMModelWidget.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/24 16:25:08 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CMIRIAMMODELWIDGET
#define COPASI_CMIRIAMMODELWIDGET

#include <vector>
#include <qdatetimeedit.h>

#include "UI/CopasiTableWidget.h"
#include "UI/listviews.h"

class CModelMIRIAMInfo;
class CCreatorsWidget;
class CReferencesWidget;
class CModifiedWidget;
class QPushButton;

class CMIRIAMModelWidget : public CopasiWidget
  {
    Q_OBJECT
  public:
    CMIRIAMModelWidget(QWidget *parent, const char * name = 0, WFlags f = 0);

  private:
    std::vector<CopasiTableWidget*> mWidgets;
    bool mChanged;
    QDateTimeEdit* mpCreatedWidget;
    QHBoxLayout* mpHLayoutDT;

    QPushButton* btnOK;
    QPushButton* btnCancel;
    QPushButton* btnDelete;
    QPushButton* btnNew;
    QPushButton* btnClear;

    ListViews::ObjectType mOT;

    void updateCreatedWidget();

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnDeleteClicked();
    virtual void slotBtnNewClicked();
    virtual void slotBtnClearClicked();
    virtual void slotEnableOKAndCancel(bool e);
    virtual void slotCreatedValueChanged(const QDateTime & dt);

  public:
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
  };

#endif // COPASI_CMIRIAMMODELWIDGET
