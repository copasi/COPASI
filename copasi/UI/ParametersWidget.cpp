/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ParametersWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/01/25 10:52:14 $
   End CVS Header */

#include "ParametersWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "model/CModel.h"
#include "model/CCompartment.h"
#include "model/CMetabNameInterface.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"

class CParameterListItem : public QListViewItem
  {
  public:
    CParameterListItem(QListView *parent, const QString & text)
        : QListViewItem(parent, text),
        mpObject(NULL)
    {
      setOpen(true);
    }

    CParameterListItem(CParameterListItem *parent, const QString & text)
        : QListViewItem(parent, text),
        mpObject(NULL)
    {
      setOpen(true);
    }

    CParameterListItem(CParameterListItem *parent, const QString & name,
                       CCopasiObject* obj, C_FLOAT64 value, const QString & unit)
        : QListViewItem(parent, name, QString::number(value), unit),
        mpObject(obj)
    {
      setRenameEnabled(1, true);
    }

    CCopasiObject* getObject() const
      {return mpObject;}

    //QString key(int, bool) const;

  protected:
    CCopasiObject* mpObject;
  };

//****************************************************************************

ParametersWidget::ParametersWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("ParametersWidget");
  ParametersWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ParametersWidgetLayout");

  commitButton = new QPushButton(this, "commitButton");
  commitButton->setText("Commit");
  ParametersWidgetLayout->addWidget(commitButton, 2, 0);

  revertButton = new QPushButton(this, "revertButton");
  revertButton->setText("Revert");
  ParametersWidgetLayout->addMultiCellWidget(revertButton, 2, 2, 1, 2);

  spacer2 = new QSpacerItem(414, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  ParametersWidgetLayout->addItem(spacer2, 2, 3);

  listView = new QListView(this, "listView");
  listView->addColumn("Name");
  listView->addColumn("Value");
  listView->addColumn("Unit");
  listView->setSelectionMode(QListView::Single);
  listView->setAllColumnsShowFocus(TRUE);
  listView->setItemMargin(1);
  listView->setResizeMode(QListView::LastColumn);
  listView->setDefaultRenameAction(QListView::Accept);

  ParametersWidgetLayout->addMultiCellWidget(listView, 0, 0, 2, 3);

  layoutLeft = new QVBoxLayout(0, 0, 6, "layoutLeft");

  labelTitle = new QLabel(this, "labelTitle");
  labelTitle->setAlignment(int(QLabel::WordBreak | QLabel::AlignVCenter | QLabel::AlignRight));
  labelTitle->setText("<h2>Model parameters</h2>");
  layoutLeft->addWidget(labelTitle);
  spacer1 = new QSpacerItem(20, 261, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layoutLeft->addItem(spacer1);

  ParametersWidgetLayout->addMultiCellLayout(layoutLeft, 0, 1, 0, 1);
  //languageChange();
  //resize(QSize(511, 572).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(commitButton, SIGNAL(clicked()), this, SLOT(commitPressed()));
  connect(revertButton, SIGNAL(clicked()), this, SLOT(revertPressed()));

  connect(listView, SIGNAL(clicked(QListViewItem*, const QPoint &, int)),
           this, SLOT(editItem(QListViewItem*, const QPoint &, int)));

  connect(listView, SIGNAL(returnPressed(QListViewItem*)),
           this, SLOT(editItem(QListViewItem*)));
  connect(listView, SIGNAL(spacePressed(QListViewItem*)),
           this, SLOT(editItem(QListViewItem*)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
ParametersWidget::~ParametersWidget()
{}

void ParametersWidget::commitPressed()
{
  saveToModel();
}

void ParametersWidget::revertPressed()
{
  loadFromModel();
}

bool ParametersWidget::loadFromModel()
{
  CModel* model = dynamic_cast< CModel * >(GlobalKeys.get(objKey));
  if (!model) return false;

  listView->clear();

  unsigned C_INT32 i, imax, j, jmax;
  QString unit;

  //Compartments
  mCompItem = new CParameterListItem(listView, "Volumes");
  unit = FROM_UTF8(model->getVolumeUnit());
  const CCopasiVector< CCompartment > & comps = model->getCompartments();
  imax = comps.size();
  for (i = 0; i < imax; ++i)
    new CParameterListItem(mCompItem, FROM_UTF8(comps[i]->getObjectName()),
                           comps[i], comps[i]->getInitialVolume(), unit);

  //Metabs
  mMetabItem = new CParameterListItem(listView, "Initial concentrations");
  unit = FROM_UTF8(model->getQuantityUnit() + "/" + model->getVolumeUnit());
  const CCopasiVector< CMetab > & metabs = model->getMetabolites();
  imax = metabs.size();
  for (i = 0; i < imax; ++i)
    new CParameterListItem(mMetabItem, FROM_UTF8(CMetabNameInterface::getDisplayName(model, *metabs[i])),
                           metabs[i], metabs[i]->getInitialConcentration(), unit);

  //Reactions
  mReacItem = new CParameterListItem(listView, "Kinetic parameters");
  const CCopasiVector< CReaction > & reacs = model->getReactions();
  CReaction* reac;
  CParameterListItem* tmp;
  imax = reacs.size();
  for (i = 0; i < imax; ++i)
    {
      reac = reacs[i];
      tmp = new CParameterListItem(mReacItem, FROM_UTF8(reac->getObjectName()));

      jmax = reac->getParameters().size();
      for (j = 0; j < jmax; ++j)
        new CParameterListItem(tmp, FROM_UTF8(reac->getParameters().getParameter(j)->getObjectName()),
                               reac->getParameters().getParameter(j),
                               *(C_FLOAT64*)reac->getParameters().getParameter(j)->getValue(), "");
    }

  return true;
}

bool ParametersWidget::saveToModel() const
  {
  }

//slot
void ParametersWidget::editItem(QListViewItem * item, const QPoint & C_UNUSED(pnt), int c)
{
  if (!item) return;
  if (c == 1) //column 1
    item->startRename(1);
}

//slot
void ParametersWidget::editItem(QListViewItem * item)
{
  if (!item) return;
  item->startRename(1);
}

//***********************************************************************************

bool ParametersWidget::enter(const std::string & key)
{
  objKey = key;
  CModel* model = dynamic_cast< CModel * >(GlobalKeys.get(key));

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
  return saveToModel();
}
