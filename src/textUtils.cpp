#include "textUtils.h"


/*
 * Thanks for user whoan.
 * https://stackoverflow.com/a/27992321
 */
string join(const strings& data, const char *delim)
{
    ostringstream res;
    copy(data.begin(), data.end(),
           ostream_iterator<string>(res, delim));

    const string& sr = res.str();
    return sr.substr(0, sr.size() - 1);
}


string url_join(const dict& data)
{
    strings pairs;
    for(const auto& kv : data)
    {
        ostringstream param;
        param << kv.first << '=' << kv.second;
        pairs.push_back(param.str());
    }

    const string& params_str = join(pairs, "&");
    return params_str.c_str();
}
