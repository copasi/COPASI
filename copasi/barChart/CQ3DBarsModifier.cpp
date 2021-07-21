// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.





#include  "CQ3DBarsModifier.h"

#ifdef WITH_QT5_VISUALIZATION

#include <QtDataVisualization/q3dbars.h>
#include <QtDataVisualization/qbardataproxy.h>
#include <QtDataVisualization/qabstract3dseries.h>

#include <QMenu>
#include <QAction>
#include <QFont>
#include <QDebug>
#include <QStringList>
#include <QPointer>
#include <QPropertyAnimation>

#ifdef WITH_DATAVISUALIZATION_NAMESPACES
using namespace QtDataVisualization;
#endif

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
#include <copasi/UI/CQArrayAnnotationsWidget.h>

#include <copasi/UI/qtUtilities.h>

CQ3DBarsModifier::CQ3DBarsModifier(CQArrayAnnotationsWidget* widget, Q3DBars *bargraph)
  : m_graph(bargraph),
    m_inputHandler(NULL),
    m_xRotation(0.0f),
    m_yRotation(0.0f),
    m_fontSize(30),
    m_segments(4),
    m_subSegments(3),
    m_minval(-1.0f),
    m_maxval(1.0f),
    m_valueAxis(new QValue3DAxis),
    m_rowAxis(new QCategory3DAxis),
    m_colAxis(new QCategory3DAxis),
    m_primarySeries(new QBar3DSeries),
    m_barMesh(QAbstract3DSeries::MeshBar),
    m_smooth(false)
{
  m_graph->activeTheme()->setType(Q3DTheme::ThemeArmyBlue);
  m_graph->activeTheme()->setBackgroundEnabled(false);
  m_graph->activeTheme()->setLabelBackgroundEnabled(true);
  m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
  m_graph->setMultiSeriesUniform(true);

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

  m_primarySeries->setItemLabelFormat(QStringLiteral("@rowLabel, @colLabel : @valueLabel"));
  m_primarySeries->setMesh(QAbstract3DSeries::MeshBar);
  m_primarySeries->setMeshSmooth(false);

  m_graph->addSeries(m_primarySeries);

  changePresetCamera();

  clearData();

  // Set up property animations for zooming to the selected bar
  Q3DCamera *camera = m_graph->scene()->activeCamera();
  camera->setCameraPreset(Q3DCamera::CameraPresetIsometricRight);
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

  m_inputHandler = new CQCustomInputHandler(m_graph);
  m_inputHandler->setAxes(m_rowAxis, m_colAxis, m_valueAxis);
  m_graph->setActiveInputHandler(m_inputHandler);
  connect(m_inputHandler, SIGNAL(signalShowContextMenu(const QPoint &)), widget, SLOT(slotShowContextMenu(const QPoint&)));
  connect(m_inputHandler, SIGNAL(signalBarDoubleClicked(int, int)), widget, SLOT(selectTableCell(int, int)));

}

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

          if (std::isnan(value) || !std::isfinite(value))
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

