// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 




%{
#include <fstream>
#include <sstream>    
#include "copasi/parameterFitting/CExperiment.h"
#include "copasi/commandline/CLocaleString.h"

%}

%ignore CExperiment::XMLType;
%ignore CExperiment::TypeName;
%ignore CExperiment::WeightMethodName;
%ignore CExperiment::WeightMethodType;
%ignore CExperiment::operator=;
%ignore CExperiment::sumOfSquares;
%ignore CExperiment::sumOfSquaresStore;
%ignore CExperiment::printResult;


// read is rather useless since it takes an istream as its first argument

%include "copasi/parameterFitting/CExperiment.h"

%extend CExperiment 
{
   /** 
    * Reads the experiment from a file or string buffer
    * 
    * @param s the experiment filename, or experiment read to string
    * @param startLine the first line to read (defaults to 0)
    * @param isFilename boolean indcating whether s is a file, or buffer (defaults to true)
    * 
    * @return the last line read, or -1 in case of failure   
    * 
    */ 
   int read(const std::string& s, int startLine = 0, bool isFilename=true)
   {
       size_t n=startLine;
       bool result=false;
       if(isFilename)
       {
          std::fstream fin; 
          fin.open(CLocaleString::fromUtf8(s).c_str(), std::ios::in | std::ios::binary);
          if (fin.fail())
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 8, s.c_str());
              return -1; // File can not be opened.
            }
          result=$self->read(fin,n);
          fin.close();
       }
       else
       {
          std::stringstream sin;
          sin.str(s);          
          result=$self->read(sin,n);
       }
       
       if (result)
         return n;
       
       return -1;
   }

}


