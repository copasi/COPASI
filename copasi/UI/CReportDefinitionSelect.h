/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CReportDefinitionSelect.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:46 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 08/15
Comment : CReportDefinitionSelect to select the report definition for one task
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

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