void CQ3DBarsModifier::actionTriggered(QAction* action)
{
  if (action == NULL) return;

  QString option = action->text();
  QMenu *menu = qobject_cast<QMenu*> (action->parent());

  if (menu == NULL)
    {
      if (option == "Change label style")
        {
          changeLabelBackground();
        }
      else if (option == "Smooth bars")
        {
          setSmoothBars(!m_primarySeries->isMeshSmooth());
        }
      else if (option == "Change camera preset")
        {
          changePresetCamera();
        }
      else if (option == "Zoom to selected bar")
        {
          zoomToSelectedBar();
        }
      else if (option == "Show background")
        {
          setBackgroundEnabled(!m_graph->activeTheme()->isBackgroundEnabled());
        }
      else if (option == "Show grid")
        {
          setGridEnabled(!m_graph->activeTheme()->isGridEnabled());
        }
      else if (option == "Show reflections")
        {
          setReflection(!m_graph->isReflection());
        }
      else if (option == "Show Gradients")
        {
          toggleGradient();
        }

      return;
    }

  QString title = menu->title();

  if (title == "Theme")
    {
      changeTheme(menu->actions().indexOf(action));
    }
  else if (title == "Selection Mode")
    {
      if (option == "None")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionNone);
        }
      else if (option == "Bar")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionItem);
        }
      else if (option == "Row")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionRow);
        }
      else if (option == "Bar and Row")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow);
        }
      else if (option == "Column")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionColumn);
        }
      else if (option == "Bar and Column")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn);
        }
      else if (option == "Row and Column")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionRowAndColumn);
        }
      else if (option == "Bar, Row and Column")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemRowAndColumn);
        }
      else if (option == "Slice into Row")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionRow);
        }
      else if (option == "Slice into Row and Item")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndRow);
        }
      else if (option == "Slice into Column")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionColumn);
        }
      else if (option == "Slice into Column and Item")
        {
          m_graph->setSelectionMode(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndColumn);
        }
    }
  else if (title == "Style")
    {
      if (option == "Bar")
        {
          m_primarySeries->setMesh(QAbstract3DSeries::MeshBar);
        }
      else if (option == "Pyramid")
        {
          m_primarySeries->setMesh(QAbstract3DSeries::MeshPyramid);
        }
      else if (option == "Cone")
        {
          m_primarySeries->setMesh(QAbstract3DSeries::MeshCone);
        }
      else if (option == "Cylinder")
        {
          m_primarySeries->setMesh(QAbstract3DSeries::MeshCylinder);
        }
      else if (option == "Bevel bar")
        {
          m_primarySeries->setMesh(QAbstract3DSeries::MeshBevelBar);
        }
      else if (option == "Sphere")
        {
          m_primarySeries->setMesh(QAbstract3DSeries::MeshSphere);
        }

    }
  else if (title == "Shadow")
    {
      if (option == "None")
        {
          m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
        }
      else if (option == "Low")
        {
          m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityLow);
        }
      else if (option == "Medium")
        {
          m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityMedium);
        }
      else if (option == "High")
        {
          m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityHigh);
        }
      else if (option == "Low Soft")
        {
          m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
        }
      else if (option == "Medium Soft")
        {
          m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftMedium);
        }
      else if (option == "High Soft")
        {
          m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftHigh);
        }
    }

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

  static int preset = Q3DCamera::CameraPresetFront;

  m_graph->scene()->activeCamera()->setCameraPreset((Q3DCamera::CameraPreset)preset);

  if (++preset > Q3DCamera::CameraPresetDirectlyBelow)
    preset = Q3DCamera::CameraPresetFrontLow;

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

void CQ3DBarsModifier::selectBar(int row, int col)
{
  if (row == -1 || col == -1) return;

  m_primarySeries->setSelectedBar(QPoint(row, col));
  emit m_primarySeries->selectedBarChanged(QPoint(row, col));
}

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
      QVector3D endTarget;
      float xMin = m_graph->columnAxis()->min();
      float xRange = m_graph->columnAxis()->max() - xMin;
      float zMin = m_graph->rowAxis()->min();
      float zRange = m_graph->rowAxis()->max() - zMin;
      endTarget.setX((selectedBar.y() - xMin) / xRange * 2.0f - 1.0f);
      endTarget.setZ((selectedBar.x() - zMin) / zRange * 2.0f - 1.0f);

      // Rotate the camera so that it always points approximately to the graph center
      qreal endAngleX = 90.0 - qRadiansToDegrees(qAtan(qreal(endTarget.z() / endTarget.x())));

      if (endTarget.x() > 0.0f)
        endAngleX -= 180.0f;

      float barValue = m_graph->selectedSeries()->dataProxy()->itemAt(selectedBar.x(),
                       selectedBar.y())->value();
      float endAngleY = barValue >= 0.0f ? 30.0f : -30.0f;

      if (m_graph->valueAxis()->reversed())
        endAngleY *= -1.0f;

      m_animationCameraX.setEndValue(QVariant::fromValue(float(endAngleX)));
      m_animationCameraY.setEndValue(QVariant::fromValue(endAngleY));
      m_animationCameraZoom.setEndValue(QVariant::fromValue(250));
      m_animationCameraTarget.setEndValue(QVariant::fromValue(endTarget));
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

