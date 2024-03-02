#include "exceptions.h"

FileException::FileException(const std::string& msg) : message(msg)
{
}

const char* FileException::what()
{
	return message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message{ "not good" }
{
}

RepositoryException::RepositoryException(const std::string& msg) : message{ msg }
{
}

const char* RepositoryException::what()
{
	return this->message.c_str();
}
