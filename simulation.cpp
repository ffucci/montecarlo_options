#include "EuropeanPricer.hpp"
#include "SUD.hpp"
#include "GBM.hpp"
#include "Rng.hpp"
#include "EulerFDM.hpp"

#include <memory>
#include <utility>
#include <cmath>

int main()
{
    // int num_sim = 1'000'000;
    int num_sim = 20'000;
    int nt = 500;

    double drift_coefficient = 0.08;
    double diffusion_coefficient = 0.3;

    double dividend_yield = 0.0;
    double initial_condition = 60.0;
    double expiry = 0.25;

    auto sde = std::make_shared<GBM>(drift_coefficient, 
                                     diffusion_coefficient, 
                                     dividend_yield, 
                                     initial_condition, 
                                     expiry);
    
    double K = 65.0;

    // Factories for objects in context diagram
    std::function<double(double)> payoffPut = [&K](double x) { return std::max<double>(0.0, K - x); };
    std::function<double(double)> payoffCall = [&K](double x){ return std::max<double>(0.0, x - K); };
    double r = 0.08; double T = 0.25;
    std::function<double()> discounter = [&r, &T](){ return std::exp(-r * T); };
    
    auto pricer_call = std::shared_ptr<Pricer<EuropeanPricer>>(new EuropeanPricer(payoffCall, discounter));
    auto pricer_put = std::shared_ptr<Pricer<EuropeanPricer>>(new EuropeanPricer(payoffPut, discounter));

    auto fdm = std::shared_ptr<EulerFDM<GBM>>(new EulerFDM(sde, nt));

    auto rng_pm = std::shared_ptr<Rng<PolarMarsaglia>>(new PolarMarsaglia());
    auto rng_cpp = std::shared_ptr<Rng<CPPRng>>(new CPPRng());
  
    SUD<GBM, Pricer<EuropeanPricer>, EulerFDM<GBM>, Rng<CPPRng>> sud(sde, pricer_put, fdm, rng_cpp, num_sim, nt);
    sud.start();

    std::cout << "C++ rng: " << pricer_put->price() << '\n';
    return 0;
}