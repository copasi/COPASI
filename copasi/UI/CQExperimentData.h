/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentData.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/02 15:48:31 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQExperimentData.ui'
 **
 ** Created: Mon Oct 31 11:59:05 2005
 **      by: The User Interface Compiler ($Id: CQExperimentData.h,v 1.3 2005/11/02 15:48:31 shoops Exp $)
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

    virtual bool load(CExperimentSet * & pExperimentSet);

  public slots:
    virtual void syncExperiments();

  protected:
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

    bool loadExperiment(const CExperiment * pExperiment);
    bool saveExperiment(CExperiment * pExperiment);

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

  private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;

    void init();
    void destroy();
  };

#endif // CQEXPERIMENTDATA_H
