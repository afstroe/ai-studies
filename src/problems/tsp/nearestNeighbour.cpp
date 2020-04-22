#include "nearestNeighbour.h"

void problems::tsp::nearestNeighbour(const Cities& cities, size_t startCity, TourArray& tour, double& tourDistance)
{
  std::vector<bool> visited(cities.size());
  visited[startCity] = true;
  tourDistance = 0;

  tour.resize(cities.size());
  tour[0] = startCity;

  const auto sz = cities.size();

  FOR(i, sz - 1)
  {
    const auto lastVisited = tour[i];
    double minimumDistance = std::numeric_limits<double>::max();

    auto nextIndex = i + 1;
    auto& currentCityInTour = tour[nextIndex];

    // find the closest to our last visited city
    FOR(j, sz)
    {
      double currentDistance = 0;
      if (!visited[j] && (currentDistance = distance(cities[lastVisited], cities[j])) < minimumDistance)
      {
        currentCityInTour = j;
        minimumDistance = currentDistance;
      }
    }
    visited[currentCityInTour] = true;
    tourDistance += minimumDistance;
  }

  tourDistance += distance(cities[tour[0]], cities[*tour.rbegin()]);
}

void problems::tsp::reverseSegment(TourArray& tour, size_t startIndex, size_t endIndex)
{
  const auto s = tour.size();

  // account for the fact that tour is cyclic
  auto halfIntervalSize = ((s + endIndex - startIndex + 1) % s) / 2;

  int left = startIndex;
  int right = endIndex;
  
  FOR(i, halfIntervalSize)
  {
    std::swap(tour[left], tour[right]);
    left = ++left % s;
    right = (s + right - 1) % s;
  }
}
