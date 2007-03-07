// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingItemWidget.h,v $
//   $Revision: 1.21 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/07 20:28:20 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Wed Mar 7 15:22:38 2007
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.h,v 1.21 2007/03/07 20:28:20 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGITEMWIDGET_H
#define CQFITTINGITEMWIDGET_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>
#include "TaskWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTable;
class QLabel;
class QCheckBox;
class QToolButton;
class QLineEdit;
class QComboBox;
class QPushButton;
class CCopasiSelectionDialog;
class COptItem;
class CCopasiObject;
class CCopasiObjectName;
class CQValidatorBound;
class CQValidatorNotEmpty;
class QColor;
class CExperimentSet;
class CCopasiParameterGroup;
class CCrossValidationSet;

class CQFittingItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQFittingItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQFittingItemWidget();

    QTable* mpTable;
    QLabel* mpLblCrossValidations;
    QCheckBox* mpCheckLowerInf;
    QToolButton* mpBtnDel;
    QLabel* mpLblStart;
    QToolButton* mpBtnUp;
    QLineEdit* mpEditUpper;
    QToolButton* mpBtnUpperEdit;
    QToolButton* mpBtnNew;
    QLabel* mpLblUpper;
    QToolButton* mpBtnDown;
    QLabel* mpLblLower;
    QLabel* mpLblExperiments;
    QToolButton* mpBtnCopy;
    QLineEdit* mpEditStart;
    QToolButton* mpBtnReset;
    QLineEdit* mpEditLower;
    QToolButton* mpBtnLowerEdit;
    QCheckBox* mpCheckAll;
    QComboBox* mpBoxExperiments;
    QToolButton* mpBtnExperiments;
    QLabel* mpLblObject;
    QCheckBox* mpCheckCrossValidationsAll;
    QComboBox* mpBoxCrossValidations;
    QToolButton* mpBtnCrossValidations;
    QCheckBox* mpCheckUpperInf;
    QLineEdit* mpEditObject;
    QToolButton* mpBtnObject;
    QPushButton* mpBtnPerExperiment;

    enum ItemType {OPT_ITEM = 0, OPT_CONSTRAINT, FIT_ITEM, FIT_CONSTRAINT};

    virtual bool load(CCopasiParameterGroup * pItems, const std::map<std::string, std::string> * pExperimentMap, const std::map<std::string, std::string> * pCrossValidationMap);
    virtual bool save(const std::map<std::string, std::string> * pExperimentMap, const std::map<std::string, std::string> * pCrossValidationMap);
    void setItemType(const ItemType & type);
    void setExperimentSet(const CExperimentSet * & pExperimentSet);
    void setCrossValidationSet(const CCrossValidationSet * & pCrossValidationSet);

  signals:
    void numberChanged(int);

  protected:
    const CCrossValidationSet **mppCrossValidationSet;
    std::set< unsigned int > mSelection;
    unsigned int mCurrentRow;
    std::vector< COptItem * > * mpItemsCopy;
    ItemType mItemType;
    QColor mChangedColor;
    QColor mSavedColor;
    bool mUpperInfChanged;
    bool mLowerInfChanged;
    CQValidatorBound * mpUpperValidator;
    CQValidatorBound * mpLowerValidator;
    CQValidatorNotEmpty * mpObjectValidator;
    const CCopasiObject* mpUpperObject;
    const CCopasiObject* mpLowerObject;
    CCopasiObjectName* mpObjectCN;
    const CExperimentSet ** mppExperimentSet;
    CCopasiParameterGroup * mpItems;

    QVBoxLayout* CQFittingItemWidgetLayout;
    QGridLayout* layout18;
    QSpacerItem* mpSpacer3;
    QSpacerItem* mpSpacer2;
    QSpacerItem* mpSpacer1;
    QSpacerItem* mpSpacerLeft;
    QHBoxLayout* mpLayoutUpper;
    QHBoxLayout* mpLayoutStart;
    QHBoxLayout* mpLayoutLower;
    QHBoxLayout* mpLayoutExperiments;
    QHBoxLayout* mpLayoutCrossValidations;
    QHBoxLayout* mpLayoutObject;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;

    void init();
    void destroy();
    void setTableText(const int & row, const COptItem * pItem);
    unsigned int currentRow();
    void loadSelection();
    void saveSelection();
    void selectRow(const unsigned int & row);
    void setItemSelection(const std::set<unsigned int> & selection);

  private slots:
    void slotCheckLowerInf(bool checked);
    void slotCheckUpperInf(bool checked);
    void slotLowerEdit();
    void slotUpperEdit();
    void slotParamEdit();
    void slotExperiments();
    void slotExperimentChanged();
    void slotDelete();
    void slotCopy();
    void slotUp();
    void slotDown();
    void slotDuplicatePerExperiment();
    void slotNew();
    void slotSelectionChanged();
    void slotLowerLostFocus();
    void slotUpperLostFocus();
    void slotReset();
    void slotStartLostFocus();
    void slotCrossValidations();
    void slotCrossValidationChanged();
    void slotCheckAllCrossValidations(bool checked);
    void slotCheckAllExperiments(bool checked);
  };

#endif // CQFITTINGITEMWIDGET_H
