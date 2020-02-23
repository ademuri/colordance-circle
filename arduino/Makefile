PORT ?= "/dev/ttyACM0"
libraries:=build/Arduino/libraries
arduino_cli_or_link:=build/arduino-cli
CLI="$(arduino_cli_or_link) --config-file arduino-cli.yaml"

build: direct/direct.ino $(libraries) $(arduino_cli_or_link)
	"$(CLI)" compile direct/direct.ino --fqbn="$(FQBN)" --build-path="$(PWD)/build"
.PHONY: build

upload: direct/direct.ino $(libraries) $(arduino_cli_or_link)
	"$(CLI)" compile direct/direct.ino -u -t --port "$(PORT)" -o "$(PWD)/build/direct.bin" --fqbn="$(FQBN)" --build-path="$(PWD)/build"
.PHONY: upload

.ONESHELL:
$(libraries):
	if [ ! -d "build/Arduino/libraries" ]; then
		mkdir -p "$(libraries)"
		ln -s "$(PWD)/../generic" "$(libraries)/generic"
		git clone https://github.com/candykingdom/FastLED.git "$(libraries)/FastLED"
	fi

# Either add a symlink to an arduino-cli already on the path, or download it.
# This is a file so that Make knows to get this before building other targets.
# Note: dowloading only supports 64-bit platforms.
$(arduino_cli_or_link):
	mkdir -p build
ifeq (, $(shell which arduino-cli))

ifeq ($(OS),Windows_NT)
	wget https://github.com/arduino/arduino-cli/releases/download/0.6.0/arduino-cli_0.6.0_Windows_64bit.zip -O "$(arduino_cli_or_link).tar.gz"
else

ifeq ($(UNAME_S),Darwin)
	wget https://github.com/arduino/arduino-cli/releases/download/0.6.0/arduino-cli_0.6.0_macOS_64bit.tar.gz -O "$(arduino_cli_or_link).tar.gz"
else
	wget https://github.com/arduino/arduino-cli/releases/download/0.6.0/arduino-cli_0.6.0_Linux_64bit.tar.gz -O "$(arduino_cli_or_link).tar.gz"
endif

endif

	tar xf "$(arduino_cli_or_link).tar.gz" -C build
	"$(arduino_cli_or_link)" core update-index
else
	ln -s "$(shell which arduino-cli)" "$(arduino_cli_or_link)"
endif

clean:
	find build/ ! -path 'build/Arduino/*' ! -path 'build/Arduino' ! -path 'build/' -delete
	# Someone please tell me how to do this better - invalidate the cache so `make` will notice that something changed.
	touch direct/direct.ino
.PHONY: clean

clean-all:
	rm -rf build/*
.PHONY: clean-all
