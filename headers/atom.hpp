/**
   @file core.hpp
   @brief Our main header file.
   This holds all of our functions and classes.
   We may seperate this in the future, and if we do we must update
   the documentation.
*/
#ifndef KENT_ATOM_HPP_
#define KENT_ATOM_HPP_

#include <set>
#include <vector>
#include <string>
#include <stdexcept>

#include "beta.hpp"

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
	class Atom;

    //-------------------------------------------------------------------------------
    // Typedefs.

    //typedef double Real;
    typedef rational<long> Real;

	//Forward declaring operators for Atoms
    bool operator <(const Atom&, const Atom&) throw();
    bool operator ==(const Atom&, const Atom&) throw();


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
    class Atom {
    public:
	typedef std::string label_type;
	const label_type label() const;

	Atom& operator =(Atom& rhs);
#ifdef DEBUG
	~Frame();
#endif 

    protected:
	label_type label_;
    };

// Using this, we get free definitions of the other 6 logical and
// ordering operators based off of our definitions of < and ==.
    using namespace std::rel_ops;
}

#endif
