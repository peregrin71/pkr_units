#pragma once

#include <pkr_units/math/4d/vector_4d.h>
#include <pkr_units/constants.h>
#include <array>
#include <cmath>
#include <vector>

namespace three_body_double
{

// Gravitational constant (in m^3 / (kg * s^2)), converted to km^3 / (kg * s^2)
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
    pkr::units::vec_4d_t<double> position; // position in km (w=1)
    pkr::units::vec_4d_t<double> velocity; // velocity in km/s (w=0)
    double mass;                           // mass in kg

    Body(pkr::units::vec_4d_t<double> pos, pkr::units::vec_4d_t<double> vel, double m)
        : position(pos)
        , velocity(vel)
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
        for (size_t j = 0; j < bodies.size(); ++j)
        {
            if (i != j)
            {
                double dx = bodies[j].position.x - bodies[i].position.x;
                double dy = bodies[j].position.y - bodies[i].position.y;
                double dz = bodies[j].position.z - bodies[i].position.z;
                double r_sq = dx * dx + dy * dy + dz * dz;
                double r = std::sqrt(r_sq);
                if (r > 1e-10)
                {
                    double factor = G * bodies[j].mass / (r_sq * r);
                    acc.x += factor * dx;
                    acc.y += factor * dy;
                    acc.z += factor * dz;
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
            k1_vel[i] = bodies[i].velocity;
            k1_acc[i] = acceleration(i);
        }

        // k2
        std::vector<Body> temp_bodies = bodies;
        for (size_t i = 0; i < n; ++i)
        {
            temp_bodies[i].position = bodies[i].position + k1_vel[i] * (dt / 2.0);
            temp_bodies[i].velocity = bodies[i].velocity + k1_acc[i] * (dt / 2.0);
        }
        std::swap(bodies, temp_bodies);
        for (size_t i = 0; i < n; ++i)
        {
            k2_vel[i] = bodies[i].velocity;
            k2_acc[i] = acceleration(i);
        }
        std::swap(bodies, temp_bodies);

        // k3
        for (size_t i = 0; i < n; ++i)
        {
            temp_bodies[i].position = bodies[i].position + k2_vel[i] * (dt / 2.0);
            temp_bodies[i].velocity = bodies[i].velocity + k2_acc[i] * (dt / 2.0);
        }
        std::swap(bodies, temp_bodies);
        for (size_t i = 0; i < n; ++i)
        {
            k3_vel[i] = bodies[i].velocity;
            k3_acc[i] = acceleration(i);
        }
        std::swap(bodies, temp_bodies);

        // k4
        for (size_t i = 0; i < n; ++i)
        {
            temp_bodies[i].position = bodies[i].position + k3_vel[i] * dt;
            temp_bodies[i].velocity = bodies[i].velocity + k3_acc[i] * dt;
        }
        std::swap(bodies, temp_bodies);
        for (size_t i = 0; i < n; ++i)
        {
            k4_vel[i] = bodies[i].velocity;
            k4_acc[i] = acceleration(i);
        }
        std::swap(bodies, temp_bodies);

        // Update
        for (size_t i = 0; i < n; ++i)
        {
            bodies[i].position = bodies[i].position + (k1_vel[i] + k2_vel[i] * 2.0 + k3_vel[i] * 2.0 + k4_vel[i]) * (dt / 6.0);
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
                double dx = bodies[j].position.x - bodies[i].position.x;
                double dy = bodies[j].position.y - bodies[i].position.y;
                double dz = bodies[j].position.z - bodies[i].position.z;
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
    std::vector<Body> bodies;
};

} // namespace three_body_double
