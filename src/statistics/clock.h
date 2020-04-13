// implementation: Alin Stroe
// mail to: afstroe@gmail.com
// linkedin: https://www.linkedin.com/in/alinstroe/
// purpose: something to time bits and pieces
// Copyright © 2020 Alin Stroe, all rights reserved

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <chrono>
#include <iostream>

/*! \defgroup statistics statistics - module for application performance monitors */
namespace statistics
{

  /*!
    * \brief Function to measure the time needed to perform a function
    *
    * \tparam FunctionType - type of the function to be timed
    *
    * \param function - pointer to the function to be timed
    *
    * \return the time (in milliseconds) needed to perform the function
    * \ingroup statistics
    */
  template<typename FunctionType>
  double clock(FunctionType function)
  {
    auto start = std::chrono::system_clock::now();

    function();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> time = end - start;

    return time.count() * 1000;
  };


  /*!
    * \brief Utility function to measure the time needed to perform a task.
    * This variant has an added echo to cout
    * \tparam FunctionType - type of the function to be timed
    *
    * \param function - pointer to the function to be timed
    * \param name - user friendly name of the function to be timed
    *
    * \return the time needed (in milliseconds) to perform the function
    * \ingroup statistics
    */
  template<typename FunctionType>
  double clock(FunctionType function, const char* name)
  {
    auto t = clock(function);

    std::cout << name << " done in " << t << " ms" << std::endl;

    return t;
  }
    
}


#endif // !__CLOCK_H__
