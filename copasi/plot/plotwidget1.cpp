/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/plotwidget1.cpp,v $
   $Revision: 1.29 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/12/15 13:25:34 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'plotwidget1.ui'
 **
 ** Created: Fri Sep 26 16:01:29 2003
 **      by: The User Interface Compiler ($Id: plotwidget1.cpp,v 1.29 2004/12/15 13:25:34 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "plotwidget1.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtabwidget.h>
#include <qcheckbox.h>

#include "curve2dwidget.h"
#include "plotwindow.h"
#include "CPlotSpecification.h"
#include "report/CKeyFactory.h"
#include "CopasiUI/CCopasiPlotSelectionDialog.h"
#include "model/CMetabNameInterface.h"
#include "CopasiUI/DataModelGUI.h" 
//temporary
#include "mathematics.h"

//-----------------------------------------------------------------------------

/*
 *  Constructs a PlotWidget1 as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
PlotWidget1::PlotWidget1(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("PlotWidget1");
  PlotWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "PlotWidget1Layout");

  layout20 = new QVBoxLayout(0, 0, 6, "layout20");

  layout5 = new QHBoxLayout(0, 0, 6, "layout5");

  titleLabel = new QLabel(this, "titleLabel");
  layout5->addWidget(titleLabel);

  titleLineEdit = new QLineEdit(this, "titleLineEdit");
  layout5->addWidget(titleLineEdit);

  //activeLabel = new QLabel(this, "active?");
  //layout5->addWidget(activeLabel);

  activeCheckBox = new QCheckBox("active?", this, "activeCheckBox");
  layout5->addWidget(activeCheckBox);
  layout20->addLayout(layout5);

  layout19 = new QVBoxLayout(0, 0, 6, "layout19");

  line2 = new QFrame(this, "line2");
  line2->setFrameShape(QFrame::HLine);
  line2->setFrameShadow(QFrame::Sunken);
  line2->setFrameShape(QFrame::HLine);
  layout19->addWidget(line2);

  layout18 = new QVBoxLayout(0, 0, 6, "layout18");

  layout17 = new QHBoxLayout(0, 0, 6, "layout17");

  curveSpecLabel = new QLabel(this, "curveSpecLabel");
  layout17->addWidget(curveSpecLabel);
  QSpacerItem* spacer = new QSpacerItem(51, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout17->addItem(spacer);

  addCurveButton = new QPushButton(this, "addCurveButton");
  layout17->addWidget(addCurveButton);

  deleteCurveButton = new QPushButton(this, "deleteCurveButton");
  layout17->addWidget(deleteCurveButton);
  layout18->addLayout(layout17);

  tabs = new QTabWidget(this, "tabs");
  //tabs = new MyQTabWidget(this, "tabs");
  layout18->addWidget(tabs);
  layout19->addLayout(layout18);

  line3 = new QFrame(this, "line3");
  line3->setFrameShape(QFrame::HLine);
  line3->setFrameShadow(QFrame::Sunken);
  line3->setFrameShape(QFrame::HLine);
  layout19->addWidget(line3);

  layout4 = new QHBoxLayout(0, 0, 6, "layout4");

  startPlotButton = new QPushButton(this, "Commit");
  layout4->addWidget(startPlotButton);

  deletePlotButton = new QPushButton(/*this*/0, "deletePlotButton");
  //layout4->addWidget(deletePlotButton);

  addPlotButton = new QPushButton(/*this*/0, "addPlotButton");
  //layout4->addWidget(addPlotButton);

  resetButton = new QPushButton(this, "Revert");
  layout4->addWidget(resetButton);
  layout19->addLayout(layout4);
  layout20->addLayout(layout19);

  PlotWidget1Layout->addLayout(layout20, 0, 0);
  languageChange();
  //resize(QSize(508, 505).expandedTo(minimumSizeHint()));

  //TODO: adjust tab order? - mostly fine

  // signals and slots connections
  connect(addCurveButton, SIGNAL(clicked()), this, SLOT(addCurveGroupBox()));
  connect(deleteCurveButton, SIGNAL(clicked()), this, SLOT(removeCurveGroupBox()));
  connect(startPlotButton, SIGNAL(clicked()), this, SLOT(startPlot()));
  connect(deletePlotButton, SIGNAL(clicked()), this, SLOT(deletePlot()));
  connect(addPlotButton, SIGNAL(clicked()), this, SLOT(addPlot()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(resetPlot()));

  //TODO: this is for debugging only.
  //channelNames += "time";
  //channelNames += "X-Data";
  //channelNames += "Y-Data";

  //mpPlotSpec = new CPlotSpecification;
}

