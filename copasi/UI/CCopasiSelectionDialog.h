// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiSelectionDialog.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/09 21:16:51 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCopasiSelectionDialog_H__
#define CCopasiSelectionDialog_H__

#include <vector>

#include <qdialog.h>

#include "UI/CCopasiSimpleSelectionTree.h"

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
    void okButton_clicked();
    void cancelButton_clicked();
    void modeButton_toggled(bool checked);

  public:
    CCopasiSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = FALSE);
    ~CCopasiSelectionDialog();
    void setOutputVector(std::vector<CCopasiObject*>* outputVector);
    void setModel(const CModel* model,
                  const CCopasiSimpleSelectionTree::SelectionFlag & flag);
    void setSingleSelection(bool singleSelectionMode);
    void enableExpertMode(bool enable);

    static
    CCopasiObject * getObjectSingle(QWidget * pParent,
                                    const CCopasiSimpleSelectionTree::SelectionFlag & flag,
                                    CCopasiObject * pCurrentObject = NULL);
    static
    std::vector<CCopasiObject *> getObjectVector(QWidget * pParent,
        const CCopasiSimpleSelectionTree::SelectionFlag & flag,
        const std::vector<CCopasiObject *> * pCurrentSelection = NULL);
  };
#endif /* SimpleSelectionDialog_H__ */
