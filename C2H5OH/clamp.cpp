#include "precompile.hpp"
#include "clamp.hpp"

float clampMax(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}

float clampMin(float n, float lower, float upper) {
	return std::min(upper, std::max(lower, n));
}