// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQPLPlotWidget.h"
#include "copasi/utilities/CProfileSettings.h"
#include "qtUtilities.h"
#include "CQMultipleSelectionDialog.h"

#include <QFileDialog>
#include <QScrollArea>
#include <QDebug>

#include <copasi/utilities/json.hpp>
#include <copasi/utilities/stats.hpp>
#include "copasi/resourcesUI/CQIconResource.h"

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
  mpTxtPrefix->setText(FROM_UTF8((*pSettings)["Prefix"].get<std::string>()));

  auto & plot = (*pSettings)["Plot"];

  mpTxtScaleBottom->setText(QString::number(plot.at("Scale Bottom").get<double>()));
  mpTxtScaleTop->setText(QString::number(plot.at("Scale Top").get<double>()));
  mpTxtThresholds->setText(FROM_UTF8(plot.at("Thresholds").get<std::string>()));
  mpTxtVertical->setText(FROM_UTF8(plot.at("Vertical Lines").get<std::string>()));

  mpSettings = const_cast< CProfileSettings * >(pSettings);
}

void CQPLPlotWidget::saveSettings(CProfileSettings * pSettings)
{
  if (!pSettings)
    return;

  (*pSettings)["Directory"] = TO_UTF8(mpTxtTarget->text());
  (*pSettings)["Prefix"] = TO_UTF8(mpTxtPrefix->text());

  auto & plot = (*pSettings)["Plot"];

  plot["Scale Bottom"] = mpTxtScaleBottom->text().toDouble();
  plot["Scale Top"] = mpTxtScaleTop->text().toDouble();
  plot["Thresholds"] = TO_UTF8(mpTxtThresholds->text());
  plot["Vertical Lines"] = TO_UTF8(mpTxtVertical->text());

  pSettings->save();
}

