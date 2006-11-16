/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExperimentData.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/11/16 15:45:13 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQExperimentData.ui'
 **
 ** Created: Thu Nov 9 09:21:41 2006
 **      by: The User Interface Compiler ($Id: CQExperimentData.h,v 1.13 2006/11/16 15:45:13 shoops Exp $)
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
class QLabel;
class QLineEdit;
class QFrame;
class QToolButton;
class QListBox;
class QListBoxItem;
class QComboBox;
class QCheckBox;
class QButtonGroup;
class QRadioButton;
class QTable;
class QPushButton;
class CExperimentSet;
class CExperimentFileInfo;
class CExperiment;
class CQExperimentDataValidator;
class QSignalMapper;
class CCrossValidationSet;

class CQExperimentData : public QDialog
  {
    Q_OBJECT

  public:
    CQExperimentData(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
    ~CQExperimentData();

    QLabel* mpLblWeight;
    QLineEdit* mpEditWeight;
    QLabel* mpLblThreshold;
    QLineEdit* mpEditThreshold;
    QFrame* mpLineCrossValidation;
    QToolButton* mpBtnFileAdd;
    QLabel* mpLblFile;
    QListBox* mpBoxFile;
    QToolButton* mpBtnExperimentDelete;
    QToolButton* mpBtnFileDelete;
    QToolButton* mpBtnExperimentAdd;
    QListBox* mpBoxExperiment;
    QLabel* mpLblExperiment;
    QLabel* mpLblHeader;
    QLineEdit* mpEditName;
    QFrame* mpLine;
    QLabel* mpLblName;
    QLineEdit* mpEditSeparator;
    QLineEdit* mpEditLast;
    QComboBox* mpBoxWeightMethod;
    QLabel* mpLblExperimentType;
    QLineEdit* mpEditHeader;
    QLabel* mpLblFirst;
    QCheckBox* mpCheckTab;
    QButtonGroup* mpBtnGroup;
    QRadioButton* mpBtnSteadystate;
    QRadioButton* mpBtnTimeCourse;
    QCheckBox* mpCheckFrom;
    QCheckBox* mpCheckTo;
    QCheckBox* mpCheckHeader;
    QLabel* mpLblSeperator;
    QLabel* mpLblCopy;
    QLabel* mpLblWeightMethod;
    QLineEdit* mpEditFirst;
    QLabel* mpLblLast;
    QTable* mpTable;
    QPushButton* mpBtnOK;
    QPushButton* mpBtnRevert;
    QPushButton* mpBtnCancel;

    friend class CQExperimentDataValidator;

    virtual bool load(CExperimentSet * pExperimentSet);

  public slots:
    virtual void loadTable(CExperiment * pExperiment, const bool & guess);

  signals:
    void experimentChanged();

  protected:
    unsigned int mOldWeightMethod;
    QPixmap mCopasi;
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
    bool mCrossValidation;

    virtual bool loadExperiment(CExperiment * pExperiment);
    bool saveExperiment(CExperiment * pExperiment, const bool & full);
    void syncExperiments();
    bool saveTable(CExperiment * pExperiment);
    bool isLikePreviousExperiment(CExperiment * pExperiment);
    void enableEdit(const bool & enable);

    QVBoxLayout* CQExperimentDataLayout;
    QHBoxLayout* mpLayoutCrossValidation;
    QGridLayout* mpLayoutFile;
    QGridLayout* layout23;
    QHBoxLayout* mpBtnGroupLayout;
    QHBoxLayout* layout16;
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

  private slots:
    void slotWeightMethod(int weightMethod);
  };

#endif // CQEXPERIMENTDATA_H
