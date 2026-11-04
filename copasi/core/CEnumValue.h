// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <memory>
#include <any>

#include "copasi/core/CEnumAnnotation.h"

// 1. The uniform, non-templated interface (The Wrapper)
class CEnumValue
{
private:
  // The internal abstract base concept
  struct Concept {
    virtual ~Concept() = default;

    virtual Concept & _assign(const std::int32_t &) = 0;
    virtual Concept & _assign(const std::string &) = 0;

    virtual std::int32_t _enum() = 0;
    virtual std::string _annotation() = 0;
  };

  // The templated concrete model that wraps any type T
  template < typename T >
  struct Model : Concept
  {
    using E = T::EnumType;
    using A = T::AnnotationType;

    T object;

    Model(const std::any & annotation)
      : object(T(annotation))
    {}

    Model(T obj)
      : object(std::move(obj))
    {}

    Concept & _assign(const std::int32_t & rhs) override
    {
      object = rhs;
      return *this;
    }

    Concept & _assign(const std::string & rhs) override
    {
      object = rhs;
      return *this;
    }

    std::int32_t _enum()
    {
      return static_cast< std::int32_t >(object);
    }

    std::string _annotation() override
    {
      return object.annotation();
    }
  };

  std::unique_ptr< Concept > self;

public:
  // Templated constructor accepts any type that has the concept required methods
  template < typename T >
  CEnumValue(T obj)
    : self(std::make_unique< Model< T > >(std::move(obj)))
  {}

  CEnumValue & operator=(std::int32_t rhs)
  {
    self->_assign(rhs);
    return *this;
  }

  CEnumValue & operator=(const std::string & rhs)
  {
    self->_assign(rhs);
    return *this;
  }

  CEnumValue & operator=(const char * rhs)
  {
    self->_assign(rhs);
    return *this;
  }

  operator std::int32_t()
  {
    return self->_enum();
  }

  std::string annotation()
  {
    return self->_annotation();
  }
};

template < typename Annotation >
class CEnumValueWithAnnotation
{
public:
  using EnumType = Annotation::EnumType;
  using AnnotationType = Annotation::AnnotationType;
  using AnnotationTypeReturn = Annotation::AnnotationTypeReturn;

  CEnumValueWithAnnotation() = delete;

  CEnumValueWithAnnotation(const Annotation & annotation)
    : mpAnnotation(&annotation)
    , mEnum(Annotation::Default)
  {}

  CEnumValueWithAnnotation & operator=(EnumType e)
  {
    mEnum = mpAnnotation->toEnum(e);
    return *this;
  }

  CEnumValueWithAnnotation & operator=(std::int32_t e)
  {
    mEnum = mpAnnotation->toEnum(e);
    return *this;
  }

  CEnumValueWithAnnotation & operator=(const AnnotationType & annotation)
  {
    mEnum = mpAnnotation->toEnum(annotation);
    return *this;
  }

  operator EnumType() const
  {
    return mEnum;
  }

  operator std::int32_t() const
  {
    return static_cast< std::int32_t >(mEnum);
  }

  AnnotationTypeReturn annotation() const
  {
    return mpAnnotation->operator[](mEnum);
  }

private:
  const Annotation * mpAnnotation;
  EnumType mEnum;
};

// Custom deduction guide
template < typename Annotation,
           typename A = typename std::decay_t< Annotation > >
CEnumValueWithAnnotation(Annotation) -> CEnumValueWithAnnotation< A >;
