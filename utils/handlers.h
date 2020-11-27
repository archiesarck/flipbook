// #include "includes.h"
#include "runtime.h"
// #include "generator_functions.h"


#ifndef HANDLERS_H 
#define HANDLERS_H

bool handleTimedList(std::ifstream &fin, Runtime *proc, unsigned int &line_number, std::string variable_name);
bool handleUntimedList(std::ifstream &fin, Runtime *proc, unsigned int &line_number, std::string variable_name);
bool handleFolder(std::vector<std::string> tokens, Runtime *proc);
bool handleFrames(std::ifstream &fin, Runtime *proc, unsigned int &line_number, std::string variable_name);

#endif