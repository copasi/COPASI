/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/simpleselectionwidget.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/10/07 15:13:51 $
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
  this->singleSelect = true;
  this->itemTree->setSortColumn(-1);
  this->itemTree->setRootIsDecorated(true);

  this->selectedItemsBox->setMinimumWidth(270);

  this->reactionSubtree = new QListViewItem(this->itemTree, "reactions");
  this->particleFluxSubtree = new QListViewItem(this->reactionSubtree, "particle fluxes");
  this->concentrationFluxSubtree = new QListViewItem(this->reactionSubtree, "concentration fluxes");

  this->metaboliteSubtree = new QListViewItem(this->itemTree, "metabolites");
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

      //const std::string name=object->getCN();
      QListViewItem* lvitem = this->findListViewItem(object);
      const std::string name = lvitem->text(0);
      QListBoxText* item = new QListBoxText(this->selectedItemsBox, name.c_str());

      this->selectedItemsBox->setSelected(item, true);
      this->selectedObjects[item] = object;
      if (this->singleSelect)
        {
          //QListViewItem* lvitem=this->findListViewItem(object);
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
          if (this->singleSelect)
            {
              QListViewItem* lvitem = this->findListViewItem(object);
              lvitem->setEnabled(true);
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
  std::vector<QListViewItem*> toCheck;
  std::vector<QListViewItem*> unchecked;
  if (this->timeSubtree->isSelected())
    {
      unchecked.push_back(this->timeSubtree);
    }
  else
    {
      toCheck.push_back(timeSubtree);
    }
  if (this->metaboliteSubtree->isSelected())
    {
      unchecked.push_back(this->initialConcentrationSubtree);
      unchecked.push_back(this->initialParticleNumberSubtree);
      unchecked.push_back(this->transientConcentrationSubtree);
      unchecked.push_back(this->transientParticleNumberSubtree);
    }
  else
    {
      if (this->initialConcentrationSubtree->isSelected())
        {
          unchecked.push_back(this->initialConcentrationSubtree);
        }
      else
        {
          toCheck.push_back(this->initialConcentrationSubtree);
        }
      if (this->initialParticleNumberSubtree->isSelected())
        {
          unchecked.push_back(this->initialParticleNumberSubtree);
        }
      else
        {
          toCheck.push_back(this->initialParticleNumberSubtree);
        }
      if (this->transientConcentrationSubtree->isSelected())
        {
          unchecked.push_back(this->transientConcentrationSubtree);
        }
      else
        {
          toCheck.push_back(this->transientConcentrationSubtree);
        }
      if (this->transientParticleNumberSubtree->isSelected())
        {
          unchecked.push_back(this->transientParticleNumberSubtree);
        }
      else
        {
          toCheck.push_back(this->transientParticleNumberSubtree);
        }
    }
  if (this->reactionSubtree->isSelected())
    {
      unchecked.push_back(this->concentrationFluxSubtree);
      unchecked.push_back(this->particleFluxSubtree);
    }
  else
    {
      if (this->concentrationFluxSubtree->isSelected())
        {
          unchecked.push_back(this->concentrationFluxSubtree);
        }
      else
        {
          toCheck.push_back(this->concentrationFluxSubtree);
        }
      if (this->particleFluxSubtree->isSelected())
        {
          unchecked.push_back(this->particleFluxSubtree);
        }
      else
        {
          toCheck.push_back(this->particleFluxSubtree);
        }
    }
  unsigned int counter;
  unsigned int maxCount = unchecked.size();
  QListViewItem* child = NULL;
  for (counter = 0; counter < maxCount;++counter)
    {
      child = unchecked[counter]->firstChild();
      while (child)
        {
          CCopasiObject* object = this->treeItems[child];
          selection->push_back(object);
          child = child->nextSibling();
        }
    }
  maxCount = toCheck.size();
  for (counter = 0; counter < maxCount;++counter)
    {
      child = toCheck[counter]->firstChild();
      while (child)
        {
          if (child->isSelected())
            {
              CCopasiObject* object = this->treeItems[child];
              selection->push_back(object);
            }
          child = child->nextSibling();
        }
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
      /*
      item=new QListViewItem(name+"(t=0)");
      treeItems[item]=(CCopasiObject*)metab.getObject(CCopasiObjectName("Reference=InitialParticleNumber"));
      this->initialParticleNumberSubtree->insertItem(item);
      item=new QListViewItem(name+"(t)");
      treeItems[item]=(CCopasiObject*)metab.getObject(CCopasiObjectName("Reference=ParticleNumber"));
      this->particleNumberSubtree->insertItem(item);
      */
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
    }
}

void SimpleSelectionWidget::destroy()
{
  this->clearTree();
  delete this->timeSubtree;
  delete this->concentrationFluxSubtree;
  delete this->particleFluxSubtree;
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
}

void SimpleSelectionWidget::setOutputVector(std::vector<CCopasiObject *> * outputVector)
{
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
