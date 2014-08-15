// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
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
%ignore CLayout::getListOfCompartmentGlyphs() const;
%ignore CLayout::getListOfReactionGlyphs() const;
%ignore CLayout::getListOfGeneralGlyphs() const;
%ignore CLayout::exportToDotFile;
%ignore CLayout::getListOfLocalRenderInformationObjects;
%ignore CLayout::getListOfMetaboliteGlyphs;
%ignore CLayout::getListOfTextGlyphs;
%ignore CLayout::getRenderInformation;

// suppress warnings on multiple inheritance
%warnfilter(813) CLayout;


%include "layout/CLayout.h"


