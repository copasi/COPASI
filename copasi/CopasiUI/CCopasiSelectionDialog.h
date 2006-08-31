/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CCopasiSelectionDialog.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/08/31 15:45:46 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCopasiSelectionDialog_H__
#define CCopasiSelectionDialog_H__

#include "qdialog.h"
#include <vector>

class QPushButton;
class QCheckBox;
class CCopasiSelectionWidget;
class QHBox;
class QVBoxLayout;
class QHBoxLayout;
class CCopasiObject;
class CModel;

class CCopasiSelectionDialog: public QDialog
  {
    Q_OBJECT

  protected:
    QPushButton* mpOKButton;
    QPushButton* mpCancelButton;
    QCheckBox* mpModeCheckBox;
    QHBoxLayout* mpButtonBox;
    QWidget* mpMainWidget;
    CCopasiSelectionWidget* mpSelectionWidget;
    QVBoxLayout* mpMainLayout;
    std::vector<CCopasiObject*>* mpTmpVector;
    std::vector<CCopasiObject*>* mpOutputVector;
    bool mExpertMode;
    bool mExpertModeEnabled;

  protected slots:
    virtual void okButton_clicked();
    virtual void cancelButton_clicked();
    virtual void modeButton_toggled(bool checked);

  public:
    CCopasiSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = FALSE);
    virtual ~CCopasiSelectionDialog();
    virtual void setOutputVector(std::vector<CCopasiObject*>* outputVector);
    virtual void setModel(const CModel* model);
    virtual void setSingleSelection(bool singleSelectionMode);
    virtual void enableExpertMode(bool enable);

    static CCopasiObject * getObjectSingle(QWidget * parent = 0);
    static std::vector<CCopasiObject *> getObjectVector(QWidget * parent = 0);
  };

class CCopasiRuleExpressionSelectionDialog: public CCopasiSelectionDialog
  {
    Q_OBJECT

  public:
    CCopasiRuleExpressionSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = false);
    virtual ~CCopasiRuleExpressionSelectionDialog();
    virtual void enableExpertMode(bool){};
  protected:
    virtual void modeButton_toggled(bool){};
  };

#endif /* SimpleSelectionDialog_H__ */
