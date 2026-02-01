#pragma once

#include "three_body_helpers.h"
#include <cmath>

namespace pkr {
namespace test {
namespace numerical {

// ============================================================================
// Energy Computation for Plain Doubles
// ============================================================================

double compute_total_energy_double(const three_body_state_double_t& state) {
    // Kinetic energy: 0.5 * m * v^2 for each body
    double ke1 = 0.5 * m1 * (state.vel1.x*state.vel1.x + state.vel1.y*state.vel1.y + state.vel1.z*state.vel1.z);
    double ke2 = 0.5 * m2 * (state.vel2.x*state.vel2.x + state.vel2.y*state.vel2.y + state.vel2.z*state.vel2.z);
    double ke3 = 0.5 * m3 * (state.vel3.x*state.vel3.x + state.vel3.y*state.vel3.y + state.vel3.z*state.vel3.z);

    // Potential energy: -G * m_i * m_j / r_ij for each pair
    double r12 = std::sqrt((state.pos1.x - state.pos2.x)*(state.pos1.x - state.pos2.x) +
                           (state.pos1.y - state.pos2.y)*(state.pos1.y - state.pos2.y) +
                           (state.pos1.z - state.pos2.z)*(state.pos1.z - state.pos2.z));
    double r13 = std::sqrt((state.pos1.x - state.pos3.x)*(state.pos1.x - state.pos3.x) +
                           (state.pos1.y - state.pos3.y)*(state.pos1.y - state.pos3.y) +
                           (state.pos1.z - state.pos3.z)*(state.pos1.z - state.pos3.z));
    double r23 = std::sqrt((state.pos2.x - state.pos3.x)*(state.pos2.x - state.pos3.x) +
                           (state.pos2.y - state.pos3.y)*(state.pos2.y - state.pos3.y) +
                           (state.pos2.z - state.pos3.z)*(state.pos2.z - state.pos3.z));

    double pe12 = -G * m1 * m2 / r12;
    double pe13 = -G * m1 * m3 / r13;
    double pe23 = -G * m2 * m3 / r23;

    return ke1 + ke2 + ke3 + pe12 + pe13 + pe23;
}

} // namespace numerical
} // namespace test
} // namespace pkr