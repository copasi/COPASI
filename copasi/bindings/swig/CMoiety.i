// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CMoiety.i,v $ 
//   $Revision: 1.6 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/08/20 10:58:39 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "model/CMoiety.h"  
  
%}

%nodefaultctor CMoiety;
%nodefaultdtor CMoiety;

class CMoiety : public CCopasiContainer
{
  public:

    /**
     * get the string representation of the moiety using the CMetabNameInterface
     */
    std::string getDescription(const CModel* model) const;

    /**
     * Retrieve and refresh the dependent number;
     * @return const C_FLOAT64 & dependentNumber
    const C_FLOAT64 & dependentNumber();
     */

    /**
     *
     */
    C_FLOAT64 getNumber() const;

    /**
     *  Returns a string with the name of this compartment.
     *  @return std::string key
     */
    virtual const std::string & getKey() const; //By G

%extend
{
  
  C_FLOAT64 getDependentNumber()
  {
    self->refreshDependentNumber();
    return self->getDependentNumber();
  }  

}


};


