// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include "UI/CopasiFileDialog.h"
#include "UI/CWindowInterface.h"
#include "utilities/COutputHandler.h"

class QAction;

class CopasiPlot;
class CPlotSpecification;
class CPlotSpec2Vector;
class CCopasiContainer;
class COutputHandlerPlot;
class CopasiUI3Window;
class QMenu;
class QAction;

class PlotWindow : public CWindowInterface, public COutputInterface
{
  Q_OBJECT

private:

  // points to the plot instance inside this window
  CopasiPlot *mpPlot;
  COutputHandlerPlot *mpHandler;
  CopasiUI3Window * mpMainWindow;
  QMenu* mpWindowMenu;

  QAction *mpaCloseWindow;
  QAction *mpaShowAll;
  QAction *mpaHideAll;
  QAction *mpaPrint;
  QAction *mpaSaveImage;
  QAction *mpaSaveData;
  QAction *mpaZoomOut;
  QAction *mpaToggleLogX;
  QAction *mpaToggleLogY;

  bool initializing;

  void createToolBar();
  void createMenus();
  void createActions();

public:
  PlotWindow(COutputHandlerPlot * pHandler, const CPlotSpecification* ptrSpec, CopasiUI3Window * pMainWindow);

  ~PlotWindow();

  bool initFromSpec(const CPlotSpecification* ptrSpec);

  CopasiPlot * getPlot() const;

  /**
   *
   * @return a pointer to this plot windows 'window' menu.
   */
  virtual QMenu *getWindowMenu() const;

  /**
   * compile the object list from name vector
   * @param std::vector< CCopasiContainer * > listOfContainer
   * @param  const CCopasiDataModel* pDataModel
   * @return bool success
   */
  virtual bool compile(std::vector< CCopasiContainer * > listOfContainer, const CCopasiDataModel* pDataModel);

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
   * Retrieve the list of objects handled by the interface
   * @return const std::set< const CCopasiObject * > & objects
   */
  virtual const std::set< const CCopasiObject * > & getObjects() const;

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

protected:
  virtual void closeEvent(QCloseEvent *closeEvent);
};
