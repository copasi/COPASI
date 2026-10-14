// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <random>

template < class IntType = int >
class poisson_distribution
{
public:
  using result_type = IntType;

  class param_type
  {
  public:
    param_type()
      : mMean(1.0)
    {}

    param_type(double mean)
      : mMean(mean)
    {}

    double mean() const
    {
      return mMean;
    }

    friend bool
    operator==(const param_type & lhs, const param_type & rhs)
    {
      return lhs.mMean == rhs.mMean;
    }

  private:
    double mMean;
  };

  poisson_distribution()
    : mDistribution()
    , mParams()
  {}

  poisson_distribution(const param_type & params)
    : mDistribution(1.0)
    , mParams(params)
  {
    if (mParams.mean() > 0.0)
      mDistribution.param(typename std::poisson_distribution< result_type >::param_type(mParams.mean()));
  }

  template < class Generator >
  result_type operator()(Generator & g)
  {
    if (mParams.mean() > 0.0)
      return mDistribution(g);

    return 0;
  }

  template < class Generator >
  result_type operator()(Generator & g, const param_type & params)
  {
    if (params.mean() > 0.0)
      return mDistribution(g, typename std::poisson_distribution< result_type >::param_type(params.mean()));

    return 0;
  }

private:
  std::poisson_distribution< result_type > mDistribution;
  param_type mParams;
};
