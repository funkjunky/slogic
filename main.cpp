//Main interface for collecting data to form opinions and betas
//Currently it is setup to only take Betas
 //
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <utility>
#include <algorithm>
#include <sstream>
#include <boost/make_shared.hpp>

#include "subj_logic.hpp"

using namespace std;
using namespace Subj_logic;

//Only the Beta states are currently being used.
//All functions using hte opinions have been gaurded from use with exceptions.
enum CLIState {
	ENTRYSELECT, STATSPACE
	, ANOTHERFRAME
	//if Opinion is selcted:
	, ATOMS
	, SF_BYNAME
	, SF_BMASS, SF_ENDCHECK 
	//if evidence is selected:
	, EV_R, EV_S, EV_A, EV_ENDCHECK
	//State to exit loop.
	, ENDSTATE
};

struct Predicate : public Atom
{
  Predicate(label_type label)
  {
    label_ = label;
  }
};

map<Frame, vector<Beta> > Betas;

map<CLIState, string (*)(CLIState&,istringstream&)> StateOperations;
map<CLIState, string> StateMessages;

//Obsolete thus far.
string EntrySelect(CLIState& CurrentState, istringstream& in)
{
	throw domain_error("This function 'EntrySelect' is not currently in use.");
	string input;
	in >> input;
	if(input == "x")
	{
		throw string("Subj_Logic: XML Input Not Implemented Yet");
	}
	else if(input == "i")
	{
		CurrentState = STATSPACE;
		return "Data Input selected...";
	}
	else
		return "Input was not a valid command. Choose either 'i' or 'e'.";
}

//Obsolete thus far.
string StatSpace(CLIState& CurrentState, istringstream& in)
{
	throw domain_error("This function 'EntrySelect' is not currently in use.");
	string input;
	in >> input;
	if(input == "e")
	{
		CurrentState = EV_R;
		return "Entering Evidence Space Input Mode...";
	}
	else if(input == "o")
	{
		CurrentState = ATOMS;
		return "Entering Opinion Space Input Mode...";
	}
	else
		return "Input was not a valid command. Choose either 'e' or 'o'.";
}

//Obsolete thus far.
string Subframe_Entrytype(CLIState& CurrentState, istringstream& in)
{
	throw domain_error("This function 'EntrySelect' is not currently in use.");
	string input;
	in >> input;
	if(input == "i")
	{
		//commented out, because it is out of service.
		//CurrentState = SF_BYINDEX;
		return "Going into subframe creation mode using atom indices...";
	}
	else if(input == "n")
	{
		CurrentState = SF_BYNAME;
		return "Going into subframe creation mode using atom names...";
	}
	else
		return "You entered an invalid input. Either 'i' or 'n'.";
}

class Build_Frame
{
	typedef set<AtomPtr>::iterator	 			set_aIter;
	typedef set<AtomPtr>::const_iterator		const_set_aIter;
	typedef set<Sub_framePtr>::iterator			set_sIter;
	typedef set<Sub_framePtr>::const_iterator	const_set_sIter;
	public:
	static string Atoms(CLIState& CurrentState, istringstream& in)
	{
		string input;
		in >> input;
		if(input != "$$")
		{
			f.register_atom(make_shared<Predicate>(input));
			return "Atom Successfully registered...";
		}
		else
		{
			CurrentState = EV_R; 
			ostringstream prep;
			prep << "Done entering Atoms..." << endl
					<< "Atoms entered in the frame are:" << endl;
			for(const_aIter pos = f.atoms().begin(); pos != f.atoms().end(); ++pos)
				prep << "\"" << (*pos)->label() << "\" ";
			prep << endl;
			return prep.str();
		}
	}

	static string AnotherFrame(CLIState& CurrentState, istringstream& in)
	{
		cerr << "in AnotherFrame..." << endl;
		string input;
		in >> input;
		if(input == "y")
		{
			cerr << "in y option..." << endl;
			CurrentState = ATOMS;
			clear();
			return "Frame cleared... starting a new frame...";
		}
		else if(input == "n")
		{
			cerr << "in n option..." << endl;
			CurrentState = ENDSTATE;
			clear();
			return "Frame cleared... done entering frames...";
		}
		else
			return "Invalid input... try y or n...";
	}

