// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CCoreEnum
#define COPASI_CCoreEnum

#include <array>

#include "copasi/core/CFlags.h"

class CMathUpdateSequence;

class CCore
{
public:
  typedef CMathUpdateSequence CUpdateSequence;

  enum struct SimulationContext
  {
    Default,
    // This is used to indicate deterministic simulation
    // Deterministic = 0x1,
    // This must be set when using the reduced model
    UseMoieties,
    // This updates the total mass of a moiety and must be set
    // at the beginning of the simulation or after events
    UpdateMoieties,
    // This is used to indicate stochastic simulation
    // Stochastic = 0x8,
    // Event handling
    EventHandling,
    // This is used to detect whether a delay value depends on other delay values.
    DelayValues,
    __SIZE
  };

  typedef CFlags< SimulationContext > SimulationContextFlag;

  enum struct Framework
  {
    Concentration = 0,
    ParticleNumbers
  };

  /**
   * Convert an annotation to enum. If no matching name is found the parameter enumDefault is returned.
   * @param const AType & annotation
   * @param const std::array<AType, static_cast<size_t>(Enum::__SIZE)> & enumAnnotations
   * @param const Enum & enumDefault (default Enum::__SIZE)
   * @return Enum enum
   */
  template < typename Enum, typename AType >
  Enum AnnotationToEnum(const AType & annotation,
                        const std::array< AType, static_cast< size_t >(Enum::__SIZE) > & enumAnnotations,
                        const Enum & enumDefault = Enum::__SIZE)
  {
    for (size_t i = 0; i < static_cast< size_t >(Enum::__SIZE); i++)
      if (annotation == enumAnnotations[i]) return static_cast< Enum >(i);

    return enumDefault;
  }

  /**
   * Convert an annotation to enum. If no matching name is found the parameter enumDefault is returned.
   * @param const const char * & annotation
   * @param const std::array<const char *, static_cast<size_t>(Enum::__SIZE)> & enumAnnotations
   * @param const Enum & enumDefault (default Enum::__SIZE)
   * @return Enum enum
   */
  template < typename Enum >
  Enum AnnotationToEnum(const char * annotation,
                        const std::array< const char *, static_cast< size_t >(Enum::__SIZE) > & enumAnnotations,
                        const Enum & enumDefault = Enum::__SIZE)
  {
    for (size_t i = 0; i < static_cast< size_t >(Enum::__SIZE); i++)
      if (strcmp(annotation, enumAnnotations[i]) == 0) return static_cast< Enum >(i);

    return enumDefault;
  }

  /**
   * Convert an enum to its annotation.
   * @param const Enum & e
   * @param const std::array<AType, static_cast<size_t>(Enum::__SIZE)> & enumAnnotations
   * @return AType
   */
  template < typename Enum, typename AType >
  AType EnumToAnnotation(const Enum & e,
                         const std::array< AType, static_cast< size_t >(Enum::__SIZE) > & enumAnnotations)
  {
    if (static_cast< size_t >(Enum::__SIZE) <= static_cast< size_t >(e))
      {
        return AType();
      }

    return enumAnnotations[static_cast<size_t>(e)];
  }

  /**
   * Convert an enum to its annotation.
   * @param const Enum & e
   * @param const std::array<const char *, static_cast<size_t>(Enum::__SIZE)> & enumAnnotations
   * @return const char *
   */
  template < typename Enum >
  const char * EnumToAnnotation(const Enum & e,
                                const std::array< const char *, static_cast< size_t >(Enum::__SIZE) > & enumAnnotations)
  {
    if (static_cast<size_t>(Enum::__SIZE) <= static_cast<size_t>(e))
      {
        return NULL;
      }

    return enumAnnotations[static_cast<size_t>(e)];
  }
};

#endif // COPASI_CCoreEnum
