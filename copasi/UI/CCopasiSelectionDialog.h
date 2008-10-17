// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiSelectionDialog.h,v $
//   $Revision: 1.11.4.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/17 10:38:14 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
class CArrayAnnotation;

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
    std::vector<const CCopasiObject * > * mpTmpVector;
    std::vector<const CCopasiObject * > * mpOutputVector;
    bool mExpertMode;
    bool mExpertModeEnabled;

  protected slots:
    void okButton_clicked();
    void cancelButton_clicked();
    void modeButton_toggled(bool checked);

  public:
    CCopasiSelectionDialog(QWidget * parent = 0, const char * name = 0, bool modal = false);
    ~CCopasiSelectionDialog();
    void setOutputVector(std::vector< const CCopasiObject * > * outputVector);
    void setModel(const CModel* model,
                  const CCopasiSimpleSelectionTree::SelectionFlag & flag);
    void setSingleSelection(bool singleSelectionMode);
    void enableExpertMode(bool enable);

    static
    const CCopasiObject * getObjectSingle(QWidget * pParent,
                                          const CCopasiSimpleSelectionTree::SelectionFlag & flag,
                                          const CCopasiObject * pCurrentObject = NULL);
    static
    std::vector< const CCopasiObject * > getObjectVector(QWidget * pParent,
        const CCopasiSimpleSelectionTree::SelectionFlag & flag,
        const std::vector< const CCopasiObject * > * pCurrentSelection = NULL);

    /**
     * single=true means only one object can be returned (in the first element of the return vector)
     *  when single=true and the dialog is canceled the return vector will have size=1 and contain the NULL pointer.
     *  when single=false and the dialog is canceled the return vector will be empty.
     * value=true means only objects that have a value (i.e. arrayElementReferences) are allowed.
     * otherwise also the whole array annotation may be returned.
     */
    static std::vector<const CCopasiObject*> chooseCellMatrix(const CArrayAnnotation * pArrayAnnotation,
        bool single, bool value);
  };
#endif /* SimpleSelectionDialog_H__ */
