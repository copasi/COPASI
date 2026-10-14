// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <random>

template < class IntType = int >
class poisson_distribution
{
private:
  std::poisson_distribution< IntType > mDistribution;

public:
  using result_type = IntType;
  using param_type = std::poisson_distribution< IntType >::param_type;

  poisson_distribution(double mean = 1.0)
    : mDistribution(mean)
  {}

  poisson_distribution(const param_type & params)
    : mDistribution(params)
  {}

  template < class Generator >
  result_type operator()(Generator & g)
  {
    if (mDistribution.mean() > 0.0)
      {
        return mDistribution(g);
      }

    return 0;
  }

  template < class Generator >
  result_type operator()(Generator & g, const param_type & params)
  {
    if (params.mean() > 0.0)
      {
        return mDistribution(g, params);
      }

    return 0;
  }
};
