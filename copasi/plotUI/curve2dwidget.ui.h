/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/curve2dwidget.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/01/14 17:01:39 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you wish to add, delete or rename functions or slots use
 ** Qt Designer which will update this file, preserving your code. Create an
 ** init() function in place of a constructor, and a destroy() function in
 ** place of a destructor.
 *****************************************************************************/

bool Curve2DWidget::LoadFromCurveSpec(const Curve2DSpec * curve, const QStringList & channels)
{
  if (!curve) return false;

  lineEditTitle->setText(curve->title.c_str());

  //set the comboboxes for axis selection
  if (curve->xAxis == QwtPlot::xTop) comboXAxis->setCurrentItem(0);
  else comboXAxis->setCurrentItem(1);

  if (curve->yAxis == QwtPlot::yRight) comboYAxis->setCurrentItem(1);
  else comboYAxis->setCurrentItem(0);

  //set the comboboxes for data channel selection
  comboXData->insertStringList(channels);
  comboXData->setCurrentItem(curve->xChannel.index);

  comboYData->insertStringList(channels);
  comboYData->setCurrentItem(curve->yChannel.index);

  return true;
}

bool Curve2DWidget::SaveToCurveSpec(Curve2DSpec * curve) const
  {
    if (!curve) return false;

    curve->title = lineEditTitle->text().latin1();

    //read the comboboxes for axis selection
    if (comboXAxis->currentItem() == 0) curve->xAxis = QwtPlot::xTop;
    else curve->xAxis = QwtPlot::xBottom;

    if (comboYAxis->currentItem() == 1) curve->yAxis = QwtPlot::yRight;
    else curve->yAxis = QwtPlot::yLeft;

    //read the comboboxes for data channel selection
    curve->xChannel.index = comboXData->currentItem();
    curve->yChannel.index = comboYData->currentItem();

    return true;
  }
