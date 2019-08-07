// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SIMGUI_H_
#define SIMGUI_H_

#include <QtCore/QObject>

#include <QFrame>
#include <QtCore/QString>
#include <QIcon>

#include <string>

#include "CDataEntity.h"
#include "CVisParameters.h"
#include "copasi/copasi.h"

class CLayout;
class CQCurrentValueTable;
class CQGLViewport;
class CQParaPanel;
class CQPlayerControlWidget;
class CVisParameters;
class QAction;
class QActionGroup;
class QCloseEvent;
class QComboBox;
class QFrame;
class QMenu;
class QSplitter;
class QToolBar;
class QSlider;
class QFrame;
class QToolBar;
class CLayout;
class CQPlayerControlWidget;
class QCloseEvent;

class CQLayoutMainWindow : public QFrame
{

  Q_OBJECT      // must include this if you use Qt signals/slots

public:
  CQLayoutMainWindow(QWidget* pParent);
  void setLayout(CLayout* pLayout);
  CQPlayerControlWidget* getControlWidget();
  void setIndividualScaling();
  void setGlobalScaling();
  void setSizeMode();
  void setColorMode();
  void setValueOnSlider(C_INT32);
  void insertValueTable(CDataEntity dataSet);
  void updateValueTable(CDataEntity dataSet);
  void setMinValue(C_INT32 minNdSize); // set minimum possible node size
  void setMaxValue(C_INT32 maxNdSize); // set maximum possible node size
  void setMinAndMaxValue(C_INT32 minNdSize, C_INT32 maxNdSize);
  void setFontSizeForLabels(C_INT32 size);
  bool getAnimationRunning();
  void setAnimationRunning(bool animationRunningP);
  void setMinNodeSize(C_FLOAT64 minNdSize);
  void setMaxNodeSize(C_FLOAT64 minNdSize);
  C_FLOAT64 getMinNodeSize();
  C_FLOAT64 getMaxNodeSize();
  C_INT32 getStepsPerSecond();
  void setStepsPerSecond(C_INT16 val);
  CVisParameters::SCALING_MODE getScalingMode();
  CVisParameters::MAPPING_MODE getMappingMode();
  C_INT16 getFontSize();
  size_t getCurrentStep();
  void addItemInAnimation(std::string s);
  void removeItemInAnimation(std::string s);

  static const char* const ZOOM_FACTOR_STRINGS[];
  static const double ZOOM_FACTORS[];

protected:

public:
  void setZoomFactor(QString s);
  void setZoomFactor(double zoom);

private slots:
  void loadSBMLFile();
  void showAnimation();
  void showStep(int i);
  void startAnimation();
  void pauseAnimation();
  void stopAnimation();
  void forwardAnimation();
  void backwardAnimation();
  void stepForwardAnimation();
  void stepBackwardAnimation();
  void parameterTableValueChanged(int row);

// for the new code we need the following slots to be public
// so that we can use them from the new main window class
public slots:
  void slotResetView();

  /**
   * Make the layout fit the screen.
   */
  double slotFitToScreen();
  void loadData();
  void saveImage();
  void mapLabelsToCircles();
  void mapLabelsToRectangles();
  void changeMinMaxNodeSizes();
  void changeFontSize();
  void slotValueTableToggled(bool checked);
  void slotParameterTableToggled(bool checked);
  void slotPlayerControlToggled(bool checked);
  void slotToolbarToggled(bool checked);
  void slotLoopActivated(bool checked);

public slots:
  void changeStepValue(int i);
  void endOfAnimationReached();

private:
  bool maybeSave();
  QIcon createStartIcon();
  QIcon createStopIcon();

  CVisParameters *mpVisParameters;
  QMenu *mpFileMenu;
  QMenu *mpOptionsMenu;
  QMenu *mpLabelShapeMenu;
  QMenu *mpViewMenu;
  QMenu *mpZoomMenu;
  QMenu *mpPlayMenu;

  QAction *mpCreatePicture;
  QAction *mpOpenSBMLFile;
  QAction *mpCloseAction;
  QAction *mpRectangularShape;
  QAction *mpCircularShape;
  QAction *mpMimaNodeSizes;
  QAction *mpSFontSize;
  QAction *mpLoadDataAction;

  CQParaPanel *mpParaPanel;
  CQCurrentValueTable *mpValTable;
  QFrame *mpMainBox;
  QSplitter* mpSplitter;
  CQGLViewport *mpGLViewport;
  QSlider *mpTimeSlider;

  QFrame *mpFrame;

  QFrame *mpInfoBox;

  CQPlayerControlWidget* mpControlWidget;

  bool mDataPresent; // shows whether time series data already load
  QString mCurrentPlace;
  QToolBar* mpToolbar;
  QComboBox* mpZoomComboBox;
  bool mLooping;
  QAction* mpLoopItemAction;
  QAction* mpValueTableAction;
  QAction* mpParameterTableAction;
  QActionGroup* mpZoomActionGroup;
  CLayout* mpLayout;
};

#endif /*SIMGUI_H_*/
