#ifndef KENT_DISCOUNTING_CPP_
#define KENT_DISCOUNTING_CPP_

#include "core.hpp"
#include "opinion.hpp"
#include "beta.hpp"
#include "discounting.hpp"

namespace Subj_logic
{
    /**
       @brief Discounts an opinion according to another opinion using 
       Uncertainty Favouring Discounting.
       From page 44 of Josangs first draft of his book:
       A's disbelief in the recommending agent, B, means that A thinks that 
       B ignored the truth value of x. As a result A also ignores the truth
       value of x.
    */
    Opinion uncertainty_discount(const Opinion& OpinionOfB, const Opinion& B) throw()
    {
	return Opinion(
	    OpinionOfB.get_belief() * B.get_belief(),		//belief
	    OpinionOfB.get_belief() * B.get_disbelief(),	//disbelief
	    B.get_base_rate());					//atomicity
    }

    /**
       @brief Discounts an opinion according to another opinion using Opposite 
       Belief Favouring Discounting. From page 45 of Josangs first draft of 
       his book:
       A's disbelief in the recommendation agenti, B, means that A thinks that 
       B consistently recommends the opposite of his real opinion about the 
       truth value of x. As a result, A not only disbelieves in x to the degree 
       that B recommends belief, but she also believes in x to the degree that 
       B recommends disbelief in x, because the combination of two disbeliefs 
       results in belief in this case.
    */
    Opinion opposite_discount(const Opinion& OpinionOfB, const Opinion& B) throw()
    {
	return Opinion(
	    OpinionOfB.get_belief() * B.get_belief()
	    + OpinionOfB.get_disbelief() * B.get_disbelief(),	//belief
	    OpinionOfB.get_belief() * B.get_disbelief()
	    + OpinionOfB.get_disbelief() * B.get_belief(),	//disbelief
	    B.get_base_rate());					//atomicity
    }

    /**
       @brief Discounts an opinion according to another opinion using Base Rate 
       Sensitive Discounting.
       This discounting was created to combat lack of base rate factor for 
       discounting. See section 4.6.3 or page 46 of the first draft of his 
       book 46 for more information.
    */
    Opinion base_rate_discount(const Opinion& OpinionOfB, const Opinion& B) throw()
    {
	return Opinion(
	    OpinionOfB.get_probability_expectation() * B.get_belief(), //belief
	    OpinionOfB.get_probability_expectation() * B.get_disbelief(),  //disbelief
	    B.get_base_rate()); // atomicity
    }
}

#endif
