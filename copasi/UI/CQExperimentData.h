/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentData.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/06 22:21:02 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQExperimentData.ui'
 **
 ** Created: Sun Nov 6 11:17:14 2005
 **      by: The User Interface Compiler ($Id: CQExperimentData.h,v 1.5 2005/11/06 22:21:02 shoops Exp $)
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
    QToolButton* mpBtnLast;
    QLabel* mpLblLast;
    QCheckBox* mpCheckTab;
    QLineEdit* mpEditFirst;
    QLineEdit* mpEditHeader;
    QLabel* mpLblName;
    QLineEdit* mpEditSeparator;
    QToolButton* mpBtnFirst;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QToolButton* mpBtnHeader;
    QLineEdit* mpEditLast;
    QLabel* mpLblSeperator;
    QCheckBox* mpCheckHeader;
    QLineEdit* mpEditName;
    QLabel* mpLblFirst;
    QLabel* mpLblHeader;
    QTable* mpTable;
    QPushButton* mpBtnOK;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnCancel;

    friend class CQExperimentDataValidator;

    bool load(CExperimentSet * & pExperimentSet);

  protected:
    QSignalMapper * mpBtnMap;
    CQExperimentDataValidator * mpValidatorHeader;
    CQExperimentDataValidator * mpValidatorLast;
    CExperiment * mpExperiment;
    CExperimentFileInfo * mpFileInfo;
    CExperimentSet * mpExperimentSet;
    CExperimentSet * mpExperimentSetCopy;
    std::map<std::string, std::string> mKeyMap;
    std::map<std::string, std::string> mFileMap;
    CQExperimentDataValidator * mpValidatorFirst;
    unsigned int mShown;
    CQExperimentDataValidator * mpValidatorName;
    QSignalMapper * mpComboMap;

    bool loadExperiment(const CExperiment * pExperiment);
    bool saveExperiment(CExperiment * pExperiment);
    void syncExperiments();
    void loadTable(const bool & guess);

    QVBoxLayout* CQExperimentDataLayout;
    QGridLayout* mpLayoutFile;
    QGridLayout* mpLayoutExperiment;
    QVBoxLayout* mpBtnGroupLayout;
    QHBoxLayout* mpLayoutButton;

  protected slots:
    virtual void languageChange();

    void slotRevert();
    void slotFirst();
    void slotLast();
    void slotHeader();
    void slotExprimentType(bool);
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

  private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;

    void init();
    void destroy();
  };

#endif // CQEXPERIMENTDATA_H
