// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLReactionGlyph.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:26 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 



%{

#include "layout/CLReactionGlyph.h"

%}

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
%ignore CLReactionGlyph::getCurve() const;
%ignore CLReactionGlyph::print;
%ignore CLReactionGlyph::exportToSBML;
%ignore CLReactionGlyph::CLReactionGlyph(const ReactionGlyph & , const std::map<std::string, std::string> & , std::map<std::string, std::string> & , const CCopasiContainer * pParent = NULL);




%include "layout/CLReactionGlyph.h"

%template(MetabReferenceGlyphVector) CCopasiVector<CLMetabReferenceGlyph>;
typedef CCopasiVector<CLMetabReferenceGlyph> MetabReferenceGlyphVector;


