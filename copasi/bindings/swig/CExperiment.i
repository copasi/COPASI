// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CExperiment.i,v $ 
//   $Revision: 1.1.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/24 17:05:42 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{
#include <fstream>
#include <sstream>    
#include "parameterFitting/CExperiment.h"

%}

%ignore CExperiment::XMLType;
%ignore CExperiment::WeightMethodType;
%ignore CExperiment::operator=;

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
          fin.open(utf8ToLocale(s).c_str(), std::ios::binary);
          if (fin.fail())
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCFitting + 8, s.c_str());
              return false; // File can not be opened.
            }
          unsigned C_INT32 n=0;
          result=$self->read(fin,n);
          fin.close();
       }
       else
       {
          std::stringstream sin;
          sin.str(s);
          unsigned C_INT32 n=0;
          result=$self->read(sin,n);
       }
       return result;
   }

}


