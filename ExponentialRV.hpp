#include "RandomVariable.hpp"

class ExponentialRV: public RandomVariable {

   public:
      ExponentialRV(int);
      ExponentialRV(int,double,double); //lambda, upper, lower limits

      bool setUpperLimit(double);
      bool setLowerLimit(double);
      bool setDomain(double, double);

      double getLowerDomain();
      double getUpperDomain();

      // evaluate PDF/PMF at point and store in result
      bool pdf (double, double&);
      // evaluate CDF at point and store in result 
      bool cdf (double, double&); 

      // create array of points on the object's range for the specified function
      std::vector<double> generatePoints_pdf(std::vector<double>::size_type); 

      std::vector<double> generatePoints_cdf(std::vector<double>::size_type); 

      // theoretical mean, also known as the expectation
      double mean(); 
      // mean of randomly generated points (number of points is specified)
      double mean(std::vector<double>::size_type);
      // mean of specified points
      double mean (const std::vector<double>&, std::vector<double>::size_type);

      // theoretical variance
      double variance();
      // variance of randomly generated points (number of points is specified)
      double variance(std::vector<double>::size_type);
      //variance of specified points
      double variance(const std::vector<double>&, std::vector<double>::size_type);

   private:
      int lambda; //defines the exponential function

      //internal function for generating an array of random points
      std::vector<double> generatePoints(std::vector<double>::size_type); 

};
