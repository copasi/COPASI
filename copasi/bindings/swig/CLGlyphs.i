// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLGlyphs.i,v $ 
//   $Revision: 1.1.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/10 15:33:43 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLGlyphs.h"

%}

%ignore CLMetabGlyph::operator= (const CLMetabGlyph&);
%ignore operator<<(std::ostream&,const CLMetabGlyph&);
%ignore CLMetabGlyph::CLMetabGlyph(const SpeciesGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CCopasiContainer* pParent = NULL);
%ignore CLMetabGlyph::exportToSBML; 

%ignore CLCompartmentGlyph::operator= (const CLCompartmentGlyph&);
%ignore operator<<(std::ostream&,const CLCompartmentGlyph&);
%ignore CLCompartmentGlyph::CLCompartmentGlyph(const CompartmentGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CCopasiContainer* pParent = NULL);
%ignore CLCompartmentGlyph::exportToSBML; 


%ignore CLTextGlyph::operator= (const CLTextGlyph&);
%ignore operator<<(std::ostream&,const CLTextGlyph&);
%ignore CLTextGlyph::CLTextGlyph(const TextGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CCopasiContainer* pParent = NULL);
%ignore CLTextGlyph::exportToSBML; 
%ignore CLTextGlyph::exportReferenceToSBML;


%include "layout/CLGlyphs.h"


