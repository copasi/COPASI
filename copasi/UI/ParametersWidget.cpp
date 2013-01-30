// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "ParametersWidget.h"

#include <QPushButton>
#include <q3listview.h>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetabNameInterface.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"
#include "utilities/CDimension.h"
#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "commandline/CLocaleString.h"

#define COL_NAME 0
#define COL_STATUS 1
#define COL_VALUE 2
#define COL_UNIT 3

class CParameterListItem : public Q3ListViewItem
{
public:
  CParameterListItem(Q3ListView *parent, const QString & text)
    : Q3ListViewItem(parent, text),
      mpObject(NULL),
      mIsChanged(false)
  {
    setOpen(true);
    setSelectable(false);
  }

  CParameterListItem(CParameterListItem *parent, const QString & text)
    : Q3ListViewItem(parent, text),
      mpObject(NULL),
      mIsChanged(false)
  {
    setOpen(true);
    setSelectable(false);
  }

  CParameterListItem(CParameterListItem *parent, const QString & name,
                     CCopasiObject* obj, C_FLOAT64 value, const QString & unit, int framework = 0)
    : Q3ListViewItem(parent, name, "", QString::number(value), unit),
      mpObject(obj),
      mIsChanged(false)
  {
    setRenameEnabled(COL_VALUE, true);

    CModelEntity* me = dynamic_cast<CModelEntity*>(obj);

    if (me) //object is a CModelEntity
      {
        bool InitiaValueChangeAllowed = (me->getInitialExpression() == "");

        CMetab * pMetab = dynamic_cast< CMetab * >(me);

        if (pMetab != NULL && framework == 0)
          InitiaValueChangeAllowed &= static_cast<const bool>(pMetab->isInitialConcentrationChangeAllowed());

        switch (me->getStatus())
          {
            case CModelEntity::FIXED:
              setText(COL_STATUS, "fixed");
              setRenameEnabled(COL_VALUE, InitiaValueChangeAllowed);
              break;

            case CModelEntity::ODE:
              setText(COL_STATUS, "ode");
              setRenameEnabled(COL_VALUE, InitiaValueChangeAllowed);
              break;

            case CModelEntity::ASSIGNMENT:
              setText(COL_STATUS, "assign");
              setRenameEnabled(COL_VALUE, false);
              break;

            case CModelEntity::REACTIONS:

              if (static_cast< CMetab * >(me)->isDependent())
                setText(COL_STATUS, "dep");
              else if (me->isUsed())
                setText(COL_STATUS, "indep");
              else
                setText(COL_STATUS, "unused");

              setRenameEnabled(COL_VALUE, InitiaValueChangeAllowed);
              break;

            case CModelEntity::TIME:

              if (static_cast< CModel * >(me)->isAutonomous())
                setRenameEnabled(COL_VALUE, false);
              else
                setRenameEnabled(COL_VALUE, true);

              break;

            default:
              break;
          }
      }
  }

  //this constructor is used for global parameters in reactions
  CParameterListItem(CParameterListItem *parent, const QString & name,
                     CCopasiObject* obj, const QString & value, const QString & unit)
    : Q3ListViewItem(parent, name, "", value, unit),
      mpObject(obj),
      mIsChanged(false)
  {
    setRenameEnabled(COL_VALUE, false);
    setText(COL_STATUS, "global");
  }

  CCopasiObject* getObject() const
  {return mpObject;}

  C_FLOAT64 getValue() const
  {return text(COL_VALUE).toDouble();}

  bool isChanged() const
  {return mIsChanged;}

  //QString key(int, bool) const;

protected:
  CCopasiObject* mpObject;
  bool mIsChanged;

  virtual void okRename(int col)
  {
    QString oldText = text(COL_VALUE);
    Q3ListViewItem::okRename(col);
    QString newText = text(COL_VALUE);

    if (oldText == newText) return;

    mIsChanged = true;

    if ('*' != text(COL_NAME)[0])
      setText(COL_NAME, "*" + text(COL_NAME)); //TODO: find better way to display changed values
  }
};

//****************************************************************************

