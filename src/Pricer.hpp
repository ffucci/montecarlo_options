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

template <typename Payoff, typename Discounter>
class Pricer
{

public:

    Pricer() = default;

    Pricer(Payoff& payoff, Discounter& discounter) : m_payoff(std::forward<Payoff>(payoff)), m_discounter(std::forward<Discounter>(discounter))
    {}

protected:

    Payoff m_payoff;
    Discounter m_discounter;
}; 

#endif