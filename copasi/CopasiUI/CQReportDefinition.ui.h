/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQReportDefinition.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/09 14:13:16 $
   End CVS Header */

void CQReportDefinition::btnAdvanceClicked()
{
  if (mAdvanced)
    {
      // :TODO: We should issue a warning that this might result in loss of customization.
      mAdvanced = false;

      mpBtnAdvanced->setText("Advanced >>");
      mpReportSectionTab->setTabEnabled(mpTableList, true);
      mpReportSectionTab->setTabEnabled(mpHeaderList, false);
      mpReportSectionTab->setTabEnabled(mpBodyList, false);
      mpReportSectionTab->setTabEnabled(mpFooterList, false);
      mpReportSectionTab->setCurrentPage(0);
      mpBtnSeparator->hide();
      mpBtnText->hide();
      mpTitleCheck->show();
    }
  else
    {
      mAdvanced = true;

      mpBtnAdvanced->setText("Advanced <<");
      mpReportSectionTab->setTabEnabled(mpTableList, false);
      mpReportSectionTab->setTabEnabled(mpHeaderList, true);
      mpReportSectionTab->setTabEnabled(mpBodyList, true);
      mpReportSectionTab->setTabEnabled(mpFooterList, true);
      mpReportSectionTab->setCurrentPage(2);
      mpBtnSeparator->show();
      mpBtnText->show();
      mpTitleCheck->hide();
    }
}

void CQReportDefinition::btnItemClicked()
{
  qWarning("CQReportDefinition::btnItemClicked(): Not implemented yet");
}

void CQReportDefinition::btnSeparatorClicked()
{
  qWarning("CQReportDefinition::btnSeparatorClicked(): Not implemented yet");
}

void CQReportDefinition::btnTextClicked()
{
  qWarning("CQReportDefinition::btnTextClicked(): Not implemented yet");
}

void CQReportDefinition::btnDeleteClicked()
{
  qWarning("CQReportDefinition::btnDeleteClicked(): Not implemented yet");
}

void CQReportDefinition::btnUpClicked()
{
  qWarning("CQReportDefinition::btnUpClicked(): Not implemented yet");
}

void CQReportDefinition::btnDownClicked()
{
  qWarning("CQReportDefinition::btnDownClicked(): Not implemented yet");
}

void CQReportDefinition::chkTabClicked()
{
  qWarning("CQReportDefinition::chkTabClicked(): Not implemented yet");
}

void CQReportDefinition::chkTitleClicked()
{
  qWarning("CQReportDefinition::chkTitleClicked(): Not implemented yet");
}

void CQReportDefinition::btnDeleteReportClicked()
{
  qWarning("CQReportDefinition::btnDeleteReportClicked(): Not implemented yet");
}

void CQReportDefinition::btnNewReportClicked()
{
  qWarning("CQReportDefinition::btnNewReportClicked(): Not implemented yet");
}

void CQReportDefinition::btnRevertClicked()
{
  qWarning("CQReportDefinition::btnRevertClicked(): Not implemented yet");
}

void CQReportDefinition::btnCommitClicked()
{
  qWarning("CQReportDefinition::btnCommitClicked(): Not implemented yet");
}

void CQReportDefinition::init()
{
  // We start with the table since this is simpler.
  mAdvanced = true;

  btnAdvanceClicked();
}

bool CQReportDefinition::update(ListViews::ObjectType objectType,
                                ListViews::Action action,
                                const std::string & key)
{
  return false;
}

bool CQReportDefinition::leave()
{
  return false;
}

bool CQReportDefinition::enter(const std::string & key)
{
  return false;
}
