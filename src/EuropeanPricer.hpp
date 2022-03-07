#ifndef __EUROPEAN_PRICER_HPP
#define __EUROPEAN_PRICER_HPP

#include "Pricer.hpp"
#include <iostream>

template <typename Payoff, typename Discounter>
class EuropeanPricer : public Pricer<Payoff, Discounter>
{
private:
    double m_price;
    double sum;
    double n_sim;

public:
    EuropeanPricer() {}
    EuropeanPricer(Payoff& payoff,Discounter& discounter) : Pricer<Payoff,Discounter>(payoff, discounter)
    {
        m_price = sum = 0.0;
        n_sim = 0;
    }

    // Create a single path
    void process_path(const std::vector<double>& arr) {
        sum += Pricer<Payoff,Discounter>::m_payoff(arr.back());
        n_sim++;
    }

    //  Notify the end of a simulation
    void post_process() 
    {
        m_price = discount_factor() * sum / n_sim; 
    }

    double discount_factor()
    {
        return Pricer<Payoff,Discounter>::m_discounter();
    }

    // Option price
    double price()
    {
        return m_price;
    }

};

#endif