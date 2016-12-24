#include "RandomVariable.hpp"

class ExponentialRV: public RandomVariable {

   public:
      ExponentialRV(int);
      ExponentialRV(int,double,double);


      bool setUpperDomain(double);
      bool setLowerDomain(double);
      bool setDomain(double, double);

      double getLowerDomain();
      double getUpperDomain();
      
      // create array of points on the object's range
      bool generatePoints(size_t, std::vector<double>&); 

      // evaluate PDF/PMF at point and store in result
      bool probabilityAt (double, double&);
      // evaluate CDF at point and store in result 
      bool cumulativeProbability (double, double&); 

      // theoretical mean, also known as the expectation
      double mean(); 
      // mean of randomly generated points (number of points is specified)
      double mean(size_t);
      // mean of specified points
      double mean (const std::vector<double>&, size_t);

      // theoretical variance
      double variance();
      // variance of randomly generated points (number of points is specified)
      double variance(size_t);
      //variance of specified points
      double variance(const std::vector<double>&, size_t);

   private:
      int lambda; //defines the exponential function

};
