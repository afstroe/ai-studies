// implementation: Alin Stroe
// mail to: afstroe@gmail.com
// linkedin: https://www.linkedin.com/in/alinstroe/
// purpose: an implementation of the Random Search algorithm
// description:
//	this algorithm will sample the ScearchSpace at random locations searching for elements
//		that match the SearchCost criterion;
//	the SearchPredicate will provide the solution at random locations;
//	both the SearchCost and the SearchPredicate are to be provided by the user
// Copyright © 2020 Alin Stroe, all rights reserved

#ifndef __RANDOM_SEARCH_H__
#define __RANDOM_SEARCH_H__

#include "../random_generators/vectorGenerator.h"

/*! \defgroup stochastic A group of stochastic algorithms */
namespace stochastic
{	
/*! \class SearchSpace2D
	* \brief Definition of a 2D search space.
	*
	* This is essentially an interval on an axis
	*
	* \tparam Type: the type of the search space
	* \ingroup stochastic
	*/
	template <typename Type>
	class SearchSpace2D
	{
	public:

		/*!
			* \brief default c-tor
			*/
		SearchSpace2D()
		{
			_left = _right = 0.0;
		}


		/*!
			* \brief init c-tor
			*/
		SearchSpace2D(const Type& left, const Type& right)
		{
			_left = left;
			_right = right;
		}


		/*!
			* \brief retrieves the length of the search space
			* \return the search space length
			*/
		inline Type length()
		{
			return std::abs(_right - _left);
		}


		/*!
			* \brief retrieves the left hand side (the smallest number) of the search space
			* \return the left hand side (the smallest number) of the search space
			*/
		inline Type& left()
		{
			return _left;
		}

		/*!
			* \brief retrieves the right hand side (the biggest number) of the search space
			* \return the right hand side (the biggest number) of the search space
			*/
		inline Type& right()
		{
			return _right;
		}
	protected:
		Type _left;
		Type _right;
	};

/*!
	* \brief Function to generate a set of problemSize values in the space of the searchSpace	
	* \tparam Type: the number type used
	*
	* \param problemSize: the vector dimension to generate
	* \param searchSpace: the search space into which we generate
	*
	* \return the generated vector
	*/
	template <class Type, template <class> class SearchSpace>
	std::vector<Type> randomGeneration2D(size_t problemSize, SearchSpace<Type> searchSpace)
	{
		// call the random generator for the given size and space
		return randomGenerators::generateRandomVector<Type, std::vector>(problemSize, searchSpace.left(), searchSpace.right(), randomGenerators::Distribution::UNIFORM);
	}


	/*!
		* \brief The random search algorithm
		* Sample solution across the search space using an uniform distribution.
		* The solution is just an approximation.
		* \tparam Type: the number type used for the random search
		* \tparam SearchSpace: the search space used by the algorithm
		* \tparam FunctionToOptimize: the prototype of the function to optimize
		* \tparam RandomGenerationFunction: the prototype of the random numbers generator
		* \tparam CostComparatorFunction: the prototype of the cost comparator
		*
		* \param initialOptimal: initial optimal value
		* \param problemSize: the dimension of the vector to scan
		* \param numIterations: the number of iterations used to reach the solution
		* \param searchSpace: the search space object
		* \param function: the function whose solution we are computing
		* \param randomGenerationFunction: the random numbers generator
		* \param acceptNewCost: function to compare and accept costs
		*
		* \return the solution
		* \ingroup stochastic
		*/
	template <typename Type, template <class> class SearchSpace, class FunctionToOptimize, class RandomGenerationFunction, class CostComparatorFunction>
	Type randomSearch(Type initialOptimal, size_t problemSize, size_t numIterations, SearchSpace<Type> searchSpace, FunctionToOptimize function, RandomGenerationFunction randomGenerationFunction, CostComparatorFunction acceptNewCost)
	{
		// the result to be outputted
		Type optimal = initialOptimal;

		// iterate numIteration to find an approximate optimal
		for (int i = 0; i < numIterations; ++i)
		{
			// generate a set of inputs for the random generation function
			auto inputs = randomGenerationFunction(problemSize, searchSpace);

			// function has to accept a std::vector<Type> of problemSize size()
			Type cost = function(inputs);

			// compare the cost against our current optimal;
			// the costComparator function needs to be a boolean functions
			// deciding on accepting/rejecting the new cost
			if (acceptNewCost(optimal, cost))
			{
				optimal = cost;
			}
		}

		// this is our computed optimal result
		return optimal;
	}


	void randomSearchTest();
}
#endif // !__RANDOM_SEARCH_H__
