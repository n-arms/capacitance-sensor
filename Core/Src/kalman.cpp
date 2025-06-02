#include "kalman.hpp"

kalman_filter::kalman_filter(float initial_reading, float process_variance)
		: estimate(initial_reading),
		  estimate_variance(1.),
		  process_variance(process_variance),
		  last_predict(tick::now()) {}

void kalman_filter::update(float measurement, float measurement_variance) {
	// Kn = estimate_variance / (estimate_variance + measurement_variance)
	// x_n+1 = x_n + Kn (z_n - x_n)
	// p_n+1 = (1 - Kn) * p_n
	predict();
	float kalman_gain = estimate_variance / (estimate_variance + measurement_variance);
	estimate += kalman_gain * (measurement - estimate);
	estimate_variance *= (1 - kalman_gain);
}

void kalman_filter::predict() {
	tick now = tick::now();
	uint32_t elapsed_micros = now.elapsed_since(last_predict);
	last_predict = now;
	float dt = (float) elapsed_micros / 1000000.0;
	estimate_variance += process_variance * dt;
}

float kalman_filter::state() {
	return estimate;
}

float kalman_filter::state_variance() {
	predict();
	return estimate_variance;
}
