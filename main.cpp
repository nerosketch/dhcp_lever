/* 
 * File:   main.cpp
 * Author: ns
 *
 * Created on February 13, 2019, 11:10 PM
 */

#include <algorithm>
#include <iostream>
#include <sstream>

#include <curl/curl.h>
#include "http.h"
#include "sha256.h"
#include "textUtils.h"
#include "regexp.h"
#include "types.h"
#include "configs.h"


using namespace std;


string make_sign(strings& data, const string& api_auth_secret)
{
    sort(data.begin(), data.end());
    data.push_back(api_auth_secret);

    string keys = join(data, "_");
    return sha256(keys);
}


bool send_to(dict& data, const string& server, const string& api_auth_secret)
{
    strings data_values;
    data_values.reserve(data.size());
    for(const auto& kv : data)
    {
        data_values.push_back(kv.second);
    }

    string sign = make_sign(data_values, api_auth_secret);
    data.insert(pair<string ,string>("sign", sign));

    ostringstream url;
    url << server << "?" << urlencode(data);
    string html = http_get(url.str());

    cout << html << endl;

    return true;
}


int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cerr << "Too few arguments, exiting..." << endl
             << "Usage:" << endl
             << "COMMIT: ./dhcp_lever.py commit 192.168.1.100 ff:12:c5:9f:12:56 98:45:28:85:25:1a 3" << endl
             << "EXPIRY or RELEASE: ./dhcp_lever.py [release |commit]" << endl;
        return 1;
    }
    
    Conf::CONFIG cnf;
    if(!Conf::readConfig(cnf, "params.cfg"))
    {
        cerr << "Failed read config" << endl;
        return 6;
    }

    if(cnf.api_auth_secret == "your api key")
    {
        cerr << "You must specified secret api key" << endl;
        return 2;
    }

    const string action = argv[1];

    if(action == "commit")
    {
        if(argc < 6)
        {
            cerr << "Too few arguments, exiting..." << endl;
            return 3;
        }
        try{
            dict data = {
                {"client_ip", regexp::validate_ip(argv[2])},
                {"client_mac", regexp::validate_mac(argv[3])},
                {"switch_mac", regexp::validate_mac(argv[4])},
                {"switch_port", regexp::validate_int(argv[5])},
                {"cmd", action}
            };
            send_to(data, cnf.url, cnf.api_auth_secret);
        }catch(const exception& err)
        {
            cerr << "Error: " << err.what() << endl;
            return 4;
        }
    }else if(action == "expiry" || action == "release")
    {
        try{
            dict data = {
                {"client_ip", regexp::validate_ip(argv[2])},
                {"cmd", action}
            };
            send_to(data, cnf.url, cnf.api_auth_secret);
        }catch(const exception& err)
        {
            cerr << "Error: " << err.what() << endl;
            return 5;
        }
    }

    return 0;
}
