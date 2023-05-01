#include <libcpp/exceptions.hpp>

std::exception::exception(const char* exception) noexcept
    : _m_exception(exception) { }

const char* std::exception::what() const noexcept { return "An exception occured"; }

std::exception& std::exception::operator=(const std::exception& c) noexcept
{
    _m_exception = c._m_exception; 
    return *this; 
}