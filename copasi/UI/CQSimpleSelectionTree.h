// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef SimpleSelectionTree_H__
#define SimpleSelectionTree_H__

#include <QTreeWidget>
#include <vector>
#include <map>
#include <string>

template <class CType> class CDataVector;

class CDataObject;
class QTreeWidgetItem;
class QWidget;
class CModel;
class CMetab;
class CDataModel;
class CExpressionGenerator;

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
  void populateTree(const std::vector< const CDataObject * > & objectList);
  void setOutputVector(std::vector< const CDataObject * > * outputVector);
  void setAllowExpressions(bool allowExpressions);
  bool treeHasSelection();
  std::vector<const CDataObject * > * getTreeSelection();

private:
  void populateInformation(CDataModel * pDataModel, const ObjectClasses & classes);

public slots:
  virtual void commitClicked();
  virtual void slotItemDoubleClicked(QTreeWidgetItem * item, int column);
  void slotExpressionOperationClicked(QAction * action);
  void slotCustomContextMenuRequested(const QPoint & pos);

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
  QTreeWidgetItem* mpResultTimeSensitivitySubtree;

#ifdef WITH_ANALYTICS
  QTreeWidgetItem* mpResultAnalyticsSubtree;
#endif // WITH_ANALYTICS

  QTreeWidgetItem* mpResultMCASubtree;
  QTreeWidgetItem* mpResultTSSASubtree;
  QTreeWidgetItem* mpResultLNASubtree;
  QTreeWidgetItem* mpResultLyapunovSubtree;
  QTreeWidgetItem* mpInformationSubtree;

  CExpressionGenerator * mpExpressionGenerator;
  bool mAllowExpressions;

  std::map< QTreeWidgetItem *, const CDataObject * > treeItems;
  std::vector< const CDataObject * > * mpOutputVector;

  bool isMetaboliteNameUnique(const std::string & name, const CDataVector<CMetab> & metabolites);
  QTreeWidgetItem * findListViewItem(const CDataObject * object);
  void selectObjects(std::vector< const CDataObject * > * objects);
  void removeEmptySubTree(QTreeWidgetItem ** ppSubTree);
  void removeAllEmptySubTrees();

protected:

public:
  static bool filter(const ObjectClasses & classes, const CDataObject * pObject);

signals:
  void selectionCommitted();
};

#endif
