/**
   @file core.hpp
   @brief Our main header file.
   This holds all of our functions and classes.
   We may seperate this in the future, and if we do we must update
   the documentation.
*/
#ifndef KENT_OPINION_HPP_
#define KENT_OPINION_HPP_

#include <set>
#include <vector>
#include <string>
#include <stdexcept>

#include "core.hpp"
#include "beta.hpp"
#include "atom.hpp"
#include "sub_frame.hpp"

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

	//forward declare opinion, so I can use it in the operator prototypes.
	//Operator prototypes need to go first, because they are friended by 
	//the opinion class.
	class Opinion;
	class Beta;
	class Frame;
	struct Out_of_Range{};
    // Operators.

    Opinion operator +(const Opinion&, const Opinion&) throw(Out_of_Range);
    Opinion operator -(const Opinion&, const Opinion&) throw(Out_of_Range);
    Opinion operator &(const Opinion&, const Opinion&) throw();
    Opinion operator |(const Opinion&, const Opinion&) throw();
    Opinion operator ~(const Opinion&) throw();

    bool operator <(const Opinion&, const Opinion&) throw();
    bool operator ==(const Opinion&, const Opinion&) throw();

   //-------------------------------------------------------------------------------
    // Class definitions.
    /**
     * @class Opinion
     * This holds the opinion for a sub_frame of the frame of discernment.
     * It includes the belief, disbelief, uncertainty, and relative atomicity
     * for a set of atoms to be exist.
     */
    class Opinion {
    public:
	Opinion();

	/**
	 * Create an opinion based on f.
	 */
	Opinion(const Frame& f, const Sub_frame& sf);
	/**
	   Explicitly sets the parameters of the opinion. Uncertainty is assumed.
	*/
	Opinion(Real belief, Real disbelief, Real base_rate);

	//converts a beta to an opinion. Same idea as Beta::Opinion_Representation
	Opinion(Beta b);

	void set_frame(const Frame& f, const Sub_frame& sf);

	const Real get_belief() const;
	const Real get_disbelief() const;
	const Real get_uncertainty() const;
	const Real get_base_rate() const;

	const Real get_probability_expectation() const;
	
	Beta Beta_Representation() const;

    private:
	Real belief_;
	Real disbelief_;
	Real uncertainty_;
	Real base_rate_;
	Real probability_expectation_;
    };

// Using this, we get free definitions of the other 6 logical and
// ordering operators based off of our definitions of < and ==.
    using namespace std::rel_ops;
}

#endif
