/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressItem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:13:22 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressItem.ui'
 **
 ** Created: Thu Apr 21 13:02:55 2005
 **      by: The User Interface Compiler ($Id: CQProgressItem.h,v 1.1 2005/04/25 18:13:22 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQPROGRESSITEM_H
#define CQPROGRESSITEM_H

#include <qvariant.h>
#include <qwidget.h>
#include "utilities/CVector.h"
#include "utilities/CProcessReport.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;

class CQProgressItem : public QWidget
  {
    Q_OBJECT

  public:
    CQProgressItem(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQProgressItem();

    virtual bool initFromProcessReportItem(CProcessReportItem * pItem);
    virtual bool process();
    virtual bool reset();

  protected:
    CProcessReportItem * mpItem;

    QHBoxLayout* mLabel;

  protected slots:
    virtual void languageChange();
  };

#endif // CQPROGRESSITEM_H
