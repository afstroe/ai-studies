#ifndef __ADAPTIVE_RANDOM_SEARCH_H__
#define __ADAPTIVE_RANDOM_SEARCH_H__

#include <utility>

#include "../utility/Defines.h"

#include "RandomSearch.h"


namespace stochastic {
  
  /*! 
    * \brief Complete solution for a objective / cost function.   
    *
    * \tparam Type - the data type of the solution
    * \ingroup stochastic
    */
  template <typename Type>
  class Solution
  {
    DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(Type, cost)

    DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(std::vector<Type>, parameters)

  public:
    //! default c-tor
    Solution()
    {
      cost() = 0;
    }

    /*!
      * \brief init c-tor
      * \param cost - the cost of the solution
      * \param parameters - the parameters used to compute the cost
      */
    Solution(Type cost, std::vector<Type>&& parameters)
    {
      _cost = cost;
      _parameters = std::move(parameters);
    }

    Solution(Solution&& rhs) noexcept
    {
      *this = std::move(rhs);
    }

    Solution& operator = (Solution&& rhs) noexcept
    {
      _cost = rhs._cost;
      _parameters = std::move(rhs._parameters);
      return *this;
    }
  };

  template <typename Type, TEMPLATE_TYPE_STD_VECTOR(Parameters), template<class> class SearchSpace>
  STD_VECTOR(Type, Parameters)& takeStep(Type step, const STD_VECTOR(Type, Parameters)& current, const SearchSpace<Type>& searchSpace)
  {
    static std::vector<Type> out;
    out.clear();

    // reserve the size of the output; will get a new position taking a random step ( rstep in (-step + current[d], step + current[d]) ) in each dimension.
    out.reserve(current.size());

    // compute the new position.
    for (auto& c : current)
    {
      // take care not to overflow the search space
      const auto left = std::max(c - step, searchSpace.left());
      const auto right = std::min(c + step, searchSpace.right());

      // push back a random position component
      auto number = randomGenerators::generateUniformDistributedRandomNumber(left, right);
      out.push_back(number);
    }

    return out;
  }

  template <typename Type, template <class, class> class Parameters, template <class> class SearchSpace, class ObjectiveFunctionType>
  std::pair<Solution<Type>, Solution<Type>> computeSteps(const STD_VECTOR(Type, Parameters)& current, ObjectiveFunctionType objectiveFunction, const SearchSpace<Type>& searchSpace, Type stepSize, Type bigStepSize)
  {
    // each iteration we'll trial two steps: one with a small step size and one with a big step size.
    static std::vector<Type> stepParameters;
    stepParameters.clear();
    stepParameters.reserve(current.size());

    static std::vector<Type> bigStepParameters;
    bigStepParameters.clear();
    bigStepParameters.reserve(current.size());

    stepParameters = takeStep(stepSize, current, searchSpace);
    bigStepParameters = takeStep(bigStepSize, current, searchSpace);

    auto stepCost = objectiveFunction(stepParameters);
    auto bigStepCost = objectiveFunction(bigStepParameters);

    return std::make_pair(Solution<Type>(stepCost, std::move(stepParameters)), Solution<Type>(bigStepCost, std::move(bigStepParameters)));
  }

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

  template <typename Type, template <class> class SearchSpace, class ObjectiveFunctionType, class RandomGenerationFunction, class CostComparatorFunction>
  Type adaptiveRandomSearch(size_t iterations, size_t problemSize, const SearchSpace<Type>& searchSpace, ObjectiveFunctionType objectiveFunction, RandomGenerationFunction randomFunction, CostComparatorFunction costComparator,
                            Type ssInitFactor, Type ssSmallFactor, Type ssLargeFactor, size_t ssIterationFactor, size_t noChangeMax)
  {
    // the counter of no changes
    auto noChangeCounter = 0;

    // initial step here
    auto stepSize = searchSpace.length() * ssInitFactor;

    auto initialPosition = randomGenerators::generateRandomVector<Type, std::vector>(problemSize, searchSpace.left(), searchSpace.right(), randomGenerators::Distribution::UNIFORM);
    auto initialPositionCost = objectiveFunction(initialPosition);

    Solution<Type> crtSolution(initialPositionCost, std::move(initialPosition));

    // do the iterations
    FOR(i, iterations)
    {
      auto bigStepSize = computeLargeStepSize(i, stepSize, ssSmallFactor, ssLargeFactor, ssIterationFactor);

      auto stepsSolutions = computeSteps(crtSolution.parameters(), objectiveFunction,  searchSpace, stepSize, bigStepSize);
      
      const auto csCost = crtSolution.cost();
      const auto ssCost = stepsSolutions.first.cost();
      const auto bssCost = stepsSolutions.second.cost();

      if (costComparator(csCost, ssCost))
      {
        crtSolution = std::move(stepsSolutions.first);
        noChangeCounter = 0;
      }
      else if (costComparator(csCost, bssCost))
      {
        stepSize = bigStepSize;
        crtSolution = std::move(stepsSolutions.second);
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

    return crtSolution.cost();
  }

  namespace unitTest {
    void adaptiveRandomSearch();
  }

}// namespace stochastic {

#endif // !__ADAPTIVE_RANDOM_SEARCH_H__

