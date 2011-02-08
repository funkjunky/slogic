/**
 * \todo Do inherited members show up in initializer lists???
 */

#include "subj_logic.hpp"
#include <iostream>
#include <set>

using namespace std;
using namespace Subj_logic;

template <typename T>
T reduce(T data) { return data; }

int main()
{
  // Example D: Reliability Analusis

  Opinion x(Real(41, 100), Real(24, 100), Real(30, 100));
  Opinion y(Real(23, 100), Real(56, 100), Real(11, 100));

  // test out the & operator
  Opinion z = x & y;
  
  // test out the | operator
  Opinion z2 = x | y;

  // test out the + operator
  Opinion z3 = x + y;

  // test out the - operator
  Opinion z4 = x - y;


  
  // now lets see if it gives the correct numbers.
  // these numbers are correct, we tested them using the program on josangs website.
  cout << "x:" << endl
       << "belief: " << reduce(x.get_belief()) << endl
       << "disbelief: " << reduce(x.get_disbelief()) << endl
       << "uncertainty: " << reduce(x.get_uncertainty()) << endl
       << "Atomicity: " << reduce(x.get_base_rate()) << endl
       << "x probability: " << reduce(x.get_probability_expectation()) << endl
	   << "---" << endl;
  cout << "y:" << endl
       << "belief: " << reduce(y.get_belief()) << endl
       << "disbelief: " << reduce(y.get_disbelief()) << endl
       << "uncertainty: " << reduce(y.get_uncertainty()) << endl
       << "Atomicity: " << reduce(y.get_base_rate()) << endl
       << "y probability: " << reduce(y.get_probability_expectation()) << endl
	   << "---" << endl;
  cout << "x & y:" << endl
       << "belief: " << reduce(z.get_belief()) << endl
       << "disbelief: " << reduce(z.get_disbelief()) << endl
       << "uncertainty: " << reduce(z.get_uncertainty()) << endl
       << "Atomicity: " << reduce(z.get_base_rate()) << endl
       << "z probability: " << reduce(z.get_probability_expectation()) << endl
	   << "---" << endl;
  cout << "x | y:" << endl
       << "belief: " << reduce(z2.get_belief()) << endl
       << "disbelief: " << reduce(z2.get_disbelief()) << endl
       << "uncertainty: " << reduce(z2.get_uncertainty()) << endl
       << "Atomicity: " << reduce(z2.get_base_rate()) << endl
       << "z probability: " << reduce(z2.get_probability_expectation()) << endl
	   << "---" << endl;
  cout << "x + y:" << endl
       << "belief: " << reduce(z3.get_belief()) << endl
       << "disbelief: " << reduce(z3.get_disbelief()) << endl
       << "uncertainty: " << reduce(z3.get_uncertainty()) << endl
       << "Atomicity: " << reduce(z3.get_base_rate()) << endl
       << "z probability: " << reduce(z3.get_probability_expectation()) << endl
	   << "---" << endl;
  cout << "x - y:" << endl
       << "belief: " << reduce(z4.get_belief()) << endl
       << "disbelief: " << reduce(z4.get_disbelief()) << endl
       << "uncertainty: " << reduce(z4.get_uncertainty()) << endl
       << "Atomicity: " << reduce(z4.get_base_rate()) << endl
       << "z probability: " << reduce(z4.get_probability_expectation()) << endl
	   << "---" << endl;
}
