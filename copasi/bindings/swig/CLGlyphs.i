// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLGlyphs.i,v $ 
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

#include "layout/CLGlyphs.h"

%}

%ignore CLMetabGlyph::operator= (const CLMetabGlyph&);
%ignore operator<<(std::ostream&,const CLMetabGlyph&);
%ignore CLCompartmentGlyph::operator= (const CLCompartmentGlyph&);
%ignore operator<<(std::ostream&,const CLCompartmentGlyph&);
%ignore CLTextGlyph::operator= (const CLTextGlyph&);
%ignore operator<<(std::ostream&,const CLTextGlyph&);


%include "layout/CLGlyphs.h"


