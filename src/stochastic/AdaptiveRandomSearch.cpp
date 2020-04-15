#include "../statistics/clock.h"
#include "../random_generators/vectorGenerator.h"
#include "../utility/Defines.h"
#include "AdaptiveRandomSearch.h"

double stochastic::unitTest::adaptiveRandomSearchMin()
{
  auto& d = randomGenerators::DefaultRandomEngine::get();

  auto result = 0.0;

  result = stochastic::adaptiveRandomSearch(
    BENCHMARK_ITERATIONS,
    BENCHMARK_PROBLEM_SIZE,
    stochastic::SearchSpace2D<double>(-5, 5),
    [](const std::vector<double>& xi) {                                   // function to evaluate 
      auto sum = 0.0;
      for (int i = 0; i < xi.size(); ++i)
      {
        sum += (xi[i] * xi[i]);
      }

      return sum;
    },
    stochastic::randomGeneration2D<double, stochastic::SearchSpace2D>,
    [](double oldOptimal, double valueToCheck) {                          // cost comparator function
      return valueToCheck < oldOptimal;
    },
    0.05,
    1.3,
    3.0,
    10,
    30
  );

  return result;
}
