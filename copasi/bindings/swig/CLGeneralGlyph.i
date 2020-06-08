// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 







%{

#include "copasi/layout/CLReactionGlyph.h"

%}


%include "copasi/layout/CLReactionGlyph.h"

%template(ReferenceGlyphVector) CDataVector<CLReferenceGlyph>;
typedef CDataVector<CLReferenceGlyph> ReferenceGlyphVector;

%template(GeneralGlyphVector) CDataVector<CLGeneralGlyph>;
typedef CDataVector<CLGeneralGlyph> GeneralGlyphVector;

