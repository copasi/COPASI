// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 


%template(CompartmentGlyphVector) CCopasiVector<CLCompartmentGlyph>;
typedef CCopasiVector<CLCompartmentGlyph> CompartmentGlyphVector;

%template(MetabGlyphVector) CCopasiVector<CLMetabGlyph>;
typedef CCopasiVector<CLMetabGlyph> MetabGlyphVector;

%template(ReactionGlyphVector) CCopasiVector<CLReactionGlyph>;
typedef CCopasiVector<CLReactionGlyph> ReactionGlyphVector;

%template(TextGlyphVector) CCopasiVector<CLTextGlyph>;
typedef CCopasiVector<CLTextGlyph> TextGlyphVector;

%template(GraphicalObjectVector) CCopasiVector<CLGraphicalObject>;
typedef CCopasiVector<CLGraphicalObject> GraphicalObjectVector;


%{

#include "layout/CLayout.h"

%}

%ignore operator<<;

%ignore CLayout::CLayout(const Layout & , std::map<std::string, std::string> & , const CCopasiContainer * pParent = NULL);
%ignore CLayout::exportToSBML;
%ignore CLayout::print;
%ignore CLayout::exportToDotFile;
%ignore CLayout::getListOfLocalRenderInformationObjects;
%ignore CLayout::getListOfMetaboliteGlyphs;
%ignore CLayout::getListOfTextGlyphs;
%ignore CLayout::getRenderInformation;

// suppress warnings on multiple inheritance
%warnfilter(813) CLayout;


%include "layout/CLayout.h"


