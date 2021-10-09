#ifndef STOCHASTIC_DIFFERENTIAL_EQUATION
#define STOCHASTIC_DIFFERENTIAL_EQUATION

#include <concepts>

template <typename SDE, typename D=double>
concept StochasticDifferentialEquation = requires(SDE sde, D x, D t, D B)
{
    sde.drift(x, t);
    sde.diffusion(x, t);
    sde.drift_corrected(x, t, B);
    sde.diffusion_derivative(x, t);
    sde.initial_condition();
    sde.expiry();
};

#endif