typedef struct _response {
    char *data;
    size_t len;
} Response;

typedef struct _headers {
    char **data;
    int columns;
    int rows;
} Headers;

typedef struct _request {
    char method[10];
    char *endpoint;
    Headers headers;
    char *body;
    char *params;
} Request;

typedef struct _api {
    char *domain;
    Headers headers;
} Api;

// typedef struct _request {
//     char *data;
//     size_t size;
//     size_t pos;
// } Request;

void init_response(Response *response);
size_t writefunc(void *ptr, size_t size, size_t nmemb, void *stream);
size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream);
Response get(const Api *api, const Request *req);
Response post(const Api *api, const Request *req);
Response put(const Api *api, const Request *req);
Response delete(const Api *api, const Request *req);
Response request(char *domain, const char *method, const char *endpoint, const Headers headers, const char *body, const char *params);

void init_api(Api *api, const char *domain);
void set_global_headers(Api *api, const char **headers);
void clear_global_headers(Api *api);
void destroy_api(Api *api);