// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.


#include <copasi/config.h>


#ifdef WITH_QT5_VISUALIZATION

#include "CQDataVizPlot.h"
#  include "CQPlotColors.h"


#  include "copasi/plot/CPlotSpecification.h"
#  include "copasi/UI/qtUtilities.h"
#  include "copasi/core/CRootContainer.h"
#  include "copasi/model/CModel.h"
#  include "copasi/commandline/CLocaleString.h"
#  include "copasi/CopasiDataModel/CDataModel.h"

# include <QGridLayout>
# include <QApplication>

# include <QtDataVisualization/Q3DBars>
# include <QtDataVisualization/Q3DScatter>
# include <QtDataVisualization/Q3DSurface>

#  include <QtDataVisualization/QBar3DSeries>
#  include <QtDataVisualization/QScatter3DSeries>
#  include <QtDataVisualization/QSurface3DSeries>

#  ifdef WITH_DATAVISUALIZATION_NAMESPACES
using namespace QtDataVisualization;
#  endif

QT_USE_NAMESPACE


#  define ActivitySize 8
C_FLOAT64 CQDataVizPlot::MissingValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

//#define DEFAULT_MODE DataVizPlot::PlotMode::Surface
#  define DEFAULT_MODE CQDataVizPlot::PlotMode::Scatter

CQDataVizPlot::CQDataVizPlot(QWidget * parent)
  : QWidget(parent)
  , mCurves(0)
  , mCurveMap()
  , mDataBefore(0)
  , mDataDuring(0)
  , mDataAfter(0)
  , mHaveBefore(false)
  , mHaveDuring(false)
  , mHaveAfter(false)
  , mpPlotSpecification(NULL)
  , mNextPlotTime()
  , mIgnoreUpdate(false)
  , mReplotFinished(false)
  , m_isTouching(false)
  , mpGraph(NULL)
  , mpWidget(NULL)
  , mpAxisX(NULL)
  , mpAxisY(NULL)
  , mpAxisZ(NULL)
  , mMode(DEFAULT_MODE)
  , mpContextMenu(NULL)
{
}

CQDataVizPlot::CQDataVizPlot(const CPlotSpecification * plotspec, QWidget * parent, PlotMode mode)
  : QWidget(parent)
  , mCurves(0)
  , mCurveMap()
  , mDataBefore(0)
  , mDataDuring(0)
  , mDataAfter(0)
  , mHaveBefore(false)
  , mHaveDuring(false)
  , mHaveAfter(false)
  , mpPlotSpecification(NULL)
  , mNextPlotTime()
  , mIgnoreUpdate(false)
  , mReplotFinished(false)
  , m_isTouching(false)
  , mpGraph(NULL)
  , mpWidget(NULL)
  , mpAxisX(NULL)
  , mpAxisY(NULL)
  , mpAxisZ(NULL)
  , mMode(mode)
  , mpContextMenu(NULL)
{

  // Size the vectors to be able to store information for all activities.
  mData.resize(ActivitySize);
  mObjectValues.resize(ActivitySize);
  mObjectInteger.resize(ActivitySize);
  mDataSize.resize(ActivitySize);
  mDataIndex.clear();

  QGridLayout * layout = new QGridLayout(this);
  setLayout(layout);

  // Initialize from the plot specification
  initFromSpec(plotspec);
  connect(this, SIGNAL(replotSignal()), this, SLOT(replot()));
  connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotShowContextMenu(const QPoint &)));
}


QString CQDataVizPlot::titleText() const
{
  if (!mpGraph)
    return "";

  return mpGraph->title();
}

const CPlotSpecification *
CQDataVizPlot::getPlotSpecification() const
{
  return mpPlotSpecification;
}


bool CQDataVizPlot::createGraph(CQDataVizPlot::PlotMode mode)
{
  if (mode != mMode)
    {
      if (mpWidget)
        {
          layout()->removeWidget(mpWidget);
          mpWidget->deleteLater();
          mpWidget = NULL;
        }

      if (mpGraph)
        {
          mpGraph->deleteLater();
          mpGraph = NULL;
        }
    }

  if (!mpGraph)
    {
      switch (mMode)
        {
          case CQDataVizPlot::PlotMode::Bars:
            mpGraph = new Q3DBars();
            break;

          case CQDataVizPlot::PlotMode::Scatter:
          {
            auto * graph = new Q3DScatter();

            if (!mpAxisX)
              mpAxisX = new QValue3DAxis;

            graph->setAxisX(qobject_cast< QValue3DAxis * >(mpAxisX));

            if (!mpAxisY)
              mpAxisY = new QValue3DAxis;

            graph->setAxisY(qobject_cast< QValue3DAxis * >(mpAxisY));

            if (!mpAxisZ)
              mpAxisZ = new QValue3DAxis;

            graph->setAxisZ(qobject_cast< QValue3DAxis * >(mpAxisZ));
            mpGraph = graph;
          }
          break;

          case CQDataVizPlot::PlotMode::Surface:
          {
            auto * graph = new Q3DSurface();

            if (!mpAxisX)
              mpAxisX = new QValue3DAxis;

            graph->setAxisX(qobject_cast< QValue3DAxis * >(mpAxisX));

            if (!mpAxisY)
              mpAxisY = new QValue3DAxis;

            graph->setAxisY(qobject_cast< QValue3DAxis * >(mpAxisY));

            if (!mpAxisZ)
              mpAxisZ = new QValue3DAxis;

            graph->setAxisZ(qobject_cast< QValue3DAxis * >(mpAxisZ));
            mpGraph = graph;
          }
          break;

          default:
            return false;
            break;
        }

      mpWidget = QWidget::createWindowContainer(mpGraph);
      layout()->addWidget(mpWidget);
    }
  else
    {
      removeSeries();
    }

  mpGraph->setTitle(FROM_UTF8(mpPlotSpecification->getTitle()));
  createContextMenu();
  return true;
}

