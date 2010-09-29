// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQNewMainWindow.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/09/29 13:45:04 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQNEWMAINWINDOW_H__
#define CQNEWMAINWINDOW_H__

#include <QMainWindow>
#include <QString>
#include <QIcon>
#include <string>

class CCopasiDataModel;
class CLayout;
class CLRenderInformationBase;
class CQLayoutMainWindow;
class CQGLLayoutViewer;
class QAction;
class QActionGroup;
class QCloseEvent;
class QComboBox;
class QMenu;
class QStackedWidget;
class QToolBar;

class CQNewMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  CQNewMainWindow(CCopasiDataModel* pDatamodel);

protected:
  void updateRenderer();

  void updateRenderInformationList();

  void addGlobalRenderInfoItemsToList();

  void addDefaultRenderInfoItemsToList();

  void change_style(bool defaultStyle = false);

  void resetView();

public slots:
  void slotLayoutChanged(int index);

private slots:
  void slotResetView();
  void slotRenderInfoChanged(int index);
  void slotZoomChanged(int index);
  void slotZoomMenuItemActivated(QAction*);

  /**
   * This slot is called when the selection is changed and
   * only a single curve is selected.
   */
  void slotSingleCurveSelected(bool selected);

  /**
   * This slot initiates the export
   * of the layout as a bitmap.
   * The user gets to choose which part of the
   * layout is to be exported and how large the
   * resulting bitmap is supposed to be.
   */
  void slotScreenshot();

  /**
   * Exports a bitmap of the given size to
   * the file with the given name.
   */
  void export_bitmap(const QString& filename, double x, double y, double width, double height, unsigned int imageWidth, unsigned int imageHeight, bool drawSelection);

  /**
   * Fills the layout dropdown list.
   */
  void updateLayoutList();

  /**
   * switches the display mode between animation mode and
   * graph mode.
   */
  void switchMode();

  /**
   * Change the status message.
   */
  void setStatusMessage(const QString& message, int timeout);

private:
  enum DISPLAY_MODE
  {
    GRAPH_MODE,
    ANIMATION_MODE
  };

  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void setAnimationToolbar();
  void setGraphToolbar();
  void setAnimationMenu();
  void setGraphMenu();

  DISPLAY_MODE mMode;
  QStackedWidget* mpWidgetStack;
  QMenu *mpFileMenu;
  QMenu *mpPlayMenu;
  QMenu *mpViewMenu;
  QMenu *mpOptionsMenu;
  QMenu *mpHelpMenu;
  QMenu *mpZoomMenu;
  QToolBar *mpFileToolBar;
  QToolBar *mpSelectionToolBar;
  QAction *mpSwitchModeAct;
  QAction *mpRevertCurveAct;
  QAction *mpCloseAct;
  QAction *mpScreenshotAct;
  QAction *mpLoadDataAct;
  QAction *mpCircularShape;
  QAction *mpRectangularShape;
  QAction *mpMimaNodeSizes;
  QAction *mpSFontSize;
  QAction* mpLoopItemAction;
  QActionGroup* mpZoomActionGroup;
  CQGLLayoutViewer* mpLayoutViewer;
  CQLayoutMainWindow* mpAnimationWindow;
  CCopasiDataModel* mpDataModel;
  QComboBox* mpLayoutDropdown;
  QComboBox* mpRenderDropdown;
  QComboBox* mpZoomDropdown;
  CLayout* mpCurrentLayout;
  CLRenderInformationBase* mpCurrentRenderInformation;
  bool mDocumentChanged;

  static const char* const ZOOM_FACTOR_STRINGS[];
  static const double ZOOM_FACTORS[];

  std::string mCurDir;

  QIcon mGraphIcon;
  QIcon mAnimationIcon;
};

#endif /* CQNEWMAINWINDOW_H__ */
