/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingItemWidget.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/08 18:50:55 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Tue Mar 7 21:46:59 2006
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.h,v 1.9 2006/03/08 18:50:55 shoops Exp $)
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
class QPushButton;
class QCheckBox;
class QLabel;
class QToolButton;
class QComboBox;
class QLineEdit;
class CCopasiSelectionDialog;
class COptItem;
class CFitItem;
class CCopasiObject;
class CCopasiObjectName;
class CQValidatorBound;
class CQValidatorNotEmpty;
class QColor;
class CExperimentSet;
class CCopasiParameterGroup;

class CQFittingItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQFittingItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQFittingItemWidget();

    QTable* mpTable;
    QPushButton* mpBtnPerExperiment;
    QCheckBox* mpCheckLowerInf;
    QLabel* mpLblExperiments;
    QToolButton* mpBtnNew;
    QToolButton* mpBtnDown;
    QToolButton* mpBtnDel;
    QToolButton* mpBtnCopy;
    QToolButton* mpBtnUp;
    QCheckBox* mpCheckAll;
    QComboBox* mpBoxExperiments;
    QToolButton* mpBtnExperiments;
    QLabel* mpLblObject;
    QLabel* mpLblUpper;
    QCheckBox* mpCheckUpperInf;
    QLabel* mpLblLower;
    QLineEdit* mpEditLower;
    QToolButton* mpBtnLowerEdit;
    QLineEdit* mpEditUpper;
    QToolButton* mpBtnUpperEdit;
    QLineEdit* mpEditObject;
    QToolButton* mpBtnObject;

    virtual bool load(CCopasiParameterGroup * pItems, const std::map<std::string, std::string> * pKeyMap);
    virtual bool save(const std::map<std::string, std::string> * pKeyMap);
    void enableFitItem(const bool & enable);
    void setExperimentSet(const CExperimentSet * & pExperimentSet);

  signals:
    void numberChanged(int);

  protected:
    CCopasiParameterGroup * mpItems;
    const CExperimentSet ** mppSet;
    COptItem * mpItem;
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
    bool mIsFitItem;
    std::vector< COptItem * > * mpItemsCopy;

    QVBoxLayout* CQFittingItemWidgetLayout;
    QGridLayout* mpLayout;
    QSpacerItem* mpSpacer1;
    QSpacerItem* mpSpacerLeft;
    QSpacerItem* mpSpacer2;
    QSpacerItem* mpSpacer3;
    QHBoxLayout* mpLayoutExperiments;
    QHBoxLayout* mpLayoutLower;
    QHBoxLayout* mpLayoutUpper;
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
    bool loadItem(COptItem * pItem);
    void saveItem();
    void setTableText(const int & row, const COptItem * pItem);

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
    void slotItemChanged(int row, int col);
  };

#endif // CQFITTINGITEMWIDGET_H
