#ifndef __GBM_HPP
#define __GBM_HPP

// Simple stochastic diffential equation
class GBM
{
private:
    double mu;      // Drift
    double vol;     // Volatility
    double d;
    double ic;
    double exp;

public:

    GBM() = default;
    GBM(double drift_coefficient,
        double diffusion_coefficient,
        double dividend_yield,
        double initial_condition,
        double expiry)
    {
        mu = drift_coefficient;
        vol = diffusion_coefficient;
        d = dividend_yield;
        ic = initial_condition;
        exp = expiry;
    }

    double drift(const double x, const double t) const
    {
        return (mu - d) * x;
    }

    double diffusion(const double x, const double t) const
    {
        return vol*x;
    }

    double drift_corrected(const double x, const double t, const double B) const
    {
        return drift(x, t) - B * diffusion(x, t) * diffusion_derivative(x, t);
    }

    double diffusion_derivative(const double x, const double t) const
    {
        return vol;
    }

    double initial_condition() const
    {
        return ic;
    }

    double expiry() const 
    {
        return exp;
    }
};

#endif