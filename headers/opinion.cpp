/**
   @file core.cpp
   @brief Our main header file.
   This holds all of our functions and classes.
   We may seperate this in the future, and if we do we must update
   the documentation.
*/
#ifndef KENT_OPINION_CPP_
#define KENT_OPINION_CPP_

#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <utility>

#include "core.hpp"
#include "atom.hpp"
#include "sub_frame.hpp"
#include "opinion.hpp"
#include "beta.hpp"
#include "beta_opinion.hpp"

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

    /**
     * @class Opinion
     * This holds the opinion for a sub_frame of the frame of discernment.
     * It includes the belief, disbelief, uncertainty, and relative atomicity
     * for a set of atoms to be exist.
     */
	Opinion::Opinion()
	{
	}

	/**
	 * Create an opinion based on f.
	 */
	Opinion::Opinion(const Frame& f, const Sub_frame& sf) :
	    belief_(belief(f, sf))
	    , disbelief_(disbelief(f, sf))
	    , uncertainty_(uncertainty(f, sf))
	    , base_rate_(atomicity(f, sf))
	    , probability_expectation_(probability_expectation(f, sf))
	{
	}

	/**
	   Explicitly sets the parameters of the opinion. Uncertainty is assumed.
	*/
	Opinion::Opinion(Real belief, Real disbelief, Real base_rate)
	    : belief_(belief)
	    , disbelief_(disbelief)
	    , uncertainty_(1 - belief - disbelief)
	    , base_rate_(base_rate)
	    , probability_expectation_(belief + base_rate * (1 - belief - disbelief))
	{
	}

	Opinion::Opinion(Beta b)
		: belief_(belief(b.get_r(), b.get_s()))
		, disbelief_(disbelief(b.get_r(), b.get_s()))
		, uncertainty_(uncertainty(b.get_r(), b.get_s()))
		, base_rate_(b.get_a())
		, probability_expectation_(
				probability_expectation(b.get_r(), b.get_s(), b.get_a()))
	{}

	void Opinion::set_frame(const Frame& f, const Sub_frame& sf)
	{
	    belief_ = belief(f, sf);
	    disbelief_ = disbelief(f, sf);
	    uncertainty_ = uncertainty(f, sf);
	    base_rate_ = atomicity(f, sf);
	    probability_expectation_ = probability_expectation(f, sf);
	}

	const Real Opinion::get_belief() const
	{
	    return belief_;
	}
	const Real Opinion::get_disbelief() const
	{
	    return disbelief_;
	}
	const Real Opinion::get_uncertainty() const
	{
	    return uncertainty_;
	}
	const Real Opinion::get_base_rate() const
	{
	    return base_rate_;
	}

	const Real Opinion::get_probability_expectation() const
	{
	    return probability_expectation_;
	}
	
	Beta Opinion::Beta_Representation() const
	{
		return Beta(*this);
	}

    //-------------------------------------------------------------------------------
    // Overloaded operators.

    /* Propositional conjunction for 2 opinions
     * found on page 14 of Josangs "A Logic for uncertain Probability"
     * Modified according to a request by Dr. Kent and the draft book by Josang.
     */
    Opinion operator &(const Opinion& a, const Opinion& b) throw()
    {
	
	Real belief = a.get_belief() * b.get_belief() +
	    ((1-a.get_base_rate()) * b.get_base_rate() * a.get_belief() * b.get_uncertainty() +
	     a.get_base_rate() * (1 - b.get_base_rate()) * a.get_uncertainty() * b.get_belief()) /
	     (1 - a.get_base_rate() * b.get_base_rate());
	Opinion c(belief, // generate the new belief
		  a.get_disbelief() + b.get_disbelief() - a.get_disbelief() * b.get_disbelief(), // disbelief
		  a.get_base_rate() * b.get_base_rate()); // base rate
	// generate the new base_rate

	return c;
    }

