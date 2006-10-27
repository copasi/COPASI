%{

#include "utilities/CVersion.h"

%}

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


// add ignore statements for the setVersion function
// disable the Constructor since there is no need to create an object of type
// CVersion
%ignore CVersion::setVersion(const C_INT32 & major,
                   const C_INT32 & minor,
                   const C_INT32 & devel,
                   const std::string & comment);
%ignore CVersion::CVersion();
%ignore CVersion::~CVersion();

%include "utilities/CVersion.h"

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


