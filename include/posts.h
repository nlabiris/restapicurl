#ifndef H_POSTS
#define H_POSTS

#include <jansson.h>
#include "list.h"

typedef struct _post {
    int user_id;
    int id;
    char *title;
    char *body;
} Post;

Post *get_post(char *data);
List *get_posts(char *data);
Post *parse_json(json_t *data);

#endif