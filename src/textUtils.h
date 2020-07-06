/* 
 * File:   textUtils.h
 * Author: ns
 *
 * Created on February 13, 2019, 11:47 PM
 */

#ifndef TEXTUTILS_H
#define TEXTUTILS_H

#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include "types.h"


using namespace std;


/*
 * Thanks for user whoan.
 * https://stackoverflow.com/a/27992321
 */
string join(const strings& data, const char *delim="_");


string url_join(const dict&);


#endif /* TEXTUTILS_H */

