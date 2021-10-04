#!/bin/bash
TYPE=`uname -m`

if [[ "$OSTYPE" == "linux-gnu"* && "$TYPE" == "x86_64" ]]; then
	sudo apt update
	sudo apt-get install libsdl2-dev
	sudo apt-get install libsdl2-ttf-dev
	sudo apt-get install libsdl2-image-dev
	sudo apt-get install libsdl2-mixer-dev
elif [[ "$OSTYPE" == "darwin"* ]]; then
	brew update
	brew install sdl2
	brew install sdl2_ttf
	brew install sdl2_image
	brew install sdl2_mixer
else
	echo "This operating system is not supported."
fi
