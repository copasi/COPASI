// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 01:53:45 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQMoietiesTaskResult.ui'
 **
 ** Created: Fri Jun 27 13:46:42 2008
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
class QLabel;
class QTabWidget;
class QTable;
class CQArrayAnnotationsWidget;
class QPushButton;
class QSignalMapper;
class CMoietiesTask;

class CQMoietiesTaskResult : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQMoietiesTaskResult(QWidget* parent = 0, const char* name = 0);
    ~CQMoietiesTaskResult();

    QLabel* mpLblResult;
    QTabWidget* mpTabWidget;
    QTable* mpMoieties;
    CQArrayAnnotationsWidget* mpStoichiometry;
    CQArrayAnnotationsWidget* mpLinkMatrix;
    CQArrayAnnotationsWidget* mpReducedStoichiometry;
    QPushButton* mpBtnSave;
    QPushButton* mpBtnPrintAsImage;

    virtual bool leave();
    virtual bool enter(const std::string &);
    void load();
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  public slots:
    virtual void printAsImage();

  protected:
    QPixmap mToolBtn;
    QSignalMapper * mpToolBtnMap;
    CMoietiesTask * mpMoietiesTask;

    QVBoxLayout* CQMoietiesTaskResultLayout;
    QHBoxLayout* layout3;
    QSpacerItem* spacer3;

  protected slots:
    virtual void languageChange();

  private:
    void init();

  private slots:
    void slotSave(void);
    void slotCreateGlobalQuantity(int row);
  };

#endif // CQMOIETIESTASKRESULT_H
