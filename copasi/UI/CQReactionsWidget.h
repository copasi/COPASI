// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionsWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/03/05 17:23:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQReactionsWidget_h
#define CQReactionsWidget_h

#include "ui_CQReactionsWidget.h"
#include "CQReactionDM.h"

class CQReactionsWidget : public CopasiWidget, public Ui::CQReactionsWidget
  {
    Q_OBJECT

  public:
    CQReactionsWidget(QWidget* parent = 0, const char* name = 0);
    ~CQReactionsWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");


  private:
    CQReactionDM* mpReactionDM;
    void deleteSelectedReaction();

  protected:
    virtual void keyPressEvent (QKeyEvent* ev);

  protected slots:
    virtual void languageChange();
    virtual void slotBtnDeleteClicked();
    virtual void slotBtnNewClicked();
    virtual void slotBtnClearClicked();
    virtual void slotDoubleClicked(const QModelIndex index);
    virtual void dataChanged(const QModelIndex& topLeft,
                             const QModelIndex& bottomRight);
  };

#endif // CQReactionsWidget_h
