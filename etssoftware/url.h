// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef URL_H
#define URL_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
namespace ETS
{
    class url
    {
        public:
            url(const std::string& url_s);
            std::string protocol();
            std::string host();
            std::string path();
            std::string query();
            std::string queryArr();
            std::string queryArr2();
            bool to_bool(std::string const& s);
            std::vector<std::string> extractparams(std::string rawparams);
        private:
            void parse(const std::string& url_s);
            std::string protocol_;
            std::string host_; 
            std::string path_; 
            std::string query_;
            std::string queryArr_;
            std::string queryArr2_;
    };
}
#endif
