// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/09 21:16:51 $
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
      NO_RESTRICTION = -1,
      NUMERIC = 1,
      TRANSIENT = 2,
      INITIAL = 4
    };

    CCopasiSimpleSelectionTree(QWidget* parent, const char* name = 0, WFlags fl = 0);
    ~CCopasiSimpleSelectionTree();

    void populateTree(const CModel * pModel, const SelectionFlag & flag);
    void setOutputVector(std::vector<CCopasiObject*>* outputVector);

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
    QListViewItem* mpCompartmentVolumeSubtree;
    QListViewItem* mpCompartmentInitialVolumeSubtree;
    QListViewItem* mpExpertSubtree;
#ifdef COPASI_DEBUG
    QListViewItem* matrixSubtree;
#endif //COPASI_DEBUG
    std::map<QListViewItem*, CCopasiObject*> treeItems;
    std::vector<CCopasiObject*>* mpOutputVector;

    bool treeHasSelection();
    bool isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites);
    QListViewItem * findListViewItem(const CCopasiObject * object);
    void selectObjects(std::vector<CCopasiObject *> * objects);
    std::vector<CCopasiObject*>* getTreeSelection();
  };

#endif