//-----------------------------------------------------------------------------
/*
 *  Destroys the object and frees any allocated resources
 */
PlotWidget1::~PlotWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

//-----------------------------------------------------------------------------
/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void PlotWidget1::languageChange()
{
  setCaption(tr("PlotWidget1"));
  titleLabel->setText(tr("Title"));
  titleLineEdit->setText(tr("Copasi"));
  curveSpecLabel->setText(tr("Curve Specification"));
  addCurveButton->setText(tr("New Curve"));
  deleteCurveButton->setText(tr("Delete Curve"));
  startPlotButton->setText(tr("Commit"));
  deletePlotButton->setText(tr("Delete Plot"));
  addPlotButton->setText(tr("New Plot"));
  resetButton->setText(tr("Revert"));
}

//-----------------------------------------------------------------------------

void PlotWidget1::addCurveTab(const std::string & title,
                              const CPlotDataChannelSpec & x,
                              const CPlotDataChannelSpec & y)
{
  CPlotItem* item = new CPlotItem(title, NULL, CPlotItem::curve2d);
  item->addChannel(x);
  item->addChannel(y);

  Curve2DWidget * curveWidget = new Curve2DWidget(tabs);
  curveWidget->LoadFromCurveSpec(item);
  tabs->addTab(curveWidget, item->getTitle().c_str());

  delete item;
}

void PlotWidget1::addCurveGroupBox()
{
  CCopasiPlotSelectionDialog* pBrowser = new CCopasiPlotSelectionDialog();
  std::vector<CCopasiObject*>* pVector1 = new std::vector<CCopasiObject*>();
  std::vector<CCopasiObject*>* pVector2 = new std::vector<CCopasiObject*>();
  pBrowser->setOutputVectors(pVector1, pVector2);
  pBrowser->setModel(dataModel->getModel());

  if (pBrowser->exec () == QDialog::Rejected)
    {
      //pdelete(pBrowser1);
      pdelete(pVector1);
      pdelete(pVector2);
      return;
    }

  if (pVector1->size() == 0 || pVector2->size() == 0)
    {
      //pdelete(pBrowser1);
      pdelete(pVector1);
      pdelete(pVector2);
      return;
    }

  std::string cn;
  std::vector<CCopasiObjectName> objects1, objects2;
  unsigned C_INT32 i;
  std::vector<CCopasiObjectName>::const_iterator sit;

  for (i = 0; i < pVector1->size(); i++)
    if ((*pVector1)[i])
      {
        cn = (*pVector1)[i]->getCN();
        for (sit = objects1.begin(); sit != objects1.end(); ++sit)
          if (*sit == cn) break;
        if (sit == objects1.end())
          {
            objects1.push_back(cn);
            std::cout << "***" << cn << std::endl;
          }
      }

  for (i = 0; i < pVector2->size(); i++)
    if ((*pVector2)[i])
      {
        cn = (*pVector2)[i]->getCN();
        for (sit = objects2.begin(); sit != objects2.end(); ++sit)
          if (*sit == cn) break;
        if (sit == objects2.end())
          {
            objects2.push_back(cn);
            std::cout << "---" << cn << std::endl;
          }
      }

  //CPlotSpec* pspec = dynamic_cast< CPlotSpec * >(GlobalKeys.get(objKey));
  //if (!pspec) return;

  C_INT32 storeTab = tabs->count();

  if (objects1.size() == 1)
    {
      for (i = 0; i < objects2.size(); ++i)
      {addCurveTab(CCopasiContainer::ObjectFromName(objects2[i])->getObjectUniqueName() , objects1[0], objects2[i]);}
    }
  else if (objects2.size() == 1)
    {
      for (i = 0; i < objects1.size(); ++i)
      {addCurveTab(CCopasiContainer::ObjectFromName(objects1[i])->getObjectUniqueName(), objects1[i], objects2[0]);}
    }
  else
    {
      unsigned C_INT32 imax;
      if (objects1.size() > objects2.size())
        imax = objects2.size();
      else
        imax = objects1.size();

      for (i = 0; i < imax; ++i)
        {
          addCurveTab(CCopasiContainer::ObjectFromName(objects2[i])->getObjectUniqueName()
                      + " / " + CCopasiContainer::ObjectFromName(objects1[i])->getObjectUniqueName() ,
                      objects1[i], objects2[i]);
        }
    }

  tabs->setCurrentPage(storeTab);

  pdelete(pVector1);
  pdelete(pVector2);
}

