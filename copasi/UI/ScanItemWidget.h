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
#include "report/CCopasiObject.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QLabel;
class ScanCheckBox;
class ScanLineEdit;
class ScanRadioButton;
class QScrollView;
class CMethodParameterList;

class ScanItemWidget : public QWidget
  {
    Q_OBJECT
  private:
    bool isFirstWidget;
    static int labelMaxWidth;
    QString strDensityLabel;
    QString strMaxLabel;
    QString strMinLabel;
    QString strMeanLabel;
    QString strSTDLabel;

    QScrollView* mParent;
    CMethodParameterList* pParameter;
    void ResetData();
    void InitializeParameterList();

  public:
    ScanItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ScanItemWidget();

    ScanLineEdit* mMin;
    ScanLineEdit* mMax;
    ScanLineEdit* mDensity;
    ScanCheckBox* mLogarithmic;
    ScanCheckBox* mIndependent;
    ScanRadioButton* mRegularGridRadio;
    ScanRadioButton* mUniformRadio;
    ScanRadioButton* mGaussianRadio;
    ScanRadioButton* mPosGaussianRadio;

    QLabel* mMaxLabel;
    QLabel* mMinLabel;
    QLabel* mDensityLabel;
    QLabel* randomeLabel;
    QButtonGroup* buttonGroup;

  protected:
    QGridLayout* ScanItemWidgetLayout;
    QVBoxLayout* layout18;
    QHBoxLayout* layout15;
    QHBoxLayout* layout16;
    QHBoxLayout* layout17;
    QVBoxLayout* layout21;
    QGridLayout* buttonGroupLayout;
    QVBoxLayout* layout19;
    QVBoxLayout* layout20;

  public slots:
    virtual void languageChange();

    virtual void mousePressEvent (QMouseEvent * e)
    {
      QWidget::mousePressEvent(e);
    }
    void setObject(CMethodParameterList* pNewParameter)
    {
      pParameter = pNewParameter;
    }

    CMethodParameterList* getObject()
    {
      return pParameter;
    }
    void loadObject();
    void updateObject();
    void setFirstWidget(bool isFirst);

    void MaxValueChanged(const QString&);
    void MinValueChanged(const QString&);
    void DensityValueChanged(const QString&);
    void IndependentClicked();
    void LogarithmicClicked();
    void RegularGridClicked();
    void UniformClicked();
    void GaussianClicked();
    void PosGaussianClicked();
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
