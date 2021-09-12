//============================================================================
// Name        : VirtualKeyboard.cpp
// Author      : Suraj B. Pal
// Version     :
// Copyright   : Your copyright notice
// Description : Virtual Keyboard in C++, Ansi-style
//============================================================================

#include <iostream>
#include "VirtualKeyboard.h"

int main() {
	std::cout << "!!!Welcome to Virtual Keyboard, Let's Type! Press Ctrl-Q to Quit!!!" << std::endl;
	VK::VirtualKeyboard * vk = new VK::VirtualKeyboard();
	while (true) {
	  vk->readLine();
	}
	return 0;
}
