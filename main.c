#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"

int main(int argc, char **argv) {
    // char endpoint[50] = "/posts";
    // char *body = "{ \"title\": \"foo foo\", \"body\": \"bar\", \"userId\": 1 }";
    // Response s = post(endpoint, body);

    char endpoint[50] = "/posts/10";
    Response s = get(endpoint, NULL, NULL);
    
    // char endpoint[50] = "/posts/101";
    // char *body = "{ \"title\": \"foo foo\", \"body\": \"bar\", \"userId\": 1 }";
    // Response s = delete(endpoint, NULL);
    printf("\n%s\n", s.data);
    free(s.data);
    return EXIT_SUCCESS;
}