//-----------------------------------------------------------------------------

void PlotWidget1::removeCurveGroupBox()
{
  delete tabs->currentPage();
}

//-----------------------------------------------------------------------------

void PlotWidget1::startPlot()
{
  saveToPlotSpec();

  //commented for testing
  //startPlotButton->setEnabled(false);
  /*    deletePlotButton->setEnabled(false);
      addCurveButton->setEnabled(false);
      deleteCurveButton->setEnabled(false);
      titleLineEdit->setEnabled(false);
      scrollView->setEnabled(false);
    */
}

//-----------------------------------------------------------------------------

void PlotWidget1::deletePlot()
{}

//-----------------------------------------------------------------------------

void PlotWidget1::addPlot()
{}

//-----------------------------------------------------------------------------

void PlotWidget1::resetPlot()
{
  loadFromPlotSpec(dynamic_cast<CPlotSpecification*>(GlobalKeys.get(objKey)));
}

//-----------------------------------------------------------------------------

// not properly used for now
void PlotWidget1::plotFinished()
{
  startPlotButton->setEnabled(true);
  // ...and enable all other input fields
}

bool PlotWidget1::loadFromPlotSpec(const CPlotSpecification *pspec)
{
  if (!pspec) return false;

  //title
  titleLineEdit->setText(pspec->getTitle().c_str());

  //active?
  activeCheckBox->setChecked(pspec->isActive());

  C_INT32 oldIndex = tabs->currentPageIndex();

  //clear tabWidget
  while (tabs->currentPage()) delete tabs->currentPage();

  //reconstruct tabWidget from curve specs
  Curve2DWidget* curve;
  const CCopasiVector<CPlotItem> & curves = pspec->getItems();
  unsigned C_INT32 i, imax = curves.size();
  for (i = 0; i < imax; ++i)
    {
      curve = new Curve2DWidget(tabs);
      curve->LoadFromCurveSpec(curves[i]);
      tabs->addTab(curve, curves[i]->getTitle().c_str());
    }

  tabs->setCurrentPage(oldIndex);

  return true; //TODO really check
}

bool PlotWidget1::saveToPlotSpec()
{
  CPlotSpecification* pspec = dynamic_cast< CPlotSpecification * >(GlobalKeys.get(objKey));
  if (!pspec) return false;

  pspec->cleanup();

  //title
  if (pspec->getTitle() != (const char*)titleLineEdit->text().utf8())
    {
      pspec->setTitle((const char*)titleLineEdit->text().utf8());
      protectedNotify(ListViews::PLOT, ListViews::RENAME, objKey);
    }

  //active?
  pspec->setActive(activeCheckBox->isChecked());

  //curves
  CPlotItem* item;
  unsigned C_INT32 i, imax;
  imax = tabs->count();
  for (i = 0; i < imax; ++i)
    {
      item = pspec->createItem("dummyname", CPlotItem::curve2d);
      dynamic_cast<Curve2DWidget*>(tabs->page(i))->SaveToCurveSpec(item);
    }

  //TODO: CopasiParameters

  return true;
}

//-----------------------------------------------------------------------------

//TODO:  save a copy!

bool PlotWidget1::enter(const std::string & key)
{
  objKey = key;
  CPlotSpecification* pspec = dynamic_cast< CPlotSpecification * >(GlobalKeys.get(key));

  if (!pspec) return false;

  return loadFromPlotSpec(pspec);
}

//-----------------------------------------------------------------------------

bool PlotWidget1::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {//TODO: check list:
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REPORT:
    case ListViews::PLOT:
      return loadFromPlotSpec(dynamic_cast< CPlotSpecification * >(GlobalKeys.get(objKey)));
      break;

    default:
      break;
    }
  return true;
}

//-----------------------------------------------------------------------------

bool PlotWidget1::leave()
{
  return saveToPlotSpec();
}
