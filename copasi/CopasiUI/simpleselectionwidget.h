/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/simpleselectionwidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/08 09:00:57 $
   End CVS Header */

/****************************************************************************
 ** Form interface generated from reading ui file 'simpleselectionwidget.ui'
 **
 ** Created: Fri Oct 8 10:36:21 2004
 **      by: The User Interface Compiler ($Id: simpleselectionwidget.h,v 1.3 2004/10/08 09:00:57 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef SIMPLESELECTIONWIDGET_H
#define SIMPLESELECTIONWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include <map>
#include <vector>
#include <string>
#include "model/CMetab.h"
#include "utilities/CCopasiVector.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QSplitter;
class QListView;
class QListViewItem;
class QListBox;
class QListBoxItem;
class QPushButton;
class CCopasiObject;
class CModel;

class SimpleSelectionWidget : public QWidget
  {
    Q_OBJECT

  public:
    SimpleSelectionWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~SimpleSelectionWidget();

    QSplitter* splitter2;
    QListView* itemTree;
    QListBox* selectedItemsBox;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* moveUpButton;
    QPushButton* moveDownButton;

    virtual void populateTree(CModel * model);
    virtual void setOutputVector(std::vector<CCopasiObject *> * outputVector);

  protected:
    QListViewItem* metaboliteSubtree;
    QListViewItem* reactionSubtree;
    QListViewItem* concentrationFluxSubtree;
    std::map<QListBoxItem*, CCopasiObject*> selectedObjects;
    std::map<QListViewItem*, CCopasiObject*> treeItems;
    std::vector<CCopasiObject*>* outputVector;
    QListViewItem* initialParticleNumberSubtree;
    QListViewItem* initialConcentrationSubtree;
    QListViewItem* transientParticleNumberSubtree;
    QListViewItem* transientConcentrationSubtree;
    QListViewItem* particleFluxSubtree;
    QListViewItem* timeSubtree;
    bool singleSelect;

    virtual void init();
    virtual bool treeHasSelection();
    virtual std::vector<CCopasiObject*>* getTreeSelection();
    virtual std::vector<CCopasiObject*>* getListSelection();
    virtual bool listHasSelection();
    virtual void destroy();
    virtual bool isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites);
    virtual void clearTree();
    virtual QListViewItem * findListViewItem(const CCopasiObject * object);
    virtual const std::vector<int>* getSelectedIndicesFromList();
    virtual void updateMoveButtons();
    virtual void updateOutputVector();
    virtual void selectObjects(std::vector<CCopasiObject *> * objects);

    QHBoxLayout* SimpleSelectionWidgetLayout;
    QHBoxLayout* layout4;
    QVBoxLayout* layout3;
    QSpacerItem* spacer4;
    QSpacerItem* spacer5;
    QSpacerItem* spacer6;

  protected slots:
    virtual void languageChange();

    virtual void addButtonClicked();
    virtual void deleteButtonClicked();
    virtual void selectionChangedInTree();
    virtual void selectionChangedInList();
    virtual void moveUpButton_clicked();
    virtual void moveDownButton_clicked();
  };

#endif // SIMPLESELECTIONWIDGET_H
