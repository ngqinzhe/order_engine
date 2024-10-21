.PHONY: build
build:
	rm -rf ./build
	cmake -S . -B build
	cd build && cmake --build . && ./order_engine

.PHONY: clean
clean: ## Cleans the build directory
	rm -rf build/*