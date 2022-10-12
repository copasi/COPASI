// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQAdvancedPlotSettings.h"
#include "ui_CQAdvancedPlotSettings.h"

#include <copasi/config.h>
#include <copasi/plot/CPlotSpecification.h>
#include <copasi/UI/qtUtilities.h>

#include <QComboBox>

CQAdvancedPlotSettings::CQAdvancedPlotSettings(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CQAdvancedPlotSettings)
{
  ui->setupUi(this);

  ui->cmbEngines->addItems(QStringList()
#ifdef COPASI_USE_QWT
                           << "QWT"
#endif
#ifdef COPASI_USE_QCUSTOMPLOT
                           << "QCustomPlot"
#endif
#ifdef COPASI_USE_QTCHARTS
                           << "Qt Charts"
#endif
#ifdef WITH_QT5_VISUALIZATION
                           << "Qt DataVizualization (scatter)"
                           << "Qt DataVizualization (surface)"
#endif
                          );
}

CQAdvancedPlotSettings::~CQAdvancedPlotSettings()
{
  delete ui;
}

void
CQAdvancedPlotSettings::loadFromPlotSpec(const CPlotSpecification * pspec)
{
  ui->txtXAxis->setText(getParameterValue(pspec, "x axis").toString());
  ui->txtYAxis->setText(getParameterValue(pspec, "y axis").toString());
  ui->txtZAxis->setText(getParameterValue(pspec, "z axis").toString());

  QString engine = getParameterValue(pspec, "plot engine").toString();

  // fall back to first entry if not in supported list
  int index = ui->cmbEngines->findText(engine);

  if (index < 0)
    index = 0;

  ui->cmbEngines->setCurrentIndex(index);
}

void
CQAdvancedPlotSettings::saveToPlotSpec(CPlotSpecification * pspec)
{
  pspec->assertParameter("x axis", CCopasiParameter::Type::STRING, std::string(""));
  pspec->assertParameter("y axis", CCopasiParameter::Type::STRING, std::string(""));
  pspec->assertParameter("z axis", CCopasiParameter::Type::STRING, std::string(""));
  pspec->assertParameter("plot engine", CCopasiParameter::Type::STRING, std::string("QWT"));

  setParameterValue(pspec, "x axis", ui->txtXAxis->text());
  setParameterValue(pspec, "y axis", ui->txtYAxis->text());
  setParameterValue(pspec, "z axis", ui->txtZAxis->text());
  setParameterValue(pspec, "plot engine", ui->cmbEngines->currentText());
}
