#ifndef KENT_CONSENSUS_TEMPLATE_CPP_
#define KENT_CONSENSUS_TEMPLATE_CPP_
#include <boost/rational.hpp>
#include "beta_opinion.hpp"

namespace Subj_logic
{
	/**
		Dependant consensus on a vector of agents observations.
		IMPORTANT: In order to use this function you must define it's use
						As a template prototype ie.:
						template Beta_Opinion dependant_consensus<vector::itr>(...);
	*/
	template <typename Iter>
	Beta_Opinion dependant_consensus(Iter first, Iter last)
	{
		Real sum_r = 0, sum_s = 0, sum_a = 0;
		int count = 0;
		for(Iter i = first; i != last; i++)
		{
			sum_r += i->get_r();
			sum_s += i->get_s();
			sum_a += i->get_base_rate();
			++count;
		}
		
		return Beta_Opinion(sum_r / count
									, sum_s / count
									, sum_a / count);
	}
}
#endif
