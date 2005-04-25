/* Begin CVS Header
   $Source: /home/cvs/copasi_dev/cvs_admin/c++style,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/05 18:38:04 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQProgressItem.ui'
 **
 ** Created: Thu Apr 21 13:02:55 2005
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
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
