/*
 * VirtualKeyboard.h
 *
 *      Author: suraj
 */

#ifndef VIRTUALKEYBOARD_H_
#define VIRTUALKEYBOARD_H_

#include <termios.h>
#include <string>
#include <signal.h>

namespace VK {

class VirtualKeyboard {
 public:
  VirtualKeyboard();
  virtual ~VirtualKeyboard();
  void initialize();
  void readLine();
  void writeLine();
 private:
  void initTermios(int);
  void resetTermios();
  char readChar(int);
  void setSignalHandler(int);

  struct termios old;
  struct termios current;
  std::string buffer;
  struct sigaction sa;
};

} /* namespace VK */

#endif /* VIRTUALKEYBOARD_H_ */
