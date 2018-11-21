typedef struct _response {
    char *data;
    size_t len;
} Response;

typedef struct _request {
    char method[10];
    char *endpoint;
    typedef struct _headers {
        char **data;
        int columns;
        int rows;
    } headers;
    char *body;
    char *params;
} Request;

typedef struct _api {
    char *domain;
    typedef struct _headers {
        char **data;
        int columns;
        int rows;
    } headers;
} Api;

// typedef struct _request {
//     char *data;
//     size_t size;
//     size_t pos;
// } Request;

void init_response(Response *response);
size_t writefunc(void *ptr, size_t size, size_t nmemb, void *stream);
size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream);
Response get(Request *request);
Response post(Request *request);
Response put(Request *request);
Response delete(Request *request);
Response request(Request *request);

void init_api(Api *api);
void set_global_headers(Api *api, const char **headers);
void clear_global_headers(Api *api);
void destroy_api(Api *api);