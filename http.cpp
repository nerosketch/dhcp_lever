#include <sstream>
#include <curl/curl.h>
#include "textUtils.h"
#include "http.h"


size_t writeFunction(void *ptr, size_t size, size_t nmemb, string* data)
{
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}


string http_get(const string& url)
{
    auto curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        //curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "djing_client");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10L);
        //curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, CURL_ERROR_SIZE);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        string response_string;
        string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        char* url;
        long response_code;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;

        return response_string;
    }

    return "";
}

