#ifndef GEN_H
#define GEN_H

#include "runtime.h"

bool generate_tokens(std::string line, std::vector<std::string> &tokens);
bool invalid_token(std::string token);
bool generate_video(Runtime *proc, std::vector<std::string> tokens);
bool generate_pdf(Runtime *proc, std::vector<std::string> tokens);

#endif