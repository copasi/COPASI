// Copyright (C) 2022 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <QtCore/QString>
#include <QColor>   //might need to go to the header file
#include <QCursor>
#include <QtCore/QMutexLocker>

#include <qwt_symbol.h>
#include <qwt_legend.h>
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
#include <qwt_legend_data.h>
#include <qwt_legend_label.h>
#include <qwt_plot_canvas.h>
#include <qwt_compat.h>
#else
#include <qwt_legend_item.h>
#endif

#include <qwt_scale_engine.h>
#include <qwt_color_map.h>
#include <qwt_scale_widget.h>

#include <limits>
#include <algorithm>
#include <cmath>

#include "copasi/copasi.h"

#include "scrollzoomer.h"
#include "CQwtPlot.h"
#include "CQPlotColors.h"

#include "copasi/plot/CPlotSpecification.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include <copasi/plotUI/C2DCurveData.h>
#include <copasi/plotUI/CBandedGraphData.h>
#include <copasi/plotUI/CHistoCurveData.h>
#include <copasi/plotUI/CSpectorgramData.h>

#include <copasi/plotUI/C2DPlotCurve.h>
#include <copasi/plotUI/CPlotSpectogram.h>

#include <copasi/plotUI/CLinearColorMap.h>

#include <QApplication>

#ifdef COPASI_USE_QWT

#  include <qwt_plot.h>
#  include <qwt_scale_engine.h>

#  if QWT_VERSION > QT_VERSION_CHECK(6, 0, 0)
#    include <qwt_plot_renderer.h>
#    include <qwt_text.h>
#  endif

#  if QWT_VERSION < QT_VERSION_CHECK(6, 0, 0)
// taken from qwt examples/bode
class PrintFilter : public QwtPlotPrintFilter
{
public:
  PrintFilter() {};

  virtual QFont font(const QFont & f, Item, int) const
  {
    QFont f2 = f;
    f2.setPointSize((int)(f.pointSize() * 0.75));
    return f2;
  }
};
#  endif


#if QT_VERSION > QT_VERSION_CHECK(6,0,0)
#include <QRegularExpression>
#endif

#define ActivitySize 8
C_FLOAT64 CQwtPlot::MissingValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();

CQwtPlot::CQwtPlot(QWidget* parent):
  QwtPlot(parent),
  mCurves(0),
  mCurveMap(),
  mSpectograms(0),
  mSpectogramMap(),
  mDataBefore(0),
  mDataDuring(0),
  mDataAfter(0),
  mHaveBefore(false),
  mHaveDuring(false),
  mHaveAfter(false),
  mpPlotSpecification(NULL),
  mNextPlotTime(),
  mIgnoreUpdate(false),
  mpZoomer(NULL),
  mReplotFinished(false)
{}

CQwtPlot::CQwtPlot(const CPlotSpecification* plotspec, QWidget* parent):
  QwtPlot(parent),
  mCurves(0),
  mCurveMap(),
  mSpectograms(0),
  mSpectogramMap(),
  mDataBefore(0),
  mDataDuring(0),
  mDataAfter(0),
  mHaveBefore(false),
  mHaveDuring(false),
  mHaveAfter(false),
  mpPlotSpecification(NULL),
  mNextPlotTime(),
  mIgnoreUpdate(false),
  mpZoomer(NULL),
  mReplotFinished(false)
{
  QwtLegend *legend = new QwtLegend(this);

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  legend->setDefaultItemMode(QwtLegendData::Checkable);
  ((QwtPlotCanvas*)canvas())->setPaintAttribute(QwtPlotCanvas::Opaque, true);

  connect(legend, SIGNAL(checked(const QVariant &, bool, int)),
          SLOT(legendChecked(const QVariant &, bool)));

#else
  legend->setItemMode(QwtLegend::CheckableItem);
  setCanvasLineWidth(0);
  canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, true);
#endif

  // whole legend can not be displayed at bottom on DARWIN
  // maybe a Qwt bug ?!?
#ifdef Darwin
  insertLegend(legend, QwtPlot::TopLegend);
#else
  insertLegend(legend, QwtPlot::BottomLegend);
#endif

  // Set up the zoom facility
  mpZoomer = new ScrollZoomer(canvas());
  mpZoomer->setRubberBandPen(QColor(Qt::black));
  mpZoomer->setTrackerPen(QColor(Qt::black));
  mpZoomer->setTrackerMode(QwtPicker::AlwaysOn);
  mpZoomer->setTrackerFont(this->font());

  // white background better for printing...
  setCanvasBackground(Qt::white);

  //  setTitle(FROM_UTF8(plotspec->getTitle()));

#if QWT_VERSION < QT_VERSION_CHECK(6,0,0)
  connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)),
          SLOT(showCurve(QwtPlotItem *, bool)));
#endif

  // Size the vectors to be able to store information for all activities.
  mData.resize(ActivitySize);
  mObjectValues.resize(ActivitySize);
  mObjectInteger.resize(ActivitySize);
  mDataSize.resize(ActivitySize);
  mDataIndex.clear();

  // Initialize from the plot specification
  initFromSpec(plotspec);
  connect(this, SIGNAL(replotSignal()), this, SLOT(replot()));
}

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
void CQwtPlot::legendChecked(const QVariant &itemInfo, bool on)
{
  QwtPlotItem *plotItem = infoToItem(itemInfo);

  if (plotItem)
    showCurve(plotItem, on);
}
#endif

