/****************************************************************************
 ** Form interface generated from reading ui file '.\ScanItemWidget.ui'
 **
 ** Created: Thu May 22 10:43:21 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef SCANITEMWIDGET_H
#define SCANITEMWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QCheckBox;
class QLabel;
class QLineEdit;
class QRadioButton;

class ScanItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    ScanItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanItemWidget();

    QCheckBox* bMaster;
    QCheckBox* bLogarithmic;
    QButtonGroup* RandomGroup;
    QRadioButton* mUniformRadio;
    QRadioButton* mPosNormalRadio;
    QRadioButton* mNormalRadio;
    QRadioButton* bRegularGrid;
    QLabel* TextLabel3;
    QLabel* TextLabel2;
    QLabel* TextLabel1;
    QLineEdit* nMin;
    QLineEdit* nMax;
    QLineEdit* nDensity;

  protected:
    QGridLayout* ScanItemWidgetLayout;
    QVBoxLayout* Layout13;
    QGridLayout* Layout4;
    QGridLayout* Layout34;
    QGridLayout* Layout7;
    QVBoxLayout* Layout33;
  };

#endif // SCANITEMWIDGET_H
