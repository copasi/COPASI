/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingItemWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 16:43:28 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Fri Oct 7 11:52:16 2005
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.h,v 1.1 2005/10/07 16:43:28 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGITEMWIDGET_H
 #define CQFITTINGITEMWIDGET_H

#include <qvariant.h>
 #include <qwidget.h>
 #include <string>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QCheckBox;
class QLineEdit;
class QToolButton;
class CFitProblem;
class CFitItem;
class CCopasiObject;
class CCopasiObjectName;

class CQFittingItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQFittingItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQFittingItemWidget();

    QLabel* mpLblLower;
    QLabel* mpLblUpper;
    QLabel* mpLblObject;
    QCheckBox* mpLowerInf;
    QCheckBox* mpUpperInf;
    QLineEdit* mpEditUpper;
    QToolButton* mpBtnUpperEdit;
    QLineEdit* mpEditObject;
    QToolButton* mpBtnObject;
    QLineEdit* mpEditLower;
    QToolButton* mpBtnLowerEdit;

    virtual bool initFromFitItem(const CFitItem & item);
    virtual bool saveToFitItem(CFitProblem * pg) const;

  protected:
    CCopasiObjectName* mpObjectCN;
    const CCopasiObject* mpLowerObject;
    const CCopasiObject* mpUpperObject;
    CCopasiObject* mpObject;

    QGridLayout* CQFittingItemWidgetLayout;
    QSpacerItem* mpSpacerRight;
    QSpacerItem* mpSpacerLeft;
    QHBoxLayout* mpLayoutUpper;
    QHBoxLayout* mpLayoutObject;
    QHBoxLayout* mpLayoutLower;

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

#endif // CQFITTINGITEMWIDGET_H
