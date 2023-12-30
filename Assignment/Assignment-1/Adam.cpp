//
// Created by Roberto Sala on 12/09/23.
//

#include "Adam.h"
#include <random>
#include <cmath>


std::vector<int> Adam::create_batch() {

    std::vector<int> indices;

    for (std::size_t i = 0; i < dim_batch; ++i)
        indices.push_back(distribution(generator));

    return indices;

}


double Adam::evaluate_batch(const Point &parameters, const std::vector<int> & batch) const {

    double value = 0.0;

    for (const auto i : batch)
        value += f.evaluate(observations[i], parameters);

    return value / batch.size();

}


double Adam::evaluate_partial_derivative_batch(std::size_t j, const Point &parameters, const std::vector<int> & batch) const {

    double value = 0.0;

    for(const auto i : batch) {
        value += f.evaluate_partial_derivative(j, observations[i], parameters);
    }

    return value / batch.size();

}


void Adam::set_f(const FunctionRn &f_) {

    f = f_;

}


void Adam::set_observations(const std::vector<Point> &observations_) {

    observations = observations_;

}


void Adam::set_dim_batch(unsigned int dim_batch_) {

    dim_batch = dim_batch_;

}


void Adam::set_tolerance(double tolerance_) {

    tolerance = tolerance_;

}


void Adam::set_max_iterations(unsigned int max_iterations_) {

    max_iterations = max_iterations_;

}


void Adam::set_inf_limits(const std::vector<double> &inf_limits_) {

    inf_limits = inf_limits_;

}


void Adam::set_sup_limits(const std::vector<double> &sup_limits_) {

    sup_limits = sup_limits_;

}


const FunctionRn & Adam::get_f() const {

    return f;

}


const std::vector<Point> & Adam::get_observations() const {

    return observations;

}


unsigned int Adam::get_dim_batch() const {

    return dim_batch;

}


double Adam::get_tolerance() const {

    return tolerance;

}


unsigned int Adam::get_max_iterations() const {

    return max_iterations;

}


const std::vector<double> & Adam::get_inf_limits() const {

    return inf_limits;

}


const std::vector<double> & Adam::get_sup_limits() const {

    return sup_limits;

}


Point Adam::solve(const Point &initial_parameters) {

    Point theta, m, v;
    for (size_t i=0; i<initial_parameters.get_dimension(); ++i) {

        // copy parameters (check if they are in range)
        double par = initial_parameters.get_coordinate(i);
        if (par<inf_limits[i]) {
            theta.set_coordinate(i, inf_limits[i]);
        }
        else {
            theta.set_coordinate(i, par);
        }
        if (par>sup_limits[i]) {
            theta.set_coordinate(i, sup_limits[i]);
        }
        else {
            theta.set_coordinate(i, par);
        }

        // initialize m and v
        m.set_coordinate(i, 0.0);
        v.set_coordinate(i, 0.0);

    }

    unsigned t = 0;

    bool flag = false;

    while (!flag && t<max_iterations) {

        ++t;

        // extract a batch
        std::vector<int> indexes = create_batch();

        Point g, m_hat, v_hat, theta_new;

        for (size_t i=0; i<theta.get_dimension(); ++i) {

            // evaluate the gradient
            g.set_coordinate(i, evaluate_partial_derivative_batch(i, theta, indexes));

            // first and second moment estimate
            m.set_coordinate(i, gamma1*m.get_coordinate(i)+(1-gamma1)*g.get_coordinate(i));
            v.set_coordinate(i, gamma2*v.get_coordinate(i)+(1-gamma2)*pow(g.get_coordinate(i),2));

            // m hat and v hat
            m_hat.set_coordinate(i, m.get_coordinate(i)/(1-pow(gamma1, t)));
            v_hat.set_coordinate(i, v.get_coordinate(i)/(1-pow(gamma2, t)));

            // actual parameters (check if they are in range)
            double par = theta.get_coordinate(i)-(alpha*m_hat.get_coordinate(i)/(sqrt(v_hat.get_coordinate(i))+epsilon));
            if (g.get_coordinate(i)>0) {
                theta_new.set_coordinate(i, std::max(par, inf_limits[i]));
            }
            else {
                theta_new.set_coordinate(i, std::min(par, sup_limits[i]));
            }

        }

        // check if convergence is reached
        if (theta_new.distance(theta)<tolerance || abs(evaluate_batch(theta_new, indexes)-evaluate_batch(theta, indexes))<tolerance) {
            flag = true;
        }

        // update parameters
        for (size_t i=0; i<theta.get_dimension(); ++i) {
            theta.set_coordinate(i, theta_new.get_coordinate(i));
        }

    }

    return theta;

}
