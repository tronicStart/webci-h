#ifndef WEBCI_H
#define WEBCI_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <curl/curl.h>
#include "webci_def.h"

typedef signed char results;
typedef char *PAGE_URL;
typedef char *WEB_FILES;
typedef char *String;
typedef int array;

struct Server{
    int server_fd, new_socket, valread, client_socket;
    struct sockaddr_in address, client_address;
    socklen_t client_address_length;
    int opt;
    int addrlen;
    int error;
    int port;
    int buffer_file;
    int buffer_img;
    char cookie_time[30];
    char cookie_file_name[V];
    int cookie_active;
};

typedef struct{
    char smtp_url[V];
    char user_smtp[V];
    char password_smtp[V];
    char mail_from[V];
    char recipient[V];
    char payload_text[SMTP_TEXT];
} smtp_email;

typedef struct{
    char current_date[20];
    char hour[9];
} Date;

typedef struct{
    struct{
        array range;
        array Array[100];
    } Int;
    struct{
        array range;
        String Array[100];
    } string;
    struct{
        array range;
        results Array[100];
    } Result;
    struct{
        array range;
        PAGE_URL Array[100];
    } Pages_url;
    struct{
        array range;
        WEB_FILES Array[100];
    } Web_files;
    array i;
} Array;

typedef struct {
    int (*open_)(const String , const String, const String);
    String (*load_)();
    void (*close_)();
    int (*send_)();
    int status;
    String data;
}request;

struct files {
    String name_file;
    String type_file;
    String length_file;
    int status_file;
    int len_namefile;
    int len_file;
    int len_typefile;
};

typedef struct {
    void (*title)(const String);
    void (*center_o)();
    void (*center_c)();
    void (*h1)(const String, const String);
    void (*h2)(const String, const String);
    void (*h3)(const String, const String);
    void (*h4)(const String, const String);
    void (*h5)(const String, const String);
    void (*h6)(const String, const String);
    void (*button)(const String, const String);
    void (*script)(const String const String);
    //nuevos
    void (*div)(const String);
    void (*div_o)(const String);
    void (*div_c)();
    void (*body_o)();
    void (*body_c)();
    void (*body)();
    void (*head_o)();
    void (*head_c)();
    void (*head)();
    void (*img)();
    String src;
    String alt;
    void (*a)();
    String href;
    void (*section_o)();
    void (*section_c)();
    void (*section)();
    void (*article_o)();
    void (*arcticle_c)();
    void (*arcticle)();
    void (*header_o)();
    void (*header_c)();
    void (*header)();
    void (*style)(const String);
    void (*footer)();
    void (*footer_o)();
    void (*footer_c)();
    void (*video)();
    String source;
    void (*form)();
    void (*form_o)();
    void (*form_c)();
    String method;
    String action;
    String enctype;
    void (*input)();
    String type;
    String name;
    void (*meta)();
    String charset;
    void (*link)();
    void (*aside)();
    void (*hr)();
    void (*br)();
    void (*pre)();
    void (*center)();
    void (*textarea)();
    void (*blockquote)();
    void (*ol)();
    void (*ol_o)();
    void (*ol_c)();
    void (*ul)();
    void (*ul_o)();
    void (*ul_c)();
    void (*li)();
    void (*li_o)();
    void (*li_c)();
    void (*dl)();
    void (*dl_o)();
    void (*dl_c)();
    void (*dt)();
    void (*dt_o)();
    void (*dt_c)();
    void (*dd)();
    void (*dd_o)();
    void (*dd_c)();
    void (*figure)();
    void (*figure_o)();
    void (*figure_c)();
    String span;
    void (*small)();
    void (*cite)();
    void (*sub)();
    void (*sup)();
    void (*mark)();
    void (*iframe)();
    void (*embed)();
    void (*audio)();
    void (*table)();
    void (*table_o)();
    void (*table_c)();
    void (*tbody)();
    void (*tbody_o)();
    void (*tbody_c)();
    void (*thead)();
    void (*thead_o)();
    void (*thead_c)();
    void (*tfoot)();
    void (*tfoot_o)();
    void (*tfoot_c)();
    void (*tr)();
    void (*td)();
    void (*th)();
    void (*label)();
    void (*select)();
    void (*select_o)();
    void (*select_c)();
    void (*option)();
    void (*option_o)();
    void (*option_c)();
    void (*caption)();
    void (*p)(const String, const String);
    int (*send)(struct Server *);
}html;

