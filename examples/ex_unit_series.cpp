/**
 * @example ex_unit_series.cpp
 * @brief Time series operations with unit-safe quantities and measurements
 * 
 * Demonstrates:
 * - Building a time series of position measurements
 * - Computing velocity (time derivative)
 * - Interpolation at arbitrary times
 * - Resampling to uniform intervals
 * - Statistical analysis
 * - Filtering and smoothing
 */

#include <pkr_units/si_units.h>
#include <pkr_units/units/unit_series.h>
#include <pkr_units/measurements/unit_series.h>
#include <pkr_units/literals.h>

#include <iostream>
#include <chrono>
#include <format>

using namespace pkr::units;
using namespace pkr::units::literals;

int main()
{
    // ========================================================================
    // Example 1: Quantity Series with Position Data
    // ========================================================================
    
    std::cout << "=== Example 1: Position Time Series ===\n";
    
    quantity_series<meter_t> position;
    
    // Simulate position measurements over time
    auto t0 = std::chrono::high_resolution_clock::now();
    
    position.add_at(t0, 0.0_m);
    position.add_at(t0 + std::chrono::milliseconds(100), 1.0_m);
    position.add_at(t0 + std::chrono::milliseconds(200), 4.0_m);
    position.add_at(t0 + std::chrono::milliseconds(300), 9.0_m);
    position.add_at(t0 + std::chrono::milliseconds(400), 16.0_m);
    
    std::cout << "Number of points: " << position.size() << "\n";
    std::cout << "First position: " << position.front().value() << " m\n";
    std::cout << "Last position: " << position.back().value() << " m\n";
    std::cout << "Mean position: " << position.mean().value() << " m\n";
    std::cout << "Min position: " << position.min().value() << " m\n";
    std::cout << "Max position: " << position.max().value() << " m\n";
    std::cout << "Range: " << position.range().value() << " m\n";
    
    // ========================================================================
    // Example 2: Time Derivative (Position -> Velocity)
    // ========================================================================
    
    std::cout << "\n=== Example 2: Time Derivative ===\n";
    
    auto velocity = position.time_derivative();
    std::cout << "Velocity series size: " << velocity.size() << "\n";
    
    for (size_t i = 0; i < velocity.size(); ++i)
    {
        auto [t, v] = velocity.at(i);
        std::cout << "  v[" << i << "] = " << v.value() << " m/s\n";
    }
    
    // ========================================================================
    // Example 3: Interpolation
    // ========================================================================
    
    std::cout << "\n=== Example 3: Interpolation ===\n";
    
    auto t_interp = t0 + std::chrono::milliseconds(150);
    
    // Linear interpolation (default)
    auto pos_linear = position.interpolate_at(t_interp);
    std::cout << "Linear interpolation at t=150ms: " << pos_linear.value() << " m\n";
    
    // Cubic spline interpolation  
    auto pos_spline = position.interpolate_at(t_interp, pkr::units::interpolation_method::cubic_spline);
    std::cout << "Cubic spline at t=150ms: " << pos_spline.value() << " m\n";
    
    // Polynomial interpolation (order 2 = quadratic)
    auto pos_quadratic = position.interpolate_at_polynomial(t_interp, 2);
    std::cout << "Quadratic polynomial at t=150ms: " << pos_quadratic.value() << " m\n";
    
    // Polynomial interpolation (order 3 = cubic)
    auto pos_cubic_poly = position.interpolate_at_polynomial(t_interp, 3);
    std::cout << "Cubic polynomial at t=150ms: " << pos_cubic_poly.value() << " m\n";
    
    // ========================================================================
    // Example 4: Resampling
    // ========================================================================
    
    std::cout << "\n=== Example 4: Resampling ===\n";
    
    auto resampled_linear = position.resample(std::chrono::milliseconds(50));
    std::cout << "Original points: " << position.size() << "\n";
    std::cout << "Resampled (linear): " << resampled_linear.size() << "\n";
    
    // Resample with cubic spline interpolation
    auto resampled_spline = position.resample(
        std::chrono::milliseconds(50), 
        pkr::units::interpolation_method::cubic_spline);
    std::cout << "Resampled (cubic spline): " << resampled_spline.size() << "\n";
    
    // ========================================================================
    // Example 5: Filtering and Smoothing
    // ========================================================================
    
    std::cout << "\n=== Example 5: Filtering and Smoothing ===\n";
    
    auto filtered = position.filter([](const meter_t& q) {
        return q.value() < 10.0;  // Keep points below 10m
    });
    std::cout << "Filtered points (< 10 m): " << filtered.size() << "\n";
    
    auto smoothed = position.smooth(2);
    std::cout << "Smoothed with window=2: " << smoothed.size() << "\n";
    
    // ========================================================================
    // Example 6: Measurement Series with Uncertainty
    // ========================================================================
    
    std::cout << "\n=== Example 6: Measurement Series ===\n";
    
    using measurement_t = measurement_lin_t<meter_t>;
    measurement_series<meter_t> measurements;
    
    // Add measurements with uncertainty (e.g., from a sensor with ~0.1m noise)
    measurements.add_at(t0, measurement_t(0.0_m, 0.1_m));
    measurements.add_at(t0 + std::chrono::milliseconds(100), 
                        measurement_t(1.05_m, 0.1_m));
    measurements.add_at(t0 + std::chrono::milliseconds(200), 
                        measurement_t(4.1_m, 0.15_m));  // Higher uncertainty
    measurements.add_at(t0 + std::chrono::milliseconds(300), 
                        measurement_t(8.95_m, 0.1_m));
    measurements.add_at(t0 + std::chrono::milliseconds(400), 
                        measurement_t(16.2_m, 0.15_m));
    
    std::cout << "Number of measurements: " << measurements.size() << "\n";
    
    auto mean_pos = measurements.mean();
    std::cout << "Mean position: " << mean_pos.value().value() << " ± " 
              << mean_pos.uncertainty().value() << " m\n";
    
    auto [lower, upper] = measurements.uncertainty_bounds();
    std::cout << "Uncertainty bounds: [" << lower.value() << ", " 
              << upper.value() << "] m\n";
    
    auto std_dev = measurements.std_dev();
    std::cout << "Std dev: " << std_dev.value().value() << " ± " 
              << std_dev.uncertainty().value() << " m\n";
    
    // ========================================================================
    // Example 7: Measurement Series Slicing
    // ========================================================================
    
    std::cout << "\n=== Example 7: Time Range Slicing ===\n";
    
    auto sliced = measurements.slice(t0 + std::chrono::milliseconds(100),
                                     t0 + std::chrono::milliseconds(300));
    std::cout << "Original measurements: " << measurements.size() << "\n";
    std::cout << "Sliced [100ms, 300ms]: " << sliced.size() << "\n";
    
    // ========================================================================
    // Example 8: Custom Allocator (Arena Allocation)
    // ========================================================================
    
    std::cout << "\n=== Example 8: Custom Allocator ===\n";
    
    // Create a pre-allocated buffer (arena)
    std::array<std::byte, 1024> buffer;
    std::pmr::monotonic_buffer_resource arena(buffer.data(), buffer.size());
    
    quantity_series<meter_t, std::pmr::polymorphic_allocator<std::byte>>
        arena_series(std::pmr::polymorphic_allocator<std::byte>(&arena));
    
    arena_series.add_at(t0, 0.0_m);
    arena_series.add_at(t0 + std::chrono::milliseconds(100), 1.0_m);
    arena_series.add_at(t0 + std::chrono::milliseconds(200), 4.0_m);
    
    std::cout << "Arena-allocated series size: " << arena_series.size() << "\n";
    std::cout << "Mean: " << arena_series.mean().value() << " m\n";

    // ========================================================================
    // Example 9: Time Series with Unit-Based Timestamps (second_t)
    // ========================================================================
    
    std::cout << "\n=== Example 9: Unit-Based Time (second_t) ===\n";
    
    // Time series using PKR time units instead of chrono
    // This provides unit-aware timestamps with dimensional analysis
    quantity_series<meter_t, second_t<double>> position_time_units;
    
    position_time_units.add_at(0.0_s, 0.0_m);
    position_time_units.add_at(0.1_s, 1.0_m);
    position_time_units.add_at(0.2_s, 4.0_m);
    position_time_units.add_at(0.3_s, 9.0_m);
    position_time_units.add_at(0.4_s, 16.0_m);
    
    std::cout << "Position series with second_t timestamps\n";
    std::cout << "Size: " << position_time_units.size() << "\n";
    std::cout << "Mean: " << position_time_units.mean().value() << " m\n";

    // ========================================================================
    // Example 10: Uncertain Time Measurements
    // ========================================================================
    
    std::cout << "\n=== Example 10: Uncertain Time (measurement<second_t>) ===\n";
    
    // Time series with uncertain timestamps
    // Useful for experimental data where measurement times themselves have uncertainty
    using uncertain_second = measurement_lin_t<second_t<double>>;
    quantity_series<meter_t, uncertain_second> position_uncertain_time;
    
    // Add measurements with timestamps that have uncertainty
    position_uncertain_time.add_at(uncertain_second{0.0_s, 0.001_s}, 0.0_m);
    position_uncertain_time.add_at(uncertain_second{0.1_s, 0.002_s}, 1.0_m);
    position_uncertain_time.add_at(uncertain_second{0.2_s, 0.002_s}, 4.0_m);
    position_uncertain_time.add_at(uncertain_second{0.3_s, 0.001_s}, 9.0_m);
    position_uncertain_time.add_at(uncertain_second{0.4_s, 0.003_s}, 16.0_m);
    
    std::cout << "Position series with uncertain timestamps\n";
    std::cout << "Size: " << position_uncertain_time.size() << "\n";
    std::cout << "Time uncertainty at index 0: " 
              << position_uncertain_time[0].get_time_uncertainty().value() << " s\n";
    std::cout << "Mean position: " << position_uncertain_time.mean().value() << " m\n";
    
    return 0;
}
