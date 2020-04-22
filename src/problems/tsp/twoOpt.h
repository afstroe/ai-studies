#ifndef __TSP_TWO_OPT_H__
#define __TSP_TWO_OPT_H__

#include "../../utility/Defines.h"
#include "Defines.h"

namespace problems {
  namespace tsp {


    /*!
      * \brief Reverses a multi-city segment.
      *
      * (c0, c1, ..., ck) becomes (ck, ..., c1, c0)
      *
      * \param[out] tour - the tour to be optimized 
      * \param[in] startIndex - the start index inside the tour
      * \param[in] endIndex - the end index inside the tour
      *
      * \ingroup tsp
      */
    void reverseSegment(TourArray& tour, size_t startIndex, size_t endIndex);

    /*!
      * \brief Calculates the gain if the Two Opt algorithm is applied
      *
      * \param[in] x0 - the first of the first set of cities;
      * \param[in] x1 - the second of the first set of cities;
      * \param[in] y0 - the first of the second set of cities;
      * \param[in] y1 - the second of the second set of cities;
      *
      * \return the gain obtained if the Two Opt technique is applied
      * \ingroup tsp
      */
    inline double twoOptGain(const City& x0, const City& x1, const City& y0, const City& y1)
    {
      return (distance(x0, x1) + distance(y0, y1)) - (distance(x0, y0) + distance (x1, y1));
    }

    /*!
      * \image html tsp-two-opt.png
      * \brief Make the Two Opt move between two cities
      *
      * \param[out] tour - the tour to optimize
      * \param[in] i - the first city in the switch (X1)
      * \param[in] j - the second city in the switch (X2)
      *       
      *
      * \ingroup tsp
      */    
    inline void makeTwoOptMove(TourArray& tour, size_t i, size_t j)
    {
      reverseSegment(tour, (i + 1) % tour.size(), j);
    }

    /*!
      * \brief Executes an optimization of the tour using the first Opt Move that provides gain.
      *
      * \param[in] cities - the cities forming the problem
      * \param[out] tour - an initial solution
      *
      * \ingroup tsp
      */
    void firstTwoOptMove(const Cities& cities, TourArray& tour);
    
    /*!
      * \brief Executes an optimization of the tour using the Opt Move that provides the best gain.
      *
      * \param[in] cities - the cities forming the problem
      * \param[out] tour - an initial solution
      *
      * \ingroup tsp
      */
    void twoOptMove(const Cities& cities, TourArray& tour);
  }
}

#endif // !__TSP_TWO_OPT_H__




