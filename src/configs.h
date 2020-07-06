/* 
 * File:   configs.h
 * Author: ns
 *
 * Created on February 14, 2019, 2:49 PM
 */

#ifndef CONFIGS_H
#define CONFIGS_H

#include <string>
#include "types.h"

using namespace std;


namespace Conf
{
    typedef struct
    {
        string api_auth_secret;
        string url;
    } CONFIG;

    bool readConfig(CONFIG& conf, const string& fname);
}


#endif /* CONFIGS_H */