ParametersWidget::ParametersWidget(QWidget* parent, const char* name, Qt::WFlags fl)
  : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("ParametersWidget");

  ParametersWidgetLayout = new QGridLayout(this);
  ParametersWidgetLayout->setMargin(11);
  ParametersWidgetLayout->setSpacing(6);
  ParametersWidgetLayout->setObjectName("ParametersWidgetLayout");

  commitButton = new QPushButton(this);
  commitButton->setObjectName("commitButton");
  commitButton->setText("Commit");
  ParametersWidgetLayout->addWidget(commitButton, 2, 0);

  revertButton = new QPushButton(this);
  revertButton->setObjectName("revertButton");
  revertButton->setText("Revert");
  ParametersWidgetLayout->addMultiCellWidget(revertButton, 2, 2, 1, 2);

  spacer2 = new QSpacerItem(414, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  ParametersWidgetLayout->addItem(spacer2, 2, 3);

  listView = new Q3ListView(this, "listView");
  listView->addColumn("Name");
  listView->addColumn("Status");
  listView->addColumn("Value");
  listView->addColumn("Unit");
  listView->setSelectionMode(Q3ListView::Single);
  listView->setAllColumnsShowFocus(true);
  listView->setItemMargin(1);
  listView->setResizeMode(Q3ListView::LastColumn);
  listView->setDefaultRenameAction(Q3ListView::Accept);

  ParametersWidgetLayout->addMultiCellWidget(listView, 1, 1, 0, 3);

  layoutLeft = new QHBoxLayout(0);
  layoutLeft->setMargin(0);
  layoutLeft->setSpacing(6);
  layoutLeft->setObjectName("layoutLeft");

  labelTitle = new QLabel(this);
  labelTitle->setObjectName("labelTitle");
  labelTitle->setAlignment(int(Qt::WordBreak | Qt::AlignVCenter | Qt::AlignRight));
  labelTitle->setText("<h2>Model Parameters</h2>");
  layoutLeft->addWidget(labelTitle);

  spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layoutLeft->addItem(spacer1);

  saveButton = new QPushButton(this);
  saveButton->setObjectName("saveButton");
  saveButton->setText("Save data...");
  layoutLeft->addWidget(saveButton);

  ParametersWidgetLayout->addMultiCellLayout(layoutLeft, 0, 0, 0, 3);

  // signals and slots connections
  connect(commitButton, SIGNAL(clicked()), this, SLOT(commitPressed()));
  connect(revertButton, SIGNAL(clicked()), this, SLOT(revertPressed()));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(savePressed()));

  connect(listView, SIGNAL(clicked(Q3ListViewItem*, const QPoint &, int)),
          this, SLOT(editItem(Q3ListViewItem*, const QPoint &, int)));

  connect(listView, SIGNAL(returnPressed(Q3ListViewItem*)),
          this, SLOT(editItem(Q3ListViewItem*)));
  connect(listView, SIGNAL(spacePressed(Q3ListViewItem*)),
          this, SLOT(editItem(Q3ListViewItem*)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
ParametersWidget::~ParametersWidget()
{}

void ParametersWidget::commitPressed()
{
  saveToModel();
  loadFromModel();
}

void ParametersWidget::revertPressed()
{
  loadFromModel();
}

void ParametersWidget::savePressed()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          "untitled.tab", "Tab Separated Files (*.tab);;Comma Separated Files (*.csv);;TEXT Files (*.txt)", "Save as");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail()) return;

  if (fileName.endsWith(".txt"))
    {
      CModel* model = dynamic_cast< CModel * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

      if (model != NULL)
        {
          file << model->printParameterOverview() << std::endl;
        }
    }
  else if (fileName.endsWith(".csv"))
    {
      saveData(file, ",");
    }
  else
    {
      saveData(file, "\t");
    }

  file.close();
}
void ParametersWidget::saveData(std::ofstream& file, const std::string& delim /*= "\t"*/) const
{
  file << "type" << delim
       << "reaction" << delim
       << "name" << delim
       << "status" << delim
       << "value" << delim
       << "unit" << std::endl;
  Q3ListViewItem *current = listView->firstChild();

  while (current != NULL)
    {
      Q3ListViewItem* item = current->firstChild();
      const std::string& currentName = current->text(0).toStdString();

      while (item != NULL)
        {
          if (currentName == "Kinetic Parameters")
            {
              const std::string& reactionName = item->text(0).toStdString();
              Q3ListViewItem* reaction = item->firstChild();

              while (reaction != NULL)
                {
                  file << currentName << delim;
                  file << reactionName << delim;
                  file << reaction->text(0).toStdString() << delim;
                  file << reaction->text(1).toStdString() << delim;
                  file << reaction->text(2).toStdString() << delim;
                  file << reaction->text(3).toStdString() << std::endl;
                  reaction = reaction->nextSibling();
                }
            }
          else
            {
              file << currentName << delim;
              file << delim;
              file << item->text(0).toStdString() << delim;
              file << item->text(1).toStdString() << delim;
              file << item->text(2).toStdString() << delim;
              file << item->text(3).toStdString() << std::endl;
            }

          item = item->nextSibling();
        }

      current = current->nextSibling();
    }
}
bool ParametersWidget::loadFromModel()
{
  CModel* model = dynamic_cast< CModel * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (!model) return false;

  listView->clear();

  size_t i, imax, j, jmax;
  QString unit;

  //Time
  mTimeItem = new CParameterListItem(listView, "Initial Time");
  unit = FROM_UTF8(model->getTimeUnitsDisplayString());
  new CParameterListItem(mTimeItem, "Model",
                         model, model->getInitialTime(), unit);

  //Compartments
  mCompItem = new CParameterListItem(listView, "Initial Volumes");
  unit = FROM_UTF8(model->getVolumeUnitsDisplayString());
  const CCopasiVector< CCompartment > & comps = model->getCompartments();
  imax = comps.size();

  for (i = 0; i < imax; ++i)
    new CParameterListItem(mCompItem, FROM_UTF8(comps[i]->getObjectName()),
                           comps[i], comps[i]->getInitialValue(), unit);

  //Metabs
  const CCopasiVector< CMetab > & metabs = model->getMetabolites();
  imax = metabs.size();

  switch (mFramework)
    {
      case 0:
        mMetabItem = new CParameterListItem(listView, "Initial Concentrations");
        unit = FROM_UTF8(model->getConcentrationUnitsDisplayString());

        for (i = 0; i < imax; ++i)
          new CParameterListItem(mMetabItem, FROM_UTF8(CMetabNameInterface::getDisplayName(model, *metabs[i], false)),
                                 metabs[i], metabs[i]->getInitialConcentration(), unit, mFramework);

        break;

      case 1:
        mMetabItem = new CParameterListItem(listView, "Initial Particle Numbers");
        unit = "";

        for (i = 0; i < imax; ++i)
          new CParameterListItem(mMetabItem, FROM_UTF8(CMetabNameInterface::getDisplayName(model, *metabs[i], false)),
                                 metabs[i], metabs[i]->getInitialValue(), unit, mFramework);

        break;
    }

  //Reactions
  mReacItem = new CParameterListItem(listView, "Kinetic Parameters");
  const CCopasiVector< CReaction > & reacs = model->getReactions();
  CReaction* reac;
  CParameterListItem* tmp;
  imax = reacs.size();

  for (i = 0; i < imax; ++i)
    {
      reac = reacs[i];

      //calculate units
      CFindDimensions units(reac->getFunction(), model->getQuantityUnitEnum() == CModel::dimensionlessQuantity,
                            model->getVolumeUnitEnum() == CModel::dimensionlessVolume,
                            model->getTimeUnitEnum() == CModel::dimensionlessTime,
                            model->getAreaUnitEnum() == CModel::dimensionlessArea,
                            model->getLengthUnitEnum() == CModel::dimensionlessLength
                           );
      units.setUseHeuristics(true);
      units.setChemicalEquation(&reac->getChemEq());
      units.findDimensions(reac->getCompartmentNumber() > 1);

      tmp = new CParameterListItem(mReacItem, FROM_UTF8(reac->getObjectName()));

      const CFunctionParameters & params = reac->getFunctionParameters();
      jmax = params.size();

      for (j = 0; j < jmax; ++j)
        if (params[j]->getUsage() == CFunctionParameter::PARAMETER)
          {
            CCopasiObject * obj = CCopasiRootContainer::getKeyFactory()->get(reac->getParameterMappings()[j][0]);

            if (!obj) continue;

            assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
            CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
            assert(pDataModel != NULL);

            if (reac->isLocalParameter(j))
              {
                CCopasiParameter * par = dynamic_cast<CCopasiParameter*>(obj); //must be a CCopasiParameter

                if (!par) continue; //or rather fatal error?

                new CParameterListItem(tmp, FROM_UTF8(params[j]->getObjectName()), par,
                                       * par->getValue().pDOUBLE,
                                       FROM_UTF8(units.getDimensions()[j].getDisplayString(pDataModel)));
              }
            else
              {
                CModelValue * par = dynamic_cast<CModelValue*>(obj); //must be a CModelValue

                if (!par) continue; //or rather fatal error?

                new CParameterListItem(tmp, FROM_UTF8(params[j]->getObjectName()), par,
                                       FROM_UTF8("-> " + par->getObjectName() + " (" + QString::number(par->getInitialValue()).ascii() + ")"),

                                       FROM_UTF8(units.getDimensions()[j].getDisplayString(pDataModel)));
              }
          }
    }

  //global Parameters
  mParamItem = new CParameterListItem(listView, "Global Quantities");
  unit = "";
  const CCopasiVector< CModelValue > & params = model->getModelValues();
  imax = params.size();

  for (i = 0; i < imax; ++i)
    new CParameterListItem(mParamItem, FROM_UTF8(params[i]->getObjectName()),
                           params[i], params[i]->getInitialValue(), unit);

  return true;
}