QResultMap CQPLPlotWidget::globFiles(const QString& directory, const QString& pattern)
{
  QDir dir(directory, pattern, QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::NoDotAndDotDot);
  auto list = dir.entryList();

  QResultMap map;
  for (QString& entry : list)
  {
    if (!entry.startsWith(mpTxtPrefix->text()) ||  !entry.endsWith("_high.txt"))
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

std::vector< LineArgs > computeThresholds(const QStringList& thresholds, double obj_val, double m, double n, double alpha = 0.05)
{
  std::vector< LineArgs > computed;
  // compute thresholds using kthohr/stats
  for (const QString& threshold : thresholds)
  {
    if (threshold == "default_68" || threshold == "copasi_68")
    {
      // the scipy.stats chi2.isf is the inverse of the chi2 distribution function
      // in kthohr/stats, this is qchisq
      int df = 1;
      double c0 = stats::qchisq(1 - 0.32, df);
      double threshold_val = obj_val * (1 + c0 / (n - m));
      computed.push_back({threshold_val, QPen(Qt::blue, 2, Qt::DashLine), "Threshold COPASI 68"});
    }
    else if (threshold == "default_95" || threshold == "copasi_95")
    {
      int df = 1;
      double c0 = stats::qchisq(1 - alpha, df);
      double threshold_val = obj_val * (1 + c0 / (n - m));
      computed.push_back({threshold_val, QPen(Qt::blue, 2, Qt::DotLine), "Threshold COPASI 95"});
    }
    else if (threshold == "schaber_chi2_1p")
    {
      int df = 1;
      double c1 = stats::qchisq(1 - alpha, df);
      double threshold_val = obj_val * std::exp(c1 / n);
      computed.push_back({threshold_val, QPen(Qt::green, 2, Qt::DashLine), "Threshold Schaber Chi2 1p"});
    }
    else if (threshold == "schaber_chi2_p")
    {
      int df = m;
      double c2 = stats::qchisq(1 - alpha, df);
      double threshold_val = obj_val * std::exp(c2 / n);
      computed.push_back({threshold_val, QPen(Qt::green, 2, Qt::DotLine), "Threshold Schaber Chi2 p"});
    }
    else if (threshold == "schaber_fratio_p")
    {
      int df = m;
      double c3 = stats::qf(1 - alpha, df, n - m);
      double threshold_val = obj_val * (1 + (m / (n - m)) * c3);
      computed.push_back({threshold_val, QPen(Qt::red, 2, Qt::DotLine), "Threshold Schaber Fratio p"});
    }
    else if (threshold == "donaldson_fratio_1p")
    {
      int df = 1;
      double c4 = stats::qf(1 - alpha, df, n - m);
      double threshold_val = obj_val * (1 + c4 / (n - m));
      computed.push_back({threshold_val, QPen(QColor(255, 127, 14), 2, Qt::DotLine), "Threshold Donaldson Fratio 1p"});
    }
    else if (threshold.endsWith("%"))
    {
      double percentage = threshold.left(threshold.lastIndexOf("%")).toDouble();
      double threshold_val = obj_val * (percentage / 100);
      computed.push_back({threshold_val, QPen(QColor(255, 127, 14), 2, Qt::DotLine), "Threshold: " + threshold  + "%"});
    }
    else {
      // check if value is numeric
      if (!std::isnan(threshold.toDouble()))
        computed.push_back({threshold.toDouble(), QPen(QColor(255, 127, 14), 2, Qt::DotLine), "Threshold: " + threshold});
    }
  }

  return computed;
}

std::vector< LineArgs > computeVerticals(const QStringList & verticals, double param_value, double param_sd)
{
  std::vector< LineArgs > computed;
  for (auto& vertical : verticals)
  {
    if (vertical.contains("VALUE"))
      computed.push_back({param_value, QPen(QColor(192, 192, 192), 2, Qt::DotLine), "= " + QString::number(param_value)});
    else if (vertical.endsWith("SD"))
    {
      double multiplier = vertical.left(vertical.lastIndexOf("SD")).toDouble();
      computed.push_back({param_value + multiplier * param_sd, QPen(QColor(173, 216, 230), 2, Qt::DotLine), QString("%1 SD").arg(multiplier)});
      computed.push_back({param_value - multiplier * param_sd, QPen(QColor(173, 216, 230), 2, Qt::DotLine), QString("%1 SD").arg(-multiplier)});
    }

    else if (vertical.endsWith("%"))
    {
      double percentage = vertical.left(vertical.lastIndexOf("%")).toDouble();
      computed.push_back({param_value * (percentage / 100), QPen(QColor(173, 216, 230), 2, Qt::DotLine), QString("%1 %").arg(percentage)});
    }
    else {
      // check if value is numeric
      if (!std::isnan(vertical.toDouble()))
        computed.push_back({vertical.toDouble(), QPen(QColor(173, 216, 230), 2, Qt::DotLine), QString("%1").arg(vertical)});
    }
  }
  return computed;
}

void readProfileData(QFile & file, QVector< double > & x, QVector< double > & y, QString & label, bool readLabel)
{
  QTextStream stream(&file);
  bool first = true;
  while (!stream.atEnd())
    {
      auto line = stream.readLine();
      auto parts = line.split("\t");
      if (first)
        {
          if (readLabel && parts.size() > 0)
            label = parts[0];
          first = false;
          continue;
        }
      if (parts.size() < 3)
        continue;
      x.append(parts[0].toDouble());
      y.append(parts[2].toDouble());
    }

  file.close();
};

#ifdef COPASI_USE_QCUSTOMPLOT

QCustomPlot * CQPLPlotWidget::createPlot(const PlotArgs & args, bool allowPopout)
{
  auto & x = args.x;
  auto & y = args.y;
  auto & label = args.label;
  auto & param_value = args.param_value;
  auto & param_sd = args.param_sd;
  auto & obj_val = args.obj_val;
  auto & thresholds = args.thresholds;
  auto & verticals = args.verticals;
  auto & y_min = args.y_min;
  auto & y_max = args.y_max;
  auto & scale_bottom = args.scale_bottom;
  auto scale_top = args.scale_top;

  // add the graph to the plot
  auto * pPlot = new QCustomPlot();

  auto * pGraph = pPlot->addGraph();
  pGraph->setName(label);
  pGraph->setPen(QPen(Qt::red, 2));
  pGraph->setLineStyle(QCPGraph::lsLine);
  pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
  pGraph->setAntialiasedFill(false);
  pGraph->setAntialiased(true);
  pGraph->setAntialiased(true);

  pGraph->setData(x, y);

  // set the axis labels
  pPlot->xAxis->setLabel(label);
  pPlot->yAxis->setLabel("Value");

  // set the axis ranges
  pPlot->xAxis->setRange(x.first(), x.last());
  pPlot->yAxis->setRange(y.first(), y.last());

  // set the plot title
  pPlot->plotLayout()->insertRow(0);
  QString sd = (!std::isnan(param_sd) && param_sd != 0) ? QString(" with sd %1").arg(param_sd) : QString("");
  QString title = QString("Profile for %1 (around %2%3)").arg(label).arg(param_value).arg(sd);
  pPlot->plotLayout()->addElement(0, 0, new QCPTextElement(pPlot, title));
  
  if (allowPopout)
    {
  auto * popOutElement = new QCPTextElement(pPlot, QString("⛶"));

  // Connect the click signal to hide the plot
  connect(popOutElement, &QCPTextElement::clicked, [this, args, title]() {
    // when pop out is clicked
    auto * pCopy = createPlot(args, false);
    // create a qdialog to show the copy
    QDialog * dialog = new QDialog();
#ifndef Darwin
    dialog->setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin
    dialog->setWindowTitle(title);
    dialog->setModal(false);
    dialog->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
    dialog->setMinimumSize(640, 480);

    QGridLayout * layout = new QGridLayout(dialog);
    layout->addWidget(pCopy, 0, 0);

    dialog->exec();
  });

  pPlot->plotLayout()->addElement(0, 1, popOutElement);

  auto * pHideElement = new QCPTextElement(pPlot, QString("❌"));

  // Connect the click signal to hide the plot
  connect(pHideElement, &QCPTextElement::clicked, [pPlot, pHideElement]() {
    pPlot->setVisible(false);
  });

  pPlot->plotLayout()->addElement(0, 2, pHideElement);
    }

  // add a silver dotted line with the obj value
  auto * pLine = pPlot->addGraph();
  pLine->setName("Obj = " + QString::number(obj_val));
  pLine->setPen(QPen(QColor(192, 192, 192), 2, Qt::DotLine));
  pLine->setLineStyle(QCPGraph::lsLine);
  pLine->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
  pLine->setAntialiasedFill(false);
  pLine->setAntialiased(true);
  pLine->setData(QVector< double >{x.first(), x.last()}, QVector< double >{obj_val, obj_val});

  // add the thresholds to the plot as lines
  for (auto & threshold : thresholds)
    {
      auto * pThreshold = pPlot->addGraph();
      pThreshold->setName(threshold.label);
      pThreshold->setPen(threshold.pen);
      pThreshold->setLineStyle(QCPGraph::lsLine);
      pThreshold->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
      pThreshold->setAntialiased(true);
      pThreshold->setData(QVector< double >{x.first(), x.last()}, QVector< double >{threshold.value, threshold.value});
    }

  // add vertical lines
  for (auto & vertical : verticals)
    {
      auto * pVertical = pPlot->addGraph();
      pVertical->setPen(vertical.pen);
      pVertical->setName(vertical.label);
      pVertical->setLineStyle(QCPGraph::lsLine);
      pVertical->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
      pVertical->setAntialiased(true);
      pVertical->setData(QVector< double >{vertical.value, vertical.value}, QVector< double >{y_min, y_max});
    }

  // add parabola: obj_val + (x-param_value)^2  / param_sd
  // if param_sd is not 0 or nan
  if (!std::isnan(param_sd) && param_sd != 0)
    {
      auto * pParabola = pPlot->addGraph();
      pParabola->setPen(QPen(Qt::green, 2, Qt::DotLine));
      pParabola->setLineStyle(QCPGraph::lsLine);
      pParabola->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));
      pParabola->setAntialiased(true);
      pParabola->setVisible(false);
      // lambda to compute the parabola
      auto y_parabola = [obj_val, param_sd, param_value](double x) {
        return obj_val + (x - param_value) * (x - param_value) / param_sd;
      };
      QVector< double > y_parabola_values;
      for (auto & x_value : x)
        y_parabola_values.append(y_parabola(x_value));
      pParabola->setData(x, y_parabola_values);
      pParabola->setName("Parabola");
    }

  // scale axes automatically and replot
  pPlot->rescaleAxes(true);

  // if range is specified, use it
  if (!std::isnan(scale_bottom))
    pPlot->yAxis->setRangeLower(scale_bottom);
  if (std::isnan(scale_top))
    scale_top = y_max;

  pPlot->yAxis->setRangeUpper(scale_top);

  pPlot->plotLayout()->setColumnStretchFactor(1, 0.05);
  pPlot->plotLayout()->setColumnStretchFactor(2, 0.05);
  pPlot->plotLayout()->setRowStretchFactor(1, 4);
  pPlot->replot();

  // allow plot to be navigated with mouse
  pPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


  // add a legend
  auto * pLegend = pPlot->legend;
  pLegend->setVisible(false);
  pLegend->setFont(QFont("Arial", 10));
  pLegend->setBrush(QBrush(QColor(255, 255, 255, 128)));
  pLegend->setBorderPen(QPen(QColor(0, 0, 0), 1));
  pLegend->setIconSize(QSize(10, 10));
  pPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom | Qt::AlignRight);
  

      QObject::connect(
                        pPlot,
                        &QCustomPlot::legendClick,
    [pPlot, scale_bottom, scale_top](QCPLegend * legend, QCPAbstractLegendItem * item, QMouseEvent * event)
                        {
      auto * plItem = qobject_cast< QCPPlottableLegendItem * >(item);
      if (!plItem)
        return;

      auto * pl = plItem->plottable();
      pl->setVisible(!pl->visible());

      pPlot->replot();
        // scale axes automatically and replot
      pPlot->rescaleAxes(true);

      // if range is specified, use it
      if (!std::isnan(scale_bottom))
        pPlot->yAxis->setRangeLower(scale_bottom);
      if (!std::isnan(scale_top))
        pPlot->yAxis->setRangeUpper(scale_top);
                        });
  // show tooltips on hover
  connect(pPlot, &QCustomPlot::mouseMove, [=](QMouseEvent * event) {
    // Get the pixel coordinates of the mouse
    int x_pixel = event->pos().x();
    int y_pixel = event->pos().y();

    // Convert the pixel coordinates to plot coordinates
    double x_coord = pPlot->xAxis->pixelToCoord(x_pixel);

    // Find the closest data point on the graph
    QCPGraph * graph = pPlot->graph(0);
    if (graph)
      {
        // Use findBegin or findEnd to locate the closest data index
        int index = graph->findBegin(x_coord);
        double x_data = graph->dataMainKey(index);
        double y_data = graph->dataMainValue(index);

        // Display this data using a QToolTip
        QToolTip::showText(QCursor::pos(), QString("X: %1\nY: %2").arg(x_data).arg(y_data));
      }
    else
      {
        QToolTip::hideText();
      }
  });

  // add context menu to the plot

  auto * pContextMenu = new QMenu(pPlot);
  pContextMenu->addAction("Toggle Legend", [pPlot]() {
    pPlot->legend->setVisible(!pPlot->legend->visible());
    pPlot->replot();
  });
  pContextMenu->addAction("Toggle Grid", [pPlot]() {
    pPlot->xAxis->grid()->setVisible(!pPlot->xAxis->grid()->visible());
    pPlot->yAxis->grid()->setVisible(!pPlot->yAxis->grid()->visible());
    pPlot->replot();
  });
  pContextMenu->addSeparator();
  pContextMenu->addAction("Save Plot", [pPlot]() {
    QString fileName = QFileDialog::getSaveFileName(pPlot, "Save Plot", "", "PNG Files (*.png)");
    if (fileName.isEmpty())
      return;
    pPlot->savePng(fileName);
  });
  // open context menu with right click
  connect(pPlot, &QCustomPlot::mouseRelease, [pContextMenu](QMouseEvent * event) {
    if (event->button() == Qt::RightButton) {
      pContextMenu->popup(event->globalPos());
    }
  });
  
  return pPlot;
}

