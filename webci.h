#ifndef WEBCI_H
#define WEBCI_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <curl/curl.h>

#define BUFFER_SIZE 4096
#define MAX_COOKIES 10
#define V 200
#define Q 50
#define ERROR -1
#define OK 2
#define WEB_TRUE 1
#define WEB_FALSE 0
#define WEB_OK 1
#define WEB_ERROR -5
#define SMTP_TEXT 500
#define _POST char *post
#define POST post
#define _GET char *get
#define GET get
#define IMAGE_PNG_FILE "image/png"
#define IMAGE_JPEG_FILE "image/jpeg"
#define VIDEO_MP4_FILE "video/mp4"
#define OCTET_STREAM_FILE "application/octet-stream"
#define ANDROID_APP_FILE "application/vnd.android.package-archive"
#define HAVE_FILE "Content-Length"
#define IS_ACTIVE 200
#define IS_NO_ACTIVE -200

typedef unsigned char results;
typedef char *PAGE_URL;
typedef char *WEB_FILES;
typedef char *String;
typedef int array;

struct Server{
    int server_fd, new_socket, valread, client_socket;
    struct sockaddr_in address, client_address;
    socklen_t client_address_length;
    int opt;
    int addrlen;
    int error;
    int port;
    int buffer_size;
    char cookie_time[30];
    char cookie_file_name[V];
    int cookie_active;
};

typedef struct{
    char smtp_url[V];
    char user_smtp[V];
    char password_smtp[V];
    char mail_from[V];
    char recipient[V];
    char payload_text[SMTP_TEXT];
} smtp_email;

typedef struct{
    char current_date[20];
    char hour[9];
} Date;

typedef struct{
    struct{
        array range;
        array Array[100];
    } Int;
    struct{
        array range;
        String Array[100];
    } string;
    struct{
        array range;
        results Array[100];
    } Result;
    struct{
        array range;
        PAGE_URL Array[100];
    } Pages_url;
    struct{
        array range;
        WEB_FILES Array[100];
    } Web_files;
    array i;
} Array;

char buffer[BUFFER_SIZE] = {0};
char buffer_2[BUFFER_SIZE][BUFFER_SIZE];
char *_post;
char *_get;
char cookie_value[30];

void where(unsigned const char *condition, void (*func_1)(), void (*func_2)()){
    if (condition){
        func_1;
    }
    else{
        func_2;
    }
}

void cat_str(const char *texto1, const char *texto2, char *resultado){
    strcpy(resultado, texto1);
    strcat(resultado, texto2);
}

void split_lines(const char *text){
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        printf("%s\n", line);
        line = strtok(NULL, "\n");
    }
    free(text_copy);
}

