/* Begin CVS Header
   $Source: /home/cvs/copasi_dev/copasi/CopasiUI/CMCAResultSubwidget.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/03/02 02:21:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CMCAResultSubwidget.ui'
 **
 ** Created: Thu Feb 23 13:33:29 2006
 **      by: The User Interface Compiler ($Id: CMCAResultSubwidget.h,v 1.7 2006/03/02 02:21:43 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CMCARESULTSUBWIDGET_H
#define CMCARESULTSUBWIDGET_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QComboBox;
class QPushButton;
class QTabWidget;
class QTable;
class CMCAMethod;

class CMCAResultSubwidget : public QWidget
  {
    Q_OBJECT

  public:
    CMCAResultSubwidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CMCAResultSubwidget();

    QLabel* mTopLabel;
    QComboBox* mComboScale;
    QPushButton* mSaveButton;
    QTabWidget* mTabWidget;
    QWidget* tab;
    QTable* mTableElasticities;
    QWidget* tab_2;
    QTable* mTableFCC;
    QWidget* TabPage;
    QTable* mTableCCC;

  public slots:
    virtual void loadAll(const CMCAMethod * mcaMethod);
    virtual void loadElasticities(const CMCAMethod * mcaMethod);
    virtual void loadConcentrationCCs(const CMCAMethod * mcaMethod);
    virtual void loadFluxCCs(const CMCAMethod * mcaMethod);
    virtual void clear();

  protected:
    QVBoxLayout* CMCAResultSubwidgetLayout;
    QHBoxLayout* layout3;
    QVBoxLayout* tabLayout;
    QVBoxLayout* tabLayout_2;
    QVBoxLayout* TabPageLayout;

  protected slots:
    virtual void languageChange();

    virtual void init();
    virtual void slotSave();
    virtual void slotScaled();

  private:
    const CMCAMethod * mMCAMethod;
  };

#endif // CMCARESULTSUBWIDGET_H
