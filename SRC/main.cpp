#include "Vector.hpp"
#include <iostream>
#include "Moujassam-math.hpp"
#include <chrono>
#include <sycl/sycl.hpp>
#include "Matrix.hpp"
#define N 10000000

using namespace sycl;

int main()
{

	queue q(gpu_selector_v);
	std::cout << q.get_device().get_info<ext::intel::info::device::gpu_eu_count>() << "\n";
	std::cout << q.get_device().get_info<ext::intel::info::device::gpu_eu_simd_width>() << "\n";
	std::cout << q.get_device().get_info<ext::intel::info::device::gpu_hw_threads_per_eu>() << "\n";
	std::cout << q.get_device().get_info<ext::intel::info::device::gpu_slices>() << "\n";
	std::cout << q.get_device().get_info<ext::intel::info::device::gpu_subslices_per_slice>() << "\n";
	std::cout << q.get_device().get_info<ext::intel::info::device::gpu_eu_count_per_subslice>() << "\n";
	
	queue q2(gpu_selector_v);
	std::cout << q2.get_device().get_info<info::device::max_compute_units>() << "\n";
	std::cout << q2.get_device().get_info<info::device::native_vector_width_double>() << "\n";
	
	
	
	Matrix4x4 *a = malloc_device<Matrix4x4>(N, q);
	Matrix4x4 *b = malloc_device<Matrix4x4>(N, q);
	Matrix4x4 *c = malloc_device<Matrix4x4>(N, q);

	Vector3 av(1, 1, 1);
	Vector3 bv(2, 0, 2);
	Vector3 cv(1, 1, 0);
	Vector3 dv(4, 4, 4);
	

	q.fill(a, Matrix4x4(av, bv, cv, dv), N);
	q.fill(b, Matrix4x4(av, bv, cv, dv), N);
	q.fill(c, Matrix4x4(0.0f), N);
	
	int jobs = q.get_device().get_info<ext::intel::info::device::gpu_eu_count>() * q.get_device().get_info<ext::intel::info::device::gpu_hw_threads_per_eu>();
	// jobs = 1000;
	q.parallel_for(jobs, [=](item<1> it){
		for(unsigned long i = it[0]; i < N; i += it.get_range(0))
		{
			c[i] = a[i] * b[i] * b[i].Transpose() * a[i].LookAt(Vector3(1, 1, 1), Vector3(10, 10, -10), Vector3(0, 1, 0)) * b[i] * a[i];
		}
	});

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	q.wait();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

	Matrix4x4 *result = new Matrix4x4[N];
	q.copy(c, result, N);
	q.wait();

	Vector3 v = (result[0] * av);
	std::cout<< v.x << v.y << v.z << "\n";

    return 0;
}