char buffer[BUFFER_SIZE] = {0};
char buffer_2[BUFFER_SIZE][BUFFER_SIZE];
char *_post;
char *_get;
char cookie_value[30];
String ob;
String _get;
String _post;
int result_;
String resq;
PAGE_URL pages_request;
String post_params_request;
static char true_html[BUFFER_SIZE] = " ";
static char result_html[BUFFER_SIZE] = "<html>";
static char _hh[BUFFER_SIZE];
static char total_2[BUFFER_SIZE];
static char total_html[BUFFER_SIZE];

void cat_str(const String texto1, const String texto2, String resultado){
    strcpy(resultado, texto1);
    strcat(resultado, texto2);
}

static void _title (const String title){
    char temp[HTML_LONG];
    cat_str("<title>",title, temp);
    cat_str(temp,"</title>",result_html);
    cat_str(result_html,"",true_html);
}

static void _center_open (){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    cat_str("<center>","",temp);
    cat_str(temp,"",temp_2);
    cat_str(true_html,"",temp_3);
    cat_str(temp_2,"",result_html);
    cat_str(temp_3,result_html,true_html);
}

static void _center_close (){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    cat_str("","",temp);
    cat_str(temp,"</center>",temp_2);
    cat_str(true_html,"",temp_3);
    cat_str(temp_2,"",result_html);
    cat_str(temp_3,result_html,true_html);
}
/*Etiquetas del body*/
static void _h1 (const String attributes, const String h1){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<h1>",h1,temp);
        cat_str(temp,"</h1>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<h1 ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,h1,temp_5);
        cat_str(temp_5,"</h1>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _h2 (const String attributes, const String h2){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<h2>",h2,temp);
        cat_str(temp,"</h2>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<h2 ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,h2,temp_5);
        cat_str(temp_5,"</h2>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _h3 (const String attributes, const String h3){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<h3>",h3,temp);
        cat_str(temp,"</h3>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<h3 ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,h3,temp_5);
        cat_str(temp_5,"</h3>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _h4 (const String attributes, const String h4){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<h4>",h4,temp);
        cat_str(temp,"</h4>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<h4 ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,h4,temp_5);
        cat_str(temp_5,"</h4>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _h5 (const String attributes, const String h5){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<h5>",h5,temp);
        cat_str(temp,"</h5>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<h5 ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,h5,temp_5);
        cat_str(temp_5,"</h5>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _h6 (const String attributes, const String h6){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<h6>",h6,temp);
        cat_str(temp,"</h6>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<h6 ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,h6,temp_5);
        cat_str(temp_5,"</h6>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _p (const String attributes, const String p){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<p>",p,temp);
        cat_str(temp,"</p>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<p ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,p,temp_5);
        cat_str(temp_5,"</p>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _button (const String attributes, const String button){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<button>",button,temp);
        cat_str(temp,"</button>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<button ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,button,temp_5);
        cat_str(temp_5,"</button>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _script (const String attributes, const String script){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<script>",script,temp);
        cat_str(temp,"</script>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<script ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,script,temp_5);
        cat_str(temp_5,"</script>",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

/*Nuevas etiquetas html*/
static void _style (const String style){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    cat_str("<style>",style,temp);
    cat_str(temp,"</style>",temp_2);
    cat_str(true_html,"",temp_3);
    cat_str(temp_2,"",result_html);
    cat_str(temp_3,result_html,true_html);
}

static void _div (const String div){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    cat_str("<div>",div,temp);
    cat_str(temp,"</div>",temp_2);
    cat_str(true_html,"",temp_3);
    cat_str(temp_2,"",result_html);
    cat_str(temp_3,result_html,true_html);
}

static void _div_o (const String attributes){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    char temp_4[HTML_LONG];
    char temp_5[HTML_LONG];
    if(attributes == NULL){
        cat_str("<div>","",temp);
        cat_str(temp,"",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    } else {
        cat_str("<div ",attributes,temp_4);
        cat_str(temp_4,">",temp);
        cat_str(temp,"",temp_2);
        cat_str(true_html,"",temp_3);
        cat_str(temp_2,"",result_html);
        cat_str(temp_3,result_html,true_html);
    }
}

static void _div_c (){
    char temp[HTML_LONG];
    char temp_2[HTML_LONG];
    char temp_3[HTML_LONG];
    cat_str("","",temp);
    cat_str(temp,"</div>",temp_2);
    cat_str(true_html,"",temp_3);
    cat_str(temp_2,"",result_html);
    cat_str(temp_3,result_html,true_html);
}

static void _body_o (){
    
}
static void _body_c (){
    
}

static void _body (){
    
}

static void _head_o (){
    
}

static void _head_c (){
    
}

static void _head (){
    
}

static void _img (){
    
}

static void _a (){
    
}

static void _section_o (){
    
}

static void _section_c (){
    
}

static void _section (){
    
}

static void _article_o (){
    
}

static void _arcticle_c (){
    
}

static void _arcticle (){
    
}

static void _header_o (){
    
}

static void _header_c (){
    
}

static void _header (){
    
}

static void _footer (){
    
}

static void _footer_o (){
    
}

static void _footer_c (){
    
}

static void _video (){
    
}

static void _form (){
    
}

static void _form_o (){
    
}

static void _form_c (){
    
}

static void _input (){
    
}

static void _meta (){
    
}

static void _link (){
    
}

static void _aside (){
    
}

static void  _hr (){
    
}

static void _br (){
    
}

static void _pre (){
    
}

static void _center (){
    
}

static void _textarea (){
    
}

static void _blockquote (){
    
}

static void _ol (){
    
}

static void _ol_o (){
    
}

static void _ol_c (){
    
}

static void _ul (){
    
}

static void _ul_o (){
    
}

static void _ul_c (){
    
}

static void _li (){
    
}

static void _li_o (){
    
}

static void _li_c (){
    
}

static void _dl (){
    
}

static void _dl_o (){
    
}

static void _dl_c (){
    
}

static void _dt (){
    
}

static void _dt_o (){
    
}

static void _dt_c (){
    
}

static void _dd (){
    
}

static void _dd_o (){
    
}

static void _dd_c (){
    
}

static void _figure (){
    
}

static void _figure_o (){
    
}

static void _figure_c (){
    
}

static void _small (){
    
}

static void _cite (){
    
}

static void _sub (){
    
}

static void _sup (){
    
}

static void _mark (){
    
}

static void _iframe (){
    
}

static void _embed (){
    
}

static void _audio (){
    
}

static void _table (){
    
}

static void _table_o (){
    
}

static void _table_c (){
    
}

static void _tbody (){
    
}

static void _tbody_o (){
    
}

static void _tbody_c (){
    
}

static void _thead (){
    
}

static void _thead_o (){
    
}

static void _thead_c (){
    
}

static void _tfoot (){
    
}

static void _tfoot_o (){
    
}

static void _tfoot_c (){
    
}

static void _tr (){
    
}

static void _td (){
    
}

static void _th (){
    
}

static void _label (){
    
}

static void _select (){
    
}

static void _select_o (){
    
}

static void _select_c (){
    
}

static void _option (){
    
}

static void _option_o (){
    
}

static void _option_c (){
    
}

static void _caption (){
    
}

static int _send_html (struct Server * server){
    if (listen(server->server_fd, 3) < 0){
        return HTML_ERROR;
    }
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        return HTML_ERROR;
    }
    char *response_2[BUFFER_SIZE];
    server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
    cat_str("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", true_html, response_2);
    write(server->new_socket, response_2, strlen(response_2));
    close(server->new_socket);
    return HTML_OK;
}

void ini_html (html * html){
    html->title = _title;
    html->h1 = _h1;
    html->h2 = _h2;
    html->h3 = _h3;
    html->h4 = _h4;
    html->h5 = _h5;
    html->h6 = _h6;
    html->p = _p;
    html->button = _button;
    html->script = _script;
    html->center_o = _center_open;
    html->center_c = _center_close;
    html->send = _send_html;
    html->div = _div;
    html->div_o = _div_o;
    html->div_c = _div_c;
    html->style = _style;
    /*html->body_o;
    html->body_c;
    html->body;
    html->head_o;
    html->head_c;
    html->head;
    html->img;
    html->a;
    html->section_o;
    html->section_c;
    html->section;
    html->article_o;
    html->arcticle_c;
    html->arcticle;
    html->header_o;
    html->header_c;
    html->header;
    html->footer;
    html->footer_o;
    html->footer_c;
    html->video;
    html->form;
    html->form_o;
    html->form_c;
    html->input;
    html->meta;
    html->link;
    html->aside;
    html->hr;
    html->br;
    html->pre;
    html->center;
    html->textarea;
    html->blockquote;
    html->ol;
    html->ol_o;
    html->ol_c;
    html->ul;
    html->ul_o;
    html->ul_c;
    html->li;
    html->li_o;
    html->li_c;
    html->dl;
    html->dl_o;
    html->dl_c;
    html->dt;
    html->dt_o;
    html->dt_c;
    html->dd;
    html->dd_o;
    html->dd_c;
    html->figure;
    html->figure_o;
    html->figure_c;
    html->small;
    html->cite;
    html->sub;
    html->sup;
    html->mark;
    html->iframe;
    html->embed;
    html->audio;
    html->table;
    html->table_o;
    html->table_c;
    html->tbody;
    html->tbody_o;
    html->tbody_c;
    html->thead;
    html->thead_o;
    html->thead_c;
    html->tfoot;
    html->tfoot_o;
    html->tfoot_c;
    html->tr;
    html->td;
    html->th;
    html->label;
    html->select;
    html->select_o;
    html->select_c;
    html->option;
    html->option_o;
    html->option_c;
    html->caption;*/
}

void server_file_response(int client_socket, const char *content_type, const char *content){
    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %lu\n\n%s", content_type, strlen(content), content);
    write(client_socket, response, strlen(response));
}

void where(unsigned const char *condition, void (*func_1)(), void (*func_2)()){
    if (condition){
        func_1;
    }
    else{
        func_2;
    }
}

int create_file(const String name, const String data, const String read){
    FILE * fp = fopen(name,read);
    if(fp == NULL){
        return ERROR;
    } 
    fprintf(fp,"%s",data);
    fclose(fp);
    return OK;
}

void split_lines(const char *text){
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        printf("%s\n", line);
        line = strtok(NULL, "\n");
    }
    free(text_copy);
}

int search_words(const char *text, const char *word){
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        if (strstr(line, word) != NULL){
            return WEB_OK;
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

Array * create_array_int(Array *Array, ...){
    array *Arra = malloc(Array->Int.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->Int.range);
    for (Array->i = 0; Array->i < Array->Int.range; Array->i++){
        array x = va_arg(valist, array);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->Int.range; Array->i++){
        Array->Int.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

Array * create_array_results(Array *Array, ...){
    array *Arra = malloc(Array->Result.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->Int.range);
    for (Array->i = 0; Array->i < Array->Result.range; Array->i++){
        results x = va_arg(valist, results);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->Result.range; Array->i++){
        Array->Result.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

Array * create_array_WEBFILES(Array *Array, ...){
    array *Arra = malloc(Array->Web_files.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->Web_files.range);
    for (Array->i = 0; Array->i < Array->Web_files.range; Array->i++){
        WEB_FILES x = va_arg(valist, WEB_FILES);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->Int.range; Array->i++){
        Array->Web_files.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

Array * create_array_page_url(Array *Array, ...){
    array *Arra = malloc(Array->Pages_url.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->Pages_url.range);
    for (Array->i = 0; Array->i < Array->Pages_url.range; Array->i++){
        PAGE_URL x = va_arg(valist, PAGE_URL);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->Pages_url.range; Array->i++){
        Array->Pages_url.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

Array * create_array_String(Array *Array, ...){
    array *Arra = malloc(Array->string.range * sizeof(array));
    va_list valist;
    va_start(valist, Array->string.range);
    for (Array->i = 0; Array->i < Array->string.range; Array->i++){
        String x = va_arg(valist, String);
        Arra[Array->i] = x;
    }
    va_end(valist);
    for (Array->i = 0; Array->i < Array->string.range; Array->i++){
        Array->Int.Array[Array->i] = Arra[Array->i];
    }
    free(Arra);
    return Array;
}

size_t write_callback(void *buffer, size_t size, size_t nmemb, void *userp) {
    String data = (String)buffer;
    ob = data;
    return size * nmemb;
}

int open_ (const String solicitud, const String params_post, const String page_url){
    _get ="GET";
    _post = "POST";
    if(strcmp(solicitud,_get) == 0){
        result_ = INI_REQUEST;
        resq = "GET";
        pages_request = page_url;
        return INI_REQUEST;
    } else if(strcmp(solicitud,_post) == 0){
        result_ = INI_REQUEST;
        resq = "POST";
        pages_request = page_url;
        if(params_post == NULL){
            return NO_INI_REQUEST;
        }
        post_params_request = params_post;
        return INI_REQUEST;
    }
    return NO_INI_REQUEST;
}

String load_(){
    return ob;
}

void close_ (){
    _get = "GET";
    _post = "POST";
    pages_request = '\0';
    post_params_request = '\0';
    resq = '\0';
    result_ = '\0';
    ob = '\0';
}

int send_ (){
    if(result_ == INI_REQUEST){
        if(strcmp(resq,_get) == 0){
            CURL *curl;
            CURLcode res;
            curl_global_init(CURL_GLOBAL_DEFAULT);
            curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, pages_request);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
                res = curl_easy_perform(curl);
                if (res != CURLE_OK) {
                    return STATUS_ERROR;
                }
                curl_easy_cleanup(curl);
            }
            curl_global_cleanup();
            return STATUS_OK;
        } else if(resq,_post){
            CURL *curl;
            CURLcode res;
            curl_global_init(CURL_GLOBAL_DEFAULT);
            curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, pages_request);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_params_request);
                res = curl_easy_perform(curl);
                if (res != CURLE_OK) {
                    return STATUS_ERROR;
                }
                curl_easy_cleanup(curl);
            }
            curl_global_cleanup();
            return STATUS_OK;
        } else {
            return STATUS_ERROR;
        }
    }
    return STATUS_ERROR;
}

void prepare_request (request * request){
    request->open_ = open_;
    request->load_ = load_;
    request->close_ = close_;
    request->send_ = send_;
    ob = "NULL";
}

void get_date(Date *date){
    time_t tiempo;
    struct tm *tm_info;
    time(&tiempo);
    tm_info = localtime(&tiempo);
    strftime(date->current_date, 20, "%Y-%m-%d", tm_info);
}

void get_time(Date *date){
    time_t tiempo;
    struct tm *tm_info;
    time(&tiempo);
    tm_info = localtime(&tiempo);
    strftime(date->hour, 9, "%H:%M:%S", tm_info);
}

int time_cmp(Date *date, const String other_hour){
    if (strcmp(date->hour, other_hour)){
        return WEB_TRUE;
    }
    return WEB_FALSE;
}

int date_cmp(Date *date, const String other_date){
    if (strcmp(date->current_date, other_date)){
        return WEB_TRUE;
    }
    return WEB_FALSE;
}

int date_cmp_func(Date *date, const String other_date, void (*func)()){
    if (strcmp(date->current_date, other_date)){
        func;
    }
    return WEB_FALSE;
}

int time_cmp_func(Date *date, const String other_hour, void (*func)()){
    if (strcmp(date->hour, other_hour)){
        func;
    }
    return WEB_FALSE;
}

int create_database(const String name, const String create_table_query){
    sqlite3 *db;
    char *error_message = 0;
    int result = sqlite3_open(name, &db);
    if (result != SQLITE_OK){
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return DATABASE_ERROR;
    }
    result = sqlite3_exec(db, create_table_query, 0, 0, &error_message);
    if (result != SQLITE_OK){
        printf("%s\n", error_message);
        sqlite3_free(error_message);
        sqlite3_close(db);
        return DATABASE_ERROR;
    }
    sqlite3_close(db);
    return DATABASE_OK;
}

int insert_database(const String name_base, int total_data, const String sql, String insert, ...){
    sqlite3 *db;
    char *err_msg = 0;
    int rc, i;
    String chonps;
    rc = sqlite3_open(name_base, &db);
    if (rc != SQLITE_OK){
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return DATABASE_ERROR;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK){
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DATABASE_ERROR;
    }
    char insert_query[100];
    va_list args;
    va_start(args, insert);
    for (i = 0; i < total_data + 1 - 1; i++){
        String count = va_arg(args, String);
        sprintf(insert_query, insert, count, chonps);
    }
    va_end(args);
    rc = sqlite3_exec(db, insert_query, 0, 0, &err_msg);
    if (rc != SQLITE_OK){
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DATABASE_ERROR;
    }
    sqlite3_close(db);
    return DATABASE_OK;
}

int search_database(const String name, const String query, int start, int (*callback)()){
    if (start != 0){
        sqlite3 *db;
        char *error_msg = 0;
        int rc = sqlite3_open(name, &db);
        if (rc != SQLITE_OK){
            fprintf(stderr, "%s\n", sqlite3_errmsg(db));
            return DATABASE_ERROR;
        }
        rc = sqlite3_exec(db, query, callback, 0, &error_msg);
        if (rc != SQLITE_OK){
            fprintf(stderr, "%s\n", error_msg);
            sqlite3_free(error_msg);
            sqlite3_close(db);
            return DATABASE_ERROR;
        }
        sqlite3_close(db);
    }
}

int update_database (const String name, const String sql, int total_data, ...){
    sqlite3 *db;
    char *err_msg = 0;
    String new_sql;
    int i;
    int rc = sqlite3_open(name, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return DATABASE_ERROR;
    }
    va_list args;
    va_start(args, sql);
    for (i = 0; i < total_data; i++){
        String count = va_arg(args, String);
        sprintf(new_sql, sql, count);
    }
    va_end(args);
    rc = sqlite3_exec(db, new_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "%s\n", err_msg);
        sqlite3_free(err_msg);
        return DATABASE_ERROR;
    }
    sqlite3_close(db);
    return DATABASE_OK;
}

int delete_database (const String name, const String sql){
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open(name, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        return DATABASE_ERROR;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "%s\n", err_msg);
        sqlite3_free(err_msg);
        return DATABASE_ERROR;
    }
    sqlite3_close(db);
    return DATABASE_OK;
}

int create_cookie(struct Server *server, const char *request, const char *data_cookie){
    recv(server->valread, request, BUFFER_SIZE, 0);
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char response[BUFFER_SIZE];
    FILE *fp = fopen(server->cookie_file_name, "w");
    if (fp == NULL){
        perror("  ");
        return WEB_ERROR;
    }
    else{
        fprintf(fp, "%s", data_cookie);
    }
    close(server->valread);
    fclose(fp);
    server->cookie_active = IS_ACTIVE;
    return IS_ACTIVE;
}

int remove_cookie(struct Server *server){
    if (remove(server->cookie_file_name) == ERROR){
        perror("  ");
        return WEB_ERROR;
    }
    server->cookie_active = IS_NO_ACTIVE;
    return IS_NO_ACTIVE;
}

String read_cookie(struct Server *servidor, const char *request){
    recv(servidor->valread, request, BUFFER_SIZE, 0);
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(servidor->cookie_time, sizeof(servidor->cookie_time), "%Y-%m-%d %H:%M:%S", tm_info);
    char response[BUFFER_SIZE];
    char data[BUFFER_SIZE];
    FILE *cookie = fopen(servidor->cookie_file_name, "r");
    if (cookie == NULL){
        perror("  ");
        return WEB_ERROR;
    }
    else{
        while (feof(cookie) == 0){
            fgets(data, BUFFER_SIZE, cookie);
            snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", data);
        }
    }
    close(servidor->valread);
    fclose(cookie);
    return response;
}

String post (const String text, const String word, int ini){
    String text_copy = strdup(text);
    String line = strtok(text_copy, "\n");
    int end_index = 100;
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index <= strlen(line)){
                String result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                return result;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

/*int get_GET_IMG (struct Server * server, const String text, const String word, int end_index){
    
    char img_content[server->buffer_img];
    size_t img_size;
    int ini = 5;
    
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                FILE * fp = fopen(word,"rb");
                if(fp == NULL){
                    return WEB_FILE_ERROR;
                } else{
                    //img_size = fread(img_content, sizeof(char), server->buffer_img, fp);
                    server_file_response(server->valread, "text/html", word);
                    fclose(fp);
                    close(server->new_socket);
                    printf("Img content: %s\n", word);
                    return WEB_OK;
                }
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}*/

char * get(const char *text, const char *word, int ini, int end_index, struct Server *server){
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    char response[BUFFER_SIZE];
    size_t bytesRead;
    FILE *fp;
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                fp = fopen(result, "r");
                if (fp == NULL){
                    return WEB_ERROR;
                }
                while ((bytesRead = fread(response, 1, sizeof(response), fp)) > 0){
                    send(server->client_socket, response, bytesRead, 0);
                }
                fclose(fp);
                close(server->client_socket);
                return WEB_OK;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

String getPlatform (const String text){
    String word = "sec-ch-ua-platform: ";
    int ini = 20;
    int end_index = 10;
    String text_copy = strdup(text);
    String line = strtok(text_copy, "\n");
    while (line != NULL){
        String word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index <= strlen(line)){
                String result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                return result;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

int send_email(smtp_email *email){
    CURL *curl;
    CURLcode res = CURLE_OK;
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, email->smtp_url);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, email->mail_from);
        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, email->recipient);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_USERNAME, email->user_smtp);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, email->password_smtp);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, email->payload_text);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "%s\n", curl_easy_strerror(res));
            
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
    return (int)res;
}

int getLengthNameFile (struct files * f, const String text){
    char *word = "filename=\"";
    int ini = 9;
    int end_index = 50;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                f->len_namefile = strlen(result);
                return WEB_OK;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

char *getFileName(struct files * f, const char *text, int end_index){
    char *word = "filename=\"";
    int ini = 9;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                f->len_namefile = strlen(result);
                if(f->len_namefile > end_index){
                    f->status_file = ERROR_LENGTH_STRINGS_UP;
                    return ERROR_LENGTH_STRINGS_UP;
                } else if(f->len_namefile < end_index){
                    f->status_file = ERROR_LENGTH_STRINGS_DOWN;
                    return ERROR_LENGTH_STRINGS_DOWN;
                }
                f->name_file = result;
                return WEB_OK;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

int getLengthTypeFile (struct files * f, const String text){
    char *word = "Content-Type: ";
    int ini = 15;
    int end_index = 10;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                f->len_typefile = strlen(result);
                return WEB_OK;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

char *getTypeFile(struct files * f, const char *text, int end_index){
    char *word = "Content-Type:";
    int ini = 13;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                f->len_typefile = strlen(result);
                if(f->len_typefile > end_index){
                    f->status_file = ERROR_LENGTH_STRINGS_UP;
                    return ERROR_LENGTH_STRINGS_UP;
                } else if(f->len_typefile < end_index){
                    f->status_file = ERROR_LENGTH_STRINGS_DOWN;
                    return ERROR_LENGTH_STRINGS_DOWN;
                }
                f->type_file = result;
                return WEB_OK;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

int getLengthStringFile (struct files * f, const String text){
    char *word = "Content-Length: ";
    int ini = 15;
    int end_index = 10;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                f->len_file = strlen(result);
                return WEB_OK;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

char *getLengthFile(struct files * f, const char *text, int end_index){
    char *word = "Content-Length: ";
    int ini = 15;
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    while (line != NULL){
        char *word_position = strstr(line, word);
        if (word_position != NULL){
            size_t start_index = word_position + ini - line;
            if (start_index + end_index <= strlen(line)){
                char *result = malloc(end_index + 1);
                strncpy(result, line + start_index, end_index);
                result[end_index] = '\0';
                free(text_copy);
                f->len_file = strlen(result);
                if(f->len_file > end_index){
                    f->status_file = ERROR_LENGTH_STRINGS_UP;
                    return ERROR_LENGTH_STRINGS_UP;
                } else if(f->len_file < end_index){
                    f->status_file = ERROR_LENGTH_STRINGS_DOWN;
                    return ERROR_LENGTH_STRINGS_DOWN;
                }
                f->length_file = result;
                return WEB_OK;
            }
        }
        line = strtok(NULL, "\n");
    }
    free(text_copy);
    return WEB_ERROR;
}

/*int save_file (struct files * f){
    
}*/

int save_response(const char *data){
    FILE *fp = fopen("data_response.txt", "a");
    if (fp == NULL){
        return WEB_ERROR;
    }
    fprintf(fp, "%s", data);
    fclose(fp);
    return WEB_OK;
}

char *get_response(){
    return buffer;
}

int send_simple_response(struct Server *server, const char *response){
    if (listen(server->server_fd, 3) < 0){
        perror("");
        return WEB_ERROR;
    }
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        perror("");
        return WEB_ERROR;
    }
    char *response_2[BUFFER_SIZE];
    server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
    cat_str("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", response, response_2);
    write(server->new_socket, response_2, strlen(response_2));
    close(server->new_socket);
}

int send_args_response(struct Server *server, int total,const char *response, ...){
    int i;
    if (listen(server->server_fd, 3) < 0){
        perror("  ");
        return WEB_ERROR;
    }
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        perror("  ");
        return WEB_ERROR;
    }
    char *response_2[BUFFER_SIZE], response_total[BUFFER_SIZE];
    if(total < 1){
        server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
        cat_str("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", response, response_2);
        server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
        write(server->new_socket, response_2, strlen(response_2));
         close(server->new_socket);
         return OK;
    } else {
        va_list args;
        va_start(args, response);
        for (i = 0; i < total + 1 - 1; i++){
             String count = va_arg(args, String);
             sprintf(response_2, response, count);
        }
        va_end(args);
        cat_str("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n",response_2,response_total);
        server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
        write(server->new_socket, response_total, strlen(response_total));
        close(server->new_socket);
    }
}

int send_response_server_view_js(struct Server *server, const char *archivo){
    char response_2[BUFFER_SIZE];
    const String js = "<script>window.onerror = function(message, source, lineno, colno, error) {let errorDiv = document.getElementById('error-log');if (errorDiv) {errorDiv.innerHTML += '<strong>Error:</strong> ' + message + '<br>';}};</script><div id=\"error-log\"></div>";
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        perror("  ");
        return ERROR;
    }
    server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
    FILE *file = fopen(archivo, "r");
    if (file == NULL){
        perror("  ");
        return ERROR;
    }
    char html_content[server->buffer_file];
    size_t html_size = fread(html_content, sizeof(char), server->buffer_file, file);
    cat_str(js,html_content,response_2);
    fclose(file);
    server_file_response(server->new_socket, "text/html", response_2);
    close(server->new_socket);
}

int send_response_server_varic(struct Server *server, const char *archivo, int total, ...){
    int i;
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        perror("  ");
        return ERROR;
    }
    server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
    FILE *file = fopen(archivo, "r");
    if (file == NULL){
        perror("  ");
        return ERROR;
    }
    char html_content[server->buffer_file];
    size_t html_size = fread(html_content, sizeof(char), server->buffer_file, file);
    fclose(file);
    va_list args;
    va_start(args, html_content);
    char response_2[BUFFER_SIZE];
    for (i = 0; i < total; i++){
          String count = va_arg(args, String);
          sprintf(response_2, html_content, count);
     }
    va_end(args);
    server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
    server_file_response(server->new_socket, "text/html", response_2);
    close(server->new_socket);
}

int open_server(struct Server *server){
    server->opt = 1;
    server->addrlen = sizeof(server->address);
    if ((server->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("  ");
        return ERROR;
    }
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &server->opt, sizeof(server->opt))){
        perror("  ");
        return ERROR;
    }
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    if (bind(server->server_fd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0){
        perror("  ");
        return ERROR;
    }
    if (listen(server->server_fd, 3) < 0){
        perror("  ");
        return ERROR;
    }
}

int send_response_server (struct Server *server, const char *archivo){
    if ((server->new_socket = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen)) < 0){
        perror("  ");
        return ERROR;
    }
    server->valread = read(server->new_socket, buffer, BUFFER_SIZE);
    FILE *file = fopen(archivo, "r");
    if (file == NULL){
        perror("  ");
        return ERROR;
    }
    char html_content[server->buffer_file];
    size_t html_size = fread(html_content, sizeof(char), server->buffer_file, file);
    fclose(file);
    server_file_response(server->new_socket, "text/html", html_content);
    close(server->new_socket);
}

void ini_simple_server(struct Server *S){
    S->opt = 1;
    S->addrlen = sizeof(S->address);
    S->error = OK;
}

int config_simple_server(struct Server *S){
    S->error = ERROR;
    if ((S->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("  ");
        return S->error;
    }
    if (setsockopt(S->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &S->opt, sizeof(S->opt))){
        perror("  ");
        return S->error;
    }
    S->address.sin_family = AF_INET;
    S->address.sin_addr.s_addr = INADDR_ANY;
    S->address.sin_port = htons(S->port);
    if (bind(S->server_fd, (struct sockaddr *)&S->address, sizeof(S->address)) < 0){
        perror("  ");
        return S->error;
    }
}

int send_response_simple_server(struct Server *S, const char *response){
    if (listen(S->server_fd, 3) < 0){
        perror("  ");
        return S->error;
    }
    if ((S->new_socket = accept(S->server_fd, (struct sockaddr *)&S->address, (socklen_t *)&S->addrlen)) < 0){
        perror("");
        return S->error;
    }
    S->valread = read(S->new_socket, buffer, BUFFER_SIZE);
    write(S->new_socket, response, strlen(response));
    printf("Respuesta enviada\n");
    close(S->new_socket);
}
#endif
