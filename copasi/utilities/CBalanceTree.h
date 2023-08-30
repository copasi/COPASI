// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <vector>
#include "copasi/utilities/CFunctor.h"

template < class CType >
struct BalanceTree
{
  typedef CFunctor< CType, const CType &, const CType & > join_functor;
  typedef CType(*join_method)(const CType &, const CType &);

  static CType create(const std::vector< CType > nodes, join_method pJoinMethod)
  {
    std::vector< CType > Balanced {nodes};

    while (Balanced.size() > 1)
      {
        std::vector< CType > Tmp;

        typename std::vector< CType >::const_iterator it = Balanced.begin();
        typename std::vector< CType >::const_iterator end = Balanced.end();
        bool first = true;

        for (; it != end; ++it)
          {
            if (first)
              {
                first = false;

                if (Balanced.size() % 2)
                  {
                    Tmp.push_back(*it);
                    continue;
                  }
              }

            const CType & First = *it;
            const CType & Second = *++it;

            Tmp.emplace_back((*pJoinMethod)(First, Second));
          }

        Balanced = Tmp;
      }

    return Balanced[0];
  }

  static CType create(const std::vector< CType > nodes, join_functor * pJoinFunctor)
  {
    std::vector< CType > Balanced {nodes};

    while (Balanced.size() > 1)
      {
        std::vector< CType > Tmp;

        typename std::vector< CType >::const_iterator it = Balanced.begin();
        typename std::vector< CType >::const_iterator end = Balanced.end();
        bool first = true;

        for (; it != end; ++it)
          {
            if (first)
              {
                first = false;

                if (Balanced.size() % 2)
                  {
                    Tmp.push_back(*it);
                    continue;
                  }
              }

            const CType & First = *it;
            const CType & Second = *++it;

            Tmp.emplace_back(pJoinFunctor->operator()(First, Second));
          }

        Balanced = Tmp;
      }

    return Balanced[0];
  }
};
