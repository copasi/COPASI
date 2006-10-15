/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportDefinition.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQReportDefinition.ui'
 **
 ** Created: Fri Dec 23 12:49:03 2005
 **      by: The User Interface Compiler ($Id: CQReportDefinition.h,v 1.8 2006/10/15 06:57:33 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQREPORTDEFINITION_H
#define CQREPORTDEFINITION_H

#include <qvariant.h>
#include <qlistbox.h>
#include "CopasiUI/copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QTextEdit;
class QLineEdit;
class QComboBox;
class QCheckBox;
class QLabel;
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
    QTextEdit* mpCommentEdit;
    QLineEdit* mpName;
    QComboBox* mpTaskBox;
    QLineEdit* mpSeparator;
    QCheckBox* mpTabCheck;
    QLineEdit* mpPrecision;
    QLabel* mpPrecisionLabel;
    QLabel* mpTaskLabel;
    QLabel* mpSeparatorLabel;
    QLabel* mpNameLabel;
    QLabel* mpCommentLabel;
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

    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

  protected:
    QVBoxLayout* CQReportDefinitionLayout;
    QGridLayout* mpReportFrameLayout;
    QHBoxLayout* mpSeparatorLayout;
    QHBoxLayout* mpEditListsFrameLayout;
    QVBoxLayout* mpEditBtnLayout;
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
    void nameChanged(const QString & string);
    void taskChanged(const QString & string);
    void commentChanged();
    void separatorChanged(const QString & string);
    void precisionChanged(const QString & string);
    void chkTabClicked();
    void btnAdvancedClicked();
    void btnItemClicked();
    void btnSeparatorClicked();
    void btnTextClicked();
    void btnDeleteClicked();
    void btnUpClicked();
    void btnDownClicked();
    void chkTitleClicked();
    void btnDeleteReportClicked();
    void btnNewReportClicked();
    void btnRevertClicked();
    void btnCommitClicked();
  };

#endif // CQREPORTDEFINITION_H
