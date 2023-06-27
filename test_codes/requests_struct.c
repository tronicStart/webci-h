#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

int main (){
    
    request request;
    ini_request(&request);
    request.open_("GET",NULL,"http://www.ejemplo.com");
    request.send_();
    request.responses = request.load_();
    printf("Data: %s\n",request.responses);
    request.close_();
    
    return 0;
}
