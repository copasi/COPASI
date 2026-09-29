// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "copasi/core/CBidirectionalMap.h"

// Custom type trait to identify valid string types
template < typename T >
concept IsStringOrDerived =
  std::same_as< std::decay_t< T >, std::string > || std::is_base_of_v< std::string, std::decay_t< T > >;
// Custom type trait to identify valid string types

template < typename _Map >
class CEnumAnnotation : private _Map
{
public:
  using EnumType = _Map::KeyType;
  using AnnotationType = _Map::ValueType;
  using AnnotationTypeReturn = std::conditional_t< std::is_same_v< AnnotationType, std::string_view >, std::string, const AnnotationType &>;

  constexpr static size_t Size = _Map::Size;

  constexpr CEnumAnnotation(const _Map & map, EnumType enumDefault)
    : _Map(map)
    , mEnumDefault(enumDefault)
  {
    isDefaultValid(this->keys(), mEnumDefault);
  }

  // Accepts the unpacked Nodes and constructs the flat arrays smoothly
  template < typename... Nodes >
  constexpr CEnumAnnotation(EnumType enumDefault, Nodes &&... nodes)
    : _Map({std::forward< Nodes >(nodes)...})
    , mEnumDefault(enumDefault)
  {
    isDefaultValid(this->keys(), mEnumDefault);
  }

  template < size_t N >
  constexpr CEnumAnnotation< CBidirectionalMap< EnumType, AnnotationType, N > > subset(EnumType enumDefault, const std::array< EnumType, N > keys) const
  {
    // Instantiates the sub-annotation using the new safely constructed sub-map
    return CEnumAnnotation< CBidirectionalMap< EnumType, AnnotationType, N > >(
        _Map::subset(keys),
        enumDefault
    );
  }

  constexpr size_t size() const
  {
    return Size;
  }

  /**
   * Operator []
   * @param EnumType e
   * @return const AnnotationType & annotation
   */
  AnnotationTypeReturn operator[](EnumType e) const
  {
    if (!this->containsKey(e))
      e = mEnumDefault;

    if constexpr (std::is_same_v< AnnotationType, std::string_view >)
      {
        return std::string(*this->findByKey(e));
      }
    else
      {
        return *this->findByKey(e);
      }
  }

  /**
   * Operator []
   * @param std::int32_t e
   * @return const AnnotationType & annotation
   */
  AnnotationTypeReturn operator[](std::int32_t e) const
  {
    return operator[](static_cast< EnumType >(e));
  }

  EnumType toEnum(EnumType e) const
  {
    if (this->containsKey(e))
      return e;

    return mEnumDefault;
  }

  EnumType toEnum(std::int32_t e) const
  {
    return toEnum(static_cast< EnumType >(e));
  }

  /**
   * Conversion from annotation to enum
   * @param const AnnotationType & annotation
   */
  EnumType toEnum(const AnnotationType & annotation) const
  {
    return toEnum(annotation, mEnumDefault);
  }

  /**
   * Conversion from annotation to enum
   * @param const AnnotationType & annotation
   * @param EnumType enumDefault
   */
  EnumType toEnum(const AnnotationType & annotation, EnumType enumDefault) const
  {
    const EnumType * pEnum = this->findByValue(annotation);

    if (pEnum != nullptr)
      return *pEnum;

    if (this->containsKey(enumDefault))
      return enumDefault;

    return mEnumDefault;
  }

#ifndef SWIG
  /**
   * Conversion from annotation to enum
   * @param const char * pAnnotation
   */
  EnumType toEnum(const char * pAnnotation) const
    requires IsStringOrDerived< AnnotationType >
  {
    return toEnum(AnnotationType(pAnnotation), mEnumDefault);
  }

  /**
   * Conversion from annotation to enum
   * @param const char * pAnnotation
   * @param EnumType enumDefault
   */
  EnumType toEnum(const char * pAnnotation, EnumType enumDefault) const
    requires IsStringOrDerived< AnnotationType >
  {
    return toEnum(AnnotationType(pAnnotation), enumDefault);
  }
#endif // SWIG

  std::vector< AnnotationTypeReturn > annotations() const
  {
    std::vector< AnnotationTypeReturn > Annotations;
    Annotations.reserve(Size);

    for (const AnnotationType & a: this->values())
      if constexpr (std::is_same_v< AnnotationType, std::string_view >)
        Annotations.emplace_back(std::string(a));
      else
        Annotations.emplace_back(a);

    return Annotations;
  }

  template < typename Filter >
  std::vector< AnnotationTypeReturn > annotations(const Filter & filter) const
  {
    std::vector< AnnotationTypeReturn > Annotations;
    Annotations.reserve(filter.size());

    for (const AnnotationType & a: this->values())
      if (_Map::contains(filter, toEnum(a)))
        {
          if constexpr (std::is_same_v< AnnotationType, std::string_view >)
            Annotations.emplace_back(std::string(a));
          else
            Annotations.emplace_back(a);
        }

    return Annotations;
  }

private:
  template < typename Keys >
  constexpr bool isDefaultValid(const Keys & keys, EnumType enumDefault)
  {
    for (const auto & key: keys)
      if (key == enumDefault)
        return true;

    throw "CEnumAnnotation: Invalid Default";

    return false;
  }

  const EnumType mEnumDefault;
};

#ifndef SWIG
// Custom deduction guide based on the lightweight MapNode aggregate type
template < typename EnumType,
           typename... Nodes,
           typename K = std::common_type_t< typename std::decay_t< Nodes >::KeyType... >,
           typename V = std::common_type_t< typename std::decay_t< Nodes >::ValueType... > >
CEnumAnnotation(EnumType, Nodes...) -> CEnumAnnotation< CBidirectionalMap< K, V, sizeof...(Nodes) > >;
#endif // SWIG
