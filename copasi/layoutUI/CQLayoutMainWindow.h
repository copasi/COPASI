// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.h,v $
//   $Revision: 1.38 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/04 08:33:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SIMGUI_H_
#define SIMGUI_H_
#include <qaction.h>
#include <qmainwindow.h>
#include <qapplication.h>
#include <qfiledialog.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qgl.h>
#include <qlayout.h>
//#include <qscrollview.h>
#include <qsplitter.h>
#include <qlayout.h>
#include <qwidget.h>
#include <qhbox.h>
#include <qvbox.h>
#include <qframe.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qiconset.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qevent.h>
#include <qtoolbar.h>
//#include <qlayout.h>
//#include <qslider.h>
//#include <qwt_slider.h>

//#include "CQGLNetworkPainter.h"
#include "copasi/layoutUI/ParaPanel.h"
#include "copasi/layoutUI/CQCurrentValueTable.h"

#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/layoutUI/CVisParameters.h"
#include "copasi/layoutUI/CDataEntity.h"

#include <string>

class QwtSlider;
class CQGLViewport;
class QSplitter;
class QComboBox;

class CQLayoutMainWindow : public QMainWindow
  {

    Q_OBJECT      // must include this if you use Qt signals/slots

  public:
    CQLayoutMainWindow(QWidget *parent = 0, const char *name = 0);
    //CQLayoutMainWindow();
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

    CVisParameters *pVisParameters;
    bool getAnimationRunning();
    void setAnimationRunning(bool animationRunningP);
    void setMinNodeSize(C_FLOAT64 minNdSize);
    void setMaxNodeSize(C_FLOAT64 minNdSize);
    C_FLOAT64 getMinNodeSize();
    C_FLOAT64 getMaxNodeSize();
    C_INT32 getStepsPerSecond();
    void setStepsPerSecond(C_INT16 val);
    C_INT16 getScalingMode();
    C_INT16 getMappingMode();
    C_INT16 getFontSize();

    C_INT32 getCurrentStep();

    void addItemInAnimation (std::string s);
    void removeItemInAnimation (std::string s);

  protected:
    void closeEvent(QCloseEvent *event);
    void setZoomFactor(std::string s);

  private slots:
    void loadSBMLFile();
    void loadData();
    void showAnimation();
    void saveImage();
    void closeApplication();

    void mapLabelsToCircles();
    void mapLabelsToRectangles();

    void changeMinMaxNodeSizes();
    void changeFontSize();

    void showStep(double i);
    void startAnimation();
    void stopAnimation();
    void checkAllCheckboxesInTable();
    void uncheckAllCheckboxesInTable();

    void slotResetView();
    void slotZoomItemActivated(int id);

  public slots:
    void changeStepValue(C_INT32 i);
    void endOfAnimationReached();
    void slotActivated(int);

  private:
    void createActions();
    void createMenus();
    bool maybeSave();

    QPopupMenu *mpFileMenu;
    QPopupMenu *mpActionsMenu;
    QPopupMenu *mpOptionsMenu;
    QPopupMenu *mpLabelShapeMenu;
    QPopupMenu *mpViewMenu;
    QPopupMenu *mpZoomMenu;

    QAction *mpRunAnimation;
    QAction *mpCreatePicture;
    QAction *mpOpenSBMLFile;
    QAction *mpCloseAction;

    QAction *mpRectangluarShape;
    QAction *mpCircularShape;

    QAction *mpMimaNodeSizes;
    QAction *mpSFontSize;
    //QAction *automaticRescaleToggle;

    ParaPanel *paraPanel;
    CQCurrentValueTable *valTable;
    CQGLViewport *mpGLViewport;
    QSplitter* mpSplitter;
    QwtSlider *timeSlider;

    QFrame *frame;
    QVBox *mainBox;

    QVBox *infoBox;

    QPushButton *startStopButton;
    QIconSet startIcon;
    QIconSet stopIcon;

    QIconSet createStartIcon();
    QIconSet createStopIcon();

    bool dataPresent; // shows whether time series data already load
    QString currentPlace;
    QToolBar* mpToolbar;
    QComboBox* mpZoomComboBox;
  };

#endif /*SIMGUI_H_*/
