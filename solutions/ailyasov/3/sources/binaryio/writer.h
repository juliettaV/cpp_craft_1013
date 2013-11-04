#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace binaryio
{
    class Writer {
        public:
            Writer(const std::string filename);
            template <typename T> void save_binary( T const & v)
            {
                out.write(reinterpret_cast<const char*>(&v), sizeof( T ) );
            }
            bool eof() const;
            bool is_open() const;
            void save_string(std::string const &);
            ~Writer();
        private:
            std::ofstream out;
            Writer();
            Writer(Writer const &);
            void operator=(Writer const &);
    };
}
