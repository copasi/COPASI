// Copyright (C) 2025 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQPLPlotWidget_H__
#define CQPLPlotWidget_H__
#include <QWidget>
#include <QString>
#include <QMap>
#include <tuple>

#include <copasi/config.h>
#include "copasi/UI/ui_CQPLPlotWidget.h"
#include <copasi/UI/CQProfileWidget.h>

class QAction;
class QPushButton;
class CProfileSettings;
class QCustomPlot;

typedef QMap<QString, std::pair<QString, QString>> QResultMap;

struct LineArgs
{
  double value;
  QPen pen;
  QString label;
};

struct PlotArgs
{
  QVector< double > x;
  QVector< double > y;
  QString label;
  double param_value;
  double param_sd;
  double parabola_coeff;
  double obj_val;
  std::vector< LineArgs > thresholds;
  std::vector< LineArgs > verticals;
  double y_min;
  double y_max;
  double scale_bottom;
  double scale_top;
};

class CQPLPlotWidget : public QWidget
  , public Ui::CQPLPlotWidget, public CQProfileWidget
{

  Q_OBJECT

  QStringList mFiles;
  QResultMap mMap;
  CProfileSettings * mpSettings;

  private:
#ifdef COPASI_USE_QCUSTOMPLOT
  QCustomPlot * createPlot(const PlotArgs & args, bool allowPopout=true);
#endif //COPASI_USE_QCUSTOMPLOT

public:
  CQPLPlotWidget(QWidget * parent = 0);

  virtual void loadSettings(const CProfileSettings * pSettings);
  virtual void saveSettings(CProfileSettings * pSettings);

  QResultMap globFiles(const QString& directory, const QString& pattern);

public slots:
  /**
   * browses for a directory with reports to generate plots for
   */
  virtual void browseDirectory();

  /**
   * displays a selection dialog, to add a threshold to display in plots
   */
  virtual void addThreshold();

  /**
   * generates plots for all reports in the selected directory
   */
  virtual void generatePlots();

  /**
   * saves plots as PDF files
   */
  virtual void savePlots();
};

#endif // CQPLPlotWidget_H__
