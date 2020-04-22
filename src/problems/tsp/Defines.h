#ifndef __TSP_DEFINES_H__
#define __TSP_DEFINES_H__

#include <vector>
#include <cmath>

/*! \defgroup problems A collection of well known problems. */
namespace problems {
  /*! \defgroup tsp Traveling salesman. 
      \ingroup problems
  */
  namespace tsp {
    using City = struct
    {
      double x = 0, y = 0;
    };

    static const std::vector<City> Berlin52 = {
      {565, 575 }, {25, 185}, {345, 750},  {945, 685},  {845, 655}, 
      {880, 660}, {25, 230}, {525, 1000}, {580, 1175}, {650, 1130}, {1605, 620}, 
      {1220, 580}, {1465, 200}, {1530, 5}, {845, 680}, {725, 370}, {145, 665}, 
      {415, 635}, {510, 875}, {560, 365}, {300, 465}, {520, 585}, {480, 415}, 
      {835, 625}, {975, 580}, {1215, 245}, {1320, 315}, {1250, 400}, {660, 180}, 
      {410, 250}, {420, 555}, {575, 665}, {1150, 1160}, {700, 580}, {685, 595}, 
      {685, 610}, {770, 610}, {795, 645}, {720, 635}, {760, 650}, {475, 960}, 
      {95, 260}, {875, 920}, {700, 500}, {555, 815}, {830, 485}, {1170, 65}, 
      {830, 610}, {605, 625}, {595, 360}, {1340, 725}, {1740, 245}
    };

    using TourArray = std::vector<size_t>;
    using Cities = std::vector<City>;

    inline double distance(const City& city0, const City& city1)
    {
      const auto cx = city0.x - city1.x;
      const auto cy = city0.y - city1.y;
      return std::sqrt(cx * cx + cy * cy);
    }
  }
}

#endif // !__TSP_DEFINES_H__
