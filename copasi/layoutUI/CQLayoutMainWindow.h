// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/05/31 19:40:14 $
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
#include <qslider.h>

#include "CQGLNetworkPainter.h"

#include "CopasiDataModel/CCopasiDataModel.h"

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

    void showStep(int i);

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
    QSlider *timeSlider;
  };

#endif /*SIMGUI_H_*/
