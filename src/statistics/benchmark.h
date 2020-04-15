// implementation: Alin Stroe
// mail to: afstroe@gmail.com
// linkedin: https://www.linkedin.com/in/alinstroe/
// purpose: definition of a benchmark mechanism
// Copyright © 2020 Alin Stroe, all rights reserved

#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <string>
#include <list>
#include <sstream>

#include "../utility/Defines.h"
#include "clock.h"

namespace statistics {
  /*! \class Benchmark
    * \brief Class to benchmark algorithms.
    *
    *  Base | Algorithm | Iterations | Time |Best Time|Worst time| Average result | Variance from base average
    *  :--: | :-------: | :--------: | :--: | :-----: | :------: | :------------: | :------------------------:
    *   1/0 |  name     |     #      | ms   |  ms     | ms       |    -           |                -
    *
    * \ingroup statistics
    */
  class Benchmark
  {
  public:
    /*! \class AlgorithmStatistics
      * \brief Description of the algorithm .
      *
      * This is run by the Benchmark class
      */
    class AlgorithmStatistics
    {
      DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(bool, base)
      DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(std::string, name)
      DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(size_t, iterations)
      DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(double, timeMillis)
      DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(double, averageResult)
      DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(double, worstTime)
      DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(double, bestTime)


      /*!
        * \brief Init c-tor.
        * Executes the algorithm and collects statistics
        * \tparam Function - the algorithm function type
        * \tparam Args - the Arguments
        *
        * \param iterations - the number of iterations to execute
        * \param name - the name of the algorithm
        * \param isBase - this is the base algorithm (there can be only one)
        * \param algorithm - the function that executes the algorithm
        * \param algorithmArguments - algorithm arguments
        */
      template <class Function, class... Args>
      inline AlgorithmStatistics(size_t iterations, const char* name, bool isBase, Function algorithm, Args... algorithmArguments);
      
      /*!
        * \brief Init c-tor.
        * Executes the algorithm and collects statistics
        * \tparam Function - the algorithm function type        
        *
        * \param iterations - the number of iterations to execute
        * \param name - the name of the algorithm
        * \param isBase - this is the base algorithm (there can be only one)
        * \param algorithm - the function that executes the algorithm        
        */
      template <class Function>
      inline AlgorithmStatistics(size_t iterations, const char* name, bool isBase, Function algorithm);
      
      //! default c-tor
      inline AlgorithmStatistics() :
        _base(false)
      , _iterations(0)
      , _timeMillis(0)
      , _averageResult(0)
      , _worstTime(0)
      , _bestTime(std::numeric_limits<double>::max())
      {
        ;
      }
    };
  public:


    /*!
      * \brief Adds an algorithm to the benchmark
      *
      * The algorithm was already executed in the c-tor and statistics are now available
      *
      * \param algorithm - the algorithm statistics
      */
    void addAlgorithm(const AlgorithmStatistics algorithm)
    {
      table.push_back(algorithm);
      if (algorithm.base())
      {
        base = &*table.rbegin();
      }      
    }


    /*!
      * \brief Prints the benchmark results to console
      */
    void printResults()
    {
      std::stringstream info;
      for (auto& a : table)
      {        
        info << "Is base: " << a.base() << "; " << std::endl;
        info << "Algorithm: " << a.name() << "; " << std::endl;
        info << "Iterations: " << a.iterations() << "; " << std::endl;
        info << "Average Time: " << a.timeMillis() << " ms; " << std::endl;
        info << "Best time: " << a.bestTime() << " ms; " << std::endl;
        info << "Worst time: " << a.worstTime() << " ms; " << std::endl;
        info << "Average result: " << a.averageResult() << "; " << std::endl;
        info << "Variance from base: " << std::abs(base->averageResult() - a.averageResult()) << "; " << std::endl;
        info << "====================================================================================" << std::endl;
      }

      std::cout << info.str();
    }

  protected:
    std::list<AlgorithmStatistics> table;
    const AlgorithmStatistics* base = nullptr;
  };

  template <class Function, class... Args>
  Benchmark::AlgorithmStatistics::AlgorithmStatistics(size_t iterations, const char* name, bool isBase, Function algorithm, Args... algorithmArguments):
    AlgorithmStatistics()
  {
    _base = isBase;
    _name = name;
    _iterations = iterations;
    double result = 0;
    double time = 0;
    FOR(i, iterations)
    {           
      auto crtTime = clock(
        [&result, &algorithm , &algorithmArguments...]()
        {
          result += algorithm(std::forward(algorithmArguments...));
        }
      ); 
      if (crtTime < _bestTime)
      {
        _bestTime = crtTime;
      }
      if(crtTime > _worstTime)
      { 
        _worstTime = crtTime;
      }

      time += crtTime;
    }

    _timeMillis = time / iterations;
    _averageResult = result / iterations;
  }
  template <class Function>
  Benchmark::AlgorithmStatistics::AlgorithmStatistics(size_t iterations, const char* name, bool isBase, Function algorithm):
    AlgorithmStatistics()
  {
    _base = isBase;
    _name = name;
    _iterations = iterations;
    double result = 0;
    double time = 0;
    FOR(i, iterations)
    {
      auto crtTime = clock(
        [&result, &algorithm]()
        {
          result += algorithm();
        }
      );
      if (crtTime < _bestTime)
      {
        _bestTime = crtTime;
      }
      if (crtTime > _worstTime)
      {
        _worstTime = crtTime;
      }

      time += crtTime;
    }

    _timeMillis = time / iterations;
    _averageResult = result / iterations;
  }
}

#endif // !__BENCHMARK_H__

