#include <tchar.h>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>

#include "stochastic/RandomSearch.h"
#include "stochastic/AdaptiveRandomSearch.h"
#include "iterative/IterativeMinMax.h"
#include "random_generators/vectorGenerator.h"
#include "statistics/clock.h"
#include "statistics/benchmark.h"
#include "stochastic/hillClimbing.h"
#include "problems/tsp/nearestNeighbour.h"
#include "problems/tsp/twoOpt.h"

int main(int argc, TCHAR** a)
{
  randomGenerators::DefaultRandomEngine::get();

  // stochastic::unitTest::climbHill();

  statistics::Benchmark benchmark;
  //benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "RandomSearch", false, stochastic::unitTest::randomSearchMin));
  //benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "AdaptiveRandomSearch", false, stochastic::unitTest::adaptiveRandomSearchMin));
  //benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "Iterative", true, iterative::unitTest::iterativeMin));
  
  
  //benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "hillClimb", true, stochastic::unitTest::climbHill));  

  double tourDistance = 0;
  double minTourDistance = std::numeric_limits<double>::max();
  problems::tsp::TourArray tour;
  problems::tsp::TourArray bestTour;
  int bestTourIndex = 0;

  FOR(i, problems::tsp::Berlin52.size())
  {    
    problems::tsp::nearestNeighbour(problems::tsp::Berlin52, i, tour, tourDistance);
    if (tourDistance < minTourDistance)
    {
      minTourDistance = tourDistance;
      bestTour = tour;
      bestTourIndex = i;
    }
  }

  problems::tsp::twoOptMove(problems::tsp::Berlin52, bestTour);

  for (auto t : bestTour)
  {
    std::cout << problems::tsp::Berlin52[t].x << std::endl;
  }
  std::cout << std::endl;
  for (auto t : bestTour)
  {
    std::cout << problems::tsp::Berlin52[t].y << std::endl;
  }
  std::cout << std::endl;

  auto d = problems::tsp::tourLength(problems::tsp::Berlin52, bestTour);

  benchmark.printResults();

  return 0;
}
