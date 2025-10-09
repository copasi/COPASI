#include "CQPLPlotWidget.h"
#include "copasi/utilities/CProfileSettings.h"  
#include "qtUtilities.h"
#include "CQMultipleSelectionDialog.h"

#include <QFileDialog>
#include <QScrollArea>
#include <QDebug>

#include <copasi/utilities/json.hpp>
#include <copasi/utilities/stats.hpp>

#ifdef COPASI_USE_QCUSTOMPLOT
#include <qcustomplot.h>
#endif

CQPLPlotWidget::CQPLPlotWidget(QWidget * parent)
{
  setupUi(this);
}

void CQPLPlotWidget::loadSettings(const CProfileSettings * pSettings)
{
  mpTxtTarget->setText(FROM_UTF8(pSettings->getDirectory()));

  auto * pGroup = pSettings->getGroup("Plot");
  if (!pGroup)
    return;

  mpTxtScaleBottom->setText(QString::number(pGroup->getValue< double >("Scale Bottom")));
  mpTxtScaleTop->setText(QString::number(pGroup->getValue< double >("Scale Top")));
  mpTxtThresholds->setText(FROM_UTF8(pGroup->getValue< std::string >("Thresholds")));
  mpTxtVertical->setText(FROM_UTF8(pGroup->getValue< std::string >("Vertical Lines")));
}

void CQPLPlotWidget::saveSettings(CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  pSettings->setValue< std::string >("Directory", TO_UTF8(mpTxtTarget->text()));
  
  auto * pGroup = pSettings->getGroup("Plot");
  if (!pGroup)
    return;

  pGroup->setValue<double>("Scale Bottom", mpTxtScaleBottom->text().toDouble());
  pGroup->setValue<double>("Scale Top", mpTxtScaleTop->text().toDouble());
  pGroup->setValue<std::string>("Thresholds", TO_UTF8(mpTxtThresholds->text()));
  pGroup->setValue<std::string>("Vertical Lines", TO_UTF8(mpTxtVertical->text()));
  
}

QResultMap CQPLPlotWidget::globFiles(const QString& directory, const QString& pattern)
{
  QDir dir(directory, pattern, QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoDotAndDotDot);
  auto list = dir.entryList();
  
  QResultMap map;
  for (QString& entry : list)
  {
    if (!entry.endsWith("_high.txt"))
      continue;
    
    // get the base name
    auto base = entry.left(entry.lastIndexOf("_"));

    // verify that the "_low.txt" file exists
    if (!dir.exists(base + "_low.txt"))
      continue;

    map[base] =  std::make_pair(
      directory + "/" + base + "_low.txt", 
      directory + "/" + base + "_high.txt");
  }
  return map;
}

void CQPLPlotWidget::browseDirectory()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", "", QFileDialog::ShowDirsOnly);
  if (dir.isEmpty())
    return;

	mpTxtTarget->setText(dir);
}

void CQPLPlotWidget::addThreshold()
{
  QStringList allThresholds;
  allThresholds.append("default_68");
  allThresholds.append("default_95");
  allThresholds.append("schaber_chi2_1p");
  allThresholds.append("schaber_chi2_p");
  allThresholds.append("schaber_fratio_p");
  allThresholds.append("donaldson_fratio_1p");

  QStringList currentThresholds = mpTxtThresholds->text().split(";");

  // show selection dialog with all thresholds, selecting the ones that are already in the currentThresholds list
  CQMultipleSelectionDialog* dlg = new CQMultipleSelectionDialog(this);
  dlg->setWindowTitle("Select Thresholds");
  dlg->setSelectionList(allThresholds);
  dlg->setCurrentSelection(currentThresholds);
  if (dlg->exec() != QDialog::Accepted)
    return;
  mpTxtThresholds->setText(dlg->getSelection().join(";"));
}

