#ifndef __TSP_NEAREST_NEIGHBOUR_H__
#define __TSP_NEAREST_NEIGHBOUR_H__

#include "../../utility/Defines.h"
#include "Defines.h"

namespace problems {
  namespace tsp {
    
    /*!
      * \brief Solves the Traveling Salesman Problem by using the nearest neighbour method            
      *
      * \param[in] cities - the cities in defining the problem
      * \param[in] startCity - the index of the first city
      * \param[out] tour - the computed tour
      * \param[out] tourDistance - the tour distance
      *
      * \ingroup tsp
      */
    void nearestNeighbour(const Cities& cities, size_t startCity, TourArray& tour, double& tourDistance);
  }
}

#endif // !__TSP_NEAREST_NEIGHBOUR_H__