#endif // COPASI_USE_QCUSTOMPLOT

void CQPLPlotWidget::generatePlots()
{
  saveSettings(mpSettings);

  mMap = globFiles(mpTxtTarget->text(), "*.txt");

  // clear all widgets from mpScrollContents widget

  QVBoxLayout * layout = mpScrollContents->layout() != NULL ? qobject_cast< QVBoxLayout * >(mpScrollContents->layout()) : new QVBoxLayout(mpScrollContents);

  if (layout)
    {
      QLayoutItem * item;
      while ((item = layout->takeAt(0)) != nullptr)
        {
          if (item->widget())
            {
              delete item->widget(); // Deletes the widget
            }
          delete item; // Deletes the layout item
        }
    }

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
      try
      {
          auto info = nlohmann::json::parse(stream.readAll().toStdString());
          obj_val = info["obj"].get< double >();
          num_params = info["num_params"].get< int >();
          num_data = info["num_data"].get< int >();
          param_values = info["param_values"].get< std::vector< double > >();
          param_names = info["param_names"].get< std::vector< std::string > >();
          param_sds = info["param_sds"].get< std::vector< double > >();
        }
      catch (...)
      {
          param_sds.resize(param_values.size());
      }
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

    // read the low file
    QVector<double> x, y;
    QString label;

    readProfileData(fileLow, x, y, label, true);
    readProfileData(fileHigh, x, y, label, false);

    if (x.empty() || y.empty())
      continue;

    // find the index of the parameter in the param_names vector
    auto index_pos = std::find(param_names.begin(), param_names.end(), label.toStdString());
    if (index_pos == param_names.end())
      continue;

    // compute y_min and y_max
    auto y_min = *std::min_element(y.begin(), y.end());
    if (!std::isnan(scale_bottom) && scale_bottom < y_min)
      y_min = scale_bottom;

    auto y_max = *std::max_element(y.begin(), y.end());
    if (!std::isnan(scale_top) && scale_top > y_max)
      y_max = scale_top;

    int param_index = int(index_pos - param_names.begin());
    double param_value = param_values[param_index];
    double param_sd = param_sds[param_index];

    auto verticals = computeVerticals(mpTxtVertical->text().split(";"), param_value, param_sd);

    auto plotArgs = PlotArgs{x, y, label, param_value, param_sd, obj_val, thresholds, verticals, y_min, y_max, scale_bottom, scale_top};

    auto* pPlot = createPlot(plotArgs);

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
