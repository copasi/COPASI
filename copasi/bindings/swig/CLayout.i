// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLayout.i,v $ 
//   $Revision: 1.1.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/10 15:33:43 $ 
// End CVS Header 

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

%ignore CLayout::CLayout(const Layout & , std::map<std::string, std::string> & , const CCopasiContainer * pParent = NULL);
%ignore CLayout::exportToSBML;


%include "layout/CLayout.h"


