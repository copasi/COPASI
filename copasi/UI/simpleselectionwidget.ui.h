/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/simpleselectionwidget.ui.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/28 13:48:45 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you wish to add, delete or rename functions or slots use
 ** Qt Designer which will update this file, preserving your code. Create an
 ** init() function in place of a constructor, and a destroy() function in
 ** place of a destructor.
 *****************************************************************************/

void SimpleSelectionWidget::init()
{
  this->mSingleSelect = false;
  this->itemTree->setSortColumn(-1);
  this->itemTree->setRootIsDecorated(true);

  this->selectedItemsBox->setMinimumWidth(270);

  this->reactionSubtree = new QListViewItem(this->itemTree, "reactions");
  this->particleFluxSubtree = new QListViewItem(this->reactionSubtree, "particle fluxes");
  this->concentrationFluxSubtree = new QListViewItem(this->reactionSubtree, "concentration fluxes");

  this->metaboliteSubtree = new QListViewItem(this->itemTree, "metabolites");
  this->reactionParameterSubtree = new QListViewItem(this->reactionSubtree, "reaction parameters");
  this->transientParticleNumberSubtree = new QListViewItem(this->metaboliteSubtree, "transient particle numbers");
  this->transientConcentrationSubtree = new QListViewItem(this->metaboliteSubtree, "transient concentrations");
  this->initialParticleNumberSubtree = new QListViewItem(this->metaboliteSubtree, "initial particle numbers");
  this->initialConcentrationSubtree = new QListViewItem(this->metaboliteSubtree, "initial concentrations");

  this->timeSubtree = new QListViewItem(this->itemTree, "time");

  connect(itemTree, SIGNAL(selectionChanged()), this, SLOT(selectionChangedInTree()));
  connect(selectedItemsBox, SIGNAL(selectionChanged()), this, SLOT(selectionChangedInList()));
  connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
}

void SimpleSelectionWidget::addButtonClicked()
{
  /* add all leaves of the selected subtrees to the list of selected objects */
  /* disable those leaves in the tree */
  std::vector<CCopasiObject*>* selection = this->getTreeSelection();
  unsigned int counter;
  unsigned int maxCount = this->selectedItemsBox->count();
  for (counter = 0; counter < maxCount;++counter)
    {
      this->selectedItemsBox->setSelected(counter, false);
    }
  maxCount = selection->size();
  for (counter = 0; counter < maxCount;++counter)
    {
      CCopasiObject* object = selection->at(counter);

      const std::string name = object->getCN();
      QListViewItem* lvitem = this->findListViewItem(object);
      //const std::string name = lvitem->text(0);
      QListBoxText* item = new QListBoxText(this->selectedItemsBox, name.c_str());

      this->selectedItemsBox->setSelected(item, true);
      this->selectedObjects[item] = object;
      if (this->mSingleSelect)
        {
          lvitem->setEnabled(false);
        }
    }
  this->updateOutputVector();
  this->itemTree->clearSelection();
  this->addButton->setEnabled(false);
  delete selection;
}

void SimpleSelectionWidget::deleteButtonClicked()
{
  /* remove all selected items from the list and enable the corresponding items in the tree */
  unsigned int counter;
  unsigned int maxCount = this->selectedItemsBox->count();
  for (counter = maxCount; counter > 0;--counter)
    {
      QListBoxItem* item = this->selectedItemsBox->item(counter - 1);
      if (item->isSelected())
        {
          CCopasiObject* object = this->selectedObjects[item];
          this->selectedObjects.erase(this->selectedObjects.find(item));
          this->selectedItemsBox->removeItem(counter - 1);
          if (this->mSingleSelect)
            {
              QListViewItem* lvitem = this->findListViewItem(object);
              if (lvitem)
                {
                  lvitem->setEnabled(true);
                }
            }
        }
    }
  this->updateOutputVector();
}

void SimpleSelectionWidget::selectionChangedInTree()
{
  // if something is selected enable the add button
  if (this->treeHasSelection())
    {
      this->addButton->setEnabled(true);
    }
  else
    {
      this->addButton->setEnabled(false);
    }
}

void SimpleSelectionWidget::selectionChangedInList()
{
  // if something is selected enable the delete button
  if (this->listHasSelection())
    {
      this->deleteButton->setEnabled(true);
      this->updateMoveButtons();
    }
  else
    {
      this->deleteButton->setEnabled(false);
      this->moveUpButton->setEnabled(false);
      this->moveDownButton->setEnabled(false);
    }
}

