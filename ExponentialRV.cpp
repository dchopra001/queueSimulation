#include "ExponentialRV.hpp"
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>

#include <iostream>

using namespace std;

   /*
   * constructor with one input.
   * inputs
   * @lambda: the defining parameter for an exponential distribution 
   */
   ExponentialRV::ExponentialRV (int lambda)
   {
      this->lambda = lambda;
      //upper and lower limits of theoretical RV
      maxUpperLimit = std::numeric_limits<double>::infinity();
      minLowerLimit = 0;

      upperLimit = maxUpperLimit;
      lowerLimit = minLowerLimit;
      
   }

   /*
   * constructor with three inputs.
   * inputs
   * @lambda: the defining parameter for an exponential distribution
   * @lowerLimit: lower restriction on domain 
   * @upperLimit: upper restriction on domain 
   */
   ExponentialRV::ExponentialRV (int lambda, double lowerLimit, double upperLimit)
   : RandomVariable(lowerLimit, upperLimit)
   {
      this->lambda = lambda;
      //upper and lower limits of theoretical RV
      maxUpperLimit = std::numeric_limits<double>::infinity();
      minLowerLimit = 0;
      //call super constructor with the two limits to set the domain
   }

   /*
   * Setter method for upper limit for PDF/CDF function. If illegal value is
   * provided, then the domain defaults to the global const maxUpperLimit.
   * inputs
   * @upperLimit: upper restriction on PDF/CDF function
   * returns
   * @bool: true if value is legal and set, false otherwise
   */
   bool ExponentialRV::setUpperLimit(double upperLimit)
   {
      if (upperLimit < maxUpperLimit && upperLimit >= lowerLimit)
      {
         this->upperLimit = upperLimit;
         return true;
      }
      return false;
   }

   /*
   * Setter method for lower limit for PDF/CDF function. If illegal value is
   * provided, then the domain defaults to the global const minLowerLimit.
   * inputs
   * @lowerLimit: lower restriction on PDF/CDF function
   * returns
   * @bool: true if value is legal and set, false otherwise
   */
   bool ExponentialRV::setLowerLimit(double lowerLimit)
   {
      if (lowerLimit > minLowerLimit && lowerLimit <= upperLimit)
      {
         this->lowerLimit = lowerLimit; 
         return true;
      }
      return false;
   }

   /*
   * Setter method for domain for PDF/CDF function. If illegal values are
   * provided, then the domain defaults to the global consts for max upper
   * and lower bounds.
   * inputs
   * @lowerLimit: lower restriction on PDF/CDF function to be applied
   * @upperLimit: upper restriction on PDF/CDF to be applied
   * returns
   * @bool: true if values are legal and set, false otherwise
   */
   bool ExponentialRV::setDomain(double lowerLimit, double upperLimit)
   {
      if (upperLimit < lowerLimit || lowerLimit < minLowerLimit || upperLimit > maxUpperLimit)
         return false; 

      this->lowerLimit = lowerLimit;
      this->upperLimit = upperLimit;
      return true;
   }

   /*
   * Getter method for lower domain of PDF/CDF functions
   */
   double ExponentialRV::getLowerDomain()
   {
      return this->lowerLimit;
   }

   /*
   * Getter method for upper domain of PDF/CDF functions
   */
   double ExponentialRV::getUpperDomain()
   {
      return this->upperLimit;
   }

   /*
   * Private method that generates a specified number of uniformly distributed points
   * in the random variable's domain. These points can be used to evaluate the function.
   * inputs
   * @numberOfPoints: total number of points to generate
   * returns
   * @data: vector of uniformly distributed points 
   */
   vector<double> ExponentialRV::generatePoints (vector<double>::size_type numberOfPoints)
   {
      srand(time(NULL));

      double lower = lowerLimit;
      double upper = upperLimit;

      vector<double> data(numberOfPoints);

      for (auto i = 0u; i < numberOfPoints; i++)
      {
         //generates number between 0 and 1
         double x_input = (double)rand()/RAND_MAX; 
         // adjust the data to fit within the domain
         double result = lower + (upper - lower) * x_input;
         data.push_back(result);
      }
      return data;
   }

   vector<double> ExponentialRV::generatePoints_pdf(vector<double>::size_type numberOfPoints)
   {
      vector<double> data = generatePoints(numberOfPoints);

      for (auto i = 0u; i < numberOfPoints; i++)
      {
         pdf(data[i], data[i]);
      }

      return data;
   }

   vector<double> ExponentialRV::generatePoints_cdf(vector<double>::size_type numberOfPoints)
   {
      vector<double> data = generatePoints(numberOfPoints);

      for (auto i = 0u; i < numberOfPoints; i++)
      {
         cdf(data[i], data[i]);
      }

      return data;
   }

   bool ExponentialRV::cdf (double x_value, double& data)
   {
      if (x_value < lowerLimit || x_value > upperLimit)
         return false;

      data = 1 - exp(-1 * lambda * x_value);
      return true;
   }

   bool ExponentialRV::pdf (double x_value, double& data)
   {
      if (x_value < lowerLimit || x_value > upperLimit)
         return false;

      data = lambda * exp(-1 * lambda * x_value);
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

      vector<double> data = generatePoints(numberOfPoints);

      return mean(data, numberOfPoints);
   }

   double ExponentialRV::mean(const vector<double> &data, vector<double>::size_type size)
   {
      double sum = 0;

      for (auto i = 0u; i < data.size(); i++)
         sum += data[i];

      return sum/(double)size;
   }

   double ExponentialRV::variance()
   {
      return 1/(float)(pow(lambda,2));
   }

   double ExponentialRV::variance(vector<double>::size_type numberOfPoints)
   {
      if (numberOfPoints <= 0)
         return 0;

      vector<double> data = generatePoints(numberOfPoints);

      return variance(data, numberOfPoints);
   }

   double ExponentialRV::variance(const vector<double> &data, vector<double>::size_type size)
   {
      double sum = 0;
      double avg =  mean(data, size);

      for(auto i = 0u; i < data.size(); i++)
         sum += pow(data[i] - avg, 2);
      
      return sum/(size - 1);
   }