std::vector< std::pair<double, QPen> > computeThresholds(const QStringList& thresholds, double obj_val, double m, double n, double alpha = 0.05)
{
  std::vector< std::pair<double, QPen> > computed;
  // compute thresholds using kthohr/stats
  // threshold for COPASI chi2 alpha is 68% (sahle)
  if (thresholds.contains("default_68") || thresholds.contains("copasi_68"))
  {
    // the scipy.stats chi2.isf is the inverse of the chi2 distribution function
    // in kthohr/stats, this is qchisq
    int df = 1;    
    double c0 = stats::qchisq(1 - 0.32, df);
    double threshold = obj_val * (1 + c0 / (n - m));
    computed.push_back(std::make_pair(threshold, QPen(Qt::blue, 2, Qt::DashLine)));
  }
  // threshold for COPASI chi2 alpha is 95% (sahle)
  if (thresholds.contains("default_95") || thresholds.contains("copasi_95"))
  {
    int df = 1;    
    double c0 = stats::qchisq(1 - alpha, df);
    double threshold = obj_val * (1 + c0 / (n - m));
    computed.push_back(std::make_pair(threshold, QPen(Qt::blue, 2, Qt::DotLine)));
  }
  // estimating chi-square value fitting one parameter (schaber)
  if (thresholds.contains("schaber_chi2_1p"))
  {
    int df = 1;    
    double c1 = stats::qchisq(1 - alpha, df);
    double threshold = obj_val * std::exp(c1 / n);
    computed.push_back(std::make_pair(threshold, QPen(Qt::green, 2, Qt::DashLine)));
  }
  // estimating chi-square value fitting m parameters (schaber)
  if (thresholds.contains("schaber_chi2_p"))
  {
    int df = m;    
    double c2 = stats::qchisq(1 - alpha, df);
    double threshold = obj_val * std::exp(c2 / n);
    computed.push_back(std::make_pair(threshold, QPen(Qt::green, 2, Qt::DotLine)));
  }
  // estimating fratio value fitting m parameters (schaber)
  if (thresholds.contains("schaber_fratio_p"))
  {
    int df = m;    
    double c3 = stats::qf(1 - alpha, df, n - m);
    double threshold = obj_val * (1 + (m / (n - m)) * c3);
    computed.push_back(std::make_pair(threshold, QPen(Qt::red, 2, Qt::DotLine)));
  }
  // estimating chi-square value fitting 1 parameter (donaldson)
  if (thresholds.contains("donaldson_fratio_1p"))
  {
    int df = 1;    
    double c4 = stats::qf(1 - alpha, df, n - m);
    double threshold = obj_val * (1 + c4 / (n - m));
    computed.push_back(std::make_pair(threshold, QPen(QColor(255, 127, 14), 2, Qt::DotLine)));
  }

  return computed;
}

std::vector< std::pair<double, QPen> > computeVerticals(const QStringList& verticals, double param_value, double param_sd)
{
  std::vector< std::pair<double, QPen> > computed;
  for (auto& vertical : verticals)
  {
    if (vertical.contains("VALUE"))
      computed.push_back(std::make_pair(param_value, QPen(QColor(192, 192, 192), 2, Qt::DotLine)));
    if (vertical.endsWith("SD"))
    {
      double multiplier = vertical.left(vertical.lastIndexOf("SD")).toDouble();
      computed.push_back(std::make_pair(param_value + multiplier * param_sd, QPen(QColor(173, 216, 230), 2, Qt::DotLine)));
      computed.push_back(std::make_pair(param_value - multiplier * param_sd, QPen(QColor(173, 216, 230), 2, Qt::DotLine)));
    }
    
  }
  return computed;
}

