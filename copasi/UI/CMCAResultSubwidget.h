// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CMCAResultSubwidget.h,v $
//   $Revision: 1.9.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/04/16 14:39:19 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CMCAResultSubwidget.ui'
 **
 ** Created: Fri Apr 13 12:53:44 2007
 **      by: The User Interface Compiler ($Id: CMCAResultSubwidget.h,v 1.9.2.1 2007/04/16 14:39:19 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CMCARESULTSUBWIDGET_H
#define CMCARESULTSUBWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class CQArrayAnnotationsWidget;
class QLabel;
class QComboBox;
class QPushButton;
class QTabWidget;
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
    CQArrayAnnotationsWidget* mpArrayElasticities;
    QWidget* tab_2;
    CQArrayAnnotationsWidget* mpArrayFCC;
    QWidget* TabPage;
    CQArrayAnnotationsWidget* mpArrayCCC;

    virtual void loadAll(const CMCAMethod * mcaMethod);
    virtual void loadElasticities(const CMCAMethod * mcaMethod);
    virtual void loadConcentrationCCs(const CMCAMethod * mcaMethod);
    virtual void loadFluxCCs(const CMCAMethod * mcaMethod);
    virtual void clear();

  protected:
    virtual void init();

    QVBoxLayout* CMCAResultSubwidgetLayout;
    QHBoxLayout* layout3;
    QHBoxLayout* tabLayout;
    QGridLayout* tabLayout_2;
    QGridLayout* TabPageLayout;

  protected slots:
    virtual void languageChange();

    virtual void slotSave();
    virtual void slotScaled();

  private:
    const CMCAMethod * mMCAMethod;

    QPixmap image0;
  };

#endif // CMCARESULTSUBWIDGET_H
