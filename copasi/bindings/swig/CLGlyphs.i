// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CLGlyphs.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLGlyphs.h"

%}

%ignore operator<<;

%ignore CLMetabGlyph::operator= (const CLMetabGlyph&);
%ignore CLMetabGlyph::CLMetabGlyph(const SpeciesGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CCopasiContainer* pParent = NULL);
%ignore CLMetabGlyph::exportToSBML; 
%ignore CLMetabGlyph::print; 

%ignore CLCompartmentGlyph::operator= (const CLCompartmentGlyph&);
%ignore CLCompartmentGlyph::CLCompartmentGlyph(const CompartmentGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CCopasiContainer* pParent = NULL);
%ignore CLCompartmentGlyph::exportToSBML; 
%ignore CLCompartmentGlyph::print; 


%ignore CLTextGlyph::operator= (const CLTextGlyph&);
%ignore CLTextGlyph::CLTextGlyph(const TextGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CCopasiContainer* pParent = NULL);
%ignore CLTextGlyph::exportToSBML; 
%ignore CLTextGlyph::exportReferenceToSBML;
%ignore CLTextGlyph::print;


%include "layout/CLGlyphs.h"


