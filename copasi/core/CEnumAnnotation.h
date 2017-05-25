// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CEnumAnnotation
#define COPASI_CEnumAnnotation

#include <array>

template < class Type, class Enum > class CEnumAnnotation
  : public std::array< Type, static_cast< size_t >(Enum::__SIZE) >
{
public:
  /**
   * typedef for the base class
   */
  typedef std::array< Type, static_cast< size_t >(Enum::__SIZE) > base;

  /**
   * Disable the default constructor
   */
  CEnumAnnotation() = delete;

  /**
   * Disable the copy constructor
   */
  CEnumAnnotation(const CEnumAnnotation &) = delete;

  /**
   * Disable the assignment operator
   */
  CEnumAnnotation & operator = (const CEnumAnnotation &) = delete;

  /**
   * Specific constructor from the base class
   * @param const base & src
   */
  CEnumAnnotation(typename std::enable_if < !(std::is_same< Type, const char * >::value || std::is_const< Type >::value), const base & >::type src):
    base(src)
  {}

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
    for (size_t i = 0; i < static_cast< size_t >(Enum::__SIZE); ++i)
      if (annotation == base::at(i))
        {
          return static_cast< Enum >(i);
        }

    return enumDefault;
  }
};

#endif // COPASI_CEnumAnnotation