	class Build_Sub_Frame
	{
		public:
		//out of service thus far.
		static string SF_Byname(CLIState& CurrentState, istringstream& in)
		{
			throw domain_error("This function 'EntrySelect' is not currently in use.");
			string input;
			in >> input;
			if(input != "$$")
			{
				for(const_aIter pos = f.atoms().begin(); pos!=f.atoms().end(); ++pos) {
					if((*pos)->label() == input) {
						frame_subset.insert(*pos);
						return "Atom entered into subframe...";
					}
				}
				return "Atom not found in frame...";
			}
			else
			{
				CurrentState = SF_BMASS;
				ostringstream prep;
				prep << "Done entering Atoms for subframe..." << endl
						<< "Atoms entered into subframe include:" << endl;
				for(const_set_aIter pos = frame_subset.begin(); pos != frame_subset.end(); ++pos)
					prep << "\"" << (*pos)->label() << "\" ";
				prep << endl;
				return prep.str();
			}
		}
	
		//out of service thus far.
		static string SF_Bmass(CLIState& CurrentState, istringstream& in)
		{
			throw domain_error("This function 'EntrySelect' is not currently in use.");
			Real input;
			in >> input;
			frame_bmass = input;
			CurrentState = SF_ENDCHECK;
			return "Belief Mass set for Opinion...";
		}
	
		//This state registers the subframe and stores the opinion.
		//maybe it shouldn't, but any idea I come up with that is better,
		//would take longer than I'm willing to take to develop.

		//out of service thus far.
		static string SF_Endcheck(CLIState& CurrentState, istringstream& in)
		{
			throw domain_error("This function 'EntrySelect' is not currently in use.");
			string input;
			in >> input;
			addSubframeAndClear();
			if(input == "y")
			{
				CurrentState = SF_BYNAME;
				return "Subframe registered...";
			}
			else if(input == "n")
			{
				CurrentState = ENDSTATE;
				return "Subframe registered...\nSo normally we would use this information to do stuff, however currently I'm waiting on building a sortof DSS, so for now it ends here.";
			}
			else
				return "You did not enter a valid input. Either 'y' or 'n'.";
		}

		private:
		Build_Sub_Frame()
		{}
	
		//out of service (basically obsolete thus far)
		static void addSubframeAndClear()
		{
			throw domain_error("This function 'EntrySelect' is not currently in use.");
			
			f.register_sub_frame(make_shared<Sub_frame>(frame_subset.begin(), frame_subset.end(), frame_bmass));
	
			frame_subset.clear();
			frame_bmass = NULL;
		}

		static set<AtomPtr> frame_subset;
		static Real frame_bmass;
	};


	class Build_Beta
	{
		public:
		static string EV_r(CLIState& CurrentState, istringstream& in)
		{
			Real input;
			in >> input;
			r = input;
			CurrentState = EV_S;
			return "Evidence Registered...";
		}
	
		static string EV_s(CLIState& CurrentState, istringstream& in)
		{
			Real input;
			in >> input;
			s = input;
			CurrentState = EV_A;
			return "Evidence Against Registered...";
		}
	
		static string EV_a(CLIState& CurrentState, istringstream& in)
		{
			Real input;
			in >> input;
			a = input;
			CurrentState = EV_ENDCHECK;
			return "Relative Atomicity of the event Registered...";
		}
	
		static string EV_endCheck(CLIState& CurrentState, istringstream& in)
		{
			string input;
			in >> input;
			string successOutput = "Beta prepared and appended to evidence space...\n";
			if(input == "y")
			{
				addEvidenceAndClear();
				CurrentState = EV_R;
				successOutput += "Preparing for another Beta(set of evidence) to be added.";
				return successOutput;
			}
			else if(input == "n")
			{
				addEvidenceAndClear();
				CurrentState = ANOTHERFRAME;
				successOutput += "End of input, until we add more things and such... Have a good day.";
				return successOutput;
			}
			else
				return "You did not enter a correct command. Either 'y', or 'n'.";
		}

		private:
		Build_Beta()
		{}	

		static void addEvidenceAndClear()
		{
			Betas[f].push_back(Beta(r,s,a));
			r = s = a = 0;
		}

		static Real r;
		static Real s;
		static Real a;
	};
	
	private:
	Build_Frame()
	{}
	
