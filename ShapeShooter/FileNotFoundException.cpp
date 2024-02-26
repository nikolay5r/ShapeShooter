#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(const char* message)
	: message(message)
{}

FileNotFoundException::FileNotFoundException(const std::string& message)
	: message(message)
{}

FileNotFoundException::~FileNotFoundException() noexcept {}

const char* FileNotFoundException::what() const noexcept
{
	return message.c_str();
}