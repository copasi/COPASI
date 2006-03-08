/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentData.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/08 20:11:23 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQExperimentData.ui'
 **
 ** Created: Wed Mar 8 14:51:48 2006
 **      by: The User Interface Compiler ($Id: CQExperimentData.h,v 1.9 2006/03/08 20:11:23 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQEXPERIMENTDATA_H
 #define CQEXPERIMENTDATA_H

#include <qvariant.h>
 #include <qpixmap.h>
 #include <qdialog.h>
 #include <string>
 #include <map>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QToolButton;
class QLabel;
class QListBox;
class QListBoxItem;
class QCheckBox;
class QLineEdit;
class QButtonGroup;
class QRadioButton;
class QFrame;
class QTable;
class QPushButton;
class CExperimentSet;
class CExperimentFileInfo;
class CExperiment;
class CQExperimentDataValidator;
class QSignalMapper;

class CQExperimentData : public QDialog
  {
    Q_OBJECT

  public:
    CQExperimentData(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQExperimentData();

    QToolButton* mpBtnFileAdd;
    QLabel* mpLblFile;
    QListBox* mpBoxFile;
    QToolButton* mpBtnExperimentDelete;
    QToolButton* mpBtnFileDelete;
    QToolButton* mpBtnExperimentAdd;
    QListBox* mpBoxExperiment;
    QLabel* mpLblExperiment;
    QLabel* mpLblHeader;
    QCheckBox* mpCheckFrom;
    QLineEdit* mpEditLast;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QCheckBox* mpCheckTo;
    QLineEdit* mpEditSeparator;
    QLabel* mpLblFirst;
    QLineEdit* mpEditFirst;
    QLabel* mpLblName;
    QLabel* mpLblCopy;
    QLabel* mpLblExperimentType;
    QFrame* line1;
    QLabel* mpLblSeperator;
    QLabel* mpLblLast;
    QLineEdit* mpEditHeader;
    QCheckBox* mpCheckHeader;
    QCheckBox* mpCheckTab;
    QLineEdit* mpEditName;
    QTable* mpTable;
    QPushButton* mpBtnOK;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnCancel;

    friend class CQExperimentDataValidator;

    bool load(CExperimentSet * & pExperimentSet);

  public slots:
    virtual void loadTable(CExperiment * pExperiment, const bool & guess);

  signals:
    void experimentChanged();

  protected:
    QSignalMapper * mpComboMap;
    CQExperimentDataValidator * mpValidatorName;
    unsigned int mShown;
    CQExperimentDataValidator * mpValidatorFirst;
    std::map<std::string, std::string> mFileMap;
    std::map<std::string, std::string> mKeyMap;
    CExperimentSet * mpExperimentSetCopy;
    CExperimentSet * mpExperimentSet;
    CExperimentFileInfo * mpFileInfo;
    CExperiment * mpExperiment;
    CQExperimentDataValidator * mpValidatorLast;
    CQExperimentDataValidator * mpValidatorHeader;
    QSignalMapper * mpBtnMap;
    QPixmap mDots;

    virtual bool loadExperiment(CExperiment * pExperiment);
    bool saveExperiment(CExperiment * pExperiment, const bool & full);
    void syncExperiments();
    bool saveTable(CExperiment * pExperiment);
    bool isLikePreviousExperiment(CExperiment * pExperiment);
    void enableEdit(const bool & enable);

    QVBoxLayout* CQExperimentDataLayout;
    QGridLayout* mpLayoutFile;
    QGridLayout* layout4;
    QSpacerItem* mpSpacer1;
    QSpacerItem* mpSpacer3;
    QSpacerItem* mpSpacer2;
    QSpacerItem* mpSpacer4;
    QHBoxLayout* mpBtnGroupLayout;
    QHBoxLayout* mpLayoutButton;

  protected slots:
    virtual void languageChange();

    void slotRevert();
    void slotFirst();
    void slotLast();
    void slotHeader();
    void slotExprimentType(bool isSteadyState);
    void slotCheckTab(bool checked);
    void slotCheckHeader(bool checked);
    void slotExperimentAdd();
    void slotExperimentChanged(QListBoxItem * pItem);
    void slotExperimentDelete();
    void slotFileAdd();
    void slotFileChanged(QListBoxItem * pItem);
    void slotFileDelete();
    void slotCancel();
    void slotOK();
    void slotUpdateTable();
    void slotModelObject(int row);
    void slotTypeChanged(int row);
    void slotSeparator();
    void slotCheckFrom(bool checked);
    void slotCheckTo(bool checked);

  private:
    QPixmap image0;
    QPixmap image1;

    void init();
    void destroy();
  };

#endif // CQEXPERIMENTDATA_H
