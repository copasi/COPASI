/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingItemWidget.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/28 15:38:20 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'CQFittingItemWidget.ui'
 **
 ** Created: Wed Oct 26 13:39:24 2005
 **      by: The User Interface Compiler ($Id: CQFittingItemWidget.h,v 1.7 2005/10/28 15:38:20 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef CQFITTINGITEMWIDGET_H
 #define CQFITTINGITEMWIDGET_H

#include <qvariant.h>
 #include <qpixmap.h>
 #include <qwidget.h>
 #include <string>
 #include <map>

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

    CQFittingItemWidget * copy();
    bool load(const CFitItem & item);
    bool load(const COptItem & item);
    bool save(CFitItem & item);
    bool save(COptItem & item);
    void enableFitItem(const bool & enable);
    bool update(const std::map<std::string, std::string> & keymap);

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

    bool loadCommon(const COptItem & item);
    bool saveCommon(COptItem & item);

    QGridLayout* CQFittingItemWidgetLayout;
    QSpacerItem* mpSpacerLeft;
    QHBoxLayout* mpLayoutLower;
    QHBoxLayout* mpLayoutUpper;
    QHBoxLayout* mpLayoutExperiments;
    QHBoxLayout* mpLayoutObject;

  protected slots:
    virtual void languageChange();

  private:
    QPixmap image0;

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
