/****************************************************************************
 ** $Author: Liang Xu
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
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qlineedit.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QLabel;
class ScanWidget;
class ScanCheckBox;
class ScanLineEdit;
class ScanRadioButton;
class QScrollView;

class ScanItemWidget : public QWidget
  {
    Q_OBJECT
  private:
    QScrollView* mParent;

  public:
    ScanItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanItemWidget();

    ScanCheckBox* bMaster;
    ScanCheckBox* bLogarithmic;
    QButtonGroup* RandomGroup;
    ScanRadioButton* mUniformRadio;
    ScanRadioButton* mPosNormalRadio;
    ScanRadioButton* mNormalRadio;
    ScanRadioButton* bRegularGrid;
    QLabel* TextLabel3;
    QLabel* TextLabel2;
    QLabel* TextLabel1;
    ScanLineEdit* nMin;
    ScanLineEdit* nMax;
    ScanLineEdit* nDensity;

  protected:
    QGridLayout* ScanItemWidgetLayout;
    QVBoxLayout* Layout13;
    QGridLayout* Layout4;
    QGridLayout* Layout34;
    QGridLayout* Layout7;
    QVBoxLayout* Layout33;
  public:
    virtual void mousePressEvent (QMouseEvent * e)
    {
      QWidget::mousePressEvent(e);
      //  mParent->mousePressEvent(e);
    }
  };

class ScanCheckBox : public QCheckBox
  {
    Q_OBJECT
  private:
    ScanItemWidget* mParent;
  public:
    ScanCheckBox(QWidget* parent = 0, const char* name = 0)
        : QCheckBox(parent, name)
    {
      mParent = (ScanItemWidget*)parent;
    }
    virtual void mousePressEvent (QMouseEvent * e)
    {
      QCheckBox::mousePressEvent(e);
      mParent->mousePressEvent(e);
    }
  };

class ScanRadioButton: public QRadioButton
  {
    Q_OBJECT
  private:
    ScanItemWidget* mParent;
  public:
    ScanRadioButton(QWidget* parent = 0, const char* name = 0)
        : QRadioButton(parent, name)
    {
      mParent = (ScanItemWidget*)parent;
    }
    virtual void mousePressEvent (QMouseEvent * e)
    {
      QRadioButton::mousePressEvent(e);
      mParent->mousePressEvent(e);
    }
  };

class ScanLineEdit: public QLineEdit
  {
    Q_OBJECT
  private:
    ScanItemWidget* mParent;
  public:
    ScanLineEdit(QWidget* parent = 0, const char* name = 0)
        : QLineEdit(parent, name)
    {
      mParent = (ScanItemWidget*)parent;
    }
    virtual void mousePressEvent (QMouseEvent * e)
    {
      QWidget::mousePressEvent(e);
      mParent->mousePressEvent(e);
    }
  };

#endif // SCANITEMWIDGET_H
