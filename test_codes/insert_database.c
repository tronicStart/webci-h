//Codigo para insertar datos en una base de datos sqlite3 con datos enviados desde un formulario
#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

int main(){
    
    struct Server servidor; //declaramos una variable en struct Server
    
    servidor.port = 8080;         //asignamos el puerto al servidor
    servidor.buffer_file = 4024;  //asignamos el tamaño de buffer de los archivos
    start_server_file(&servidor); //inicializamos el servidor
    results res;//variable para poder capturar los posible errores enviados

    while (WEB_TRUE){ //bucle principal para escuchar las solicitides entrantes
        //listen_server_file(&servidor,"index.html");//funcion para enviar una respuesta a la web
        listen_server_error_js(&servidor, "index.html"); //funcion para enviar una respuesta a la web con la opcion de ver posibles errores de javascript
        if (get_POST(get_response(), "User=", 5, 6) != WEB_ERROR){
            _post = get_POST(get_response(), "User=", 5, 6);
            res = insert_database("inserts.db", 2, "CREATE TABLE IF NOT EXISTS usuarios (id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, pass TEXT);", "INSERT INTO usuarios (pass, nombre) VALUES ('%s', '%s')", _post, "7155");
            if (res == DATABASE_OK){
                send_response_inst(&servidor, "<h1>Se guardaron los datos</h1>");
            }
            else{
                send_response_inst(&servidor, "<h1>No se guardaron los datos, Error</h1>");
            }
        }
    }
    return 0;
}
