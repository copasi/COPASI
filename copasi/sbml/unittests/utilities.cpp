// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/xml/CCopasiXML.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/model/CModel.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/layout/CListOfLayouts.h"

bool load_cps_model_from_stream(std::istream& is, CDataModel& dataModel)
{
  return dataModel.loadModel(is, std::string(""), NULL);
}

bool save_cps_model_to_stream(std::ostream& os, CDataModel* pDataModel)
{
  bool success = true;

  if (pDataModel != NULL &&
      pDataModel->getModel() != NULL)
    {
      CCopasiXML XML;

      XML.setModel(pDataModel->getModel());
      XML.setTaskList(pDataModel->getTaskList());
      XML.setReportList(pDataModel->getReportDefinitionList());
      XML.setPlotList(pDataModel->getPlotDefinitionList());
      XML.setGUI(pDataModel->getGUI());
      XML.setLayoutList(*pDataModel->getListOfLayouts());
      XML.setDatamodel(pDataModel);

      try
        {
          success = XML.save(os, "");
        }
      catch (...)
        {
          return false;
        }
    }
  else
    {
      success = false;
    }

  return success;
}
