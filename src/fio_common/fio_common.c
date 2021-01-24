/**
 *
 * @FILE        	: FIO_COMMON.C
 * @DESCRIPTION 	: LIB TO EXECUTE COMMON BASH FILE OPERATION
 *
 * @AUTHOR      	: VIKI ( VIGNESH NATARAJAN )
 * @CONTACT         : VIKILABS.ORG
 *
 */

/*
    Copyright (c) 2016 Viki( Vignesh Natarajan )
    
    Contact @ vikilabs.org

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software
    is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fio_common.h"
#include "../bash_common/bash_common.h"

#define FIO_DEBUG 1

static void clear_string(char *str, int str_len)
{
    int i;

    for(i=0; i<str_len; i++){   
            str[i] = '\0';
    }
}

static void clear_escape_char(char *str, int str_len)
{
    int i;

    for(i=0; i<str_len; i++){  
        if(str[i] == '\r'){
            str[i] = '\0';
        }else if(str[i] == '\n'){
            str[i] = '\0';
        }else if(str[i] == '\b'){
            str[i] = '\0';
        }
    }
}

int create_empty_file(char *fname)
{
    char cmd[256], ret = 0;
    if(!fname) return 0;
    snprintf(cmd, sizeof(cmd), "touch %s", fname);
    
    int i=0;while((i++)<10){
        
        if(is_file_exist(fname)){ 
            ret = 1;
            break;
        }

        if(FIO_DEBUG) printf("[ fio_common ] %s \n", cmd);
        exec_command(cmd);
        sleep(1);
    }

    return ret;
}

int rm(char *file_name)
{
    char cmd[256], ret = 0;
    if(!file_name) return 0;

    snprintf(cmd, 256, "rm %s", file_name);

    int i=0;while((i++)<10){
        
        if(!is_file_exist(file_name)){
            ret = 1;
            break;
        }

        if(FIO_DEBUG) printf("[ fio_common ] %s \n", cmd);
        exec_command(cmd);
        sleep(1);
    }

    return ret;
}


int rm_force(char *dir_name)
{
    char cmd[256], ret = 0;
    if(!dir_name) return 0;

    if(!is_file_exist(dir_name)) return 0;

    snprintf(cmd, 256, "rm -rf %s", dir_name);

    int i=0;while((i++)<10){
        if(!is_file_exist(dir_name)){
            ret = 1;
            break;
        }
        
        if(FIO_DEBUG) printf("[ fio_common ] %s \n", cmd);
        exec_command(cmd);
        sleep(1);
    }

    return ret;
}


int mv(char *src, char *dst)
{
    char cmd[512], ret = 0;
    if(!src) return 0;
    if(!dst) return 0;

    if(!is_file_exist(src)) return 0;

    rm_force(dst);

    snprintf(cmd, 512, "mv %s %s", src, dst);

    int i=0;while((i++)<10){
        if(FIO_DEBUG) printf("[ fio_common ] %s \n", cmd);
        exec_command(cmd);
        sleep(2);

        if(is_file_exist(dst)){
            ret = 1;
            break;
        }
    }

    return ret;
}

int cp_file(char *src, char *dst)
{
    char cmd[512], ret = 0;
    if(!src) return 0;
    if(!dst) return 0;

    if(!is_file_exist(src)) return 0;

    rm_force(dst);

    snprintf(cmd, 512, "cp -f %s %s", src, dst);

    int i=0;while((i++)<10){
        if(FIO_DEBUG) printf("[ fio_common ] %s \n", cmd);
        exec_command(cmd);
        sleep(2);

        if(is_file_exist(dst)){
            ret = 1;
            break;
        }
    }

    return ret;
}

int cp_dir(char *src, char *dst)
{
    char cmd[512], ret = 0;
    if(!src) return 0;
    if(!dst) return 0;

    if(!is_file_exist(src)) return 0;

    rm_force(dst);

    snprintf(cmd, 512, "cp -arf %s %s", src, dst);

    int i=0;while((i++)<10){
        if(FIO_DEBUG) printf("[ fio_common ] %s \n", cmd);
        exec_command(cmd);
        sleep(2);

        if(is_file_exist(dst)){
            ret = 1;
            break;
        }
    }

    return ret;
}

int rm_link(char *file_link)
{
    char cmd[512];
    if(!file_link) return 0;

    snprintf(cmd, 512, "unlink %s", file_link);

    if(exec_command(cmd) == 0){
        if(!is_file_exist(file_link)){
            if(FIO_DEBUG) printf("[ success ] %s \n", cmd);
            return 1;
        }
    }   

    if(FIO_DEBUG) printf("[ failure ] %s \n", cmd);
    return 0;
}


int create_link(char *file_name, char *file_link)
{
    char cmd[512];
    if(!file_name) return 0;
    if(!file_link) return 0;

    if(!is_file_exist(file_name)) return 0;

    rm_link(file_link);

    snprintf(cmd, 512, "ln -sf %s %s", file_name, file_link);

    if(exec_command(cmd) == 0){
        if(is_file_exist(file_link)){
            if(FIO_DEBUG) printf("[ success ] %s \n", cmd);
            return 1;
        }
    }

    if(FIO_DEBUG) printf("[ failure ] %s \n", cmd);
    return 0;
}

int mkdir_p(char *dir_name)
{
    char cmd[512];
    if(!dir_name) return 0;

    if(is_file_exist(dir_name)) return 1;

    snprintf(cmd, 512, "mkdir -p %s", dir_name);

    if(exec_command(cmd) == 0){
        if(is_file_exist(dir_name)){
            if(FIO_DEBUG) printf("[ success ] %s \n", cmd);
            return 1;
        }
    }

    if(FIO_DEBUG) printf("[ failure ] %s \n", cmd);
    return 0;
}


int is_file_exist(char *file_name)
{
    if( access( file_name, F_OK ) != 0 ) {
        if(FIO_DEBUG) printf("[ status ] file ( %s ) not exist \n", file_name);
        return 0;
    }

    if(FIO_DEBUG) printf("[ status ] file ( %s ) exist \n", file_name);
    return 1;
}

int get_first_line_of_file_as_string(char *file_name, char *str, int str_len)
{
    char cmd[256];

    if(!str){ 
        return -1;
    }else{
        clear_string(str, str_len);
    }
    
    if(!file_name) return -1;
    if(!is_file_exist(file_name)) return -1;

    snprintf(cmd, 256, "cat %s", file_name);

    get_command_out_first_line(cmd, str, str_len);

    clear_escape_char(str, str_len);

    return 0;
}

int get_md5sum(char *file_name, char *str, int str_len)
{
    char cmd[256];

    if(!str){ 
        return -1;
    }else{
        clear_string(str, str_len);
    }
    
    if(!file_name) return -1;
    if(!is_file_exist(file_name)) return -1;

    snprintf(cmd, 256, "md5sum %s | awk \'{print $1}\'", file_name);
    get_command_out_first_line(cmd, str, str_len);
    clear_escape_char(str, str_len);
     
    return 0;
}



int file_truncate_write(char *file_name, char *str)
{
    char cmd[256];
    
    if(!file_name)
        return 0;
    
    if(!str)
        return 0;
    
    snprintf(cmd, 256, "echo \"%s\" > %s", str,  file_name);

    if(exec_command(cmd) == 0){
        sleep(1);
        if(FIO_DEBUG) printf("[ success ] %s \n", cmd);
        return 1;
    }else{
        if(FIO_DEBUG) printf("[ failure ] %s \n", cmd);
        sleep(1);
        return 0;
    }

    return 0;
}

int tar(char *input, char *output)
{
    char cmd[512];
    if(!input) return 0;
    if(!output) return 0;

    if(!is_file_exist(input)) return 0;

    if(is_file_exist(output)) {
        rm_force(output);
    }

    snprintf(cmd, 512, "tar -czf %s %s", output, input);

    if(exec_command_discard_output(cmd) == 0){
        if(is_file_exist(output)) {
            if(FIO_DEBUG) printf("[ success ] %s \n", cmd);
            return 1;
        }
    }

    if(FIO_DEBUG) printf("[ failure ] %s \n", cmd);
    return 0;
}

int untar(char *input, char *output)
{
    char cmd[512];
    if(!input) return 0;

    if(!is_file_exist(input)) return 0;

    if(output){
        if(is_file_exist(output)) {
            rm_force(output);
        }
    }

    snprintf(cmd, 512, "tar -zxf %s", input);

    if(exec_command_discard_output(cmd) == 0){
        if(is_file_exist(output)) {
            if(FIO_DEBUG) printf("[ success ] %s \n", cmd);
            return 1;
        }
    }

    if(FIO_DEBUG) printf("[ failure ] %s \n", cmd);
    return 0;
}

int cd_and_tar(char *path, char *input, char *output)
{
    char cmd[1024], fin[128], fout[128];
    if(!input) return 0;
    if(!output) return 0;
    if(!path) return 0;

    clear_string(fin, sizeof(fin));
    clear_string(fout, sizeof(fout));
    snprintf(fin, sizeof(fin), "%s/%s", path, input);

    if(!is_file_exist(fin)) return 0;

    snprintf(fout, sizeof(fout), "%s/%s", path, output);

    if(is_file_exist(fout)){
        rm_force(fout);
    }

    snprintf(cmd, sizeof(cmd), "cd %s; tar -czf %s %s", path, output, input);

    if(exec_command_discard_output(cmd) == 0){
        if(is_file_exist(fout)){
            if(FIO_DEBUG) printf("[ success ] %s \n", cmd);
            return 1;
        }
    }

    if(FIO_DEBUG) printf("[ failure ] %s \n", cmd);
    return 0;
}

int cd_and_untar(char *path, char *input, char *output)
{
    char cmd[1024], fin[128], fout[128];
    if(!input) return 0;
    if(!output) return 0;
    if(!path) return 0;

    clear_string(fin, sizeof(fin));
    clear_string(fout, sizeof(fout));
    snprintf(fin, sizeof(fin), "%s/%s", path, input);

    if(!is_file_exist(fin)) return 0;

    snprintf(fout, sizeof(fout), "%s/%s", path, output);

    if(is_file_exist(fout)){
        rm_force(fout);
    }

    snprintf(cmd, sizeof(cmd), "cd %s; tar -zxf %s", path, input);

    if(exec_command_discard_output(cmd) == 0){
        if(is_file_exist(fout)){
            if(FIO_DEBUG) printf("[ success ] %s \n", cmd);
            return 1;
        }
    }

    if(FIO_DEBUG) printf("[ failure ] %s \n", cmd);
    return 0;
}

int delete_object_force(char *path, char *fname)
{
    char full_path[1024];
    if(!path) return 0;
    if(!fname) return 0;

    snprintf(full_path, sizeof(full_path), "%s/%s", path, fname);
    
    if(!is_file_exist(full_path)) return 0;

    rm_force(full_path);

    if(!is_file_exist(full_path)) return 1;

    return 0;
}

#if 0
int main(){
    char out[512];
    int out_len = 512;
    create_link("/home/factory", "/home/test123");
    sleep(10);
    
    get_first_line_of_file_as_string("/home/imei.txt", out, out_len);

    printf("OUTPUT = %s\n", out);

    sleep(10);
    rm_link("/home/test123");
    sleep(10);
    file_truncate_write("/home/ttt", "test");
    sleep(10);
    mv("/home/ttt", "/home/www");
    sleep(10);
    cp_file("/home/www", "/home/t1");
    sleep(10);
    cp_file("/home/www", "/home/t2");
    sleep(10);
    cp_file("/home/www", "/home/t3");
    sleep(10);
    mkdir_p("/home/test_dir");
    sleep(10);
    cp_dir("/home/factory", "/home/f1");
    sleep(10);
    rm_force("/home/test_dir");
    sleep(10);
    get_first_line_of_file_as_string("/home/firmware/config/cred.xml", out, out_len);
    printf("OUTPUT = %s\n", out);

    //tar("/home/factory", "/home/f1.tar.gz");
    //untar("/home/fl/factory.tar.gz", NULL);

    //cd_and_tar("/home", "factory", "f2.tar.gz");
    cd_and_untar("/home/f2", "f2.tar.gz", "f2");

}
#endif
