/**
	@file beta.hpp
	@brief Beta relative code
	This holds the definition for the Beta class, which is an evidence
	collection of an event.
*/
#ifndef KENT_BETA_HPP_
#define KENT_BETA_HPP_

#include <boost/rational.hpp>
#include "opinion.hpp"

namespace Subj_logic
{
    typedef boost::rational<long> Real;

	//forward declarations.
	class Opinion;

	//@class Beta
	//This holds evidence for and against an event.
    class Beta
    {
	 	public:
			Beta(Real r, Real s, Real a) ;
			Beta(Opinion op);

			Real get_r() const;
			Real get_s() const;
			Real get_a() const;

			Opinion Opinion_Representation() const;

		protected:
			Real r_;	//The evidence supporting the opinion.
			Real s_;	//The evidence supporting the opinion's negation.
			Real a_;	//Relative Atomicity.
    };

	Real ev_for_op(const Opinion& op);
	Real ev_against_op(const Opinion& op);
}

#endif
