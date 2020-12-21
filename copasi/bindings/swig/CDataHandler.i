// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include <copasi/report/CDataHandler.h>
%}


%include <copasi/report/CDataHandler.h>

%extend CDataHandler
{

  int getNumRowsDuring()
  {
    return (int)self->getDuringData().size();
  }
  
  std::vector<double> getNthRow(int index)
  {
    const std::vector< std::vector< C_FLOAT64 > > & data = self->getDuringData();
    if (index >= data.size())
      return std::vector<double>();
      
    return data[index];
  }
  
}

