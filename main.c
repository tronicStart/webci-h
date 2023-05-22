#include "webci.h"
#include <sqlite3.h>

int main(){
    
    struct Server Servidor;
    
    Servidor.port = 8090;
    char * Code = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>Webci.h | iniciar sesion</title><style>body {background-color: blue;font-family: Arial, sans-serif;}.container {width: 300px;margin: 0 auto;margin-top: 100px;background-color: white;padding: 20px;border-radius: 5px;}h1 {text-align: center;}.form-group {margin-bottom: 20px;}.form-group label {display: block;margin-bottom: 5px;}.form-group input {width: 100%;padding: 10px;border: 1px solid lightgray;border-radius: 3px;}.form-group input[type=\"submit\"] {background-color: blue;color: white;cursor: pointer;}</style></head><body><div class=\"container\"><h1>Inicio de sesion</h1><form><div class=\"form-group\"><label for=\"username\">Usuario:</label><input type=\"text\" id=\"username\" name=\"username\" required></div><div class=\"form-group\"><label for=\"password\">Contraseña:</label><input type=\"password\" id=\"password\" name=\"password\" required></div><div class=\"form-group\"><input type=\"submit\" value=\"Iniciar sesión\"></div></form></div></body></html>";
    
    ini_server(&Servidor);
    config_server(&Servidor);
    while(WEB_TRUE){
        listen_server(&Servidor, Code);
    }
    
    return 0;
}
