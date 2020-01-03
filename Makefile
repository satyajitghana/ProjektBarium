all:
	mkdir -p build
	cd build && conan install .. && cmake .. && cmake --build .

clean:
	rm -rf build