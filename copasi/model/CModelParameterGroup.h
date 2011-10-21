// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelParameterGroup.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/21 17:45:15 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CModelParameterGroup
#define COPASI_CModelParameterGroup

#include <vector>

#include "copasi.h"

#include "copasi/model/CModelParameter.h"

class CModel;

class CModelParameterGroup: public CModelParameter
{
public:
  typedef std::vector< CModelParameter * >::iterator iterator;
  typedef std::vector< CModelParameter * >::const_iterator const_iterator;

public:
  CModelParameterGroup(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::Group);

  CModelParameterGroup(const CModelParameterGroup & src, CModelParameterGroup * pParent);

  virtual ~CModelParameterGroup();

  virtual CModel * getModel();

  CModelParameter * add(const CModelParameter::Type & type);

  void remove(const size_t & index);

  iterator begin();

  iterator end();

  const_iterator begin() const;

  const_iterator end() const;

  virtual void compile();

  void clear();

  virtual const CompareResult & diff(const CModelParameter & other);

  virtual bool updateModel();

private:
  std::vector< CModelParameter * > mModelParameters;
};

#endif // COPASI_CModelParameterGroup
