#include <cmath>

namespace netk
{
	// The activation function of the original neat library
	inline float NEATSigmoid(float value, void* metadata)
	{
		return (1.0f / (1.0f + (expf(-(4.924273f * value)))));
	}
}