void CQDataVizPlot::removeSeries()
{
  Q3DScatter * scatter = qobject_cast< Q3DScatter * >(mpGraph);
  Q3DSurface * surface = qobject_cast< Q3DSurface * >(mpGraph);

  if (surface)
for (auto * series : surface->seriesList())
      surface->removeSeries(series);

  if (scatter)
for (auto * series : scatter->seriesList())
      scatter->removeSeries(series);
}


bool CQDataVizPlot::initFromSpec(const CPlotSpecification * plotspec)
{

  mIgnoreUpdate = true;
  mpPlotSpecification = plotspec;

  std::map< std::string, QAbstract3DSeries * >::iterator found;

  CDataVector< CPlotItem >::const_iterator itPlotItem = mpPlotSpecification->getItems().begin();
  CDataVector< CPlotItem >::const_iterator endPlotItem = mpPlotSpecification->getItems().end();

  CVector< bool > Visible(mpPlotSpecification->getItems().size());
  Visible = true;
  bool * pVisible = Visible.array();

  for (; itPlotItem != endPlotItem; ++itPlotItem, ++pVisible)
    {
      if ((found = mCurveMap.find(itPlotItem->CCopasiParameter::getKey())) != mCurveMap.end())
        {
          *pVisible = found->second->isVisible();
        }
    }


  if (!createGraph(mMode))
    return false;

  mpGraph->setTitle(FROM_UTF8(mpPlotSpecification->getTitle()));

  itPlotItem = mpPlotSpecification->getItems().begin();
  pVisible = Visible.array();

  mCurves.resize(mpPlotSpecification->getItems().size());

  auto ppCurve = mCurves.begin();
  unsigned long int k = 0;
  bool needLeft = false;
  bool needRight = false;

  for (; itPlotItem != endPlotItem; ++itPlotItem, ++pVisible, ++ppCurve, ++k)
    {
      auto plotType = itPlotItem->getType();

      if (plotType != CPlotItem::spectogram && plotType != CPlotItem::surface && plotType != CPlotItem::bandedGraph)
        continue;

      // set up the curve
      QAbstract3DSeries * series = NULL;
      QColor color;
      bool haveColor = false;

      if (itPlotItem->getType() == CPlotItem::bandedGraph)
        {
          std::string colorstr = itPlotItem->getValue< std::string >("Color");
          color = CQPlotColors::getColor(colorstr, k);
          haveColor = true;
        }

      switch (mMode)
        {
          case CQDataVizPlot::PlotMode::Bars:
          {
            auto *s = new QBar3DSeries();

            if (haveColor)
              s->setBaseColor(color);

            qobject_cast< Q3DBars* >(mpGraph)->addSeries(s);
            series = s;
            break;
          }

          case CQDataVizPlot::PlotMode::Scatter:
          {
            auto * s = new QScatter3DSeries();

            if (haveColor)
              s->setBaseColor(color);

            qobject_cast< Q3DScatter * >(mpGraph)->addSeries(s);
            series = s;
            break;
          }

          case CQDataVizPlot::PlotMode::Surface:
          {
            auto * s = new QSurface3DSeries();

            if (haveColor)
              s->setBaseColor(color);

            qobject_cast< Q3DSurface * >(mpGraph)->addSeries(s);
            series = s;
            break;
          }

          default:
            return false;
        }

      series->setProperty("curve_type", QVariant((int) plotType));
      series->setProperty("activity", QVariant((int) itPlotItem->getActivity()));
      series->setProperty("copasi_key", QVariant(FROM_UTF8(itPlotItem->CCopasiParameter::getKey())));
      series->setName(FROM_UTF8(itPlotItem->getTitle()));

      *ppCurve = series;

      showCurve(series, *pVisible);

      mCurveMap[itPlotItem->CCopasiParameter::getKey()] = series;

    }

  mIgnoreUpdate = false;

  return true;
}


