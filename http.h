/* 
 * File:   http.h
 * Author: ns
 *
 * Created on February 13, 2019, 12:30 AM
 */

#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <map>
#include "types.h"

using namespace std;

typedef map<string, string> dict;


string http_get(const string& url);

#endif /* HTTP_H */

