//Archivo para probar la libreria webci.h y tambien como usarla
#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

int main(){
    
    struct Server servidor;
    struct files files;
    
    servidor.port = 8090;
    servidor.buffer_file = 4024;
    strcpy(servidor.cookie_file_name,"namefileuser.txt");
    open_server(&servidor);
    
    while(WEB_TRUE){
        send_response_server(&servidor,"index.html");
        printf("%s",get_response());
        //evitamos que el programa colapse por no haber datos al inicio o para que no interrumpa el flujo de ejecuciòn
        if(getFileName(&files,get_response(),10) != WEB_ERROR){
            //obtener el nombre del archivo
            getLengthNameFile(&files,get_response());
            getFileName(&files,get_response(),files.len_namefile);
            //obtener el peso del archivo
            getLengthStringFile(&files,get_response());
            getLengthFile(&files,get_response(),files.len_file);
            //obtener el tipo de archivo(la funciòn getTypeFile() tiene un error)
            getLengthTypeFile(&files,get_response());
            getTypeFile(&files,get_response(),files.len_typefile);
            printf("La longitud de len_namefile es: %d\n",files.len_namefile);
            printf("La longitud de len_file es: %d\n",files.len_file);
            printf("La longitud de len_typefile es: %d\n",files.len_typefile);
            printf("El nombre del archivo es: %s\n",files.name_file);
            printf("El peso del archivo es: %s\n",files.length_file);
            printf("Tipo de archivo es: %s\n",files.type_file);
        }
    }
    
    return 0;
}
