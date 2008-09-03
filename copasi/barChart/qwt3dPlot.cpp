// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/qwt3dPlot.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/09/03 13:11:52 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "qwt3dPlot.h"

Plot3d::Plot3d(QWidget* parent, const char* name)
    : BaseWidget(parent, name)
{

  mpGrid = new QGridLayout(mpFrame, 0, 0);
  mpPlot = new Qwt3D::SurfacePlot(mpFrame);
  mpGrid->addWidget(mpPlot, 0, 0);
  mpPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mpPlot->setRotation(30, 0, 15);
  //setScale(1,1,1);
  mpPlot->setShift(0.15, 0, 0);

  mTitle = QString("");
  mColorLegend = true;

  mData.maxValue = 0;
  mData.minValue = 0;

  mpPlot->coordinates()->setAutoScale(false);
  mpPlot->updateData();
  mpPlot->updateGL();
}

Plot3d::~Plot3d()
{}

void Plot3d::setZoom()
{
  double zoom;
  if (mData.maxItems < 7)
    zoom = (double)(mData.maxItems) / 10;
  else
    zoom = 0.7;
  mpPlot->setZoom(zoom);
}

void Plot3d::plotData()
{

  resizeCoordSys();

  mpBar = (Bar*)mpPlot->setPlotStyle(Bar(mData.faktor * 0.4, -1, -1));

  setPlotTitle();

  if (mColorLegend == true) setLegend();

  setZoom();
  setAxes();
  mpPlot->setCoordinateStyle(Qwt3D::FRAME);
  mpPlot->updateData();
  mpPlot->updateGL();
}

