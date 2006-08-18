/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingItemWidget.h,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/18 18:33:23 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Fri Aug 18 12:41:10 2006
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.h,v 1.17 2006/08/18 18:33:23 shoops Exp $)
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
class QPushButton;
class QComboBox;
class CCopasiSelectionDialog;
class COptItem;
class CCopasiObject;
class CCopasiObjectName;
class CQValidatorBound;
class CQValidatorNotEmpty;
class QColor;
class CExperimentSet;
class CCopasiParameterGroup;
enum ItemType {OPT_ITEM = 0, FIT_ITEM, FIT_CONSTRAINT};

class CQFittingItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQFittingItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQFittingItemWidget();

    QTable* mpTable;
    QLabel* mpLblLower;
    QCheckBox* mpCheckUpperInf;
    QToolButton* mpBtnNew;
    QLineEdit* mpEditLower;
    QToolButton* mpBtnLowerEdit;
    QToolButton* mpBtnDel;
    QLineEdit* mpEditStart;
    QToolButton* mpBtnReset;
    QLabel* mpLblExperiments;
    QToolButton* mpBtnUp;
    QLabel* mpLblUpper_2;
    QPushButton* mpBtnPerExperiment;
    QLineEdit* mpEditObject;
    QToolButton* mpBtnObject;
    QToolButton* mpBtnDown;
    QToolButton* mpBtnCopy;
    QCheckBox* mpCheckLowerInf;
    QLineEdit* mpEditUpper;
    QToolButton* mpBtnUpperEdit;
    QLabel* mpLblUpper;
    QCheckBox* mpCheckAll;
    QComboBox* mpBoxExperiments;
    QToolButton* mpBtnExperiments;
    QLabel* mpLblObject;

    virtual bool load(CCopasiParameterGroup * pItems, const std::map<std::string, std::string> * pKeyMap);
    virtual bool save(const std::map<std::string, std::string> * pKeyMap);
    void setItemType(const ItemType & type);
    void setExperimentSet(const CExperimentSet * & pExperimentSet);

  signals:
    void numberChanged(int);

  protected:
    CCopasiParameterGroup * mpItems;
    const CExperimentSet ** mppSet;
    CCopasiObjectName* mpObjectCN;
    const CCopasiObject* mpLowerObject;
    const CCopasiObject* mpUpperObject;
    CQValidatorNotEmpty * mpObjectValidator;
    CQValidatorBound * mpLowerValidator;
    CQValidatorBound * mpUpperValidator;
    bool mLowerInfChanged;
    bool mUpperInfChanged;
    QColor mSavedColor;
    QColor mChangedColor;
    ItemType mItemType;
    std::vector< COptItem * > * mpItemsCopy;
    unsigned int mCurrentRow;
    std::set< unsigned int > mSelection;

    QVBoxLayout* CQFittingItemWidgetLayout;
    QGridLayout* layout11;
    QSpacerItem* mpSpacer3;
    QSpacerItem* mpSpacerLeft;
    QSpacerItem* mpSpacer2;
    QSpacerItem* mpSpacer1;
    QHBoxLayout* mpLayoutLower;
    QHBoxLayout* mpLayoutStart;
    QHBoxLayout* mpLayoutObject;
    QHBoxLayout* mpLayoutUpper;
    QHBoxLayout* mpLayoutExperiments;

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
    void slotCheckAll(bool checked);
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
  };

#endif // CQFITTINGITEMWIDGET_H
