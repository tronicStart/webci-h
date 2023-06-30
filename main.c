//Archivo para probar la libreria webci.h y tambien como usarla
#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

int main(){
    
    struct Server servidor;
    
    servidor.port = 8090;
    servidor.buffer_file = 4024;
    open_server(&servidor);
    
    //variable para obtener el nombre del archivo
    String nameFile;
    
    while(WEB_TRUE){
        send_response_server(&servidor,"index.html");
        printf("%s",get_response());
        if(getFileName(get_response(),10) != WEB_ERROR){
            nameFile = getFileName(get_response(),10);
            printf("El nombre del archivo es: %s\n",nameFile);
        }
    }
    
    return 0;
}
