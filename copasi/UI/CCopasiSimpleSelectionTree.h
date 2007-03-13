// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/13 19:56:56 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

  public:
    enum SelectionFlag {
      DOUBLE = 0x01,
      INTEGER = 0x02,
      NUMERIC = DOUBLE | INTEGER,
      INITIAL = 0x04,
      INITIAL_VALUE = DOUBLE | INITIAL,
      TRANSIENT = 0x08,
      TRANSIENT_VALUE = DOUBLE | TRANSIENT,
      EXPRESSION = 0x10,
      INITIAL_EXPRESSION = DOUBLE | INITIAL | EXPRESSION,
      TRANSIENT_EXPRESSION = DOUBLE | TRANSIENT | EXPRESSION,
      NO_RESTRICTION = -1
    };

    CCopasiSimpleSelectionTree(QWidget* parent, const char* name = 0, WFlags fl = 0);
    ~CCopasiSimpleSelectionTree();

    void populateTree(const CModel * pModel, const SelectionFlag & flag);
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
#ifdef COPASI_DEBUG
    QListViewItem* matrixSubtree;
#endif //COPASI_DEBUG
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
    static bool filter(const SelectionFlag & flag, const CCopasiObject * pObject);
  };

#endif
