// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.


#include <copasi/config.h>

#if defined(COPASI_USE_QCUSTOMPLOT)

#  include "CQCustomPlot.h"

#  include "CQPlotColors.h"

#  include "copasi/plot/CPlotSpecification.h"
#  include "copasi/UI/qtUtilities.h"
#  include "copasi/core/CRootContainer.h"
#  include "copasi/model/CModel.h"
#  include "copasi/commandline/CLocaleString.h"
#  include "copasi/CopasiDataModel/CDataModel.h"

#  include <QApplication>

class CHistoHelper
{
public:
  CHistoHelper(double increment)
    : mpX(NULL)
    , mSize(0)
    , mMaxSize(0)
    , mLastRectangle(0)
    , mCount(0)
    , mMinX(std::numeric_limits< double >::quiet_NaN())
    , mMaxX(std::numeric_limits< double >::quiet_NaN())
    , mMinY(std::numeric_limits< double >::quiet_NaN())
    , mMaxY(std::numeric_limits< double >::quiet_NaN())
    , mIncrement(increment)
    , mMap()
    , mHistoX(0)
    , mHistoY(0)
  {
  }

  bool updateData(const double * x, size_t dataSize)
  {
    if (dataSize == mSize)
      return false;

    mpX = x;
    mSize = dataSize;

    const double * xIt = mpX + mLastRectangle;
    const double * end = mpX + mSize;

    mLastRectangle = mSize;

    double InvIncrement = 1.0 / mIncrement;

    for (; xIt != end; ++xIt)
      {
        //just ignore breaks. Later we perhaps want to start a new histogram...
        if (std::isnan(*xIt)) //NaN
          continue;

        ++mCount;

        if (-std::numeric_limits< C_FLOAT64 >::infinity() < *xIt && *xIt < std::numeric_limits< C_FLOAT64 >::infinity())
          {
            mMap[(C_INT32) floor(*xIt * InvIncrement)]++;
            mMap[(C_INT32) floor(*xIt * InvIncrement) + 1];
          }
      }

    //construct arrays
    mHistoX.resize(mMap.size() + 1);
    mHistoY.resize(mMap.size() + 1);

    auto pX = mHistoX.begin();
    auto pY = mHistoY.begin();

    //add one bin to the left
    if (mMap.size() > 0)
      {
        *pX = (mMap.begin()->first - 1) * mIncrement;
      }
    else
      {
        *pX = 0.0;
      }

    *pY = 0.0;

    mMinX = mMaxX = *pX++;
    mMinY = mMaxY = *pY++;

    std::map< C_INT32, C_INT32 >::const_iterator it = mMap.begin();
    std::map< C_INT32, C_INT32 >::const_iterator itEnd = mMap.end();

    for (; it != itEnd; ++it, ++pX, ++pY)
      {
        *pX = it->first * mIncrement;
        *pY = (double) it->second * 100.0 / (double) mCount;

        if (*pX < mMinX)
          mMinX = *pX;

        if (*pX > mMaxX)
          mMaxX = *pX;

        if (*pY < mMinY)
          mMinY = *pY;

        if (*pY > mMaxY)
          mMaxY = *pY;
      }

    return true;
  }

  void updateGraph(QCPGraph * graph)
  {
    graph->setData(mHistoX, mHistoY, true);
    graph->rescaleAxes(true);
  }

private:
  const double * mpX;
  size_t mSize;
  size_t mMaxSize;

  mutable size_t mLastRectangle;
  mutable size_t mCount;
  mutable double mMinX;
  mutable double mMaxX;
  mutable double mMinY;
  mutable double mMaxY;

  double mIncrement;

  mutable std::map< C_INT32, C_INT32 > mMap;
  mutable QVector< double > mHistoX;
  mutable QVector< double > mHistoY;
};

#  define ActivitySize 8
C_FLOAT64 CQCustomPlot::MissingValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

