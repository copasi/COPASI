// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQNewMainWindow.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/03/11 21:21:15 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQNEWMAINWINDOW_H__
#define CQNEWMAINWINDOW_H__

#include <QMainWindow>
#include <QString>
#include <QIcon>
#include <string>
#include <vector>
#include <set>

#include <copasi/copasi.h>
#include <copasi/layout/CLReactionGlyph.h>

class CCopasiDataModel;
class CLayout;
class CLRenderInformationBase;
class CQLayoutMainWindow;
class CQGLLayoutViewer;
class QAction;
class QActionGroup;
class QCloseEvent;
class QComboBox;
class QLabel;
class QMenu;
class QStackedWidget;
class QToolBar;
class CFluxMode;

#ifdef COPASI_AUTOLAYOUT
class CCompartment;
class CCopasiObject;
class CLayout;
class CMetab;
class CModel;
class CReaction;
class CLCompartmentGlyph;
class CLMetabGlyph;
class CLTextGlyph;
#endif // COPASI_AUTOLAYOUT

class CQNewMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  CQNewMainWindow(CCopasiDataModel* pDatamodel);

  void updateRenderer();
protected:

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

#ifdef COPASI_DEBUG
  /**
   * Is called when the menu entry for toggling highlighting
   * of elementary modes is toggled.
   */
  void toggleHighlightSlot(bool checked);

  /**
   * Checks for calculated elementary modes.
   */
  void checkForElementaryModesSlot();

  /**
   * Checks which elementary mode has been toggled and updates the
   * highlighted objects list.
   */
  void elementaryModeTriggeredSlot(QAction* pAction);

  /**
   * This slot is triggered when the user wants to change
   * the fog or the highlighting color, depending on the current
   * highlighting mode.
   */
  void changeColorSlot(bool);

#endif // COPASI_DEBUG

#ifdef COPASI_AUTOLAYOUT
  virtual void closeEvent(QCloseEvent * event);

  /**
   * Creates a CLMetabGlyph for the given CMetab object.
   * If the creation failed, a NULL pointers is returned.
   */
  static CLMetabGlyph* createMetabGlyph(const std::string& modelobjectkey, double width, double height);

  /**
   * Creates a CLTextGlyph for the given graphical object keys and size.
   */
  static CLTextGlyph* createTextGlyph(const std::string& modelobjectkey, const std::string& objectkey, double width, double height);

  /**
   * Creates a CLCompartmentGlyph for the given size and position
   */
  static CLCompartmentGlyph* createCompartmentGlyph(const std::string& modelobjectkey, double x, double y, double width, double height);

  /**
   * Creates a CLReactionGlyph for the given size and position
   */
  static CLReactionGlyph* createReactionGlyph(const std::string& modelobjectkey, double x, double y, double length);

  /**
   * Creates a CLMetabReferenceGlyph for the given endpoints.
   */
  static CLMetabReferenceGlyph* createMetabReferenceGlyph(const std::string& modelobjectkey, const std::string& metabglyphkey, CLMetabReferenceGlyph::Role role, double x1, double y1, double x2, double y2);

protected slots:
  /**
   * This slot is called when the stop button is presed.
   * It notifies the layout method to stop the spring layout iterations.
   */
  void slotStopClicked();

  void slotRunSpringLayout();
#endif // COPASI_AUTOLAYOUT 


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
#ifdef COPASI_DEBUG
  QMenu *mpElementaryModesMenu;
#endif // COPASI_DEBUG
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
  QLabel* mpRenderLabel;
  CLRenderInformationBase* mpCurrentRenderInformation;
  bool mDocumentChanged;

  static const char* const ZOOM_FACTOR_STRINGS[];
  static const double ZOOM_FACTORS[];

  std::string mCurDir;

  QIcon mGraphIcon;
  QIcon mAnimationIcon;
#ifdef COPASI_DEBUG
  // It does not make sense to update
  // the elementary flux modes menu each time
  // because that will delete the information about
  // selected modes.
  // We have to remember the modes and only update if necessary.
  std::vector<const CFluxMode*> mFluxModes;

  // we need two icons for the fog and
  // the highlight color
  QPixmap* mpFogColorPixmap;
  QPixmap* mpHighlightColorPixmap;
  QAction* mpHighlightModeAction;
  QAction* mpChangeColorAction;
#endif // COPASI_DEBUG

#ifdef COPASI_AUTOLAYOUT
  // a flag that determines if the iterations
  // of the random layout should be stopped
  bool mStopLayout;

  QAction* mpStopLayoutAction;

public:
  void redrawNow();

  /**
   * This method creates a random layout using the elements
   * in the compartments, reactions, species and side species
   * containers.
   */
  void createRandomLayout(const std::set<const CCompartment*>& compartments,
                          const std::set<const CReaction*>& reactions,
                          const std::set<const CMetab*>& metabs,
                          const std::set<const CMetab*>& sideMetabs
                         );

  /**
   * Creates a spring layout.
   * The method takes the number of iterations for the
   * layout algorithm and an update interval which tells the algorithm
   * how often to update the display.
   * A value of -1 means that the update of the display is only done once
   * at the end.
   */
  void createSpringLayout(int numIterations, int updateInterval);
#endif // COPASI_AUTOLAYOUT

};

#endif /* CQNEWMAINWINDOW_H__ */
