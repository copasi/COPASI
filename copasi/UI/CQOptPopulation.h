// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QtGui/QToolButton>

#include "copasi/copasi.h"
#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/UI/CWindowInterface.h"
#include "copasi/utilities/COutputHandler.h"

class CCopasiContainer;
class CopasiUI3Window;
class QMenu;
class QAction;

class CQOptPopulation : public CWindowInterface, public COutputInterface
{
  Q_OBJECT

private:
  COutputHandler *mpHandler;

  CopasiUI3Window * mpMainWindow;
  QMenu* mpWindowMenu;

  QToolBar * mpToolBar;
  QAction *mpaCloseWindow;

  bool initializing;

  void createToolBar();
  void createMenus();
  void createActions();

public:
  CQOptPopulation(COutputHandler * pHandler,  CopasiUI3Window * pMainWindow);

  virtual ~CQOptPopulation();

  bool initFromSpec();


  /**
   *
   * @return a pointer to this plot windows 'window' menu.
   */
  virtual QMenu *getWindowMenu() const;

  /**
   * compile the object list from name vector
   * @param CObjectInterface::ContainerList listOfContainer
   * @param  const CCopasiDataModel* pDataModel
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

  /// Save data into a file
  void slotSaveData();
  void slotCloseWindow();


protected:
  virtual void closeEvent(QCloseEvent *closeEvent);
};
