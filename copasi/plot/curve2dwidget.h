/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/curve2dwidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/05 12:54:14 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'curve2dwidget.ui'
 **
 ** Created: Wed Aug 4 15:18:54 2004
 **      by: The User Interface Compiler ($Id: curve2dwidget.h,v 1.3 2004/08/05 12:54:14 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CURVE2DWIDGET_H
#define CURVE2DWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include "CPlotSpecification.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QComboBox;

class Curve2DWidget : public QWidget
  {
    Q_OBJECT

  public:
    Curve2DWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~Curve2DWidget();

    QFrame* line;
    QLabel* textLabelTitle;
    QLineEdit* lineEditTitle;
    QLineEdit* lineEditXName;
    QLineEdit* lineEditXCN;
    QLineEdit* lineEditYName;
    QLineEdit* lineEditYCN;
    QLabel* textLabelX;
    QLabel* textLabelY;
    QComboBox* comboXAxis;
    QComboBox* comboYAxis;

    virtual bool LoadFromCurveSpec(const CPlotItem * curve);
    virtual bool SaveToCurveSpec(CPlotItem * curve) const;

  protected:
    QGridLayout* Curve2DWidgetLayout;

  protected slots:
    virtual void languageChange();
  };

#endif // CURVE2DWIDGET_H
