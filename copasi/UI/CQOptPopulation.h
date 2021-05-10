// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <fstream>
#include <string>
#include <vector>
#include <QToolButton>
#include <QGraphicsScene>
#include <QMutex>

#include "copasi/copasi.h"
#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/UI/CWindowInterface.h"
#include "copasi/UI/CColorScale.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/core/CVector.h"
#include "copasi/utilities/CopasiTime.h"

class CDataContainer;
class CopasiUI3Window;
class QMenu;
class QAction;
class QLabel;
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
  std::vector< C_FLOAT64 > mObjectiveValues;


  bool mDataInitialized;
  bool mGraphInitialized;
  bool mDidAllocate;
  bool mInUpdate;

  bool initializing;

  C_INT32 mNumParameters;
  std::vector<C_FLOAT64> mRangeMin;
  std::vector<C_FLOAT64> mRangeMax;
  std::vector<bool> mIsLog;

  std::vector< std::vector<C_FLOAT64> > mScaledData;

  QGraphicsScene * mpGS;
  QGraphicsView * mpGV;

  //list of list of graphics items. The outer list allows for several projections simultaneously
  //the inner list enumerates graphical representations of the individual parameter sets in the population
  std::vector< std::vector<QGraphicsItem *> > mGraphicItems;
  std::vector< std::vector< QGraphicsItem * > > mLineItems;

  //These are coordinate shifts that specify where on the plane the different projections are located
  std::vector<double> mShiftX;
  std::vector<double> mShiftY;

  std::vector<C_INT32> mXIndex;
  std::vector<C_INT32> mYIndex;

  qreal mDiameter;
  QAction * mpaRefresh;
  QAction * mpaDecreaseCircle;
  QAction * mpaIncreaseCircle;
  QAction * mpaResetCircle;
  QAction * mpaSaveToFile;

  CColorScaleAuto mCS;
  C_INT32 mMinIndex = 0;
  C_INT32 mMaxIterations = 500;
  QMutex mMutex;
  CCopasiTimeVariable mNextPlotTime;
  QLabel * mpLabel;

  void createToolBar();
  void createMenus();
  void createActions();
  void setCircle(qreal diameter);

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

  void slotFullRefresh();
  /// Save data into a file
  void slotSaveData();
  void slotCloseWindow();
  void slotResizeCircle();
  void slotSaveImage();

public slots:
  virtual void update();

protected:
  virtual void closeEvent(QCloseEvent *closeEvent);

signals:
  void updateSignal();
  void setDebugText(QString str);
};
