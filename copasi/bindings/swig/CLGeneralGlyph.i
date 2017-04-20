// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 







%{

#include "layout/CLReactionGlyph.h"

%}


%include "layout/CLReactionGlyph.h"

%template(ReferenceGlyphVector) CDataVector<CLReferenceGlyph>;
typedef CDataVector<CLReferenceGlyph> ReferenceGlyphVector;

%template(GeneralGlyphVector) CDataVector<CLGeneralGlyph>;
typedef CDataVector<CLGeneralGlyph> GeneralGlyphVector;

