/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/curve2dwidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/01/14 17:01:39 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'curve2dwidget.ui'
 **
 ** Created: Wed Jan 14 17:53:29 2004
 **      by: The User Interface Compiler ($Id: curve2dwidget.h,v 1.1 2004/01/14 17:01:39 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CURVE2DWIDGET_H
#define CURVE2DWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include "CPlotSpec.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QFrame;
class QComboBox;
class QLineEdit;

class Curve2DWidget : public QWidget
  {
    Q_OBJECT

  public:
    Curve2DWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~Curve2DWidget();

    QLabel* textLabelTitle;
    QFrame* line;
    QComboBox* comboXAxis;
    QComboBox* comboXData;
    QLabel* textLabelX;
    QLineEdit* lineEditTitle;
    QComboBox* comboYData;
    QComboBox* comboYAxis;
    QLabel* textLabelY;

    bool LoadFromCurveSpec(const Curve2DSpec * curve, const QStringList & channels);
    bool SaveToCurveSpec(Curve2DSpec * curve) const;

  protected:
    QGridLayout* Curve2DWidgetLayout;
    QGridLayout* layout1;

  protected slots:
    virtual void languageChange();
  };

#endif // CURVE2DWIDGET_H
