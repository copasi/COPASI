/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/12/09 15:49:53 $
   End CVS Header */

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

    virtual void populateTree(CModel * model);
    virtual std::vector<CCopasiObject*>* getTreeSelection();

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
    QListViewItem* expertSubtree;
    std::map<QListViewItem*, CCopasiObject*> treeItems;

    virtual bool treeHasSelection();
    virtual bool isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites);
    virtual void clearTree();
    virtual QListViewItem * findListViewItem(const CCopasiObject * object);
    virtual void selectObjects(std::vector<CCopasiObject *> * objects);
  };

#endif