CPlotSpectogram *
CQwtPlot::createSpectogram(const CPlotItem *plotItem)
{
  QString strLimitZ = FROM_UTF8(plotItem->getValue<std::string>("maxZ"));
  bool flag;
  double limitZ = strLimitZ.toDouble(&flag);

  if (!flag)
    limitZ = std::numeric_limits<double>::quiet_NaN();

  bool logZ = plotItem->getValue<bool>("logZ");

  CPlotSpectogram *pSpectogram = new CPlotSpectogram(
    &mMutex,
    plotItem->getType(),
    plotItem->getActivity(),
    FROM_UTF8(plotItem->getTitle()),
    logZ,
    limitZ,
    plotItem->getValue<bool>("bilinear"));

  pSpectogram->attach(this);
  pSpectogram->setRenderHint(QwtPlotItem::RenderAntialiased);
  QPen pen; pen.setWidthF(0.5);
  pSpectogram->setDefaultContourPen(pen);

  std::string colorMap = *const_cast< CPlotItem * >(plotItem)->assertParameter("colorMap", CCopasiParameter::Type::STRING, std::string("Default"));

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  pSpectogram->setRenderThreadCount(0);

  if (colorMap == "Grayscale")
    {
      QwtLinearColorMap *colorMap = new CLinearColorMap(Qt::white, Qt::black);
      pSpectogram->setColorMap(colorMap);
    }
  else if (colorMap == "Yellow-Red")
    {
      QwtLinearColorMap *colorMap = new CLinearColorMap(Qt::yellow, Qt::red);
      pSpectogram->setColorMap(colorMap);
    }
  else if (colorMap == "Blue-White-Red")
    {
      CLinearColorMap *colorMap = new CLinearColorMap(Qt::blue, Qt::red);
      colorMap->addColorStop(0.5, Qt::white);
      pSpectogram->setColorMap(colorMap);
    }
  else if (colorMap == "Hot")
    {
      CLinearColorMap * colorMap = new CLinearColorMap(QColor(50, 0, 0), Qt::white);
      colorMap->addColorStop(0.2, QColor(180, 10, 0));
      colorMap->addColorStop(0.4, QColor(245, 50, 0));
      colorMap->addColorStop(0.6, QColor(255, 150, 10));
      colorMap->addColorStop(0.8, QColor(255, 255, 50));
      pSpectogram->setColorMap(colorMap);
    }
  else if (colorMap == "Cold")
    {
      CLinearColorMap * colorMap = new CLinearColorMap(QColor(0, 0, 50), Qt::white);
      colorMap->addColorStop(0.2, QColor(0, 10, 180));
      colorMap->addColorStop(0.4, QColor(0, 50, 245));
      colorMap->addColorStop(0.6, QColor(10, 150, 255));
      colorMap->addColorStop(0.8, QColor(50, 255, 255));
      pSpectogram->setColorMap(colorMap);
    }
  else
    {
      QwtLinearColorMap *colorMap = new CLinearColorMap(Qt::darkCyan, Qt::red);
      colorMap->addColorStop(0.1, Qt::cyan);
      colorMap->addColorStop(0.6, Qt::green);
      colorMap->addColorStop(0.95, Qt::yellow);

      pSpectogram->setColorMap(colorMap);
    }

#else

  if (colorMap == "Grayscale")
    {
      CLinearColorMap colorMap(Qt::white, Qt::black);
      pSpectogram->setColorMap(colorMap);
    }
  else if (colorMap == "Yellow-Red")
    {
      CLinearColorMap colorMap(Qt::yellow, Qt::red);
      pSpectogram->setColorMap(colorMap);
    }
  else if (colorMap == "Blue-White-Red")
    {
      CLinearColorMap colorMap(Qt::blue, Qt::red);
      colorMap.setAbsoluteStop(0.0, Qt::white);
      pSpectogram->setColorMap(colorMap);
    }
  else
    {
      CLinearColorMap colorMap(Qt::darkCyan, Qt::red);
      colorMap.addColorStop(0.1, Qt::cyan);
      colorMap.addColorStop(0.6, Qt::green);
      colorMap.addColorStop(0.95, Qt::yellow);

      pSpectogram->setColorMap(colorMap);
    }

#endif

  QString contours = FROM_UTF8(* const_cast< CPlotItem * >(plotItem)->assertParameter("contours", CCopasiParameter::Type::STRING, std::string("")));

  int levels = contours.toInt(&flag);

  if (flag)
    {
      // have only a certain number of levels, applying them here
      QwtValueList contourLevels;

      for (double level = 0.5; level < levels; level += 1.0)
        contourLevels += level;

      pSpectogram->setContourLevels(contourLevels);
      pSpectogram->setDisplayMode(QwtPlotSpectrogram::ContourMode, true);
    }
  else
    {
      // have explicit list of numbers to plot
#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
      QStringList list = contours.split(QRegExp(",| |;"), QString::SkipEmptyParts);
#elif QT_VERSION < QT_VERSION_CHECK(6,0,0)
      QStringList list = contours.split(QRegExp(",| |;"), Qt::SkipEmptyParts);
#else
      QStringList list = contours.split(QRegularExpression(",| |;"), Qt::SkipEmptyParts);
#endif
      QwtValueList contourLevels;

      foreach(const QString & level, list)
      {
        contourLevels += level.toDouble();
      }

      pSpectogram->setContourLevels(contourLevels);
      pSpectogram->setDisplayMode(QwtPlotSpectrogram::ContourMode, true);
    }

  CDataModel* dataModel = mpPlotSpecification->getObjectDataModel();
  assert(dataModel != NULL);

  const CObjectInterface * pObj = dataModel->getObject((plotItem->getChannels()[0]));

  if (pObj == NULL)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6, plotItem->getChannels()[0].c_str());
    }

  setAxisTitle(xBottom, FROM_UTF8(pObj != NULL ? pObj->getObjectDisplayName() : "Not found"));
  enableAxis(xBottom);

  pObj = dataModel->getObject((plotItem->getChannels()[1]));

  if (pObj == NULL)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6, plotItem->getChannels()[1].c_str());
    }

  setAxisTitle(yLeft, FROM_UTF8(pObj != NULL ? pObj->getObjectDisplayName() : "Not found"));
  enableAxis(yLeft);

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  setAxisScaleEngine(xTop,
                     logZ ? (QwtScaleEngine *)new QwtLogScaleEngine() : (QwtScaleEngine *)new QwtLinearScaleEngine());
