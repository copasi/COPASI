#ifndef QLAYOUT_VIEW_H
#define QLAYOUT_VIEW_H

#include <QGraphicsView>

class QLayoutScene;
class QAction;
class QMenu;
class QToolBar;
class QComboBox;
class CCopasiDataModel;

class QLayoutView: public QGraphicsView
{
  Q_OBJECT
public:
  QLayoutView(QWidget*parent=NULL);
  QLayoutView(QLayoutScene *scene);
  virtual ~QLayoutView();  
  void fillZoomMenu(QMenu* menu);
  void fillZoomTooBar(QToolBar* toolBar);
  void fillSelectionToolBar(QToolBar* toolBar);
  void setDataModel(CCopasiDataModel* dataModel);
  CCopasiDataModel* getDataModel();

public slots:
  void slotFitOnScreen();
  void slotResetZoom();
  void slotZoomIn();
  void slotZoomOut();
  void slotSaveToFile(const QString& fileName);
  void slotLayoutChanged(int);
  void slotRenderInformationChanged(int);

protected:
  void wheelEvent ( QWheelEvent* event );

  QAction* mpActZoomIn;
  QAction* mpActZoomOut;
  QAction* mpActFitOnScreen;
  QAction* mpActResetZoom;
  double   mScaleFactor;
  QComboBox* mpLayoutDropdown;
  QComboBox* mpRenderDropdown;
  bool mIgnoreEvents;
  CCopasiDataModel* mpDataModel;

private: 
  void createActions();
};

#endif