void CQ3DBarsModifier::toggleGradient()
{
  if (m_primarySeries->colorStyle() == Q3DTheme::ColorStyleRangeGradient)
    {
      m_primarySeries->setColorStyle(Q3DTheme::ColorStyleUniform);
    }
  else
    {
      QLinearGradient gr;
      gr.setColorAt(0.0, Qt::darkGreen);
      gr.setColorAt(0.5, Qt::yellow);
      gr.setColorAt(0.8, Qt::red);
      gr.setColorAt(1.0, Qt::darkRed);

      m_primarySeries->setBaseGradient(gr);
      m_primarySeries->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    }
}

void CQ3DBarsModifier::changeShadowQuality(int quality)
{
  QAbstract3DGraph::ShadowQuality sq = QAbstract3DGraph::ShadowQuality(quality);
  m_graph->setShadowQuality(sq);
  emit shadowQualityChanged(quality);
}

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

void CQ3DBarsModifier::setReverseValueAxis(int enabled)
{
  m_graph->valueAxis()->setReversed(enabled);
}

void CQ3DBarsModifier::setReflection(bool enabled)
{
  m_graph->setReflection(enabled);
}



CQCustomInputHandler::CQCustomInputHandler(DATAVIS_NS_PREFIX QAbstract3DGraph * graph, QObject * parent)
  : DATAVIS_NS_PREFIX QTouch3DInputHandler(parent)
  , m_graph(graph)
  , m_axisX(NULL)
  , m_axisY(NULL)
  , m_axisZ(NULL)
  , mState(CQCustomInputHandler::StateNormal)
{

}

void CQCustomInputHandler::mouseDoubleClickEvent(QMouseEvent * event)
{
  auto* barGraph = qobject_cast<Q3DBars*>(m_graph);

  if (!barGraph) return;

  auto* series = barGraph->selectedSeries();

  if (!series) return;

  auto point = series->selectedBar();
  emit signalBarDoubleClicked(point.rx(), point.ry());
}

void CQCustomInputHandler::mousePressEvent(QMouseEvent * event, const QPoint & mousePos)
{
  mPosDown = mousePos;
  Q3DInputHandler::mousePressEvent(event, mousePos);

  if (event->button() == Qt::LeftButton &&
      (qApp->keyboardModifiers() & Qt::ControlModifier) == Qt::ControlModifier)
    mState = CQCustomInputHandler::StateScrolling;
}

void CQCustomInputHandler::mouseMoveEvent(QMouseEvent * event, const QPoint & mousePos)
{
  if (mState == CQCustomInputHandler::StateScrolling  &&
      (qApp->keyboardModifiers() & Qt::ControlModifier) == Qt::ControlModifier)
    {
      float distanceX = 0.0f;
      float distanceY = 0.0f;
      // Get scene orientation from active camera
      float xRotation = scene()->activeCamera()->xRotation();
      float yRotation = scene()->activeCamera()->yRotation();

      // Calculate directional drag multipliers based on rotation
      float xMulX = qCos(qDegreesToRadians(xRotation));
      float xMulY = qSin(qDegreesToRadians(xRotation));
      float zMulX = qSin(qDegreesToRadians(xRotation));
      float zMulY = qCos(qDegreesToRadians(xRotation));
      float m_speedModifier = 200.0f;

      QPoint move = mousePos - mPosDown;
      float yMove = (yRotation < 0) ? -move.y() : move.y();

      distanceX = (move.x() * xMulX - yMove * xMulY) / m_speedModifier;
      distanceY = (move.x() * zMulX + yMove * zMulY) / m_speedModifier;

      QVector3D target = m_graph->scene()->activeCamera()->target();

      m_graph->scene()->activeCamera()->setTarget(target - QVector3D(distanceX, 0.0f, -distanceY));

      mPosDown = mousePos;
    }

  Q3DInputHandler::mouseMoveEvent(event, mousePos);
}

void CQCustomInputHandler::mouseReleaseEvent(QMouseEvent * event, const QPoint & mousePos)
{
  mState = CQCustomInputHandler::StateNormal;

  if (event->button() == Qt::RightButton)
    {
      QPoint diff = mousePos - mPosDown;

      if (diff.manhattanLength() < 5)
        emit signalShowContextMenu(mousePos);
    }

  Q3DInputHandler::mouseReleaseEvent(event, mousePos);
}

#endif
