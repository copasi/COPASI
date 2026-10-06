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
  using EngineVariant = std::variant< bool,
                                      std::independent_bits_engine< std::mt19937, 64, result_type >,
                                      std::mt19937_64,
                                      std::independent_bits_engine< CSobolSequence, 64, result_type >,
                                      std::independent_bits_engine< CR250, 64, result_type > >;

  enum struct Type
  {
    R250 = 0,
    MersenneTwister,
    MersenneTwister_64,
    SobolSequence
  };

private:
  constexpr static CEnumAnnotationInstance _TypeAnnotation{
    Type::MersenneTwister,
    MapNode{Type::R250, "R250"},
    MapNode{Type::MersenneTwister, "Mersenne Twister"},
    MapNode{Type::MersenneTwister_64, "Mersenne Twister (64 bit)"},
    MapNode{Type::SobolSequence, "Sobol Sequence"}
  };

public:
  constexpr static CEnumAnnotation< Type, std::string_view > TypeAnnotation{_TypeAnnotation};

  static CConfigurableRNG::result_type getSystemSeed();

  CConfigurableRNG(Type engineType = Type::MersenneTwister, result_type initialSeed = 0);

  CConfigurableRNG(const CConfigurableRNG & src);

  CConfigurableRNG * copy();

  void seed(result_type newSeed);

  result_type operator()();

  void discard(result_type z);

  constexpr static result_type min() {return 0;};

  constexpr static result_type max() {return std::numeric_limits< result_type >::max();};

  // Type getType() const;

  Type getType() const;

  void setType(Type engineType, result_type initialSeed = 0);

private:
  void initialize();

  EngineVariant mEngine;
  Type mType;
  result_type mSeed;
};
