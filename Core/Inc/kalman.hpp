#ifndef KALMAN_H
#define KALMAN_H

#include "tick.hpp"

class kalman_filter {
public:
	kalman_filter(float initial_reading, float process_variance);
	void update(float measurement, float measurement_variance);
	float state();
	float state_variance();
private:
	void predict();

	float estimate;
	float estimate_variance;
	float process_variance;
	tick last_predict;
	// Kn = estimate_variance / (estimate_variance + measurement_variance)
	// x_n+1 = x_n + Kn (z_n - x_n)
	// p_n+1 = (1 - Kn) * p_n
};

#endif
