/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CCopasiSimpleSelectionTree.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:40 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SimpleSelectionTree_H__
#define SimpleSelectionTree_H__

#include "qlistview.h"
#include <vector>
#include <map>
#include <string>
#include "utilities/CCopasiVector.h"

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
    QListViewItem* reactionParameterSubtree;
    QListViewItem* timeSubtree;
    QListViewItem* particleFluxSubtree;
    QListViewItem* transientConcentrationSubtree;
    QListViewItem* transientParticleNumberSubtree;
    QListViewItem* initialConcentrationSubtree;
    QListViewItem* initialParticleNumberSubtree;
    QListViewItem* concentrationFluxSubtree;
    QListViewItem* reactionSubtree;
    QListViewItem* metaboliteSubtree;
    QListViewItem* modelValueSubtree;
    QListViewItem* valueSubtree;
    QListViewItem* initialValueSubtree;
    QListViewItem* compartmentSubtree;
    QListViewItem* volumeSubtree;
    QListViewItem* initialVolumeSubtree;
    QListViewItem* expertSubtree;
#ifdef COPASI_DEBUG
    QListViewItem* matrixSubtree;
#endif //COPASI_DEBUG
    std::map<QListViewItem*, CCopasiObject*> treeItems;
    std::vector<CCopasiObject*>* mpOutputVector;

    virtual bool treeHasSelection();
    virtual bool isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites);
    //virtual void clearTree();
    virtual QListViewItem * findListViewItem(const CCopasiObject * object);
    virtual void selectObjects(std::vector<CCopasiObject *> * objects);
    virtual std::vector<CCopasiObject*>* getTreeSelection();
  };

#endif
