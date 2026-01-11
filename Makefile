.PHONY: build build_wasm run clean

build:
	cmake -S . -B build
	cmake --build build

build_wasm:
	emcmake cmake -S . -B build_wasm
	emmake cmake --build build_wasm

run: build
	./build/log

clean:
	rm -rf build build_wasm
