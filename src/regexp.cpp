/* 
 * File:   regexp.cpp
 * Author: ns
 * 
 * Created on February 14, 2019, 1:20 AM
 */

#include <regex>
#include "regexp.h"


const static string MAC_ADDR_REGEX = "^([0-9A-Fa-f]{1,2}[:-]){5}([0-9A-Fa-f]{1,2})$";

const static string IP_ADDR_REGEX =
    "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";


string _val(const string& str, const string& reg)
{
    regex re(reg);
    smatch m;
    regex_search(str, m, re);
    return m.str();
}


namespace regexp
{
    string validate_ip(const string& ip)
    {
        return _val(ip, IP_ADDR_REGEX);
    }

    string validate_mac(const string& mac)
    {
        return _val(mac, MAC_ADDR_REGEX);
    }

    string validate_int(const string& s)
    {
        // if `s` is number
        if(!s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end())
        {
            return s;
        }
        throw runtime_error(s + " is not number");
    }
}
