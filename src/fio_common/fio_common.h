/**
 *
 * @FILE        	: FIO_COMMON.H
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

#ifndef FIO_COMMON_H
#define FIO_COMMON_H

extern int rm(char *file_name);
extern int rm_force(char *dir_name);
extern int mv(char *src, char *dst);
extern int cp_file(char *src, char *dst);
extern int cp_dir(char *src, char *dst);
extern int mkdir_p(char *dir_name);
extern int rm_link(char *file_name);
extern int create_link(char *file_name, char *link);
extern int get_first_line_of_file_as_string(char *file_name, char *str, int str_len);
extern int file_truncate_write(char *file_name, char *str);
extern int is_file_exist(char *file_name);
extern int tar(char *input, char *output);
extern int untar(char *input, char *output);
extern int cd_and_tar(char *path, char *input, char *output);
extern int cd_and_untar(char *path, char *input, char *output);
extern int cd_and_untar_and_clean(char *path, char *input, char *output);
extern int delete_object_force(char *path, char *fname);
extern int create_empty_file(char *fname);
extern int get_md5sum(char *file_name, char *str, int str_len);

#endif
