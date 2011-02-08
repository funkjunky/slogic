/**
	@file beta_opinion.hpp
	@brief Beta Opinion relative code
	This holds the definition of the Beta_Opinion class, as well
	as the functions key to Beta_Opinions.
*/
#ifndef KENT_BETA_OPINION_HPP_
#define KENT_BETA_OPINION_HPP_

#include "core.hpp"
#include "beta.hpp"

namespace Subj_logic
{
	Real disbelief(const Real& r, const Real& s);
	Real belief(const Real& r, const Real& s);
	Real uncertainty(const Real& r, const Real& s);
	Real probability_expectation(const Real& r, const Real& s, const Real& a);

	//@class Beta_Opinion
	//This holds an opinion based on evidence for and against an event.
    class Beta_Opinion: public Beta, public Opinion
    {
	 	public:
			Beta_Opinion(Real r, Real s, Real a) ;
    };
	 
	//These were pulled form page 21 from "A Logic for Uncertain Probabilities" -Josang(2000)
	Real belief(const Real& r, const Real& s);

	Real disbelief(const Real& r, const Real& s);

	Real uncertainty(const Real& r, const Real& s);
}

#endif
