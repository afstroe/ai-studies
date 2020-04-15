// implementation: Alin Stroe
// mail to: afstroe@gmail.com
// linkedin: https://www.linkedin.com/in/alinstroe/
// purpose: iterative min/max calculation
// Copyright © 2020 Alin Stroe, all rights reserved

#ifndef __ITERATIVE_MIN_MAX_H__
#define __ITERATIVE_MIN_MAX_H__

#include <xmemory>
#include <functional>

#include "../utility/Defines.h"

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


  /*!
    * \brief Iteratively computes the optima for the given objective function    
    * \tparam Type - the data type used by the algorithm
    * \tparam SearchSpace - the search space type
    * \tparam ObjectiveFunction - the objective function type
    * \tparam CostEvalFunction - the cost function type
    *
    * \param initialOptima - initial value for the optima
    * \param problemSize - size of the parameters vector
    * \param searchSpace - the search space
    * \param objectiveFunction - the function we want to optimize
    * \param costEvalFunction - the function we use to evaluate the cost
    *
    * \return the optima
    * \ingroup iterative
    */
  template <typename Type, template <class> class SearchSpace, class ObjectiveFunction, class CostEvalFunction>
  Type optima(Type initialOptima, size_t problemSize, SearchSpace<Type> searchSpace, ObjectiveFunction objectiveFunction, CostEvalFunction costEvalFunction)
  {
    std::vector<Type> parameters(problemSize);
    auto result = initialOptima;
    
    std::function<void(int)> loop = [&](int index)
    {
      if (index == parameters.size() - 1)
      {
        for (auto i = searchSpace.left(); i <= searchSpace.right(); i += 0.01)
        {
          parameters[index] = i;
          auto instResult = objectiveFunction(parameters);
          if (costEvalFunction(result, instResult))
          {
            result = instResult;
          }
        }
      }
      else
      {
        for (auto i = searchSpace.left(); i <= searchSpace.right(); i += 0.01)
        {
          parameters[index] = i;
          loop(index + 1);
        }
      }
    };

    loop(0);

    return result;
  }

  namespace unitTest {
    double iterativeMin();
  }
}

#endif