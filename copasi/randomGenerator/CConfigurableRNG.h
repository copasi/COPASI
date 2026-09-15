// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <random>
#include <variant>
#include <concepts>

#include "copasi/core/CCore.h"
#include "copasi/core/CEnumAnnotation.h"
#include "copasi/lgpl/CSobolSequence.h"
#include "copasi/randomGenerator/CR250.h"

class CConfigurableRNG
{
public:
  using result_type = std::mt19937_64::result_type;
  using EngineVariant = std::variant< std::mt19937_64,
                                      std::independent_bits_engine< CSobolSequence, 64, result_type >,
                                      std::independent_bits_engine< CR250, 64, result_type > >;

  enum struct Type
  {
    R250 = 0,
    Obsolete,
    MersenneTwister,
    SobolSequence,
    __SIZE
  };

  static const CEnumAnnotation< std::string, Type > TypeAnnotation;
  static CConfigurableRNG * create(Type engineType = Type::MersenneTwister, result_type initialSeed = 0);
  static CConfigurableRNG::result_type getSystemSeed();

  CConfigurableRNG() = delete;
  CConfigurableRNG(const CConfigurableRNG &) = default;

  CConfigurableRNG * copy();

  void seed(result_type newSeed);

  result_type operator()();
  void discard(result_type z);

  constexpr static result_type min()
  {
    return 0;
  };
  constexpr static result_type max()
  {
    return std::numeric_limits< result_type >::max();
  };

  Type getType() const;
  void setType(Type engineType, result_type initialSeed = 0);

private:
  CConfigurableRNG(Type mEngineType, result_type initialSeed);

  EngineVariant mEngine;
  Type mType;
};
