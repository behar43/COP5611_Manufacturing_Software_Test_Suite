// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "url.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <functional>
using namespace std;

ETS::url::url(const std::string& url_s)
: protocol_(), host_(), path_(), query_(), queryArr_(), queryArr2_()
{
    parse(url_s);
}
std::string ETS::url::protocol()
{
    return protocol_;
}
std::string ETS::url::host()
{
    return host_;
}
std::string ETS::url::path()
{
    return path_;
}
std::string ETS::url::query()
{
    return query_;
}
std::string ETS::url::queryArr()
{
    return queryArr_;
}
std::string ETS::url::queryArr2()
{
    return queryArr2_;
}
bool ETS::url::to_bool(std::string const& s) 
{
    return s != "0";
}
std::vector<std::string> ETS::url::extractparams(std::string rawparams)
{
    std::vector<std::string> strings;
    std::istringstream frmt(rawparams);
    std::string stmp;

    while (std::getline(frmt, stmp, '=')) 
    {
        std::cout << stmp << std::endl;
        strings.push_back(stmp);
    }   
    return strings;
}
void ETS::url::parse(const std::string& url_s)
{
    const string prot_end("/");
    string::const_iterator prot_i = search(url_s.begin(), url_s.end(),
            prot_end.begin(), prot_end.end());
    protocol_.reserve(distance(url_s.begin(), prot_i));
    transform(url_s.begin(), prot_i,
            back_inserter(protocol_),
            [](int c) { return std::tolower(c); });

    advance(prot_i, prot_end.length());

    string::const_iterator query_i = find(prot_i, url_s.end(), '?');
    path_.assign(prot_i, query_i);
    
    if( query_i != url_s.end() )
    {
        ++query_i;
    }

    string::const_iterator queryArr_i = find(query_i, url_s.end(), '&');
    query_.assign(query_i, queryArr_i);
    if( queryArr_i != url_s.end() )
    {
        ++queryArr_i;
    }
    
    string::const_iterator queryArr_i2 = find(queryArr_i, url_s.end(), '&');
    queryArr_.assign(queryArr_i, queryArr_i2);
    if( queryArr_i2 != url_s.end() )
    {
        ++queryArr_i2;
    }
    queryArr2_.assign(queryArr_i2, url_s.end());
}

