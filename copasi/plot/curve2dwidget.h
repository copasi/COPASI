/****************************************************************************
** Form interface generated from reading ui file 'curve2dwidget.ui'
**
** Created: Tue Oct 19 15:51:19 2004
**      by: The User Interface Compiler ($Id: curve2dwidget.h,v 1.1.1.1 2004/10/26 15:18:00 anuragr Exp $)
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
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;
class QComboBox;

class Curve2DWidget : public QWidget
{
    Q_OBJECT

public:
    Curve2DWidget( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
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

    virtual bool LoadFromCurveSpec( const CPlotItem * curve );
    virtual bool SaveToCurveSpec( CPlotItem * curve ) const;

protected:
    QGridLayout* Curve2DWidgetLayout;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

};

#endif // CURVE2DWIDGET_H
