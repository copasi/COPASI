// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.


#include  "CQ3DBarsModifier.h"

#ifdef WITH_QT5_VISUALIZATION


#include <QtDataVisualization/q3dbars.h>
#include <QtDataVisualization/qbardataproxy.h>
#include <QtDataVisualization/qabstract3dseries.h>

#include <QFont>
#include <QDebug>
#include <QStringList>
#include <QPointer>
#include <QPropertyAnimation>

using namespace QtDataVisualization;


#include <QtDataVisualization/qcategory3daxis.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/qbardataproxy.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qbar3dseries.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QTime>
#include <QComboBox>
#include <qmath.h>

#include <copasi/core/CDataArray.h>

#include <copasi/ui/qtUtilities.h>

using namespace QtDataVisualization;

//! [0]
CQ3DBarsModifier::CQ3DBarsModifier(Q3DBars *bargraph)
  : m_graph(bargraph),
    m_xRotation(0.0f),
    m_yRotation(0.0f),
    m_fontSize(30),
    m_segments(4),
    m_subSegments(3),
    m_minval(-1.0f),
    m_maxval(1.0f),
    //! [1]
    m_valueAxis(new QValue3DAxis),
    m_rowAxis(new QCategory3DAxis),
    m_colAxis(new QCategory3DAxis),
    m_primarySeries(new QBar3DSeries),
    //! [1]
    m_barMesh(QAbstract3DSeries::MeshBar),
    m_smooth(false)
{
  //! [2]
  m_graph->activeTheme()->setType(Q3DTheme::ThemeArmyBlue);
  m_graph->activeTheme()->setBackgroundEnabled(false);
  m_graph->activeTheme()->setLabelBackgroundEnabled(true);
  m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
  m_graph->setMultiSeriesUniform(true);

  //! [3]
  m_valueAxis->setSegmentCount(m_segments);
  m_valueAxis->setSubSegmentCount(m_subSegments);
  m_valueAxis->setRange(m_minval, m_maxval);
  m_valueAxis->setLabelFormat(QString(QStringLiteral("%.1f ")));
  m_valueAxis->setLabelAutoRotation(30.0f);
  m_valueAxis->setTitleVisible(false);

  m_rowAxis->setLabelAutoRotation(30.0f);
  m_rowAxis->setTitleVisible(false);
  m_colAxis->setLabelAutoRotation(30.0f);
  m_colAxis->setTitleVisible(false);

  m_graph->setValueAxis(m_valueAxis);
  m_graph->setRowAxis(m_rowAxis);
  m_graph->setColumnAxis(m_colAxis);
  //! [3]

  //! [8]
  m_primarySeries->setItemLabelFormat(QStringLiteral("@rowLabel, @colLabel : @valueLabel"));
  m_primarySeries->setMesh(QAbstract3DSeries::MeshBar);
  m_primarySeries->setMeshSmooth(false);

  m_graph->addSeries(m_primarySeries);

  changePresetCamera();

  clearData();

  // Set up property animations for zooming to the selected bar
  //! [12]
  Q3DCamera *camera = m_graph->scene()->activeCamera();
  m_defaultAngleX = camera->xRotation();
  m_defaultAngleY = camera->yRotation();
  m_defaultZoom = camera->zoomLevel();
  m_defaultTarget = camera->target();

  m_animationCameraX.setTargetObject(camera);
  m_animationCameraY.setTargetObject(camera);
  m_animationCameraZoom.setTargetObject(camera);
  m_animationCameraTarget.setTargetObject(camera);

  m_animationCameraX.setPropertyName("xRotation");
  m_animationCameraY.setPropertyName("yRotation");
  m_animationCameraZoom.setPropertyName("zoomLevel");
  m_animationCameraTarget.setPropertyName("target");

  int duration = 1700;
  m_animationCameraX.setDuration(duration);
  m_animationCameraY.setDuration(duration);
  m_animationCameraZoom.setDuration(duration);
  m_animationCameraTarget.setDuration(duration);

  // The zoom always first zooms out above the graph and then zooms in
  qreal zoomOutFraction = 0.3;
  m_animationCameraX.setKeyValueAt(zoomOutFraction, QVariant::fromValue(0.0f));
  m_animationCameraY.setKeyValueAt(zoomOutFraction, QVariant::fromValue(90.0f));
  m_animationCameraZoom.setKeyValueAt(zoomOutFraction, QVariant::fromValue(50.0f));
  m_animationCameraTarget.setKeyValueAt(zoomOutFraction,
                                        QVariant::fromValue(QVector3D(0.0f, 0.0f, 0.0f)));
  //! [12]

}
//! [0]

