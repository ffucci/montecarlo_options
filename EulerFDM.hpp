// Euler FDM contains the source for applying Euler Finite-Difference Method for 
// stochastic differential equations 
#ifndef __EULER_FDM_HPP
#define __EULER_FDM_HPP

#include <memory>
#include <vector>

template <typename SDE>
class EulerFDM
{
private:
    std::shared_ptr<SDE> sde;
    int nt;

public:

    std::vector<double> x; // Mesh array
    
    // Mesh size
    double k; 

    double dt_sqrt;

    EulerFDM() = default;
    
    EulerFDM(const std::shared_ptr<SDE>& stochastic_equation,
             int number_subdivisions) : sde(stochastic_equation), nt{number_subdivisions}
    {
        k = sde->expiry();
        dt_sqrt = std::sqrt(k);
        x = std::vector<double>(nt + 1);

        // Create the mesh array
        for(size_t n = 1; n < x.size(); ++n)
        {
            x[n] = x[n - 1] + k;
        }
    }

    double advance(const double xn, const double tn, const double dt, const double normal_var, const double normal_var2) const
    {
        return xn + sde->drift(xn, tn) * dt + sde->diffusion(xn, tn) * dt_sqrt * normal_var;
    }
};

#endif 