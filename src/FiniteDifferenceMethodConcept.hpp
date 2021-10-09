#ifndef FINITE_DIFFERENCE_METHOD
#define FINITE_DIFFERENCE_METHOD

template <typename Method>
concept MethodSDE = requires(Method method, const double xn, const double tn, const double dt, const double normal_var, const double normal_var2){
    method.advance(xn, tn, dt, normal_var, normal_var2);
};

#endif