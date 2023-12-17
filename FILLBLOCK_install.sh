#!/bin/bash

make re
if [[ $(env | grep PATH) == *"$PWD"* ]]; then
	echo "PATH already set"
else
	if [[ $(cat ~/.bashrc | grep PATH) == *"$PWD"* ]]; then
		echo "export PATH=$PWD:\$PATH" | tee -a ~/.bashrc
	elif [[ $(cat ~/.cshrc | grep PATH) == *"$PWD"* ]]; then
		echo "setenv PATH $PWD:\$PATH" | tee -a ~/.cshrc
	elif [[ $(cat ~/.zshrc | grep PATH) == *"$PWD"* ]]; then
		echo "export PATH=$PWD:\$PATH" | tee -a ~/.zshrc
	fi
	if [[ $SHELL == *"/bin/bash"* ]]; then
		source ~/.bashrc
	elif [[ $SHELL == *"/bin/zsh"* ]]; then
		source ~/.zshrc
	else
		source ~/.cshrc
	fi
fi