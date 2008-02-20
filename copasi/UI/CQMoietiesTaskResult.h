// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/15 17:42:13 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMoietiesTaskResult.ui'
 **
 ** Created: Wed Feb 20 14:47:08 2008
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.8   edited Jan 11 14:47 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQMOIETIESTASKRESULT_H
#define CQMOIETIESTASKRESULT_H

#include <qvariant.h>
#include "copasiWidget.h"
#include "CQArrayAnnotationsWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QTable;
class CQArrayAnnotationsWidget;
class QLabel;
class QPushButton;
class QSignalMapper;
class CMoietiesTask;

class CQMoietiesTaskResult : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQMoietiesTaskResult(QWidget* parent = 0, const char* name = 0);
    ~CQMoietiesTaskResult();

    QTabWidget* mpTabWidget;
    QTable* mpMoieties;
    CQArrayAnnotationsWidget* mpStoichiometry;
    CQArrayAnnotationsWidget* mpLinkMatrix;
    CQArrayAnnotationsWidget* mpReducedStoichiometry;
    QLabel* mpLblResult;
    QPushButton* mpBtnSave;

    virtual bool leave();
    virtual bool enter(const std::string &);
    void load();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    QPixmap mToolBtn;
    QSignalMapper * mpToolBtnMap;
    CMoietiesTask * mpMoietiesTask;

    QGridLayout* CQMoietiesTaskResultLayout;

  protected slots:
    virtual void languageChange();

  private:
    void init();

  private slots:
    void slotSave(void);
    void slotCreateGlobalQuantity(int row);
  };

#endif // CQMOIETIESTASKRESULT_H
