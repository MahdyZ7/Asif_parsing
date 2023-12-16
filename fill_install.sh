#!/bin/bash

make re
if [[ $(env | grep PATH) == *"$PWD"* ]]; then
	echo "PATH already set"
else
	echo "export PATH=$PWD:\$PATH" | tee -a ~/.bashrc
	echo "setenv PATH $PWD:\$PATH" | tee -a ~/.cshrc
	echo "export PATH=$PWD:\$PATH" | tee -a ~/.zshrc
	if [[ $SHELL == *"/bin/bash"* ]]; then
		source ~/.bashrc
	elif [[ $SHELL == *"/bin/zsh"* ]]; then
		source ~/.zshrc
	else
		source ~/.cshrc
	fi
fi