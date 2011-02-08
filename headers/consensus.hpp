#ifndef KENT_CONSENSUS_HPP_
#define KENT_CONSENSUS_HPP_

#include "core.hpp"
#include "beta_opinion.hpp"

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
    Beta_Opinion independant_consensus(const Beta_Opinion& A, const Beta_Opinion& B) throw();
	
	/**
		Combining observations from two seperate agents that were assumed
		to have observed an event in nearly the same circumstances.
	*/
    Beta_Opinion dependant_consensus(const Beta_Opinion& A, const Beta_Opinion& B) throw();

	/**
		Dependant consensus on a vector of agents observations.
	*/
	template <typename Iter>
	Beta_Opinion dependant_consensus(Iter first, Iter last);
	
	/**
		Combining observations from two agents who have observed an event
		who shared parts of circumstances.
	*/
    Beta_Opinion partial_consensus(const Beta_Opinion& A, const Beta_Opinion& B, const Real& ADepB, const Real& BDepA) throw();

	/**
		Combining the opinions of two agents about an event where the two 
		agents were in unique circumstances.
	*/
	Opinion independant_consensus(const Opinion& A, const Opinion& B) throw();

	/**
		similar circumstances.
	*/
	Opinion dependant_consensus(const Opinion& A, const Opinion& B) throw();

	/**
		partially similar, partially unique.
	*/
	Opinion partial_consensus(const Opinion& A, const Opinion& B
										, const Real& AdepB, const Real& BdepA) throw();
}

#ifndef DONTINCLUDEDEFNFORTEMPLATES
	#include "consensus_template_funcs.cpp"
#endif
#endif
