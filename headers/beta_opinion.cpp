/**
	@file beta_opinion.Cpp
	@brief Beta Opinion relative code
	This holds the definition of the Beta_Opinion class, as well
	as the functions key to Beta_Opinions.
*/
#ifndef KENT_BETA_OPINION_CPP_
#define KENT_BETA_OPINION_CPP_

#include "core.hpp"
#include "beta.hpp"
#include "beta_opinion.hpp"
#include <algorithm>

namespace Subj_logic
{
	//@class Beta_Opinion
	//This holds an opinion based on evidence for and against an event.
			Beta_Opinion::Beta_Opinion(Real r, Real s, Real a) 
				: Beta(r, s, a), Opinion(belief(r,s), disbelief(r,s), a)
			{ }
	 
	//These were pulled form page 21 from "A Logic for Uncertain Probabilities" -Josang(2000)
	Real belief(const Real& r, const Real& s)
	{
		return r / (r + s + 2);
	}

	Real disbelief(const Real& r, const Real& s)
	{
		return s / (r + s + 2);
	}

	Real uncertainty(const Real& r, const Real& s)
	{
		return 2 / (r + s + 2);
	}

	//Taken from page 19 of "A Logic for Uncertain Probabilities" -Josang(2000)
	Real probability_expectation(const Real& r, const Real& s, const Real& a)
	{
		return (r + 2*a) / (r + s + 2);
	}
}

#endif
