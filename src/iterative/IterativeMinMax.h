// implementation: Alin Stroe
// mail to: afstroe@gmail.com
// linkedin: https://www.linkedin.com/in/alinstroe/
// purpose: iterative min/max calculation
// Copyright © 2020 Alin Stroe, all rights reserved

#ifndef __ITERATIVE_MIN_MAX_H__
#define __ITERATIVE_MIN_MAX_H__

#include <xmemory>

/*! \defgroup iterative Non-smart iterative methods - for benchmarks */
namespace iterative
{
  /*!
  * \brief Iterative algorithm to look for the smallest element of a std::vector
  * \tparam Type - the type of the elements inside the vector
  * \tparam Container - the vector type
  *
  * \param container - the vector for which we require the minimum
  *
  * \return the smallest element inside the vector
  * \ingroup iterative
  */
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

  /*!
  * \brief Iterative algorithm to look for the largest element of a std::vector
  * \tparam Type - the type of the elements inside the vector
  * \tparam Container - the vector type
  *
  * \param container - the vector for which we require the maximum
  *
  * \return the largest element inside the vector
  * \ingroup iterative
  */
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