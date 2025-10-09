#include "CQProfileWizard.h"

#include "copasi/resourcesUI/CQIconResource.h"

void CQProfileWizard::loadPage(int index)
{
  auto * previousPage = tabWidget->widget(index);
  if (!previousPage)
    return;

  auto * pProfileWidget =
    index == 0   ? dynamic_cast< CQProfileWidget * >(wdgGenerate)
    : index == 1 ? dynamic_cast< CQProfileWidget * >(wdgProcess)
                 : dynamic_cast< CQProfileWidget * >(wdgPlot);

  if (!pProfileWidget)
    return;

  pProfileWidget->loadSettings(&mSettings);
}

void CQProfileWizard::savePage(int index)
{
  auto * previousPage = tabWidget->widget(index);
  if (!previousPage)
    return;

  auto * pProfileWidget =
    index == 0   ? dynamic_cast< CQProfileWidget * >(wdgGenerate)
    : index == 1 ? dynamic_cast< CQProfileWidget * >(wdgProcess)
                 : dynamic_cast< CQProfileWidget * >(wdgPlot);

  if (!pProfileWidget)
    return;

  pProfileWidget->saveSettings(&mSettings);
}

CQProfileWizard::CQProfileWizard(QWidget * parent, const CProfileSettings * pSettings)
  : QDialog(parent)
  , mSettings()
  , mCurrentPage(0)
{
#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  setupUi(this);

  if (pSettings)
    mSettings = *pSettings;

  loadPage(mCurrentPage);
}

void CQProfileWizard::onTabChanged(int index)
{
  savePage(mCurrentPage);
  mCurrentPage = index;
  loadPage(index);
}

void CQProfileWizard::open()
{
  QDialog::open();
}
