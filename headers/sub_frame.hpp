/**
   @file core.hpp
   @brief Our main header file.
   This holds all of our functions and classes.
   We may seperate this in the future, and if we do we must update
   the documentation.
*/
#ifndef KENT_SUBFRAME_HPP_
#define KENT_SUBFRAME_HPP_

#include <vector>
#include <string>
#include <stdexcept>

#include "beta.hpp"
#include "atom.hpp"
#include "core.hpp"

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

   // Forward declarations.

    // Classes.

    class Atom;

   //-------------------------------------------------------------------------------
    // Class definitions.
    /**
     * @class Sub_frame
     * This class represents a sub-frame: a vector of atoms from
     * the frame of discernment. Sub-frames have belief masses
     * associated to them.
     */
    class Sub_frame {
    public:
	Sub_frame();

	///@param mass The atomic belief mass of an atom.
	Sub_frame(AtomPtr a, Real mass);

	template <typename Iter>
	Sub_frame(Iter first, Iter last);

	///@param mass The atomic belief mass of the atoms.
	template <typename Iter>
	Sub_frame(Iter first, Iter last, Real mass);

	Sub_frame& operator =(Sub_frame& rhs);

	void set_mass(Real m);

	const std::vector<AtomPtr>& atoms() const;
	const Real mass() const;

	~Sub_frame();

    private:
	Real mass_;
	std::vector<AtomPtr> atoms_;

	protected:
		void clear();
    };

	//operators
    bool operator <(const Sub_frame&, const Sub_frame&) throw();
    bool operator ==(const Sub_frame&, const Sub_frame&) throw();

// Using this, we get free definitions of the other 6 logical and
// ordering operators based off of our definitions of < and ==.
    using namespace std::rel_ops;
}

#ifndef DONOTINCLUDETEMPLATEFUNCTIONSFORSUBFRAMES
	#include "sub_frame_template_funcs.cpp"
#endif

#endif
