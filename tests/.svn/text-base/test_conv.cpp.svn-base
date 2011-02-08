#include "subj_logic.hpp"
#include "beta_opinion.hpp"
#include <iostream>
#include <set>
#include <vector>

using namespace std;
using namespace Subj_logic;

int main()
{
	Opinion zo1(Real(1,3), Real(1,3), Real(1,2));
	Beta b1(2,2,Real(1,2));

	Beta c_zo1 = zo1.Beta_Representation();
	Opinion c_b1 = b1.Opinion_Representation();

	cout << "zo1, an explicitly made Opinion:" << endl;
	cout << "belief = " << zo1.get_belief() << endl;
	cout << "disbelief = " << zo1.get_disbelief() << endl;
	cout << "uncertainty = " << zo1.get_uncertainty() << endl;
	cout << "rel atomicity = " << zo1.get_base_rate() << endl;
	cout << "zo1, converted to Beta:" << endl;
	cout << "evidence for = " << c_zo1.get_r() << endl;
	cout << "evidence against = " << c_zo1.get_s() << endl;
	cout << "rel atomicity = " << c_zo1.get_a() << endl;
	cout << "c1, converted to Opinion:" << endl;
	cout << "belief = " << c_b1.get_belief() << endl;
	cout << "disbelief = " << c_b1.get_disbelief() << endl;
	cout << "uncertainty = " << c_b1.get_uncertainty() << endl;
	cout << "rel atomicity = " << c_b1.get_base_rate() << endl;
}