#else
  setAxisScaleEngine(xTop,
                     logZ ? (QwtScaleEngine *)new QwtLog10ScaleEngine() : (QwtScaleEngine *)new QwtLinearScaleEngine());
#endif

  pObj = dataModel->getObject((plotItem->getChannels()[2]));

  if (pObj == NULL)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6, plotItem->getChannels()[2].c_str());
    }

  setAxisTitle(xTop, FROM_UTF8(pObj != NULL ? pObj->getObjectDisplayName() : "Not found"));

  QwtScaleWidget *topAxis = axisWidget(QwtPlot::xTop);
  topAxis->setColorBarEnabled(true);

  enableAxis(xTop);

  return pSpectogram;
}

void
CQwtPlot::setSymbol(C2DPlotCurve * pCurve, QwtSymbol::Style symbol,
                    QColor color, int size, float width)
{
#if QWT_VERSION > QT_VERSION_CHECK(6, 0, 0)
  pCurve->setSymbol(new QwtSymbol(symbol, QBrush(), QPen(QBrush(color), width), QSize(size, size)));
  pCurve->setLegendAttribute(QwtPlotCurve::LegendShowSymbol);
#else
  pCurve->setSymbol(QwtSymbol(symbol, QBrush(), QPen(QBrush(color), 2), QSize(size, size)));
#endif
}

