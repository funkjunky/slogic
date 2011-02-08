/**
   @file core.cpp
   @brief Our main header file.
   This holds all of our functions and classes.
   We may seperate this in the future, and if we do we must update
   the documentation.
*/
#ifndef KENT_SLOGIC_CPP_
#define KENT_SLOGIC_CPP_

#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <utility>

#include "atom.hpp"
#include "beta.hpp"

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

    /**
     * @class Atom
     * This class represents the smallest element type
     * in the library. Essentially all it is is a 'thingie'
     * with a label. Atoms are used to make up the more
     * important objects: Sub_frames.
     *
     * If you wish to use custom-types in the frame,
     * have those custom-types inherit publically from
     * Atom.
     */
	typedef std::string label_type;
	const label_type Atom::label() const
	{
	    return label_;
	}

	Atom& Atom::operator =(Atom& rhs)
	{
	    label_ = rhs.label_;
	    return *this;
	}

#ifdef DEBUG
	Atom::~Atom()
	{
		cerr << "In Atom Destructor for Atom with label: " << label_ << endl;
	}
#endif

    bool operator <(const Atom& a, const Atom& b) throw()
    {
	// Arbitrary check. If the labels are different sizes, then
	// It will make the difference here.
	return sizeof(a) < sizeof(b);
    }

    bool operator ==(const Atom& a, const Atom& b) throw()
    {
	return a.label() == b.label();
    }


// Using this, we get free definitions of the other 6 logical and
// ordering operators based off of our definitions of < and ==.
    using namespace std::rel_ops;
}

#endif
