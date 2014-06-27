// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 




%{
#include <fstream>
#include <sstream>    
#include "parameterFitting/CExperiment.h"
#include "commandline/CLocaleString.h"

%}

%ignore CExperiment::read;
%ignore CExperiment::XMLType;
%ignore CExperiment::TypeName;
%ignore CExperiment::WeightMethodName;
%ignore CExperiment::WeightMethodType;
%ignore CExperiment::operator=;
%ignore CExperiment::sumOfSquares;
%ignore CExperiment::sumOfSquaresStore;
%ignore CExperiment::printResult;
%ignore CExperiment::getDependentObjects;
%ignore CExperiment::getIndependentObjects;


// read is rather useless since it takes an istream as its first argument
%ignore CExperiment::read(std::istream&,unsigned C_INT32&);

%include "parameterFitting/CExperiment.h"

//%rename (read) CExperiment::read;

%extend CExperiment {
   // we add a method that takes a string as its forst argument
   // if the second argument is true, the string is to be interpreted as a
   // filename otherwise, the string is the actual data content
   bool read(const std::string& s,bool filename=true)
   {
       bool result=false;
       if(filename==true)
       {
          std::fstream fin; 
          fin.open(CLocaleString::fromUtf8(s).c_str(), std::ios::binary);
          if (fin.fail())
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 8, s.c_str());
              return false; // File can not be opened.
            }
          size_t n=0;
          result=$self->read(fin,n);
          fin.close();
       }
       else
       {
          std::stringstream sin;
          sin.str(s);
          size_t n=0;
          result=$self->read(sin,n);
       }
       return result;
   }

}


