/****************************************************************************
 ** Form interface generated from reading ui file '.\CReportDefinitionSelect.ui'
 **
 ** Created: Fri Aug 15 09:16:02 2003
 **      by: The User Interface Compiler ($Id: CReportDefinitionSelect.h,v 1.2 2003/08/18 16:08:30 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CREPORTDEFINITIONSELECT_H
#define CREPORTDEFINITIONSELECT_H

#include <qvariant.h>
#include <qDialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QFrame;
class QLabel;
class QComboBox;
class QLineEdit;
class QCheckBox;

class CReportDefinitionSelect : public QDialog
  {
    Q_OBJECT

  public:
    CReportDefinitionSelect(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CReportDefinitionSelect();

    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QFrame* frame5;
    QLabel* reportLabel;
    QComboBox* comboBox9;
    QLineEdit* targetEdit;
    QLabel* targetLabel;
    QCheckBox* appendChecked;
    QPushButton* jumpButton;

  protected:
    QGridLayout* CReportDefinitionSelectLayout;
    QGridLayout* frame5Layout;

  protected slots:
    virtual void languageChange();
  };

#endif // CREPORTDEFINITIONSELECT_H
