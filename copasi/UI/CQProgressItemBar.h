/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemBar.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/11 13:05:30 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressItemBar.ui'
 **
 ** Created: Mon Sep 11 08:50:36 2006
 **      by: The User Interface Compiler ($Id: CQProgressItemBar.h,v 1.8 2006/09/11 13:05:30 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQPROGRESSITEMBAR_H
#define CQPROGRESSITEMBAR_H

#include <qvariant.h>
#include <qpixmap.h>
#include "CQProgressItem.h"
#include "utilities/CVector.h"
#include "utilities/CProcessReport.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QProgressBar;

class CQProgressItemBar : public CQProgressItem
  {
    Q_OBJECT

  public:
    CQProgressItemBar(QWidget* parent = 0, const char* name = 0);
    ~CQProgressItemBar();

    QLabel* mItemName;
    QProgressBar* mProgressBar;

    virtual bool initFromProcessReportItem(CProcessReportItem * pItem);
    virtual bool process();
    virtual bool reset();

  protected:
    QHBoxLayout* mpLayout;
    QSpacerItem* mSpacer;

  protected slots:
    virtual void languageChange();

  private:
    void (CQProgressItemBar::*mpSetValue)();
    C_FLOAT64 mFactor;
    CCopasiParameter::Value mEnd;
    CCopasiParameter::Value mStart;
    CCopasiParameter::Value mValue;
    C_INT32 mLastSet;
    C_INT32 mCurrentValue;

    QPixmap image0;

    virtual void setValueFromDOUBLE();
    virtual void setValueFromINT();
    virtual void setValueFromUINT();
    void destroy();
    void init();
  };

#endif // CQPROGRESSITEMBAR_H
