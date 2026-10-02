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
#include <type_traits>
#include <memory>

#include "copasi/core/CBidirectionalMap.h"

// Custom type trait to identify valid string types
template < typename T >
concept IsStringOrDerived =
  std::same_as< std::decay_t< T >, std::string > || std::is_base_of_v< std::string, std::decay_t< T > >;
// Custom type trait to identify valid string types

template < typename _Map >
class CEnumAnnotationInstance : private _Map
{
public:
  using EnumType = _Map::KeyType;
  using AnnotationType = _Map::ValueType;
  using AnnotationTypeReturn = std::conditional_t< std::is_same_v< AnnotationType, std::string_view >, std::string, AnnotationType >;

  constexpr static size_t Size = _Map::Size;

  virtual ~CEnumAnnotationInstance() = default;

  constexpr CEnumAnnotationInstance(const _Map & map, EnumType enumDefault)
    : _Map(map)
    , mEnumDefault(enumDefault)
  {
    isDefaultValid(this->keys(), mEnumDefault);
  }

  // Accepts the unpacked Nodes and constructs the flat arrays smoothly
  template < typename... Nodes >
  constexpr CEnumAnnotationInstance(EnumType enumDefault, Nodes &&... nodes)
    : _Map({std::forward< Nodes >(nodes)...})
    , mEnumDefault(enumDefault)
  {
    isDefaultValid(this->keys(), mEnumDefault);
  }

  constexpr size_t size() const
  {
    return Size;
  }

