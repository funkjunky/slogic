#include "subj_logic.hpp"
#include <iostream>

using namespace Subj_logic;

struct Predicate : public Atom
{
  Predicate(label_type label)
  {
    label_ = label;
  }
};


using namespace std;

int main()
{
	Frame myFrame;

	AtomPtr a1 = AtomPtr(new Predicate("test1"));
	myFrame.register_atom(a1);
	Sub_framePtr s1 = Sub_framePtr(new Sub_frame(a1, 0.1));
	myFrame.register_sub_frame(s1);

	cout << "myFrame toString:" << endl;
	cout << myFrame.toString() << endl;
}
