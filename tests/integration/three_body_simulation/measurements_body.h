#pragma once

#include <pkr_units/si_units.h>
#include <pkr_units/math/4d/vector_4d.h>
#include <pkr_units/math/measurements/measurement_math_rss.h>
#include <pkr_units/math/measurement_math_4d.h>
#include <array>
#include <cmath>
#include <vector>

namespace three_body_measurements
{

// Gravitational constant (in km^3 / (kg * s^2))
constexpr double G = 6.67430e-20;

// Helper to create position vector (w=1)
inline pkr::units::vec_4d_t<double> make_position(double x, double y, double z)
{
    return pkr::units::vec_4d_t<double>{x, y, z, 1};
}

// Helper to create direction vector (w=0)
inline pkr::units::vec_4d_t<double> make_direction(double x, double y, double z)
{
    return pkr::units::vec_4d_t<double>{x, y, z, 0};
}

struct Body
{
    using Position = pkr::units::vec_4d_t<pkr::units::measurement_t<pkr::units::kilometer_t>>;

    Position position; // position in km with uncertainty (w=1)
    Position velocity; // velocity in km/s (w=0)
    double mass;       // mass in kg

    Body(pkr::units::vec_4d_t<double> pos, pkr::units::vec_4d_t<double> vel, double m)
        : position{pkr::units::measurement_t<pkr::units::kilometer_t>{pos.x, std::abs(pos.x * 0.001)}, pkr::units::measurement_t<pkr::units::kilometer_t>{pos.y, std::abs(pos.y * 0.001)}, pkr::units::measurement_t<pkr::units::kilometer_t>{pos.z, std::abs(pos.z * 0.001)}, pkr::units::measurement_t<pkr::units::kilometer_t>{pos.w, 0.0}}
        , velocity{pkr::units::measurement_t<pkr::units::kilometer_t>{vel.x, 0.0}, pkr::units::measurement_t<pkr::units::kilometer_t>{vel.y, 0.0}, pkr::units::measurement_t<pkr::units::kilometer_t>{vel.z, 0.0}, pkr::units::measurement_t<pkr::units::kilometer_t>{vel.w, 0.0}}
        , mass(m)
    {
    }
};

class ThreeBodySystem
{
public:
    ThreeBodySystem(const std::vector<Body>& bodies)
        : bodies(bodies)
    {
    }

    // Calculate acceleration of body i due to other two bodies
    pkr::units::vec_4d_t<double> acceleration(size_t i) const
    {
        pkr::units::vec_4d_t<double> acc = make_direction(0, 0, 0);
        auto pos_i = make_position(bodies[i].position.x.value().value(), bodies[i].position.y.value().value(), bodies[i].position.z.value().value());

        for (size_t j = 0; j < bodies.size(); ++j)
        {
            if (i != j)
            {
                auto pos_j = make_position(bodies[j].position.x.value().value(), bodies[j].position.y.value().value(), bodies[j].position.z.value().value());
                auto r_vec = pos_j - pos_i;
                double r_sq = r_vec.x * r_vec.x + r_vec.y * r_vec.y + r_vec.z * r_vec.z;
                double r = std::sqrt(r_sq);
                if (r > 1e-10)
                {
                    double factor = G * bodies[j].mass / (r_sq * r);
                    acc = acc + r_vec * (factor / r);
                }
            }
        }
        return acc;
    }

