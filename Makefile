all:
	icpx -fsycl -fsycl-targets=spir64_gen,spir64 -Xsycl-target-backend="spir64_gen" "-device *" SRC/*.cpp