bool ParametersWidget::saveToModel()
{
  if (listView->isRenaming())
    {
      //the following is a hack to force termination of an active editor
      Q3ListViewItem* tmp = listView->currentItem();
      listView->setCurrentItem(listView->firstChild());

      if (tmp)
        {
          listView->setCurrentItem(tmp);
        }
    }

  bool changed = false;

  CParameterListItem * child;

  //Time
  child = (CParameterListItem *)mTimeItem->firstChild();

  if (child->isChanged())
    {
      changed = true;
      CModel* tmp = dynamic_cast<CModel*>(child->getObject());

      if (tmp) tmp->setInitialTime(child->getValue());
    }

  //Metabs
  child = (CParameterListItem *)mMetabItem->firstChild();

  while (child)
    {
      if (child->isChanged())
        {
          changed = true;
          CMetab* tmp = dynamic_cast<CMetab*>(child->getObject());

          if (tmp)
            switch (mFramework)
              {
                case 0:
                  tmp->setInitialConcentration(child->getValue());
                  break;

                case 1:
                  tmp->setInitialValue(child->getValue());
                  break;
              }
        }

      child = (CParameterListItem *)child->nextSibling();
    }

  //Compartments
  child = (CParameterListItem *)mCompItem->firstChild();

  while (child)
    {
      if (child->isChanged())
        {
          changed = true;
          CCompartment* tmp = dynamic_cast<CCompartment*>(child->getObject());

          if (tmp) tmp->setInitialValue(child->getValue());
        }

      child = (CParameterListItem *)child->nextSibling();
    }

  //Reactions
  CParameterListItem * child2;
  child = (CParameterListItem *)mReacItem->firstChild();

  while (child)
    {
      child2 = (CParameterListItem *)child->firstChild();

      while (child2)
        {
          if (child2->isChanged())
            {
              changed = true;
              CCopasiParameter* tmp = dynamic_cast<CCopasiParameter*>(child2->getObject());

              if (tmp) tmp->setValue(child2->getValue());

              //this does nothing for global parameters since the dynamic cast fails for those
            }

          child2 = (CParameterListItem *)child2->nextSibling();
        }

      child = (CParameterListItem *)child->nextSibling();
    }

  //global Parameters
  child = (CParameterListItem *)mParamItem->firstChild();

  while (child)
    {
      if (child->isChanged())
        {
          changed = true;
          CModelValue* tmp = dynamic_cast<CModelValue*>(child->getObject());

          if (tmp) tmp->setInitialValue(child->getValue());
        }

      child = (CParameterListItem *)child->nextSibling();
    }

  if (changed)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      protectedNotify(ListViews::STATE, ListViews::CHANGE, (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();
    }

  return true;
}

//slot
void ParametersWidget::editItem(Q3ListViewItem * item, const QPoint & C_UNUSED(pnt), int c)
{
  if (!item) return;

  if (c == COL_VALUE) //column 1
    item->startRename(COL_VALUE);
}

//slot
void ParametersWidget::editItem(Q3ListViewItem * item)
{
  if (!item) return;

  item->startRename(COL_VALUE);
}

//***********************************************************************************

bool ParametersWidget::enterProtected()
{
  CModel* model = dynamic_cast< CModel * >(mpObject);

  if (model) return loadFromModel();
  else return false;
}

bool ParametersWidget::update(ListViews::ObjectType objectType,
                              ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
      case ListViews::REACTION:
      case ListViews::MODEL:
      case ListViews::METABOLITE:
      case ListViews::COMPARTMENT:
        return loadFromModel();
        break;

      default:
        break;
    }

  return true;
}

bool ParametersWidget::leave()
{
  bool success = true;

  if (!saveToModel()) success = false;

  if (!loadFromModel()) success = false;

  return success;
}

void ParametersWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
  loadFromModel();
}
