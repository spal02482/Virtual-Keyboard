/*
 * VirtualKeyboard.cpp
 *
 *      Author: suraj
 */

#include "VirtualKeyboard.h"
#include <iostream>
#include <signal.h>
#include <cstring>

namespace VK {

VirtualKeyboard::VirtualKeyboard() {
  // TODO Auto-generated constructor stub
  initialize();
}

VirtualKeyboard::~VirtualKeyboard() {
  // TODO Auto-generated destructor stub
}

void noaction(int signal, siginfo_t * siginfo, void * arg) {

}


void VirtualKeyboard::readLine() {
  char ch;
  while ((ch = readChar(0)) != '\n') { // read till encountering newline character

    if (ch == 17) {  // on encountering ctrl-q character
      writeLine();
      exit(EXIT_SUCCESS);
    }

    buffer += ch;
  }
  writeLine();

}

void VirtualKeyboard::writeLine() {
  if (buffer.size() != 0) {
    std::cout << buffer << std::endl;
  }
  buffer.clear();
}

void VirtualKeyboard::initialize() {
  system("stty -ixon"); // disable Ctrl-S (terminal pause) and Ctrl-Q (terminal unpause)
  system("stty -ixoff");

  // prepare sigaction structure
  memset(&sa, 0, sizeof (struct sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = noaction;
  sa.sa_flags = SA_SIGINFO;

  // Catch Ctrl-C and Ctrl-Z
  setSignalHandler(SIGINT);
  setSignalHandler(SIGTSTP);
}

/* Initialize new terminal i/o settings */
void VirtualKeyboard::initTermios(int echo) {
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
     current.c_lflag |= ECHO; /* set echo mode */
  } else {
     current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void VirtualKeyboard::resetTermios() {
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char VirtualKeyboard::readChar(int echo) {
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

void VirtualKeyboard::setSignalHandler(int signal) {
  sigaction(signal, &sa, NULL);
}

} /* namespace VK */
