#ifndef __TETRISDRIVER__
#define __TETRISDRIVER__

#include <vector>
#include <tins/tins.h>
#include <iostream>
#include <fstream>

#define USER_CONFIG "user.config"

using namespace Tins;

struct user_settings_{
	std::string interface;
	std::string username;
	std::string password;
}; typedef user_settings_ user_settings;


#endif
