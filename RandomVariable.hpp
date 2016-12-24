#include <limits>
#include <vector>
#include <stddef.h>

class RandomVariable {

   public:
      RandomVariable(): lowerLimit(minLowerLimit), upperLimit(maxUpperLimit) {};

      RandomVariable(double lowerLimit, double upperLimit)
      {
         this->lowerLimit = lowerLimit;
         this->upperLimit = upperLimit;
      }

      ~RandomVariable() {};

      virtual bool setUpperDomain(double) = 0;
      virtual bool setLowerDomain(double) = 0;
      virtual bool setDomain(double, double) = 0;

      virtual double getLowerDomain() = 0;
      virtual double getUpperDomain() = 0;
      
      // create array of points on the object's range
      virtual bool generatePoints(size_t, std::vector<double>&) = 0; 

      // evaluate PDF/PMF at x and store in result
      virtual bool probabilityAt (double, double&) = 0;
      // evaluate CDF at x and store in result 
      virtual bool cumulativeProbability (double, double&) = 0; 

      // theoretical mean, also known as the expectation
      virtual double mean() = 0; 
      // mean of randomly generated points (number of points is specified)
      virtual double mean(size_t) = 0;
      // mean of specified points
      virtual double mean (const std::vector<double>&, size_t) = 0;

      // theoretical variance
      virtual double variance() = 0;
      // variance of randomly generated points (number of points is specified)
      virtual double variance(size_t)= 0;
      //variance of specified points
      virtual double variance(const std::vector<double>&, size_t) = 0;

   protected:
      const double maxUpperLimit = std::numeric_limits<double>::infinity();
      const double minLowerLimit = 0;

      double lowerLimit;
      double upperLimit; //domain restrictions, if uninitialized then [0,inf)
      
};

