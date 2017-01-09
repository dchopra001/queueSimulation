#include <limits>
#include <vector>
#include <stddef.h>

class RandomVariable {

   public:
      RandomVariable() {};

      RandomVariable(double lowerLimit, double upperLimit): lowerLimit(lowerLimit), upperLimit(upperLimit) { };

      ~RandomVariable() {};

      virtual bool setUpperLimit(double) = 0;
      virtual bool setLowerLimit(double) = 0;
      virtual bool setDomain(double, double) = 0;

      virtual double getLowerDomain() = 0;
      virtual double getUpperDomain() = 0;
      
      // generate a vector of random points for the specified function
      virtual std::vector<double> generatePoints_pdf(std::vector<double>::size_type) = 0;
      
      virtual std::vector<double> generatePoints_cdf(std::vector<double>::size_type) = 0;

      // evaluate PDF/PMF at x and store in result
      virtual bool pdf (double, double&) = 0;
      // evaluate CDF at x and store in result 
      virtual bool cdf (double, double&) = 0; 

      // theoretical mean, also known as the expectation
      virtual double mean() = 0; 
      // mean of randomly generated points (number of points is specified)
      virtual double mean(std::vector<double>::size_type) = 0;
      // mean of specified points
      virtual double mean (const std::vector<double>&, std::vector<double>::size_type) = 0;

      // theoretical variance
      virtual double variance() = 0;
      // variance of randomly generated points (number of points is specified)
      virtual double variance(std::vector<double>::size_type)= 0;
      //variance of specified points
      virtual double variance(const std::vector<double>&, std::vector<double>::size_type) = 0;

   protected:
      double maxUpperLimit; // these two consts represent the domain under which this random variable
      double minLowerLimit; // is THEORETICALLY defined

      double lowerLimit; //these two represent the user imposed domain on the random variable currently
      double upperLimit; //by default they take the value of the theoretical max/min [0,inf)
};