bool SimpleSelectionWidget::treeHasSelection()
{
  bool hasSelection = false;
  QListViewItemIterator it(this-> itemTree);
  while (it.current())
    {
      if (it.current()->isSelected())
        {
          hasSelection = true;
          break;
        }
      ++it;
    }
  return hasSelection;
}

std::vector<CCopasiObject*>* SimpleSelectionWidget::getTreeSelection()
{
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  // go through the whole tree and check for selected items.
  // if the selected item has children, add all children that are leaves
  // if the selected item is a leave, add it directly
  QListViewItemIterator it(this->itemTree);
  QListViewItem* currentItem = it.current();
  while (currentItem)
    {
      if (currentItem->isSelected())
        {
          if (currentItem->childCount() == 0)
            {
              if (this->treeItems.find(currentItem) != this->treeItems.end())
                {
                  selection->push_back(this->treeItems[currentItem]);
                }
            }
          else
            {
              QListViewItemIterator it2(currentItem);
              QListViewItem* tmpItem = it2.current();
              while (tmpItem)
                {
                  if ((tmpItem->childCount() == 0) && (this->treeItems.find(tmpItem) != this->treeItems.end()))
                    {
                      selection->push_back(this->treeItems[currentItem]);
                    }
                  ++it2;
                  tmpItem = it2.current();
                }
            }
        }
      ++it;
      currentItem = it.current();
    }
  return selection;
}

std::vector<CCopasiObject*>* SimpleSelectionWidget::getListSelection()
{
  return this->outputVector;
}

bool SimpleSelectionWidget::listHasSelection()
{
  bool hasSelection = false;
  unsigned int counter;
  unsigned int numItems = this->selectedItemsBox->count();
  for (counter = 0; counter < numItems; counter++)
    {
      if (this->selectedItemsBox->item(counter)->isSelected())
        {
          hasSelection = true;
          break;
        }
    }
  return hasSelection;
}

void SimpleSelectionWidget::populateTree(CModel* model)
{
  if (!model) return;
  // find all metabolites and create items in the metabolite subtree
  QListViewItem* item = new QListViewItem(this->timeSubtree, "time");
  this->treeItems[item] = (CCopasiObject*)model->getObject(CCopasiObjectName("Reference=Time"));
  const CCopasiVector<CMetab>& metabolites = model->getMetabolites();
  unsigned int counter;
  unsigned int maxCount = metabolites.size();
  for (counter = 0; counter < maxCount;++counter)
    {
      const CMetab* metab = metabolites[counter];
      std::string name = metab->getObjectName();
      bool unique = this->isMetaboliteNameUnique(name, metabolites);
      if (!unique)
        {
          const CCompartment* comp = metab->getCompartment();
          if (comp)
            {
              name = name + "(" + comp->getObjectName() + ")";
            }
        }
      name = "[" + name + "]";
      item = new QListViewItem(this->initialConcentrationSubtree, (name + "(t=0)").c_str());
      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=InitialConcentration"));
      item = new QListViewItem(this->transientConcentrationSubtree, (name + "(t)").c_str());
      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=Concentration"));
      item = new QListViewItem(initialParticleNumberSubtree, (name + "(t=0)").c_str());

      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=InitialParticleNumber"));
      item = new QListViewItem(this->transientParticleNumberSubtree, (name + "(t)").c_str());
      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=ParticleNumber"));
    }

  // find all reactions and create items in the reaction subtree
  const CCopasiVectorNS<CReaction>& reactions = model->getReactions();
  maxCount = reactions.size();
  for (counter = 0; counter < maxCount;++counter)
    {
      const CReaction* react = reactions[counter];
      std::string name = react->getObjectName();
      name = "flux(" + name + ")";
      item = new QListViewItem(this->concentrationFluxSubtree, name.c_str());
      treeItems[item] = (CCopasiObject*)react->getObject(CCopasiObjectName("Reference=Flux"));
      item = new QListViewItem(this->particleFluxSubtree, ("particle_" + name).c_str());
      treeItems[item] = (CCopasiObject*)react->getObject(CCopasiObjectName("Reference=ParticleFlux"));
      // create items for the reaction parameters
      item = new QListViewItem(this->reactionParameterSubtree, react->getObjectName());
      const CCopasiParameterGroup& parameters = react->getParameters();
      unsigned int j;
      unsigned int numParameters = parameters.size();
      for (j = 0; j < numParameters;++j)
        {
          CCopasiParameter* parameter = ((CCopasiParameterGroup&)parameters).getParameter(j);
          QListViewItem* parameterItem = new QListViewItem(item, parameter->getObjectName());
          treeItems[parameterItem] = (CCopasiObject*)parameter;
        }
    }
}

