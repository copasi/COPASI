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

C_INT main(void)
{
  try
    {
      CModel model;
      model.initialize();
  
      CCompartment compartment;
      compartment.initialize();
      
      CReadConfig in("tmp"); 
      CWriteConfig out("tmp"); 
      
      CMetab metabolite;

      metabolite.setName("m_1");
      compartment.addMetabolite(metabolite);
  
      metabolite.setName("m_2");
      compartment.addMetabolite(metabolite);
  
      metabolite.setName("m_3");
      compartment.addMetabolite(metabolite);
  
      model.getCompartments()->add(compartment);
    }
  
  catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }

  return 0;
}

