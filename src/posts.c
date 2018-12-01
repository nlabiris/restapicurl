#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include "posts.h"
#include "list.h"

Post *get_post(char *data) {
    json_t *root;
    json_error_t error;
    Post *post;

    root = json_loads(data, 0, &error);

    if (json_is_object(root)) {
        post = parse_json(root);
        printf("%d %s\n", post->id, post->title);
    }

    json_decref(root);

    return post;
}

List *get_posts(char *data) {
    json_t *root;
    json_t *element;
    json_error_t error;
    Post *post;
    List *list = (List *)malloc(sizeof(List));
    int i = 0;

    root = json_loads(data, 0, &error);
    initializeList(&list);

    if(json_is_array(root)) {
        json_array_foreach(root, i, element) {
            post = parse_json(element);
            addHead(&list, post);
            free(post);
        }
    }
    
    json_decref(root);

    return list;
}

Post *parse_json(json_t *data) {
    json_t *user_id;
    json_t *id;
    json_t *title;
    json_t *body;
    Post *post = (Post *)malloc(sizeof(Post));

    user_id = json_object_get(data, "userId");
    if(json_is_integer(user_id)) {
        post->user_id = json_integer_value(user_id);
    }

    id = json_object_get(data, "id");
    if(json_is_integer(id)) {
        post->id = json_integer_value(id);
    }

    title = json_object_get(data, "title");
    if(json_is_string(title)) {
        post->title = malloc(json_string_length(title) + 1);
        strcpy(post->title, json_string_value(title));
    }

    body = json_object_get(data, "body");
    if(json_is_string(body)) {
        post->body = malloc(json_string_length(body) + 1);
        strcpy(post->body, json_string_value(body));
    }

    return post;
}