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

static double randomSolution(const std::vector<double>& problemSpace)
{
  std::random_device randomDevice;
  std::default_random_engine randomEngine(randomDevice());
  std::uniform_int_distribution<> ud(0, static_cast<int>(problemSpace.size() - 1));
  
  auto pos = ud(randomEngine);

  return problemSpace[pos];
}

int main(int argc, TCHAR** a)
{
  auto r = iterative::unitTest::iterativeMin();

  randomGenerators::DefaultRandomEngine::get();

  statistics::Benchmark benchmark;
  benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "RandomSearch", false, stochastic::unitTest::randomSearchMin));
  benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "AdaptiveRandomSearch", false, stochastic::unitTest::adaptiveRandomSearchMin));
  benchmark.addAlgorithm(statistics::Benchmark::AlgorithmStatistics::AlgorithmStatistics(100, "Iterative", true, iterative::unitTest::iterativeMin));

  benchmark.printResults();

  return 0;
}