	static void clear()
	{
		f.clear();
	}

	static Frame f;
};

	Frame Build_Frame::f;

		set<AtomPtr> Build_Frame::Build_Sub_Frame::frame_subset;
		Real Build_Frame::Build_Sub_Frame::frame_bmass;

	//TODO: Try using namespace Build_Frame::Build_Beta or some shortcut.
		Real Build_Frame::Build_Beta::r;
		Real Build_Frame::Build_Beta::s;
		Real Build_Frame::Build_Beta::a;

void initializeInterface()
{
	StateMessages.insert(make_pair(ENTRYSELECT, "Enter [x] if you want to input a file using XML, and [i] if you would like to go through the interactive menu for adding information."));
	StateOperations.insert(make_pair(ENTRYSELECT,
		&EntrySelect));

	StateMessages.insert(make_pair(STATSPACE,
		"Enter [e] if you want to prepare information for the evidence space, and [o] if you want to enter information for the opinion space."));
	StateOperations.insert(make_pair(STATSPACE,
		&StatSpace));

	StateMessages.insert(make_pair(ATOMS,
		"Enter a name for the atom. When you are done enter '$$'."));
	StateOperations.insert(make_pair(ATOMS,
		&Build_Frame::Atoms));

	//StateMessages.insert(make_pair(SUBFRAME_ENTRYTYPE,
	//	"To add atom's to the subframe using numerical indices in the same order you added atoms enter [i], if you want to add atoms using their names enter [n]."));
	//StateOperations.insert(make_pair(SUBFRAME_ENTRYTYPE,
	//	&Subframe_Entrytype));

	//StateMessages.insert(make_pair(SF_BYINDEX, 
	//	"Enter the index of the atom you wish to add to the sub frame. Enter '$$' when you're done."));
	//StateOperations.insert(make_pair(SF_BYINDEX,
	//	&(Build_Frame::Build_Sub_Frame::SF_Byindex)));

	StateMessages.insert(make_pair(SF_BYNAME,
		"Enter the name of the atom you wish to add to the sub frame. Enter '$$' when you're done."));
	StateOperations.insert(make_pair(SF_BYNAME,
		&(Build_Frame::Build_Sub_Frame::SF_Byname)));

	StateMessages.insert(make_pair(SF_BMASS,
		"Enter the Belief mass for this sub frame."));
	StateOperations.insert(make_pair(SF_BMASS,
		&(Build_Frame::Build_Sub_Frame::SF_Bmass)));

	StateMessages.insert(make_pair(SF_ENDCHECK,
		"Do you wish to create another sub frame? [y/n]"));
	StateOperations.insert(make_pair(SF_ENDCHECK,
		&(Build_Frame::Build_Sub_Frame::SF_Endcheck)));

	StateMessages.insert(make_pair(EV_R,
		"Enter the Evidence For this Beta."));
	StateOperations.insert(make_pair(EV_R,
		&(Build_Frame::Build_Beta::EV_r)));

	StateMessages.insert(make_pair(EV_S,
		"Enter the Evidence Against this Beta."));
	StateOperations.insert(make_pair(EV_S,
		&(Build_Frame::Build_Beta::EV_s)));

	StateMessages.insert(make_pair(EV_A,
		"Enter the Relative Atomicity for this beta."));
	StateOperations.insert(make_pair(EV_A,
		&(Build_Frame::Build_Beta::EV_a)));

	StateMessages.insert(make_pair(EV_ENDCHECK,
		"Do you wish to create another Beta? [y/n]"));
	StateOperations.insert(make_pair(EV_ENDCHECK,
		&(Build_Frame::Build_Beta::EV_endCheck)));
	
	StateMessages.insert(make_pair(ANOTHERFRAME,
		"Do you wish to create another Frame? [y/n]"));
	StateOperations.insert(make_pair(ANOTHERFRAME,
		&(Build_Frame::AnotherFrame)));
}

int main()
{
	initializeInterface();

	//put the statemachine in the first state.
	CLIState CurrentState = ATOMS;

	string temp;
	while(CurrentState != ENDSTATE)
	{
		cout << StateMessages[CurrentState] << endl;
		cin >> (temp = "");
		istringstream in(temp);
		cout << StateOperations[CurrentState](CurrentState, in) << endl;
	}
}
