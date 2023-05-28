#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

int main(){
    
    struct Server servidor;
    
    char *page_2 = "http://localhost:8090/servicios.html";
    char *main_page = "http://localhost:8090/index.html";
    
    servidor.port = 8090;
    servidor.buffer_size = 4024;//No necesario
    start_server_file(&servidor);
    
    while(WEB_TRUE){
        listen_server_file(&servidor,"index.html");
        split_lines(get_response());
        if(search_words(get_response(), page_2) == WEB_OK){
            while(WEB_TRUE){
                listen_server_file(&servidor,"servicios.html");
                split_lines(get_response());
                if(search_words(get_response(),main_page) == WEB_OK){
                    listen_server_file(&servidor,"index.html");
                }
            }
        }
    }
    return 0;
}
