/****************************************************************************
 ** Form interface generated from reading ui file 'curvegroupbox.ui'
 **
 ** Created: Wed Oct 1 13:58:12 2003
 **      by: The User Interface Compiler ($Id: curvegroupbox.h,v 1.1 2003/10/14 15:06:16 huwenjun Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CURVEGROUPBOX_H
#define CURVEGROUPBOX_H

//#include <qvariant.h>
//#include <qwidget.h>
#include <qgroupbox.h>

class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QComboBox;
//class QFrame;
class QLabel;
class QLineEdit;
class QRadioButton;

class CurveGroupBox : public QGroupBox
  {
    Q_OBJECT

  public:
    CurveGroupBox(QWidget* parent = 0, const char* name = 0);
    ~CurveGroupBox();

    QLabel* curveTitleLabel;
    QLabel* xLabel;
    QLabel* textLabel5;
    QLabel* yLabel;
    QLabel* textLabel5_2;
    QLineEdit* curveTitleLineEdit;
    QComboBox* xComboBox;
    QLineEdit* xTitleLineEdit;
    QComboBox* yComboBox;
    QLineEdit* yTitleLineEdit;
    QButtonGroup* buttonGroup2;
    QRadioButton* xBtmRadioButton;
    QRadioButton* xTopRadioButton;
    QButtonGroup* buttonGroup2_2;
    QRadioButton* yLeftRadioButton;
    QRadioButton* yRightRadioButton;

  protected:
    QVBoxLayout* CurveGroupBoxLayout;
    QVBoxLayout* layout26;
    QHBoxLayout* layout25;
    QVBoxLayout* layout24;
    QVBoxLayout* layout23;
    QHBoxLayout* layout22;
    QVBoxLayout* layout34;
    QVBoxLayout* layout33;
    QGridLayout* buttonGroup2Layout;
    QVBoxLayout* layout15;
    QGridLayout* buttonGroup2_2Layout;
    QVBoxLayout* layout15_2;

  protected slots:
    virtual void languageChange();
  };

#endif // CURVEGROUPBOX_H
