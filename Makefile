avr: avr_main.c
	mkdir -p build
	avr-gcc avr_main.c -o ./build/avr_main.elf -mmcu=atmega328p -DF_CPU=16000000UL -Os
	avr-objcopy ./build/avr_main.elf -O ihex ./build/avr_main.hex
	avrdude -c usbasp -p m328p -U flash:w:"./build/avr_main.hex":a

build/sounds/dzin.h: sounds/dzin.wav
	mkdir -p build/sounds
	python3 generate_sound.py dzin

build/sounds/hi.h: sounds/hi.wav
	mkdir -p build/sounds
	python3 generate_sound.py hi

build/sounds/bump.h: sounds/bump.wav
	mkdir -p build/sounds
	python3 generate_sound.py bump

build/sounds/spoon.h: sounds/spoon.wav
	mkdir -p build/sounds
	python3 generate_sound.py spoon

build/sounds/spoon2.h: sounds/spoon2.wav
	mkdir -p build/sounds
	python3 generate_sound.py spoon2

build/sounds/click.h: sounds/click.wav
	mkdir -p build/sounds
	python3 generate_sound.py click

sounds: build/sounds/dzin.h build/sounds/hi.h build/sounds/bump.h build/sounds/spoon.h build/sounds/spoon2.h build/sounds/click.h

build: sounds sdl_main.c
	mkdir -p build
	gcc -Wall sdl_main.c -lSDL2 -lm -lSDL2main -o ./build/sdl

clean:
	rm -rf build
