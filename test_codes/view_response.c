//Codigo mostrar las solicitudes o respuestas del navegador
#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

int main(){
    
    struct Server servidor; //declaramos una variable en struct Server
    
    servidor.port = 8080;         //asignamos el puerto al servidor
    servidor.buffer_file = 4024;  //asignamos el tamaño de buffer de los archivos
    start_server_file(&servidor); //inicializamos el servidor

    while (WEB_TRUE){ //bucle principal para escuchar las solicitides entrantes
        //listen_server_file(&servidor,"index.html");//funcion para enviar una respuesta a la web
        listen_server_error_js(&servidor, "index.html"); //funcion para enviar una respuesta a la web con la opcion de ver posibles errores de javascript
        printf("%s",get_response());//funcion get_response() devuelve la respuesta o solicitud enviada por el navegador
    }
    return 0;
}
