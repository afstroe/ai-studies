#include "../utility/Defines.h"
#include "../stochastic/RandomSearch.h"

#include "IterativeMinMax.h"


double iterative::unitTest::iterativeMin()
{
  return iterative::optima(std::numeric_limits<double>::max(), BENCHMARK_PROBLEM_SIZE, stochastic::SearchSpace2D<double>(-5.0, 5.0),
    [](const std::vector<double>& xi) {
      auto sum = 0.0;
      for (int i = 0; i < xi.size(); ++i)
      {
        sum += (xi[i] * xi[i]);
      }

      return sum;
    },
    [](double oldOptimal, double valueToCheck) {
      return valueToCheck < oldOptimal;
    }
  );
}
