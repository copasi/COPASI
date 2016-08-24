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
#include <QTGui/QGraphicsScene>

#include "copasi/copasi.h"
#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/UI/CWindowInterface.h"
#include "copasi/utilities/COutputHandler.h"
#include "copasi/utilities/CVector.h"
class CCopasiContainer;
class CopasiUI3Window;
class QMenu;
class QAction;
class COptMethod;
class COptPopulationMethod;

class CQOptPopulation : public CWindowInterface, public COutputInterface
{
  Q_OBJECT

private:
  COutputHandler *mpHandler;

  CopasiUI3Window * mpMainWindow;
  QMenu* mpWindowMenu;

  QToolBar * mpToolBar;
  QAction *mpaCloseWindow;
  
  COptMethod * mpSourceMethod;
  COptPopulationMethod * mpPopulationMethod;
  
  C_INT32 mCounter;
  
  std::vector< CVector < C_FLOAT64 > * > mPopulation;
  CVector<C_FLOAT64> mObjectiveValues;
  
  bool mDataInitialized;
  bool mGraphInitialized;
  

  bool initializing;
  
  C_INT32 mNumParameters;
  std::vector<C_FLOAT64> mRangeMin;
  std::vector<C_FLOAT64> mRangeMax;
  std::vector<bool> mIsLog;
  
  
  std::vector< std::vector<C_FLOAT64> > mScaledData;

  QGraphicsScene * mpGS;
  QGraphicsView * mpGV;
  

  void createToolBar();
  void createMenus();
  void createActions();

public:
  CQOptPopulation(COutputHandler * pHandler,  CopasiUI3Window * pMainWindow);

  virtual ~CQOptPopulation();

  bool initFromSpec();

  ///set the method that is the data source
  void setMethod(COptMethod* pMethod);

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

public slots:
  virtual void update();


protected:
  virtual void closeEvent(QCloseEvent *closeEvent);
  
signals:
  void updateSignal();
  
};
