// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 





%{

#include "layout/CLReactionGlyph.h"

%}

%ignore operator<<;

%ignore CLReferenceGlyph::operator= (const CLReferenceGlyph&);
%ignore operator<< (std::ostream&,const CLReferenceGlyph&);
%ignore CLReferenceGlyph::getCurve() const;
%ignore CLReferenceGlyph::CLReferenceGlyph(const ReferenceGlyph & sbml, //TODO preliminary
                   const std::map<std::string, std::string> & modelmap,
                   std::map<std::string, std::string> & layoutmap,
                   const CCopasiContainer * pParent = NULL);
%ignore CLReferenceGlyph::exportToSBML;
%ignore CLReferenceGlyph::RoleName;
%ignore CLReferenceGlyph::XMLRole;
%ignore CLReferenceGlyph::print;


%ignore CLGeneralGlyph::operator= (const CLGeneralGlyph&);
%ignore operator<< (std::ostream&,const CLGeneralGlyph&);
%ignore CLGeneralGlyph::getCurve() const;
%ignore CLGeneralGlyph::print;
%ignore CLGeneralGlyph::exportToSBML;
%ignore CLGeneralGlyph::CLGeneralGlyph((const GraphicalObject & sbml, //TODO
                 const std::map<std::string, std::string> & modelmap,
                 std::map<std::string, std::string> & layoutmap,
                 const CCopasiContainer * pParent = NULL);




%include "layout/CLReactionGlyph.h"

%template(ReferenceGlyphVector) CCopasiVector<CLReferenceGlyph>;
typedef CCopasiVector<CLReferenceGlyph> ReferenceGlyphVector;

%template(GeneralGlyphVector) CCopasiVector<CLGeneralGlyph>;
typedef CCopasiVector<CLGeneralGlyph> GeneralGlyphVector;

