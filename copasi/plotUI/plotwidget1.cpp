/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/plotwidget1.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:32:39 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'plotwidget1.ui'
 **
 ** Created: Fri Sep 26 16:01:29 2003
 **      by: The User Interface Compiler ($Id: plotwidget1.cpp,v 1.4 2003/10/16 16:32:39 shoops Exp $)
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
//#include <qtooltip.h>
//#include <qwhatsthis.h>
//#include <qimage.h>
//#include <qpixmap.h>

#include "crvspecscrlview.h"
#include "curvegroupbox.h"
#include "plotwindow.h"
#include "plotspec.h"

//temporary
#include <math.h>

CurveSpecScrollView::CurveSpecScrollView(QWidget * parent, const char * name, WFlags f)
    : QScrollView(parent, name, f)
{}

//-----------------------------------------------------------------------------

/*
 *  Constructs a PlotWidget1 as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */ 
//TODO: this widget should inherit CopasiWidget, but omitting inheritance for now with
//all the copasi code elsewhere
PlotWidget1::PlotWidget1(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl), filename("plotdata"), nextPlotKey(0), currentPlotKey(-1)
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

  scrollView = new CurveSpecScrollView(this, "scrollView");
  layout18->addWidget(scrollView);
  layout19->addLayout(layout18);

  layoutScrlView = new QVBoxLayout(scrollView->viewport(), 0, 6, "layoutScrlView");

  layoutGrpBox = new QVBoxLayout(0, 0, 0, "layoutGrpBox");
  layoutScrlView->addLayout(layoutGrpBox);

  scrollView->setVScrollBarMode(QScrollView::AlwaysOn);
  scrollView->verticalScrollBar()->setEnabled(true);

  CurveGroupBox* cgbox = new CurveGroupBox(scrollView->viewport());
  scrollView->addChild(cgbox);
  layoutGrpBox->addWidget(cgbox);
  cgrpboxes.push_back(cgbox);

  // a hack to get the layout 'right' (though still not that pretty)
  CurveGroupBox* big_box = new CurveGroupBox(scrollView->viewport());
  scrollView->addChild(big_box);
  layoutGrpBox->addWidget(big_box);
  delete big_box;

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
  resize(QSize(508, 505).expandedTo(minimumSizeHint()));

  //TODO: adjust tab order? - mostly fine

  // signals and slots connections
  connect(addCurveButton, SIGNAL(clicked()), this, SLOT(addCurveGroupBox()));
  connect(deleteCurveButton, SIGNAL(clicked()), this, SLOT(removeCurveGroupBox()));
  connect(startPlotButton, SIGNAL(clicked()), this, SLOT(startPlot()));
  connect(deletePlotButton, SIGNAL(clicked()), this, SLOT(deletePlot()));
  connect(addPlotButton, SIGNAL(clicked()), this, SLOT(addPlot()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(resetPlot()));

  // for the test application

  // prepare the data file - 'simulates' what happens in copasi
  targetfile.open(filename.c_str(), std::ios::in | std::ios::out | std::ios::trunc);

  stepSize = 100;  // also the initial number of points
  count = 0;

  for (int i = 1; i <= stepSize; i++)
    {
      double temp = 0.05 * double(i);
      targetfile << temp << "\t" << sin(temp) << "\t" << tan(temp) << "\t" << cos(temp) << "\t" << log(temp) << "\n";
    }

  pos = targetfile.tellp();

  // a timer that controls periodic appending of data
  QTimer* timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(appendData()));
  timer->start(4000);
}

//-----------------------------------------------------------------------------
/*
 *  Destroys the object and frees any allocated resources
 */
PlotWidget1::~PlotWidget1()
{
  // no need to delete child widgets, Qt does it all for us

  // delete all the pointers in cgrpboxes
  while (cgrpboxes.size() > 0)
    {
      delete cgrpboxes[cgrpboxes.size() - 1];  //always delete from the end of the vector
      cgrpboxes.pop_back();    //necessary?
    }

  // delete all the pointers in plotSpecVector
  while (plotSpecVector.size() > 0)
    {
      delete plotSpecVector[plotSpecVector.size() - 1];  //always delete from the end of the vector
      plotSpecVector.pop_back();
    }

  // delete all the pointers in plotWinVector
  while (plotWinVector.size() > 0)
    {
      delete plotWinVector[plotWinVector.size() - 1];  //always delete from the end of the vector
      plotWinVector.pop_back();
    }

  // for the test application
  targetfile.close();
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
  CurveGroupBox* cgbox = new CurveGroupBox(scrollView->viewport());
  cgbox->show();
  scrollView->addChild(cgbox);
  layoutGrpBox->addWidget(cgbox);
  cgrpboxes.push_back(cgbox);

  // note that for now CopasiPlot::CopasiPlot() provides 6 colours only
  // so we can't have more than six curves in one plot window
  // the following code might need to be modified...
  if (cgrpboxes.size() >= 6)
    addCurveButton->setEnabled(false);

  deleteCurveButton->setEnabled(true);

  // maybe need to set some flag here (which should be checked in startPlot())
  // so that the plot spec can be updated accordingly
  // or perhaps simply save the spec on leaving it irrespective of changes
}

