// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/Attic/CQMoietiesTaskResult.h,v $
//   $Revision: 1.1.2.1 $
//   $Name: Build-25 $
//   $Author: shoops $
//   $Date: 2008/02/20 20:25:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMoietiesTaskResult.ui'
 **
 ** Created: Wed Feb 20 14:47:08 2008
 **      by: The User Interface Compiler ($Id: CQMoietiesTaskResult.h,v 1.1.2.1 2008/02/20 20:25:40 shoops Exp $)
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
