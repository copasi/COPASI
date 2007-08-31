// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.h,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/08/31 10:56:28 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include <qscrollview.h>
#include <qsplitter.h>
#include <qlayout.h>
#include <qwidget.h>
#include <qhbox.h>
#include <qvbox.h>
#include <qpushbutton.h>
#include <qiconset.h>
#include <qpixmap.h>
#include <qimage.h>
//#include <qlayout.h>
//#include <qslider.h>
//#include <qwt_slider.h>

//#include "CQGLNetworkPainter.h"
#include "ParaPanel.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "layoutUI/CVisParameters.h"

class QwtSlider;
class CQGLNetworkPainter;

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

    CVisParameters *pVisParameters;
    bool getAnimationRunning();
    void setAnimationRunning(bool animationRunningP);
    C_FLOAT64 getMinNodeSize();
    C_FLOAT64 getMaxNodeSize();
    C_INT32 getStepsPerSecond();
    void setStepsPerSecond(C_INT16 val);
    C_INT16 getScalingMode();
    C_INT16 getMappingMode();

  protected:
    void closeEvent(QCloseEvent *event);
    //void contextMenuEvent(QContextMenuEvent *event);

  private slots:
    void loadSBMLFile();
    void loadData();
    void showAnimation();
    void closeApplication();

    void mapLabelsToCircles();
    void mapLabelsToRectangles();

    void showStep(double i);
    void startAnimation();
    void stopAnimation();

  public slots:
    void changeStepValue(C_INT32 i);
    void endOfAnimationReached();

  private:
    void createActions();
    void createMenus();
    bool maybeSave();

    QPopupMenu *fileMenu;
    QPopupMenu *actionsMenu;
    QPopupMenu *optionsMenu;
    QPopupMenu *labelShapeMenu;

    QAction *runAnimation;
    QAction *openSBMLFile;
    QAction *openDataFile;
    QAction *closeAction;

    QAction *rectangularShape;
    QAction *circularShape;

    //CQParameterWindow *paraWin;
    ParaPanel *paraPanel;
    CQGLNetworkPainter *glPainter;
    QScrollView *scrollView;
    //QSlider *timeSlider;
    QwtSlider *timeSlider;

    QHBox *bottomBox;
    QVBox *mainBox;

    QPushButton *startStopButton;
    QIconSet startIcon;
    QIconSet stopIcon;

    QIconSet createStartIcon();
    QIconSet createStopIcon();
  };

#endif /*SIMGUI_H_*/