void Plot3d::setAxes()
{
  double majorTicLength, minorTicLength;

  if (mData.maxItems <= 2)
    {
      majorTicLength = mData.valueZone * 3;
      minorTicLength = mData.valueZone * 2.5;
    }
  else
    if (mData.maxItems < 5)
      {
        majorTicLength = mData.valueZone;
        minorTicLength = mData.valueZone / 1.2;
      }
    else
      {
        majorTicLength = mData.valueZone / 3;
        minorTicLength = mData.valueZone / 4;
      }

  mpPlot->coordinates()->setLineSmooth(true);
  mpPlot->coordinates()->setGridLinesColor(Qwt3D::RGBA(0, 0, 0.5));
  mpPlot->coordinates()->setNumberFont("Courier", 8);
  mpPlot->coordinates()->setLabelFont("Courier", 8);
  mpPlot->coordinates()->adjustLabels(35);
  //  mpPlot->coordinates()->adjustNumbers(majorTicLength);
  mpPlot->coordinates()->setLabelColor(Qwt3D::RGBA(1, 0, 0));

  //mpPlot->coordinates()->setAutoDecoration(false);

  mpPlot->coordinates()->axes[Qwt3D::Z1].setScale(new ValueScale);
  if ((mData.maxValue > 0) && (mData.minValue < 0))
    mpPlot->coordinates()->axes[Qwt3D::Z1].setMajors(2);
  else
    mpPlot->coordinates()->axes[Qwt3D::Z1].setMajors(1);
  mpPlot->coordinates()->axes[Qwt3D::Z1].setMinors(0);
  mpPlot->coordinates()->axes[Qwt3D::Z1].setLineWidth(2, 0.7, 0.2);
  mpPlot->coordinates()->axes[Qwt3D::Z1].setTicOrientation(-1, 1, 0);
  mpPlot->coordinates()->axes[Qwt3D::Z1].setTicLength(majorTicLength, minorTicLength);
  mpPlot->coordinates()->axes[Qwt3D::Z2].setScale(new ValueScale);
  if ((mData.maxValue > 0) && (mData.minValue < 0))
    mpPlot->coordinates()->axes[Qwt3D::Z2].setMajors(2);
  else
    mpPlot->coordinates()->axes[Qwt3D::Z2].setMajors(1);
  mpPlot->coordinates()->axes[Qwt3D::Z2].setMinors(0);
  mpPlot->coordinates()->axes[Qwt3D::Z2].setLineWidth(2, 0.7, 0.2);
  mpPlot->coordinates()->axes[Qwt3D::Z2].setTicOrientation(-1, -1, 0);
  mpPlot->coordinates()->axes[Qwt3D::Z2].setTicLength(majorTicLength, minorTicLength);
  mpPlot->coordinates()->axes[Qwt3D::Z3].setScale(new ValueScale);
  if ((mData.maxValue > 0) && (mData.minValue < 0))
    mpPlot->coordinates()->axes[Qwt3D::Z3].setMajors(2);
  else
    mpPlot->coordinates()->axes[Qwt3D::Z3].setMajors(1);
  mpPlot->coordinates()->axes[Qwt3D::Z3].setMinors(0);
  mpPlot->coordinates()->axes[Qwt3D::Z3].setLineWidth(2, 0.7, 0.2);
  mpPlot->coordinates()->axes[Qwt3D::Z3].setTicOrientation(1, -1, 0);
  mpPlot->coordinates()->axes[Qwt3D::Z3].setTicLength(majorTicLength, minorTicLength);
  mpPlot->coordinates()->axes[Qwt3D::Z4].setScale(new ValueScale);
  if ((mData.maxValue > 0) && (mData.minValue < 0))
    mpPlot->coordinates()->axes[Qwt3D::Z4].setMajors(2);
  else
    mpPlot->coordinates()->axes[Qwt3D::Z4].setMajors(1); mpPlot->coordinates()->axes[Qwt3D::Z4].setMinors(0);
  mpPlot->coordinates()->axes[Qwt3D::Z4].setLineWidth(2, 0.7, 0.2);
  mpPlot->coordinates()->axes[Qwt3D::Z4].setTicOrientation(1, 1, 0);
  mpPlot->coordinates()->axes[Qwt3D::Z4].setTicLength(majorTicLength, minorTicLength);

  mpPlot->coordinates()->axes[Qwt3D::X1].setScale(new ColumnScale(mpColumnScale, getColSliderPos()));
  mpPlot->coordinates()->axes[Qwt3D::X1].setLabelString("columns");
  mpPlot->coordinates()->axes[Qwt3D::X1].setMajors(mData.columns - 1);
  mpPlot->coordinates()->axes[Qwt3D::X1].setMinors(0);
  //mpPlot->coordinates()->axes[Qwt3D::X1].setLineWidth(2, 0.7, 0);
  if (mpColumnScale)
    mpPlot->coordinates()->axes[Qwt3D::X1].setTicLength(majorTicLength, 0);
  else
    mpPlot->coordinates()->axes[Qwt3D::X1].setTicLength(0, 0);
  mpPlot->coordinates()->axes[Qwt3D::X2].setScale(new ColumnScale(mpColumnScale, getColSliderPos()));
  mpPlot->coordinates()->axes[Qwt3D::X2].setLabelString("columns");
  mpPlot->coordinates()->axes[Qwt3D::X2].setMajors(mData.columns - 1);
  mpPlot->coordinates()->axes[Qwt3D::X2].setMinors(0);
  //mpPlot->coordinates()->axes[Qwt3D::X2].setLineWidth(2, 0.7, 0);
  if (mpColumnScale)
    mpPlot->coordinates()->axes[Qwt3D::X2].setTicLength(majorTicLength, 0);
  else
    mpPlot->coordinates()->axes[Qwt3D::X2].setTicLength(0, 0);
  mpPlot->coordinates()->axes[Qwt3D::X3].setScale(new ColumnScale(mpColumnScale, getColSliderPos()));
  mpPlot->coordinates()->axes[Qwt3D::X3].setLabelString("columns");
  mpPlot->coordinates()->axes[Qwt3D::X3].setMajors(mData.columns - 1);
  mpPlot->coordinates()->axes[Qwt3D::X3].setMinors(0);
  //mpPlot->coordinates()->axes[Qwt3D::X3].setLineWidth(2, 0.7, 0);
  if (mpColumnScale)
    mpPlot->coordinates()->axes[Qwt3D::X3].setTicLength(majorTicLength, 0);
  else
    mpPlot->coordinates()->axes[Qwt3D::X3].setTicLength(0, 0);
  mpPlot->coordinates()->axes[Qwt3D::X4].setScale(new ColumnScale(mpColumnScale, getColSliderPos()));
  mpPlot->coordinates()->axes[Qwt3D::X4].setLabelString("columns");
  mpPlot->coordinates()->axes[Qwt3D::X4].setMajors(mData.columns - 1);
  //mpPlot->coordinates()->axes[Qwt3D::X4].setLineWidth(2, 0.7, 0);
  if (mpColumnScale)
    mpPlot->coordinates()->axes[Qwt3D::X4].setTicLength(majorTicLength, 0);
  else
    mpPlot->coordinates()->axes[Qwt3D::X4].setTicLength(0, 0);

  mpPlot->coordinates()->axes[Qwt3D::Y1].setLabelString("rows");
  mpPlot->coordinates()->axes[Qwt3D::Y1].setScale(new RowScale(mpRowScale, getRowSliderPos()));
  mpPlot->coordinates()->axes[Qwt3D::Y1].setMajors(mData.rows - 1);
  mpPlot->coordinates()->axes[Qwt3D::Y1].setMinors(0);
  //mpPlot->coordinates()->axes[Qwt3D::Y1].setLineWidth(2, 0.7, 0);
  mpPlot->coordinates()->axes[Qwt3D::Y1].setTicLength(majorTicLength, 0);
  mpPlot->coordinates()->axes[Qwt3D::Y2].setLabelString("rows");
  mpPlot->coordinates()->axes[Qwt3D::Y2].setScale(new RowScale(mpRowScale, getRowSliderPos()));
  mpPlot->coordinates()->axes[Qwt3D::Y2].setMajors(mData.rows - 1);
  mpPlot->coordinates()->axes[Qwt3D::Y2].setMinors(0);
  //mpPlot->coordinates()->axes[Qwt3D::Y2].setLineWidth(2, 0.7, 0);
  mpPlot->coordinates()->axes[Qwt3D::Y2].setTicLength(majorTicLength, 0);
  mpPlot->coordinates()->axes[Qwt3D::Y3].setLabelString("rows");
  mpPlot->coordinates()->axes[Qwt3D::Y3].setScale(new RowScale(mpRowScale, getRowSliderPos()));
  mpPlot->coordinates()->axes[Qwt3D::Y3].setMajors(mData.rows - 1);
  mpPlot->coordinates()->axes[Qwt3D::Y3].setMinors(0);
  //mpPlot->coordinates()->axes[Qwt3D::Y3].setLineWidth(2, 0.7, 0);
  mpPlot->coordinates()->axes[Qwt3D::Y3].setTicLength(majorTicLength, 0);
  mpPlot->coordinates()->axes[Qwt3D::Y4].setLabelString("rows");
  mpPlot->coordinates()->axes[Qwt3D::Y4].setScale(new RowScale(mpRowScale, getRowSliderPos()));
  mpPlot->coordinates()->axes[Qwt3D::Y4].setMajors(mData.rows - 1);
  mpPlot->coordinates()->axes[Qwt3D::Y4].setMinors(0);
  //mpPlot->coordinates()->axes[Qwt3D::Y4].setLineWidth(2, 0.7, 0);
  mpPlot->coordinates()->axes[Qwt3D::Y4].setTicLength(majorTicLength, 0);
}

