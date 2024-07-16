# Environment setup: https://mongoose.ws/documentation/tutorials/tools/

.PHONY: build

all build: build/firmware.uf2

build/firmware.uf2: $(wildcard *.c) $(wildcard *.h) CMakeLists.txt Makefile
	test -d build || mkdir build
	cd build && export && cmake -DPICO_SDK_PATH=$(realpath ../../../../../templates/stuff/pico-sdk) -G "Unix Makefiles" .. && make

flash: build/firmware.uf2
	picotool load $< -f

clean:
	rm -rf build

# Pico SDK, for reference purposes only
pico-sdk:
	git clone --depth 1 -b 1.5.0 https://github.com/raspberrypi/pico-sdk $@
	cd $@ && git submodule update --init
