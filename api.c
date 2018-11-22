#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <curl/curl.h>
#include <jansson.h>
#include "api.h"

void init_response(Response *response) {
    response->len = 0;
    response->data = malloc(response->len+1);
    if (response->data == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    response->data[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, void *stream) {
    if (stream) {
        Response *response = (Response *)stream;
        size_t new_len = response->len + size * nmemb;
        response->data = realloc(response->data, new_len + 1);
        if (response->data == NULL) {
            fprintf(stderr, "realloc() failed\n");
            exit(EXIT_FAILURE);
        }
        memcpy(response->data + response->len, ptr, size * nmemb);
        response->data[new_len] = '\0';
        response->len = new_len;
        return size * nmemb;
    }
    return 0;
}

// size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
//     if (stream) {
//         Request *s = (Request *)stream;
//         int available = (s->size - s->pos);
//         if (available > 0) {
//             int written = fmin(size * nmemb, available);
//             memcpy(ptr, ((char*)(s->data)) + s->pos, written);
//             s->pos += written;
//             return written;
//         }
//     }
//     return 0;
// }

Response request(char *domain, const char *method, const char *endpoint, const Headers headers, const char *body, const char *params) {
    Response response;
    // char domain[80] = "https://jsonplaceholder.typicode.com";
    CURL *curl = NULL;
    // CURLcode res;
    struct curl_slist *curl_headers = NULL;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    init_response(&response);

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_headers = curl_slist_append(curl_headers, "Accept: application/json");
        curl_headers = curl_slist_append(curl_headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
        curl_easy_setopt(curl, CURLOPT_URL, strcat(domain, endpoint));
        if (strcmp(method, "GET") && body != NULL) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(curl_headers);
        curl_global_cleanup();
    }

    return response;
}

Response get(const Api *api, const Request *req) {
    return request(api->domain, "GET", req->endpoint, req->headers, NULL, req->params);
}

Response post(const Api *api, const Request *req) {
    return request(api->domain, "POST", req->endpoint, req->headers, req->body, req->params);
}

Response put(const Api *api, const Request *req) {
    return request(api->domain, "PUT", req->endpoint, req->headers, req->body, req->params);
}

Response delete(const Api *api, const Request *req) {
    return request(api->domain, "DELETE", req->endpoint, req->headers, req->body, req->params);
}

void set_global_headers(Api *api, const char **headers) {
    int i = 0;
    if (headers) {
        for(i = 0; i < api->headers.rows; i++) {
            strcpy(api->headers.data[i], headers[i]);
        }
    }
}

void clear_global_headers(Api *api) {
    int i = 0;
    for(i = 0; i < api->headers.rows; i++) {
        free(api->headers.data[i]);
    }
    free(api->headers.data);
    api->headers.data = NULL;
}

void init_api(Api *api, const char *domain) {
    api->domain = (char *)malloc(strlen(domain) * sizeof(char));
    strcpy(api->domain, domain);
}

void destroy_api(Api *api) {
    free(api->domain);
    free(api);
    api->domain = NULL;
    api = NULL;

}