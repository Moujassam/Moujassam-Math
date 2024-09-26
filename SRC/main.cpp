#include "Vector.hpp"
#include <iostream>
#include "Moujassam-math.hpp"
#include <chrono>
#include <sycl/sycl.hpp>
#include "Matrix.hpp"
#define N 65535*100//100000000
#include <thread>
using namespace sycl;


void thread_wait(queue q)
{
	q.wait();
}

int main(int arg_num, char **args)
{
	queue qgpu;
	queue qcpu;
	// if(arg_num > 1)
	// {
	// 	if(std::string(args[1]) == "cpu")
	// 		q = queue(cpu_selector_v);
	// 	else if(std::string(args[1]) == "gpu")
	// 		q = queue(gpu_selector_v);
	// 	else 
	// 		q = queue(default_selector_v);
	// }
	qcpu = queue(cpu_selector_v);
	qgpu = queue(gpu_selector_v);
	
	// std::cout << q.get_device().get_info<ext::intel::info::device::gpu_eu_count>() << "\n";
	// std::cout << q.get_device().get_info<ext::intel::info::device::gpu_eu_simd_width>() << "\n";
	// std::cout << q.get_device().get_info<ext::intel::info::device::gpu_hw_threads_per_eu>() << "\n";
	// std::cout << q.get_device().get_info<ext::intel::info::device::gpu_slices>() << "\n";
	// std::cout << q.get_device().get_info<ext::intel::info::device::gpu_subslices_per_slice>() << "\n";
	// std::cout << q.get_device().get_info<ext::intel::info::device::gpu_eu_count_per_subslice>() << "\n";
	
	// queue q2(gpu_selector_v);
	// std::cout << q2.get_device().get_info<info::device::max_compute_units>() << "\n";
	
	std::cout << qgpu.get_device().get_info<info::device::native_vector_width_char>() << "\n";
	std::cout << qcpu.get_device().get_info<info::device::native_vector_width_char>() << "\n";	
	std::cout << qgpu.get_device().get_info<info::device::native_vector_width_short>() << "\n";
	std::cout << qcpu.get_device().get_info<info::device::native_vector_width_short>() << "\n";	
	std::cout << qgpu.get_device().get_info<info::device::native_vector_width_int>() << "\n";
	std::cout << qcpu.get_device().get_info<info::device::native_vector_width_int>() << "\n";	
	std::cout << qgpu.get_device().get_info<info::device::native_vector_width_long>() << "\n";
	std::cout << qcpu.get_device().get_info<info::device::native_vector_width_long>() << "\n";	
	std::cout << qgpu.get_device().get_info<info::device::native_vector_width_half>() << "\n"; 
	std::cout << qcpu.get_device().get_info<info::device::native_vector_width_half>() << "\n"; 	
	std::cout << qgpu.get_device().get_info<info::device::native_vector_width_float>() << "\n"; 
	std::cout << qcpu.get_device().get_info<info::device::native_vector_width_float>() << "\n"; 	
	std::cout << qgpu.get_device().get_info<info::device::native_vector_width_double>() << "\n"; 
	std::cout << qcpu.get_device().get_info<info::device::native_vector_width_double>() << "\n"; 	
	
	// Matrix4x4 *a = malloc_device<Matrix4x4>(N, q);
	// Matrix4x4 *b = malloc_device<Matrix4x4>(N, q);
	// Matrix4x4 *c = malloc_device<Matrix4x4>(N, q);
	Vector3 *cgpu = malloc_device<Vector3>(N/2, qgpu);
	Vector3 *ccpu = malloc_device<Vector3>(N-N/2, qcpu);


	Vector3 av(1, 1, 1);
	Vector3 bv(2, 0, 2);
	Vector3 cv(1, 1, 0);
	Vector3 dv(4, 4, 4);
	
	std::vector<event> e;
	// e.push_back(q.fill(a, Matrix4x4(av, bv, cv, dv), N));
	// e.push_back(q.fill(b, Matrix4x4(av, bv, cv, dv), N));
	// e.push_back(q.fill(c, Matrix4x4(1.0f), N));
	
	// e.push_back(q.fill(c, Vector3(0, 0, 0), N));
	// int jobs = 0;
	// if(q.get_device().is_gpu())
	// 	jobs = q.get_device().get_info<ext::intel::info::device::gpu_eu_count>() * q.get_device().get_info<ext::intel::info::device::gpu_hw_threads_per_eu>();
	// else if(q.get_device().is_cpu())
	// 	jobs = q.get_device().get_info<info::device::max_compute_units>();
	// else
	// 	jobs = 4096;
	int jobs_cpu = qcpu.get_device().get_info<info::device::max_compute_units>();
	int jobs_gpu = qgpu.get_device().get_info<ext::intel::info::device::gpu_eu_count>() * qgpu.get_device().get_info<ext::intel::info::device::gpu_hw_threads_per_eu>();
	
	std::cout << "jobs_cpu = " << jobs_cpu << "\n";
	std::cout << "jobs_gpu = " << jobs_gpu << "\n";
	qgpu.wait();
	qcpu.wait();
	
	Matrix4x4 test(av, bv, cv, dv);
	qgpu.submit([&](handler &h){
		// h.depends_on(e);
		h.parallel_for(jobs_gpu, [=](item<1> it){
			for(unsigned long i = it[0]; i < N/2; i += it.get_range(0))
			{
				cgpu[i] = test * Vector3(1.0f, 1.0f, 1.0f);
			}
		});
	});
	qcpu.submit([&](handler &h){
		// h.depends_on(e);
		h.parallel_for(jobs_cpu, [=](item<1> it){
			for(unsigned long i = it[0]; i < N-N/2; i += it.get_range(0))
			{
				ccpu[i] = test * Vector3(1.0f, 1.0f, 1.0f);
			}
		});
	});
	
	std::thread th_gpu(thread_wait, qgpu);
	std::thread th_cpu(thread_wait, qcpu);
	

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	th_gpu.join();
	th_cpu.join();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

	// Matrix4x4 *result = new Matrix4x4[N];
	Vector3 *result = new Vector3[N];
	qgpu.copy(cgpu, result, N/2);
	qcpu.copy(ccpu, result + N/2, N-N/2);
	qgpu.wait();
	qcpu.wait();

	Vector3 v = (result[0]);
	// Vector3 v = result[0] * Vector3(1.0f, 1.0f, 1.0f);
	std::cout<< v.x() <<" "<< v.y() << " " << v.z() << "\n";

    return 0;
}
