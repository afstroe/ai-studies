#include "../random_generators/vectorGenerator.h"

#include "hillClimbing.h"

double stochastic::unitTest::climbHill()
{
  static const size_t oneMaxSize = 1000;

  auto bitstring = randomGenerators::generateRandomVector<int, std::vector, short>(oneMaxSize, 0, 1, randomGenerators::Distribution::UNIFORM);
  auto costCalculator = [](const std::vector<short>& bitstring) -> size_t
  {
    return std::count_if(bitstring.begin(), bitstring.end(), [](int i) { return i != 0; });    
  };

  auto costEvaluator = [&costCalculator](const std::vector<short>& candidate, const std::vector<short>& currentSolution)
  {
    return costCalculator(candidate) >= costCalculator(currentSolution);
  };

  auto neighbourGenerator = [](std::vector<short>& bitstring)
  {
    auto pos = randomGenerators::generateUniformDistributedRandomNumber<int>(0, static_cast<int>(bitstring.size() - 1));
    bitstring[pos] = 1;
  };

  auto ic = costCalculator(bitstring);

  auto solution = stochastic::hillClimbing(5000, bitstring, neighbourGenerator, costEvaluator);
  
  auto ac = costCalculator(solution);

  return 0.0;

}
