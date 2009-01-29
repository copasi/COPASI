// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.h,v $
//   $Revision: 1.15.4.3.4.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/29 20:25:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SimpleSelectionTree_H__
#define SimpleSelectionTree_H__

#include "qlistview.h"
#include <vector>
#include <map>
#include <string>

template <class CType> class CCopasiVector;

class CCopasiObject;
class QListViewItem;
class QWidget;
class CModel;
class CMetab;

class CCopasiSimpleSelectionTree: public QListView
  {
    Q_OBJECT

  private:
    /*
    enum SelectionFlagBase {
      BASE_DOUBLE = 0x01,
      BASE_INTEGER = 0x02,
      BASE_INITIAL = 0x04,
      BASE_TRANSIENT = 0x08,
      BASE_EXPRESSION = 0x10,
      BASE_MODEL = 0x20,
      BASE_GLOBAL = 0x40,
      BASE_TASK = 0x80,
      BASE_ARRAY = 0x100
    };
    */

  public:
    /*
    enum SelectionFlag {
      NUMERIC = BASE_DOUBLE | BASE_INTEGER,
      INITIAL_VALUE = BASE_DOUBLE | BASE_INITIAL | BASE_MODEL,
      TRANSIENT_VALUE = BASE_DOUBLE | BASE_TRANSIENT | BASE_MODEL,
      INITIAL_EXPRESSION = BASE_DOUBLE | BASE_INITIAL | BASE_EXPRESSION | BASE_MODEL,
      TRANSIENT_EXPRESSION = BASE_DOUBLE | BASE_TRANSIENT | BASE_EXPRESSION | BASE_MODEL,
      TARGET_EVENT = BASE_DOUBLE | BASE_TRANSIENT | BASE_MODEL,
      INITIAL_PARAMETER = BASE_DOUBLE | BASE_INITIAL | BASE_TASK,
      NO_RESTRICTION = -1,
      OPTIMIZATION_EXPRESSION = BASE_DOUBLE | BASE_EXPRESSION | BASE_ARRAY,
      SENSITIVITY_VARIABLE = INITIAL_VALUE | BASE_ARRAY,
      //   ARRAY = BASE_ARRAY,
      PLOT_OBJECT = BASE_ARRAY,
      REPORT_ITEM = BASE_ARRAY
    };
    */
    enum ObjectClass {
      InitialTime = 0x01,
      Parameters = 0x02,
      Variables = 0x04,
      ObservedConstants = 0x08,
      Time = 0x10,
      ObservedValues = 0x20,
      Results = 0x40,
      NumericValues = 0x80,
      AnyObject = 0x100
    };

    typedef int ObjectClasses;

    CCopasiSimpleSelectionTree(QWidget* parent, const char* name = 0, WFlags fl = 0);
    ~CCopasiSimpleSelectionTree();

    void populateTree(const CModel * pModel, const ObjectClasses & classes);
    void setOutputVector(std::vector< const CCopasiObject * > * outputVector);

  public slots:
    virtual void commitClicked();

  protected:
    QListViewItem* mpTimeSubtree;
    QListViewItem* mpReactionSubtree;
    QListViewItem* mpReactionParameterSubtree;
    QListViewItem* mpReactionFluxConcentrationSubtree;
    QListViewItem* mpReactionFluxNumberSubtree;
    QListViewItem* mpMetaboliteSubtree;
    QListViewItem* mpMetaboliteTransientConcentrationSubtree;
    QListViewItem* mpMetaboliteTransientNumberSubtree;
    QListViewItem* mpMetaboliteInitialConcentrationSubtree;
    QListViewItem* mpMetaboliteInitialNumberSubtree;
    QListViewItem* mpMetaboliteRateConcentrationSubtree;
    QListViewItem* mpMetaboliteRateNumberSubtree;
    QListViewItem* mpModelQuantitySubtree;
    QListViewItem* mpModelQuantityTransientValueSubtree;
    QListViewItem* mpModelQuantityInitialValueSubtree;
    QListViewItem* mpModelQuantityRateSubtree;
    QListViewItem* mpCompartmentSubtree;
    QListViewItem* mpCompartmentTransientVolumeSubtree;
    QListViewItem* mpCompartmentInitialVolumeSubtree;
    QListViewItem* mpCompartmentRateSubtree;
    QListViewItem* mpExpertSubtree;
    QListViewItem* mpModelMatrixSubtree;
    QListViewItem* mpResultMatrixSubtree;
    QListViewItem* mpResultSteadyStateSubtree;
    QListViewItem* mpResultSensitivitySubtree;
    QListViewItem* mpResultMCASubtree;

    std::map< QListViewItem *, const CCopasiObject * > treeItems;
    std::vector< const CCopasiObject * > * mpOutputVector;

    bool treeHasSelection();
    bool isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites);
    QListViewItem * findListViewItem(const CCopasiObject * object);
    void selectObjects(std::vector< const CCopasiObject * > * objects);
    std::vector<const CCopasiObject * > * getTreeSelection();
    void removeEmptySubTree(QListViewItem ** ppSubTree);
  protected:

  public:
    static bool filter(const ObjectClasses & classes, const CCopasiObject * pObject);
  };

#endif
