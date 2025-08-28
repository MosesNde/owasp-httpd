#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

char *fetch_url(const char *url) {
    CURL *curl = curl_easy_init();
    if (!curl) return NULL;
    CURLcode res;
    char *data = malloc(1024);
    if (!data) {
        curl_easy_cleanup(curl);
        return NULL;
    }
    data[0] = '\0';
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
        free(data);
        return NULL;
    }
    return data;
}