#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

void perform_request(const char *url) {
    CURL *curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            printf("Request failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
}