void Plot3d::setLegend()
{
  mpPlot->legend()->setLimits(mpPlot->hull().minVertex.z, mpPlot->hull().maxVertex.z);
  if ((mpPlot->hull().minVertex.z < 0) && (mpPlot->hull().maxVertex.z < 0))
    mpPlot->legend()->setLimits(mpPlot->hull().minVertex.z, 0);
  if ((mpPlot->hull().minVertex.z > 0) && (mpPlot->hull().maxVertex.z > 0))
    mpPlot->legend()->setLimits(0, mpPlot->hull().maxVertex.z);

  mpPlot->legend()->setMajors(4);
  mpPlot->legend()->setMinors(0);

  mpPlot->showColorLegend(true);
}

void Plot3d::setPlotTitle()
{
  mpPlot->setTitlePosition(0.97, 0.5, Qwt3D::TopCenter); //!< Set caption position
  mpPlot->setTitleFont("Courier", 8); //!< Set caption font
  mpPlot->setTitleColor(Qwt3D::RGBA(0, 0, 0)); //!< Set caption color
  mpPlot->setTitle(mTitle); //!< Set caption text (one row only)
}

void Plot3d::setScale(const std::vector<std::string> *columnsDescript, const std::vector<std::string> *rowsDescript)
{
  mpColumnScale = columnsDescript;
  mpRowScale = rowsDescript;
}

void Plot3d::setColors(std::vector<QColor> mColors, double min, double max)
{
  unsigned int i;
  mData.maxValue = max;
  mData.minValue = min;
  Qwt3D::ColorVector cv;

  Qwt3D::RGBA rgb;

  for (i = 0; i < mColors.size(); i++)
    {
      double r, g, b;
      r = (mColors[i].red()); g = (mColors[i].green()); b = (mColors[i].blue());
      rgb.r = r / 254; rgb.g = g / 254; rgb.b = b / 254;
      //rgb.a = 1;
      cv.push_back(rgb);
    }

  BarColor* mpCol = new BarColor(mpPlot, 100, min, max);
  mpCol->setColorVector(cv);
  mpPlot->setDataColor(mpCol);
}

