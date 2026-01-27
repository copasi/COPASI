// Copyright (C) 2023 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include <vector>
#include <functional>
#include <type_traits>

template < class CType >
struct BalanceTree
{
  static CType create(const std::vector< CType > & unbalanced, const std::function< CType(const CType &, const CType &) > && joinFunction)
  {
    if (unbalanced.empty())
      return std::is_pointer< CType >::value ? nullptr : CType();

    std::vector< CType > Balanced {unbalanced};

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

            Tmp.emplace_back(joinFunction(First, Second));
          }

        Balanced = Tmp;
      }

    return Balanced[0];
  }
};
