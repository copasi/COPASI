// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/02/26 10:31:07 $
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

#include "CQGLNetworkPainter.h"

#include "CopasiDataModel/CCopasiDataModel.h"

class CQLayoutMainWindow : public QMainWindow
  {

    Q_OBJECT

  public:
    CQLayoutMainWindow(QWidget *parent = 0, const char *name = 0);
    //CQLayoutMainWindow();
  protected:
    void closeEvent(QCloseEvent *event);
    //void contextMenuEvent(QContextMenuEvent *event);

  private slots:
    void loadSBMLFile();
    void loadDataFile();
    void exitApplication();

  private:
    void createActions();
    void createMenus();
    bool maybeSave();

    QPopupMenu *fileMenu;

    QAction *openSBMLFile;
    QAction *openDataFile;
    QAction *exitAction;

    CQGLNetworkPainter *glPainter;
    QScrollView *scrollView;
  };

#endif /*SIMGUI_H_*/
