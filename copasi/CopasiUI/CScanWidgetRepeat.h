/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanWidgetRepeat.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/27 20:27:39 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CScanWidgetRepeat.ui'
 **
 ** Created: Do Feb 24 23:25:10 2005
 **      by: The User Interface Compiler ($Id: CScanWidgetRepeat.h,v 1.1 2005/02/27 20:27:39 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CSCANWIDGETREPEAT_H
#define CSCANWIDGETREPEAT_H

#include <qvariant.h>
#include <qwidget.h>
#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;

class CScanWidgetRepeat : public QWidget
  {
    Q_OBJECT

  public:
    CScanWidgetRepeat(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CScanWidgetRepeat();

    QFrame* frame;
    QLabel* labelTitle;
    QLabel* labelNumber;
    QLineEdit* lineEditNumber;

    virtual bool initFromScanItem(CCopasiParameterGroup * pg);
    virtual bool saveToScanItem(CScanProblem * pg) const;

  protected:
    QVBoxLayout* CScanWidgetRepeatLayout;
    QHBoxLayout* frameLayout;
    QSpacerItem* spacer1;

  protected slots:
    virtual void languageChange();

  private:
    void init();
  };

#endif // CSCANWIDGETREPEAT_H
