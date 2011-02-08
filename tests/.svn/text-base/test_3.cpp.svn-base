/**
 * \todo Do inherited members show up in initializer lists???
 */

#include "subj_logic.hpp"
#include <iostream>
#include <set>
#include <boost/make_shared.hpp>

using namespace Subj_logic;
using namespace std;

struct Predicate : public Atom
{
  Predicate(label_type label)
  {
    label_ = label;
  }
};

template <typename T>
T reduce(T data) { return data; }

int main()
{
	Frame f;

  // the following example is taken from Josang's "A Logic for Uncertain Probabilaty" on page 12
  // there are 9 balls in this example
  AtomPtr p1(new Predicate("Red Ball"));
  AtomPtr p2(new Predicate("Blue Ball"));
  AtomPtr p3(new Predicate("Pink Ball"));
  AtomPtr p4(new Predicate("Black Ball"));
  AtomPtr p5(new Predicate("White Ball"));
  AtomPtr p6(new Predicate("Brown Ball"));
  AtomPtr p7(new Predicate("Yellow Ball"));
  AtomPtr p8(new Predicate("Green Ball"));
  AtomPtr p9(new Predicate("Orange Ball"));

  f.register_atom(p1);
  f.register_atom(p2);
  f.register_atom(p3);
  f.register_atom(p4);
  f.register_atom(p5);
  f.register_atom(p6);
  f.register_atom(p7);
  f.register_atom(p8);
  f.register_atom(p9);

  // now we need to set the subframes
  set<AtomPtr> Sp1;
  Sp1.insert(p1);
  Sp1.insert(p4);
  Sp1.insert(p7);

  set<AtomPtr> Sp2;
  Sp2.insert(p2);
  Sp2.insert(p3);
  Sp2.insert(p5);
  Sp2.insert(p6);
  Sp2.insert(p8);
  Sp2.insert(p9);

  set<AtomPtr> Sp3;
  Sp3.insert(p1);
  Sp3.insert(p2);
  Sp3.insert(p3);

  set<AtomPtr> Sp4;
  Sp4.insert(p4);
  Sp4.insert(p5);
  Sp4.insert(p6);
  Sp4.insert(p7);
  Sp4.insert(p8);
  Sp4.insert(p9);

  f.register_sub_frame(make_shared<Sub_frame>(
								p1, Real(2, 8)));
  f.register_sub_frame(make_shared<Sub_frame>(
								Sp1.begin(), Sp1.end(), Real(1, 8)));
  f.register_sub_frame(make_shared<Sub_frame>(
								Sp2.begin(), Sp2.end(), Real(2, 8)));
  f.register_sub_frame(make_shared<Sub_frame>(
								Sp3.begin(), Sp3.end(), 0));
  f.register_sub_frame(make_shared<Sub_frame>(
								Sp4.begin(), Sp4.end(), 0));

  f.register_theta(Real(3, 8));

	//testing a random value. I'll try some more examples at a later time.
	//mostly just ensuring no runtime errors, or extremely irregular results.
  //Opinion z10(f2);
	Opinion z10(Real(1,3), Real(1,3), Real(1,2));
	Opinion o_of_obs (Real(1,3), Real(1, 3), Real(1, 2)); //opinion of observer.
	Opinion u_discount = uncertainty_discount(o_of_obs, z10);
	Opinion o_discount = opposite_discount(o_of_obs, z10);
	Opinion a_discount = base_rate_discount(o_of_obs, z10);
  
	cout << "Opinion of either 2, 3, 5, 6, 8, or 9 being chosen:" << endl;
	cout << "Belief: "		<< reduce(z10.get_belief()) << endl;
	cout << "Disbelief: "	<< reduce(z10.get_disbelief()) << endl;
	cout << "Uncertainty: "	<< reduce(z10.get_uncertainty()) << endl;
	cout << "Base Rate: "	<< reduce(z10.get_base_rate()) << endl;
	cout << endl;
	cout << "Opinion of the observer for the above opinon:" << endl;
	cout << "Belief: "		<< reduce(o_of_obs.get_belief()) << endl;
	cout << "Disbelief: "	<< reduce(o_of_obs.get_disbelief()) << endl;
	cout << "Uncertainty: "	<< reduce(o_of_obs.get_uncertainty()) << endl;
	cout << "Base Rate: "	<< reduce(o_of_obs.get_base_rate()) << endl;
	cout << endl;
	cout << "a's opinion of f1, after considering a's opinion of the "
			<< "observer." << endl;
	cout << endl;
	cout << "Uncertainty Discount:" << endl;
	cout << "Belief: "		<< reduce(u_discount.get_belief()) << endl;
	cout << "Disbelief: "	<< reduce(u_discount.get_disbelief()) << endl;
	cout << "Uncertainty: "	<< reduce(u_discount.get_uncertainty()) << endl;
	cout << "Base Rate: "	<< reduce(u_discount.get_base_rate()) << endl;
	cout << endl;
	cout << "Opposite Discount:" << endl;
	cout << "Belief: "		<< reduce(o_discount.get_belief()) << endl;
	cout << "Disbelief: "	<< reduce(o_discount.get_disbelief()) << endl;
	cout << "Uncertainty: "	<< reduce(o_discount.get_uncertainty()) << endl;
	cout << "Base Rate: "	<< reduce(o_discount.get_base_rate()) << endl;
	cout << endl;
	cout << "Base Rate Discount:" << endl;
	cout << "Belief: "		<< reduce(a_discount.get_belief()) << endl;
	cout << "Disbelief: "	<< reduce(a_discount.get_disbelief()) << endl;
	cout << "Uncertainty: "	<< reduce(a_discount.get_uncertainty()) << endl;
	cout << "Base Rate: "	<< reduce(a_discount.get_base_rate()) << endl;
	cout << endl;
}
