all:
	icpx -fsycl -fsycl-targets=spir64_x86_64,spir64_gen,spir64 -Xsycl-target-backend="spir64_x86_64"  "-march=avx" -Xsycl-target-backend="spir64_gen" "-device *" SRC/*.cpp