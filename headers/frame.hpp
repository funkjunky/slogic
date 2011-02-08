/**
	@file frame.hpp
	@brief Frame of Discernment relative code.
	This holds a class which holds all information relative to a frame.
	A good example of a frame would be a multiple choice question in a
	survey. It would contain Atoms which would be answers, and an opinion
	on a subframe would represent the opinion on the answers in the subframe.
*/
#ifndef KENT_FRAME_HPP_
#define KENT_FRAME_HPP_

#include <vector>
#include <boost/rational.hpp>
#include "atom.hpp"
#include "sub_frame.hpp"
#include "core.hpp"

namespace Subj_logic
{
    typedef boost::rational<long> Real;

	//forward declarations.
	class Atom;
	class Sub_frame;

	class Frame
	{
		public:
			Frame();

			const std::vector<AtomPtr>& atoms() const;
			const std::vector<Sub_framePtr>& sub_frames() const;

			void register_atom(AtomPtr a) throw();
			void register_sub_frame(Sub_framePtr sf) throw();
			void register_theta(Real theta_mass) throw();
			void clear() throw();

			std::string toString() const throw();

			//This will do what CleanUpFrame currently does.
			~Frame();
		protected:
			std::vector<AtomPtr> atoms_;
			std::vector<Sub_framePtr> sub_frames_;
	};

	bool operator<(const Frame& a, const Frame& b);
}

#endif
