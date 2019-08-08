// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
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





%template(CompartmentGlyphVector) CDataVector<CLCompartmentGlyph>;
typedef CDataVector<CLCompartmentGlyph> CompartmentGlyphVector;

%template(MetabGlyphVector) CDataVector<CLMetabGlyph>;
typedef CDataVector<CLMetabGlyph> MetabGlyphVector;

%template(ReactionGlyphVector) CDataVector<CLReactionGlyph>;
typedef CDataVector<CLReactionGlyph> ReactionGlyphVector;

%template(TextGlyphVector) CDataVector<CLTextGlyph>;
typedef CDataVector<CLTextGlyph> TextGlyphVector;

%template(GraphicalObjectVector) CDataVector<CLGraphicalObject>;
typedef CDataVector<CLGraphicalObject> GraphicalObjectVector;


%{

#include "copasi/layout/CLayout.h"

%}

%ignore operator<<;

%ignore CLayout::CLayout(const Layout & , std::map<std::string, std::string> & , const CDataContainer * pParent = NULL);
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


%include "copasi/layout/CLayout.h"


