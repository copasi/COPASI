// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CReactionParameter
#define COPASI_CReactionParameter

#include "copasi/function/CFunctionParameter.h"

class CReactionParameter : public CFunctionParameter
{
  CReactionParameter();

  CReactionParameter(const CReactionParameter & src)

  CReactionParameter(const CFunctionParameter & base)

  ~CReactionParameter()

  void setValue();

  const C_FLOAT64 & getValue() const;

  bool isLocal() const;

  const std::vector< CRegisteredCommonName > & getCNs() const;

  bool setCNs(const std::vector< CRegisteredCommonName >& CNs);

  const std::vector< const CDataObject * > & getObjects(const size_t & index) const;

  bool setObjects(const std::vector< const CDataObject * >& objects);

  bool setObject(const CDataObject * object);

  bool addObject(const CDataObject * object);

private:
  std::vector< CRegisteredCommonName > mCNs;
  std::vector< const CDataObject * > mObjects;
  std::vector< C_FLOAT64 > mLocalValues;
  std::vector< C_FLOAT64 * > mValuePointers;
};

#endif // COPASI_CReactionParameter
