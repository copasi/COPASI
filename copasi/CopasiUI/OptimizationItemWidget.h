/****************************************************************************
 ** Form interface generated from reading ui file '.\OptimizationItemWidget.ui'
 **
 ** Created: Mon Sep 29 00:08:08 2003
 **      by: The User Interface Compiler ($Id: OptimizationItemWidget.h,v 1.3 2003/10/04 18:55:20 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

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

class OptimizationItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    OptimizationItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~OptimizationItemWidget();

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

    std::string getItemUpperLimit();
    std::string getItemLowerLimit();

    setItemUpperLimit(std::string strUpperLimit);
    setItemLowerLimit(std::string strLowerLimit);

    CCopasiObject* getCopasiObject();
    void setCopasiObjecPtr (CCopasiObject* sourceObject);

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