//-----------------------------------------------------------------------------

void PlotWidget1::removeCurveGroupBox()
{
  //TODO
  //1. record the 'index' of the CurveGroupBox in focus

  //2. for the GUI, delete this CurveGroupBox (remove and delete the pointer from cgrpboxes)

  //test code for now
  delete cgrpboxes[cgrpboxes.size() - 1];
  cgrpboxes.pop_back();
  //end of test code

  //3. for the backend, delete the corresponding entry in plotSpecVector[currentPlotkey]->curves[index]
  // and remove the corresponding curve in the plot

  //4. also record the index in deleteCurveIndices: deleteCurveIndices.push_back(index);

  if (cgrpboxes.size() == 0)
    deleteCurveButton->setEnabled(false);

  // the number might need changing if we allow more curves in one plot
  if (cgrpboxes.size() < 6)
    addCurveButton->setEnabled(true);
}

//-----------------------------------------------------------------------------

void PlotWidget1::startPlot()
{
  // save changes first
  // let the user confirm changes to existing spec?
  // code creating/manipulating ptspec could be moved to a method saveChanges()

  std::vector<CurveSpec*> crvspecs;
  std::vector<int> vindices;

  // see if the plot spec exists. no - create a new window displaying the plot
  if (currentPlotKey == -1)
    {
      //disable the start plot button

      //commented for testing
      //startPlotButton->setEnabled(false);
      deletePlotButton->setEnabled(false);
      addCurveButton->setEnabled(false);
      deleteCurveButton->setEnabled(false);
      titleLineEdit->setEnabled(false);
      scrollView->setEnabled(false);

      // ...and maybe all other input fields??
      // note that these must be enabled again when the plot window is destroyed

      // create new CurveSpec objects and a new PlotTaskSpec
      //TODO: validate all user input...is that necessary?

      for (unsigned int i = 0; i < cgrpboxes.size(); i++)
        {
          CurveGroupBox* cgb = cgrpboxes[i];
          int axis_h = (cgb->xBtmRadioButton->isChecked()) ? 2 : 3,
                       axis_v = (cgb->yLeftRadioButton->isChecked()) ? 0 : 1;

          // and some code to map selected variables for X an Y axes into column indices
          // dummy values for now
          int coordX = 0, coordY = 1;
          vindices.push_back(coordX);
          vindices.push_back(coordY);

          //NB: this might not quite work...
          //in CopasiPlot::updatePlot(), it is assumed that elements in vindices (varIndices)
          // are distinct and in ascending order (so that data retrieval can be optimised)
          // this requires a bit more work than the above code
          // moreover, the indices fed into the CurveSpec constructor must correspond to (i.e. be the subscripts of)
          // the 'variable indices' stored in vindices
          // one possibility is to store the variable names (in string format) in the CurveSpec instance
          // and then converted to subscripts in CopasiPlot::updatePlot()

          // hmm, not really...
          CurveSpec* cs = new CurveSpec(cgb->curveTitleLineEdit->text().latin1(),
                                        2 * i, 2 * i + 1, axis_h, axis_v,
                                        cgb->xTitleLineEdit->text().latin1(),
                                        cgb->xTitleLineEdit->text().latin1());
          // note that 2 * i and 2*i+1 are now indices into the vector of variable indices for this curve...

          //TODO: modify CopasiPlot::updatePlot() accordingly

          crvspecs.push_back(cs);
        }

      // we need a file stream from somewhere...(probably this model)
      // for now this is a dummy value
      //std::fstream sourcefile;
      //sourcefile.open("plotdata", std::ios::in);

      PlotTaskSpec* ptspec = new PlotTaskSpec(targetfile, titleLineEdit->text().latin1(),
                                              vindices, crvspecs, PlotTaskSpec::PlotType(0));

      plotSpecVector.push_back(ptspec);

      // create a new window
      PlotWindow* win = new PlotWindow(targetfile);
      plotWinVector.push_back(win);

      win->resize(600, 360);
      win->show();
      // this doesn't do what I'd like...
      //connect(win, SIGNAL(destroyed()), this, SLOT(plotFinished()));

      currentPlotKey = nextPlotKey++;
    }
  else
    {
      // mostly reload the plot, but also check if new curves have been added
      // i.e. compare the size of cgrpboxes(for the GUI) and plotSpecVector[currentPlotKey]->curvespecs(the backend)

      // modify the current plot spec if necessary...
      PlotTaskSpec* ptspec = plotSpecVector[currentPlotKey];

      int formNum = cgrpboxes.size(), deletedNum = deletedCurveIndices.size();

      //TODO: test the code to modify the spec

      // delete the curve specs as specified
      for (int i = 0; i < deletedNum; i++)
        {
          delete ptspec->curves[i];
          ptspec->curves.erase(ptspec->curves.begin() + i);
        }

      // add the new curve specs
      int specNum = ptspec->curves.size();
      if (formNum > specNum)
        {
          for (int i = specNum; i < formNum; i++)
            {
              CurveGroupBox* cgb = cgrpboxes[i];
              int axis_h = (cgb->xBtmRadioButton->isChecked()) ? 2 : 3,
                           axis_v = (cgb->yLeftRadioButton->isChecked()) ? 0 : 1;

              // and some code to map selected variables for X an Y axes into column indices
              // dummy values for now
              int coordX = 0, coordY = 1;
              vindices.push_back(coordX);
              vindices.push_back(coordY);

              // hmm, not really...see above
              CurveSpec* cs = new CurveSpec(cgb->curveTitleLineEdit->text().latin1(),
                                            2 * i, 2 * i + 1, axis_h, axis_v,
                                            cgb->xTitleLineEdit->text().latin1(),
                                            cgb->xTitleLineEdit->text().latin1());
              // note that 2 * i and 2*i+1 are now indices into the vector of variable indices for this curve...

              crvspecs.push_back(cs);
            }
        }

      // show the window again
      PlotWindow* winptr = plotWinVector[currentPlotKey];
      winptr->reloadPlot(ptspec, deletedCurveIndices);
      winptr->resize(600, 360);
      winptr->show();

      // flush the vector
      while (deletedCurveIndices.size() > 0)
        deletedCurveIndices.pop_back();
    }

  //maybe this method should return the id of the plot, or similar...
}

