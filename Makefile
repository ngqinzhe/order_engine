.PHONY: build
build:
	rm -rf ./build
	cmake -S . -B build
	cd build && cmake --build .

.PHONY: clean
clean: ## Cleans the build directory
	rm -rf build/*