void SimpleSelectionWidget::destroy()
{
  this->clearTree();
  delete this->timeSubtree;
  delete this->concentrationFluxSubtree;
  delete this->particleFluxSubtree;
  delete this->reactionParameterSubtree;
  delete this->initialConcentrationSubtree;
  delete this->initialParticleNumberSubtree;
  delete this->transientParticleNumberSubtree;
  delete this->transientConcentrationSubtree;
  delete this->metaboliteSubtree;
  delete this->reactionSubtree;
  std::map<QListBoxItem*, CCopasiObject*>::iterator it = this->selectedObjects.begin();
  while (it != this->selectedObjects.end())
    {
      delete it->first;
      ++it;
    }
}

bool SimpleSelectionWidget::isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites)
{
  bool unique = true;
  bool found = false;
  unsigned int counter;
  for (counter = 0; counter < metabolites.size();++counter)
    {
      const std::string& thisName = metabolites[counter]->getObjectName();
      if (name == thisName)
        {
          if (found)
            {
              unique = false;
              break;
            }
          found = true;
        }
    }
  return unique;
}

void SimpleSelectionWidget::clearTree()
{
  QListViewItem* child = this->timeSubtree->firstChild();
  QListViewItem* nextSibling;
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->concentrationFluxSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->particleFluxSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->initialConcentrationSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->initialParticleNumberSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->transientParticleNumberSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->transientConcentrationSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->reactionParameterSubtree->firstChild();
  while (child)
    {
      nextSibling = child->firstChild();
      if (!nextSibling)
        {
          nextSibling = child->nextSibling();
          delete child;
        }
      child = nextSibling;
    }
}

void SimpleSelectionWidget::setOutputVector(std::vector<CCopasiObject *> * outputVector)
{
  this->selectObjects(outputVector);
  this->outputVector = outputVector;
}

QListViewItem* SimpleSelectionWidget::findListViewItem(const CCopasiObject * object)
{
  QListViewItem* item = NULL;
  std::map<QListViewItem*, CCopasiObject*>::iterator it = this->treeItems.begin();
  std::map<QListViewItem*, CCopasiObject*>::iterator endPos = this->treeItems.end();
  while (it != endPos)
    {
      if (it->second == object)
        {
          item = it->first;
          break;
        }
      ++it;
    }
  return item;
}

void SimpleSelectionWidget::moveUpButton_clicked()
{
  // move all selected items up one place and check if the first item is now selected.
  // if so, disable the moveUpButton
  // also check, if the last item is selected, if not, enable the moveDownButton
  const std::vector<int>* selectedIndices = this->getSelectedIndicesFromList();
  unsigned int counter;
  unsigned int maxCount = selectedIndices->size();
  for (counter = 0; counter < maxCount;++counter)
    {
      int index = selectedIndices->at(counter);
      QListBoxItem* item = this->selectedItemsBox->item(index);
      this->selectedItemsBox->takeItem(item);
      this->selectedItemsBox->insertItem(item, index - 1);
    }
  this->updateMoveButtons();
  this->updateOutputVector();
  delete selectedIndices;
}

void SimpleSelectionWidget::moveDownButton_clicked()
{
  // move all selected items down one place and check if the last item is now selected.
  // if so, disable the moveDownButton
  // also check, if the first item is selected, if not, enable the moveUpButton
  const std::vector<int>* selectedIndices = this->getSelectedIndicesFromList();
  unsigned int counter;
  unsigned int maxCount = selectedIndices->size();
  for (counter = maxCount; counter > 0;--counter)
    {
      int index = selectedIndices->at(counter - 1);
      QListBoxItem* item = this->selectedItemsBox->item(index);
      this->selectedItemsBox->takeItem(item);
      this->selectedItemsBox->insertItem(item, index + 1);
    }
  this->updateMoveButtons();
  this->updateOutputVector();
  delete selectedIndices;
}

