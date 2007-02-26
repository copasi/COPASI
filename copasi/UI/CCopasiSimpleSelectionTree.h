// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/26 18:10:48 $
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
    CCopasiSimpleSelectionTree(QWidget* parent, const char* name = 0, WFlags fl = 0);
    ~CCopasiSimpleSelectionTree();

    virtual void populateTree(const CModel * model);
    virtual void setOutputVector(std::vector<CCopasiObject*>* outputVector);

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

    virtual bool treeHasSelection();
    virtual bool isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites);
    virtual QListViewItem * findListViewItem(const CCopasiObject * object);
    virtual void selectObjects(std::vector<CCopasiObject *> * objects);
    virtual std::vector<CCopasiObject*>* getTreeSelection();
  };

class CCopasiRuleExpressionSelectionTree: public CCopasiSimpleSelectionTree
  {
    Q_OBJECT

  public:
    CCopasiRuleExpressionSelectionTree(QWidget* parent, const char* name = 0, WFlags fl = 0);
    virtual ~CCopasiRuleExpressionSelectionTree(){};
    virtual void populateTree(const CModel * model);
  };

#endif
