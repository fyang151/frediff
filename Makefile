CMAKE := /usr/bin/cmake

build:
	cmake -S . -B build
	cmake --build build

build_wasm:
	emcmake cmake -S . -B build_wasm
	emmake cmake --build build_wasm

run: build
	./build/log

clean:
	rm -rf build

clean_wasm:
	rm -rf build_wasm
