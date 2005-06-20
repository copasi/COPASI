/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationItemWidget.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/06/20 21:09:31 $
   End CVS Header */

/********************************************************
Comment : OptimizationItemWidget for embeded widget for limit of the optimization function
 *********************************************************/

#ifndef OPTIMIZATIONITEMWIDGET_H
#define OPTIMIZATIONITEMWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include <qlineedit.h>
#include <qcheckbox.h>

#include "copasi.h"
#include "report/CCopasiObject.h"
#include "optimization/COptProblem.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class ScanLineEdit;
class QPushButton;
class QComboBox;
class ScanCheckBox;
class QFrame;
class OptimizationWidget;

class OptimizationItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    OptimizationItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~OptimizationItemWidget();
    QWidget* mpParent;

    CCopasiObject* mpObject;
    QLabel* textLabel2;
    QComboBox* comboBoxLowerOp;
    QLabel* textLabel4;
    QLineEdit* lineLower;
    QLineEdit* ObjectName;
    QPushButton* buttonParamEdit;
    QPushButton* buttonLowerEdit;
    QFrame* line3;
    QComboBox* comboBoxUpperOp;
    QFrame* line3_2;
    QLabel* textLabel3;
    QLineEdit* lineUpper;
    QPushButton* buttonUpperEdit;
    QCheckBox* checkUpperInf;
    QCheckBox* checkLowerInf;

    std::string getItemUpperLimit() const;
    std::string getItemLowerLimit() const;

    void setItemUpperLimit(std::string strUpperLimit);
    void setItemLowerLimit(std::string strLowerLimit);

    std::string getItemUpperOper();
    std::string getItemLowerOper();

    void setItemUpperOper(std::string oper);
    void setItemLowerOper(std::string oper);

    CCopasiObject* getCopasiObject();
    void setCopasiObjectPtr (CCopasiObject* sourceObject);

    virtual bool saveToOptItem(COptProblem * pg) const;

  private:

    CCopasiObject *paramObject, *lbObject, *ubObject;

  public slots:
    virtual void slotPosInfClicked();
    virtual void slotLowerEdit();
    virtual void slotNegInfClicked();
    virtual void slotUpperEdit();
    virtual void slotParamEdit();

  protected:
    QGridLayout* OptimizationItemWidgetLayout;
    QHBoxLayout* layout13;
    QHBoxLayout* layout14;

  protected slots:
    virtual void languageChange();
  };

#endif // OPTIMIZATIONITEMWIDGET_H
