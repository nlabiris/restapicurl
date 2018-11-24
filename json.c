#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include "json.h"

Post get_post(json_t *data) {
    json_t *user_id;
    json_t *id;
    json_t *title;
    json_t *body;
    Post post;

    user_id = json_object_get(data, "userId");
    if(json_is_integer(user_id)) {
        post.user_id = json_integer_value(user_id);
    }

    id = json_object_get(data, "id");
    if(json_is_integer(id)) {
        post.id = json_integer_value(id);
    }

    title = json_object_get(data, "title");
    if(json_is_string(title)) {
        post.title = malloc(json_string_length(title) + 1);
        strcpy(post.title, json_string_value(title));
    }

    body = json_object_get(data, "body");
    if(json_is_string(body)) {
        post.body = malloc(json_string_length(body) + 1);
        strcpy(post.body, json_string_value(body));
    }

    return post;
}

void parse_json(char *data) {
    json_t *root;
    json_t *element;
    json_error_t error;
    Post post;
    int i = 0;

    root = json_loads(data, 0, &error);

    json_array_foreach(root, i, element){
        post = get_post(element);
        printf("%d %s\n", post.id, post.title);
    }

    json_decref(root);
}