CQCustomPlot::CQCustomPlot(QWidget * parent)
  : QCustomPlot(parent)
  , mCurves(0)
  , mCurveMap()
  , mY2Map()
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
  , mpTitle(NULL)
  , mLogTicker(NULL)
  , mDefaultTicker(NULL)
{
}

CQCustomPlot::CQCustomPlot(const CPlotSpecification * plotspec, QWidget * parent)
  : QCustomPlot(parent)
  , mCurves(0)
  , mCurveMap()
  , mY2Map()
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
  , mpTitle(NULL)
  , mLogTicker(new QCPAxisTickerLog)
{
  // Size the vectors to be able to store information for all activities.
  mData.resize(ActivitySize);
  mObjectValues.resize(ActivitySize);
  mObjectInteger.resize(ActivitySize);
  mDataSize.resize(ActivitySize);
  mDataIndex.clear();

  //setNoAntialiasingOnDrag(true);
  //setSelectionRectMode(QCP::srmZoom);
  setInteractions(QCP::iRangeDrag | QCP::iRangeZoom /*| QCP::iSelectPlottables*/);
  mDefaultTicker = xAxis->ticker();

  // Initialize from the plot specification
  initFromSpec(plotspec);
  connect(this, SIGNAL(replotSignal()), this, SLOT(replot()));
  connect(this, SIGNAL(legendClick(QCPLegend *, QCPAbstractLegendItem *, QMouseEvent *)),
          this, SLOT(legendClicked(QCPLegend *, QCPAbstractLegendItem *, QMouseEvent *)));
  connect(this, SIGNAL(plottableClick(QCPAbstractPlottable*, int, QMouseEvent*)),
          this, SLOT(displayToolTip(QCPAbstractPlottable*, int, QMouseEvent*)));
}