void CQPLPlotWidget::generatePlots()
{
  mMap = globFiles(mpTxtTarget->text(), "*.txt");

  // clear all widgets from mpScrollContents widget
  
  if (mpScrollContents->layout())
    {
      for (auto * pWidget : mpScrollContents->findChildren< QWidget * >())
        {
          mpScrollContents->layout()->removeWidget(pWidget);
          delete pWidget;
        }
    }
  
  QVBoxLayout * layout = mpScrollContents->layout() != NULL ? qobject_cast< QVBoxLayout *> (mpScrollContents->layout()) : new QVBoxLayout(mpScrollContents);
  

  // read the info.json file
  QFile file(mpTxtTarget->text() + "/" + "_info.json");
  double obj_val; 
  int num_params;
  int num_data;
  std::vector<double> param_sds;
  std::vector< double > param_values;
  std::vector< std::string > param_names;
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream stream(&file);
      auto info = nlohmann::json::parse(stream.readAll().toStdString());
      obj_val = info["obj"].get<double>();
      num_params = info["num_params"].get<int>();
      num_data = info["num_data"].get<int>();
      param_sds = info["param_sds"].get<std::vector<double>>();
      param_values = info["param_values"].get< std::vector< double > >();
      param_names = info["param_names"].get< std::vector< std::string > >();
      file.close();
    }

  auto thresholds = computeThresholds(mpTxtThresholds->text().split(";"), obj_val, num_params, num_data);
  double scale_bottom = mpTxtScaleBottom->text().toDouble();
  double scale_top = mpTxtScaleTop->text().toDouble();

  #ifdef COPASI_USE_QCUSTOMPLOT
  // create a new widget for each file
  for (auto it = mMap.constBegin(); it != mMap.constEnd(); ++it)
  {
    // read the two tsv files 
    QFile fileLow(it.value().first);
    QFile fileHigh(it.value().second);
    if (!fileLow.open(QIODevice::ReadOnly | QIODevice::Text))
      continue;
    if (!fileHigh.open(QIODevice::ReadOnly | QIODevice::Text))
      continue;

    // create a new qcustomplot widget for each file 
    // and add a plot to the scroll area
    auto* pPlot = new QCustomPlot();


    // read the low file
    QTextStream streamLow(&fileLow);
    QTextStream streamHigh(&fileHigh);

    QVector<double> x, y;
    bool first = true;
    QString label;
    while (!streamLow.atEnd())
    {
      auto lineLow = streamLow.readLine();
      auto parts = lineLow.split("\t");
      if (first)
        {
          label = parts[0];
          first = false;
          continue;
        }
      if (parts.size() < 3)
        continue;
      x.append(parts[0].toDouble());
      y.append(parts[2].toDouble());
    }
    
    first = true;
    while (!streamHigh.atEnd())
    {
      auto lineHigh = streamHigh.readLine();
      if (first) { first = false; continue;}
      auto parts = lineHigh.split("\t");
      if (parts.size() < 3)
        continue;
      x.append(parts[0].toDouble());
      y.append(parts[2].toDouble());
    }

    // compute y_min and y_max
    auto y_min = *std::min_element(y.begin(), y.end());
    if (!std::isnan(scale_bottom) && scale_bottom < y_min)
      y_min = scale_bottom;

    auto y_max = *std::max_element(y.begin(), y.end());
    if (!std::isnan(scale_top) && scale_top > y_max)
      y_max = scale_top;

    // find the index of the parameter in the param_names vector
    auto index_pos = std::find(param_names.begin(), param_names.end(), label.toStdString());
    if (index_pos == param_names.end())
      continue;

    int param_index = index_pos - param_names.begin();
    double param_value = param_values[param_index];
    double param_sd = param_sds[param_index];

    // add the graph to the plot
    auto* pGraph = pPlot->addGraph();
    pGraph->setPen(QPen(Qt::red, 2));
    pGraph->setLineStyle(QCPGraph::lsLine);
    pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
    pGraph->setAntialiasedFill(false);
    pGraph->setAntialiased(true);
    pGraph->setAntialiased(true);
    
    if (x.empty())
      continue;
    
    pGraph->setData(x, y);

    // set the axis labels
    pPlot->xAxis->setLabel(label);
    pPlot->yAxis->setLabel("Value");

    // set the axis ranges
    pPlot->xAxis->setRange(x.first(), x.last());
    pPlot->yAxis->setRange(y.first(), y.last());

    // set the plot title
    pPlot->plotLayout()->insertRow(0);
    pPlot->plotLayout()->addElement(0, 0, new QCPTextElement(pPlot, QString("Profile for %1 (around %2 with sd %3)").arg(label).arg(param_value).arg(param_sd)));

    // add a silver dotted line with the obj value 
    auto* pLine = pPlot->addGraph();
    pLine->setPen(QPen(QColor(192, 192, 192), 2, Qt::DotLine));
    pLine->setLineStyle(QCPGraph::lsLine);
    pLine->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
    pLine->setAntialiasedFill(false);
    pLine->setAntialiased(true);
    pLine->setData(QVector<double>{x.first(), x.last()}, QVector<double>{obj_val, obj_val});


    // add the thresholds to the plot as lines 
    for (auto& threshold : thresholds)
    {
      auto* pThreshold = pPlot->addGraph();
      pThreshold->setPen(threshold.second);
      pThreshold->setLineStyle(QCPGraph::lsLine);
      pThreshold->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
      pThreshold->setAntialiased(true);
      pThreshold->setData(QVector<double>{x.first(), x.last()}, QVector<double>{threshold.first, threshold.first});
    }

    // add vertical lines
    auto verticals = computeVerticals(mpTxtVertical->text().split(";"), param_value, param_sd);

    for (auto & vertical : verticals)
    {
      auto* pVertical = pPlot->addGraph();
      pVertical->setPen(vertical.second);
      pVertical->setLineStyle(QCPGraph::lsLine);
      pVertical->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
      pVertical->setAntialiased(true);
      pVertical->setData(QVector<double>{vertical.first, vertical.first}, QVector<double>{y_min, y_max});
    }

    // scale axes automatically and replot
    pPlot->rescaleAxes();

    // if range is specified, use it
    if (!std::isnan(scale_bottom))
      pPlot->yAxis->setRangeLower(scale_bottom);
    if (!std::isnan(scale_top))
        pPlot->yAxis->setRangeUpper(scale_top);

    pPlot->replot();

    // allow plot to be navigated with mouse
    pPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // show tooltips on hover
    connect(pPlot, &QCustomPlot::mouseMove, this, [=](QMouseEvent *event) {
        // Get the pixel coordinates of the mouse
        int x_pixel = event->pos().x();
        int y_pixel = event->pos().y();

        // Convert the pixel coordinates to plot coordinates
        double x_coord = pPlot->xAxis->pixelToCoord(x_pixel);

        // Find the closest data point on the graph
        QCPGraph *graph = pPlot->graph(0);
        if (graph) {
            // Use findBegin or findEnd to locate the closest data index
            int index = graph->findBegin(x_coord);
            double x_data = graph->dataMainKey(index);
            double y_data = graph->dataMainValue(index);

            // Display this data using a QToolTip
            QToolTip::showText(QCursor::pos(), QString("X: %1\nY: %2").arg(x_data).arg(y_data));
        } else {
            QToolTip::hideText();
        }
    });
    // add the plot to the layout
    layout->addWidget(pPlot);
    
  }
  #endif
}

void CQPLPlotWidget::savePlots()
{
  // open a save dialog filter for PNG files
  QString fileName = QFileDialog::getSaveFileName(this, "Save Plots", "", "PNG Files (*.png)");
  if (fileName.isEmpty())
    return;

  // Set the desired scale factor for higher resolution rendering
  int scale = 2;
  
  // Calculate the actual content size in pixels
  QSize contentSize = mpScrollContents->size();
  
  // Create a scaled pixmap for high-resolution rendering
  QPixmap scaledPixmap(contentSize * scale);
  scaledPixmap.fill(Qt::transparent);
  QPainter pixmapPainter(&scaledPixmap);
  pixmapPainter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  pixmapPainter.scale(scale, scale);
  mpScrollContents->render(&pixmapPainter);
  pixmapPainter.end();
  
  // Save the scaled pixmap as PNG
  scaledPixmap.save(fileName, "PNG");
}