  constexpr EnumType enumDefault() const
  {
    return mEnumDefault;
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

  EnumType toEnum(EnumType e) const
  {
    if (this->containsKey(e))
      return e;

    return mEnumDefault;
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

  std::vector< AnnotationType > values() const
  {
    return std::vector< AnnotationType >(this->_Map::values().begin(), this->_Map::values().end());
  }

private:
  template < typename Keys >
  constexpr static bool isDefaultValid(const Keys & keys, EnumType enumDefault)
  {
    for (const auto & key : keys)
      if (key == enumDefault)
        return true;

    throw "CEnumAnnotationInstance: Invalid Default";

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
CEnumAnnotationInstance(EnumType, Nodes...) -> CEnumAnnotationInstance< CBidirectionalMap< K, V, sizeof...(Nodes) > >;
#endif // SWIG

template < typename EnumType, typename AnnotationType >
class CEnumAnnotation
{
public:
  using AnnotationTypeReturn = std::conditional_t< std::is_same_v< AnnotationType, std::string_view >, std::string, AnnotationType >;

private:
  // 1. Define a constexpr Function Pointer VTable instead of a virtual class
  struct VTable
  {
    size_t (*size)(const void *) = nullptr;
    EnumType (*eDefault)(const void *) = nullptr;
    AnnotationTypeReturn (*at)(const void *, EnumType) = nullptr;
    EnumType (*toEnum)(const void *, EnumType) = nullptr;
    std::vector< AnnotationType > (*values)(const void *) = nullptr;
    EnumType (*toEnumAnnot)(const void *, const AnnotationType &, EnumType) = nullptr;
  };

  // 2. Compile-time generation of the VTable for a specific concrete type
  template < typename ConcreteType >
  static constexpr VTable make_vtable()
  {
    return VTable{
      .size = [](const void * ptr) {return static_cast< const ConcreteType * >(ptr)->size(); },
      .eDefault = [](const void * ptr) {return static_cast< const ConcreteType * >(ptr)->enumDefault(); },
      .at = [](const void * ptr, EnumType e) {return (*static_cast< const ConcreteType * >(ptr))[e]; },
      .toEnum = [](const void * ptr, EnumType e) {return static_cast< const ConcreteType * >(ptr)->toEnum(e); },
      .values = [](const void * ptr) {return static_cast< const ConcreteType * >(ptr)->values(); },
      .toEnumAnnot = [](const void * ptr, const AnnotationType & a, EnumType d) {return static_cast< const ConcreteType * >(ptr)->toEnum(a, d); }};
  }

  // Helper to hold a static vtable instance per type
  template < typename ConcreteType >
  static constexpr VTable vtable_instance = make_vtable< ConcreteType >();

public:
  // 3. Constexpr Constructor: Stores a reference to an external constexpr instance
  template < typename Instance >
  constexpr CEnumAnnotation(const Instance & annotation)
    : mSelf(&annotation)
    , mVtbl(&vtable_instance< Instance >)
  {}

  // 4. Uniform Public Interface utilizing the VTable
  size_t size() const
  {
    return mVtbl->size(mSelf);
  }

  EnumType enumDefault() const
  {
    return mVtbl->eDefault(mSelf);
  }

  AnnotationTypeReturn operator[](EnumType e) const
  {
    return mVtbl->at(mSelf, e);
  }

  AnnotationTypeReturn operator[](std::int32_t e) const
  {
    return mVtbl->at(mSelf, static_cast< EnumType >(e));
  }

  EnumType toEnum(EnumType e) const
  {
    return mVtbl->toEnum(mSelf, e);
  }

  EnumType toEnum(const AnnotationType & a) const
  {
    return mVtbl->toEnumAnnot(mSelf, a, enumDefault());
  }

  EnumType toEnum(const AnnotationType & a, EnumType d) const
  {
    return mVtbl->toEnumAnnot(mSelf, a, d);
  }

  std::vector< AnnotationType > values() const
  {
    return mVtbl->values(mSelf);
  }

  template < typename FilterArray >
  std::vector< AnnotationType > values(const FilterArray & filter) const
  {
    std::vector< AnnotationType > Values;
    Values.reserve(filter.size());

    for (const AnnotationType & a : mVtbl->values(mSelf))
      if (std::find(filter.begin(), filter.end(), toEnum(a)) != filter.end())
        Values.emplace_back(a);

    return Values;
  }

  std::vector< AnnotationTypeReturn > annotations() const
  {
    std::vector< AnnotationTypeReturn > Annotations;
    Annotations.reserve(size());

    for (const AnnotationType & a : values())
      if constexpr (std::is_same_v< AnnotationType, std::string_view >)
        Annotations.emplace_back(std::string(a));
      else
        Annotations.emplace_back(a);

    return Annotations;
  }

  template < typename FilterArray >
  std::vector< AnnotationTypeReturn > annotations(const FilterArray & filter) const
  {
    std::vector< AnnotationTypeReturn > Annotations;
    Annotations.reserve(filter.size());

    for (const AnnotationType & a : values(filter))
      if constexpr (std::is_same_v< AnnotationType, std::string_view >)
        Annotations.emplace_back(std::string(a));
      else
        Annotations.emplace_back(a);

    return Annotations;
  }

  template < size_t N >
  constexpr auto subset(EnumType def, const std::array< EnumType, N > & keys) const
  {
    return CEnumAnnotationSubset< EnumType, AnnotationType, N >(*this, def, keys);
  }

private:
  constexpr CEnumAnnotation()
    : mSelf(nullptr)
    , mVtbl(nullptr)
  {}

  const void * mSelf;
  const VTable * mVtbl;
};

template < typename EnumType, typename AnnotationType, size_t N >
class CEnumAnnotationSubset
{
public:
  using AnnotationTypeReturn = std::conditional_t< std::is_same_v< AnnotationType, std::string_view >, std::string, AnnotationType >;
  constexpr static size_t Size = N;

  constexpr CEnumAnnotationSubset(const CEnumAnnotation< EnumType, AnnotationType > & annotation, EnumType def, std::array< EnumType, N > subset)
    : mEnumAnnotation(annotation)
    , mEnumDefault(def)
    , mSubset(subset)
  {
    isDefaultValid(subset, def);
  }

  // Mirrors the interface expected by your static closures
  constexpr size_t size() const
  {
    return Size;
  }

  constexpr EnumType enumDefault() const
  {
    return mEnumDefault;
  }

  constexpr AnnotationTypeReturn operator[](EnumType e) const
  {
    // If the requested enum is part of our subset bounds, query the original map
    if (std::find(mSubset.begin(), mSubset.end(), e) != mSubset.end())
      {
        return mEnumAnnotation[e];
      }

    return mEnumAnnotation[mEnumDefault]; // Fallback to your subset default
  }

  EnumType toEnum(EnumType e) const
  {
    if (std::find(mSubset.begin(), mSubset.end(), e) != mSubset.end())
      return e;

    return mEnumDefault;
  }

  /**
   * Conversion from annotation to enum
   * @param const AnnotationType & annotation
   * @param EnumType enumDefault
   */
  EnumType toEnum(const AnnotationType & annotation, EnumType enumDefault) const
  {
    EnumType Enum = mEnumAnnotation.toEnum(annotation, enumDefault);

    // If the requested enum is part of our subset bounds, query the original map
    if (std::find(mSubset.begin(), mSubset.end(), Enum) != mSubset.end())
      {
        return Enum;
      }

    return enumDefault; // Fallback to your subset default
  }

  std::vector< AnnotationType > values() const
  {
    std::vector< AnnotationType > Values;
    Values.reserve(Size);

    for (const AnnotationType & a : mEnumAnnotation.values())
      if (std::find(mSubset.begin(), mSubset.end(), toEnum(a, mEnumDefault)) != mSubset.end())
        Values.emplace_back(a);

    return Values;
  }

private:
  template < typename Keys >
  constexpr static bool isDefaultValid(const Keys & keys, EnumType enumDefault)
  {
    for (const auto & key : keys)
      if (key == enumDefault)
        return true;

    throw "CEnumAnnotationInstance: Invalid Default";

    return false;
  }

  const CEnumAnnotation< EnumType, AnnotationType > & mEnumAnnotation;
  const EnumType mEnumDefault;
  std::array< EnumType, N > mSubset;
};
