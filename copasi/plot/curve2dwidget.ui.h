/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/curve2dwidget.ui.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/16 14:03:19 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you wish to add, delete or rename functions or slots use
 ** Qt Designer which will update this file, preserving your code. Create an
 ** init() function in place of a constructor, and a destroy() function in
 ** place of a destructor.
 *****************************************************************************/

#include "report/CCopasiContainer.h"

bool Curve2DWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve) return false;

  if (curve->getType() != CPlotItem::curve2d) return false;
  //if (curve->getChannels().getSize != 2) return false;

  lineEditTitle->setText(curve->getTitle().c_str());

  //set the comboboxes for axis selection
  /*if (curve->xAxis == QwtPlot::xTop) comboXAxis->setCurrentItem(0);
  else comboXAxis->setCurrentItem(1);

  if (curve->yAxis == QwtPlot::yRight) comboYAxis->setCurrentItem(1);
  else comboYAxis->setCurrentItem(0);*/

  //std::vector< CCopasiContainer * > LOfC; //dummy

  //set the comboboxes for data channel selection
  //TODO: check if objects exist....

  CCopasiObject* co1 = CCopasiContainer::ObjectFromName(curve->getChannels()[0]);
  CCopasiObject* co2 = CCopasiContainer::ObjectFromName(curve->getChannels()[1]);

  if ((!co1) || (!co2)) return false;

  lineEditXName->setText(co1->getObjectDisplayName().c_str());
  lineEditXCN->setText(co1->getCN().c_str());

  lineEditYName->setText(co2->getObjectDisplayName().c_str());
  lineEditYCN->setText(co2->getCN().c_str());

  //for debugging:
  //  std::cout << "Curve2DWidget::LoadFromCurveSpec:" << std::endl;
  //  std::cout << "  title: " << curve->title << std::endl;
  //  std::cout << "  " << curve->mChannels.size() << "  " << curve->mChannels[0].object << "  " << curve->mChannels[1].object << std::endl;

  //  std::string sss = CCopasiContainer::ObjectFromName(ListOfContainer, curve->mChannels[0].object)->getObjectUniqueName().c_str();
  //  std::cout << "uni : " << sss << " *** " << std::endl;

  return true; //TODO
}

bool Curve2DWidget::SaveToCurveSpec(CPlotItem * curve) const
  {
    //title
    curve->setTitle((const char*)lineEditTitle->text().utf8());

    //channels
    curve->getChannels().resize(0);
    curve->getChannels().push_back(CPlotDataChannelSpec(std::string((const char*)lineEditXCN->text().utf8())));
    curve->getChannels().push_back(CPlotDataChannelSpec(std::string((const char*)lineEditYCN->text().utf8())));
    /* if (!curve) return false;

     curve->title = lineEditTitle->text().latin1();

     //read the comboboxes for axis selection
     if (comboXAxis->currentItem() == 0) curve->xAxis = QwtPlot::xTop;
     else curve->xAxis = QwtPlot::xBottom;

     if (comboYAxis->currentItem() == 1) curve->yAxis = QwtPlot::yRight;
     else curve->yAxis = QwtPlot::yLeft;

     //read the comboboxes for data channel selection
     curve->mChannels[0].index = comboXData->currentItem();
     curve->mChannels[1].index = comboYData->currentItem();
    */
    return true;
  }
