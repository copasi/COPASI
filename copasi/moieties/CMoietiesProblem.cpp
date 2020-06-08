// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "CMoietiesProblem.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/core/CDataArray.h"

//  Default constructor
CMoietiesProblem::CMoietiesProblem(const CTaskEnum::Task & type,
                                   const CDataContainer * pParent):
  CCopasiProblem(type, pParent)
{}

// copy constructor
CMoietiesProblem::CMoietiesProblem(const CMoietiesProblem & src,
                                   const CDataContainer * pParent):
  CCopasiProblem(src, pParent)
{}

// Destructor
CMoietiesProblem::~CMoietiesProblem()
{}

void CMoietiesProblem::printResult(std::ostream * pOstream) const
{
  const CModel & Model = mpContainer->getModel();

  // Print all Moieties
  *pOstream << "Dependent Species" << "\t";
  *pOstream << "Total Amount" << "\t";
  *pOstream << "Total Particle Amount" << "\t";
  *pOstream << "Expression" << std::endl;

  CDataVector< CMoiety >::const_iterator it = Model.getMoieties().begin();
  CDataVector< CMoiety >::const_iterator end = Model.getMoieties().end();

  for (; it != end; ++it)
    {
      *pOstream << it->getObjectName() << "\t";
      *pOstream << it->getAmount() << "\t";
      *pOstream << it->getNumber() << "\t";
      *pOstream << it->getDescription(&Model) << std::endl;
    }

  *pOstream << std::endl;

  // Print Reordered Stoichiometry Matrix
  *pOstream << *dynamic_cast<const CDataArray *>(Model.getObject(CCommonName("Array=Stoichiometry(ann)"))) << std::endl;

  // Print Link Matrix
  *pOstream << *dynamic_cast<const CDataArray *>(Model.getObject(CCommonName("Array=Link matrix(ann)"))) << std::endl;

  // Print Reduced Stoichiometry Matrix
  *pOstream << *dynamic_cast<const CDataArray *>(Model.getObject(CCommonName("Array=Reduced stoichiometry(ann)"))) << std::endl;

  return;
}
