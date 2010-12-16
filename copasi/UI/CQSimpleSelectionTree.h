// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSimpleSelectionTree.h,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/12/16 15:27:50 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SimpleSelectionTree_H__
#define SimpleSelectionTree_H__

#include <QTreeWidget>
#include <vector>
#include <map>
#include <string>

template <class CType> class CCopasiVector;

class CCopasiObject;
class QTreeWidgetItem;
class QWidget;
class CModel;
class CMetab;

class CQSimpleSelectionTree: public QTreeWidget
{
  Q_OBJECT

public:
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
    AnyObject = 0x100,
    EventTarget = 0x200
  };

  typedef int ObjectClasses;

  CQSimpleSelectionTree(QWidget* parent);
  ~CQSimpleSelectionTree();

  void populateTree(const CModel * pModel, const ObjectClasses & classes);
  void setOutputVector(std::vector< const CCopasiObject * > * outputVector);

public slots:
  virtual void commitClicked();

protected:
  QTreeWidgetItem* mpTimeSubtree;
  QTreeWidgetItem* mpReactionSubtree;
  QTreeWidgetItem* mpReactionParameterSubtree;
  QTreeWidgetItem* mpReactionFluxConcentrationSubtree;
  QTreeWidgetItem* mpReactionFluxNumberSubtree;
  QTreeWidgetItem* mpMetaboliteSubtree;
  QTreeWidgetItem* mpMetaboliteTransientConcentrationSubtree;
  QTreeWidgetItem* mpMetaboliteTransientNumberSubtree;
  QTreeWidgetItem* mpMetaboliteInitialConcentrationSubtree;
  QTreeWidgetItem* mpMetaboliteInitialNumberSubtree;
  QTreeWidgetItem* mpMetaboliteRateConcentrationSubtree;
  QTreeWidgetItem* mpMetaboliteRateNumberSubtree;
  QTreeWidgetItem* mpModelQuantitySubtree;
  QTreeWidgetItem* mpModelQuantityTransientValueSubtree;
  QTreeWidgetItem* mpModelQuantityInitialValueSubtree;
  QTreeWidgetItem* mpModelQuantityRateSubtree;
  QTreeWidgetItem* mpCompartmentSubtree;
  QTreeWidgetItem* mpCompartmentTransientVolumeSubtree;
  QTreeWidgetItem* mpCompartmentInitialVolumeSubtree;
  QTreeWidgetItem* mpCompartmentRateSubtree;
  QTreeWidgetItem* mpExpertSubtree;
  QTreeWidgetItem* mpModelMatrixSubtree;
  QTreeWidgetItem* mpResultMatrixSubtree;
  QTreeWidgetItem* mpResultSteadyStateSubtree;
  QTreeWidgetItem* mpResultSensitivitySubtree;
  QTreeWidgetItem* mpResultMCASubtree;

  std::map< QTreeWidgetItem *, const CCopasiObject * > treeItems;
  std::vector< const CCopasiObject * > * mpOutputVector;

  bool treeHasSelection();
  bool isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites);
  QTreeWidgetItem * findListViewItem(const CCopasiObject * object);
  void selectObjects(std::vector< const CCopasiObject * > * objects);
  std::vector<const CCopasiObject * > * getTreeSelection();
  void removeEmptySubTree(QTreeWidgetItem ** ppSubTree);
protected:

public:
  static bool filter(const ObjectClasses & classes, const CCopasiObject * pObject);
};

#endif
