#include "subj_logic.hpp"
#include "beta_opinion.hpp"
#include <iostream>
#include <set>
#include <vector>

using namespace std;
using namespace Subj_logic;

typedef vector<Beta_Opinion>::iterator V_ITER;
template Beta_Opinion dependant_consensus<V_ITER>(V_ITER, V_ITER);

int main()
{
	Beta_Opinion z1(5, 2, Real(1,2));
	Beta_Opinion z2(2, 7, Real(1,4));
	Beta_Opinion z3(8, 8, Real(1,4));
	Opinion zo1(Real(1,3), Real(1,3), Real(1,2));
	Opinion zo2(Real(1,3), Real(1,3), Real(1,2));
	Opinion zo3(Real(2,10), Real(2,10), Real(1,2));

	vector<Beta_Opinion> zset;
	zset.push_back(z1);
	zset.push_back(z2);
	zset.push_back(z3);

	Opinion zo1_i_zo2 = independant_consensus(zo1, zo2);
	Opinion zo1_d_zo2 = dependant_consensus(zo1, zo2);
	Opinion zo1_p_zo2 = partial_consensus(zo1, zo2, Real(1,2), Real(1,2));

	Beta_Opinion z1_i_z2 = independant_consensus(z1, z2);
	Beta_Opinion z1_d_z2 = dependant_consensus(z1, z2);
	Beta_Opinion z1_p_z2 = partial_consensus(z1, z2, Real(1,2), Real(1,2));
	Beta_Opinion set_d_consensus
						= dependant_consensus(zset.begin(), zset.end());

	cout << "---" << endl;
	cout << "First, the Opinion tests:" << endl;
	cout << "---" << endl;
	cout << "zo1, an explicitly made Opinion:" << endl;
	cout << "belief = " << zo1.get_belief() << endl;
	cout << "disbelief = " << zo1.get_disbelief() << endl;
	cout << "uncertainty = " << zo1.get_uncertainty() << endl;
	cout << "rel atomicity = " << zo1.get_base_rate() << endl;
	cout << "zo2, an explicitly made Opinion:" << endl;
	cout << "belief = " << zo2.get_belief() << endl;
	cout << "disbelief = " << zo2.get_disbelief() << endl;
	cout << "uncertainty = " << zo2.get_uncertainty() << endl;
	cout << "rel atomicity = " << zo2.get_base_rate() << endl;
	cout << "zo3, an explicitly made Opinion:" << endl;
	cout << "belief = " << zo3.get_belief() << endl;
	cout << "disbelief = " << zo3.get_disbelief() << endl;
	cout << "uncertainty = " << zo3.get_uncertainty() << endl;
	cout << "rel atomicity = " << zo3.get_base_rate() << endl;
	cout << "zo1 independent consensus with zo2:" << endl;
	cout << "belief = " << zo1_i_zo2.get_belief() << endl;
	cout << "disbelief = " << zo1_i_zo2.get_disbelief() << endl;
	cout << "uncertainty = " << zo1_i_zo2.get_uncertainty() << endl;
	cout << "rel atomicity = " << zo1_i_zo2.get_base_rate() << endl;
	cout << "zo1 fully dependent consensus with zo2:" << endl;
	cout << "belief = " << zo1_d_zo2.get_belief() << endl;
	cout << "disbelief = " << zo1_d_zo2.get_disbelief() << endl;
	cout << "uncertainty = " << zo1_d_zo2.get_uncertainty() << endl;
	cout << "rel atomicity = " << zo1_d_zo2.get_base_rate() << endl;
	cout << "zo1 partially dependent consensus with zo2 (50%,50%):" << endl;
	cout << "belief = " << zo1_p_zo2.get_belief() << endl;
	cout << "disbelief = " << zo1_p_zo2.get_disbelief() << endl;
	cout << "uncertainty = " << zo1_p_zo2.get_uncertainty() << endl;
	cout << "rel atomicity = " << zo1_p_zo2.get_base_rate() << endl;
	cout << endl;
	cout << "---" << endl;
	cout << "Second, the Beta Opinion tests:" << endl;
	cout << "---" << endl;
	cout << "z1, an explicitly made Beta Opinion:" << endl;
	cout << "belief = " << z1.get_belief() << endl;
	cout << "disbelief = " << z1.get_disbelief() << endl;
	cout << "uncertainty = " << z1.get_uncertainty() << endl;
	cout << "rel atomicity = " << z1.get_base_rate() << endl;
	cout << "z2, an explicitly made Beta Opinion:" << endl;
	cout << "belief = " << z2.get_belief() << endl;
	cout << "disbelief = " << z2.get_disbelief() << endl;
	cout << "uncertainty = " << z2.get_uncertainty() << endl;
	cout << "rel atomicity = " << z2.get_base_rate() << endl;
	cout << "z3, an explicitly made Beta Opinion:" << endl;
	cout << "belief = " << z3.get_belief() << endl;
	cout << "disbelief = " << z3.get_disbelief() << endl;
	cout << "uncertainty = " << z3.get_uncertainty() << endl;
	cout << "rel atomicity = " << z3.get_base_rate() << endl;
	cout << "z1 independent consensus with z2:" << endl;
	cout << "belief = " << z1_i_z2.get_belief() << endl;
	cout << "disbelief = " << z1_i_z2.get_disbelief() << endl;
	cout << "uncertainty = " << z1_i_z2.get_uncertainty() << endl;
	cout << "rel atomicity = " << z1_i_z2.get_uncertainty() << endl;
	cout << "z1 fully dependent consensus with z2:" << endl;
	cout << "belief = " << z1_d_z2.get_belief() << endl;
	cout << "disbelief = " << z1_d_z2.get_disbelief() << endl;
	cout << "uncertainty = " << z1_d_z2.get_uncertainty() << endl;
	cout << "rel atomicity = " << z1_d_z2.get_uncertainty() << endl;
	cout << "z1 partially dependent consensus with z2 (50%,50%):" << endl;
	cout << "belief = " << z1_p_z2.get_belief() << endl;
	cout << "disbelief = " << z1_p_z2.get_disbelief() << endl;
	cout << "uncertainty = " << z1_p_z2.get_uncertainty() << endl;
	cout << "rel atomicity = " << z1_p_z2.get_uncertainty() << endl;
	cout << "z1 fully dependent consensus with z2 and z3:" << endl;
	cout << "belief = " << set_d_consensus.get_belief() << endl;
	cout << "disbelief = " << set_d_consensus.get_disbelief() << endl;
	cout << "uncertainty = " << set_d_consensus.get_uncertainty() << endl;
	cout << "rel atomicity = " << set_d_consensus.get_uncertainty() << endl;
}
