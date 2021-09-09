#ifndef __SUD_HPP
#define __SUD_HPP

#include <memory>
#include <vector>
#include <iostream>

template<typename Sde, typename Pricer, typename Fdm, typename Rng>
class SUD : private Sde, private Pricer, private Fdm, private Rng
{
    private:
        std::shared_ptr<Sde> sde;
        std::shared_ptr<Pricer> pricer;
        std::shared_ptr<Fdm> fdm;
        std::shared_ptr<Rng> rng; // Random number generator

        // Montecarlo data
        int n_sim;
        std::vector<double> sim_path;

    public:
    SUD() {}
    SUD(const std::shared_ptr<Sde>& s,
        const std::shared_ptr<Pricer>& p,
        const std::shared_ptr<Fdm>& f,
        const std::shared_ptr<Rng>& r,
        int numberSimulations, int NT) : sde(s), pricer(p), fdm(f), rng(r) {
        n_sim = numberSimulations;
        sim_path = std::vector<double>(NT + 1);
    }

    void start() {

        double v_old, v_new;

        for(int i = 1 ; i <= n_sim; ++i) {
            if((i / 100000) * 100000 == 1) {
                std::cout << i << ",";
            }

            v_old = sde->initial_condition();
            sim_path[0] =  v_old;

            // Inner loop can go into another method
            for(size_t n = 1; n < sim_path.size(); ++n){
                v_new = fdm->advance(v_old, fdm->x[n - 1], fdm->k, rng->generate_rn(), rng->generate_rn());
                sim_path[n] = v_new;
                v_old = v_new;
            }

            // send to pricer
            pricer->process_path(sim_path);
            pricer->post_process();
        }
    }
};

#endif