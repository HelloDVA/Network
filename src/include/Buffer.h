
#pragma once
#include<string>

class Buffer
{
    private:
        std::string buffer;
    public:
        void Append(const char *_str, int _size);
        ssize_t Size();
        const char *Cstr();
        void Clean();

		std::string getbuffer();


};
