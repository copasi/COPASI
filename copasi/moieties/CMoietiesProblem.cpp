// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMoietiesProblem.h"

#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "utilities/CAnnotatedMatrix.h"

//  Default constructor
CMoietiesProblem::CMoietiesProblem(const CCopasiTask::Type & type,
                                   const CCopasiContainer * pParent):
  CCopasiProblem(type, pParent)
{}

// copy constructor
CMoietiesProblem::CMoietiesProblem(const CMoietiesProblem & src,
                                   const CCopasiContainer * pParent):
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
  *pOstream << "Expression" << std::endl;

  CCopasiVector< CMoiety >::const_iterator it = Model.getMoieties().begin();
  CCopasiVector< CMoiety >::const_iterator end = Model.getMoieties().end();

  for (; it != end; ++it)
    {
      *pOstream << (*it)->getObjectName() << "\t";
      *pOstream << (*it)->getNumber() << "\t";
      *pOstream << (*it)->getDescription(&Model) << std::endl;
    }

  *pOstream << std::endl;

  // Print Reordered Stoichiometry Matrix
  *pOstream << *dynamic_cast<const CArrayAnnotation *>(Model.getObject(CCopasiObjectName("Array=Stoichiometry(ann)"))) << std::endl;

  // Print Link Matrix
  *pOstream << *dynamic_cast<const CArrayAnnotation *>(Model.getObject(CCopasiObjectName("Array=Link matrix(ann)"))) << std::endl;

  // Print Reduced Stoichiometry Matrix
  *pOstream << *dynamic_cast<const CArrayAnnotation *>(Model.getObject(CCopasiObjectName("Array=Reduced stoichiometry(ann)"))) << std::endl;

  return;
}
