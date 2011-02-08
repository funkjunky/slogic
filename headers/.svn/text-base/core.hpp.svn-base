/**
   @file core.hpp
   @brief Our main header file.
   This holds all of our functions and classes.
   We may seperate this in the future, and if we do we must update
   the documentation.
*/
#ifndef KENT_SLOGIC_HPP_
#define KENT_SLOGIC_HPP_

#include <vector>
#include <string>
#include <stdexcept>

#include <boost/rational.hpp>
#include <boost/shared_ptr.hpp>

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

    // Forward Classe declarations.

    class Atom;
    class Sub_frame;
    class Opinion;
	class Frame; 

    //-------------------------------------------------------------------------------
    // Typedefs.

    //typedef double Real;
    typedef rational<long> Real;
		typedef shared_ptr<Atom> AtomPtr;
		typedef shared_ptr<Sub_frame> Sub_framePtr;
		typedef std::vector<AtomPtr>::iterator aIter;
		typedef std::vector<Sub_framePtr>::iterator sIter;
		typedef std::vector<AtomPtr>::const_iterator const_aIter;
		typedef std::vector<Sub_framePtr>::const_iterator const_sIter;


    //-------------------------------------------------------------------------------
    // Exceptions.

    struct Invalid_BMA {
    };
  
    struct Empty_frame : std::runtime_error {
	Empty_frame() 
	    : std::runtime_error("Empty frame")
	{
	}
    };
	
	//I tried forward declaring the exception in Opinion, but the compiler
	//was being a bitch and saying it was incomplete, blah blah
	//so now the full declaration is in Opinion. It was only one line anyways
    //struct Out_of_Range{};

    //-------------------------------------------------------------------------------
    // Forward declarations.


    // Functions.

    Real belief(const Frame&, const Sub_frame&) throw();
    Real disbelief(const Frame&, const Sub_frame&) throw();
    Real uncertainty(const Frame&, const Sub_frame&) throw();

    Real atomicity(const Frame&, const Sub_frame&) throw();
    Real atomicity(const Sub_frame&, const Sub_frame&) throw();

    bool check_BMA() throw();

    Real probability_expectation(const Frame&, const Sub_frame&) throw();
    Real probability_expectation(const Opinion&) throw();

    //-------------------------------------------------------------------------------
    // Global variables.

    ///Atoms_ represents the global Frame of Discernment
	
    std::vector<Atom*>& Atoms_();
	
    ///Sub_frames_ represents the powerset of the Frame of Discernment.
    ///It is assumed that is an element of the powerset of Atoms_ does
    ///not exist, then it's belief mass is 0.
    std::vector<Sub_frame>& Sub_frames_();

    //-------------------------------------------------------------------------------
    // Helper functions. Consider wrapping them in a seperate namespace.

    // Consider moving this to a sub-namespace for helper functions.
    template <typename T>
    bool is_subset(const std::vector<T>& x, const std::vector<T>& y);

    //-------------------------------------------------------------------------------
    // Function definitions: belief, disbelief, uncertainty, atomicity, and
    // probability expectation.

    /**
     * This function computes the belief in x, based on the definition
     * in the paper.
     * @param x The frame to compute the belief of.
     */
    Real belief(const Sub_frame& x) throw();

    /**
     * This function computes the disbelief in the frame x
     * based on the definition in the paper.
     * @param x The frame to compute the disbelief of.
     */
    Real disbelief(const Sub_frame& x) throw();
    
    /**
     * This function computes the uncertainty of x
     * based on the identity b(x) + d(x) + u(x) = 1.
     * @param x The frame to compute the disbelief of.
     */
    Real uncertainty(const Sub_frame& x) throw();

    /**
     * This function computes the atomicity of x with
     * respect to the entire frame of discernment.
     * @param x The frame to compute the atomicity of.
     */
    Real atomicity(const Sub_frame& x) throw();

    /**
     * This function computes the atomicity of x with respect
     * to y.
     * @param x The subframe to compute the relative atomicity of.
     * @param y The subframe of reference.
     *
     * This should not return an exeption on empty frame y, it should
     * return 0
     * - Gilles
     */
    Real atomicity(const Sub_frame& x, const Sub_frame& y) throw();

    Real probability_expectation(const Sub_frame& sub_frame) throw();

    /**
       @brief Determines the probability expectation of an opinion.
       Interpolating from page 17 (eqn 12), justified considering the 
       rearrangement on page 6 (eqn 4) all from 
       A Logic for Uncertain Probability.
    */
    Real probability_expectation(const Opinion& opinion) throw();

    /*
     * This function implements division as defined in the paper
     * `Multiplication and Co-multiplication of Beliefs`.
     */
    Opinion divide(const Opinion& x, const Opinion& y) throw();

    /*
     * This function implements co-division as defined in the paper
     * `Multiplication and Co-multiplication of Beliefs`.
     */
    Opinion co_divide(const Opinion& x, const Opinion& y) throw();
	
    //-------------------------------------------------------------------------------
    // Overloaded operators.

// Using this, we get free definitions of the other 6 logical and
// ordering operators based off of our definitions of < and ==.
    using namespace std::rel_ops;
}

#endif
