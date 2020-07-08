// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CQAutolayoutWizard_h__
#define CQAutolayoutWizard_h__

// Qt includes
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QWizard>
#include <QWizardPage>

#include <set>
#include <string>
#include <utility>

// I know I am not supposed to use copasi.h in a header file,
// but if I don't, the cpp file created by moc will include this header
// without copasi.h before and compilation will fail because this header indirectly
// include CopasiVector which uses C_INT32
#include "copasi/copasi.h"
#include "copasi/layout/CLReactionGlyph.h"

class QPushButton;
class QListWidget;
class QTreeWidget;

class CCompartment;
class CMetab;
class CModel;
class CReaction;

class CQModelElementTreeWidgetItem : public QTreeWidgetItem
{
protected:
  // we store the key of the object as well as the display name
  // when we create a new object
  std::string mKey;

public:
  /**
   * Constructor which in addition to the attributes of the original class
   * also takes a string which is the key of the object that is represented
   * by the item.
   */
  CQModelElementTreeWidgetItem(const QStringList & strings, const std::string& key, int type = QTreeWidgetItem::Type);

  /**
   * Returns a const reference to the key of the object.
   */
  const std::string& getKey() const;

  /**
   * Returns a pointer to the COPASI object
   * represented by this item.
   */
  CDataObject* getObject() const;
};

/**
 * This page is shown as the second wizard page
 * if the user hasn't selectzed anything in the
 * selection page.
 */
class CQNoSelectionErrorWizardPage : public QWizardPage
{
  Q_OBJECT

public:
  CQNoSelectionErrorWizardPage();

  virtual bool isComplete() const;
};

/**
 * This is the first page of the wizard.
 * It displays a tree where the user can select the objects
 * that should be included in the layout.
 */
class CQSelectionWizardPage : public QWizardPage
{
  Q_OBJECT

public:
  // constructor that takes a model
  // to fill the tree
  CQSelectionWizardPage(const CModel& model);

  /**
   * Checks which elements have been selected in the tree
   * and fills the containers that are passed in with those
   * elements.
   */
  void fillContainers(std::set<const CCompartment*>& compartments, std::set<const CReaction*>& reactions, std::set<const CMetab*>& species) const;

protected:
  // fills the selection tree with elements from the model
  void fillTree(const CModel& model);

protected:
  // flag that determines if compartment layout elements
  // are created for the layout.
  bool mCreateCompartmentElements;

  // QTreeWidget for the selection of model elements
  // for which we want to create the layout
  QTreeWidget* mpSelectionTree;

  // Top level tree widget item that holds the compartments
  QTreeWidgetItem* mpCompartmentsItem;

  // Top level tree widget item that holds the reactions
  QTreeWidgetItem* mpReactionsItem;

protected slots:
  // is called when the state of the compartment layout creation checkbox changes
  void slotCreateCompartments(int state);

  void slotItemChanged(QTreeWidgetItem* pItem, int column);
};

/**
 * In this page the user can select which species should be treated
 * as side compounds by the layout algorithm.
 */
class CQSideCompoundWizardPage : public QWizardPage
{
  Q_OBJECT

public:
  // default constructor
  CQSideCompoundWizardPage();

  /**
   * Fills the given set with the side compounds that
   * have been selected by the user.
   */
  void getSideCompounds(std::set<const CMetab*>& sideCompounds) const;

  /**
   * Passes the species that have been selected by the user
   * for use in the layout to the page.
   * These species are used to fill the list on the left.
   */
  void setSpeciesList(const std::set<const CMetab*>& metabs);

protected:
  class alphaSorter
  {
  public:
    bool operator()(const CMetab* m1, const CMetab* m2) const;
  };

  class CQListWidgetModelItem : public QListWidgetItem
  {
  public:
    // constructor which takes a string that is displayed for the item
    // and the key of a model object
    CQListWidgetModelItem(const QString& text, const std::string& key);

    // returns the key of the associated model object
    const std::string& getKey() const;

    CDataObject* getObject() const;

  protected:
    std::string mKey;
  };

protected:
  // the left list that contains the species
  QListWidget* mpSpeciesList;

  // the right list that contains the selected side compounds
  QListWidget* mpSideCompoundList;

  // the button that adds selected items to the
  // side compound list
  QPushButton* mpAddButton;

  // the button that removes items from the list of
  // list compounds
  QPushButton* mpRemoveButton;

  // this set sorts the metabolites alphabetically
  std::set<const CMetab*, alphaSorter> mSortedSpecies;

protected slots:
  // called when the add button was clicked
  void slotAddButtonClicked();

  // called when the remove button was clicked
  void slotRemoveButtonClicked();

  // called when the selection in the species list changes
  void slotSpeciesSelectionChanged();

  // called when the side compounds selection changes
  void slotSideCompoundSelectionChanged();
};

/**
 * In this page, the user can set all parameters
 * for the layout algorithm.
 */
class CQLayoutParametersWizardPage : public QWizardPage
{
  Q_OBJECT
};

class CQAutolayoutWizard : public QWizard
{
  Q_OBJECT

protected:
  enum PageOrder
  {
    NO_PAGE = -1,
    SELECTION_PAGE_ID = 1,
    NO_SELECTION_ERROR_PAGE_ID = 2,
    SIDE_COMPOUND_PAGE_ID = 3,
    LAYOUT_PARAMETER_PAGE_ID = 4
  };

  const CModel& mModel;

  // a set of species pointers for the species
  // that shall be part of the layout
  mutable std::set<const CMetab*> mSpecies;

  // a set of species which should be treated as side species
  // which means that the nodes for those species are duplicated
  // for each reaction in which they occur
  mutable std::set<const CMetab*> mSideSpecies;

  // the a set of compartments for which we create layout elements
  mutable std::set<const CCompartment*> mCompartments;

  // a set of reactions for which we create layout elements
  mutable std::set<const CReaction*> mReactions;

  // remember the id of the last page we visited
  PageOrder mLastPageId;

public:
  /**
   * Constructor needs a const reference to
   * a COPASI model and a layout object that is filled by
   * the wizard.
   */
  CQAutolayoutWizard(const CModel& model, QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());

  // Destructor
  ~CQAutolayoutWizard();

  virtual int nextId() const;

  const std::set<const CCompartment*>& getSelectedCompartments() const
  {
    return this->mCompartments;
  }

  const std::set<const CReaction*>& getSelectedReactions() const
  {
    return this->mReactions;
  }

  const std::set<const CMetab*>& getSelectedMetabolites() const
  {
    return this->mSpecies;
  }

  const std::set<const CMetab*>& getSideMetabolites() const
  {
    return this->mSideSpecies;
  }

protected:
  // this is called when the wizard is cloned
  // I use this method to update the containers
  virtual void done(int result);

  // creates the first page for the wizard
  // This is the page where the user selects the model elements
  QWizardPage* createSelectionPage();

  // creates the second page for the wizard
  // here the user can decide if certain species should be
  // treated as side components
  QWizardPage* createSideCompoundPage();

  // creates the third page for the wizard
  // here the user can make settings for the layout
  // algorithm
  QWizardPage* createLayoutParameterPage();

  // creates the error page for the wizard
  // where the user is asked to please select element for the layout
  QWizardPage* createErrorPage();

protected slots:
  // this is called whenever the page changes
  void slotCurrentIdChanged(int id);
};

#endif // CQAutolayoutWizard_h__
