/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/curve2dwidget.ui.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/28 17:28:29 $
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
#include "CopasiUI/CCopasiSelectionDialog.h"
#include "CopasiUI/qtUtilities.h"

// comboBoxType lines|points|symbols

bool Curve2DWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve) return false;

  if (curve->getType() != CPlotItem::curve2d) return false;
  //if (curve->getChannels().getSize != 2) return false;

  lineEditTitle->setText(FROM_UTF8(curve->getTitle()));

  //TODO: check if objects exist....

  mpObjectX = mpObjectY = NULL;
  if (curve->getChannels().size() >= 1)
    mpObjectX = CCopasiContainer::ObjectFromName(curve->getChannels()[0]);
  if (curve->getChannels().size() >= 2)
    mpObjectY = CCopasiContainer::ObjectFromName(curve->getChannels()[1]);

  if (mpObjectX)
    lineEditXName->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  if (mpObjectY)
    lineEditYName->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));

  const void* tmp;

  if (!(tmp = curve->getValue("Line type"))) return false;
  comboBoxType->setCurrentItem(*(unsigned C_INT32*)tmp);

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
    //if (!(mpObjectX && mpObjectY)) return false;

    //title
    curve->setTitle((const char*)lineEditTitle->text().utf8());

    //channels
    curve->getChannels().resize(0);
    curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectX ? mpObjectX->getCN() : std::string("")));
    curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectY ? mpObjectY->getCN() : std::string("")));

    curve->setValue("Line type", (unsigned C_INT32)comboBoxType->currentItem());

    return true;
  }

void Curve2DWidget::buttonPressedX()
{
  if (!mpModel) return;
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);
  browseDialog->setModel(mpModel);
  browseDialog->setSingleSelection(true);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  if (mpObjectX)
    selection->push_back(mpObjectX);
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      if (mpObjectX == selection->at(0)) return; //nothing to be done
      mpObjectX = selection->at(0);
      if (mpObjectX)
        lineEditXName->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
      else
        lineEditXName->setText("");

      if (mpObjectX && mpObjectY)
        lineEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                         + "|"
                                         + mpObjectX->getObjectDisplayName()));
      //TODO update tab title
    }
}

void Curve2DWidget::buttonPressedY()
{
  if (!mpModel) return;
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);
  browseDialog->setModel(mpModel);
  browseDialog->setSingleSelection(true);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  if (mpObjectY)
    selection->push_back(mpObjectY);
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      if (mpObjectY == selection->at(0)) return; //nothing to be done
      mpObjectY = selection->at(0);
      if (mpObjectY)
        lineEditYName->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));
      else
        lineEditYName->setText("");

      if (mpObjectX && mpObjectY)
        lineEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                         + "|"
                                         + mpObjectX->getObjectDisplayName()));
      //TODO update tab title
    }
}

void Curve2DWidget::setModel(const CModel * model)
{
  mpModel = model;
}
