typedef struct _response {
    char *body;
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
} Api;

void init_response(Response *response);
size_t writefunc(void *ptr, size_t size, size_t nmemb, void *stream);
size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream);
Response get(Api api, Request req);
Response post(Api api, Request req);
Response put(Api api, Request req);
Response delete(Api api, Request req);
Response request(char *domain, char *method, char *endpoint, char *body, char *params);

void init_api(Api *api, char *domain);
Request create(char *endpoint, char *body, char *params);
void cleanup(Request *request, Response *response);
void destroy_api(Api *api);