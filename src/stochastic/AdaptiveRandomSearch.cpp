#include "../statistics/clock.h"
#include "../random_generators/vectorGenerator.h"
#include "../utility/Defines.h"
#include "AdaptiveRandomSearch.h"



void stochastic::unitTest::adaptiveRandomSearch()
{
  auto& d = randomGenerators::DefaultRandomEngine::get();

  auto result = 0.0;

  FOR(i, 100){
    auto t = statistics::clock(
      [&result]()
      {
        result = stochastic::adaptiveRandomSearch(
          10000,
          2,
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
            return valueToCheck > oldOptimal;
          },
          0.05,
          1.3,
          3.0,
          10,
          30
        );
      },
      "adaptiveRandomSearch"
    );
    std::cout << "Result is: " << result << std::endl;
  }
}
