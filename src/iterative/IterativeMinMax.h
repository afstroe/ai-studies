// implementation: Alin Stroe
// mail to: afstroe@gmail.com
// linkedin: https://www.linkedin.com/in/alinstroe/
// purpose: iterative min/max calculation
// Copyright © 2020 Alin Stroe, all rights reserved

#ifndef __ITERATIVE_MIN_MAX_H__
#define __ITERATIVE_MIN_MAX_H__

#include <xmemory>

namespace iterative
{
  // iteratively looks for the min element in a std::vector
  template <class Type, template <class, class> class Container>
  Type min(const Container<Type, std::allocator<Type>>& container)
  {
    auto min = container[0];
    for (auto& element : container)
    {
      min = element < min ? element : min;
    }

    return min;
  }

  // iteratively looks for the max element in the std::vector
  template <class Type, template <class, class> class Container>
  Type max(const Container<Type, std::allocator<Type>>& container)
  {
    auto max = container[0];
    for (auto& element : container)
    {
      max = element > max ? element : max;
    }

    return max;
  }

}

#endif