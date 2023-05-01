#pragma once

namespace std
{
    class exception
    {
    public:
        exception(const char* exception) noexcept;
        virtual const char* what() const noexcept;
        exception& operator=(const exception& c) noexcept;

    private:
        const char* _m_exception;
    };
}