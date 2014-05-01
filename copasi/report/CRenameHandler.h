// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRenameHandler
#define COPASI_CRenameHandler

//just the abstract class to handle things that need to be done after every rename

class CRenameHandler
{
public:
  virtual ~CRenameHandler() {};

  virtual void handle(const std::string & oldCN, const std::string & newCN) const = 0;

  /**
   * Enable and disable the rename handler
   * @param const bool & enabled
   */
  virtual void setEnabled(const bool & enabled) = 0;
};

#endif
