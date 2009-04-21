// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.h,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/21 16:20:31 $
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

#include "q3listview.h"
#include <vector>
#include <map>
#include <string>

template <class CType> class CCopasiVector;

class CCopasiObject;
class Q3ListViewItem;
class QWidget;
class CModel;
class CMetab;

class CCopasiSimpleSelectionTree: public Q3ListView
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
  enum ObjectClass
  {
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

  CCopasiSimpleSelectionTree(QWidget* parent, const char* name = 0, Qt::WFlags fl = 0);
  ~CCopasiSimpleSelectionTree();

  void populateTree(const CModel * pModel, const ObjectClasses & classes);
  void setOutputVector(std::vector< const CCopasiObject * > * outputVector);

public slots:
  virtual void commitClicked();

protected:
  Q3ListViewItem* mpTimeSubtree;
  Q3ListViewItem* mpReactionSubtree;
  Q3ListViewItem* mpReactionParameterSubtree;
  Q3ListViewItem* mpReactionFluxConcentrationSubtree;
  Q3ListViewItem* mpReactionFluxNumberSubtree;
  Q3ListViewItem* mpMetaboliteSubtree;
  Q3ListViewItem* mpMetaboliteTransientConcentrationSubtree;
  Q3ListViewItem* mpMetaboliteTransientNumberSubtree;
  Q3ListViewItem* mpMetaboliteInitialConcentrationSubtree;
  Q3ListViewItem* mpMetaboliteInitialNumberSubtree;
  Q3ListViewItem* mpMetaboliteRateConcentrationSubtree;
  Q3ListViewItem* mpMetaboliteRateNumberSubtree;
  Q3ListViewItem* mpModelQuantitySubtree;
  Q3ListViewItem* mpModelQuantityTransientValueSubtree;
  Q3ListViewItem* mpModelQuantityInitialValueSubtree;
  Q3ListViewItem* mpModelQuantityRateSubtree;
  Q3ListViewItem* mpCompartmentSubtree;
  Q3ListViewItem* mpCompartmentTransientVolumeSubtree;
  Q3ListViewItem* mpCompartmentInitialVolumeSubtree;
  Q3ListViewItem* mpCompartmentRateSubtree;
  Q3ListViewItem* mpExpertSubtree;
  Q3ListViewItem* mpModelMatrixSubtree;
  Q3ListViewItem* mpResultMatrixSubtree;
  Q3ListViewItem* mpResultSteadyStateSubtree;
  Q3ListViewItem* mpResultSensitivitySubtree;
  Q3ListViewItem* mpResultMCASubtree;

  std::map< Q3ListViewItem *, const CCopasiObject * > treeItems;
  std::vector< const CCopasiObject * > * mpOutputVector;

  bool treeHasSelection();
  bool isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites);
  Q3ListViewItem * findListViewItem(const CCopasiObject * object);
  void selectObjects(std::vector< const CCopasiObject * > * objects);
  std::vector<const CCopasiObject * > * getTreeSelection();
  void removeEmptySubTree(Q3ListViewItem ** ppSubTree);
protected:

public:
  static bool filter(const ObjectClasses & classes, const CCopasiObject * pObject);
};

#endif
