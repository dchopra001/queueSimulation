#include "ExponentialRV.hpp"
#include <iostream>

using namespace std;

int main()
{
   ExponentialRV *rv = new ExponentialRV(75, 0,9);
   cout << "UpperDomain:" << rv->getUpperDomain() << endl;
   cout << "LowerDomain:" << rv->getLowerDomain() << endl;

   vector <double> randomPoints;
   //rv->generatePoints(1000, randomPoints);

   cout << "Theoretical Variance: " << rv->mean() << endl;

   cout << "Random Points Variance: " << rv->mean(1000) << endl;

   return 0;
}
