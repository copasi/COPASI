/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingItemWidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/10 18:53:10 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Mon Oct 10 11:54:12 2005
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.h,v 1.3 2005/10/10 18:53:10 shoops Exp $)
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
class CCopasiSelectionDialog;
class CFitItem;
class CCopasiObject;
class CCopasiObjectName;
class CQValidatorBound;
class CQValidatorNotEmpty;

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

  protected:
    CFitItem * mpFitItem;
    CCopasiObjectName* mpObjectCN;
    const CCopasiObject* mpLowerObject;
    const CCopasiObject* mpUpperObject;
    CCopasiObject* mpObject;
    CQValidatorNotEmpty * mpObjectValidator;
    CQValidatorBound * mpLowerValidator;
    CQValidatorBound * mpUpperValidator;

    bool loadFitItem(const CFitItem * pItem);
    CFitItem * saveFitItem(CFitItem * pItem);

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
    void destroy();

  private slots:
    void slotNegativeInfinity();
    void slotPositiveInfinity();
    void slotLowerEdit();
    void slotUpperEdit();
    void slotParamEdit();
    void slotExperiments();
  };

#endif // CQFITTINGITEMWIDGET_H
