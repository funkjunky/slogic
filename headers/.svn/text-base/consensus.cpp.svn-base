#ifndef KENT_CONSENSUS_CPP_
#define KENT_CONSENSUS_CPP_

#include "core.hpp"
#include "beta_opinion.hpp"
#include "consensus.hpp"

#include <iostream>

namespace Subj_logic
{
  	//The following consensus operators were taken from the paper
	//"Exploring Different Types of Trust Propagation" -Josang(2007?)
	class Opinion;
	class Beta_Opinion;

	/**
		Combining observations from two seperate agents that were assumed
		an event in completely different circumstances.
	*/
    Beta_Opinion independant_consensus(const Beta_Opinion& A, const Beta_Opinion& B) throw()
    {
		return Beta_Opinion(A.get_r() + B.get_r()
									, A.get_s() + B.get_s()
									,(A.get_base_rate() * (A.get_r() + A.get_s())
										+ B.get_base_rate() * (B.get_r() + B.get_s()))
									/ (A.get_r() + A.get_s() 
										+ B.get_r() + B.get_s()));
    }
	
	/**
		Combining observations from two seperate agents that were assumed
		to have observed an event in nearly the same circumstances.
	*/
    Beta_Opinion dependant_consensus(const Beta_Opinion& A, const Beta_Opinion& B) throw()
    {
		return Beta_Opinion((A.get_r() + B.get_r()) / 2 
									, (A.get_s() + B.get_s()) / 2
									, (A.get_base_rate() + B.get_base_rate()) / 2);
    }
	
	/**
		Combining observations from two agents who have observed an event
		who shared parts of circumstances.
	*/
    Beta_Opinion partial_consensus(const Beta_Opinion& A, const Beta_Opinion& B, const Real& ADepB, const Real& BDepA) throw()
    {
		Beta_Opinion Ai(A.get_r() * (1 - ADepB)
								, A.get_s() * (1 - ADepB)
								, A.get_base_rate());
		Beta_Opinion Bi(B.get_r() * (1 - BDepA)
								, B.get_s() * (1 - BDepA)
								, B.get_base_rate());
		Beta_Opinion AdB(A.get_r() * ADepB
								, A.get_s() * ADepB
								, A.get_base_rate());
		Beta_Opinion BdA(B.get_r() * BDepA
								, B.get_s() * BDepA
								, B.get_base_rate());

		return independant_consensus(
					independant_consensus(Ai, Bi),
					dependant_consensus(AdB, BdA));
    } 

	/**
		Combining the opinions of two agents about an event where the two 
		agents were in unique circumstances.
	*/
	Opinion independant_consensus(const Opinion& A, const Opinion& B) throw()
	{
		//pg5, if uncertainty = 0, it sounds like you jsut return ANY opinion
		//their function implies B, but I don't think the choice matters.
		if(A.get_uncertainty() == 0 && B.get_uncertainty() == 0)
			return B;

		return Opinion((A.get_belief()*B.get_uncertainty() 
								+ B.get_belief()*A.get_uncertainty())
							/ (A.get_uncertainty() + B.get_uncertainty()
								- A.get_uncertainty()*B.get_uncertainty())
							, (A.get_disbelief()*B.get_uncertainty()
								+ B.get_disbelief()*A.get_uncertainty())
							/ (A.get_uncertainty() + B.get_uncertainty()
								- A.get_uncertainty()*B.get_uncertainty())
							, (A.get_base_rate()*B.get_uncertainty()
								+ B.get_base_rate()*A.get_uncertainty()
								- (A.get_base_rate() + B.get_base_rate())
									* A.get_uncertainty()*B.get_uncertainty())
							/ (A.get_uncertainty() + B.get_uncertainty()
								- 2*A.get_uncertainty()*B.get_uncertainty()));
	}

	/**
		similar circumstances.
	*/
	Opinion dependant_consensus(const Opinion& A, const Opinion& B) throw()
	{
		Real intermediate_b = (A.get_belief() / A.get_uncertainty()
										+ B.get_belief() / B.get_uncertainty());
		Real intermediate_d = (A.get_disbelief() / A.get_uncertainty()
										+	B.get_disbelief() / B.get_uncertainty());

		return Opinion(intermediate_b / (intermediate_b + intermediate_d)
							, intermediate_d / (intermediate_b + intermediate_d)
							, (A.get_base_rate() + B.get_base_rate()) / 2);
	}

	/**
		partially similar, partially unique.
	*/
	Opinion partial_consensus(const Opinion& A, const Opinion& B
										, const Real& AdepB, const Real& BdepA) throw()
	{
		Real rem_AdB = 1 - AdepB;
		Real rem_BdA = 1 - BdepA;

		Real mew_Ai = rem_AdB / (rem_AdB*(A.get_belief() + A.get_disbelief())
											+ A.get_uncertainty());
		Real mew_AdB = AdepB / (AdepB*(A.get_belief() + A.get_disbelief())
											+ A.get_uncertainty());
		Real mew_Bi = rem_BdA / (rem_BdA*(B.get_belief() + B.get_disbelief())
											+ B.get_uncertainty());
		Real mew_BdA = BdepA / (AdepB*(B.get_belief() + B.get_disbelief())
											+ B.get_uncertainty());

		Opinion Ai(A.get_belief() * mew_Ai
						, A.get_disbelief() * mew_Ai
						, A.get_base_rate());
		Opinion AdB(A.get_belief() * mew_AdB
						, A.get_disbelief() * mew_AdB
						, A.get_base_rate());
		Opinion Bi(B.get_belief() * mew_Bi
						, B.get_disbelief() * mew_Bi
						, B.get_base_rate());
		Opinion BdA(B.get_belief() * mew_BdA
						, B.get_disbelief() * mew_BdA
						, B.get_base_rate());

		return independant_consensus(
					independant_consensus(Ai, Bi),
					dependant_consensus(AdB, BdA));
	}
}

#endif
