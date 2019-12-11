CLI="arduino-cli --config-file arduino-cli.yaml"
PORT ?= "/dev/ttyACM0"
libraries:=build/Arduino/libraries

build: direct/direct.ino $(libraries)
	"$(CLI)" compile direct/direct.ino --fqbn="$(FQBN)" --build-path="$(PWD)/build"
.PHONY: build

upload: direct/direct.ino $(libraries)
	"$(CLI)" compile direct/direct.ino -u -t --port "$(PORT)" -o "$(PWD)/build/direct.bin" --fqbn="$(FQBN)" --build-path="$(PWD)/build"
.PHONY: upload

.ONESHELL:
$(libraries):
	if [ ! -d "build/Arduino/libraries" ]; then
		mkdir -p "$(libraries)"
		ln -s "$(PWD)/../generic" "$(libraries)/generic"
		git clone https://github.com/candykingdom/FastLED.git "$(libraries)/FastLED"
	fi

clean:
	find build/ ! -path 'build/Arduino/*' ! -path 'build/Arduino' ! -path 'build/' -delete
	# Someone please tell me how to do this better - invalidate the cache so `make` will notice that something changed.
	touch direct/direct.ino
.PHONY: clean

clean-all:
	rm -rf build/*
.PHONY: clean-all
