%{

#include "trajectory/CTimeSeries.h"
  
%}

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


%include "trajectory/CTimeSeries.h"

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


