#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
int make_vulnerable_request(const char *url) {
    CURL *curl = curl_easy_init();
    if (!curl) return -1;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
        return -1;
    }
    return 0;
}