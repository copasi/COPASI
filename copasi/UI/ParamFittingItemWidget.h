/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ParamFittingItemWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2004/11/04 15:53:28 $
   End CVS Header */

#ifndef ParamFittingItemWidget_H
#define ParamFittingItemWidget_H

#include <qvariant.h>
#include <qwidget.h>

#include "copasi.h"
#include "report/CCopasiObject.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class ScanLineEdit;
class QPushButton;
class QComboBox;
class ScanCheckBox;
class QFrame;
class ParamFittingWidget;

class ParamFittingItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    ParamFittingItemWidget(ParamFittingWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ParamFittingItemWidget();
    ParamFittingWidget* mpParent;

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
    QGridLayout* ParamFittingItemWidgetLayout;
    QHBoxLayout* layout13;
    QHBoxLayout* layout14;

  protected slots:
    virtual void languageChange();
  };

#endif // ParamFittingItemWidget_H
