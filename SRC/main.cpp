#include "Vector.hpp"
#include <iostream>
#include "Moujassam-math.hpp"
#include <chrono>
#include <sycl/sycl.hpp>
#include "Matrix.hpp"
#define N 100000
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
	

	Vector3 av(1, 1, 1);
	Vector3 bv(2, 0, 2);
	Vector3 cv(1, 1, 0);
	Vector3 dv(4, 4, 4);
	
	// std::vector<event> e;
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

	const int jobs_cpu = qcpu.get_device().get_info<info::device::max_compute_units>();
	const int jobs_gpu = qgpu.get_device().get_info<ext::intel::info::device::gpu_eu_count>() * qgpu.get_device().get_info<ext::intel::info::device::gpu_hw_threads_per_eu>();
	const int cpu_width = qcpu.get_device().get_info<info::device::native_vector_width_float>();
	const unsigned long cpu_pow = jobs_cpu * 4000;
	const int gpu_width = qgpu.get_device().get_info<info::device::native_vector_width_float>();
	const unsigned long gpu_pow = jobs_gpu * 1000;
	std::cout << cpu_pow << "\n";
	std::cout << gpu_pow << "\n";
	std::cout << qgpu.get_device().get_info<info::device::max_clock_frequency>() <<"\n";
	const unsigned long work_gpu = commonMath::remap(gpu_pow, 0, gpu_pow + cpu_pow, 0.0f, 1.0f) * N;

	const unsigned long work_cpu = N-work_gpu;//commonMath::remap(cpu_pow, 0, gpu_pow + cpu_pow, 0.0f, 1.0f) * N;
	
	std::cout << "jobs_cpu = " << jobs_cpu << "\n";
	std::cout << "jobs_gpu = " << jobs_gpu << "\n";
	std::cout << "work_cpu = " << work_cpu << "\n";
	std::cout << "work_gpu = " << work_gpu << "\n";

	Vector3 *cgpu = malloc_device<Vector3>(work_gpu, qgpu);
	Vector3 *ccpu = malloc_shared<Vector3>(work_cpu, qcpu);

	qgpu.wait();
	qcpu.wait();
	
	Matrix4x4 test(av, bv, cv, dv);
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	qgpu.submit([&](handler &h){
		// h.depends_on(e);
		h.parallel_for(jobs_gpu, [=](item<1> it){
			for(unsigned long i = it[0]; i < work_gpu; i += it.get_range(0))
			{
				cgpu[i] = test * Vector3(1.0f, 1.0f, 1.0f);
			}
		});
	}).wait();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;
	
	begin = std::chrono::steady_clock::now();
	qcpu.submit([&](handler &h){
		// h.depends_on(e);
		h.parallel_for(jobs_cpu, [=](item<1> it){
			for(unsigned long i = it[0]; i < work_cpu; i += it.get_range(0))
			{
				ccpu[i] = test * Vector3(1.0f, 1.0f, 1.0f);
			}
		});
	}).wait();
	end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;
	
	// std::thread th_gpu(thread_wait, qgpu);
	// std::thread th_cpu(thread_wait, qcpu);
	

	


	

	// Matrix4x4 *result = new Matrix4x4[N];
	Vector3 *result = new Vector3[N];
	qgpu.copy(cgpu, result, work_gpu);
	qcpu.copy(ccpu, result + work_gpu, work_cpu);
	qgpu.wait();
	qcpu.wait();

	Vector3 v = (result[0]);
	// Vector3 v = result[0] * Vector3(1.0f, 1.0f, 1.0f);
	std::cout<< v.x() <<" "<< v.y() << " " << v.z() << "\n";

    return 0;
}
