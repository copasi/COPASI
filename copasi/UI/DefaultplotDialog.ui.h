/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DefaultplotDialog.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/18 09:04:14 $
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

void DefaultPlotDialog::slotCreate()
{
  if (!mpProblem) return;
  if (mpProblem->createDefaultPlot(mIndex))
    this->accept();
  else
    this->reject();
}

void DefaultPlotDialog::setProblem(const CCopasiProblem * p)
{
  //set window header
  //this->resize(640, 480);
  this->setCaption("Output definition assistant");

  mpProblem = p;
  if (!mpProblem) return;
  //todo check
  mList = p->getListOfDefaultPlotDescriptions();

  listBox->clear();

  std::vector<CDefaultPlotDescription>::const_iterator it, itEnd = mList.end();
  for (it = mList.begin(); it != itEnd; ++it)
    {
      listBox->insertItem(it->name);
    }
  listBox->setSelected(0, true);
}

void DefaultPlotDialog::slotSelect()
{
  if (!mpProblem) return;
  //std::cout << listBox->currentItem() << std::endl;

  C_INT32 i = listBox->currentItem();
  mIndex = mList[i].id;
  lineEditTitle->setText(mList[i].name.c_str());
  textEdit->setText(mList[i].description.c_str());
}
