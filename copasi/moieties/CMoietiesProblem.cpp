// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesProblem.cpp,v $
//   $Revision: 1.1.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/20 20:25:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMoietiesProblem.h"

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
    if (mpModel == NULL) return;

    // Print all Moieties
    *pOstream << "Dependent Species" << "\t";
    *pOstream << "Total Amount" << "\t";
    *pOstream << "Expression" << std::endl;

    CCopasiVector< CMoiety >::const_iterator it = mpModel->getMoieties().begin();
    CCopasiVector< CMoiety >::const_iterator end = mpModel->getMoieties().end();
    for (; it != end; ++it)
      {
        *pOstream << (*it)->getObjectName() << "\t";
        *pOstream << (*it)->getNumber() << "\t";
        *pOstream << (*it)->getDescription(mpModel) << std::endl;
      }
    *pOstream << std::endl;

    // Print Reordered Stoichiometry Matrix
    *pOstream << *dynamic_cast<const CArrayAnnotation *>(mpModel->getObject(CCopasiObjectName("Array=Stoichiometry(ann)"))) << std::endl;

    // Print Link Matrix
    *pOstream << *dynamic_cast<const CArrayAnnotation *>(mpModel->getObject(CCopasiObjectName("Array=Link matrix(ann)"))) << std::endl;

    // Print Reduced Stoichiometry Matrix
    *pOstream << *dynamic_cast<const CArrayAnnotation *>(mpModel->getObject(CCopasiObjectName("Array=Reduced stoichiometry(ann)"))) << std::endl;

    return;
  }
