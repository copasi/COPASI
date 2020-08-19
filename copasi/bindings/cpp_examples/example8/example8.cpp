// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

/**
 * This is an example on how to calculate and output the Jacobian matrix
 * in COPASI
 */
#include <iostream>
#include <iomanip>
#include <vector>

#define COPASI_MAIN
#include "copasi/copasi.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/model/CModelValue.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/core/CMatrix.h"

const char* MODEL_STRING = \
                           "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<!-- Created by COPASI version 4.5.31 (Debug) on 2010-05-11 13:40 with libSBML version 4.1.0-b3. -->\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n"
                           "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n"
                           "    <listOfUnitDefinitions>\n"
                           "      <unitDefinition id=\"volume\" name=\"volume\">\n"
                           "        <listOfUnits>\n"
                           "          <unit kind=\"litre\" scale=\"-3\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "      <unitDefinition id=\"substance\" name=\"substance\">\n"
                           "        <listOfUnits>\n"
                           "          <unit kind=\"mole\" scale=\"-3\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "      <unitDefinition id=\"unit_0\">\n"
                           "        <listOfUnits>\n"
                           "          <unit kind=\"second\" exponent=\"-1\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "    </listOfUnitDefinitions>\n"
                           "    <listOfCompartments>\n"
                           "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
                           "    </listOfCompartments>\n"
                           "    <listOfSpecies>\n"
                           "      <species metaid=\"COPASI2\" id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
                           "      <species metaid=\"COPASI3\" id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n"
                           "      <species metaid=\"COPASI4\" id=\"species_3\" name=\"C\" compartment=\"compartment_1\" initialConcentration=\"0\"/>\n"
                           "    </listOfSpecies>\n"
                           "    <listOfReactions>\n"
                           "      <reaction metaid=\"COPASI5\" id=\"reaction_1\" name=\"reaction_1\" reversible=\"false\">\n"
                           "        <listOfReactants>\n"
                           "          <speciesReference species=\"species_1\"/>\n"
                           "        </listOfReactants>\n"
                           "        <listOfProducts>\n"
                           "          <speciesReference species=\"species_2\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw>\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "            <apply>\n"
                           "              <times/>\n"
                           "              <ci> compartment_1 </ci>\n"
                           "              <ci> k1 </ci>\n"
                           "              <ci> species_1 </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "          <listOfParameters>\n"
                           "            <parameter id=\"k1\" name=\"k1\" value=\"0.2\" units=\"unit_0\"/>\n"
                           "          </listOfParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "      <reaction metaid=\"COPASI6\" id=\"reaction_2\" name=\"reaction_2\" reversible=\"false\">\n"
                           "        <listOfReactants>\n"
                           "          <speciesReference species=\"species_2\"/>\n"
                           "        </listOfReactants>\n"
                           "        <listOfProducts>\n"
                           "          <speciesReference species=\"species_3\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw>\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "            <apply>\n"
                           "              <times/>\n"
                           "              <ci> compartment_1 </ci>\n"
                           "              <ci> k1 </ci>\n"
                           "              <ci> species_2 </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "          <listOfParameters>\n"
                           "            <parameter id=\"k1\" name=\"k1\" value=\"0.1\" units=\"unit_0\"/>\n"
                           "          </listOfParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "    </listOfReactions>\n"
                           "  </model>\n"
                           "</sbml>\n";

