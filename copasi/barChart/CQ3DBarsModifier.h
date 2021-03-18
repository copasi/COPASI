// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.




#ifndef CQ_3DBARS_MODIFIER_H
#define CQ_3DBARS_MODIFIER_H

#include <copasi/config.h>

#ifdef WITH_QT5_VISUALIZATION

#include <QtDataVisualization/q3dbars.h>
#include <QtDataVisualization/qbardataproxy.h>
#include <QtDataVisualization/qabstract3dseries.h>

#include <QtGui/QFont>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QPointer>
#include <QtCore/QPropertyAnimation>

#ifdef WITH_DATAVISUALIZATION_NAMESPACES
#      define DATAVIS_NS_PREFIX QtDataVisualization::
#else
#      define DATAVIS_NS_PREFIX
#endif

class CDataArray;
class CQCustomInputHandler;
class CQArrayAnnotationsWidget;

class CQ3DBarsModifier : public QObject
{
  Q_OBJECT

public:
  explicit CQ3DBarsModifier(CQArrayAnnotationsWidget * widget, DATAVIS_NS_PREFIX Q3DBars * bargraph);
  ~CQ3DBarsModifier();

  void clearData();
  void loadData(const CDataArray* pData, unsigned int rowIndex = 0, unsigned int colIndex = 1);
  void changePresetCamera();
  void changeLabelBackground();
  void changeFont(const QFont &font);
  void changeFontSize(int fontsize);
  void rotateX(int rotation);
  void rotateY(int rotation);
  void setBackgroundEnabled(int enabled);
  void setGridEnabled(int enabled);
  void setSmoothBars(int smooth);
  void setReverseValueAxis(int enabled);
  void setReflection(bool enabled);

public slots:
  void actionTriggered(QAction* action);
  void changeRange(int range);
  void changeStyle(int style);
  void changeSelectionMode(int selectionMode);
  void changeTheme(int theme);
  void changeShadowQuality(int quality);
  void shadowQualityUpdatedByVisual(DATAVIS_NS_PREFIX QAbstract3DGraph::ShadowQuality shadowQuality);
  void changeLabelRotation(int rotation);
  void setAxisTitleVisibility(bool enabled);
  void setAxisTitleFixed(bool enabled);
  void selectBar(int row, int col);
  void zoomToSelectedBar();
  void toggleGradient();

signals:
  void shadowQualityChanged(int quality);
  void backgroundEnabledChanged(bool enabled);
  void gridEnabledChanged(bool enabled);
  void fontChanged(QFont font);
  void fontSizeChanged(int size);

private:
  DATAVIS_NS_PREFIX Q3DBars * m_graph;
  CQCustomInputHandler* m_inputHandler;
  float m_xRotation;
  float m_yRotation;
  int m_fontSize;
  int m_segments;
  int m_subSegments;
  float m_minval;
  float m_maxval;
  QStringList mRowHeaders;
  QStringList mColHeaders;
  DATAVIS_NS_PREFIX QValue3DAxis * m_valueAxis;
  DATAVIS_NS_PREFIX QCategory3DAxis * m_rowAxis;
  DATAVIS_NS_PREFIX QCategory3DAxis * m_colAxis;
  DATAVIS_NS_PREFIX QBar3DSeries * m_primarySeries;
  DATAVIS_NS_PREFIX QAbstract3DSeries::Mesh m_barMesh;
  bool m_smooth;
  QPropertyAnimation m_animationCameraX;
  QPropertyAnimation m_animationCameraY;
  QPropertyAnimation m_animationCameraZoom;
  QPropertyAnimation m_animationCameraTarget;
  float m_defaultAngleX;
  float m_defaultAngleY;
  float m_defaultZoom;
  QVector3D m_defaultTarget;
};


#include <QtDataVisualization/QTouch3DInputHandler>

//using namespace QtDataVisualization;

class CQCustomInputHandler : public DATAVIS_NS_PREFIX QTouch3DInputHandler
{
  Q_OBJECT

  enum InputState
  {
    StateNormal = 0,
    StateScrolling
  };

public:
  explicit CQCustomInputHandler(DATAVIS_NS_PREFIX QAbstract3DGraph * graph, QObject * parent = 0);

  inline void setAxes(DATAVIS_NS_PREFIX QAbstract3DAxis * axisX,
                      DATAVIS_NS_PREFIX QAbstract3DAxis * axisY,
                      DATAVIS_NS_PREFIX QAbstract3DAxis * axisZ)
  {
    m_axisX = axisX;
    m_axisY = axisY;
    m_axisZ = axisZ;
  }

  virtual void mouseDoubleClickEvent(QMouseEvent *event);
  virtual void mousePressEvent(QMouseEvent *event, const QPoint &mousePos);
  virtual void mouseMoveEvent(QMouseEvent *event, const QPoint &mousePos);
  virtual void mouseReleaseEvent(QMouseEvent *event, const QPoint &mousePos);

signals:
  void signalShowContextMenu(const QPoint &);
  void signalBarDoubleClicked(int row, int col);

protected:
  DATAVIS_NS_PREFIX QAbstract3DGraph * m_graph;
  DATAVIS_NS_PREFIX QAbstract3DAxis * m_axisX;
  DATAVIS_NS_PREFIX QAbstract3DAxis * m_axisY;
  DATAVIS_NS_PREFIX QAbstract3DAxis * m_axisZ;
  QPoint mPosDown;
  InputState mState;
};


#else

#include <QObject>

class CQ3DBarsModifier : public QObject
{
  Q_OBJECT
};

#endif // WITH_QT5_VISUALIZATION

#endif // CQ_3DBARS_MODIFIER_H
