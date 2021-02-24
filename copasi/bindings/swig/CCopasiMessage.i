// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "copasi/utilities/CCopasiMessage.h"
  
%}

%ignore CCopasiMessage::operator=(const CCopasiMessage&);
%ignore MESSAGES;
%ignore Message;

%include "copasi/utilities/CCopasiMessage.h"

%extend CCopasiMessage
{
    CCopasiMessage(CCopasiMessage::Type type, char const * format)
    {
        CCopasiMessage* m = new CCopasiMessage(type, format);
        return m;
    }

    CCopasiMessage(CCopasiMessage::Type type, char const* format, const char* arg)
    {
        CCopasiMessage* m = new CCopasiMessage(type, format, arg);
        return m;
    }

    CCopasiMessage(CCopasiMessage::Type type, size_t number)
    {
        CCopasiMessage* m = new CCopasiMessage(type, number);
        return m;
    }

    CCopasiMessage(CCopasiMessage::Type type, size_t number, const char* arg)
    {
        CCopasiMessage* m = new CCopasiMessage(type, number, arg);
        return m;
    }

};