bool CQDataVizPlot::compile(CObjectInterface::ContainerList listOfContainer)
{
  clearBuffers();

  size_t i, imax;
  size_t j, jmax;

  std::pair< std::set< const CObjectInterface * >::iterator, bool > Inserted;
  std::pair< Activity, size_t > DataIndex;
  std::vector< std::set< const CObjectInterface * > > ActivityObjects;

  ActivityObjects.resize(ActivitySize);

  // Loop over all curves.
  imax = mpPlotSpecification->getItems().size();
  mDataIndex.resize(imax);

  std::vector< std::vector< std::string > >::iterator itX;

  for (i = 0; i < imax; ++i)
    {
      const CPlotItem * pItem = &mpPlotSpecification->getItems()[i];
      bool isSpectogram = pItem->getType() == CPlotItem::spectogram;
      Activity ItemActivity = pItem->getActivity();
      DataIndex.first = ItemActivity;

      // Loop over all channels
      jmax = pItem->getNumChannels();
      mDataIndex[i].resize(jmax);

      for (j = 0; j < jmax; ++j)
        {
          std::string objectCN;

          const CObjectInterface * pObj = CObjectInterface::GetObjectFromCN(listOfContainer, pItem->getChannels()[j]);

          if (pObj)
            {
              mObjects.insert(pObj);
              objectCN = pObj->getCN();
              mCnNameMap[objectCN] = pObj->getObjectDisplayName();
            }
          else
            CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6,
                           pItem->getChannels()[j].c_str());

          // Remember the actual order for saving the data.
          // Note, we are currently only dealing with 2D curves and histograms.
          // In addition the data is not normalized. The same data column may appear
          // multiple times, e.g. as X value and as Y value for another curve.
          if (j == 0)
            {
              // We have an X value
              for (itX = mSaveCurveObjects.begin(); itX != mSaveCurveObjects.end(); ++itX)
                if (*itX->begin() == objectCN)
                  break;

              if (itX == mSaveCurveObjects.end())
                {
                  std::vector< std::string > NewX;
                  NewX.push_back(objectCN);

                  mSaveCurveObjects.push_back(NewX);
                  itX = mSaveCurveObjects.end() - 1;

                  setAxisUnits(CPlotInterface::Axis::xAxis, pObj);
                }

              if (pItem->getType() == CPlotItem::histoItem1d)
                mSaveHistogramObjects.push_back(objectCN);
            }
          else
            {
              itX->push_back(objectCN);

              if (j == 1)
                setAxisUnits(CPlotInterface::Axis::yAxis, pObj);

              if (j == 2)
                setAxisUnits(CPlotInterface::Axis::zAxis, pObj);
            }

          Inserted = ActivityObjects[ItemActivity].insert(pObj);

          if (Inserted.second)
            {
              if (ItemActivity & COutputInterface::BEFORE)
                mHaveBefore = true;

              if (ItemActivity & COutputInterface::DURING)
                mHaveDuring = true;

              if (ItemActivity & COutputInterface::AFTER)
                mHaveAfter = true;

              // The insert was successful
              DataIndex.second = ActivityObjects[ItemActivity].size() - 1;

              // Allocate the data buffer
              mData[ItemActivity].push_back(new CVector< double >(1000));

              // Store the pointer to the current object value. (Only if it has a double or integer value
              // and the value pointer actually exists. If not, use a dummy value.)
              void * tmp;

              const CDataObject * pDataObject = CObjectInterface::DataObject(pObj);

              if (pDataObject != NULL && (tmp = pObj->getValuePointer()) != NULL && (pDataObject->hasFlag(CDataObject::ValueInt) || pDataObject->hasFlag(CDataObject::ValueDbl)))
                {
                  mObjectValues[ItemActivity].push_back((C_FLOAT64 *) tmp); //pObj->getValuePointer());
                  mObjectInteger[ItemActivity].push_back(pDataObject->hasFlag(CDataObject::ValueInt));
                }
              else
                {
                  mObjectValues[ItemActivity].push_back(&MissingValue);
                  mObjectInteger[ItemActivity].push_back(false);
                }

              // Store [curve][channel] to data index
              mDataIndex[i][j] = DataIndex;

              // Store the [Activity][object] to data index.
              mObjectIndex[ItemActivity][objectCN] = DataIndex.second;
            }
          else
            {
              // The object already existed we only need to
              // store [curve][channel] to data index.
              DataIndex.second = mObjectIndex[ItemActivity][objectCN];
              mDataIndex[i][j] = DataIndex;
            }
        }
    }

  mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime();
  mReplotFinished = true;

  return true;
}

void CQDataVizPlot::output(const Activity & activity)
{
  size_t i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE))
    mDataBefore++;
  else if (mHaveDuring && (activity == COutputInterface::DURING))
    mDataDuring++;
  else if (mHaveAfter && (activity == COutputInterface::AFTER))
    mDataAfter++;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if ((ItemActivity & activity) && mData[ItemActivity].size())
      {
        std::vector< CVector< double > * > & data = mData[ItemActivity];
        size_t & ndata = mDataSize[ItemActivity];

        if ((imax = data.size()) != 0)
          {
            if (ndata >= data[0]->size())
              {
                resizeCurveData(ItemActivity);
              }

            //the data that needs to be stored internally:
            for (i = 0; i < imax; ++i)
              if (mObjectInteger[ItemActivity][i])
                (*data[i])[ndata] = *(C_INT32 *) mObjectValues[ItemActivity][i];
              else
                (*data[i])[ndata] = *mObjectValues[ItemActivity][i];

            ++ndata;
          }
      }

  mDataReady = false;
  updatePlot();
}

