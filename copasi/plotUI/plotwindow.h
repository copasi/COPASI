// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <fstream>
#include <string>
#include <vector>
#include <QToolButton>

#include "copasi/copasi.h"
#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/UI/CWindowInterface.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/plotUI/CPlotInterface.h"

class CPlotSpecification;
class CPlotSpec2Vector;
class CDataContainer;
class COutputHandlerPlot;
class CopasiUI3Window;
class QMenu;
class QAction;

class PlotWindow : public CWindowInterface, public COutputInterface
{
  Q_OBJECT

private:

  // points to the plot instance inside this window
  CPlotInterface *mpPlot;
  COutputHandlerPlot *mpHandler;
  CopasiUI3Window * mpMainWindow;
  QMenu* mpWindowMenu;

  QToolBar * mpToolBar;
  QAction *mpaCloseWindow;
  QAction *mpaShowAll;
  QAction *mpaHideAll;
  QAction *mpaPrint;
  QAction *mpaSaveImage;
  QAction *mpaSaveData;
  QAction *mpaZoomOut;
  QAction *mpaToggleLogX;
  QAction *mpaToggleLogY;
  QAction *mpaDeactivatePlot;
  QAction *mpaEditPlot;

  bool initializing;

  void createToolBar();
  void createMenus();
  void createActions();

public:
  PlotWindow(COutputHandlerPlot * pHandler, const CPlotSpecification* ptrSpec, CopasiUI3Window * pMainWindow);

  virtual ~PlotWindow();

  bool initFromSpec(const CPlotSpecification* ptrSpec);

  static CPlotInterface * createPlot(const CPlotSpecification * pPlotSpec);

  CPlotInterface * getPlot() const;

  /**
   *
   * @return a pointer to this plot windows 'window' menu.
   */
  virtual QMenu *getWindowMenu() const;

  /**
   * compile the object list from name vector
   * @param CObjectInterface::ContainerList listOfContainer
   * @param  const CDataModel* pDataModel
   * @return bool success
   */
  virtual bool compile(CObjectInterface::ContainerList listOfContainer);

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const Activity & activity);

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  virtual void separate(const Activity & activity);

  /**
   * Finish the output
   */
  virtual void finish();

  /**
   * Saves the current plot to the given filename.
   *
   * This implementation supports PDF, SVG and PNG
   */
  virtual void saveToFile(const QString& fileName) const;

  /**
   * Retrieve the list of objects handled by the interface
   * @return const CObjectInterface::ObjectSet & objects
   */
  virtual const CObjectInterface::ObjectSet & getObjects() const;

private slots:
  //void enableZoom();

  //void mouseReleased(const QMouseEvent &e);

  // toggle log X
  void toggleLogX(bool);

  // toggle log Y
  void toggleLogY(bool);

  // Print the plot to printer
  void printPlot();

  // Print the plot as an image
  void printAsImage();

  /// Save data into a file
  void slotSaveData();

  /// Zoom out
  void slotZoomOut();

  /**
   * Show all curves.
   */
  void slotSelectAll();

  /**
   * Hide all curves.
   */
  void slotDeselectAll();

  /*
   * Close current window
   */
  void slotCloseWindow();

  /**
   * Deactivate the plot
   */
  void slotDeactivatePlot();

  /**
   * Edit the plot specification
   */
  void slotEditPlot();

protected:
  virtual void closeEvent(QCloseEvent *closeEvent);
};
