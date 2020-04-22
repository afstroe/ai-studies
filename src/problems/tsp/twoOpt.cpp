#include "twoOpt.h"

void problems::tsp::reverseSegment(TourArray& tour, size_t startIndex, size_t endIndex)
{
  const auto s = tour.size();

  // account for the fact that tour is cyclic
  auto halfIntervalSize = ((s + endIndex - startIndex + 1) % s) / 2;

  int left = static_cast<int>(startIndex);
  int right = static_cast<int>(endIndex);

  FOR(i, halfIntervalSize)
  {
    std::swap(tour[left], tour[right]);
    left = ++left % s;
    right = static_cast<int>((s + right - 1) % s);
  }
}

void problems::tsp::firstTwoOptMove(const Cities& cities, TourArray& tour)
{
  // we'll get munching at it until no more local optima is available
  auto locallyOptimal = false;

  while (!locallyOptimal)
  {
    locallyOptimal = true;
    
    const auto s = tour.size();
    for (auto i = 0; i < s - 1 && locallyOptimal/* leave enough room for j */; ++i)
    {
      const auto& x0 = cities[tour[i]];
      const auto& x1 = cities[tour[static_cast<size_t>(i) + 1]];

      const auto l = (i == 0) ? s - 1 : s;
      for (auto j = i + 2; j < l; ++j)
      {
        const auto& y0 = cities[tour[j]];
        const auto& y1 = cities[tour[(static_cast<size_t>(j) + 1) % s]];

        if (twoOptGain(x0, x1, y0, y1) > 0)
        {
          makeTwoOptMove(tour, i, j);
          locallyOptimal = false;
          break;
        }
      }
    }      
  }
}

void problems::tsp::twoOptMove(const Cities& cities, TourArray& tour)
{
  // we'll got munching at it until no more local optima is available
  auto locallyOptimal = false;

  while (!locallyOptimal)
  {
    locallyOptimal = true;

    struct BestGain
    {
      size_t i = 0;
      size_t j = 0;
      double gain = 0;
      void set(size_t i, size_t j, double gain)
      {
        this->i = i;
        this->j = j;
        this->gain = gain;
      }
    }bestGain;

    const auto s = tour.size();
    for (auto i = 0; i < s - 1/* leave enough room for j */; ++i)
    {
      const auto& x0 = cities[tour[i]];
      const auto& x1 = cities[tour[static_cast<size_t>(i) + 1]];

      const auto l = (i == 0) ? s - 1 : s;
      for (auto j = i + 2; j < l; ++j)
      {
        const auto& y0 = cities[tour[j]];
        const auto& y1 = cities[tour[(static_cast<size_t>(j) + 1) % s]];

        if (double gain = twoOptGain(x0, x1, y0, y1) > bestGain.gain)
        {
          bestGain.set(i, j, gain);          
          locallyOptimal = false;          
        }
      }
    }
    if (!locallyOptimal)
    {
      makeTwoOptMove(tour, bestGain.i, bestGain.j);
    }
  }
}
