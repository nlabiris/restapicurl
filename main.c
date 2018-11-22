#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"

int main(int argc, char **argv) {
    // char endpoint[50] = "/posts";
    // char *body = "{ \"title\": \"foo foo\", \"body\": \"bar\", \"userId\": 1 }";
    // Response s = post(endpoint, body);

    char endpoint[50] = "/posts/10";
    Api *api = malloc(sizeof(Api));
    Request *request = malloc(sizeof(Request));
    init_api(api, "https://jsonplaceholder.typicode.com");
    printf("\n%s\n", api->domain);
    strcpy(request->endpoint, endpoint);
    Response response = get(api, request);
    // char endpoint[50] = "/posts/101";
    // char *body = "{ \"title\": \"foo foo\", \"body\": \"bar\", \"userId\": 1 }";
    // Response s = delete(endpoint, NULL);
    printf("\n%s\n", response.data);
    free(response.data);
    destroy_api(api);
    return EXIT_SUCCESS;
}
