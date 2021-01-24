/**
 *
 * @FILE        	: BASH_COMMON.C
 * @DESCRIPTION 	: LIB TO EXECUTE COMMON BASH COMMANDS
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
#include <unistd.h>
#include "bash_common.h"
#include <sys/wait.h>
#define BASH_DEBUG 1

static void collect_and_discard_output(FILE *fp)
{
    char *ret = NULL;
    char buf[512];

    while(1){
        ret = fgets(buf, sizeof(buf), fp);
        if(ret == NULL){
            break;
        }
    }

    return;
}

int exec_command_discard_output(char *bash_command)
{
    FILE *fp = NULL;
    int exit_code = 0, ret;

    if(!bash_command) return exit_code;
    
    fp = popen(bash_command, "r");

    if (fp == NULL) return exit_code;

    collect_and_discard_output(fp);

    ret = pclose(fp);

    if(ret == -1){
        exit_code = 1;
    }else{
        exit_code = WEXITSTATUS(ret);
    }

    if(BASH_DEBUG){
        printf("EXIT_CODE(%d) | CMD ( %s )\n", exit_code, bash_command);
    }

    return exit_code;

}
int exec_command(char *bash_command)
{
    FILE *fp = NULL;
    int exit_code = 0, ret;

    if(!bash_command) return exit_code;
    
    fp = popen(bash_command, "r");

    if (fp == NULL) return exit_code;

    collect_and_discard_output(fp);

    ret = pclose(fp);

    if(ret == -1){
        exit_code = 1;
    }else{
        exit_code = WEXITSTATUS(ret);
    }

    if(BASH_DEBUG){
        printf("EXIT_CODE(%d) | CMD ( %s )\n", exit_code, bash_command);
    }

    return exit_code;
}

int exec_command_bg(char *bash_command)
{
    char bg_cmd[512];
    FILE *fp = NULL;
    int ret = 0, exit_code = 0;

    if(!bash_command) return exit_code;
    
    snprintf(bg_cmd, 512, "%s  1>&- 2>&-", bash_command);
    
    fp = popen(bg_cmd, "r");

    if (fp == NULL) return exit_code;
    
  
    ret = pclose(fp);

    if(ret == -1){
        exit_code = 1;
    }else{
        exit_code = WEXITSTATUS(ret);
    }

    if(BASH_DEBUG){
        printf("EXIT_CODE(%d) | CMD ( %s )\n", exit_code, bg_cmd);
    }

    return exit_code;

}

int get_command_out_first_line(char *bash_command, char *out, int out_len)
{
    FILE *fp = NULL;
    int ret=0, exit_code = 0, i;

    if(!bash_command) return exit_code;
    if(!out) return exit_code;
    if(out_len <= 0)  return exit_code;

    for(i=0; i<out_len; i++){
        out[i] = '\0';
    }

    fp = popen(bash_command, "r");

    if (fp == NULL) return exit_code;

    fgets(out, out_len, fp);

    ret = pclose(fp);

    if(ret == -1){
        exit_code = 1;
    }else{
        exit_code = WEXITSTATUS(ret);
    }
   
    if(BASH_DEBUG){
        printf("EXIT_CODE(%d) | CMD ( %s )\n", exit_code, bash_command);
        printf("CMD_OUT ( %s )\n", out);
    }

    return exit_code;
}

#if 0
int main()
{
    char out[512];
    exec_command("ls /home/t");
    exec_command("ls asdfasdfasdf");
    exec_command_bg("touch /tmp/viki123");
    get_command_out_first_line("cat /home/imei.txt", out, 512);
    return 0;
}
#endif
