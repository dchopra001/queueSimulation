#include "ExponentialRV.hpp"
#include <iostream>

using namespace std;

int main()
{

   ExponentialRV *rv = new ExponentialRV(75, 0,1);
   cout<<"UpperDomain:" << rv->getUpperDomain() << endl;
   cout << "LowerDomain:" << rv->getLowerDomain() << endl;

   vector <double> randomPoints;
   rv->generatePoints(1000, randomPoints);

   cout << "Theoretical mean: " << rv->variance() << endl;

   cout << "Random Points Mean: " << rv->variance(1000) << endl;

   return 0;



}
