/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingItemWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 18:41:23 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Fri Oct 7 14:23:54 2005
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.h,v 1.2 2005/10/07 18:41:23 shoops Exp $)
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
class QComboBox;
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
    QCheckBox* mpLowerInf;
    QLineEdit* mpEditLower;
    QToolButton* mpBtnLowerEdit;
    QLabel* mpLblUpper;
    QLineEdit* mpEditUpper;
    QToolButton* mpBtnUpperEdit;
    QCheckBox* mpUpperInf;
    QLabel* mpLblExperiments;
    QComboBox* mpBoxExperiments;
    QToolButton* mpBtnExperiments;
    QLabel* mpLblObject;
    QLineEdit* mpEditObject;
    QToolButton* mpBtnObject;

    virtual bool initFromFitItem(const CFitItem & item);
    virtual bool saveToFitItem(CFitProblem * pg) const;

  protected:
    CCopasiObjectName* mpObjectCN;
    const CCopasiObject* mpLowerObject;
    const CCopasiObject* mpUpperObject;
    CCopasiObject* mpObject;

    QGridLayout* CQFittingItemWidgetLayout;
    QSpacerItem* mpSpacerLeft;
    QHBoxLayout* mpLayoutLower;
    QHBoxLayout* mpLayoutUpper;
    QHBoxLayout* mpLayoutExperiments;
    QHBoxLayout* mpLayoutObject;

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
