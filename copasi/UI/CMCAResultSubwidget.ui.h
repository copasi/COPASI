/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMCAResultSubwidget.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/26 15:17:35 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

void CMCAResultSubwidget::init()
{
  mTopLabel->setText("");
}

void CMCAResultSubwidget::loadAll(const CMCAMethod * mcaMethod)
{
}

void CMCAResultSubwidget::loadElasticities(const CMCAMethod * mcaMethod)
{
}

void CMCAResultSubwidget::loadConcentrationCCs(const CMCAMethod * mcaMethod)
{
}

void CMCAResultSubwidget::loadFluxCCs(const CMCAMethod * mcaMethod)
{
}
