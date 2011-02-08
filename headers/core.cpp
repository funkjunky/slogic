/**
   @file core.cpp
   @brief Our main header file.
   This holds all of our functions and classes.
   We may seperate this in the future, and if we do we must update
   the documentation.
*/
#ifndef KENT_SLOGIC_CPP_
#define KENT_SLOGIC_CPP_

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <utility>

#include "core.hpp"
#include "frame.hpp"
#include "atom.hpp"
#include "sub_frame.hpp"
#include "opinion.hpp"
#include "beta.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#include <boost/rational.hpp>

#define LEAST_UNCERTAINTY

#ifdef LEAST_ATOMICITY
#undefine LEAST_UNCERTAINTY
#endif

/**
 * @namespace Subj_logic
 * This namespace stores all of the code for the Subjective Logic
 * Library.
 */
namespace Subj_logic {

    using namespace boost;

    //-------------------------------------------------------------------------------
    // Typedefs.

    //typedef double Real;
    typedef rational<long> Real;

    //-------------------------------------------------------------------------------
    // Helper functions. Consider wrapping them in a seperate namespace.

    // Consider moving this to a sub-namespace for helper functions.
    template <typename T>
    bool is_subset(const std::vector<T>& x, const std::vector<T>& y)
    {
	typedef typename std::vector<T>::const_iterator Iter;
	for (Iter i = x.begin(); i != x.end(); ++i)
	    if (find(y.begin(),y.end(), *i) == y.end())
		return false;
	return true;
    }

    //-------------------------------------------------------------------------------
    // Function definitions: belief, disbelief, uncertainty, atomicity, and
    // probability expectation.

    /**
     * This function computes the belief in x, based on the definition
     * in the paper.
     * @param x The frame to compute the belief of.
     */
    Real belief(const Frame& f, const Sub_frame& x) throw()
    {
	Real b;
	for (const_sIter y = f.sub_frames().begin(); y != f.sub_frames().end(); ++y)
	    if (is_subset((*y)->atoms(), x.atoms()))
	    {
		b += (*y)->mass();
	    }
	return b;
    }

    /**
     * This function computes the disbelief in the frame x
     * based on the definition in the paper.
     * @param x The frame to compute the disbelief of.
     */
    Real disbelief(const Frame& f, const Sub_frame& x) throw()
    {
	Real d;
	for (const_sIter y = f.sub_frames().begin(); y != f.sub_frames().end(); ++y) {
	    // Compute the intersection of y and x.
	    std::vector<AtomPtr> intersection;
	    std::set_intersection(x.atoms().begin(), x.atoms().end(),
				  (*y)->atoms().begin(), (*y)->atoms().end(),
				  std::back_inserter(intersection));
	    if (intersection.size() == 0)
		d += (*y)->mass();
	}
	return d;
    }

    /**
     * This function computes the uncertainty of x
     * based on the identity b(x) + d(x) + u(x) = 1.
     * @param x The frame to compute the disbelief of.
     */
    Real uncertainty(const Frame& f, const Sub_frame& x) throw()
    {
	return 1 - belief(f,x) - disbelief(f, x);
    }

    /**
     * This function computes the atomicity of x with
     * respect to the entire frame of discernment.
     * @param x The frame to compute the atomicity of.
     */
    Real atomicity(const Frame& f, const Sub_frame& x) throw()
    {
	// Create a temporary sub frame around the entire frame of discernment
	// and call the other function.
	Sub_frame temp(f.atoms().begin(), f.atoms().end());
	return atomicity(x, temp);
    }

    /**
     * This function computes the atomicity of x with respect
     * to y.
     * @param x The subframe to compute the relative atomicity of.
     * @param y The subframe of reference.
     *
     * This should not return an exeption on empty frame y, it should
     * return 0
     * - Gilles
     */
    Real atomicity(const Sub_frame& x, const Sub_frame& y) throw()
    {
	if (y.atoms().size() == 0)
	    return 0;
	std::vector<AtomPtr> intersection;
	std::set_intersection(x.atoms().begin(), x.atoms().end(),
			      y.atoms().begin(), y.atoms().end(), std::back_inserter(intersection));
	return Real(intersection.size(), y.atoms().size());
    }

    //for_each algorithm would make this more terse.

    // The issue with for_each is that it requires you to pass it a function-object.
    // Unless we want to have boost as a build requirement, we can use their lambdas.
    // - Bryan
    //But now we are using Boost ;). Also what about using the new standard.
    //Lambdas are virtually gaurenteed to be in the new standard.
    Real probability_expectation(const Frame& f, const Sub_frame& sub_frame) throw()
    {
	Real sum;
	for (const_sIter i = f.sub_frames().begin(); i != f.sub_frames().end(); ++i)
	    sum += (*i)->mass() * atomicity(sub_frame, **i);

	return sum;
    }

    /**
       @brief Determines the probability expectation of an opinion.
       Interpolating from page 17 (eqn 12), justified considering the 
       rearrangement on page 6 (eqn 4) all from 
       A Logic for Uncertain Probability.
    */
    Real probability_expectation(const Opinion& opinion) throw()
    {
	return opinion.get_belief() + opinion.get_uncertainty()
	    / opinion.get_base_rate();
    }


    /*
     * This function implements division as defined in the paper
     * `Multiplication and Co-multiplication of Beliefs`.
     */
    Opinion divide(const Opinion& x, const Opinion& y) throw()
    {
	Real bx = x.get_belief();
	Real dx = x.get_disbelief();
	Real ux = x.get_uncertainty();
	Real ax = x.get_base_rate();

	Real by = y.get_belief();
	Real dy = y.get_disbelief();
	Real uy = y.get_uncertainty();
	Real ay = y.get_base_rate();
	
	Real belief = (ay * (bx + ax * ux) / (ay - ax) * (by + ay * uy))
	    - (ax * (1 - dx) / (ay - ax) * (1 - dy));
	
	Real disbelief = (dx - dy) / (1 - dy);

	Real atomicity = ax / ay;

	return Opinion(belief, disbelief, atomicity);
    }


    /*
     * This function implements co-division as defined in the paper
     * `Multiplication and Co-multiplication of Beliefs`.
     */
    Opinion co_divide(const Opinion& x, const Opinion& y) throw()
    {
	Real bx = x.get_belief();
	Real dx = x.get_disbelief();
	Real ux = x.get_uncertainty();
	Real ax = x.get_base_rate();

	Real by = y.get_belief();
	Real dy = y.get_disbelief();
	Real uy = y.get_uncertainty();
	Real ay = y.get_base_rate();

	Real belief = (bx - by) / (1 - by);

	Real disbelief = ((1 - ay) * (1 - (bx + ax * ux))
			  / (ax - ay) * (1 - (by + ay * uy)))
	    - ((1 - ax) * (1 - bx) / (ax - ay) * (1 - by));

	Real atomicity = (ax - ay) / (1 - ay);

	return Opinion(belief, disbelief, atomicity);
    }

	
    //This will ensure the sum Frame of Discernment's powerset's BMAs is
    //equal to 1.
    bool check_BMA() throw()
    {
	return true;
    }

// Using this, we get free definitions of the other 6 logical and
// ordering operators based off of our definitions of < and ==.
    using namespace std::rel_ops;
}

#endif
