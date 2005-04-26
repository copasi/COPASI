/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemBar.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/26 14:28:19 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressItemBar.ui'
 **
 ** Created: Tue Apr 26 09:49:49 2005
 **      by: The User Interface Compiler ($Id: CQProgressItemBar.h,v 1.3 2005/04/26 14:28:19 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQPROGRESSITEMBAR_H
#define CQPROGRESSITEMBAR_H

#include <qvariant.h>
#include <qpixmap.h>
#include <C:/cygwin/home/shoops/development/copasi_dev/copasi/CopasiUI/CQProgressItem.h>
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
    void * mpEnd;
    void * mpStart;
    void * mpValue;
    C_INT32 mLastSet;
    C_INT32 mValue;

    QPixmap image0;

    virtual void setValueFromDOUBLE();
    virtual void setValueFromINT();
    virtual void setValueFromUINT();
  };

#endif // CQPROGRESSITEMBAR_H
