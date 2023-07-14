//programa que usa la libreria webci.h
#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

PAGE_URL index_1 = "http://localhost:8080/";
PAGE_URL index_2 = "http://localhost:8080/index.html";
PAGE_URL registro = "http://localhost:8080/registro.html";
html page;

char estilos[][500] = {
    "body {",
       "background-color: #f2f2f2;",
       "font-family: Arial, sans-serif;",
    "}",
    ".container {",
       "max-width: 400px;",
      "margin: 0 auto;",
      "padding: 20px;",
      "background-color: #ffffff;",
      "border: 2px solid #ff0000;",
      "border-radius: 10px;",
    "}",
   ".form-group {",
      "margin-bottom: 20px;",
    "}",
    ".form-group label {",
      "display: block;",
      "margin-bottom: 5px;",
    "}",
    ".form-group input[type=\"text\"],",
    ".form-group input[type=\"password\"] {",
      "width: 100%;",
      "padding: 10px;",
      "border: 2px solid #00ff00;",
      "border-radius: 5px;",
    "}",
    ".form-group button {",
      "padding: 10px 20px;",
      "background-color: #0000ff;",
      "color: #ffffff;",
      "border: none;",
      "border-radius: 5px;",
      "cursor: pointer;",
    "}",
};

void index_page ();

int main(){
	
	struct Server test;//struct del servidor para poder ver la pagina
	test.port = 8080;
	test.buffer_file = 4024;
	int result_basedata;
	open_server(&test);
	index_page();
	while(WEB_TRUE){
	    page.send(&test,JS_ERRORS_OFF);
	    printf("%s",get_response());
	    if(post(get_response(),"username=",9,6) != WEB_ERROR){
	        _post = post(get_response(),"username=",9,6);
	        //result_basedata = create_database("test_html.db","CREATE TABLE usuarios(id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, pass TEXT)");
	        printf("_post = %s\n",_post);
	        result_basedata = insert_database("test_html.db", 2, "CREATE TABLE IF NOT EXISTS usuarios (id INTEGER PRIMARY KEY AUTOINCREMENT, usename TEXT, pass TEXT);", "INSERT INTO usuarios (username, pass) VALUES ('%s', '%s')", "soy una variable generica", _post);
	        if(result_basedata == DATABASE_ERROR){
	             return -1;
	             //page.script(NULL,"alert('Error al insertar los datos a la base de datos');");
	        }
	    }
	}
	return 0;
}

void index_page (){
    
    int numEstilos = sizeof(estilos) / sizeof(estilos[0]);
    char estilosCSS[HTML_LONG] = "";
	
	for (int i = 0; i < numEstilos; i++) {
       strcat(estilosCSS, estilos[i]);
       strcat(estilosCSS, "\n");
    }
    ini_html(&page);
    page.title("Login | home");
    page.html_o("lang=\"es\"");
    page.head_o(NULL);
    page.meta("charset=\"UTF-8\"");
    page.meta("http-equiv=\"X-UA-Compatible\" content=\"IE=Edge\"");
    page.style(estilosCSS);//pendiente
    page.head_c();
    page.body_o(NULL);
    page.div_o("class=\"container\"","");
    page.h2(NULL,"Iniciar sesión");
    page.form_o(NULL);
    page.div_o("class=\"form-group\"","");
    page.h2("for=\"username\"","Nombre de usuario");
    page.input("type=\"text\" id=\"username\" name=\"username\" placeholder=\"Ingresa tu nombre de usuario\"");
    page.div_c();
    page.div_o("class=\"form-group\"","");
    page.h2("for=\"password\"","Contraceña");
    page.input("type=\"password\" id=\"password\" name=\"password\" placeholder=\"Ingresa tu contrsceña\"");
    page.div_c();
    page.button("type=\"submit\"","Iniciar sesión");
    page.form_c();
    page.div_c();
    page.body_c();
    page.html_c();
    
}
