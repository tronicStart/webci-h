//Archivo para probar la libreria webci.h y tambien como usarla
#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

struct Server servidor;//Se declara una struct global para poder usarla en todo el programa y poder enviar las paginas webs como respuestas
//funcion para poder trabajar con la base de datos sqlite3 y necesaria(obligatorio) crear para usar la funcion search_database()
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    
    char *main_page = "http://localhost:8090/index.html";
    char *nombre = "nombre";

    for (int i = 0; i < argc; i++){
        if (strcmp(azColName[i], nombre) == 0){
            if (strcmp(argv[i] ? argv[i] : "NULL", _post) == 0){
                listen_server_file(&servidor, "end.html");
                split_lines(get_response());
                if (search_words(get_response(), main_page) == WEB_OK){
                    listen_server_file(&servidor, "index.html");
                    return 0;
                }
            }
            else{
                listen_server_file(&servidor, "bad_address.html");
                split_lines(get_response());
                if (search_words(get_response(), main_page) == WEB_OK){
                    listen_server_file(&servidor, "index.html");
                    return 0;
                }
            }
        }
    }
}

int main(){
    
    //pagìnas para hacer poder enviar las los archivos html correpondientes
    char *page_2 = "http://localhost:8090/servicios.html";
    char *main_page = "http://localhost:8090/index.html";

    //otros
    int result;
    int result_get;
    
    //configuracion del servidor
    servidor.port = 8090;
    servidor.buffer_size = 4024; //No necesario
    start_server_file(&servidor);//funcion para iniciar el servidor
    //bucle principal para escuchar las solicitudes
    while (WEB_TRUE){
        listen_server_file(&servidor, "index.html");//funcion para enviar index.html como respuesta
        split_lines(get_response());//funcion para mostrar la respuesta. . .
        result_get = get_GET (get_response(), "img.png", 0, 7, &servidor);
        if (get_POST(get_response(), "user=", 5, 6) != WEB_ERROR){
            _post = get_POST(get_response(), "user=", 5, 6);
            search_database(1, "webci_test.db", "SELECT * FROM usuarios;", callback);
        }
        result = save_response(get_response());//funcion para guardar la respuestas enviadas en un archivo llamado: data_response.txt
        if (result == ERROR){
            listen_server_file(&servidor, "bad_address.html");
        }
        if (search_words(get_response(), page_2) == WEB_OK){
        while (search_words(get_response(), page_2) == WEB_OK){
                listen_server_file(&servidor, "servicios.html");
                split_lines(get_response());
                if (search_words(get_response(), main_page) == WEB_OK){
                    while (search_words(get_response(), main_page) == WEB_OK){
                        listen_server_file(&servidor, "index.html");
                        split_lines(get_response());
                    }
                }
            }
        }
    }
    return 0;
}
