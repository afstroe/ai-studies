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

int main(int argc, TCHAR** a)
{
  randomGenerators::DefaultRandomEngine::get();

  // stochastic::unitTest::climbHill();

  statistics::Benchmark benchmark;
  //benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "RandomSearch", false, stochastic::unitTest::randomSearchMin));
  //benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "AdaptiveRandomSearch", false, stochastic::unitTest::adaptiveRandomSearchMin));
  //benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "Iterative", true, iterative::unitTest::iterativeMin));
  benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "hillClimb", true, stochastic::unitTest::climbHill));

  benchmark.printResults();

  return 0;
}
