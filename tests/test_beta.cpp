/**
 * \todo Do inherited members show up in initializer lists???
 */

#include "subj_logic.hpp"
#include "beta_opinion.hpp"
#include <iostream>
#include <set>

using namespace std;
using namespace Subj_logic;

int main()
{
	Beta_Opinion z1(5, 2, Real(1,2));

	cout << "z1, an explicitly made Beta Opinion:" << endl;
	cout << "belief = " << z1.get_belief() << endl;
	cout << "disbelief = " << z1.get_disbelief() << endl;
	cout << "uncertainty = " << z1.get_uncertainty() << endl;
	cout << "rel atomicity = " << z1.get_base_rate() << endl;
}