// Propositional disjunction for 2 opinions
// found on page 14 of Josangs "A Logic for uncertain Probability"
    Opinion operator |(const Opinion& a, const Opinion& b) throw()
    {
	Real disbelief = a.get_disbelief() * b.get_disbelief() +
	    (a.get_base_rate() * (1 - b.get_base_rate()) * a.get_disbelief() * b.get_uncertainty() +
	     (1-a.get_base_rate()) *b.get_base_rate() * a.get_uncertainty() * b.get_disbelief()) /
	     (a.get_base_rate() + b.get_base_rate() - a.get_base_rate() * b.get_base_rate());
	Opinion c((a.get_belief() + b.get_belief()) - (a.get_belief() * b.get_belief()), // generate the new belief
		  disbelief, // generate the new disbelief
		  a.get_base_rate() + b.get_base_rate() - a.get_base_rate() * b.get_base_rate() // generate the new base_rate
	    );
	return c;
    }
	
// Addition
// Found in josangs draft of his book section 4.1
// Definition 10
    Opinion operator +(const Opinion& a, const Opinion& b) throw(Out_of_Range)
    {
	if((a.get_base_rate() + b.get_base_rate()) > 1 ||
	   (a.get_belief() + b.get_belief()) > 1)
	{
	    throw Out_of_Range();
	}
		
	return Opinion(a.get_belief() + b.get_belief(), // belief
		       (a.get_base_rate() * (a.get_disbelief() - b.get_belief()) + b.get_base_rate() * (b.get_disbelief() - a.get_belief()))/
		       (a.get_base_rate() + b.get_base_rate()), // disbelief
		       a.get_base_rate() + b.get_base_rate()); // base rate
    }
	
// substration
// Found in Josangs draft of this book section 4.1
// Definition 11
    Opinion operator -(const Opinion& a, const Opinion& b) throw(Out_of_Range)
    {
	if(((a.get_base_rate() * (a.get_disbelief() + b.get_belief())) - 
	   (b.get_base_rate()* (1 + b.get_belief() - a.get_belief() - b.get_uncertainty()))) < 0 ||
	   a.get_belief() - b.get_belief() < 0 ||
	   a.get_base_rate() - b.get_base_rate() < 0)
	{
	    throw Out_of_Range();
	}
		
	return Opinion(a.get_belief() - b.get_belief(), // belief
		       ((a.get_base_rate() * (a.get_disbelief() + b.get_belief())) - 
	   (b.get_base_rate()* (1 + b.get_belief() - a.get_belief() - b.get_uncertainty())))/
		       (a.get_base_rate() - b.get_base_rate()), // disbelief
		       a.get_base_rate() - b.get_base_rate()); // base rate
    }

// Negation
// found on page 18 of Jasangs "A logic for uncertain Probability"
    Opinion operator ~(const Opinion& a) throw()
    {
	Opinion c(a.get_disbelief(), a.get_belief()
		  , 1 - a.get_base_rate());
	return c;
    }

///This is defined in the paper "A Logic for Uncertain Probabilities"
///on page 9 near the bottom.
    bool operator <(const Opinion& f1, const Opinion& f2) throw()
    {
	if (f1.get_probability_expectation() 
	    != f2.get_probability_expectation())
	    return f1.get_probability_expectation() 
		< f2.get_probability_expectation();
	else if (f1.get_uncertainty() != f2.get_uncertainty())
	    return f1.get_uncertainty() > f2.get_uncertainty();
	else
	    return f1.get_base_rate() > f1.get_base_rate();
    }

    bool operator ==(const Opinion& f1, const Opinion& f2) throw()
    {
	return f1.get_probability_expectation() 
	    == f2.get_probability_expectation() 
	    && f1.get_uncertainty() == f2.get_uncertainty()
	    && f1.get_base_rate() == f2.get_base_rate();
    }

// Using this, we get free definitions of the other 6 logical and
// ordering operators based off of our definitions of < and ==.
    using namespace std::rel_ops;
}

#endif
