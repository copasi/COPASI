/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemText.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:13:22 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressItemText.ui'
 **
 ** Created: Thu Apr 21 13:02:55 2005
 **      by: The User Interface Compiler ($Id: CQProgressItemText.h,v 1.1 2005/04/25 18:13:22 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQPROGRESSITEMTEXT_H
#define CQPROGRESSITEMTEXT_H

#include <qvariant.h>
#include "CQProgressItem.h"
#include "utilities/CVector.h"
#include "utilities/CProcessReport.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;

class CQProgressItemText : public CQProgressItem
  {
    Q_OBJECT

  public:
    CQProgressItemText(QWidget* parent = 0, const char* name = 0);
    ~CQProgressItemText();

    QLabel* mItemName;
    QLineEdit* mValue;

    virtual bool initFromProcessReportItem(CProcessReportItem * pItem);
    virtual bool process();
    virtual bool reset();

  protected:
    QHBoxLayout* mLabel;
    QSpacerItem* mSpacer;

  protected slots:
    virtual void languageChange();
  };

#endif // CQPROGRESSITEMTEXT_H
