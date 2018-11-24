#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <curl/curl.h>
#include <jansson.h>
#include "api.h"

void init_response(Response *response) {
    response->len = 0;
    response->body = malloc(response->len+1);
    if (response->body == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    response->body[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, void *stream) {
    if (stream) {
        Response *response = (Response *)stream;
        size_t new_len = response->len + size * nmemb;
        response->body = realloc(response->body, new_len + 1);
        if (response->body == NULL) {
            fprintf(stderr, "realloc() failed\n");
            exit(EXIT_FAILURE);
        }
        memcpy(response->body + response->len, ptr, size * nmemb);
        response->body[new_len] = '\0';
        response->len = new_len;
        return size * nmemb;
    }
    return 0;
}

Response request(char *domain, char *method, char *endpoint, char *body, char *params) {
    Response response;
    char *url = (char *)malloc((strlen(domain) + strlen(endpoint) + 10) * sizeof(char));
    CURL *curl = NULL;
    // CURLcode res;
    struct curl_slist *curl_headers = NULL;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    init_response(&response);

    if(curl) {
        strcpy(url, domain);
        strcat(url, endpoint);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
        curl_headers = curl_slist_append(curl_headers, "Accept: application/json");
        curl_headers = curl_slist_append(curl_headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        if (!strcmp(method, "GET") && body != NULL) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(curl_headers);
        curl_global_cleanup();
    }
    free(url);

    return response;
}

Response get(Api api, Request req) {
    return request(api.domain, "GET", req.endpoint, req.body, req.params);
}

Response post(Api api, Request req) {
    return request(api.domain, "POST", req.endpoint, req.body, req.params);
}

Response put(Api api, Request req) {
    return request(api.domain, "PUT", req.endpoint, req.body, req.params);
}

Response delete(Api api, Request req) {
    return request(api.domain, "DELETE", req.endpoint, req.body, req.params);
}

void init_api(Api *api, char *domain) {
    api->domain = (char *)malloc((strlen(domain) + 1) * sizeof(char));
    strcpy(api->domain, domain);
}

Request create(char *endpoint, char *body, char *params) {
    Request request;
    if (endpoint != NULL) {
        request.endpoint = (char *)malloc((strlen(endpoint) + 1) * sizeof(char));
        strcpy(request.endpoint, endpoint);
    } else {
        request.endpoint = NULL;
    }
    if (body != NULL) {
        request.body = (char *)malloc((strlen(body) + 1) * sizeof(char));
        strcpy(request.body, body);
    } else {
        request.body = NULL;
    }
    request.params = NULL;

    return request;
}

void cleanup(Request *request, Response *response) {
    if (request->endpoint != NULL) {
        free(request->endpoint);
        request->endpoint = NULL;
    }        
    if (request->body != NULL) {
        free(request->body);
        request->body = NULL;
    }
    if (request->params != NULL) {
        free(request->params);
        request->params = NULL;
    }
    if (response->body != NULL) {
        free(response->body);
        response->body = NULL;
    }
}

void destroy_api(Api *api) {
    free(api->domain);
    api->domain = NULL;
}