CQ3DBarsModifier::~CQ3DBarsModifier()
{
  delete m_graph;
}

void CQ3DBarsModifier::clearData()
{
  // Create data arrays
  QBarDataArray *dataSet = new QBarDataArray;
  m_primarySeries->dataProxy()->resetArray(dataSet, QStringList(), QStringList());
}

void CQ3DBarsModifier::loadData(const CDataArray * pData, unsigned int rowIndex, unsigned int colIndex)
{
  bool isOneDimensional = pData->dimensionality() == 1;

  std::vector<size_t> types = pData->size();
  size_t numRows = types.size() > rowIndex ? types[rowIndex] : 0;
  size_t numCols = isOneDimensional ? 1 : types.size() > colIndex ? types[colIndex] : 0;

  CArrayInterface::index_type mSelectedCell;
  mSelectedCell.resize(pData->dimensionality());

  QBarDataArray *dataSet = new QBarDataArray;
  QBarDataRow *dataRow;

  QStringList rowHeaders;
  QStringList colheaders;


  std::vector<std::string> rowdescr = pData->getAnnotationsString(rowIndex);

for (auto it : rowdescr)
    rowHeaders << FROM_UTF8(it);


  if (!isOneDimensional)
    {
      std::vector<std::string> coldescr = pData->getAnnotationsString(colIndex);

for (auto it : coldescr)
        colheaders << FROM_UTF8(it);
    }


  double maxValue = std::numeric_limits<double>::min();
  double minValue = std::numeric_limits<double>::max();


  dataSet->reserve(numRows);

  for (size_t row = 0; row < numRows; row++)
    {
      // Create a data row
      dataRow = new QBarDataRow(numCols);

      for (size_t col = 0; col < numCols; col++)
        {

          mSelectedCell[rowIndex] = row;

          if (!isOneDimensional)
            mSelectedCell[colIndex] = col;

          double value = (double)(*pData->array())[mSelectedCell];

          if (isnan(value) || !finite(value))
            {
              value = 0;
            }

          if (value > maxValue) maxValue = value;

          if (value < minValue) minValue = value;

          // Add data to the row
          (*dataRow)[col].setValue(value);

        }

      // Add the row to the set
      dataSet->append(dataRow);
    }

  m_valueAxis->setRange(minValue, maxValue);

  // Add data to the data proxy (the data proxy assumes ownership of it)
  m_primarySeries->dataProxy()->resetArray(dataSet, rowHeaders, colheaders);

  mRowHeaders = rowHeaders;
  mColHeaders = colheaders;

}

void CQ3DBarsModifier::changeRange(int range)
{
  if (range >= mRowHeaders.count())
    m_rowAxis->setRange(0, mRowHeaders.count() - 1);
  else
    m_rowAxis->setRange(range, range);
}

void CQ3DBarsModifier::changeStyle(int style)
{
  QComboBox *comboBox = qobject_cast<QComboBox *>(sender());

  if (comboBox)
    {
      m_barMesh = QAbstract3DSeries::Mesh(comboBox->itemData(style).toInt());
      m_primarySeries->setMesh(m_barMesh);
    }
}