void CQDataVizPlot::separate(const Activity & activity)
{
  size_t i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE))
    mDataBefore++;

  if (mHaveDuring && (activity == COutputInterface::DURING))
    mDataDuring++;

  if (mHaveAfter && (activity == COutputInterface::AFTER))
    mDataAfter++;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if ((ItemActivity & activity) && mData[ItemActivity].size())
      {
        std::vector< CVector< double > * > & data = mData[ItemActivity];
        size_t & ndata = mDataSize[ItemActivity];

        if ((imax = data.size()) != 0)
          {
            if (ndata >= data[0]->size())
              {
                resizeCurveData(ItemActivity);
              }

            //the data that needs to be stored internally:
            for (i = 0; i < imax; ++i)
              (*data[i])[ndata] = MissingValue;

            ++ndata;
          }
      }

  updatePlot();

  return;
}

void CQDataVizPlot::finish()
{

  // We need to force a replot, i.e., the next mNextPlotTime should be in the past.
  mNextPlotTime = 0;
  mDataReady = true;
  replot();
}

std::set< double > resizeRange(std::set< double >& range, int maxRange = 256)
{
  if (range.size() < maxRange)
    return range;

  double ratio = range.size() / (double) maxRange;

  std::set< double > result;

  for (int i = 0; i < maxRange; ++i)
    {
      int pos = floor(i * ratio);
      result.insert(*std::next(range.begin(), pos));
    }

  return result;
}

void CQDataVizPlot::updateCurves(const size_t & activity)
{
  if (!mDataReady)
    return;

  if (activity == C_INVALID_INDEX)
    {
      C_INT32 ItemActivity;

      for (ItemActivity = 0; ItemActivity < ActivitySize; ++ItemActivity)
        {
          updateCurves(ItemActivity);
        }

      return;
    }

  size_t k = 0;
  auto itCurves = mCurves.begin();
  auto endCurves = mCurves.end();

  double x_min = mpAxisX->max();
  double x_max = mpAxisX->min();

  double y_min = mpAxisY->max();
  double y_max = mpAxisY->min();

  double z_min = mpAxisZ->max();
  double z_max = mpAxisZ->min();


  bool data_changed = false;

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      auto curve_activity = (*itCurves)->property("activity").toInt();

      if (curve_activity != activity)
        continue;

      auto * scatter = qobject_cast< QScatter3DSeries * >(*itCurves);
      auto * surface = qobject_cast< QSurface3DSeries * >(*itCurves);
      auto * bars = qobject_cast< QBar3DSeries * >(*itCurves);

      auto curve_type = (*itCurves)->property("curve_type").toInt();
      std::string curve_key = TO_UTF8((*itCurves)->property("copasi_key").toString());

      std::vector< CVector< double > * > & data = mData[curve_activity];

      auto & x = *data[mDataIndex[k][0].second];
      auto & z = *data[mDataIndex[k][1].second];
      auto & y = *data[mDataIndex[k][2].second];
      auto data_size = mDataSize[activity];
      auto data_count = (*itCurves)->property("data_count").toInt();

      if (scatter)
        {
          auto * proxy = scatter->dataProxy();

          if (data_size != data_count)
            {
              for (int i = (int)data_count; i < (int)data_size; ++i)
                {
                  auto cur_x = x[i];
                  auto cur_y = y[i];
                  auto cur_z = z[i];

                  if (qIsNaN(cur_x) || qIsNaN(cur_y) || qIsNaN(cur_z))
                    continue;

                  if (cur_x < x_min)
                    x_min = cur_x;

                  if (cur_x > x_max)
                    x_max = cur_x;

                  if (cur_y < y_min)
                    y_min = cur_y;

                  if (cur_y > y_max)
                    y_max = cur_y;

                  if (cur_z < z_min)
                    z_min = cur_z;

                  if (cur_z > z_max)
                    z_max = cur_z;

                  proxy->addItem(QScatterDataItem(QVector3D(cur_x, cur_y, cur_z)));
                }

              scatter->setProperty("data_count", int(data_size));
              mpAxisX->setRange(x_min, x_max);
              mpAxisY->setRange(y_min, y_max);
              mpAxisZ->setRange(z_min, z_max);
            }
        }

      if (bars)
        {

        }

      if (surface)
        {
          auto * proxy = surface->dataProxy();

          if (data_size != data_count)
            {
              std::set< double > x_range;
              std::set< double > y_range;
              std::map< std::pair<double, double>, QVector3D > dataMap;

              for (auto i = 0; i < data_size; ++i)
                {
                  auto cur_x = x[i];
                  auto cur_y = y[i];
                  auto cur_z = z[i];

                  if (qIsNaN(cur_x) || qIsNaN(cur_y) || qIsNaN(cur_z))
                    continue;

                  if (cur_x < x_min)
                    x_min = cur_x;

                  if (cur_x > x_max)
                    x_max = cur_x;

                  if (cur_y < y_min)
                    y_min = cur_y;

                  if (cur_y > y_max)
                    y_max = cur_y;

                  if (cur_z < z_min)
                    z_min = cur_z;

                  if (cur_z > z_max)
                    z_max = cur_z;

                  x_range.insert(cur_x);
                  y_range.insert(cur_z);
                  dataMap[std::make_pair(cur_x, cur_z)] = QVector3D(cur_x, cur_y, cur_z);
                }

              x_range = resizeRange(x_range);
              y_range = resizeRange(y_range);

              QSurfaceDataArray * dataArray = new QSurfaceDataArray();
              dataArray->reserve(x_range.size() * y_range.size());

for (auto & cur_y : y_range)
                {
                  QSurfaceDataRow * newRow = new QSurfaceDataRow(y_range.size());
                  int count = 0;

for (auto & cur_x : x_range)
                    {
                      (*newRow)[count++].setPosition(dataMap[std::make_pair(cur_x, cur_y)]);
                    }

                  dataArray->append(newRow);

                }

              mpAxisX->setRange(x_min, x_max);
              mpAxisY->setRange(y_min, y_max);
              mpAxisZ->setRange(z_min, z_max);

              proxy->resetArray(dataArray);
              surface->setProperty("data_count", int(data_size));

            }

        }

    }

}


