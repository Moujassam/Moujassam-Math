#pragma once


#include <sycl/sycl.hpp>
#include <vector>
#include <iostream>
#include "Vector.hpp"

using namespace sycl;

class HPGML_vector2
{
public:
	HPGML_vector2(queue& qarr, const Vector2  *data, const unsigned long &size);
	~HPGML_vector2();

	// takes and returns the same pointer
	float *Length(float *result);
	// queue
	queue	&q;
	//host array, acceseble from host and device
	Vector2 *host_array;
	// device array, accesseble from device only
	Vector2 *device_array;
	float* float_result;
	// size of the array
	unsigned long size;
};

float* Length(queue& q, Vector2* device_vec, float* device_float, unsigned long size);
