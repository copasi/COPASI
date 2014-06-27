// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 







%{

#include "layout/CLReactionGlyph.h"

%}

%ignore operator=;
%ignore operator<<;

%ignore CLMetabReferenceGlyph::operator= (const CLMetabReferenceGlyph&);
%ignore operator<< (std::ostream&,const CLMetabReferenceGlyph&);
%ignore CLMetabReferenceGlyph::getCurve() const;
%ignore CLMetabReferenceGlyph::CLMetabReferenceGlyph(const SpeciesReferenceGlyph & , const std::map<std::string, std::string> & , std::map<std::string, std::string> & , const CCopasiContainer * pParent = NULL);
%ignore CLMetabReferenceGlyph::exportToSBML;
%ignore CLMetabReferenceGlyph::RoleName;
%ignore CLMetabReferenceGlyph::XMLRole;
%ignore CLMetabReferenceGlyph::print;


%ignore CLReactionGlyph::operator= (const CLReactionGlyph&);
%ignore operator<< (std::ostream&,const CLReactionGlyph&);
%ignore CLGlyphWithCurve::getCurve() const;
%ignore CLGlyphWithCurve::CLGlyphWithCurve(const GraphicalObject &,const std::map<std::string, std::string> &,                   std::map<std::string, std::string> &,                   const CCopasiContainer * pParent = NULL);
%ignore CLReactionGlyph::getCurve() const;
%ignore CLReactionGlyph::print;
%ignore CLReactionGlyph::exportToSBML;
%ignore CLReactionGlyph::CLReactionGlyph(const ReactionGlyph & , const std::map<std::string, std::string> & , std::map<std::string, std::string> & , const CCopasiContainer * pParent = NULL);

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
%ignore CLGeneralGlyph::getListOfReferenceGlyphs() const;
%ignore CLGeneralGlyph::getListOfSubglyphs() const;
%ignore CLReactionGlyph::getListOfMetabReferenceGlyphs() const;
%ignore CLGeneralGlyph::getCurve() const;
%ignore CLGeneralGlyph::print;
%ignore CLGeneralGlyph::exportToSBML;
%ignore CLGeneralGlyph::CLGeneralGlyph(const GraphicalObject & sbml, //TODO
                 const std::map<std::string, std::string> & modelmap,
                 std::map<std::string, std::string> & layoutmap,
                 const CCopasiContainer * pParent = NULL);



%include "layout/CLReactionGlyph.h"

%template(MetabReferenceGlyphVector) CCopasiVector<CLMetabReferenceGlyph>;
typedef CCopasiVector<CLMetabReferenceGlyph> MetabReferenceGlyphVector;


