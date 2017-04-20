// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLGlyphs.h"

%}

%ignore operator<<;

%ignore CLMetabGlyph::operator= (const CLMetabGlyph&);
%ignore CLMetabGlyph::CLMetabGlyph(const SpeciesGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CDataContainer* pParent = NULL);
%ignore CLMetabGlyph::exportToSBML; 
%ignore CLMetabGlyph::print; 

%ignore CLCompartmentGlyph::operator= (const CLCompartmentGlyph&);
%ignore CLCompartmentGlyph::CLCompartmentGlyph(const CompartmentGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CDataContainer* pParent = NULL);
%ignore CLCompartmentGlyph::exportToSBML; 
%ignore CLCompartmentGlyph::print; 


%ignore CLTextGlyph::operator= (const CLTextGlyph&);
%ignore CLTextGlyph::CLTextGlyph(const TextGlyph&,const std::map<std::string,std::string>&,std::map<std::string,std::string>&,const CDataContainer* pParent = NULL);
%ignore CLTextGlyph::exportToSBML; 
%ignore CLTextGlyph::exportReferenceToSBML;
%ignore CLTextGlyph::print;


%include "layout/CLGlyphs.h"


