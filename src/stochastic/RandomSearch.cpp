#include "RandomSearch.h"
#include "../statistics/clock.h"

void stochastic::randomSearchTest()
{
  double randomSearchOptimal = -3;

  for (int ite = 0; ite < 10; ++ite)
  {
    statistics::clock
    (
      [&randomSearchOptimal]() {
        randomSearchOptimal = stochastic::randomSearch(
          std::numeric_limits<double>::max(),                                   // initial optimal                          
          3,                                                                    // problem size
          20,                                                                   // iterations
          stochastic::SearchSpace2D<double>(-5, 5),                             // search space
          [](const std::vector<double>& xi) {                                   // function to evaluate 
            auto sum = 0.0;
            for (int i = 0; i < xi.size(); ++i)
            {
              sum += (xi[i] * xi[i]);
            }

            return sum;
          },
          stochastic::randomGeneration2D<double, stochastic::SearchSpace2D>,    // random samples generator
          [](double oldOptimal, double valueToCheck) {                          // cost comparator function
            return valueToCheck < oldOptimal;
          }
        );
      },
      "Random search time"
    );

    double iterativeOptimal = std::numeric_limits<double>::max();
    statistics::clock
    (
      [&iterativeOptimal]() {
        for (double x2 = -5; x2 < 5; x2 += 0.1)
        {
          for (double x1 = -5; x1 < 5; x1 += 0.1)
          {
            for (double x0 = -5; x0 < 5; x0 += 0.1)
            {
              double value = [x0, x1, x2]()
              {
                return x0 * x0 + x1 * x1 + x2 * x2;
              }();
              if ([value, iterativeOptimal]() {return value < iterativeOptimal; }())
              {
                iterativeOptimal = value;
              }
            }
          }
        }
      },
      "Iterative solution time"
    );


    std::cout << "random search optimal is: " << randomSearchOptimal << std::endl;
    std::cout << "iterative optimal is: " << iterativeOptimal << std::endl;
    std::cout << std::endl;
  }
}