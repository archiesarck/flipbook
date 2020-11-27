// #include "includes.h"
#include "runtime.h"
// #include "generator_functions.h"


#ifndef HANDLERS_H 
#define HANDLERS_H

bool handleTimedList(std::ifstream &fin, Runtime *proc, unsigned int &line_number, std::string variable_name);
bool handleUntimedList(std::ifstream &fin, Runtime *proc, unsigned int &line_number, std::string variable_name);
bool handleFolder(std::vector<std::string> tokens, Runtime *proc);
bool handleFrames(std::ifstream &fin, Runtime *proc, unsigned int &line_number, std::string variable_name);
bool appendUList(Runtime *proc, std::vector<std::string> tokens);
bool appendTList(Runtime *proc, std::vector<std::string> tokens);
bool appendFrames(Runtime *proc, std::vector<std::string> tokens);
bool accessFrames();
bool accessUList();
bool accessTList();
bool TList2UList(Runtime *proc, std::vector<std::string> tokens);
bool UList2Frames(Runtime *proc, std::vector<std::string> tokens);

#endif