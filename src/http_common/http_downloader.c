/**
 *
 * @FILE        	: HTTP_COMMON.C
 * @DESCRIPTION 	: LIB TO DO FILE DOWNLOAD VIA HTTP
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
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include "http_downloader.h"

#define DOWNLOADER_DEBUG 0

size_t cb_data_received(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t ret = fwrite(ptr, size, nmemb, (FILE *)stream);
  return ret;
}

int http_download(char *url, char *out)
{
    int ret = 0;
    CURL *handle = NULL;
    FILE *fp = NULL;
    char cmd[256];

    if(!url){
         return -1;
    }

    if(!out){
        return -1;
    }

    if( access( out, F_OK ) == 0 ) {
        printf("[ http_downloader ] removing old output file with same name ( %s )\n", out);
        snprintf(cmd, 256, "/bin/rm -rf %s", out);
        system(cmd);
        sleep(1);
    }

    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();

    if(!handle){
        return -1;
    }
   
    fp = fopen(out, "wb");

    if(!fp){
        return -1;
    }

    /*Log Message - Instruct Donot log*/
    curl_easy_setopt(handle, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 1L);

    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, cb_data_received);

    curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
    printf("[ http_downloader ] downloading ( %s ) to ( %s )\n", url, out);
    ret = curl_easy_perform(handle);

    fclose(fp);

    curl_easy_cleanup(handle);
    curl_global_cleanup();

    if(ret == CURLE_OK){
        return 1;
    }else{
        return 0;
    }

}