bool CQwtPlot::initFromSpec(const CPlotSpecification* plotspec)
{

  mIgnoreUpdate = true;
  mpPlotSpecification = plotspec;

  if (mpZoomer) mpZoomer->setEnabled(false);

  // size_t k, kmax = mpPlotSpecification->getItems().size();

  setTitle(FROM_UTF8(mpPlotSpecification->getTitle()));

  mCurves.resize(mpPlotSpecification->getItems().size());
  mCurves = NULL;

  mSpectograms.resize(mpPlotSpecification->getItems().size());
  mSpectograms = NULL;

  std::map< std::string, C2DPlotCurve * >::iterator found;

  CDataVector< CPlotItem >::const_iterator itPlotItem = mpPlotSpecification->getItems().begin();
  CDataVector< CPlotItem >::const_iterator endPlotItem = mpPlotSpecification->getItems().end();

  CVector< bool > Visible(mpPlotSpecification->getItems().size());
  Visible = true;
  bool * pVisible = Visible.array();

  for (; itPlotItem != endPlotItem; ++itPlotItem, ++pVisible)
    {
      // Qwt does not like it to reuse the curve as this may lead to access
      // violation. We therefore delete the curves but remember their visibility.
      if ((found = mCurveMap.find(itPlotItem->CCopasiParameter::getKey())) != mCurveMap.end())
        {
          *pVisible = found->second->isVisible();
        }
    }

  // Remove unused curves if definition has changed
  std::map< std::string, C2DPlotCurve * >::iterator it = mCurveMap.begin();
  std::map< std::string, C2DPlotCurve * >::iterator end = mCurveMap.end();

  for (; it != end; ++it)
    pdelete(it->second);

  mCurveMap.clear();

  std::map< std::string, CPlotSpectogram * >::iterator it2 = mSpectogramMap.begin();
  std::map< std::string, CPlotSpectogram * >::iterator end2 = mSpectogramMap.end();

  for (; it2 != end2; ++it2)
    pdelete(it2->second);

  mSpectogramMap.clear();

  itPlotItem = mpPlotSpecification->getItems().begin();
  pVisible = Visible.array();
  C2DPlotCurve ** ppCurve = mCurves.array();
  CPlotSpectogram** ppSpectogram = mSpectograms.array();
  unsigned long int k = 0;
  bool needLeft = false;
  bool needRight = false;

  for (; itPlotItem != endPlotItem; ++itPlotItem, ++pVisible, ++ppCurve, ++ppSpectogram, ++k)
    {
      if (itPlotItem->getType() == CPlotItem::spectogram)
        {
          CPlotSpectogram* pSpectogram = createSpectogram(itPlotItem);

          *ppSpectogram = pSpectogram;
          mSpectogramMap[itPlotItem->CCopasiParameter::getKey()] = pSpectogram;

          showCurve(pSpectogram, *pVisible);

          needLeft = true;

          continue;
        }

      // set up the curve
      C2DPlotCurve * pCurve = new C2DPlotCurve(&mMutex,
          itPlotItem->getType(),
          itPlotItem->getActivity(),
          FROM_UTF8(itPlotItem->getTitle()));
      *ppCurve = pCurve;

      mCurveMap[itPlotItem->CCopasiParameter::getKey()] = pCurve;

      //color handling should be similar for different curve types
      QColor color;

      if (pCurve->getType() == CPlotItem::curve2d
          || pCurve->getType() == CPlotItem::histoItem1d
          || pCurve->getType() == CPlotItem::bandedGraph)
        {
          std::string colorstr = itPlotItem->getValue< std::string >("Color");
          color = CQPlotColors::getColor(colorstr, k);
        }

      pCurve->setPen(color);
      pCurve->attach(this);

      showCurve(pCurve, *pVisible);

      if (pCurve->getType() == CPlotItem::curve2d
          || pCurve->getType() == CPlotItem::histoItem1d
          || pCurve->getType() == CPlotItem::bandedGraph)
        {
          needLeft = true;
          pCurve->setRenderHint(QwtPlotItem::RenderAntialiased);

          unsigned C_INT32 linetype = itPlotItem->getValue< unsigned C_INT32 >("Line type");
          CPlotItem::LineType lineType = (CPlotItem::LineType) linetype;

          if (lineType == CPlotItem::LineType::Lines ||
              lineType == CPlotItem::LineType::LinesAndSymbols)
            {
              pCurve->setStyle(QwtPlotCurve::Lines);
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
              pCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
#endif

              unsigned C_INT32 linesubtype = itPlotItem->getValue< unsigned C_INT32 >("Line subtype");
              CPlotItem::LineStyle lineStyle = (CPlotItem::LineStyle) linesubtype;
              C_FLOAT64 width = itPlotItem->getValue< C_FLOAT64 >("Line width");

              switch (lineStyle)
                {
                  case CPlotItem::LineStyle::Dotted:
                    pCurve->setPen(QPen(QBrush(color), width, Qt::DotLine, Qt::FlatCap));
                    break;

                  case CPlotItem::LineStyle::Dashed:
                    pCurve->setPen(QPen(QBrush(color), width, Qt::DashLine));
                    break;

                  case CPlotItem::LineStyle::DotDash:
                    pCurve->setPen(QPen(QBrush(color), width, Qt::DashDotLine));
                    break;

                  case CPlotItem::LineStyle::DotDotDash:
                    pCurve->setPen(QPen(QBrush(color), width, Qt::DashDotDotLine));
                    break;

                  case CPlotItem::LineStyle::None:
                    pCurve->setStyle(QwtPlotCurve::NoCurve);
                    break;

                  case CPlotItem::LineStyle::Solid:
                  default:
                    pCurve->setPen(QPen(QBrush(color), width, Qt::SolidLine));
                    break;
                }
            }

          if (lineType == CPlotItem::LineType::Points)
            {
              C_FLOAT64 width = itPlotItem->getValue< C_FLOAT64 >("Line width");
              pCurve->setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap));
              pCurve->setStyle(QwtPlotCurve::Dots);
            }

          if (lineType == CPlotItem::LineType::Symbols)
            {
              pCurve->setStyle(QwtPlotCurve::NoCurve);
            }

          if (lineType == CPlotItem::LineType::Symbols ||
              lineType == CPlotItem::LineType::LinesAndSymbols) //line+symbols
            {
              unsigned C_INT32 symbolsubtype = itPlotItem->getValue< unsigned C_INT32 >("Symbol subtype");
              CPlotItem::SymbolType symbolType = (CPlotItem::SymbolType) symbolsubtype;

              switch (symbolType) //symbol type
                {
                  case CPlotItem::SymbolType::LargeCross:
                  case CPlotItem::SymbolType::Plus:
                    setSymbol(pCurve, QwtSymbol::Cross, color, 7, 2);

                    break;

                  case CPlotItem::SymbolType::Circle:
                    setSymbol(pCurve, QwtSymbol::Ellipse, color, 8, 1);
                    break;

                  case CPlotItem::SymbolType::Square:
                    setSymbol(pCurve, QwtSymbol::Rect, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::Diamond:
                    setSymbol(pCurve, QwtSymbol::Diamond, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::xCross:
                    setSymbol(pCurve, QwtSymbol::XCross, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::Star:
                    setSymbol(pCurve, QwtSymbol::Star2, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::TriangleUp:
                    setSymbol(pCurve, QwtSymbol::UTriangle, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::TriangleDown:
                    setSymbol(pCurve, QwtSymbol::DTriangle, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::TriangleLeft:
                    setSymbol(pCurve, QwtSymbol::LTriangle, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::TriangleRight:
                    setSymbol(pCurve, QwtSymbol::RTriangle, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::hDash:
                    setSymbol(pCurve, QwtSymbol::HLine, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::vDash:
                    setSymbol(pCurve, QwtSymbol::VLine, color, 7, 2);
                    break;

                  case CPlotItem::SymbolType::SmallCross:
                  default:
                    setSymbol(pCurve, QwtSymbol::Cross, color, 5, 1);
                    break;

                  case CPlotItem::SymbolType::None:
                    break;
                }
            }
        } //2d curves and banded graphs

      if (pCurve->getType() == CPlotItem::bandedGraph)
        {
          //set fill color
          QColor c = color;
          int alpha = 64;

          if (itPlotItem->getParameter("alpha"))
            alpha = itPlotItem->getValue< C_INT32 >("alpha");

          c.setAlpha(alpha);
          pCurve->setBrush(c);
        }

      if (pCurve->getType() == CPlotItem::histoItem1d)
        {
          pCurve->setIncrement(itPlotItem->getValue< C_FLOAT64 >("increment"));

          pCurve->setStyle(QwtPlotCurve::Steps);
          pCurve->setYAxis(QwtPlot::yRight);
          pCurve->setCurveAttribute(QwtPlotCurve::Inverted);

          needRight = true;
        }
    }

  if (plotspec->isLogX())
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
    setAxisScaleEngine(xBottom, new QwtLogScaleEngine());

#else
    setAxisScaleEngine(xBottom, new QwtLog10ScaleEngine());
#endif
  else
    setAxisScaleEngine(xBottom, new QwtLinearScaleEngine());

  setAxisAutoScale(xBottom);

  if (plotspec->isLogY())
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
    setAxisScaleEngine(yLeft, new QwtLogScaleEngine());

#else
    setAxisScaleEngine(yLeft, new QwtLog10ScaleEngine());
#endif
  else
    setAxisScaleEngine(yLeft, new QwtLinearScaleEngine());

  setAxisAutoScale(yLeft);

  enableAxis(yLeft, needLeft);

  if (needRight)
    {
      setAxisScaleEngine(yRight, new QwtLinearScaleEngine());
      setAxisTitle(yRight, "Percent %");
      enableAxis(yRight);
    }

  mIgnoreUpdate = false;

  return true; //TODO really check!
}

const CPlotSpecification *
CQwtPlot::getPlotSpecification() const
{
  return mpPlotSpecification;
}

bool CQwtPlot::compile(CObjectInterface::ContainerList listOfContainer)
{
  clearBuffers();

  size_t i, imax;
  size_t j, jmax;

  std::pair< std::set< const CObjectInterface * >::iterator, bool > Inserted;
  std::pair< Activity, size_t > DataIndex;
  std::vector< std::set < const CObjectInterface * > > ActivityObjects;

  ActivityObjects.resize(ActivitySize);

  // Loop over all curves.
  imax = mpPlotSpecification->getItems().size();
  mDataIndex.resize(imax);

  std::vector< std::vector < std::string > >::iterator itX;

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
                if (*itX->begin() == objectCN) break;

              if (itX == mSaveCurveObjects.end())
                {
                  std::vector < std::string > NewX;
                  NewX.push_back(objectCN);

                  mSaveCurveObjects.push_back(NewX);
                  itX = mSaveCurveObjects.end() - 1;

                  if (!isSpectogram)
                    setAxisUnits(xBottom, pObj);
                }

              if (pItem->getType() == CPlotItem::histoItem1d)
                mSaveHistogramObjects.push_back(objectCN);
            }
          else
            {
              itX->push_back(objectCN);

              if (!isSpectogram)
                setAxisUnits(yLeft, pObj);
            }

          Inserted = ActivityObjects[ItemActivity].insert(pObj);

          if (Inserted.second)
            {
              if (ItemActivity & COutputInterface::BEFORE) mHaveBefore = true;

              if (ItemActivity & COutputInterface::DURING) mHaveDuring = true;

              if (ItemActivity & COutputInterface::AFTER) mHaveAfter = true;

              // The insert was successful
              DataIndex.second = ActivityObjects[ItemActivity].size() - 1;

              // Allocate the data buffer
              mData[ItemActivity].push_back(new CVector<double>(1000));

              // Store the pointer to the current object value. (Only if it has a double or integer value
              // and the value pointer actually exists. If not, use a dummy value.)
              void * tmp;

              const CDataObject * pDataObject = CObjectInterface::DataObject(pObj);

              if (pDataObject != NULL &&
                  (tmp = pObj->getValuePointer()) != NULL &&
                  (pDataObject->hasFlag(CDataObject::ValueInt) || pDataObject->hasFlag(CDataObject::ValueDbl)))
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

  // We need to set the curve data here!
  size_t k = 0;
  C2DPlotCurve ** itCurves = mCurves.array();
  C2DPlotCurve ** endCurves = itCurves + mCurves.size();

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      if (*itCurves == NULL) continue;

      std::vector< CVector< double > * > & data = mData[(*itCurves)->getActivity()];

      switch ((*itCurves)->getType())
        {
          case CPlotItem::curve2d:
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
            (*itCurves)->setData(new C2DCurveData(*data[mDataIndex[k][0].second],
                                                  *data[mDataIndex[k][1].second],
                                                  0));
#else
            (*itCurves)->setData(C2DCurveData(*data[mDataIndex[k][0].second],
                                              *data[mDataIndex[k][1].second],
                                              0));
#endif
            break;

          case CPlotItem::bandedGraph:
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
            (*itCurves)->setData(new CBandedGraphData(*data[mDataIndex[k][0].second],
                                 *data[mDataIndex[k][1].second],
                                 *data[mDataIndex[k][2].second],
                                 0));
#else
            (*itCurves)->setData(CBandedGraphData(*data[mDataIndex[k][0].second],
                                                  *data[mDataIndex[k][1].second],
                                                  *data[mDataIndex[k][2].second],
                                                  0));
#endif
            break;

          case CPlotItem::histoItem1d:
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
            (*itCurves)->setData(new CHistoCurveData(*data[mDataIndex[k][0].second],
                                 0,
                                 mCurves[k]->getIncrement()));
#else
            (*itCurves)->setData(CHistoCurveData(*data[mDataIndex[k][0].second],
                                                 0,
                                                 mCurves[k]->getIncrement()));
#endif
            break;

          default:
            fatalError();
            break;
        }
    }

  k = 0;
  CPlotSpectogram ** itSpectrograms = mSpectograms.array();
  CPlotSpectogram ** endSpectrograms = itSpectrograms + mSpectograms.size();

  for (; itSpectrograms != endSpectrograms; ++itSpectrograms, ++k)
    {
      if (*itSpectrograms == NULL) continue;

      std::vector< CVector< double > * > & data = mData[(*itSpectrograms)->getActivity()];

      switch ((*itSpectrograms)->getType())
        {
          case CPlotItem::spectogram:
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
            (*itSpectrograms)->setData(
              new CSpectorgramData(
                *data[mDataIndex[k][0].second],
                *data[mDataIndex[k][1].second],
                *data[mDataIndex[k][2].second],
                0,
                (*itSpectrograms)->getLogZ(),
                (*itSpectrograms)->getLimitZ(),
                (*itSpectrograms)->getBilinear()
              )
            );
#else
            (*itSpectrograms)->setData(
              CSpectorgramData(
                *data[mDataIndex[k][0].second],
                *data[mDataIndex[k][1].second],
                *data[mDataIndex[k][2].second],
                0,
                (*itSpectrograms)->getLogZ(),
                (*itSpectrograms)->getLimitZ(),
                (*itSpectrograms)->getBilinear()
              ));
#endif
            break;

          default:
            fatalError();
            break;
        }
    }

  mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime();
  mReplotFinished = true;

  return true;
}

void CQwtPlot::output(const Activity & activity)
{
  size_t i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE)) mDataBefore++;
  else if (mHaveDuring && (activity == COutputInterface::DURING)) mDataDuring++;
  else if (mHaveAfter && (activity == COutputInterface::AFTER)) mDataAfter++;

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
                (*data[i])[ndata] = *(C_INT32 *)mObjectValues[ItemActivity][i];
              else
                (*data[i])[ndata] = *mObjectValues[ItemActivity][i];

            ++ndata;
          }
      }

  updatePlot();
}

void CQwtPlot::separate(const Activity & activity)
{
  size_t i, imax;
  C_INT32 ItemActivity;

  if (mHaveBefore && (activity == COutputInterface::BEFORE)) mDataBefore++;

  if (mHaveDuring && (activity == COutputInterface::DURING)) mDataDuring++;

  if (mHaveAfter && (activity == COutputInterface::AFTER)) mDataAfter++;

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

void CQwtPlot::finish()
{

  // We need to force a replot, i.e., the next mNextPlotTime should be in the past.
  mNextPlotTime = 0;

  replot();

  if (mpZoomer)
    {
      mpZoomer->setEnabled(true);
      mpZoomer->setZoomBase();
    }
}

void CQwtPlot::updateCurves(const size_t & activity)
{
  if (activity == C_INVALID_INDEX)
    {
      C_INT32 ItemActivity;

      for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
        updateCurves(ItemActivity);

      return;
    }

  size_t k = 0;
  C2DPlotCurve ** itCurves = mCurves.array();
  C2DPlotCurve ** endCurves = itCurves + mCurves.size();

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      if (*itCurves == NULL) continue;

      if ((size_t)(*itCurves)->getActivity() == activity)
        {
          (*itCurves)->setDataSize(mDataSize[activity]);
        }
    }

  k = 0;
  CPlotSpectogram ** itSpectograms = mSpectograms.array();
  CPlotSpectogram ** endSpectograms = itSpectograms + mSpectograms.size();

  for (; itSpectograms != endSpectograms; ++itSpectograms, ++k)
    {
      if (*itSpectograms == NULL) continue;

      if ((size_t)(*itSpectograms)->getActivity() == activity)
        {
          (*itSpectograms)->setDataSize(mDataSize[activity]);
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
          QwtScaleWidget *topAxis = axisWidget(QwtPlot::xTop);
          const QwtInterval zInterval = (*itSpectograms)->data()->interval(Qt::ZAxis);
          topAxis->setColorBarEnabled(true);

          const QwtColorMap* currentMap = (*itSpectograms)->colorMap();
          const CLinearColorMap* linearColormap = dynamic_cast<const CLinearColorMap*>(currentMap);

          if (linearColormap != NULL)
            topAxis->setColorMap(zInterval, new CLinearColorMap(*linearColormap));
          else
            topAxis->setColorMap(zInterval, const_cast<QwtColorMap*>(currentMap));

          setAxisScale(QwtPlot::xTop, zInterval.minValue(), zInterval.maxValue());
#else

          QwtScaleWidget *topAxis = axisWidget(QwtPlot::xTop);
          topAxis->setColorBarEnabled(true);
          topAxis->setColorMap((*itSpectograms)->data().range(),
                               (*itSpectograms)->colorMap());
          setAxisScale(QwtPlot::xTop,
                       (*itSpectograms)->data().range().minValue(),
                       (*itSpectograms)->data().range().maxValue());

#endif
        }
    }
}

void CQwtPlot::resizeCurveData(const size_t & activity)
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
  C2DPlotCurve ** itCurves = mCurves.array();
  C2DPlotCurve ** endCurves = itCurves + mCurves.size();

  for (; itCurves != endCurves; ++itCurves, ++k)
    {
      if (*itCurves == NULL) continue;

      if ((size_t)(*itCurves)->getActivity() == activity)
        {
          std::vector< CVector< double > * > & data = mData[activity];

          switch ((*itCurves)->getType())
            {
              case CPlotItem::curve2d:
                (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                                             data[mDataIndex[k][1].second]);
                break;

              case CPlotItem::bandedGraph:
                (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                                             data[mDataIndex[k][1].second],
                                             data[mDataIndex[k][2].second]);
                break;

              case CPlotItem::histoItem1d:
                (*itCurves)->reallocatedData(data[mDataIndex[k][0].second],
                                             NULL);
                break;

              default:
                fatalError();
                break;
            }
        }
    }

  k = 0;
  CPlotSpectogram ** itSpectograms = mSpectograms.array();
  CPlotSpectogram ** endSpectograms = itSpectograms + mSpectograms.size();

  for (; itSpectograms != endSpectograms; ++itSpectograms, ++k)
    {
      if (*itSpectograms == NULL) continue;

      if ((size_t)(*itSpectograms)->getActivity() == activity)
        {
          std::vector< CVector< double > * > & data = mData[activity];

          switch ((*itSpectograms)->getType())
            {
              case CPlotItem::spectogram:
                (*itSpectograms)->reallocatedData(data[mDataIndex[k][0].second],
                                                  data[mDataIndex[k][1].second],
                                                  data[mDataIndex[k][2].second]);
                break;

              default:
                fatalError();
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

void CQwtPlot::updatePlot()
{
  if (mReplotFinished)
    {
      mReplotFinished = false;
      emit replotSignal();
    }
}

//-----------------------------------------------------------------------------

/*void CopasiPlot::enableZoom(bool enabled)
{
  zoomOn = enabled;
}*/

//-----------------------------------------------------------------------------

CQwtPlot::~CQwtPlot()
{
  clearBuffers();
}

bool CQwtPlot::saveData(const std::string & filename)
{
  // No objects.
  if (!mObjects.size()) return true;

  // Find out whether we have any data.
  C_INT32 ItemActivity;

  for (ItemActivity = 0; ItemActivity < ActivitySize; ItemActivity++)
    if (mDataSize[ItemActivity] != 0) break;

  // No data
  if (ItemActivity == ActivitySize) return true;

  std::ofstream fs(CLocaleString::fromUtf8(filename).c_str());

  if (!fs.good()) return false;

  // Write the table header
  fs << "# ";

  std::vector< std::vector < std::string > >::const_iterator itX;
  std::vector< std::vector < std::string > >::const_iterator endX =
    mSaveCurveObjects.end();

  std::vector < std::string >::const_iterator it;
  std::vector < std::string >::const_iterator end;

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
            if ((itActivity = mObjectIndex.find(COutputInterface::BEFORE)) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
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
              if (*itData) fs << (**itData)[i];
              else fs << MissingValue;

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
            if ((itActivity = mObjectIndex.find(COutputInterface::DURING)) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::DURING][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
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
              if (*itData) fs << (**itData)[i + *itOffset];
              else fs << MissingValue;

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
            if ((itActivity = mObjectIndex.find(COutputInterface::AFTER)) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::AFTER][itObject->second];
                Offset[i] = 0;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::BEFORE | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataBefore;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
              {
                Data[i] = mData[COutputInterface::DURING | COutputInterface::AFTER][itObject->second];
                Offset[i] = mDataDuring;
                continue;
              }

            if ((itActivity = mObjectIndex.find((COutputInterface::Activity)(COutputInterface::BEFORE | COutputInterface::DURING | COutputInterface::AFTER))) != mObjectIndex.end() &&
                (itObject = itActivity->second.find(*it)) != itActivity->second.end())
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
              if (*itData) fs << (**itData)[i + *itOffset];
              else fs << MissingValue;

              fs << "\t";
            }

          fs << std::endl;
        }
    }

  bool FirstHistogram = true;
  size_t HistogramIndex = 0;

  C2DPlotCurve ** itCurves = mCurves.array();
  C2DPlotCurve ** endCurves = itCurves + mCurves.size();

  for (; (itCurves != endCurves) && (HistogramIndex < mSaveHistogramObjects.size()); ++itCurves, ++HistogramIndex)
    {
      if (*itCurves == NULL) continue;

      if ((*itCurves)->getType() == CPlotItem::histoItem1d)
        {
          if (FirstHistogram)
            {
              fs << "\n# The histograms: \n";
              FirstHistogram = false;
            }

          fs << mSaveHistogramObjects[HistogramIndex] << std::endl;

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
          CHistoCurveData * pData = static_cast< CHistoCurveData * >((*itCurves)->data());
#else
          CHistoCurveData * pData = static_cast< CHistoCurveData * >(&(*itCurves)->data());
#endif
          size_t i, imax = pData->size();

          for (i = 0; i < imax; ++i)
            {
              fs << pData->x(i) << "\t" << pData->y(i) << "\n";
            }
        }
    }

  fs.close();

  if (!fs.good()) return false;

  return true;
}

void CQwtPlot::showCurve(QwtPlotItem *item, bool on)
{
  item->setVisible(on);
  item->setItemAttribute(QwtPlotItem::AutoScale, on);
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
  QwtLegend *lgd = qobject_cast<QwtLegend *>(legend());
  QList<QWidget *> legendWidgets =
    lgd->legendWidgets(itemToInfo(item));

  if (legendWidgets.size() == 1)
    {
      QwtLegendLabel *legendLabel =
        qobject_cast<QwtLegendLabel *>(legendWidgets[0]);

      if (legendLabel)
        legendLabel->setChecked(on);
    }

#else
  QWidget *w = legend()->find(item);

  if (w && w->inherits("QwtLegendItem"))
    static_cast< QwtLegendItem * >(w)->setChecked(on);

#endif

  if (!mIgnoreUpdate)
    replot();
}

void CQwtPlot::setCurvesVisibility(const bool & visibility)
{
  std::map< std::string, C2DPlotCurve * >::iterator it = mCurveMap.begin();
  std::map< std::string, C2DPlotCurve * >::iterator end = mCurveMap.end();

  for (; it != end; ++it)
    {
      it->second->setVisible(visibility);
      it->second->setItemAttribute(QwtPlotItem::AutoScale, visibility);
#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
      QwtLegend *lgd = qobject_cast<QwtLegend *>(legend());
      QList<QWidget *> legendWidgets =
        lgd->legendWidgets(itemToInfo(it->second));

      if (legendWidgets.size() == 1)
        {
          QwtLegendLabel *legendLabel =
            qobject_cast<QwtLegendLabel *>(legendWidgets[0]);

          if (legendLabel)
            legendLabel->setChecked(visibility);
        }

#else
      QWidget *w = legend()->find(it->second);

      if (w && w->inherits("QwtLegendItem"))
        static_cast< QwtLegendItem * >(w)->setChecked(visibility);

#endif
    }

  if (!mIgnoreUpdate)
    replot();
}

void CQwtPlot::clearBuffers()
{
  mObjects.clear();

  size_t Activity;
  size_t i, imax;

  for (Activity = 0; Activity < ActivitySize; Activity++)
    {
      std::vector< CVector< double > * > & data = mData[Activity];

      // Delete each QMemArray
      for (i = 0, imax = data.size(); i < imax; i++)
        if (data[i] != NULL) delete data[i];

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

void CQwtPlot::setAxisUnits(const C_INT32 & index,
                            const CObjectInterface * pObjectInterface)
{
  setAxisTitle(index,
               getAxisText(
                 index == xBottom ? CPlotInterface::Axis::xAxis : CPlotInterface::Axis::yAxis,
                 pObjectInterface
               ));
}

void CQwtPlot::toggleLogX(bool logX)
{
  if (logX)
    {

#  if QWT_VERSION > QT_VERSION_CHECK(6, 0, 0)
      setAxisScaleEngine(QwtPlot::xBottom, new QwtLogScaleEngine());
#  else
      setAxisScaleEngine(QwtPlot::xBottom, new QwtLog10ScaleEngine());
#  endif
    }
  else
    {
      setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine());
    }

  setAxisAutoScale(QwtPlot::xBottom);
  replot();
  update();
}

void CQwtPlot::toggleLogY(bool logY)
{
  if (logY)
    {
#  if QWT_VERSION > QT_VERSION_CHECK(6, 0, 0)
      setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine());
#  else
      setAxisScaleEngine(QwtPlot::yLeft, new QwtLog10ScaleEngine());
#  endif
    }
  else
    {
      setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine());
    }

  setAxisAutoScale(QwtPlot::yLeft);
  //mpPlot->updateAxes();
  replot();
  update();
}

void CQwtPlot::resetZoom()
{
  if (mpZoomer)
    mpZoomer->zoom(0);
}

QString CQwtPlot::titleText() const
{
  return title().text();
}

void CQwtPlot::render(QPainter * painter, QRect rect)
{
#  if QWT_VERSION > QT_VERSION_CHECK(6, 0, 0)
  QwtPlotRenderer renderer;
  renderer.render(this, painter, rect);
#  else
  print(&painter, rect, PrintFilter());
#  endif
}

// virtual
void CQwtPlot::replot()
{
  if (mNextPlotTime < CCopasiTimeVariable::getCurrentWallTime())
    {
      // skip rendering when shift is pressed
      Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();

      if (((int)mods & (int)Qt::ShiftModifier) == (int)Qt::ShiftModifier &&
          !mNextPlotTime.isZero())
        {
          mReplotFinished = true;
          return;
        }

      CCopasiTimeVariable Delta = CCopasiTimeVariable::getCurrentWallTime();

      {
        QMutexLocker Locker(&mMutex);
        updateCurves(C_INVALID_INDEX);
      }

      QwtPlot::replot();

      Delta = CCopasiTimeVariable::getCurrentWallTime() - Delta;

      if (!mSpectogramMap.empty())
        mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 10 * Delta.getMicroSeconds();
      else
        mNextPlotTime = CCopasiTimeVariable::getCurrentWallTime() + 3 * Delta.getMicroSeconds();
    }

  mReplotFinished = true;
}

#endif // COPASI_USE_QWT
