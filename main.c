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
    
    //pagìnas
    char *page_2 = "http://localhost:8090/servicios.html";
    char *main_page = "http://localhost:8090/index.html";

    //otros
    int result;

    servidor.port = 8090;
    servidor.buffer_size = 4024; //No necesario
    start_server_file(&servidor);

    while (WEB_TRUE){
        listen_server_file(&servidor, "index.html");
        split_lines(get_response());
        if (get_POST_GET(get_response(), "user=", 5, 6) != WEB_ERROR){
            _post = get_POST_GET(get_response(), "user=", 5, 6);
            search_database(1, "webci_test.db", "SELECT * FROM usuarios;", callback);
        }
        result = save_response(get_response());
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
