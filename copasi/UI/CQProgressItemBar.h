/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemBar.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:30:38 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressItemBar.ui'
 **
 ** Created: Mon Apr 25 14:29:35 2005
 **      by: The User Interface Compiler ($Id: CQProgressItemBar.h,v 1.2 2005/04/25 18:30:38 shoops Exp $)
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
    virtual void setProgressFromDOUBLE();
    virtual void setProgressFromINT();
    virtual void setProgressFromUINT();

  protected:
    void * mpValue;
    void * mpStart;
    void * mpEnd;
    C_FLOAT64 mFactor;
    void (CQProgressItemBar::*mpProgress)();

    QHBoxLayout* mpLayout;
    QSpacerItem* mSpacer;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;
  };

#endif // CQPROGRESSITEMBAR_H