bool CQCustomPlot::initFromSpec(const CPlotSpecification * plotspec)
{
  mIgnoreUpdate = true;
  mpPlotSpecification = plotspec;

  if (!mpTitle)
    {
      mpTitle = new QCPTextElement(this);
      plotLayout()->insertRow(0); // insert an empty row above the axis rect
      plotLayout()->addElement(0, 0, mpTitle);
    }

  mpTitle->setText(FROM_UTF8(mpPlotSpecification->getTitle()));

  mCurves.resize(mpPlotSpecification->getItems().size());

  std::map< std::string, QCPAbstractPlottable * >::iterator found;

  CDataVector< CPlotItem >::const_iterator itPlotItem = mpPlotSpecification->getItems().begin();
  CDataVector< CPlotItem >::const_iterator endPlotItem = mpPlotSpecification->getItems().end();

  CVector< bool > Visible(mpPlotSpecification->getItems().size());
  Visible = true;
  bool * pVisible = Visible.array();

  for (; itPlotItem != endPlotItem; ++itPlotItem, ++pVisible)
    {
      if ((found = mCurveMap.find(itPlotItem->CCopasiParameter::getKey())) != mCurveMap.end())
        {
          *pVisible = found->second->visible();
        }
    }

  // Remove unused curves if definition has changed
for (auto item : mHisto)
    pdelete(item.second)
    mHisto.clear();

  clearPlottables();

  mCurveMap.clear();
  mY2Map.clear();

  itPlotItem = mpPlotSpecification->getItems().begin();
  pVisible = Visible.array();
  auto ppCurve = mCurves.begin();

  unsigned long int k = 0;
  bool needLeft = false;
  bool needRight = false;

  for (; itPlotItem != endPlotItem; ++itPlotItem, ++pVisible, ++ppCurve, ++k)
    {
      if (itPlotItem->getType() == CPlotItem::spectogram)
        {
          QCPColorMap * map = new QCPColorMap(xAxis, yAxis);
          map->setInterpolate(itPlotItem->getValue< bool >("bilinear"));
          map->data()->setSize(width(), height());
          QCPColorScale * colorScale = new QCPColorScale(this);
          plotLayout()->addElement(1, 1, colorScale);
          colorScale->setType(QCPAxis::atRight);
          map->setColorScale(colorScale);
          colorScale->axis()->setLabel("z");
          map->setName(FROM_UTF8(itPlotItem->getTitle()));

          map->setGradient(QCPColorGradient::gpSpectrum);
          map->setProperty("curve_type", QVariant((int) itPlotItem->getType()));
          map->setProperty("activity", QVariant((int) itPlotItem->getActivity()));
          map->setProperty("copasi_key", QVariant(FROM_UTF8(itPlotItem->CCopasiParameter::getKey())));

          *ppCurve = map;

          needLeft = true;

          continue;
        }

      // set up the curve
      QCPAbstractPlottable * series = NULL;

      if (itPlotItem->getType() == CPlotItem::bandedGraph || itPlotItem->getType() == CPlotItem::histoItem1d)
        series = new QCPGraph(xAxis, yAxis);
      else
        series = new QCPCurve(xAxis, yAxis);

      QCPGraph * graph = dynamic_cast< QCPGraph * >(series);
      QCPCurve * curve = dynamic_cast< QCPCurve * >(series);

      series->setProperty("curve_type", QVariant((int) itPlotItem->getType()));
      series->setProperty("activity", QVariant((int) itPlotItem->getActivity()));
      series->setProperty("copasi_key", QVariant(FROM_UTF8(itPlotItem->CCopasiParameter::getKey())));
      series->setName(FROM_UTF8(itPlotItem->getTitle()));

      *ppCurve = series;

      mCurveMap[itPlotItem->CCopasiParameter::getKey()] = series;

      //color handling should be similar for different curve types
      QColor color;

      if (itPlotItem->getType() == CPlotItem::curve2d
          || itPlotItem->getType() == CPlotItem::histoItem1d
          || itPlotItem->getType() == CPlotItem::bandedGraph)
        {
          std::string colorstr = itPlotItem->getValue< std::string >("Color");
          color = CQPlotColors::getColor(colorstr, k);
        }

      series->setPen(color);

      showCurve(series, *pVisible);

      if (itPlotItem->getType() == CPlotItem::curve2d
          || itPlotItem->getType() == CPlotItem::histoItem1d
          || itPlotItem->getType() == CPlotItem::bandedGraph)
        {
          needLeft = true;

          unsigned C_INT32 linetype = itPlotItem->getValue< unsigned C_INT32 >("Line type");
          CPlotItem::LineType lineType = (CPlotItem::LineType) linetype;

          if (lineType == CPlotItem::LineType::Lines || lineType == CPlotItem::LineType::LinesAndSymbols)
            {
              unsigned C_INT32 linesubtype = itPlotItem->getValue< unsigned C_INT32 >("Line subtype");
              CPlotItem::LineStyle lineStyle = (CPlotItem::LineStyle) linesubtype;
              C_FLOAT64 width = itPlotItem->getValue< C_FLOAT64 >("Line width");

              switch (lineStyle)
                {
                  case CPlotItem::LineStyle::Dotted:
                    series->setPen(QPen(QBrush(color), width, Qt::DotLine, Qt::FlatCap));
                    break;

                  case CPlotItem::LineStyle::Dashed:
                    series->setPen(QPen(QBrush(color), width, Qt::DashLine));
                    break;

                  case CPlotItem::LineStyle::DotDash:
                    series->setPen(QPen(QBrush(color), width, Qt::DashDotLine));
                    break;

                  case CPlotItem::LineStyle::DotDotDash:
                    series->setPen(QPen(QBrush(color), width, Qt::DashDotDotLine));
                    break;

                  case CPlotItem::LineStyle::None:
                    if (curve)
                      curve->setLineStyle(QCPCurve::lsNone);

                    if (graph)
                      graph->setLineStyle(QCPGraph::lsNone);

                    break;

                  case CPlotItem::LineStyle::Solid:
                  default:
                    series->setPen(QPen(QBrush(color), width, Qt::SolidLine));
                    break;
                }
            }

          if (lineType == CPlotItem::LineType::Points)
            {
              C_FLOAT64 width = itPlotItem->getValue< C_FLOAT64 >("Line width");
              series->setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap));

              if (curve)
                {
                  curve->setLineStyle(QCPCurve::lsNone);
                  curve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 1));
                }

              if (graph)
                {
                  graph->setLineStyle(QCPGraph::lsNone);
                  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 1));
                }
            }

          if (lineType == CPlotItem::LineType::Symbols)
            {
              if (curve)
                curve->setLineStyle(QCPCurve::lsNone);

              if (graph)
                graph->setLineStyle(QCPGraph::lsNone);
            }

          if (lineType == CPlotItem::LineType::Symbols || lineType == CPlotItem::LineType::LinesAndSymbols) //line+symbols
            {
              unsigned C_INT32 symbolsubtype = itPlotItem->getValue< unsigned C_INT32 >("Symbol subtype");
              CPlotItem::SymbolType symbolType = (CPlotItem::SymbolType) symbolsubtype;

              switch (symbolType) //symbol type
                {
                  case CPlotItem::SymbolType::LargeCross:
                  case CPlotItem::SymbolType::Plus:
                    setSymbol(series, QCPScatterStyle::ssPlus, color, 7, 2);

                    break;

                  case CPlotItem::SymbolType::Circle:
                    setSymbol(series, QCPScatterStyle::ssCircle, color, 8, 1);
                    break;

                  case CPlotItem::SymbolType::Square:
                    setSymbol(series, QCPScatterStyle::ssSquare, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::Diamond:
                    setSymbol(series, QCPScatterStyle::ssDiamond, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::xCross:
                    setSymbol(series, QCPScatterStyle::ssCross, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::Star:
                    setSymbol(series, QCPScatterStyle::ssStar, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::TriangleLeft:
                  case CPlotItem::SymbolType::TriangleUp:
                    setSymbol(series, QCPScatterStyle::ssTriangle, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::TriangleRight:
                  case CPlotItem::SymbolType::TriangleDown:
                    setSymbol(series, QCPScatterStyle::ssTriangleInverted, color, 7, 2);
                    break;

                    //case CPlotItem::SymbolType::hDash:
                    //  setSymbol(series, QwtSymbol::HLine, color, 7, 2);
                    //  break;

                    //case CPlotItem::SymbolType::vDash:
                    //  setSymbol(series, QwtSymbol::VLine, color, 7, 2);
                    //  break;

                  case CPlotItem::SymbolType::SmallCross:
                  default:
                    setSymbol(series, QCPScatterStyle::ssCross, color, 5, 1);
                    break;

                  case CPlotItem::SymbolType::None:
                    break;
                }
            }
        } //2d curves and banded graphs

      if (itPlotItem->getType() == CPlotItem::bandedGraph && graph)
        {
          //set fill color
          QColor c = color;
          int alpha = 64;

          if (itPlotItem->getParameter("alpha"))
            alpha = itPlotItem->getValue< C_INT32 >("alpha");

          c.setAlpha(alpha);
          series->setBrush(c);

          // need to create a buddy for y2 series
          QCPGraph * y2 = addGraph(xAxis, yAxis);
          y2->setPen(graph->pen());
          y2->removeFromLegend();
          graph->setChannelFillGraph(y2);
          mY2Map[graph] = y2;
        }

      if (itPlotItem->getType() == CPlotItem::histoItem1d)
        {
          mHisto[graph] = new CHistoHelper(itPlotItem->getValue< C_FLOAT64 >("increment"));
          graph->setValueAxis(yAxis2);
          graph->setLineStyle(QCPGraph::lsStepLeft);

          needRight = true;
        }
    }

  toggleLogX(plotspec->isLogX());
  toggleLogY(plotspec->isLogY());

  if (needRight)
    {
      yAxis2->setVisible(true);
      yAxis2->setLabel("Percent %");
    }

  legend->setVisible(true);
  legend->setWrap(3);
  legend->setColumnSpacing(3);
  legend->setRowSpacing(1);
  legend->setFillOrder(QCPLegend::foColumnsFirst, true);
  legend->setBorderPen(QPen(Qt::NoPen));

  QCPLayoutGrid * subLayout = new QCPLayoutGrid;
  subLayout->setMargins(QMargins(5, 0, 5, 5));
  subLayout->addElement(0, 0, legend);
  int count = plotLayout()->rowCount();
  plotLayout()->addElement(count, 0, subLayout);
  plotLayout()->setRowStretchFactor(count, 0.01);

  mIgnoreUpdate = false;

  return true;
}

void CQCustomPlot::setSymbol(QCPAbstractPlottable * pPlotable, QCPScatterStyle::ScatterShape symbol, QColor color, int symbolSize, float penWidth)
{
  QCPCurve * pCurve = dynamic_cast< QCPCurve * >(pPlotable);

  if (pCurve)
    {
      pCurve->setScatterStyle(QCPScatterStyle(
                                symbol, color, symbolSize));
    }

  QCPGraph * pGraph = dynamic_cast< QCPGraph * >(pPlotable);

  if (pGraph)
    {
      pGraph->setScatterStyle(QCPScatterStyle(
                                symbol, color, symbolSize));
    }
}

QString CQCustomPlot::titleText() const
{
  if (mpTitle)
    return mpTitle->text();

  return QString();
}

void CQCustomPlot::update()
{
  QCustomPlot::update();
}

const CPlotSpecification * CQCustomPlot::getPlotSpecification() const
{
  return mpPlotSpecification;
}

CQCustomPlot::~CQCustomPlot()
{
  clearBuffers();
}

bool CQCustomPlot::compile(CObjectInterface::ContainerList listOfContainer)
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

                  if (!isSpectogram)
                    setAxisUnits(CPlotInterface::Axis::xAxis, pObj);
                }

              if (pItem->getType() == CPlotItem::histoItem1d)
                mSaveHistogramObjects.push_back(objectCN);
            }
          else
            {
              itX->push_back(objectCN);

              if (!isSpectogram)
                setAxisUnits(CPlotInterface::Axis::yAxis, pObj);
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

void CQCustomPlot::output(const Activity & activity)
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

  updatePlot();
}