void Plot3d::setData(double** data, int columns, int rows, double valueZone)
{
  int j;
  mData.valueZone = valueZone;
  mData.columns = columns;
  mData.rows = rows;

  if (columns < rows)
    mData.maxItems = rows;
  else
    mData.maxItems = columns;

  if (mData.columns == 1)
    {
      double** dataExpand = new double * [2];
      dataExpand[0] = new double[mData.rows];
      dataExpand[1] = new double[mData.rows];

      for (j = 0; j < rows; j++)
        {
          dataExpand[0][j] = data[0][j];
          dataExpand[1][j] = data[0][j];
        }

      mData.faktor = 4 * (mData.valueZone) / (mData.rows - 1);
      mData.columnAxeLength = ((mData.columns - 1) * mData.faktor) + 0.000001;
      mData.rowAxeLength = ((mData.rows - 1) * mData.faktor);
      mpPlot->loadFromData(dataExpand, mData.columns + 1, mData.rows, 0, mData.columnAxeLength, 0, mData.rowAxeLength);
    }
  else
    {
      mData.faktor = 4 * (mData.valueZone) / (mData.maxItems - 1);
      mData.columnAxeLength = ((mData.columns - 1) * mData.faktor);
      mData.rowAxeLength = ((mData.rows - 1) * mData.faktor);
      mpPlot->loadFromData(data, mData.columns, mData.rows, 0, mData.columnAxeLength, 0, mData.rowAxeLength);
    }
  plotData();
  setSlider();
}

void Plot3d::setSlider()
{
  if (mpSlider)
    if (mData.valueZone != 0)
      {
        mpSliderColumn->setMinValue(0);
        if (mData.columns == 1)
          mpSliderColumn->setMaxValue(mData.columns - 1);
        else
          mpSliderColumn->setMaxValue(mData.columns);

        mpSliderRow->setMinValue(0);
        if (mData.rows == 1)
          mpSliderRow->setMaxValue(mData.rows - 1);
        else
          mpSliderRow->setMaxValue(mData.rows);

        sliderMoved(mpSliderColumn->value(), mpSliderRow->value());
      }
}

void Plot3d::resizeCoordSys()
{
  double minZ = mpPlot->hull().minVertex.z;
  double maxZ = mpPlot->hull().maxVertex.z;

  if ((mpPlot->hull().minVertex.z < 0) && (mpPlot->hull().maxVertex.z > 0))
    {
      if (mpPlot->hull().maxVertex.z > fabs(mpPlot->hull().minVertex.z))
        {
          minZ = -mpPlot->hull().maxVertex.z;
          maxZ = mpPlot->hull().maxVertex.z;
        }
      if (mpPlot->hull().maxVertex.z < fabs(mpPlot->hull().minVertex.z))
        {
          minZ = mpPlot->hull().minVertex.z;
          maxZ = -mpPlot->hull().minVertex.z;
        }
    }
  if ((mpPlot->hull().minVertex.z < 0) && (mpPlot->hull().maxVertex.z < 0))
    {
      minZ = mpPlot->hull().minVertex.z;
      maxZ = 0;
    }
  if ((mpPlot->hull().minVertex.z > 0) && (mpPlot->hull().maxVertex.z > 0))
    {
      minZ = 0;
      maxZ = mpPlot->hull().maxVertex.z;
    }
  mpPlot->coordinates()->init(Qwt3D::Triple(mpPlot->hull().minVertex.x, mpPlot->hull().minVertex.y, minZ),
                              Qwt3D::Triple(mpPlot->hull().maxVertex.x, mpPlot->hull().maxVertex.y, maxZ));
}

int Plot3d::getColSliderPos()
{
  if (!mpSlider) return - 1;
  if (mpSliderColumn->value() > mData.columns)
    return - 1;
  else
    return mpSliderColumn->value();
}

int Plot3d::getRowSliderPos()
{
  if (!mpSlider) return - 1;
  if (mpSliderRow->value() > mData.rows)
    return - 1;
  else
    return mpSliderRow->value();
}

