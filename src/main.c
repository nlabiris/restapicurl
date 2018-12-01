#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "posts.h"
#include "list.h"

int main(int argc, char **argv) {
    Api api;
    Request request;
    Response response;
    List *list;
    
    init_api(&api, "https://jsonplaceholder.typicode.com");
    
    request = create("/posts", NULL, NULL);
    response = get(api, request);
    list = get_posts(response.body);
    // printf("\n%s\n", response.body);

    // parse_json(response.body);

    // request = create("/posts", "{ \"title\": \"foo foo\", \"body\": \"bar\", \"userId\": 1 }", NULL);
    // response = post(api, request);
    // printf("\n%s\n", response.body);

    // request = create("/posts/1", "{ \"title\": \"foo foo test\", \"body\": \"bar\", \"userId\": 10 }", NULL);
    // Response response = put(api, request);

    // request = create("/posts/1", NULL, NULL);
    // Response response = delete(api, request);

    cleanup(&request, &response);
    freeList(&list);
    destroy_api(&api);

    return EXIT_SUCCESS;
}