void CQ3DBarsModifier::changePresetCamera()
{
  m_animationCameraX.stop();
  m_animationCameraY.stop();
  m_animationCameraZoom.stop();
  m_animationCameraTarget.stop();

  // Restore camera target in case animation has changed it
  m_graph->scene()->activeCamera()->setTarget(QVector3D(0.0f, 0.0f, 0.0f));

  //! [10]
  static int preset = Q3DCamera::CameraPresetFront;

  m_graph->scene()->activeCamera()->setCameraPreset((Q3DCamera::CameraPreset)preset);

  if (++preset > Q3DCamera::CameraPresetDirectlyBelow)
    preset = Q3DCamera::CameraPresetFrontLow;

  //! [10]
}

void CQ3DBarsModifier::changeTheme(int theme)
{
  Q3DTheme *currentTheme = m_graph->activeTheme();
  currentTheme->setType(Q3DTheme::Theme(theme));
  emit backgroundEnabledChanged(currentTheme->isBackgroundEnabled());
  emit gridEnabledChanged(currentTheme->isGridEnabled());
  emit fontChanged(currentTheme->font());
  emit fontSizeChanged(currentTheme->font().pointSize());
}

void CQ3DBarsModifier::changeLabelBackground()
{
  m_graph->activeTheme()->setLabelBackgroundEnabled(!m_graph->activeTheme()->isLabelBackgroundEnabled());
}

void CQ3DBarsModifier::changeSelectionMode(int selectionMode)
{
  QComboBox *comboBox = qobject_cast<QComboBox *>(sender());

  if (comboBox)
    {
      int flags = comboBox->itemData(selectionMode).toInt();
      m_graph->setSelectionMode(QAbstract3DGraph::SelectionFlags(flags));
    }
}

void CQ3DBarsModifier::changeFont(const QFont &font)
{
  QFont newFont = font;
  m_graph->activeTheme()->setFont(newFont);
}

void CQ3DBarsModifier::changeFontSize(int fontsize)
{
  m_fontSize = fontsize;
  QFont font = m_graph->activeTheme()->font();
  font.setPointSize(m_fontSize);
  m_graph->activeTheme()->setFont(font);
}

void CQ3DBarsModifier::shadowQualityUpdatedByVisual(QAbstract3DGraph::ShadowQuality sq)
{
  int quality = int(sq);
  // Updates the UI component to show correct shadow quality
  emit shadowQualityChanged(quality);
}

void CQ3DBarsModifier::changeLabelRotation(int rotation)
{
  m_valueAxis->setLabelAutoRotation(float(rotation));
  m_colAxis->setLabelAutoRotation(float(rotation));
  m_rowAxis->setLabelAutoRotation(float(rotation));
}

void CQ3DBarsModifier::setAxisTitleVisibility(bool enabled)
{
  m_valueAxis->setTitleVisible(enabled);
  m_colAxis->setTitleVisible(enabled);
  m_rowAxis->setTitleVisible(enabled);
}

void CQ3DBarsModifier::setAxisTitleFixed(bool enabled)
{
  m_valueAxis->setTitleFixed(enabled);
  m_colAxis->setTitleFixed(enabled);
  m_rowAxis->setTitleFixed(enabled);
}

