#ifndef __PRICER_HPP
#define __PRICER_HPP

#include <concepts>
#include <functional>
#include <vector>

template <typename P, typename Array=std::vector<double>>
concept PricerExecutor = requires(P pricer, Array arr)
{
    pricer.process_path(arr);
    pricer.post_process();
    pricer.discount_factor();
    pricer.price();
};


class Pricer
{

public:

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