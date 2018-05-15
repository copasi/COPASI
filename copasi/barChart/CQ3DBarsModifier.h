// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQ_3DBARS_MODIFIER_H
#define CQ_3DBARS_MODIFIER_H

#ifdef WITH_QT5_VISUALIZATION

#include <QtDataVisualization/q3dbars.h>
#include <QtDataVisualization/qbardataproxy.h>
#include <QtDataVisualization/qabstract3dseries.h>

#include <QtGui/QFont>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QPointer>
#include <QtCore/QPropertyAnimation>

class CDataArray;

class CQ3DBarsModifier : public QObject
{
  Q_OBJECT

public:
  explicit CQ3DBarsModifier(QtDataVisualization::Q3DBars *bargraph);
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
  void setSeriesVisibility(int enabled);
  void setReverseValueAxis(int enabled);
  void setReflection(bool enabled);

public slots:
  void changeRange(int range);
  void changeStyle(int style);
  void changeSelectionMode(int selectionMode);
  void changeTheme(int theme);
  void changeShadowQuality(int quality);
  void shadowQualityUpdatedByVisual(QtDataVisualization::QAbstract3DGraph::ShadowQuality shadowQuality);
  void changeLabelRotation(int rotation);
  void setAxisTitleVisibility(bool enabled);
  void setAxisTitleFixed(bool enabled);
  void zoomToSelectedBar();

signals:
  void shadowQualityChanged(int quality);
  void backgroundEnabledChanged(bool enabled);
  void gridEnabledChanged(bool enabled);
  void fontChanged(QFont font);
  void fontSizeChanged(int size);

private:
  QtDataVisualization::Q3DBars * m_graph;
  float m_xRotation;
  float m_yRotation;
  int m_fontSize;
  int m_segments;
  int m_subSegments;
  float m_minval;
  float m_maxval;
  QStringList mRowHeaders;
  QStringList mColHeaders;
  QtDataVisualization::QValue3DAxis *m_valueAxis;
  QtDataVisualization::QCategory3DAxis *m_rowAxis;
  QtDataVisualization::QCategory3DAxis *m_colAxis;
  QtDataVisualization::QBar3DSeries *m_primarySeries;
  QtDataVisualization::QAbstract3DSeries::Mesh m_barMesh;
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

#else

#include <QObject>

class CQ3DBarsModifier : public QObject
{
  Q_OBJECT
};

#endif // WITH_QT5_VISUALIZATION

#endif // CQ_3DBARS_MODIFIER_H
