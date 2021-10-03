#ifndef __PRICER_HPP
#define __PRICER_HPP

#include <functional>
#include <vector>

template <typename D>
class Pricer
{

public:
    // Create a single path
    void process_path(const std::vector<double>& arr) 
    {
        static_cast<D*>(this)->process_path(arr);
    }

    //  Notify the end of a simulation
    void post_process() 
    {
        static_cast<D*>(this)->post_process();
    }

    // Discount factor
    double discount_factor()
    {
        return static_cast<D*>(this)->discount_factor();
    }

    // Option price
    double price()
    {
        return static_cast<D*>(this)->price();
    }

    std::function<double (double)> m_payoff;
    std::function<double ()> m_discounter;

    Pricer() = default;

    Pricer(const std::function<double (double)>& payoff,
           const std::function<double ()>& discounter) 
    {
        m_payoff = payoff;
        m_discounter = discounter;
    }
};

#endif