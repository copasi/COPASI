/****************************************************************************
 ** Form interface generated from reading ui file '.\CReportDefinitionSelect.ui'
 **
 ** Created: Fri Aug 15 09:16:02 2003
 **      by: The User Interface Compiler ($Id: CReportDefinitionSelect.h,v 1.12 2003/09/18 23:31:18 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CREPORTDEFINITIONSELECT_H
#define CREPORTDEFINITIONSELECT_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QFrame;
class QLabel;
class QComboBox;
class QLineEdit;
class QCheckBox;
class ListViews;
class CReport;

class CReportDefinitionSelect : public QDialog
  {
    Q_OBJECT

  public:
    CReportDefinitionSelect(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CReportDefinitionSelect();
    ListViews* pListView;

    void setReport(CReport* newReport);
    CReport* mpReport;

    void cleanup();
    void loadReportDefinitionVector();

    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QFrame* frame5;
    QLabel* reportLabel;
    QComboBox* reportDefinitionNameList;
    QLineEdit* targetEdit;
    QLabel* targetLabel;
    QCheckBox* appendChecked;
    QPushButton* jumpButton;
    QPushButton* browseButton;

  protected:
    QGridLayout* CReportDefinitionSelectLayout;
    QGridLayout* frame5Layout;

  protected slots:
    virtual void languageChange();
    void cancelClicked();
    void confirmClicked();
    void jumpToReportDefinitionEdit();
    void jumpToFileBrowser();

    // defined for cancel before showing
  private:
    bool bShow;
  public slots:
    int exec();
  };

#endif // CREPORTDEFINITIONSELECT_H
