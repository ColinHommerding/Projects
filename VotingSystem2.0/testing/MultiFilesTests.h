#ifndef MultiFilesTests_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define MultiFilesTests_H

#include "../src/include/Election.h"
#include <stdio.h>
#include <string>
#include <vector>

namespace VS = VotingSystem;

bool file_exists(std::string filename);
bool TestAndRemoveFiles(VS::Election *e, bool testExists);

#endif