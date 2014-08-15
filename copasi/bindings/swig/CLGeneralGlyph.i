// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 







%{

#include "layout/CLReactionGlyph.h"

%}


%include "layout/CLReactionGlyph.h"

%template(ReferenceGlyphVector) CCopasiVector<CLReferenceGlyph>;
typedef CCopasiVector<CLReferenceGlyph> ReferenceGlyphVector;

%template(GeneralGlyphVector) CCopasiVector<CLGeneralGlyph>;
typedef CCopasiVector<CLGeneralGlyph> GeneralGlyphVector;

