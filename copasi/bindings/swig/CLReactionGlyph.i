// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLReactionGlyph.i,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/10 14:22:07 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLReactionGlyph.h"

%}

%ignore CLMetabReferenceGlyph::operator= (const CLMetabReferenceGlyph&);
%ignore operator<< (std::ostream&,const CLMetabReferenceGlyph&);
%ignore CLMetabReferenceGlyph::getCurve() const;
%ignore CLReactionGlyph::operator= (const CLReactionGlyph&);
%ignore operator<< (std::ostream&,const CLReactionGlyph&);
%ignore CLReactionGlyph::getCurve() const;



%include "layout/CLReactionGlyph.h"


