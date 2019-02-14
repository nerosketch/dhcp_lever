/* 
 * File:   configs.cpp
 * Author: ns
 * 
 * Created on February 14, 2019, 2:49 PM
 */
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include "configs.h"


void parse(dict& options, ifstream& cfgfile)
{
    for (string line; getline(cfgfile, line); )
    {
        istringstream iss(line);
        string id, eq, val;

        bool error = false;

        if (!(iss >> id))
        {
            error = true;
        }
        else if (id[0] == '#')
        {
            continue;
        }
        else if (!(iss >> eq >> val >> std::ws) || eq != "=" || iss.get() != EOF)
        {
            error = true;
        }

        if (error)
        {
            // do something appropriate: throw, skip, warn, etc.
            cerr << "Error: failed read config" << endl;
        }
        else
        {
            options[id] = val;
        }
    }
}

namespace Conf
{

    bool readConfig(CONFIG& conf, const string& fname)
    {
        ifstream f(fname);
        if(f)
        {
            dict opts;
            parse(opts, f);

            dict::iterator opt = opts.find("api_auth_secret");
            if(opt != opts.end())
                conf.api_auth_secret = opt->second;

            opt = opts.find("url");
            if(opt != opts.end())
                conf.url = opt->second;

            f.close();
            return true;
        }
        return false;
    }

}