//! [11]
void CQ3DBarsModifier::zoomToSelectedBar()
{
  m_animationCameraX.stop();
  m_animationCameraY.stop();
  m_animationCameraZoom.stop();
  m_animationCameraTarget.stop();

  Q3DCamera *camera = m_graph->scene()->activeCamera();
  float currentX = camera->xRotation();
  float currentY = camera->yRotation();
  float currentZoom = camera->zoomLevel();
  QVector3D currentTarget = camera->target();

  m_animationCameraX.setStartValue(QVariant::fromValue(currentX));
  m_animationCameraY.setStartValue(QVariant::fromValue(currentY));
  m_animationCameraZoom.setStartValue(QVariant::fromValue(currentZoom));
  m_animationCameraTarget.setStartValue(QVariant::fromValue(currentTarget));

  QPoint selectedBar = m_graph->selectedSeries()
                       ? m_graph->selectedSeries()->selectedBar()
                       : QBar3DSeries::invalidSelectionPosition();

  if (selectedBar != QBar3DSeries::invalidSelectionPosition())
    {
      // Normalize selected bar position within axis range to determine target coordinates
      //! [13]
      QVector3D endTarget;
      float xMin = m_graph->columnAxis()->min();
      float xRange = m_graph->columnAxis()->max() - xMin;
      float zMin = m_graph->rowAxis()->min();
      float zRange = m_graph->rowAxis()->max() - zMin;
      endTarget.setX((selectedBar.y() - xMin) / xRange * 2.0f - 1.0f);
      endTarget.setZ((selectedBar.x() - zMin) / zRange * 2.0f - 1.0f);
      //! [13]

      // Rotate the camera so that it always points approximately to the graph center
      //! [15]
      qreal endAngleX = 90.0 - qRadiansToDegrees(qAtan(qreal(endTarget.z() / endTarget.x())));

      if (endTarget.x() > 0.0f)
        endAngleX -= 180.0f;

      float barValue = m_graph->selectedSeries()->dataProxy()->itemAt(selectedBar.x(),
                       selectedBar.y())->value();
      float endAngleY = barValue >= 0.0f ? 30.0f : -30.0f;

      if (m_graph->valueAxis()->reversed())
        endAngleY *= -1.0f;

      //! [15]

      m_animationCameraX.setEndValue(QVariant::fromValue(float(endAngleX)));
      m_animationCameraY.setEndValue(QVariant::fromValue(endAngleY));
      m_animationCameraZoom.setEndValue(QVariant::fromValue(250));
      //! [14]
      m_animationCameraTarget.setEndValue(QVariant::fromValue(endTarget));
      //! [14]
    }
  else
    {
      // No selected bar, so return to the default view
      m_animationCameraX.setEndValue(QVariant::fromValue(m_defaultAngleX));
      m_animationCameraY.setEndValue(QVariant::fromValue(m_defaultAngleY));
      m_animationCameraZoom.setEndValue(QVariant::fromValue(m_defaultZoom));
      m_animationCameraTarget.setEndValue(QVariant::fromValue(m_defaultTarget));
    }

  m_animationCameraX.start();
  m_animationCameraY.start();
  m_animationCameraZoom.start();
  m_animationCameraTarget.start();
}
//! [11]

void CQ3DBarsModifier::changeShadowQuality(int quality)
{
  QAbstract3DGraph::ShadowQuality sq = QAbstract3DGraph::ShadowQuality(quality);
  m_graph->setShadowQuality(sq);
  emit shadowQualityChanged(quality);
}

//! [7]
void CQ3DBarsModifier::rotateX(int rotation)
{
  m_xRotation = rotation;
  m_graph->scene()->activeCamera()->setCameraPosition(m_xRotation, m_yRotation);
}

void CQ3DBarsModifier::rotateY(int rotation)
{
  m_yRotation = rotation;
  m_graph->scene()->activeCamera()->setCameraPosition(m_xRotation, m_yRotation);
}
//! [7]

void CQ3DBarsModifier::setBackgroundEnabled(int enabled)
{
  m_graph->activeTheme()->setBackgroundEnabled(bool(enabled));
}

void CQ3DBarsModifier::setGridEnabled(int enabled)
{
  m_graph->activeTheme()->setGridEnabled(bool(enabled));
}

void CQ3DBarsModifier::setSmoothBars(int smooth)
{
  m_smooth = bool(smooth);
  m_primarySeries->setMeshSmooth(m_smooth);
}

void CQ3DBarsModifier::setSeriesVisibility(int enabled)
{
  //m_secondarySeries->setVisible(bool(enabled));
}

void CQ3DBarsModifier::setReverseValueAxis(int enabled)
{
  m_graph->valueAxis()->setReversed(enabled);
}

void CQ3DBarsModifier::setReflection(bool enabled)
{
  m_graph->setReflection(enabled);
}



#endif
