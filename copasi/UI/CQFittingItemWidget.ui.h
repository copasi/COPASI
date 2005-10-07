/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingItemWidget.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 16:43:28 $
   End CVS Header */

void CQFittingItemWidget::init()
{}

void CQFittingItemWidget::setItemUpperLimit(std::string strUpperLimit)
{}

void CQFittingItemWidget::setItemLowerLimit(std::string strLowerLimit)
{}

std::string CQFittingItemWidget::getItemUpperLimit() const
  {
    return "";
  }

std::string CQFittingItemWidget::getItemLowerLimit() const
  {
    return "";
  }

CCopasiObject * CQFittingItemWidget::getCopasiObject()
{
  return mpObject;
}

void CQFittingItemWidget::setCopasiObjectPtr(CCopasiObject * sourceObject)
{}

void CQFittingItemWidget::slotNegativeInfinity()
{}

void CQFittingItemWidget::slotPositiveInfinity()
{}

void CQFittingItemWidget::slotLowerEdit()
{}

void CQFittingItemWidget::slotUpperEdit()
{}

void CQFittingItemWidget::slotParamEdit()
{}

bool CQFittingItemWidget::initFromFitItem(const CFitItem & item)
{
  return true;
}

bool CQFittingItemWidget::saveToFitItem(CFitProblem * pg) const
  {
    return true;
  }
