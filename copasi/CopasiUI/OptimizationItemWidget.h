/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationItemWidget.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: lixu1 $ 
   $Date: 2003/10/17 02:07:13 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 10/01
Comment : OptimizationItemWidget for embeded widget for limit of the optimization function
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef OPTIMIZATIONITEMWIDGET_H
#define OPTIMIZATIONITEMWIDGET_H

#include "report/CCopasiObject.h"
#include <qvariant.h>
#include <qwidget.h>

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
    OptimizationWidget* mpParent;

    QLabel* textLabel2;
    ScanLineEdit* lineLower;
    QPushButton* buttonLowerEdit;
    QComboBox* comboBoxUpperOp;
    QLabel* textLabel3;
    QComboBox* comboBoxLowerOp;
    ScanCheckBox* checkLowerInf;
    ScanLineEdit* lineUpper;
    QPushButton* buttonUpperEdit;
    QLabel* textLabel4;
    QFrame* line10;
    ScanCheckBox* checkUpperInf;
    QFrame* line11;
    ScanLineEdit* ObjectName;
    CCopasiObject* mpObject;

    // shall add a pointer to COptFunction to change its parameter simultaneously

    std::string getItemUpperLimit();
    std::string getItemLowerLimit();

    void setItemUpperLimit(std::string strUpperLimit);
    void setItemLowerLimit(std::string strLowerLimit);

    std::string getItemUpperOper();
    std::string getItemLowerOper();

    void setItemUpperOper(std::string oper);
    void setItemLowerOper(std::string oper);

    CCopasiObject* getCopasiObject();
    void setCopasiObjectPtr (CCopasiObject* sourceObject);

  public slots:
    virtual void slotPosInfClicked();
    virtual void slotLowerEdit();
    virtual void slotNegInfClicked();
    virtual void slotUpperEdit();

  protected:
    QGridLayout* OptimizationItemWidgetLayout;
    QHBoxLayout* layout13;
    QHBoxLayout* layout14;

  protected slots:
    virtual void languageChange();
  };

#endif // OPTIMIZATIONITEMWIDGET_H
