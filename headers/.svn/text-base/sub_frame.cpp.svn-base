/**
   @file core.cpp
   @brief Our main header file.
   This holds all of our functions and classes.
   We may seperate this in the future, and if we do we must update
   the documentation.
*/
#ifndef KENT_SUBFRAME_CPP_
#define KENT_SUBFRAME_CPP_

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <utility>

#include "core.hpp"
#include "atom.hpp"
#include "sub_frame.hpp"

#ifdef DEBUG
#include <iostream>
#endif

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
	//-------------------------------------------------------------------------------
    // Class definitions.

    /**
     * @class Sub_frame
     * This class represents a sub-frame: a vector of atoms from
     * the frame of discernment. Sub-frames have belief masses
     * associated to them.
     */
	Sub_frame::Sub_frame() :
	    mass_(0), atoms_()
	{
	}

	///@param mass The atomic belief mass of an atom.
	Sub_frame::Sub_frame(AtomPtr a, Real mass) :
	    mass_(mass), atoms_()
	{
	    atoms_.push_back(a);
	}

	Sub_frame& Sub_frame::operator =(Sub_frame& rhs) 
	{
	    mass_ = rhs.mass_;
	    atoms_ = rhs.atoms_;
	    return *this;
	}

	void Sub_frame::set_mass(Real m) { mass_ = m; }

	const std::vector<AtomPtr>& Sub_frame::atoms() const
	{
	    return atoms_;
	}
	const Real Sub_frame::mass() const
	{
	    return mass_;
	}

	void Sub_frame::clear()
	{
		for(aIter i = atoms_.begin(); i!=atoms_.end(); ++i)
			i->reset();
		atoms_.clear();
	}

	Sub_frame::~Sub_frame()
	{
		clear();
	}

    bool operator <(const Sub_frame& f1, const Sub_frame& f2) throw()
    {
	return &f1 < &f2;
    }

    bool operator ==(const Sub_frame& f1, const Sub_frame& f2) throw()
    {
	return &f1 == &f2;
    }

// Using this, we get free definitions of the other 6 logical and
// ordering operators based off of our definitions of < and ==.
    using namespace std::rel_ops;
}

#endif