//-----------------------------------------------------------------------------

void PlotWidget1::deletePlot()
{
  // let the user confirm?

  // just a precaution for now...
  if (currentPlotKey == -1)
    return;

  delete plotSpecVector[currentPlotKey];
  plotSpecVector.erase(plotSpecVector.begin() + currentPlotKey);

  // load the first level of plot widget?
}

//-----------------------------------------------------------------------------

void PlotWidget1::addPlot()
{
  // maybe call leave() or resetPlot() first?

  // reset the object key
  currentPlotKey = -1;

  // maybe move the following code into enter() ...
  // leave only one CurveGroupBox in the CurveScrollView
  while (cgrpboxes.size() > 1)
    {
      delete cgrpboxes[cgrpboxes.size() - 1];
      cgrpboxes.pop_back();
    }

  // set all fields to default values
  titleLineEdit->setText("Copasi");

  CurveGroupBox* cgb = cgrpboxes[0];
  cgb->curveTitleLineEdit->setText("");

  // then reset the axis title fields to be the first from the list ...

  cgb->xBtmRadioButton->setChecked(true);   // use xBottom by default
  cgb->yLeftRadioButton->setChecked(true);   // use yLeft by default

  // enable all input fields
  startPlotButton->setEnabled(true);
  deletePlotButton->setEnabled(false);
  addCurveButton->setEnabled(true);
  deleteCurveButton->setEnabled(true);
  titleLineEdit->setEnabled(true);
  scrollView->setEnabled(true);
}

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

//-----------------------------------------------------------------------------

bool PlotWidget1::enter()
{
  // this method should have an object key as an argument
  // load the plot specification according to the key or a blank form

  // just in case this is necessary... enable all fields
  startPlotButton->setEnabled(true);

  // but disable the delete button if this is a new plot
  if (currentPlotKey == -1)
    deletePlotButton->setEnabled(false);

  //dummy
  return true;
}

//-----------------------------------------------------------------------------

bool PlotWidget1::update()
{
  //dummy
  return true;
}

//-----------------------------------------------------------------------------

bool PlotWidget1::leave()
{
  // save changes? (and prompt the user to confirm first?)
  // if (currentPlotKey == -1) then create the new PlotTaskSpec object?

  //dummy
  return true;
}

//-----------------------------------------------------------------------------
// for the test application

void PlotWidget1::appendData()
{
  writeFile(count);
  count++;
}

//-----------------------------------------------------------------------------

void PlotWidget1::writeFile(int step)
{
  targetfile.seekp(pos);
  for (int i = 1 + (step + 1) * stepSize; i <= stepSize * (step + 2); i++)
    {
      double temp = 0.05 * double(i);
      targetfile << temp << "\t" << sin(temp) << "\t" << tan(temp) << "\t" << cos(temp) << "\t" << log(temp) << "\n";
    }
  pos = targetfile.tellp();
}
