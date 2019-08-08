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

#ifndef CQNEWMAINWINDOW_H__
#define CQNEWMAINWINDOW_H__

#include <copasi/UI/CWindowInterface.h>
#include <QtCore/QString>
#include <QIcon>
#include <QtCore/QRectF>
#include <string>
#include <vector>
#include <set>

class CDataModel;
class CLayout;
class CLRenderInformationBase;
class CLGraphicalObject;
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
class CReaction;
class CMetab;

#include "copasi/copasi.h"
#include "copasi/layout/CLayoutState.h"
#include "copasi/layout/CLReactionGlyph.h"
#include "copasi/layout/CCopasiSpringLayout.h"

class CCompartment;
class CDataObject;
class CLayout;
class CModel;
class CLCompartmentGlyph;
class CLMetabGlyph;
class CLTextGlyph;
class CQLayoutThread;

class CQNewMainWindow : public CWindowInterface
{
  Q_OBJECT

public:

  enum DISPLAY_MODE
  {
    GRAPH_MODE,
    ANIMATION_MODE
  };

  void setMode(DISPLAY_MODE mode = GRAPH_MODE);

  enum REACTION_SELECTION_BITS
  {
    ROLE_UNSPECIFIED          =   1 // metab reference glyphs without role
                                  , ROLE_SUBSTRATE            =   2
                                      , ROLE_SIDESUBSTRATE        =   4
                                          , ROLE_PRODUCT              =   8
                                              , ROLE_SIDEPRODUCT          =  16
                                                  , ROLE_MODIFIER             =  32
                                                      , ROLE_ACTIVATOR            =  64
                                                          , ROLE_INHIBITOR            = 128
                                                              , REACTION_GLYPH            = 256 // the reaction glyph itself
                                                                  , ASSOCIATED_SPECIES_GLYPHS = 512
  };

  CQNewMainWindow(CDataModel* pDatamodel);
  virtual ~CQNewMainWindow();

  virtual QMenu *getWindowMenu() const;

  void updateRenderer();
protected:

  void updateRenderInformationList();

  void addGlobalRenderInfoItemsToList();

  void addDefaultRenderInfoItemsToList();

  void change_style(bool defaultStyle = false);

  void resetView();

public slots:
  void slotLayoutChanged(int index);

  void slotResetView();

  /**
   * This slot is called when the "Fit To Screen" menu item
   * is activated.
   */
  void slotFitToScreen();

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
   * exports a bit map of the currently displayed image with the given scale.
   */
  void export_bitmap(const QString& filename, double scale = 4.0);

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

  /**
   * Selects the given reaction object by selecting all
   * corresponding CLReactionGlyph objects in the current layout.
   * The mask determines which parts of the reaction are selected.
   * With this, it can be specified that only the reaction glyph itself
   * or the reaction glyph plus several of the associated metab reference glyphs
   * are selected.
   * The graphical objects selected by this method are inserted into the
   * set given as the third element.
   */
  void selectReaction(const CReaction* pReaction, unsigned int selectionMask, std::set<const CLGraphicalObject*>& s);

  /**
   * Selected the given metabolite object by selecting all
   * corresponding CLMetabGlyph objects in the current layout.
   * The graphical objects selected by this method are inserted into the
   * set given as the third element.
   */
  void selectMetabolite(const CMetab* pMetab, std::set<const CLGraphicalObject*>& s);

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

  /**
   * Lets the user change the percentage of fog
   * that is added to the color.
   */
  void fogDensitySlot(bool);

  virtual void closeEvent(QCloseEvent * event);

#ifdef INCLUDE_UNUSED_CODE

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
  static CLMetabReferenceGlyph* createMetabReferenceGlyph(const std::string& modelobjectkey,
      const std::string& metabglyphkey,
      CLMetabReferenceGlyph::Role role,
      double x1, double y1, double x2, double y2);
#endif //INCLUDE_UNUSED_CODE

public slots:
  void slotRunSpringLayout();

protected slots:
  /**
   * This slot is called when the stop button is presed.
   * It notifies the layout method to stop the spring layout iterations.
   */
  void slotStopClicked();

  void slotRunRandomizeLayout();

  void slotCalculateDimensions();

private:

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
  QMenu *mpLayoutMenu;
  QMenu *mpViewMenu;
  QMenu *mpOptionsMenu;
  QMenu *mpWindowMenu;
  QMenu *mpZoomMenu;
  QMenu *mpElementaryModesMenu;
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
  CDataModel* mpDataModel;
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

  struct REACTION_SELECTION_ITEM
  {
    std::string mReactionKey;
    unsigned int mSelectionMask;

    bool operator<(const REACTION_SELECTION_ITEM& other) const
    {
      // The reaction key needs to be unique.
      // There should be no two entries with the same key.
      bool result = (this->mReactionKey < other.mReactionKey);
      return result;
    }
  };

  // we need to store the highlighted reactions and the
  // highlighted metabolites in two different structures
  // because the reaction highlighting mechanism is a bit
  // more complicated
  std::set<std::string> mHighlightedMetabolites;
  std::set<REACTION_SELECTION_ITEM> mHighlightedReactions;

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
  QAction* mpFogDensityAction;
  QAction* mpChangeColorAction;

  QAction* mpStopLayoutAction;
  QAction* mpRandomizeLayout;
  QAction* mpCalculateDimensions;

public slots:
  void slotLayoutFinished();
  void slotLayoutStateChanged(QSharedPointer<CLayoutState> state);

public:
  void redrawNow();

  void randomizeLayout();

  /**
   * Creates a spring layout.
   * The method takes the number of iterations for the
   * layout algorithm and an update interval which tells the algorithm
   * how often to update the display.
   * A value of -1 means that the update of the display is only done once
   * at the end.
   */
  void createSpringLayout(int numIterations, int updateInterval);

  // Help a descendant get to it's potential CQNewMainWindow
  // ancestor (e.g. to figure out mpDataModel)
  static CQNewMainWindow * ancestor(QObject * qObject);

  // convenience function to find/return the CDataModel
  // from the/a CQNewMainWindow ancestor of a QObject
  static CDataModel * dataModel(QObject * qObject);

  CDataModel * getDataModel() const;

protected:
  /** the layout thread */
  CQLayoutThread* mpLayoutThread;

  /** the copy on which the layout operates */
  CLayout* mpCopy;
};

#endif /* CQNEWMAINWINDOW_H__ */
