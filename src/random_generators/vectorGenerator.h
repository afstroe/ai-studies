// implementation: Alin Stroe
// mail to: afstroe@gmail.com
// linkedin: https://www.linkedin.com/in/alinstroe/
// purpose: generation of a random vector
// Copyright © 2020 Alin Stroe, all rights reserved

#ifndef __VECTOR_GENERATOR_H__
#define __VECTOR_GENERATOR_H__

#include <xmemory>
#include <random>
#include <type_traits>

/*!
  \defgroup randomGenerators Utilities for random numbers generation
*/
namespace randomGenerators
{
  /*!
    \brief the random distribution
  */
  enum class Distribution
  {
    UNIFORM = 0,/*!< uniform distributed numbers */
  };

  /*! \class Generator "vectorGenerator.h"
    *  \brief Base class for random numbers generation.
    *
    * empty.
    */
  class Generator{};


  /*! \class UniformDistributedGenerator "vectorGenerator.h"
    * \brief Base class for random uniform distributed numbers generation.
    * \tparam Type [int, double] number type
    */
  template <typename Type, typename TypeType>
  class UniformDistributedGenerator : public Generator
  {
  };


  /*! \class UniformDistributedGenerator "vectorGenerator.h"
    * \brief Base class for random uniform distributed numbers generation. Specialization for integer.
    * \tparam TypeType [short, long,...] integer type   
    */
  template <typename TypeType>
  class UniformDistributedGenerator<int, TypeType>
  { 
  public:
    UniformDistributedGenerator(int min, int max)
    {
      distribution = std::uniform_int_distribution<TypeType>(min, max);
    }

    TypeType operator()(std::default_random_engine& engine)
    {
      return distribution(engine);
    }

  protected:
    std::uniform_int_distribution<TypeType> distribution;    
  };


  /*! \class UniformDistributedGenerator
    * \brief The uniform distributed floating point numbers generator.
    *
    * \tparam floating point type [double, float, ...]
    */
  template <typename TypeType>
  class UniformDistributedGenerator<double, TypeType>
  {
  public:

    /*!
      * \brief default c-tor
      */    UniformDistributedGenerator() = default;
    UniformDistributedGenerator(double min, double max)
    {
      distribution = std::uniform_real_distribution<TypeType>(min, max);
    }

    /*!
      * \brief gets the random distribution
      * \param engine - the default random engine to use
      *
      * \return a random number with the given distribution      
      */
    TypeType operator()(std::default_random_engine& engine)
    {
      return distribution(engine);
    }

  protected:
    std::uniform_real_distribution<TypeType> distribution;/*!< distribution */
  };

  /*! \class UniformDistributedGenerator "vectorGenerator.h"
    * \brief Base class for random uniform distributed numbers generation. Specialization for integer.
    * \tparam TypeType [float, double,...] floating point type
    */
  template <typename TypeType>
  class UniformDistributedGenerator<float, TypeType> : public UniformDistributedGenerator<double, TypeType> 
  {
  public:

    /*!
      * \brief c-tor
      */
    UniformDistributedGenerator(float min, float max)
    { 
      UniformDistributedGenerator<double, TypeType>::distribution = std::uniform_real_distribution<TypeType>(min, max);
    }
  };

  /*! \class DefaultRandomEngine 
    * \brief Singleton to get the random engine.
    *
    * Creating the random engine every time it's needed can be an expensive proposition.
    * Use this to get a default random engine.
    *
    */
  class DefaultRandomEngine
  {
  public:

    /*!
      * Gets an instance of the singleton
      * \return an instance of the singleton
      * \ingroup randomGenerators
      */
    static std::default_random_engine& get()
    {
      static std::default_random_engine* s_randomEngine_ptr = nullptr;
      if (!s_randomEngine_ptr)
      {
        std::random_device randomDevice;
        static std::default_random_engine s_randomEngine(randomDevice());
        s_randomEngine_ptr = &s_randomEngine;
      }

      return *s_randomEngine_ptr;/*! the singleton instance */
    }
  protected:    
  };


  /*!
    * \brief Creates an uniform distributed random set of numbers.
    *
    * \tparam Type: the type of the numbers to populate the container
    * \tparam TypeType: the numbers sub-type.
    * \tparam Container: the container type to be filled - std::vector<Type>
    * \param size: the number of random numbers to be created
    * \param min: the smallest random number possible
    * \param max: the largest random number possible
    */
  template <class Type, class TypeType, template <class, class> class Container>
  Container<Type, std::allocator<Type>> generateUniformRandomContainer(size_t size, Type min, Type max)
  {
    auto& randomEngine = DefaultRandomEngine::get();
    Container<Type, std::allocator<Type>> vect(size);
    UniformDistributedGenerator<Type, TypeType> generate(min, max);
    for (int i = 0; i < size; ++i)
    {
      vect[i] = generate(randomEngine);
    }

    return vect;
  }


  /*!
    * \brief generates a vector of random numbers
    * \tparam Type: numbers type
    * \tparam TypeType: numbers sub-type
    * \param size: the number of random numbers to be created
    * \param min: the smallest random number possible
    * \param max: the largest random number possible
    * \param distribution: the random distribution to follow
    * \return the std::vector<Type> created
    * \ingroup randomGenerators
    */
  template <class Type, template <class, class> class Container, class TypeType = Type>
  Container<Type, std::allocator<Type>> generateRandomVector(size_t size, Type min, Type max, Distribution distribution)
  {
    switch (distribution)
    {
      default:
      case Distribution::UNIFORM:
      {
        return generateUniformRandomContainer<Type, TypeType, std::vector>(size, min, max);
      }
      break;
    }
  }
}

#endif // !__VECTOR_GENERATOR_H__

