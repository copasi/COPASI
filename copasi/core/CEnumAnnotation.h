// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CEnumAnnotation
#define COPASI_CEnumAnnotation

#include <array>
#include <vector>
#include <map>

template < class Type, class Enum > class CEnumAnnotation
  : public std::array< Type, static_cast< size_t >(Enum::__SIZE) >
{
public:
  /**
   * typedef for the base class
   */
  typedef std::array< Type, static_cast< size_t >(Enum::__SIZE) > base;

  /**
   * Default constructor
   */
  CEnumAnnotation():
    base(),
    mMap()
  {
    base::fill(Type());
  }

  /**
   * Disable the copy constructor
   */
  CEnumAnnotation(const CEnumAnnotation & src):
    base(src),
    mMap(src.mMap)
  {}

public:
  /**
   * Specific constructor from the base class
   * @param const base & src
   */
  CEnumAnnotation(typename std::enable_if < !(std::is_same< Type, const char * >::value || std::is_const< Type >::value), const base & >::type src):
    base(src),
    mMap()
  {
    for (size_t i = 0; i < static_cast< size_t >(Enum::__SIZE); ++i)
      {
        mMap[base::at(i)] = static_cast< Enum >(i);
      }
  }

  /**
   * Operator []
   * @param Enum e
   * @return const Type & annotation
   */
  typename base::const_reference operator [](Enum e) const
  {
    return base::at(static_cast< size_t >(e));
  }

  /**
   * Operator []
   * @param size_t i
   * @return const Type & annotation
   */
  typename base::const_reference operator [](size_t i) const
  {
    return base::at(i);
  }

  /**
   * Conversion from annotation to enum
   * @param const Type & annotation
   * @param Enum enumDefault (default: Enum::__SIZE)
   */
  Enum toEnum(const Type & annotation, Enum enumDefault = Enum::__SIZE) const
  {
    typename std::map< Type, Enum >::const_iterator Found = mMap.find(annotation);

    if (Found != mMap.end())
      {
        return Found->second;
      }

    return enumDefault;
  }

  /**
   * Conversion from annotation to enum
   * @param const char * pAnnotation
   * @param Enum enumDefault (default: Enum::__SIZE)
   */
  Enum toEnum(const char * pAnnotation, Enum enumDefault = Enum::__SIZE) const
  {
    if (pAnnotation == NULL)
      return enumDefault;

    return toEnum(Type(pAnnotation), enumDefault);
  }

  std::vector< Type > annotations() const
  {
    std::vector< Type > Annotations;

    for (const std::pair< Type, Enum > & a : mMap)
      Annotations.push_back(a.first);

    return Annotations;
  }

private:
  std::map< Type, Enum > mMap;
};

#endif // COPASI_CEnumAnnotation
