/* 
 * File:   regexp.h
 * Author: ns
 *
 * Created on February 14, 2019, 1:20 AM
 */

#ifndef REGEXP_H
#define REGEXP_H

#include <string>

using namespace std;


namespace regexp
{
    string validate_ip(const string&);

    string validate_mac(const string&);

    string validate_int(const string&);
}



#endif /* REGEXP_H */

