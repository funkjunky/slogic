#ifndef KENT_SUBFRAME_TEMPLATES_CPP_
#define KENT_SUBFRAME_TEMPLATES_CPP_

#include "sub_frame.hpp"
#include "atom.hpp"
#include "core.hpp"

#include <boost/rational.hpp>

namespace Subj_logic
{
    using namespace boost;

    //typedef double Real;
    typedef rational<long> Real;

	template <typename Iter>
	Sub_frame::Sub_frame(Iter first, Iter last) :
	    mass_(0), atoms_(first, last)
	{
	}

	///@param mass The atomic belief mass of the atoms.
	template <typename Iter>
	Sub_frame::Sub_frame(Iter first, Iter last, Real mass) :
	    mass_(mass), atoms_(first, last)
	{
	}
}
#endif
