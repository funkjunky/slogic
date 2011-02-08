/**
	@file frame.cpp
	@brief Frame of Discernment relative code.
	This holds a class which holds all information relative to a frame.
	A good example of a frame would be a multiple choice question in a
	survey. It would contain Atoms which would be answers, and an opinion
	on a subframe would represent the opinion on the answers in the subframe.
*/
#ifndef KENT_FRAME_CPP_
#define KENT_FRAME_CPP_

#include "frame.hpp"
#include <boost/rational.hpp>
#include <boost/make_shared.hpp>
#include <sstream>
#include <vector>
#include "atom.hpp"
#include "sub_frame.hpp"
#include "core.hpp"
	
#ifdef DEBUG
	#include <iostream>
#endif

namespace Subj_logic
{
	//forward declarations.
	class Frame;
	class Atom;
	class Sub_frame;

			Frame::Frame()
				: atoms_()
				, sub_frames_()
			{}

			const std::vector<AtomPtr>& Frame::atoms() const
			{
				return atoms_;
			}
			const std::vector<Sub_framePtr>& Frame::sub_frames() const
			{
				return sub_frames_;
			}

			void Frame::register_atom(AtomPtr a) throw()
			{
				atoms_.push_back(a);
			}

			//When we register a sub_Frame, we should continually update the theta mass, assuming it hasn't been explicitly altered yet.
			void Frame::register_sub_frame(Sub_framePtr sf) throw()
			{
				sub_frames_.push_back(sf);
			}

			void Frame::register_theta(Real theta_mass) throw()
			{
			
				register_sub_frame(make_shared<Sub_frame>(atoms_.begin(), atoms_.end(), theta_mass));
			}

			void Frame::clear() throw()
			{
				#ifdef DEBUG
					std::cerr << "beginning of clear..." << std::endl;
				#endif
				for(aIter i = atoms_.begin(); i!=atoms_.end(); ++i)
					i->reset();
				atoms_.clear();
				#ifdef DEBUG
					std::cerr << "ending of clearing atoms..." << std::endl;
				#endif

				for(sIter i = sub_frames_.begin(); i!=sub_frames_.end(); ++i)
					i->reset();
				sub_frames_.clear();
				#ifdef DEBUG
					std::cerr << "ending of clearing subframes..." << std::endl;
				#endif
			}

			std::string Frame::toString() const throw()
			{
				std::ostringstream out; 
				
				out << "Atoms in Frame:" << std::endl;
				for(const_aIter i = atoms_.begin(); i!=atoms_.end(); ++i)
					out << "\t'" << (*i)->label() << "'" << std::endl;
				out << "Subframes in Frame:" << std::endl;
				for(const_sIter i = sub_frames_.begin(); i!=sub_frames_.end(); ++i)
				{
					out << "\tAtoms in Subframe:" << std::endl;
					for(const_aIter k = (*i)->atoms().begin(); k!=(*i)->atoms().end(); ++k)
						out << "\t\t'" << (*k)->label() << "'" << std::endl;
				}
				return out.str();
			}

			//This will do what CleanUpFrame currently does.
			Frame::~Frame()
			{
				clear();
			}

	//This means NOTHING, it is just to stop the compiler form complaining.
	bool operator<(const Frame& a, const Frame& b)
	{
		return a.atoms().size() < b.atoms().size();
	}
}

#endif
