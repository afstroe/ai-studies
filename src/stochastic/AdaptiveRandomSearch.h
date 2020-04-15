#ifndef __ADAPTIVE_RANDOM_SEARCH_H__
#define __ADAPTIVE_RANDOM_SEARCH_H__

#include <utility>

#include "../utility/Defines.h"

#include "RandomSearch.h"


namespace stochastic {
  
  /*!
    * \brief Takes a new step around the current position.
    * \tparam Type - the data type used by the algorithm
    * \tparam Parameters - the position type
    * \tparam SearchSpace - the search space
    *
    * \param[in] step - the step to take
    * \param[in] current - the current position
    * \param[in] searchSpace - the search space
    * \param[out] out - the new position
    * \ingroup stochastic
    */
  template <typename Type, TEMPLATE_TYPE_STD_VECTOR(Parameters), template<class> class SearchSpace>
  void takeStep(Type step, const STD_VECTOR(Type, Parameters)& current, const SearchSpace<Type>& searchSpace, STD_VECTOR(Type, Parameters)& out)
  {
    // will get a new position taking a random step ( rstep in (-step + current[d], step + current[d]) ) in each dimension.

    // cache it baby
    const auto l = searchSpace.left();
    const auto r = searchSpace.right();

    // compute the new position.
    for (auto& c : current)
    {
      // take care not to overflow the search space
      const auto left = std::max(c - step, l);
      const auto right = std::min(c + step, r);

      // push back a random position component
      auto number = randomGenerators::generateUniformDistributedRandomNumber(left, right);
      out.push_back(number);
    }
  }


  /*!
    * \brief Computes the steps needed by the algorithm.    
    * \tparam Type - the data type used by the algorithm
    * \tparam Parameters - the type of the position
    * \tparam SearchSpace - the search space type
    * \tparam ObjectiveFunctionType - the type of the cost function
    *
    * \param[in] current - the current position
    * \param[in] objectiveFunction - pointer to the cost function
    * \param[in] searchSpace - the search space
    * \param[in] stepSize - the step size
    * \param[in] bigStepSize - the large step size
    * \param[out] stepParameters - the position as per step
    * \param[out] bigStepParameters - the position as per big step
    * \param[out] stepCost - the cost of the step position
    * \param[out] bigStepCost - the cost of the big step position
    *
    * \ingroup stochastic
    */
  template <typename Type, template <class, class> class Parameters, template <class> class SearchSpace, class ObjectiveFunctionType>
  void computeSteps(const STD_VECTOR(Type, Parameters)& current, ObjectiveFunctionType objectiveFunction, const SearchSpace<Type>& searchSpace, Type stepSize, Type bigStepSize,
                    STD_VECTOR(Type, Parameters)& stepParameters, STD_VECTOR(Type, Parameters)& bigStepParameters,
                    Type& stepCost, Type& bigStepCost)
  {
    // each iteration we'll trial two steps: one with a small step size and one with a big step size.
    takeStep(stepSize, current, searchSpace, stepParameters);
    takeStep(bigStepSize, current, searchSpace, bigStepParameters);

    stepCost = objectiveFunction(stepParameters);
    bigStepCost = objectiveFunction(bigStepParameters);
  }


  /*!
    * \brief Computes the large step size as per algorithm    
    * \tparam Type - the data type used by the algorithm
    *
    * \param[in] iteration - the number of the iteration
    * \param[in] crtStepSize - the current step size
    * \param[in] smallStepFactor - the small big step factor
    * \param[in] largeStepFactor - the large big step factor
    * \param[in] iterationFactor - the number after which the function will generate a big large step
    *
    * \return the large step size
    * \ingroup stochastic
    */
  template <typename Type>
  Type computeLargeStepSize(size_t iteration, Type crtStepSize, Type smallStepFactor, Type largeStepFactor, size_t iterationFactor)
  {
    if (iteration > 0 && iteration % iterationFactor)
    {
      return crtStepSize * largeStepFactor;
    }
    else
    {
      return crtStepSize * smallStepFactor;
    }
  }


