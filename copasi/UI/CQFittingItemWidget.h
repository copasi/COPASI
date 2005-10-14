/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingItemWidget.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/14 11:51:02 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Thu Oct 13 15:36:24 2005
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.h,v 1.6 2005/10/14 11:51:02 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGITEMWIDGET_H
 #define CQFITTINGITEMWIDGET_H

#include <qvariant.h>
 #include <qwidget.h>
 #include <string>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QCheckBox;
class QLineEdit;
class QToolButton;
class QComboBox;
class CCopasiSelectionDialog;
class COptItem;
class CFitItem;
class CCopasiObject;
class CCopasiObjectName;
class CQValidatorBound;
class CQValidatorNotEmpty;
class QColor;

class CQFittingItemWidget : public QWidget
  {
    Q_OBJECT

  public:
    CQFittingItemWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQFittingItemWidget();

    QLabel* mpLblLower;
    QCheckBox* mpLowerInf;
    QLineEdit* mpEditLower;
    QToolButton* mpBtnLowerEdit;
    QLabel* mpLblUpper;
    QLineEdit* mpEditUpper;
    QToolButton* mpBtnUpperEdit;
    QCheckBox* mpUpperInf;
    QLabel* mpLblExperiments;
    QComboBox* mpBoxExperiments;
    QToolButton* mpBtnExperiments;
    QLabel* mpLblObject;
    QLineEdit* mpEditObject;
    QToolButton* mpBtnObject;

    bool load(const CFitItem & item);
    bool save(CFitItem & item);
    CQFittingItemWidget * copy();
    void enableFitItem(const bool &);
    bool load(const COptItem &);
    bool save(COptItem & item);

  protected:
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

    bool loadCommon(const COptItem &);
    bool saveCommon(COptItem &);

    QGridLayout* CQFittingItemWidgetLayout;
    QSpacerItem* mpSpacerLeft;
    QHBoxLayout* mpLayoutLower;
    QHBoxLayout* mpLayoutUpper;
    QHBoxLayout* mpLayoutExperiments;
    QHBoxLayout* mpLayoutObject;

  protected slots:
    virtual void languageChange();

  private:
    void init();
    void destroy();

  private slots:
    void slotNegativeInfinity();
    void slotPositiveInfinity();
    void slotLowerEdit();
    void slotUpperEdit();
    void slotParamEdit();
    void slotExperiments();
  };

#endif // CQFITTINGITEMWIDGET_H
