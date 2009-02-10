// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQMiriamWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/10 21:40:10 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMIRIAMWIDGET_H
#define CQMIRIAMWIDGET_H

#include <QWidget>
#include <QVariant>

#include "ui_CQMiriamWidget.h"
#include "CQCreatorDM.h"
#include "CQReferenceDM.h"
#include "CQModifiedDM.h"
#include "CQDateTimeEditDelegate.h"

class CMIRIAMInfo;

class CQMiriamWidget : public CopasiWidget, public Ui::CQMiriamWidget
  {
    Q_OBJECT

  public:
    CQMiriamWidget(QWidget* parent = 0, const char* name = 0);
    ~CQMiriamWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    const CMIRIAMInfo & getMIRIAMInfo() const;
    const CQCreatorDM* getCreatorDM() const;

    void updateResourcesList();

  protected slots:
    virtual void languageChange();

  private:
    CMIRIAMInfo* mpMIRIAMInfo;
    CQCreatorDM* mpCreatorDM;
    CQReferenceDM* mpReferenceDM;
    CQModifiedDM* mpModifiedDM;
    CQDateTimeEditDelegate* mpDTEDelegate;
    QStringList mPredicates;
    QStringList mResources;
    //std::vector< QTableView * > mWidgets;
    void deleteSelectedAuthor();
    void deleteSelectedReference();
    void deleteSelectedModified();

  private slots:
    void slotBtnOKClicked();
    void slotBtnCancelClicked();
    void slotBtnDeleteClicked();
    void slotBtnNewClicked();
    void slotBtnClearClicked();
    void slotCreatedDTChanged(QDateTime newDT);
  };

#endif // CQMIRIAMWIDGET_H
