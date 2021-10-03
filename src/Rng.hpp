#ifndef __RNG_HPP
#define __RNG_HPP

#include <random>

template <typename D>
class Rng
{
public:
    double generate_rn()
    {
        return static_cast<D*>(this)->generate_rn();
    }
};

class PolarMarsaglia: public Rng<PolarMarsaglia>
{ // Only for educational purposes
private:
    std::default_random_engine dre;
    std::uniform_real_distribution<double> unif;
public:
    PolarMarsaglia (): dre(std::default_random_engine()),
    
    unif(std::uniform_real_distribution<double>(0.0, 1.0)) {}

    double generate_rn()
    {
        double u, v, S;
        do
        {
            u = 2.0 * unif(dre) - 1.0;
            v = 2.0 * unif(dre) - 1.0;
            S = u * u + v * v;
        } while (S > 1.0 || S <= 0.0);
        double fac = std::sqrt(-2.0 * std::log(S) / S);
        return u * fac;
    }
};

class CPPRng : public Rng<CPPRng>
{ // C++11 versions
private:
    // Normal (0,1) rng
    std::default_random_engine dre;
    std::normal_distribution<double> nor;

public:
    CPPRng() : dre(std::default_random_engine()),
    nor(std::normal_distribution<double>(0.0, 1.0)) {}
    double generate_rn()
    {
        return nor(dre);
    }
};

#endif