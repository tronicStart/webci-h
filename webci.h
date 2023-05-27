#ifndef WEBCI_H
#define WEBCI_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 4024
#define V 200
#define Q 50
#define ERROR -1
#define OK 0
#define WEB_TRUE 1
#define WEB_FALSE 0

struct data {
    
    char data[V];
    int condicion;
    char File_name[V];
    
};

struct Server {
    
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt;
    int addrlen;
    int error;
    int port;
    int buffer_size;
    
};

struct base_lite {
    
    char name_base[Q];
    char sql[Q];
    char insert_sql[Q];
    
};

char buffer[BUFFER_SIZE] = {0};
char buffer_2[BUFFER_SIZE][BUFFER_SIZE];

char * get_response (){
    
    return buffer;
    
}

char * get_response_2 (){
    
    int i,j;
    
    for(i = 0; i < BUFFER_SIZE; i++){
        for(j = 0; j < BUFFER_SIZE; j++){
            buffer_2[i][j] = buffer;
        }
    }
    
}

void server_file_response(int client_socket, const char *content_type, const char *content) {
    
    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %lu\n\n%s", content_type, strlen(content), content);
    write(client_socket, response, strlen(response));
    
}

int start_server_file (struct Server * server){
    
    server->opt = 1;
    server->addrlen = sizeof(server->address);
    
    if ((server->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("[Server] ");
        return ERROR;
    }
    
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &server->opt, sizeof(server->opt))) {
        perror("[Server] ");
        return ERROR;
    }
    
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    
    if (bind(server->server_fd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0) {
        perror("[Server] ");
        return ERROR;
    }
    
    if (listen(server->server_fd, 3) < 0) {
        perror("[Server] ");
        return ERROR;
    }
    
}

int listen_server_file (struct Server * server, const char * archivo){
    
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t*)&server->addrlen)) < 0) {
            perror("[Server] ");
            return ERROR;
        }
        
        server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
        
        FILE *file = fopen(archivo, "r");
        if (file == NULL) {
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

int buscaPalabra(const char* cadena, const char* palabra) {
    int contador = 0;
    char* copia = strdup(cadena);  // Copia la cadena de texto original

    char* token = strtok(copia, " ");  // Divide la cadena en palabras utilizando el espacio como delimitador

    while (token != NULL) {
        if (strcmp(token, palabra) == 0) {  // Compara la palabra actual con la palabra buscada
            contador++;
        }
        token = strtok(NULL, " ");  // Obtiene el siguiente token
    }

    free(copia);  // Libera la memoria asignada a la copia de la cadena
    
    if(contador < 0){
        return ERROR;
    }
    return contador;
}

int crear_sqlite_data (struct base_lite * base){
    
    sqlite3 *db;
    char *err_msg = 0;
    int rc;
    
    rc = sqlite3_open(base->name_base, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    rc = sqlite3_exec(db, base->sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al crear la %s: %s\n", base->sql, err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    
    char insert_sql[100];
    sprintf(insert_sql, base->insert_sql);
    
    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al insertar datos: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    
    sqlite3_close(db);
    
}

void ini_server (struct Server * S){
    
    S->opt = 1;
    S->addrlen = sizeof(S->address);
    S->error = OK;
    
}

int config_server (struct Server * S){
    
    S->error = ERROR;
    
    // Crear el socket
    if ((S->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("[Server] ");
        return S->error;
    }
    
    // Configurar opciones del socket
    if (setsockopt(S->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &S->opt, sizeof(S->opt))) {
        perror("[Server] ");
        return S->error;
    }
    
    S->address.sin_family = AF_INET;
    S->address.sin_addr.s_addr = INADDR_ANY;
    S->address.sin_port = htons(S->port);
    
    // Asociar el socket a la dirección y puerto
    if (bind(S->server_fd, (struct sockaddr *)&S->address, sizeof(S->address)) < 0) {
        perror("[Server] ");
        return S->error;
    }
}

int listen_server (struct Server * S, const char * response){
    // Escuchar por conexiones entrantes
    if (listen(S->server_fd, 3) < 0) {
        perror("[Server] ");
        return S->error;
    }
    
    // Aceptar conexiones entrantes y manejarlas
        if ((S->new_socket = accept(S->server_fd, (struct sockaddr *)&S->address, (socklen_t*)&S->addrlen)) < 0) {
            perror("[Server] ");
            return S->error;
        }

        // Leer la solicitud HTTP entrante
        S->valread = read(S->new_socket, buffer, BUFFER_SIZE);
        // Enviar la respuesta HTTP al cliente
        write(S->new_socket, response, strlen(response));
        printf("[Server]: Respuesta enviada\n");

        close(S->new_socket);
    
}

void send_new_page (struct Server * S, const char * response){
    
    listen_server(&S,response);
    
}

int _server_html_ (const char * response, int PORT, struct data * Data){
    
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("[Server] ");
        exit(EXIT_FAILURE);
    }

    // Configurar opciones del socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("[Server] ");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Asociar el socket a la dirección y puerto
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("[Server] ");
        exit(EXIT_FAILURE);
    }

    // Escuchar por conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        perror("[Server] ");
        exit(EXIT_FAILURE);
    }

    printf("[Server]: Servidor html iniciado. Esperando conexiones...\nEnlace: http://localhost:%i\n",PORT);

    // Aceptar conexiones entrantes y manejarlas
    while(Data->condicion) {
        
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("[Server] ");
            exit(EXIT_FAILURE);
        }

        // Leer la solicitud HTTP entrante
        valread = read(new_socket, buffer, BUFFER_SIZE);
        printf("[Server]: Solicitud recibida:\n%s\n", buffer);
        
        strcpy(Data->data,buffer);

        // Enviar la respuesta HTTP al cliente
        write(new_socket, response, strlen(response));
        printf("[Server]: Respuesta enviada\n");

        // Cerrar la conexión
        close(new_socket);
    }
    return 0;
}

int save_data_buffer_server (struct data * Data){
    
    FILE * dat = fopen(Data->File_name,"a");
    
    if(dat == NULL){
        return -1;
    }
    
    fprintf(dat,"%s\n",Data->data);
    fclose(dat);
    
    return 0;
    
}

#endif