const std::vector<int>* SimpleSelectionWidget::getSelectedIndicesFromList()
{
  std::vector<int>* selectedIndices = new std::vector<int>();
  unsigned int counter;
  unsigned int maxCount = this->selectedItemsBox->count();
  for (counter = 0; counter < maxCount;++counter)
    {
      if (this->selectedItemsBox->item(counter)->isSelected())
        {
          selectedIndices->push_back(counter);
        }
    }
  return selectedIndices;
}

void SimpleSelectionWidget::updateMoveButtons()
{
  bool firstItemSelected = this->selectedItemsBox->item(0)->isSelected();
  bool lastItemSelected = this->selectedItemsBox->item(this->selectedItemsBox->count() - 1)->isSelected();
  if (firstItemSelected)
    {
      this->moveUpButton->setEnabled(false);
    }
  else
    {
      this->moveUpButton->setEnabled(true);
    }
  if (lastItemSelected)
    {
      this->moveDownButton->setEnabled(false);
    }
  else
    {
      this->moveDownButton->setEnabled(true);
    }
  if (this->listHasSelection())
    {
      this->deleteButton->setEnabled(true);
    }
}

void SimpleSelectionWidget::updateOutputVector()
{
  if (this->outputVector)
    {
      this->outputVector->clear();
      unsigned int counter;
      unsigned int maxCount = this->selectedItemsBox->count();
      for (counter = 0; counter < maxCount;++counter)
        {
          QListBoxItem* item = this->selectedItemsBox->item(counter);
          CCopasiObject* object = this->selectedObjects[item];
          this->outputVector->push_back(object);
        }
    }
}

void SimpleSelectionWidget::selectObjects(std::vector<CCopasiObject * > * objects)
{
  //clear selectedObjects
  //remove all items from selectedItemsList
  //enable all items in the tree
  std::map<QListBoxItem*, CCopasiObject*>::const_iterator it = this->selectedObjects.begin();
  std::map<QListBoxItem*, CCopasiObject*>::const_iterator endPos = this->selectedObjects.end();
  while (it != endPos)
    {
      this->selectedItemsBox->takeItem(it->first);
      delete it->first;
      QListViewItem* lvitem = this->findListViewItem(it->second);
      if (lvitem)
        {
          lvitem->setEnabled(true);
        }
      ++it;
    }
  this->selectedObjects.clear();
  unsigned int counter;
  unsigned int maxCount = objects->size();
  for (counter = 0; counter < maxCount;++counter)
    {
      CCopasiObject* object = objects->at(counter);
      std::string name = object->getCN();
      QListViewItem* lvitem = this->findListViewItem(object);
      if (lvitem)
        {
          lvitem->setEnabled(false);
        }
      QListBoxText* item = new QListBoxText(this->selectedItemsBox, name.c_str());
      this->selectedItemsBox->setSelected(item, true);
      this->selectedObjects[item] = object;
    }
}

void SimpleSelectionWidget::setSingleSelection(bool singleSelection)
{
  if (singleSelection && !mSingleSelect)
    {
      // clear all items from the list
      // select the topmost list item in the tree
      if (this->selectedItemsBox->count() != 0)
        {
          QListBoxText* item = (QListBoxText*)this->selectedItemsBox->item(0);
          CCopasiObject* object = this->selectedObjects[item];
          std::vector<CCopasiObject*>* v = new std::vector<CCopasiObject*>();
          v->push_back(object);
          this->selectObjects(v);
          delete v;
        }
    }
  if (!singleSelection && mSingleSelect)
    {
      // add the selected tree item to the list
      this->addButtonClicked();
    }
  this->mSingleSelect = singleSelection;
  if (this->mSingleSelect)
    {
      this->itemTree->setSelectionMode(QListView::Single);
      this->selectedItemsBox->setHidden(true);
      this->addButton->setHidden(true);
      this->deleteButton->setHidden(true);
      this->moveUpButton->setHidden(true);
      this->moveDownButton->setHidden(true);
    }
  else
    {
      this->itemTree->setSelectionMode(QListView::Extended);
      this->selectedItemsBox->setHidden(false);
      this->addButton->setHidden(false);
      this->deleteButton->setHidden(false);
      this->moveUpButton->setHidden(false);
      this->moveDownButton->setHidden(false);
    }
}

bool SimpleSelectionWidget::isSingleSelection()
{
  return this->mSingleSelect;
}
