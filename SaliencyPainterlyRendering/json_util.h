#pragma once
#include "stdafx.h"
/*
struct MatchPathSeparator
{
bool operator()(char ch) const
{
return ch == '/';
}
};
std::string inline basename(std::string const& pathname)
{
return std::string(std::find_if(pathname.rbegin(), pathname.rend(), MatchPathSeparator()).base(), pathname.end());
}

std::string inline removeExtension(std::string const& filename)
{
std::string::const_reverse_iterator pivot = std::find(filename.rbegin(), filename.rend(), '.');
return pivot == filename.rend() ? filename : std::string(filename.begin(), pivot.base() - 1);
}
*/