/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportDefinition.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/11 18:07:49 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQReportDefinition.ui'
 **
 ** Created: Wed May 11 14:05:34 2005
 **      by: The User Interface Compiler ($Id: CQReportDefinition.h,v 1.3 2005/05/11 18:07:49 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQREPORTDEFINITION_H
#define CQREPORTDEFINITION_H

#include <qvariant.h>
#include <qlistbox.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QTextEdit;
class QLineEdit;
class QComboBox;
class QCheckBox;
class QPushButton;
class QTabWidget;
class QListBox;
class QListBoxItem;
class CReportDefinition;

class CQReportDefinition : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQReportDefinition(QWidget* parent = 0, const char* name = 0);
    ~CQReportDefinition();

    QFrame* mpReportFrame;
    QLabel* mpSeparatorLabel;
    QLabel* mpNameLabel;
    QLabel* mpCommentLabel;
    QTextEdit* mpCommentEdit;
    QLineEdit* mpName;
    QComboBox* mpTaskBox;
    QLineEdit* mpSeparator;
    QCheckBox* mpTabCheck;
    QLabel* mpTaskLabel;
    QFrame* mpEditListsFrame;
    QPushButton* mpBtnAdvanced;
    QPushButton* mpBtnItem;
    QPushButton* mpBtnSeparator;
    QPushButton* mpBtnText;
    QPushButton* mpBtnDelete;
    QPushButton* mpBtnUp;
    QPushButton* mpBtnDown;
    QCheckBox* mpTitleCheck;
    QTabWidget* mpReportSectionTab;
    QListBox* mpTableList;
    QListBox* mpHeaderList;
    QListBox* mpBodyList;
    QListBox* mpFooterList;
    QPushButton* mpBtnCommit;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnNewReport;
    QPushButton* mpBtnDeleteReport;

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected:
    QVBoxLayout* CQReportDefinitionLayout;
    QGridLayout* mpReportFrameLayout;
    QHBoxLayout* mpEditListsFrameLayout;
    QVBoxLayout* layout2;
    QSpacerItem* mpSpacerBtnLayout;
    QHBoxLayout* mpBtnLayout;

  protected slots:
    virtual void languageChange();

  private:
    bool mAdvanced;
    bool mChanged;
    std::string mKey;
    CReportDefinition * mpReportDefinition;

    void init();
    void destroy();
    bool load();
    bool save();
    bool setAdvancedMode(const bool & advanced);

  private slots:
    void nameChanged();
    void taskChanged();
    void commentChanged();
    void separatorChanged();
    void chkTabClicked();
    void btnAdvancedClicked();
    void btnItemClicked();
    void btnSeparatorClicked();
    void btnTextClicked();
    void btnDeleteClicked();
    void btnUpClicked();
    void btnDownClicked();
    void chkTitleClicked();
    void btnCommitClicked();
    void btnRevertClicked();
    void btnNewReportClicked();
    void btnDeleteReportClicked();
  };

#endif // CQREPORTDEFINITION_H
