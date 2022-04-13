#include <string>


std::string operator ""_bld (const char* str, size_t)
{
	return "\x1b[1m" + std::string(str) + "\x1b[0m";
}


std::string operator ""_red (const char* str, size_t)
{
	return "\x1b[0;31m" + std::string(str) + "\x1b[0m";
}

std::string operator ""_bldred (const char* str, size_t)
{
	return "\x1b[1;31m" + std::string(str) + "\x1b[0m";
}


std::string operator ""_grn (const char* str, size_t)
{
	return "\x1b[0;32m" + std::string(str) + "\x1b[0m";
}

std::string operator ""_bldgrn (const char* str, size_t)
{
	return "\x1b[1;32m" + std::string(str) + "\x1b[0m";
}


std::string operator ""_cyn (const char* str, size_t)
{
	return "\x1b[0;36m" + std::string(str) + "\x1b[0m";
}

std::string operator ""_bldcyn (const char* str, size_t)
{
	return "\x1b[1;36m" + std::string(str) + "\x1b[0m";
}