void CQCustomPlot::separate(const Activity & activity)
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

void CQCustomPlot::finish()
{
  // We need to force a replot, i.e., the next mNextPlotTime should be in the past.
  mNextPlotTime = 0;

  replot();
}

bool CQCustomPlot::saveData(const std::string & filename)
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
  size_t HistogramIndex = 0;

  auto itCurves = mCurves.begin();
  auto endCurves = mCurves.end();

  for (; (itCurves != endCurves) && (HistogramIndex < mSaveHistogramObjects.size()); ++itCurves, ++HistogramIndex)
    {
      if (*itCurves == NULL)
        continue;

      if ((*itCurves)->property("curve_type").toInt() == CPlotItem::histoItem1d)
        {
          if (FirstHistogram)
            {
              fs << "\n# The histograms: \n";
              FirstHistogram = false;
            }

          fs << mSaveHistogramObjects[HistogramIndex] << std::endl;

          auto * curve = dynamic_cast< QCPGraph * >(*itCurves);

          for (int i = 0; i < curve->dataCount(); ++i)
            {
              auto data = curve->data()->at(i);
              fs << data->key << "\t" << data->value << "\n";
            }
        }
    }

  fs.close();

  if (!fs.good())
    return false;

  return true;
}

void CQCustomPlot::setCurvesVisibility(const bool & visibility)
{
  for (int i = 0; i < this->plottableCount(); ++i)
    showCurve(plottable(i), visibility);

  QCustomPlot::replot();
}

