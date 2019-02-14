#include "textUtils.h"


/*
 * Thanks for user whoan.
 * https://stackoverflow.com/a/27992321
 */
string join(const vector<string>& data, const char *delim)
{
    ostringstream res;
    copy(data.begin(), data.end(),
           ostream_iterator<string>(res, delim));

    const string& sr = res.str();
    return sr.substr(0, sr.size() - 1);
}