void Plot3d::sliderMoved(int column, int row)
{
  if (!mpSlider) return;
  int showColumn;
  int showRow;

  if (column == mData.columns)
    showColumn = -1;
  else
    showColumn = column;

  if (row == mData.rows)
    showRow = -1;
  else
    showRow = row;

  mpPlot->coordinates()->axes[Qwt3D::X1].setScale(new ColumnScale(mpColumnScale, showColumn));
  mpPlot->coordinates()->axes[Qwt3D::X2].setScale(new ColumnScale(mpColumnScale, showColumn));
  mpPlot->coordinates()->axes[Qwt3D::X3].setScale(new ColumnScale(mpColumnScale, showColumn));
  mpPlot->coordinates()->axes[Qwt3D::X4].setScale(new ColumnScale(mpColumnScale, showColumn));

  mpPlot->coordinates()->axes[Qwt3D::Y1].setScale(new RowScale(mpRowScale, showRow));
  mpPlot->coordinates()->axes[Qwt3D::Y2].setScale(new RowScale(mpRowScale, showRow));
  mpPlot->coordinates()->axes[Qwt3D::Y3].setScale(new RowScale(mpRowScale, showRow));
  mpPlot->coordinates()->axes[Qwt3D::Y4].setScale(new RowScale(mpRowScale, showRow));

  mpBar = (Bar*)mpPlot->setPlotStyle(Bar(mData.faktor * 0.4, (mData.columnAxeLength / (mData.columns - 1)) * showColumn, (mData.rowAxeLength / (mData.rows - 1)) * showRow));

  mpPlot->updateData();
  mpPlot->updateGL();

  //  sliderPosition(column, row);
}

void Plot3d::emptyPlot()
{

  data = new double * [1];
  data[0] = new double[1];
  data[0][0] = 0;

  setScale(NULL, NULL);
  setData(data, 1, 1, 0);
  mTitle = (QString(""));
  mpPlot->showColorLegend(false);
  plotData();
}

void Plot3d::contextMenuEvent(QContextMenuEvent *)
{
  QPopupMenu* mpContextMenu = new QPopupMenu(this);
  Q_CHECK_PTR(mpContextMenu);
  mpContextMenu->insertItem("handling information", this, SLOT(hotKeysMessage()));
  if (mColorLegend)
    mpContextMenu->insertItem("hide legend", this, SLOT(showLegend()));
  else
    mpContextMenu->insertItem("show legend", this, SLOT(showLegend()));

  QPopupMenu* mpSubmenu = new QPopupMenu(this);
  Q_CHECK_PTR(mpSubmenu);
  //mpSubmenu->insertItem("&Print to printer", this, SLOT(saveDataToFile()));
  mpSubmenu->insertItem("Print to &file", this, SLOT(saveDataToFile()));
  mpContextMenu->insertItem("&Print", mpSubmenu);

  mpContextMenu->exec(QCursor::pos());
  delete mpContextMenu;
}

void Plot3d::saveDataToFile()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName, filetype_, newFilter;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileNameAndFilter(newFilter,
            this, "Save File Dialog",
            "ILDMResults-barsPrint", "BMP Files (*.bmp);;PS Files (*.ps);;PDF Files (*.pdf);;", "Save to");

      if (!fileName) return;

      fileName = fileName.remove(QRegExp("\\.$"));

      if (!fileName.endsWith(".bmp") && !fileName.endsWith(".") && !fileName.endsWith(".ps") && !fileName.endsWith(".png") && !fileName.endsWith(".pdf"))
        if (newFilter == "BMP Files (*.bmp)")
          {
            fileName += ".bmp";
            filetype_ = "BMP";
          }
        else
          if (newFilter == "PS Files (*.ps)")
            {
              fileName += ".ps";
              filetype_ = "PS";
            }
          else
            if (newFilter == "PDF Files (*.pdf)")
              {
                fileName += ".pdf";
                filetype_ = "PDF";
              }

      fileName = fileName.remove(QRegExp("\\.$"));
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  int failed = 0;
  QCursor oldCursor = cursor();
  setCursor(Qt::WaitCursor);
  failed = !Qwt3D::IO::save(mpPlot, fileName.lower(), filetype_);
  setCursor(oldCursor);

  if (failed)
    {
      std::string s = "Could not save data to ";
      s += fileName.utf8();
      QMessageBox::critical(this, "Save Error", FROM_UTF8(s), QMessageBox::Ok, QMessageBox::Cancel);
    }
}

void Plot3d::showLegend()
{

  if (mColorLegend)
    {
      mColorLegend = false;
      mpPlot->showColorLegend(false);
    }
  else
    {
      mColorLegend = true;
      mpPlot->showColorLegend(true);
    }
}

void Plot3d::hotKeysMessage()
{

  QMessageBox::information(this, "Mouse and Keyboard Handling",
                           "You can perform shifts, turns, scales and zooms. \n \n"
                           "Try Ctrl, Shift, Alt in combination with your wheel and left mouse \n"
                           "button to get a clue (or use instead your cursor keys).\n"
);

  return;
}
