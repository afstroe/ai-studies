// implementation: Alin Stroe
// mail to: afstroe@gmail.com
// linkedin: https://www.linkedin.com/in/alinstroe/
// purpose: implementation of a stochastic hill climbing algorithm 
//          although the stochastic part is left out to the user :)
// Copyright © 2020 Alin Stroe, all rights reserved

#ifndef __HILL_CLIMBING_H__
#define __HILL_CLIMBING_H__

#include <vector>

#include "../utility/Defines.h"

namespace stochastic {

  /*!
    * \brief Hill climbing using random neighbours
    *
    * The strategy of the algorithm is to select on neighbour at random and to 
    * check it against the currently accepted solution. If the cost evaluator function is satisfied
    * the neighbour becomes the currently accepted solution. The algorithm runs for a predefined number
    * of steps. The algorithm is intended to overcome the Greedy approach of the deterministic hill climbing
    * (which often results in local optima).
    *
    * \tparam Solution - the solution type;
    * \tparam GenerateRandomNeighbourFunction - the type of the function needed to generate a random neighbour;
    * \tparam CostEvaluatorFunction - the type of the function needed to evaluate the costs;
    *
    * \param[in] capIterations - the number of iterations to reach a solution;
    * \param[in] initialSolution - initial solution of the problem;
    * \param[in] randomNeighbour - the function that selects the neighbour to evaluate;
    * \param[in] costEvaluator - the function that evaluates the two solutions considered;
    *
    * \return the solution;
    * \ingroup stochastic
    * \note <b>the implementation might be suboptimal if Solution is a vector of an important size.</b>
    */
  template <class Solution, class GenerateRandomNeighbourFunction, class CostEvaluatorFunction>
  Solution hillClimbing(size_t capIterations, const Solution& initialSolution, GenerateRandomNeighbourFunction randomNeighbour, CostEvaluatorFunction costEvaluator)
  {
    // in an effort to keep this implementation as general as possible
    // user must provide the initial solution function
    // problemSpace will yield out of the currentSoltution's dimension
    //! solution should contain the parameters and the objective function result;
    auto currentSolution = initialSolution;

    // Declare the candidate here - this helps with avoiding the costly creation and allocation
    // of std::vectors in the inner loop;
    // candidate will have the same dimension as the currentSolution and that will 
    // be the project space;
    auto candidate = currentSolution;

    // algorithm loop
    FOR(ite, capIterations)
    {
      // GenerateRandomNeighbourFunction needs to output the random neighbour
      // and not return it
      randomNeighbour(candidate);

      // cost evaluator needs to return true if the current solution is 
      // to be changed
      if (costEvaluator(candidate, currentSolution))
      {
        // move to the neighbour as it presents better results
        currentSolution = candidate;
      }
      else
      {
        // reset the neighbour
        candidate = currentSolution;
      }
    }

    // the best solution found
    return currentSolution;
  }

  namespace unitTest {
    double climbHill();
  }

}


#endif // !__HILL_CLIMBING_H__

