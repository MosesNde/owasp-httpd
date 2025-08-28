#include <stdio.h>
#include <stdlib.h>

void fetch_url(const char *url) {
    char command[512];
    snprintf(command, sizeof(command), "curl -s '%s'", url);
    system(command);
}