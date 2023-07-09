#include <webci.h>
#include <sqlite3.h>
#include <curl/curl.h>

int main(){
	
	html _html;
	struct Server test;
	
	test.port = 8090;
	test.buffer_file = 4024;
	open_server(&test);
	
    ini_html(&_html);
	_html.title("Pruebas html");
	_html.style(".colores h1{ color: red;} .colores p{color : blue;} #colors{ color: red;}");
	_html.div_o("class=\"colores\"");
	_html.center_o();
	_html.h1(NULL,"Este es un titulo");
	_html.p(NULL,"Este es un parrafo de ejemplo Bene?");
	_html.h2(NULL,"Sub titulo");
	_html.p(NULL,"Este es otro parrafo");
	_html.center_c();
	_html.div_c();
	_html.send(&test);
	printf("%s\n",true_html);
	return 0;
}
