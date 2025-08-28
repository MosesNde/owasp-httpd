#include <stdio.h>
#include <stdlib.h>

int vulnerable_server_request(const char *url) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "curl -s '%s'", url);
    return system(cmd);
}