#include "subj_logic.hpp"
#include <iostream>
#include <set>
#include <vector>

using namespace std;
using namespace Subj_logic;

int main()
{
	// set the opinion of A towards the event x
	Opinion A_x (Real(41, 100), Real(24, 100), Real(30, 100));

	// set the trust opinon of all the agents
	Opinion recipient (Real(23, 100), Real(56, 100), Real(11, 100));

	// find out what each recipient ( all things being equal) would think of what A told them
	Opinion recipient_x = uncertainty_discount(recipient, A_x);
	
	// Now we need to find out what happens when R believ that each opinion is independant
	
	Opinion R_x = recipient_x; // R opinon about x after A told him
	for(int i = 0; i < 249; ++i)
	{
		R_x = independant_consensus(R_x, recipient_x);
	}
	
	// Now we need to find out what happens when R believes that each opinion is dependant
/*	
	vector<Opinion> Sp1;
	for(int i = 0; i < 250; i++)
		Sp1.push_back(recipient_x);
		
	Beta_Opinion R_x_dependant = dependant_consensus(Sp1.begin(), Sp1.end());
*/	
	cout << "---" << endl;
	cout << "The opinion of the recipient after only A:" << endl;
	cout << "---" << endl;
	cout << "belief = " << recipient_x.get_belief() << endl;
	cout << "disbelief = " << recipient_x.get_disbelief() << endl;
	cout << "uncertainty = " << recipient_x.get_uncertainty() << endl;
	cout << "rel atomicity = " << recipient_x.get_base_rate() << endl;
	cout << "---" << endl;
	cout << "The opinion of R using independant consensus:" <<endl;
	cout << "---" << endl;
	cout << "belief = " << R_x.get_belief() << endl;
	cout << "disbelief = " << R_x.get_disbelief() << endl;
	cout << "uncertainty = " << R_x.get_uncertainty() << endl;
	cout << "rel atomicity = " << R_x.get_base_rate() << endl;
	cout << "---" << endl;
/*	cout << "The opinion of R using dependant consensus:" <<endl;
	cout << "---" << endl;
	cout << "belief = " << R_x_dependant.get_belief() << endl;
	cout << "disbelief = " << R_x_dependant.get_disbelief() << endl;
	cout << "uncertainty = " << R_x_dependant.get_uncertainty() << endl;
	cout << "rel atomicity = " << R_x_dependant.get_base_rate() << endl;
*/
}
