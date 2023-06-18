//Archivo para probar la libreria webci.h y tambien como usarla
#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

struct Server servidor;//Se declara una struct global para poder usarla en todo el programa y poder enviar las paginas webs como respuestas
//funcion para poder trabajar con la base de datos sqlite3 y necesaria(obligatorio) crear para usar la funcion search_database()
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    
    PAGE_URL main_page = "http://localhost:8090/index.html";
    String nombre = "nombre";

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
    PAGE_URL page_2 = "http://localhost:8090/servicios.html";
    PAGE_URL main_page = "http://localhost:8090/index.html";
    
    //otros
    results Results[5];
    WEB_FILES have_file = HAVE_FILE;
    String hora = "12:26:00";
    //struct date
    Date fechas;
    
    //configuracion del servidor
    servidor.port = 8090;
    servidor.buffer_size = 4024;
    start_server_file(&servidor);//funcion para iniciar el servidor
    //bucle principal para escuchar las solicitudes
    while (WEB_TRUE){
        listen_server_file(&servidor, "index.html");//funcion para enviar index.html como respuesta
        split_lines(get_response());//funcion para mostrar la respuesta. . .
        if (get_POST(get_response(), "username=", 9, 6) != WEB_ERROR){
            _post = get_POST(get_response(), "user=", 5, 6);
            search_database("webci_test.db","SELECT * FROM  usuarios;",1,callback);
        }
        Results[1] = save_response(get_response());//funcion para guardar la respuestas enviadas en un archivo llamado: data_response.txt
        if (Results[1] == ERROR){
            listen_server_file(&servidor, "bad_address.html");
        }
        get_time(&fechas);
        if(time_cmp(&fechas,hora) == WEB_TRUE){
            send_response_inst(&servidor,"<style>h1{color: blue};</style><h1>Ya es hora</h1>");
        }
        if(get_platform(get_response(),7) != WEB_ERROR){
            //funcion mejorada de send_response_inst() ahora puede recivir varios parametros para enviarlo junto con la respuesta html
            send_response_varic(&servidor,1,"<h1>Tu sistema operativo es: %s</h1><script>alert('Funciona!');</script>",get_platform(get_response(),7));
        }
        if (search_words(get_response(), page_2) == WEB_OK){
        while (search_words(get_response(), page_2) == WEB_OK){
                listen_server_file(&servidor, "servicios.html");
                split_lines(get_response());
                /*Fragmento (bloque if)de codigo para insertar datos de la pagina a la base de datos sqlite3
                estos datos que se envian del formulalio de una pagina y se guardan*/
                if(get_POST(get_response(),"User=",5,6) != WEB_ERROR){
                    _post = get_POST(get_response(),"User=",5,6);
                    Results[3] = insert_database ("webci_test.db",2,"CREATE TABLE IF NOT EXISTS usuarios (id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, pass TEXT);", "INSERT INTO usuarios (pass, nombre) VALUES ('%s', '%s')", _post, "7155");
                    if(Results[3] == OK){
                        send_response_inst(&servidor,"<h1>Se guardaron los datos</h1><button><a href=\"index.html\">Inicio</a></button>");
                    } else {
                        send_response_inst(&servidor,"<h1>No se guardaron los datos, Error</h1>");
                    }
                }
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
