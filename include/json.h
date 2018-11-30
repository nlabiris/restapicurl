#ifndef H_JSON
#define H_JSON

#include <jansson.h>

typedef struct _post {
    int user_id;
    int id;
    char *title;
    char *body;
} Post;

Post *get_post(json_t *data);
void parse_json(char *data);

#endif