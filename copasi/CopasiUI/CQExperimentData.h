/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQExperimentData.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/14 16:26:03 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQExperimentData.ui'
 **
 ** Created: Fri Oct 14 12:06:34 2005
 **      by: The User Interface Compiler ($Id: CQExperimentData.h,v 1.1 2005/10/14 16:26:03 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQEXPERIMENTDATA_H
 #define CQEXPERIMENTDATA_H

#include <qvariant.h>
 #include <qpixmap.h>
 #include <qdialog.h>

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
    QToolButton* mpBtnLast;
    QToolButton* mpBtnFirst;
    QToolButton* mpBtnHeader;
    QCheckBox* mpCheckHeader;
    QLineEdit* mpEditFirst;
    QLineEdit* mpEditSeparator;
    QLineEdit* mpEditName;
    QCheckBox* mpCheckTab;
    QLineEdit* mpEditHeader;
    QLineEdit* mpEditLast;
    QLabel* mpLblLast;
    QLabel* mpLblFirst;
    QLabel* mpLblName;
    QLabel* mpLblSeperator;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QTable* mpTable;
    QPushButton* mpBtnOK;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnCancel;

    void setExperimentSet(CExperimentSet *);

  protected:
    CExperimentSet * mpExperimentSet;

    QVBoxLayout* CQExperimentDataLayout;
    QGridLayout* mpLayoutFile;
    QGridLayout* mpLayoutExperiment;
    QVBoxLayout* mpBtnGroupLayout;
    QHBoxLayout* mpLayoutButton;

  protected slots:
    virtual void languageChange();

    void slotOK();
    void slotRevert();
    void slotCancel();
    void slotFileDelete();
    void slotFirst();
    void slotLast();
    void slotHeader();
    void slotFileAdd();
    void slotExprimentType(bool);
    void slotCheckTab();
    void slotCheckHeader();
    void slotExperimentAdd();
    void slotExperimentDelete();

  private:
    QPixmap image0;
    QPixmap image1;
  };

#endif // CQEXPERIMENTDATA_H