int search_words(const char *text, const char *word){
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        if (strstr(line, word) != NULL){
            return WEB_OK;
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

int buscaPalabra(const char *cadena, const char *palabra){
    int contador = 0;
    char *copia = strdup(cadena);
    char *token = strtok(copia, " ");
    while (token != NULL){
        if (strcmp(token, palabra) == 0){
            contador++;
        }
        token = strtok(NULL, " ");
    }
    free(copia);
    if (contador < 0){
        return ERROR;
    }
    return contador;
}

Array *array_int(Array *Array, ...){
    array *Arra = malloc(Array->Int.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->Int.range);
    for (Array->i = 0; Array->i < Array->Int.range; Array->i++){
        array x = va_arg(valist, array);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->Int.range; Array->i++){
        Array->Int.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

Array *array_results(Array *Array, ...){
    array *Arra = malloc(Array->Result.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->Int.range);
    for (Array->i = 0; Array->i < Array->Result.range; Array->i++){
        results x = va_arg(valist, results);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->Result.range; Array->i++){
        Array->Result.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

Array *array_web_files(Array *Array, ...){
    array *Arra = malloc(Array->Web_files.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->Web_files.range);
    for (Array->i = 0; Array->i < Array->Web_files.range; Array->i++){
        WEB_FILES x = va_arg(valist, WEB_FILES);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->Int.range; Array->i++){
        Array->Web_files.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

Array *array_page_url(Array *Array, ...){
    array *Arra = malloc(Array->Pages_url.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->Pages_url.range);
    for (Array->i = 0; Array->i < Array->Pages_url.range; Array->i++){
        PAGE_URL x = va_arg(valist, PAGE_URL);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->Pages_url.range; Array->i++){
        Array->Pages_url.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

Array *array_String(Array *Array, ...){
    array *Arra = malloc(Array->string.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->string.range);
    for (Array->i = 0; Array->i < Array->string.range; Array->i++){
        String x = va_arg(valist, String);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->string.range; Array->i++){
        Array->Int.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

void get_date(Date *date){
    time_t tiempo;
    struct tm *tm_info;
    time(&tiempo);
    tm_info = localtime(&tiempo);
    strftime(date->current_date, 20, "%Y-%m-%d", tm_info);
}

void get_time(Date *date){
    time_t tiempo;
    struct tm *tm_info;
    time(&tiempo);
    tm_info = localtime(&tiempo);
    strftime(date->hour, 9, "%H:%M:%S", tm_info);
}

int time_cmp(Date *date, const String other_hour){
    if (strcmp(date->hour, other_hour)){
        return WEB_TRUE;
    }
    return WEB_FALSE;
}

int date_cmp(Date *date, const String other_date){
    if (strcmp(date->current_date, other_date)){
        return WEB_TRUE;
    }
    return WEB_FALSE;
}

int date_cmp_func(Date *date, const String other_date, void (*func)()){
    if (strcmp(date->current_date, other_date)){
        func;
    }
    return WEB_FALSE;
}

int time_cmp_func(Date *date, const String other_hour, void (*func)()){
    if (strcmp(date->hour, other_hour)){
        func;
    }
    return WEB_FALSE;
}

int create_base_data(const String name, const String create_table_query){
    sqlite3 *db;
    char *error_message = 0;
    int result = sqlite3_open(name, &db);
    if (result != SQLITE_OK){
        printf("[Server]: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return WEB_ERROR;
    }
    result = sqlite3_exec(db, create_table_query, 0, 0, &error_message);
    if (result != SQLITE_OK){
        printf("[Server]: %s\n", error_message);
        sqlite3_free(error_message);
        sqlite3_close(db);
        return WEB_ERROR;
    }
    sqlite3_close(db);
    return OK;
}

int insert_database(const String name_base, int total_data, const String sql, String insert, ...){
    sqlite3 *db;
    char *err_msg = 0;
    int rc, i;
    String chonps;
    rc = sqlite3_open(name_base, &db);
    if (rc != SQLITE_OK){
        fprintf(stderr, "[Server]: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return WEB_ERROR;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK){
        fprintf(stderr, "[Server]: %s\n", sqlite3_errmsg(db));
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return WEB_ERROR;
    }
    char insert_query[100];
    va_list args;
    va_start(args, insert);
    for (i = 0; i < total_data + 1 - 1; i++){
        String count = va_arg(args, String);
        sprintf(insert_query, insert, count, chonps);
    }
    va_end(args);
    rc = sqlite3_exec(db, insert_query, 0, 0, &err_msg);
    if (rc != SQLITE_OK){
        fprintf(stderr, "[Server]: %s\n", sqlite3_errmsg(db));
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return WEB_ERROR;
    }
    sqlite3_close(db);
    return OK;
}

int search_database(const String name, const String query, int start, int (*callback)()){
    if (start != 0){
        sqlite3 *db;
        char *error_msg = 0;
        int rc = sqlite3_open(name, &db);
        if (rc != SQLITE_OK){
            fprintf(stderr, "[Server]: %s\n", sqlite3_errmsg(db));
            return ERROR;
        }
        rc = sqlite3_exec(db, query, callback, 0, &error_msg);
        if (rc != SQLITE_OK){
            fprintf(stderr, "[Server]: %s\n", error_msg);
            sqlite3_free(error_msg);
            sqlite3_close(db);
            return ERROR;
        }
        sqlite3_close(db);
    }
}

int create_cookie(struct Server *server, const char *request, const char *data_cookie){
    recv(server->valread, request, BUFFER_SIZE, 0);
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char response[BUFFER_SIZE];
    FILE *fp = fopen(server->cookie_file_name, "w");
    if (fp == NULL){
        perror("[Server] ");
        return WEB_ERROR;
    }
    else{
        fprintf(fp, "%s", data_cookie);
    }
    close(server->valread);
    fclose(fp);
    server->cookie_active = IS_ACTIVE;
    return IS_ACTIVE;
}

int remove_cookie(struct Server *server){
    if (remove(server->cookie_file_name) == ERROR){
        perror("[Server] ");
        return WEB_ERROR;
    }
    server->cookie_active = IS_NO_ACTIVE;
    return OK;
}

String read_cookie(struct Server *servidor, const char *request){
    recv(servidor->valread, request, BUFFER_SIZE, 0);
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(servidor->cookie_time, sizeof(servidor->cookie_time), "%Y-%m-%d %H:%M:%S", tm_info);
    char response[BUFFER_SIZE];
    char data[BUFFER_SIZE];
    FILE *cookie = fopen(servidor->cookie_file_name, "r");
    if (cookie == NULL){
        perror("[Server] ");
        return WEB_ERROR;
    }
    else{
        while (feof(cookie) == 0){
            fgets(data, BUFFER_SIZE, cookie);
            snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", data);
        }
    }
    close(servidor->valread);
    fclose(cookie);
    return response;
}

char *get_POST(const char *text, const char *word, int ini, int end_index){
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                return result;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

char *get_GET(const char *text, const char *word, int ini, int end_index, struct Server *server){
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    char response[BUFFER_SIZE];
    size_t bytesRead;
    FILE *fp;
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                fp = fopen(result, "r");
                if (fp == NULL){
                    return WEB_ERROR;
                }
                while ((bytesRead = fread(response, 1, sizeof(response), fp)) > 0){
                    send(server->client_socket, response, bytesRead, 0);
                }
                fclose(fp);
                close(server->client_socket);
                return WEB_OK;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

char *get_platform(const char *text, int platform){
    char *android = "\"Android\"";
    char *linux = "\"Linux\"";
    char *windows = "\"Windows\"";
    char *word;
    int ini = 1;
    int end_index;

    if (platform == 7){
        end_index = 7;
        word = android;
    }
    if (platform == 5){
        end_index = 6;
        word = linux;
    }
    if (platform == 8){
        end_index = 7;
        word = windows;
    }
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                return result;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

int send_email(smtp_email *email){
    CURL *curl;
    CURLcode res = CURLE_OK;
    curl = curl_easy_init();

    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, email->smtp_url);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, email->mail_from);
        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, email->recipient);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_USERNAME, email->user_smtp);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, email->password_smtp);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, email->payload_text);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "[Server]: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
    return (int)res;
}

char *get_filename(const char *text, int end){
    char *word = "filename=\"";
    int ini = 9;
    int end_index = end;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                return result;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

char *get_type_file(const char *text){
    char *word = "Content-Type:";
    int ini = 13;
    int end_index;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                return result;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

char *get_Length_file(const char *text){
    char *word = "Content-Length: ";
    int ini = 15;
    int end_index = 100;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                return result;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

int save_response(const char *data){
    FILE *fp = fopen("data_response.txt", "a");
    if (fp == NULL){
        return WEB_ERROR;
    }
    fprintf(fp, "%s", data);
    fclose(fp);
    return WEB_OK;
}

char *get_response(){
    return buffer;
}

void server_file_response(int client_socket, const char *content_type, const char *content){
    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %lu\n\n%s", content_type, strlen(content), content);
    write(client_socket, response, strlen(response));
}

int send_response_inst(struct Server *server, const char *response){
    if (listen(server->server_fd, 3) < 0){
        perror("[Server] ");
        return WEB_ERROR;
    }
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        perror("[Server] ");
        return WEB_ERROR;
    }
    char *response_2[BUFFER_SIZE];
    server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
    cat_str("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", response, response_2);
    write(server->new_socket, response_2, strlen(response_2));
    close(server->new_socket);
}

int send_response_varic(struct Server *server, int total,const char *response, ...){
    int i;
    if (listen(server->server_fd, 3) < 0){
        perror("[Server] ");
        return WEB_ERROR;
    }
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        perror("[Server] ");
        return WEB_ERROR;
    }
    char *response_2[BUFFER_SIZE], response_total[BUFFER_SIZE];
    if(total < 1){
        server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
        cat_str("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", response, response_2);
        server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
        write(server->new_socket, response_2, strlen(response_2));
         close(server->new_socket);
         return OK;
    } else {
        va_list args;
        va_start(args, response);
        for (i = 0; i < total + 1 - 1; i++){
             String count = va_arg(args, String);
             sprintf(response_2, response, count);
        }
        va_end(args);
        cat_str("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n",response_2,response_total);
        server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
        write(server->new_socket, response_total, strlen(response_total));
        close(server->new_socket);
    }
}

int start_server_file(struct Server *server){
    server->opt = 1;
    server->addrlen = sizeof(server->address);
    if ((server->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("[Server] ");
        return ERROR;
    }
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &server->opt, sizeof(server->opt))){
        perror("[Server] ");
        return ERROR;
    }
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    if (bind(server->server_fd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0){
        perror("[Server] ");
        return ERROR;
    }
    if (listen(server->server_fd, 3) < 0){
        perror("[Server] ");
        return ERROR;
    }
}

int listen_server_file(struct Server *server, const char *archivo){
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        perror("[Server] ");
        return ERROR;
    }
    server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
    FILE *file = fopen(archivo, "r");
    if (file == NULL){
        perror("[Server] ");
        return ERROR;
    }
    char html_content[server->buffer_size];
    size_t html_size = fread(html_content, sizeof(char), server->buffer_size, file);
    fclose(file);
    server_file_response(server->new_socket, "text/html", html_content);
    printf("[Server]: Respuesta enviada\n");
    close(server->new_socket);
}

void ini_server(struct Server *S){
    S->opt = 1;
    S->addrlen = sizeof(S->address);
    S->error = OK;
}

int config_server(struct Server *S){
    S->error = ERROR;
    if ((S->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("[Server] ");
        return S->error;
    }
    if (setsockopt(S->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &S->opt, sizeof(S->opt))){
        perror("[Server] ");
        return S->error;
    }
    S->address.sin_family = AF_INET;
    S->address.sin_addr.s_addr = INADDR_ANY;
    S->address.sin_port = htons(S->port);
    if (bind(S->server_fd, (struct sockaddr *)&S->address, sizeof(S->address)) < 0){
        perror("[Server] ");
        return S->error;
    }
}

int listen_server(struct Server *S, const char *response){
    if (listen(S->server_fd, 3) < 0){
        perror("[Server] ");
        return S->error;
    }
    if ((S->new_socket = accept(S->server_fd, (struct sockaddr *)&S->address, (socklen_t *)&S->addrlen)) < 0){
        perror("[Server] ");
        return S->error;
    }
    S->valread = read(S->new_socket, buffer, BUFFER_SIZE);
    write(S->new_socket, response, strlen(response));
    printf("[Server]: Respuesta enviada\n");
    close(S->new_socket);
}
#endif