void CQCustomPlot::replot()
{
  if (mIgnoreUpdate)
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

      QCustomPlot::replot();

      Delta = CCopasiTimeVariable::getCurrentWallTime() - Delta;

      mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 10 * Delta.getMicroSeconds();
    }

  mReplotFinished = true;
}

void CQCustomPlot::toggleLog(QCPAxis * axis, bool useLog)
{
  axis->setScaleType(useLog ? QCPAxis::stLogarithmic
                     : QCPAxis::stLinear);
  axis->setTicker(useLog ? mLogTicker : mDefaultTicker);
  QCustomPlot::replot();
}

void CQCustomPlot::toggleLogX(bool logX)
{
  toggleLog(xAxis, logX);
}

void CQCustomPlot::toggleLogY(bool logY)
{
  toggleLog(yAxis, logY);
}

void CQCustomPlot::render(QPainter * painter, QRect rect)
{
  QCustomPlot::render(painter);
}

void CQCustomPlot::resetZoom()
{
  rescaleAxes(true);
  QCustomPlot::replot();
}

void CQCustomPlot::mouseMoveEvent(QMouseEvent * event)
{

  QCustomPlot::mouseMoveEvent(event);

  if (m_isTouching)
    QCustomPlot::replot(QCustomPlot::rpImmediateRefresh);
}