int main()
{
  // initialize the backend library
  // since we are not interested in the arguments
  // that are passed to main, we pass 0 and NULL to
  // init
  CRootContainer::init(0, NULL);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(pDataModel != NULL);
  assert(CRootContainer::getDatamodelList()->size() == 1);
  // next we import a simple SBML model from a string

  // clear the message queue so that we only have error messages from the import in the queue
  CCopasiMessage::clearDeque();
  bool result = pDataModel->importSBMLFromString(MODEL_STRING);
  // check if the import was successful
  CCopasiMessage::Type mostSevere = CCopasiMessage::getHighestSeverity();
  // if it was a filtered error, we convert it to an unfiltered type
  // the filtered error messages have the same value as the unfiltered, but they
  // have the 7th bit set which basically adds 128 to the value
  mostSevere = (CCopasiMessage::Type)((int)mostSevere & 127);

  // we assume that the import succeeded if the return value is true and
  // the most severe error message is not an error or an exception
  if (result != true &&  mostSevere < CCopasiMessage::ERROR)
    {
      std::cerr << "Sorry. Model could not be imported." << std::endl;
      return 1;
    }

  //
  // now we tell the model object to calculate the jacobian
  //
  CModel* pModel = pDataModel->getModel();
  assert(pModel != NULL);

  if (pModel != NULL)
    {
      // running a task, e.g. a trajectory will automatically make sure that
      // the initial values are transferred to the current state before the calculation begins.
      // If we use low level calculation methods like the one to calculate the jacobian, we
      // have to make sure the the initial values are applied to the state
      pModel->applyInitialValues();
      // we need an array that stores the result
      // the size of the matrix does not really matter because
      // the calculateJacobian automatically resizes it to the correct
      // size
      CMatrix<C_FLOAT64> jacobian;
      // the first parameter to the calculation function is a reference to
      // the matrix where the result is to be stored
      // the second parameter is the derivationFactor for the calculation
      // it basically represents a relative delta value for the calculation of the derivatives
      // the third parameter termed resolution in the C++ API is currently ignores
      // so it does not matter what value you give here.
      pModel->getMathContainer().calculateJacobian(jacobian, 1e-12, false);
      // now we print the result
      // the jacobian stores the values in the order they are
      // given in the user order in the state template so it is not really straight
      // forward to find out which column/row corresponds to which species
      const CStateTemplate& stateTemplate = pModel->getStateTemplate();
      // we get a pointer to all entities
      const CModelEntity *const* pEntities = stateTemplate.getEntities().array();
      // and we need the user order
      const CVector<size_t>& userOrder = stateTemplate.getUserOrder();
      // from those two, we can construct an new vector that contains
      // the names of the entities in the jacobian in the order in which they appear in
      // the jacobian
      std::vector<std::string> nameVector;
      const CModelEntity* pEntity = NULL;
      CModelEntity::Status status;

      for (size_t i = 0; i < userOrder.size(); ++i)
        {
          pEntity = pEntities[userOrder[i]];
          assert(pEntity != NULL);
          // now we need to check if the entity is actually
          // determined by an ODE or a reaction
          status = pEntity->getStatus();

          if (status == CModelEntity::Status::ODE ||
              (status == CModelEntity::Status::REACTIONS && pEntity->isUsed()))
            {
              nameVector.push_back(pEntity->getObjectName());
            }
        }

      assert(nameVector.size() == jacobian.numRows());
      // now we print the matrix, for this we assume that no
      // entity name is longer then 5 character which is a save bet since
      // we know the model
      std::cout << "Jacobian Matrix:" << std::endl << std::endl;
      std::cout << std::setw(5) << " ";

      for (size_t i = 0; i < nameVector.size(); ++i)
        {
          std::cout << std::setw(5) << nameVector[i];
        }

      std::cout << std::endl;

      for (size_t i = 0; i < nameVector.size(); ++i)
        {
          std::cout << std::setw(5) << nameVector[i];

          for (size_t j = 0; j < nameVector.size(); ++j)
            {
              std::cout << std::setw(5) << std::setprecision(3) << jacobian[i][j];
            }

          std::cout << std::endl;
        }

      // we can also calculate the jacobian of the reduced system
      // in a similar way
      pModel->getMathContainer().calculateJacobian(jacobian, 1e-12, true);

      // this time generating the output is actually simpler because the rows
      // and columns are ordered in the same way as the independent variables of the state temple
      std::cout << std::endl << std::endl << "Reduced Jacobian Matrix:" << std::endl << std::endl;
      std::cout << std::setw(5) << " ";
      const CModelEntity *const* beginIndependent = stateTemplate.beginIndependent();
      const CModelEntity *const* endIndependent = stateTemplate.endIndependent();

      while (beginIndependent < endIndependent)
        {
          std::cout << std::setw(5) << (*beginIndependent)->getObjectName();
          ++beginIndependent;
        }

      std::cout << std::endl;
      beginIndependent = stateTemplate.beginIndependent();
      size_t iMax = stateTemplate.getNumIndependent();

      for (size_t i = 0; i < iMax; ++i)
        {
          std::cout << std::setw(5) << (*(beginIndependent + i))->getObjectName();

          for (size_t j = 0; j < iMax; ++j)
            {
              std::cout << std::setw(5) << std::setprecision(3) << jacobian[i][j];
            }

          std::cout << std::endl;
        }
    }

  // destroy the root container once we are done
  CRootContainer::destroy();

  return 0;
}
