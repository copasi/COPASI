/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationItemWidget.h,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 16:40:23 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'OptimizationItemWidget.ui'
 **
 ** Created: Fri Oct 7 12:38:58 2005
 **      by: The User Interface Compiler ($Id: OptimizationItemWidget.h,v 1.21 2005/10/07 16:40:23 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef OPTIMIZATIONITEMWIDGET_H
 #define OPTIMIZATIONITEMWIDGET_H

#include <qvariant.h>
 #include <qwidget.h>
 #include <string>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QCheckBox;
class QLabel;
class QLineEdit;
class QToolButton;
class COptProblem;
class COptItem;
class CCopasiObject;
class CCopasiObjectName;

class OptimizationItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    OptimizationItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~OptimizationItemWidget();

    QFrame* frame;
    QCheckBox* checkLowerInf;
    QCheckBox* checkUpperInf;
    QLabel* textLower;
    QLabel* textUpper;
    QLineEdit* lineLower;
    QToolButton* buttonLowerEdit;
    QLineEdit* lineUpper;
    QToolButton* buttonUpperEdit;
    QLineEdit* lineObjectName;
    QToolButton* buttonParamEdit;
    QLabel* textParameter;

    virtual bool initFromOptItem(const COptItem & item);
    virtual bool saveToOptItem(COptProblem * pg) const;

  protected:
    CCopasiObjectName* paramObjectCN;
    const CCopasiObject* mpLowerObject;
    const CCopasiObject* mpUpperObject;
    CCopasiObject* mpObject;

    QHBoxLayout* OptimizationItemWidgetLayout;
    QGridLayout* frameLayout;
    QHBoxLayout* layoutLower;
    QHBoxLayout* layoutUpper;
    QHBoxLayout* layoutParameter;

  protected slots:
    virtual void languageChange();

  private:
    void init();
    virtual void setItemUpperLimit(std::string strUpperLimit);
    virtual void setItemLowerLimit(std::string strLowerLimit);
    virtual std::string getItemUpperLimit() const;
    virtual std::string getItemLowerLimit() const;
    virtual CCopasiObject * getCopasiObject();
    virtual void setCopasiObjectPtr(CCopasiObject * sourceObject);

  private slots:
    virtual void slotNegativeInfinity();
    virtual void slotPositiveInfinity();
    virtual void slotLowerEdit();
    virtual void slotUpperEdit();
    virtual void slotParamEdit();
  };

#endif // OPTIMIZATIONITEMWIDGET_H