void CQCustomPlot::mousePressEvent(QMouseEvent * event)
{
  m_isTouching = true;
  QCustomPlot::mousePressEvent(event);
}

void CQCustomPlot::mouseReleaseEvent(QMouseEvent * event)
{
  m_isTouching = false;
  QCustomPlot::mouseReleaseEvent(event);
}

void CQCustomPlot::wheelEvent(QWheelEvent * event)
{
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
  QCPLayerable * element = layerableAt(event->position(), true);
#else
  QCPLayerable * element = layerableAt(event->pos(), true);
#endif

  if (dynamic_cast<QCPLegend*>(element) || dynamic_cast<QCPAbstractLegendItem*>(element))
    {
      bool reorder = true;

      if (event->angleDelta().y() > 0 && legend->wrap() < 8)
        {
          legend->setWrap(legend->wrap() + 1);
        }
      else if (legend->wrap() > 1)
        {
          legend->setWrap(legend->wrap() - 1);
        }
      else
        reorder = false;

      if (reorder)
        {
          legend->setFillOrder(legend->fillOrder(), true);
          replot();
        }
    }

  QCustomPlot::wheelEvent(event);
}

void CQCustomPlot::updateCurves(const size_t & activity)
{
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

  bool data_changed = false;

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      if (mDataIndex.size() < k)
        continue;

      auto * curve = dynamic_cast< QCPCurve * >(*itCurves);
      auto * graph = dynamic_cast< QCPGraph * >(*itCurves);
      auto * map = dynamic_cast< QCPColorMap * >(*itCurves);

      auto curve_activity = (*itCurves)->property("activity").toInt();

      if (curve_activity != activity)
        continue;

      auto curve_type = (*itCurves)->property("curve_type").toInt();
      std::string curve_key = TO_UTF8((*itCurves)->property("copasi_key").toString());

      if (curve == NULL && graph == NULL && map == NULL)
        continue;

      std::vector< CVector< double > * > & data = mData[curve_activity];

      switch (curve_type)
        {
          case CPlotItem::curve2d:
          {
            auto & x = *data[mDataIndex[k][0].second];
            auto & y = *data[mDataIndex[k][1].second];

            int data_size = mDataSize[activity];
            int current_count = curve->property("last_count").toInt();
            // need to store the number of data points we added,
            // so we wont replot them in case they are skipped
            curve->setProperty("last_count", data_size);

            if (current_count != data_size)
              {
                data_changed = true;

                for (int i = current_count; i < data_size; ++i)
                  {
                    double cur_x = x[i];
                    double cur_y = y[i];

                    // only skip adding nans, if only one of them is nan
                    // when both are nan, we want to use it to create a new
                    // curve. if only one of them is, it is a missing
                    // datapoint and if added we would not be able to connect
                    // datapoints by lines

                    if (qIsNaN(cur_x)  == qIsNaN(cur_y))
                      curve->addData(cur_x, cur_y);
                  }

                curve->rescaleAxes(true);
              }

            break;
          }

          case CPlotItem::bandedGraph:
          {
            auto & x = *data[mDataIndex[k][0].second];
            auto & y = *data[mDataIndex[k][1].second];
            auto & y2 = *data[mDataIndex[k][2].second];
            auto data_size = mDataSize[activity];
            auto current_count = graph->dataCount();
            QCPGraph * pY2 = dynamic_cast< QCPGraph * >(mY2Map[graph]);

            if (current_count != data_size && pY2)
              {
                data_changed = true;

                for (int i = current_count; i < data_size; ++i)
                  {
                    double cur_x = x[i];
                    double cur_y = y[i];
                    double cur_y2 = y2[i];
                    {
                      graph->addData(cur_x, cur_y);
                      pY2->addData(cur_x, cur_y2);
                    }
                  }

                graph->rescaleAxes(true);
                pY2->rescaleAxes(true);
              }

            break;
          }

          case CPlotItem::histoItem1d:
          {
            auto & x = *data[mDataIndex[k][0].second];
            auto data_size = mDataSize[activity];
            auto current_count = graph->dataCount();
            auto * helper = mHisto[graph];

            if (current_count != data_size && helper)
              {
                helper->updateData(x.array(), data_size);
                helper->updateGraph(graph);
              }

            break;
          }

          case CPlotItem::spectogram:
          {
            auto & x = *data[mDataIndex[k][0].second];
            auto & y = *data[mDataIndex[k][1].second];
            auto & z = *data[mDataIndex[k][2].second];
            auto data_size = mDataSize[activity];
            auto current_count = map->data()->keySize();

            if (data_size != current_count)
              {
                // for now replace all
                double min_x = std::numeric_limits< double >::infinity();
                double max_x = -std::numeric_limits< double >::infinity();
                double min_y = std::numeric_limits< double >::infinity();
                double max_y = -std::numeric_limits< double >::infinity();

                std::set< double > x_range;
                std::set< double > y_range;

                for (int count = 0; count < data_size; ++count)
                  {
                    auto cur_x = x[count];
                    auto cur_y = y[count];

                    if (cur_x < min_x)
                      min_x = cur_x;

                    if (cur_x > max_x)
                      max_x = cur_x;

                    if (cur_y < min_y)
                      min_y = cur_y;

                    if (cur_y > max_y)
                      max_y = cur_y;

                    x_range.insert(cur_x);
                    y_range.insert(cur_y);
                  }

                map->data()->setSize(x_range.size(), y_range.size());
                map->data()->setKeyRange(QCPRange(min_x, max_x));
                map->data()->setValueRange(QCPRange(min_y, max_y));

                for (int count = 0; count < data_size; ++count)
                  {
                    auto cur_x = x[count];
                    auto cur_y = y[count];
                    auto cur_z = z[count];

                    if (!qIsNaN(cur_z))
                      map->data()->setData(cur_x, cur_y, cur_z);
                  }

                map->rescaleDataRange();
                map->rescaleAxes();
              }

            break;
          }
        }
    }

  if (data_changed)
    {
      //rescaleAxes(true);
      QCustomPlot::replot();
    }
}

