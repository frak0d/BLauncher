#include <string>


std::string operator ""_bld (const char* str, size_t)
{
	return "<b>" + std::string(str) + "</b>";
}

std::string operator ""_red (const char* str, size_t)
{
	return "<font color=red>" + std::string(str) + "</font>";
}

std::string operator ""_bldred (const char* str, size_t)
{
	return "<font color=red><b>" + std::string(str) + "</b></font>";
}

std::string operator ""_grn (const char* str, size_t)
{
	return "<font color=green>" + std::string(str) + "</font>";
}

std::string operator ""_bldgrn (const char* str, size_t)
{
	return "<font color=green><b>" + std::string(str) + "</b></font>";
}

std::string operator ""_cyn (const char* str, size_t)
{
	return "<font color=cyan>" + std::string(str) + "</font>";
}

std::string operator ""_bldcyn (const char* str, size_t)
{
	return "<font color=cyan><b>" + std::string(str) + "</b></font>";
}
