/**
	@file beta.cpp
	@brief Beta relative code
	This holds the definition for the Beta class, which is an evidence
	collection of an event.
*/
#ifndef KENT_BETA_CPP_
#define KENT_BETA_CPP_

#include "opinion.hpp"
#include "beta.hpp"

#include "beta_opinion.hpp"

namespace Subj_logic
{
	//@class Beta
	//This holds evidence for and against an event.
			Beta::Beta(Real r, Real s, Real a) 
					:r_(r), s_(s), a_(a)
			{ }

			Beta::Beta(Opinion op) 
					: r_(ev_for_op(op))
					, s_(ev_against_op(op))
					, a_(op.get_base_rate())
			{ }

			Real Beta::get_r() const
			{
				return r_;
			}
			Real Beta::get_s() const
			{
				return s_;
			}
			Real Beta::get_a() const
			{
				return a_;
			}

			Opinion Beta::Opinion_Representation() const
			{
				return Opinion(*this);
			}

	Real ev_for_op(const Opinion& op)
	{
		return 2*op.get_belief() / op.get_uncertainty();
	}

	Real ev_against_op(const Opinion& op)
	{
		return 2*op.get_disbelief() / op.get_uncertainty();
	}
}

#endif