void CQCustomPlot::resizeCurveData(const size_t & activity)
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

  // Tell the curves that the location of the data has changed
  // otherwise repaint events could crash
  size_t k = 0;
  auto itCurves = mCurves.begin();
  auto endCurves = mCurves.end();

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      if (*itCurves == NULL)
        continue;

      if ((size_t)(*itCurves)->property("activity").toInt() == activity)
        {
          std::vector< CVector< double > * > & data = mData[activity];

          switch ((*itCurves)->property("curve_type").toInt())
            {
                //case CPlotItem::curve2d:
                //  (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                //                               data[mDataIndex[k][1].second]);
                //  break;

                //case CPlotItem::bandedGraph:
                //  (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                //                               data[mDataIndex[k][1].second],
                //                               data[mDataIndex[k][2].second]);
                //  break;

                //case CPlotItem::histoItem1d:
                //  (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                //                               NULL);
                //  break;

              default:
                //fatalError();
                break;
            }
        }
    }

  // It is now save to delete the old data since the GUI thread has been notified.
  for (itOld = OldData.begin(); itOld != endOld; ++itOld)
    {
      // pdelete(*itOld);
    }
}

void CQCustomPlot::updatePlot()
{
  if (mReplotFinished)
    {
      mReplotFinished = false;
      emit replotSignal();
    }
}

