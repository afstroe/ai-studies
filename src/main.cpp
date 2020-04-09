#include <tchar.h>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>

#include "stochastic/RandomSearch.h"
#include "iterative/IterativeMinMax.h"
#include "random_generators/vectorGenerator.h"
#include "statistics/clock.h"

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
  stochastic::randomSearchTest();

  return 0;
}