  /*!
    * \brief The adaptive random search algorithm
    * Algorithm: <br>
    * - continually approximate the step required to reach the global optimum in the search space;
    * - achieved by trialling and adopting smaller or bigger step sizes only if they result in an improvement in the search performance;
    * - trial a larger step each iteration and adopt the larger step if performance improves;
    *   - very large steps are trialled in the same manner but with a much lower frequency;
    *   - the strategy of preferring large moves is intended to escape local optima;
    *   - if no improvement is made for a longer period smaller step sizes will be considered.
    *
    * \tparam Type - the data type used by the algorithm
    * \tparam SearchSpace - the search space
    * \tparam ObjectiveFunctionType - the type of the cost function
    * \tparam RandomGenerationFunction - the type of the random generation function
    * \tparam CostComparatorFunction - the cost comparator function 
    *
    * \param[in] iterations - the number of iterations the algorithm will use to reach the solution
    * \param[in] problemSize - the input size
    * \param[in] searchSpace - the search space
    * \param[in] objectiveFunction - pointer to the cost function
    * \param[in] randomFunction - pointer to the random generator
    * \param[in] costComparator - pointer to the cost comparator
    * \param[in] ssInitFactor - the initial step factor
    * \param[in] ssSmallFactor - the small big step factor
    * \param[in] ssLargeFactor - the large big step factor
    * \param[in] ssIterationFactor - the number of iterations after which a large big step will be trialled
    * \param[in] noChangeMax - the number after which a smaller step will be trialled
    *
    * \return the desired optima
    * \ingroup stochastic
    */
  template <typename Type, template <class> class SearchSpace, class ObjectiveFunctionType, class RandomGenerationFunction, class CostComparatorFunction>
  Type adaptiveRandomSearch(size_t iterations, size_t problemSize, const SearchSpace<Type>& searchSpace, ObjectiveFunctionType objectiveFunction, RandomGenerationFunction randomFunction, CostComparatorFunction costComparator,
                            Type ssInitFactor, Type ssSmallFactor, Type ssLargeFactor, size_t ssIterationFactor, size_t noChangeMax)
  {
    // the counter of no changes
    auto noChangeCounter = 0;

    // initial step here
    auto stepSize = searchSpace.length() * ssInitFactor;

    auto position = randomGenerators::generateRandomVector<Type, std::vector>(problemSize, searchSpace.left(), searchSpace.right(), randomGenerators::Distribution::UNIFORM);
    auto positionCost = objectiveFunction(position);

    auto csCost = positionCost;
    auto ssCost = static_cast<Type>(0);
    auto bssCost = static_cast<Type>(0);
    std::vector<Type> stepParameters; stepParameters.reserve(problemSize);
    std::vector<Type> bigStepParameters; bigStepParameters.reserve(problemSize);


    // do the iterations
    FOR(i, iterations)
    {
      stepParameters.clear();
      bigStepParameters.clear();

      auto bigStepSize = computeLargeStepSize(i, stepSize, ssSmallFactor, ssLargeFactor, ssIterationFactor);

      computeSteps(position, objectiveFunction,  searchSpace, stepSize, bigStepSize, stepParameters, bigStepParameters, ssCost, bssCost);            

      if (costComparator(csCost, ssCost))
      {
        csCost = ssCost;
        position = stepParameters;
        noChangeCounter = 0;
      }
      else if (costComparator(csCost, bssCost))
      {
        stepSize = bigStepSize;
        csCost = bssCost;
        position = bigStepParameters;
        noChangeCounter = 0;
      }
      else
      {
        ++noChangeCounter;
        if (noChangeCounter > noChangeMax)
        {
          noChangeCounter = 0;
          stepSize = stepSize / ssSmallFactor;
        }
      }      
    }

    return csCost;
  }

  namespace unitTest {
    void adaptiveRandomSearch();
  }

}// namespace stochastic {

#endif // !__ADAPTIVE_RANDOM_SEARCH_H__

