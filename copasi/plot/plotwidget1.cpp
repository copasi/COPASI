/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/plotwidget1.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/10 12:54:12 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'plotwidget1.ui'
 **
 ** Created: Fri Sep 26 16:01:29 2003
 **      by: The User Interface Compiler ($Id: plotwidget1.cpp,v 1.9 2004/05/10 12:54:12 ssahle Exp $)
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

#include "curve2dwidget.h"
#include "plotwindow.h"
#include "CPlotSpec.h"
#include "report/CKeyFactory.h"
#include "CopasiUI/ObjectBrowser.h"

//temporary
#include <math.h>

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
  layout18->addWidget(tabs);
  layout19->addLayout(layout18);

  line3 = new QFrame(this, "line3");
  line3->setFrameShape(QFrame::HLine);
  line3->setFrameShadow(QFrame::Sunken);
  line3->setFrameShape(QFrame::HLine);
  layout19->addWidget(line3);

  layout4 = new QHBoxLayout(0, 0, 6, "layout4");

  startPlotButton = new QPushButton(this, "startPlotButton");
  layout4->addWidget(startPlotButton);

  deletePlotButton = new QPushButton(this, "deletePlotButton");
  layout4->addWidget(deletePlotButton);

  addPlotButton = new QPushButton(this, "addPlotButton");
  layout4->addWidget(addPlotButton);

  resetButton = new QPushButton(this, "resetButton");
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
  channelNames += "time";
  channelNames += "X-Data";
  channelNames += "Y-Data";
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
  startPlotButton->setText(tr("Start Plot"));
  deletePlotButton->setText(tr("Delete Plot"));
  addPlotButton->setText(tr("New Plot"));
  resetButton->setText(tr("Reset"));
}

//-----------------------------------------------------------------------------

void PlotWidget1::addCurveGroupBox()
{
  ObjectBrowser* pBrowser1 = new ObjectBrowser();
  ObjectBrowser* pBrowser2 = new ObjectBrowser();

  std::vector<CCopasiObject*>* pVector1 = new std::vector<CCopasiObject*>();
  pBrowser1->setOutputVector(pVector1);

  if (pBrowser1->exec () == QDialog::Rejected)
    {
      pdelete(pBrowser1);
      pdelete(pVector1);
      return;
    }

  if (pVector1->size() == 0)
    {
      pdelete(pBrowser1);
      pdelete(pVector1);
      return;
    }

  //pdelete(pBrowser);
  //pBrowser = new ObjectBrowser();

  std::vector<CCopasiObject*>* pVector2 = new std::vector<CCopasiObject*>();
  pBrowser2->setOutputVector(pVector2);

  if (pBrowser2->exec () == QDialog::Rejected)
    {
      pdelete(pBrowser2);
      pdelete(pVector1);
      pdelete(pVector2);
      return;
    }

  if (pVector1->size() == 0)
    {
      pdelete(pBrowser2);
      pdelete(pVector1);
      pdelete(pVector2);
      return;
    }

  std::string cn;
  std::vector<std::string> objects1, objects2;
  unsigned C_INT32 i;
  std::vector<std::string>::const_iterator sit;

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

  CPlotSpec* pspec = dynamic_cast< CPlotSpec * >(GlobalKeys.get(objKey));
  if (!pspec) return;

  if (objects1.size() == 1)
    {
      for (i = 0; i < objects2.size(); ++i)
        pspec->getCurves().push_back(Curve2DSpec("***", objects1[0], objects2[i])); //TODO title
    }
  else if (objects2.size() == 1)
    {
      for (i = 0; i < objects1.size(); ++i)
        pspec->getCurves().push_back(Curve2DSpec("***", objects1[i], objects2[0])); //TODO title
    }
  else
    {
      unsigned C_INT32 imax;
      if (objects1.size() > objects2.size())
        imax = objects2.size();
      else
        imax = objects1.size();

      for (i = 0; i < imax; ++i)
        pspec->getCurves().push_back(Curve2DSpec("***", objects1[i], objects2[i])); //TODO title
    }

  loadFromPlotSpec(pspec);
  //pdelete(pBrowser1);
  //pdelete(pBrowser2);
  pdelete(pVector1);
  pdelete(pVector2);

  /*
    Curve2DWidget * curve = new Curve2DWidget(tabs);
    curveWidgetVector.push_back(curve);
    //    curve->LoadFromCurveSpec(&*it, channelNames);  //TODO somehow tell the curve widget about the channel names
    tabs->addTab(curve, "test");
  */ 
  //TODO: check for some maximum number of curves
}

//-----------------------------------------------------------------------------

void PlotWidget1::removeCurveGroupBox()
{
  C_INT32 index = tabs->currentPageIndex();
  delete curveWidgetVector[index];

  std::vector<Curve2DWidget*>::iterator it;
  C_INT32 i;
  for (it = curveWidgetVector.begin(), i = 0; (it != curveWidgetVector.end())&(i < index); ++it, ++i);
  if (it != curveWidgetVector.end()) curveWidgetVector.erase(it);
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
  //when called, this method should restore the plot specification
  //enter(...);
}

//-----------------------------------------------------------------------------

// not properly used for now
void PlotWidget1::plotFinished()
{
  startPlotButton->setEnabled(true);
  // ...and enable all other input fields
}

bool PlotWidget1::loadFromPlotSpec(const CPlotSpec *pspec)
{
  if (!pspec) return false;

  Curve2DWidget* curve;
  const std::vector<Curve2DSpec> & curves = pspec->getCurves();

  //clear tabWidget
  std::vector<Curve2DWidget*>::const_iterator itw;
  for (itw = curveWidgetVector.begin(); itw != curveWidgetVector.end(); ++itw)
    {
      //tabs->removePage(*itw);  not necessary?
      delete *itw;
    }
  curveWidgetVector.clear();

  //reconstruct tabWidget from curve specs
  std::vector<Curve2DSpec>::const_iterator it;
  for (it = curves.begin(); it != curves.end(); ++it)
    {
      curve = new Curve2DWidget(tabs);
      curveWidgetVector.push_back(curve);
      curve->LoadFromCurveSpec(&*it, channelNames);
      tabs->addTab(curve, it->title.c_str());
    }
  return true; //TODO really check
}

bool PlotWidget1::saveToPlotSpec()
{
  /*CPlotSpec* pspec = dynamic_cast< CPlotSpec * >(GlobalKeys.get(objKey));
  if (!pspec) return false;

  //clear curves vector
  pspec->getCurves().clear();

  //reconstruct curves vector from tab widget
  Curve2DSpec cspec;
  std::vector<Curve2DWidget*>::const_iterator it;
  for (it = curveWidgetVector.begin(); it != curveWidgetVector.end(); ++it)
    {
      (*it)->SaveToCurveSpec(&cspec);
      pspec->getCurves().push_back(cspec);
    }
  */return true;
}

//-----------------------------------------------------------------------------

//TODO:  save a copy!

bool PlotWidget1::enter(const std::string & key)
{
  objKey = key;
  CPlotSpec* pspec = dynamic_cast< CPlotSpec * >(GlobalKeys.get(key));
  //TODO: check if it really is a plot spec

  if (pspec) return loadFromPlotSpec(pspec);
  else return false;
}

//-----------------------------------------------------------------------------

bool PlotWidget1::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  switch (objectType)
    {//TODO: check list:
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REPORT:
    case ListViews::PLOT:
      //TODO: check if it really is a compartment
      return loadFromPlotSpec(dynamic_cast< CPlotSpec * >(GlobalKeys.get(objKey)));
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
