#include "ExponentialRV.hpp"
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <iostream>

using namespace std;

   ExponentialRV::ExponentialRV (int lambda)
   : RandomVariable()
   {
      this->lambda = lambda;
      //upper and lower limits of function set by default parent constructor
   }

   ExponentialRV::ExponentialRV (int lambda, double lowerLimit, double upperLimit)
   : RandomVariable(lowerLimit, upperLimit)
   {
      this->lambda = lambda;
      //call super constructor with the two limits to set the domain
   }

   bool ExponentialRV::setUpperDomain(double upperLimit)
   {
      if (upperLimit < maxUpperLimit && upperLimit >= lowerLimit)
      {
         this->upperLimit = upperLimit;
         return true;
      }
      return false;
   }

   bool ExponentialRV::setLowerDomain(double lowerLimit)
   {
      if (lowerLimit > minLowerLimit && lowerLimit <= upperLimit)
      {
         this->lowerLimit = lowerLimit; 
         return true;
      }
      return false;
   }

   bool ExponentialRV::setDomain(double lowerLimit, double upperLimit)
   {
      if (upperLimit < lowerLimit || lowerLimit < minLowerLimit || upperLimit > maxUpperLimit)
         return false;   //unable to set due to bounds error

      this->lowerLimit = lowerLimit;
      this->upperLimit = upperLimit;
      return true;
   }

   double ExponentialRV::getLowerDomain()
   {
      return this->lowerLimit;
   }

   double ExponentialRV::getUpperDomain()
   {
      return this->upperLimit;
   }

   // possible extension here to allow for PDF evaluation here as well
   bool ExponentialRV::generatePoints (size_t numberOfPoints, vector<double> &data)
   {
      srand(time(NULL));

      for (int i = 0; i < numberOfPoints; i++)
      {
         // generate a number between 0 and 1
         double x_input = (double)rand()/RAND_MAX; //generates number between 0 and 1
         double upper = 1 - (exp(-1 * lambda * upperLimit));
         double lower = 1 - (exp(-1 * lambda * lowerLimit));
         double tmp = lower + (upper - lower) * x_input;
         double result;
         cumulativeProbability(tmp, result);
         data.push_back(result);

         /*// use the number as a percentage and insert into domain 
         x_input *= (upperLimit - lowerLimit);
         x_input += lowerLimit; //ensure number is within the domain
         cout << "input: " << x_input << endl;
      double tmp;
         if(!(this->cumulativeProbability(x_input, tmp)))
            return false;
         cout << "tmp" << tmp << endl;
      data.push_back(tmp);

         */

      }

      return true;
   }

   bool ExponentialRV::cumulativeProbability (double x_value, double& data)
   {
      if (x_value < lowerLimit || x_value > upperLimit)
         return false;

      data = (double)(-1 * (log(1 - x_value)/lambda));
      return true;
   }

   bool ExponentialRV::probabilityAt (double x_value, double& data)
   {
      if (x_value < lowerLimit || x_value > upperLimit)
         return false;

      data = ((double)(-1)/(pow(lambda,2))) * log(x_value);
      return true;
   }

   double ExponentialRV::mean()
   {
      return ((double)1/lambda);
   }

   double ExponentialRV::mean(vector<double>::size_type numberOfPoints)
   {
      if (numberOfPoints == 0)
         return 0;

      vector<double> data(numberOfPoints);
      generatePoints(numberOfPoints, data);
  

      return mean(data, numberOfPoints);
   }

   double ExponentialRV::mean(const vector<double> &data, vector<double>::size_type size)
   {
      double sum = 0;

      for (auto i = 0; i < data.size(); i++)
         sum += data[i];

      cout << sum << endl;
      return sum/(double)size;
   }

   double ExponentialRV::variance()
   {
      return 1/(float)(pow(lambda,2));
   }

   double ExponentialRV::variance(size_t numberOfPoints)
   {
      if (numberOfPoints <= 0)
         return 0;

      vector<double> data(numberOfPoints);
      generatePoints(numberOfPoints, data);

      return variance(data, numberOfPoints);
   }

   double ExponentialRV::variance(const vector<double> &data, vector<double>::size_type size)
   {
      double sum = 0;
      double avg =  mean(data, size);

      cout << "AVG: " << avg << endl;

      for(auto i = 0; i < data.size(); i++)
         sum += pow(data[i] - avg, 2);
      
      return sum/(size - 1);
   }