    // 4th order Runge-Kutta integration step
    void rk4_step(double dt)
    {
        size_t n = bodies.size();
        std::vector<pkr::units::vec_4d_t<double>> k1_vel(n), k1_acc(n);
        std::vector<pkr::units::vec_4d_t<double>> k2_vel(n), k2_acc(n);
        std::vector<pkr::units::vec_4d_t<double>> k3_vel(n), k3_acc(n);
        std::vector<pkr::units::vec_4d_t<double>> k4_vel(n), k4_acc(n);

        // k1
        for (size_t i = 0; i < n; ++i)
        {
            k1_vel[i] = make_direction(bodies[i].velocity.x.value().value(), bodies[i].velocity.y.value().value(), bodies[i].velocity.z.value().value());
            k1_acc[i] = acceleration(i);
        }

        // k2
        std::vector<Body> temp_bodies = bodies;
        for (size_t i = 0; i < n; ++i)
        {
            // Position update with error propagation via measurement math
            temp_bodies[i].position.x = bodies[i].position.x + pkr::units::measurement_t<pkr::units::kilometer_t>{k1_vel[i].x * (dt / 2.0), 0.0};
            temp_bodies[i].position.y = bodies[i].position.y + pkr::units::measurement_t<pkr::units::kilometer_t>{k1_vel[i].y * (dt / 2.0), 0.0};
            temp_bodies[i].position.z = bodies[i].position.z + pkr::units::measurement_t<pkr::units::kilometer_t>{k1_vel[i].z * (dt / 2.0), 0.0};
            temp_bodies[i].velocity = bodies[i].velocity + k1_acc[i] * (dt / 2.0);
        }
        std::swap(bodies, temp_bodies);
        for (size_t i = 0; i < n; ++i)
        {
            k2_vel[i] = make_direction(bodies[i].velocity.x.value().value(), bodies[i].velocity.y.value().value(), bodies[i].velocity.z.value().value());
            k2_acc[i] = acceleration(i);
        }
        std::swap(bodies, temp_bodies);

        // k3
        for (size_t i = 0; i < n; ++i)
        {
            // Position update with error propagation via measurement math
            temp_bodies[i].position.x = bodies[i].position.x + pkr::units::measurement_t<pkr::units::kilometer_t>{k2_vel[i].x * (dt / 2.0), 0.0};
            temp_bodies[i].position.y = bodies[i].position.y + pkr::units::measurement_t<pkr::units::kilometer_t>{k2_vel[i].y * (dt / 2.0), 0.0};
            temp_bodies[i].position.z = bodies[i].position.z + pkr::units::measurement_t<pkr::units::kilometer_t>{k2_vel[i].z * (dt / 2.0), 0.0};
            temp_bodies[i].velocity = bodies[i].velocity + k2_acc[i] * (dt / 2.0);
        }
        std::swap(bodies, temp_bodies);
        for (size_t i = 0; i < n; ++i)
        {
            k3_vel[i] = make_direction(bodies[i].velocity.x.value().value(), bodies[i].velocity.y.value().value(), bodies[i].velocity.z.value().value());
            k3_acc[i] = acceleration(i);
        }
        std::swap(bodies, temp_bodies);

        // k4
        for (size_t i = 0; i < n; ++i)
        {
            // Position update with error propagation via measurement math
            temp_bodies[i].position.x = bodies[i].position.x + pkr::units::measurement_t<pkr::units::kilometer_t>{k3_vel[i].x * dt, 0.0};
            temp_bodies[i].position.y = bodies[i].position.y + pkr::units::measurement_t<pkr::units::kilometer_t>{k3_vel[i].y * dt, 0.0};
            temp_bodies[i].position.z = bodies[i].position.z + pkr::units::measurement_t<pkr::units::kilometer_t>{k3_vel[i].z * dt, 0.0};
            temp_bodies[i].velocity = bodies[i].velocity + k3_acc[i] * dt;
        }
        std::swap(bodies, temp_bodies);
        for (size_t i = 0; i < n; ++i)
        {
            k4_vel[i] = make_direction(bodies[i].velocity.x.value().value(), bodies[i].velocity.y.value().value(), bodies[i].velocity.z.value().value());
            k4_acc[i] = acceleration(i);
        }
        std::swap(bodies, temp_bodies);

        // Update
        for (size_t i = 0; i < n; ++i)
        {
            // Position update with error propagation via measurement math
            bodies[i].position.x = bodies[i].position.x + pkr::units::measurement_t<pkr::units::kilometer_t>{
                                                              (k1_vel[i].x + k2_vel[i].x * 2.0 + k3_vel[i].x * 2.0 + k4_vel[i].x) * (dt / 6.0), 0.0};
            bodies[i].position.y = bodies[i].position.y + pkr::units::measurement_t<pkr::units::kilometer_t>{
                                                              (k1_vel[i].y + k2_vel[i].y * 2.0 + k3_vel[i].y * 2.0 + k4_vel[i].y) * (dt / 6.0), 0.0};
            bodies[i].position.z = bodies[i].position.z + pkr::units::measurement_t<pkr::units::kilometer_t>{
                                                              (k1_vel[i].z + k2_vel[i].z * 2.0 + k3_vel[i].z * 2.0 + k4_vel[i].z) * (dt / 6.0), 0.0};
            bodies[i].velocity = bodies[i].velocity + (k1_acc[i] + k2_acc[i] * 2.0 + k3_acc[i] * 2.0 + k4_acc[i]) * (dt / 6.0);
        }
    }

    // Calculate total energy in the system
    double total_energy() const
    {
        double kinetic_energy = 0.0;
        for (const auto& body : bodies)
        {
            double v_sq = body.velocity.x * body.velocity.x + body.velocity.y * body.velocity.y + body.velocity.z * body.velocity.z;
            kinetic_energy += 0.5 * body.mass * v_sq;
        }

        double potential_energy = 0.0;
        for (size_t i = 0; i < bodies.size(); ++i)
        {
            for (size_t j = i + 1; j < bodies.size(); ++j)
            {
                double dx = bodies[j].position.x.value().value() - bodies[i].position.x.value().value();
                double dy = bodies[j].position.y.value().value() - bodies[i].position.y.value().value();
                double dz = bodies[j].position.z.value().value() - bodies[i].position.z.value().value();
                double dist = std::sqrt(dx * dx + dy * dy + dz * dz);
                if (dist > 1e-10)
                {
                    potential_energy -= G * bodies[i].mass * bodies[j].mass / dist;
                }
            }
        }

        return kinetic_energy + potential_energy;
    }

    const std::vector<Body>& get_bodies() const
    {
        return bodies;
    }

private:
    mutable std::vector<Body> bodies;
};

} // namespace three_body_measurements
