// Various Matrix tests 
// 
// (C) Stefan Hoops 2001
//

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include <vector>

#include "copasi.h"

#include "function/function.h"
#include "model/model.h"
#include "output/output.h"
#include "steadystate/steadystate.h"
#include "trajectory/trajectory.h"
#include "utilities/utilities.h"

#include "VirtualBase.h"

// #include "function/function.h"
#include <typeinfo>

int main(void)
{
  CBaseFunction baseFunction;
  CKinFunction kinFunction;
  CMassAction massFunction;
  
  CBaseFunction *pFunction;
  pFunction = &baseFunction;
  pFunction = &kinFunction;
  pFunction = &massFunction;

  CFunctionDB functionDB;
  functionDB.initialize();
  
  // vector< CCallParameter > parameters;
  // pFunction->calcValue(parameters);
  
  VirtualBase base;
  VirtualDerived derived;
  
  VirtualBase *pbase;
  	
  cout << "char: " << typeid(char).name() << endl;
  cout << "char *: " << typeid(char *).name() << endl;
  cout << "base: " << typeid(base).name() << endl;
  cout << "derived: " << typeid(derived).name() << endl;
  
  pbase = &base;
  cout << "pbase (base): " << typeid(pbase).name() << endl;
//  cout << "*pbase (base): " << typeid(*pbase).name() << endl;
  cout << pbase->getName() << endl;
  
  pbase = &derived;
  cout << "pbase (derived): " << typeid(pbase).name() << endl;
//  cout << "*pbase (derived): " << typeid(*pbase).name() << endl;
  cout << pbase->getName() << endl;
  
  return 0;
  
}

VirtualBase::VirtualBase()
{
  mFirstName = "Stefan";
  mLastName = "Hoops";
}

VirtualBase::~VirtualBase()
{
}


string VirtualBase::getName() 
{
  return mLastName;
}

VirtualDerived::VirtualDerived()
{
  // mFirstName = "Stefan";
  // mLastName = "Hoops";
  mFullName = "Stefan Hoops";
}

VirtualDerived::~VirtualDerived()
{
}


string VirtualDerived::getName() 
{
  return mFullName;
}

C_INT main2(void)
{
  try
    {
      CModel model;
      CCompartment compartment;
      // compartment.initialize();
      
      CMetab metabolite;
      metabolite.setInitialConcentration(1.0);
      
      metabolite.setName("m_1");
      compartment.addMetabolite(metabolite);
  
      metabolite.setName("m_2");
      compartment.addMetabolite(metabolite);
  
      metabolite.setName("m_3");
      compartment.addMetabolite(metabolite);
  
      model.getCompartments().add(compartment);
      model.initializeMetabolites();
      
      CReaction reaction;
      //      reaction.initialize();
      
      reaction.setName("r_1");
      reaction.setChemEq("m_1 -> m_3");
      reaction.setFunction("Mass action (reversible)");
      model.getReactions().add(reaction);

      reaction.setName("r_2");
      reaction.setChemEq("m_3 -> m_1 ");
      model.getReactions().add(reaction);
      
      reaction.setName("r_3");
      reaction.setChemEq("m_1 -> m_2 ");
      model.getReactions().add(reaction);


      model.buildStoi();
      
      unsigned C_INT32 i;
      
      for (i = 0; i < model.getMetabolites().size(); i++)
	{
	  if (i) cout << ", ";
	  cout << model.getMetabolites()[i]->getName();
	}
      cout << endl;
      
      for (i = 0; i < model.getReactions().size(); i++)
	{
	  if (i) cout << ", ";
	  cout << model.getReactions()[i]->getName();
	}
      cout << endl;
      
      model.lUDecomposition();
      
      for (i = 0; i < model.getMetabolitesX().size(); i++)
	{
	  if (i) cout << ", ";
	  cout << model.getMetabolitesX()[i]->getName();
	}
      cout << endl;
      
      for (i = 0; i < model.getReactionsX().size(); i++)
	{
	  if (i) cout << ", ";
	  cout << model.getReactionsX()[i]->getName();
	}
      cout << endl;

      
      model.setMetabolitesStatus();
      model.buildRedStoi();
      model.buildL();
      model.buildMoieties();
      
      cout << "End Test" << endl;
      
    }
  
  catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }

  return 0;
}

