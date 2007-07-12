// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.h,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/07/12 14:26:38 $
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
//#include <qslider.h>
//#include <qwt_slider.h>

#include "CQGLNetworkPainter.h"

#include "CopasiDataModel/CCopasiDataModel.h"

class QwtSlider;

class CQLayoutMainWindow : public QMainWindow
  {

    Q_OBJECT      // must include this if you use Qt signals/slots

  public:
    CQLayoutMainWindow(QWidget *parent = 0, const char *name = 0);
    //CQLayoutMainWindow();
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
    CQGLNetworkPainter *glPainter;
    QScrollView *scrollView;
    //QSlider *timeSlider;
    QwtSlider *timeSlider;

    // mainBox contains topBox and bottomBox
    QHBox *bottomBox;
    //QHBoxLayout *bottomBox;
    QVBox *mainBox;
    //QWidget *mainWidget;
    //QWidget *bottomWidget;
  };

#endif /*SIMGUI_H_*/