void CQDataVizPlot::resizeCurveData(const size_t & activity)
{
  std::vector< CVector< double > * > & data = mData[activity];
  std::vector< CVector< double > * >::iterator it = data.begin();

  std::vector< CVector< double > * > OldData = data;
  std::vector< CVector< double > * >::iterator itOld = OldData.begin();
  std::vector< CVector< double > * >::iterator endOld = OldData.end();

  size_t oldSize = (*it)->size();
  size_t newSize = 2 * (*it)->size();

  // We must not deallocate the old data since this will create a window of time
  // were the GUI thread may access the old location before it is notified.
  for (; itOld != endOld; ++itOld, ++it)
    {
      *it = new CVector< double >(newSize);
      memcpy((*it)->array(), (*itOld)->array(), oldSize * sizeof(double));
    }

}

void CQDataVizPlot::updatePlot()
{
  if (mReplotFinished)
    {
      mReplotFinished = false;
      emit replotSignal();
    }
}

CQDataVizPlot::~CQDataVizPlot()
{
  clearBuffers();
}

bool CQDataVizPlot::saveData(const std::string & filename)
{
  // No objects.
  if (!mObjects.size())
    return true;

  // Find out whether we have any data.
  C_INT32 ItemActivity;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (mDataSize[ItemActivity] != 0)
      break;

  // No data
  if (ItemActivity == ActivitySize)
    return true;

  std::ofstream fs(CLocaleString::fromUtf8(filename).c_str());

  if (!fs.good())
    return false;

  // Write the table header
  fs << "# ";

  std::vector< std::vector< std::string > >::const_iterator itX;
  std::vector< std::vector< std::string > >::const_iterator endX =
    mSaveCurveObjects.end();

  std::vector< std::string >::const_iterator it;
  std::vector< std::string >::const_iterator end;

  for (itX = mSaveCurveObjects.begin(); itX != endX; ++itX)
    for (it = itX->begin(), end = itX->end(); it != end; ++it)
      fs << mCnNameMap[*it] << "\t";

  fs << "\n";

  size_t i, imax = mObjects.size();
  std::vector< CVector< double > * > Data;
  Data.resize(imax);

  std::vector< CVector< double > * >::const_iterator itData;
  std::vector< CVector< double > * >::const_iterator endData = Data.end();

  std::vector< size_t > Offset;
  std::vector< size_t >::const_iterator itOffset;

  Offset.resize(imax);

  std::map< Activity, std::map< std::string, size_t > >::iterator itActivity;
  std::map< std::string, size_t >::iterator itObject;

  if (mDataBefore)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::BEFORE)) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                continue;
              }

            Data[i] = NULL;
          }

      for (i = 0; i < mDataBefore; i++)
        {
          for (itData = Data.begin(); itData != endData; ++itData)
            {
              if (*itData)
                fs << (**itData)[i];
              else
                fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  if (mDataDuring)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::DURING)) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            Data[i] = NULL;
          }

      for (i = 0; i < mDataDuring; i++)
        {
          for (itData = Data.begin(), itOffset = Offset.begin(); itData != endData; ++itData)
            {
              if (*itData)
                fs << (**itData)[i + *itOffset];
              else
                fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  if (mDataAfter)
    {
      for (itX = mSaveCurveObjects.begin(), i = 0; itX != endX; ++itX)
        for (it = itX->begin(), end = itX->end(); it != end; ++it, ++i)
          {
            if ((itActivity = mObjectIndex.find(COutputInterface::AFTER)) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::AFTER][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataDuring;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() && (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataBefore + mDataDuring;
                continue;
              }

            Data[i] = NULL;
          }

      for (i = 0; i < mDataAfter; i++)
        {
          for (itData = Data.begin(), itOffset = Offset.begin(); itData != endData; ++itData)
            {
              if (*itData)
                fs << (**itData)[i + *itOffset];
              else
                fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  bool FirstHistogram = true;

for (auto & curve : mCurveMap)
    {
      QSurface3DSeries * surface = qobject_cast< QSurface3DSeries * > (curve.second);
      QScatter3DSeries * scatter = qobject_cast< QScatter3DSeries * >(curve.second);

      fs << std::endl
         << std::endl
         << " FROM PROXY " << std::endl;

      if (surface)
        {
          auto * dataArr = surface->dataProxy()->array();

          for (int i = 0; i < dataArr->count(); ++i)
            {
              auto * row = dataArr->at(i);

              for (int j = 0; j < row->count(); ++j)
                {
                  auto cur = row->at(j);
                  fs << "(" << cur.x() << ", " << cur.y() << ", " << cur.z() << ")"
                     << "\t";
                }

              fs << std::endl;
            }
        }

    }

  fs.close();

  if (!fs.good())
    return false;

  return true;
}

void CQDataVizPlot::setCurvesVisibility(const bool & visibility)
{
}

void CQDataVizPlot::saveToFile(const QString & fileName, QRect & rect)
{
  auto image = mpGraph->renderToImage(8);
  image.save(fileName);
}

QString CQDataVizPlot::getSaveFilters()
{
  return "PNG Files (*.png)";
}

void CQDataVizPlot::clearBuffers()
{
  mObjects.clear();

  size_t Activity;
  size_t i, imax;

  for (Activity = 0; Activity < ActivitySize; Activity++)
    {
      std::vector< CVector< double > * > & data = mData[Activity];

      // Delete each QMemArray
      for (i = 0, imax = data.size(); i < imax; i++)
        if (data[i] != NULL)
          delete data[i];

      data.clear();

      mObjectValues[Activity].clear();
      mObjectInteger[Activity].clear();
      mDataSize[Activity] = 0;
    }

  mDataIndex.clear();
  mObjectIndex.clear();

  mSaveCurveObjects.clear();
  mCnNameMap.clear();
  mSaveHistogramObjects.clear();

  mDataBefore = 0;
  mDataDuring = 0;
  mDataAfter = 0;

  mHaveBefore = false;
  mHaveDuring = false;
  mHaveAfter = false;
}

void CQDataVizPlot::setAxisUnits(Axis axis, const CObjectInterface * pObject)
{
  if (axis == CPlotInterface::Axis::xAxis)
    {
      mpAxisX->setTitle(getAxisText(axis, pObject));
      mpAxisX->setTitleVisible(!mpAxisX->title().isEmpty());
    }
  else if (axis == CPlotInterface::Axis::yAxis)
    {
      mpAxisZ->setTitle(getAxisText(axis, pObject));
      mpAxisZ->setTitleVisible(!mpAxisZ->title().isEmpty());
    }
  else
    {
      mpAxisY->setTitle(getAxisText(axis, pObject));
      mpAxisY->setTitleVisible(!mpAxisY->title().isEmpty());
    }
}

void CQDataVizPlot::toggleLogX(bool logX)
{
#  if (QT_DATAVISUALIZATION_VERSION >= QT_DATAVISUALIZATION_VERSION_CHECK(1, 1, 0))
//    if
#endif
}

void CQDataVizPlot::toggleLogY(bool logY)
{
}

void CQDataVizPlot::render(QPainter *, QRect)
{
}

void CQDataVizPlot::resetZoom()
{

}

bool CQDataVizPlot::viewportEvent(QEvent * event)
{
  return false;
}

void CQDataVizPlot::mousePressEvent(QMouseEvent * event)
{

}

void CQDataVizPlot::mouseMoveEvent(QMouseEvent * event)
{
}

void CQDataVizPlot::mouseReleaseEvent(QMouseEvent * event)
{

  if (event->button() == Qt::RightButton)
    {
      slotShowContextMenu(event->pos());
    }

}

void CQDataVizPlot::keyPressEvent(QKeyEvent * event)
{
}

void CQDataVizPlot::update()
{
  if (mpGraph)
    mpGraph->requestUpdate();
}

void CQDataVizPlot::replot()
{
  if (!mDataReady)
    return;

  if (mNextPlotTime < CCopasiTimeVariable::getCurrentWallTime())
    {
      // skip rendering when shift is pressed
      Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();

      if (((int) mods & (int) Qt::ShiftModifier) == (int) Qt::ShiftModifier && !mNextPlotTime.isZero())
        {
          mReplotFinished = true;
          return;
        }

      CCopasiTimeVariable Delta = CCopasiTimeVariable::getCurrentWallTime();

      {
        QMutexLocker Locker(&mMutex);
        updateCurves(C_INVALID_INDEX);
      }

      if (mpGraph)
        mpGraph->requestUpdate();

      Delta = CCopasiTimeVariable::getCurrentWallTime() - Delta;

      mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 10 * Delta.getMicroSeconds();
    }

  mReplotFinished = true;
}

void CQDataVizPlot::showCurve(DATAVIS_NS_PREFIX QAbstract3DSeries* item, bool on)
{
  item->setVisible(on);

  if (!mIgnoreUpdate)
    replot();
}

void
CQDataVizPlot::contextActionTriggered(QAction* action)
{
  if (action == NULL)
    return;

  QString option = action->text();
  QMenu * menu = qobject_cast< QMenu * >(action->parent());

  if (menu == NULL)
    {
      if (option == "Change label style")
        {
          changeLabelBackground();
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
          setBackgroundEnabled(!mpGraph->activeTheme()->isBackgroundEnabled());
        }
      else if (option == "Show grid")
        {
          setGridEnabled(!mpGraph->activeTheme()->isGridEnabled());
        }
      else if (option == "Show reflections")
        {
          setReflection(!mpGraph->isReflection());
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
          mpGraph->setSelectionMode(QAbstract3DGraph::SelectionNone);
        }
      else if (option == "Item")
        {
          mpGraph->setSelectionMode(QAbstract3DGraph::SelectionItem);
        }
      else if (option == "ItemAndRow")
        {
          mpGraph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                    | QAbstract3DGraph::SelectionSlice);
        }
      else if (option == "ItemAndColumn")
        {
          mpGraph->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
                                    | QAbstract3DGraph::SelectionSlice);
        }

    }
  else if (title == "Style" && mMode == PlotMode::Scatter)
    {
      auto * scatter = dynamic_cast< Q3DScatter * >(mpGraph);

for (auto * series : scatter->seriesList())
        {
          if (option == "Cube")
            {
              series->setMesh(QAbstract3DSeries::MeshCube);
            }
          else if (option == "Minimal")
            {
              series->setMesh(QAbstract3DSeries::MeshMinimal);
            }
          else if (option == "Point")
            {
              series->setMesh(QAbstract3DSeries::MeshPoint);
            }
          else if (option == "Sphere")
            {
              series->setMesh(QAbstract3DSeries::MeshSphere);
            }
        }
    }

  else if (title == "Style" && mMode == PlotMode::Surface)
    {
      auto * surface = dynamic_cast< Q3DSurface * >(mpGraph);

for (auto * series : surface->seriesList())
        {
          if (option == "Wireframe")
            {
              series->setDrawMode(QSurface3DSeries::DrawWireframe);
            }
          else if (option == "Surface")
            {
              series->setDrawMode(QSurface3DSeries::DrawSurface);
            }
          else if (option == "SurfaceAndWireframe")
            {
              series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
            }
        }
    }
  else if (title == "Shadow")
    {
      if (option == "None")
        {
          mpGraph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
        }
      else if (option == "Low")
        {
          mpGraph->setShadowQuality(QAbstract3DGraph::ShadowQualityLow);
        }
      else if (option == "Medium")
        {
          mpGraph->setShadowQuality(QAbstract3DGraph::ShadowQualityMedium);
        }
      else if (option == "High")
        {
          mpGraph->setShadowQuality(QAbstract3DGraph::ShadowQualityHigh);
        }
      else if (option == "Low Soft")
        {
          mpGraph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
        }
      else if (option == "Medium Soft")
        {
          mpGraph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftMedium);
        }
      else if (option == "High Soft")
        {
          mpGraph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftHigh);
        }
    }
}

void CQDataVizPlot::slotShowContextMenu(const QPoint &pos)
{
  if (!mpContextMenu)
    return;

  QWidget * pSender = qobject_cast< QWidget * >(sender());

  if (pSender != NULL)
    mpContextMenu->popup(mapToGlobal(pos));
  else
    mpContextMenu->popup(this->mapToGlobal(pos));
}

void CQDataVizPlot::changePresetCamera()
{
  static int preset = Q3DCamera::CameraPresetFrontLow;

  mpGraph->scene()->activeCamera()->setCameraPreset((Q3DCamera::CameraPreset) preset);

  if (++preset > Q3DCamera::CameraPresetDirectlyBelow)
    preset = Q3DCamera::CameraPresetFrontLow;
}

void CQDataVizPlot::changeLabelBackground()
{
}

void CQDataVizPlot::changeFont(const QFont & font)
{
  QFont newFont = font;
  //newFont.setPointSizeF(m_fontSize);
  mpGraph->activeTheme()->setFont(newFont);
}

void CQDataVizPlot::changeFontSize(int fontsize)
{
}

void
CQDataVizPlot::createContextMenu()
{

  if (mpContextMenu)
    {
      disconnect(mpContextMenu, SIGNAL(triggered(QAction *)), this, SLOT(contextActionTriggered(QAction *)));
    }

  pdelete(mpContextMenu);

  mpContextMenu = new QMenu(this);


  QMenu * menu = new QMenu("Theme", mpContextMenu);
  menu->addAction(new QAction("Qt", menu));
  menu->addAction(new QAction("Primary Colors", menu));
  menu->addAction(new QAction("Digia", menu));
  menu->addAction(new QAction("Stone Moss", menu));
  menu->addAction(new QAction("Army Blue", menu));
  menu->addAction(new QAction("Retro", menu));
  menu->addAction(new QAction("Ebony", menu));
  menu->addAction(new QAction("Isabelle", menu));
  mpContextMenu->addMenu(menu); // theme

  menu = new QMenu("Shadow", mpContextMenu);
  menu->addAction(new QAction("None", menu));
  menu->addAction(new QAction("Low", menu));
  menu->addAction(new QAction("Medium", menu));
  menu->addAction(new QAction("High", menu));
  menu->addAction(new QAction("Low Soft", menu));
  menu->addAction(new QAction("Medium Soft", menu));
  menu->addAction(new QAction("High Soft", menu));
  mpContextMenu->addMenu(menu); // shadow

  menu = new QMenu("Selection Mode", mpContextMenu);
  menu->addAction(new QAction("None", menu));
  menu->addAction(new QAction("Item", menu));

  if (mMode != PlotMode::Scatter)
    {
      menu->addAction(new QAction("ItemAndRow", menu));
      menu->addAction(new QAction("ItemAndColumn", menu));
    }

  mpContextMenu->addMenu(menu); // Selection Mode

  if (mMode == PlotMode::Scatter)
    {
      menu = new QMenu("Style", mpContextMenu);
      menu->addAction(new QAction("Sphere", menu));
      menu->addAction(new QAction("Cube", menu));
      menu->addAction(new QAction("Minimal", menu));
      menu->addAction(new QAction("Point", menu));
      mpContextMenu->addMenu(menu); // style
    }

  if (mMode == PlotMode::Surface)
    {
      menu = new QMenu("Style", mpContextMenu);
      menu->addAction(new QAction("Wireframe", menu));
      menu->addAction(new QAction("Surface", menu));
      menu->addAction(new QAction("SurfaceAndWireframe", menu));
      mpContextMenu->addMenu(menu); // Style

    }

  mpContextMenu->addSeparator();

  mpContextMenu->addAction(new QAction("Change label style"));
  mpContextMenu->addAction(new QAction("Change camera preset"));
  mpContextMenu->addAction(new QAction("Show background"));
  mpContextMenu->addAction(new QAction("Show grid"));
  mpContextMenu->addAction(new QAction("Show reflections"));
  mpContextMenu->addAction(new QAction("Show Gradients"));

  connect(mpContextMenu, SIGNAL(triggered(QAction *)), this, SLOT(contextActionTriggered(QAction*)));
}

#endif // WITH_QT5_VISUALIZATION

void CQDataVizPlot::rotateX(int rotation)
{
}

void CQDataVizPlot::rotateY(int rotation)
{
}

void CQDataVizPlot::setBackgroundEnabled(int enabled)
{
  mpGraph->activeTheme()->setBackgroundEnabled((bool) enabled);
}

void CQDataVizPlot::setGridEnabled(int enabled)
{
  mpGraph->activeTheme()->setGridEnabled((bool) enabled);
}

void CQDataVizPlot::setSmoothBars(int smooth)
{
}

void CQDataVizPlot::setReverseValueAxis(int enabled)
{
}

void CQDataVizPlot::setReflection(bool enabled)
{

}

void CQDataVizPlot::changeRange(int range)
{
}

void CQDataVizPlot::changeStyle(int style)
{
}

void CQDataVizPlot::changeSelectionMode(int selectionMode)
{
}

void CQDataVizPlot::changeTheme(int theme)
{
  Q3DTheme * currentTheme = mpGraph->activeTheme();
  currentTheme->setType(Q3DTheme::Theme(theme));
  emit backgroundEnabledChanged(currentTheme->isBackgroundEnabled());
  emit gridEnabledChanged(currentTheme->isGridEnabled());
  emit fontChanged(currentTheme->font());
  emit fontSizeChanged(currentTheme->font().pointSize());
}

void CQDataVizPlot::changeShadowQuality(int quality)
{
}

void CQDataVizPlot::shadowQualityUpdatedByVisual(DATAVIS_NS_PREFIX QAbstract3DGraph::ShadowQuality shadowQuality)
{
}

void CQDataVizPlot::changeLabelRotation(int rotation)
{
}

void CQDataVizPlot::setAxisTitleVisibility(bool enabled)
{
}

void CQDataVizPlot::setAxisTitleFixed(bool enabled)
{
}

void CQDataVizPlot::zoomToSelectedBar()
{
}

void CQDataVizPlot::toggleGradient()
{
}