void CQCustomPlot::clearBuffers()
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

void CQCustomPlot::setAxisUnits(Axis axis, const CObjectInterface * pObjectInterface)
{
  if (axis == CPlotInterface::Axis::xAxis)
    xAxis->setLabel(getAxisText(axis, pObjectInterface));
  else
    yAxis->setLabel(getAxisText(axis, pObjectInterface));
}

void CQCustomPlot::legendClicked(QCPLegend * legend, QCPAbstractLegendItem * item, QMouseEvent * event)
{
  auto * plItem = dynamic_cast< QCPPlottableLegendItem * >(item);

  if (plItem != NULL)
    {
      auto * pCurve = plItem->plottable();
      showCurve(pCurve, !pCurve->visible());
      QCustomPlot::replot();
    }
}

void CQCustomPlot::displayToolTip(QCPAbstractPlottable * plottable, int dataIndex, QMouseEvent * event)
{
  auto * graph(dynamic_cast< QCPGraph * >(plottable));

  if (graph)
    {
      auto dataPoint = graph->data()->at(dataIndex);
      QToolTip::showText(event->globalPos(),
                         tr("%1: %2, %3")
                         .arg(graph->name())
                         .arg(dataPoint->key)
                         .arg(dataPoint->value),
                         this, rect());
      return;
    }

  auto * curve(dynamic_cast< QCPCurve * >(plottable));

  if (curve)
    {
      auto dataPoint = curve->data()->at(dataIndex);
      QToolTip::showText(event->globalPos(),
                         tr("%1: %2, %3")
                         .arg(curve->name())
                         .arg(dataPoint->key)
                         .arg(dataPoint->value),
                         this, rect());
      return;
    }

  auto * map(dynamic_cast< QCPColorMap * >(plottable));

  if (map)
    {
      double key, value;
      map->pixelsToCoords(event->localPos(), key, value);

      QToolTip::showText(event->globalPos(),
                         tr("(%1, %2) = %3")
                         .arg(key)
                         .arg(value)
                         .arg(map->data()->data(key, value)),
                         this, rect());
      return;
    }

  QToolTip::hideText();
}

void CQCustomPlot::showCurve(QCPAbstractPlottable * pCurve, bool on)
{
  if (!pCurve)
    return;

  auto * plItem = legend->itemWithPlottable(pCurve);
  pCurve->setVisible(on);
  plItem->setVisible(true);

  QFont legendFont = plItem->font();
  legendFont.setItalic(!on);
  legendFont.setBold(on);
  plItem->setFont(legendFont);
  auto pBuddy = mY2Map.find(plItem->plottable());

  if (pBuddy != mY2Map.end())
    (*pBuddy).second->setVisible(plItem->plottable()->visible());

  rescaleAxes(true);


}

#endif // COPASI_USE_QCUSTOMPLOT
