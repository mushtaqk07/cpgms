/*
 * Q:https://leetcode.com/problems/find-duplicate-file-in-system/
 * Find duplicate files, Hashing with key based on contenet file will
 * help in finding duplicate file, md5sum or checksum can be used as
 * Hash Key and list_files as key.
 *
 * popen() can be used to run commands and read the output from
 * pipe fd (returned from popen()).Other way is to use System()
 * along with file open and read.
 *
 * strtok_r(string,delimeter,**saveptr), can be used to split the string
 * based on token. Note, strings passed to strtok will be modified,
 * where ever delimeter is there it will replaced with NULL on each
 * call to strtok/strtok_r.
 * Dup the string using strdup(), this function allocates the
 * memory and this needs to be freed.strtok_r() returns one taoken
 * on each call.
 * Note: Strtok_r, save the pointer in string pointing after the delimeter
 * in the pointer saveptr passed to function. The pointer saveptr,
 * can be passed later to fetch further tokens. Even NULL can be passed as
 * first argumnet if no inbetween strtok/strtok_r with different string.
 *
 * Strtok_r() can be called back to back with different strings as pointer
 * in string after token is saved in saveptr and further taokens in string
 * can fetched passing the saveptr each time.
 * In this pgm, instead of md5sum/checksum, directly contents are compared as
 * contents passed are strings of limited size.
 * First version of pgm with no optimization.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_NAME_SIZE 512
#define MAX_CHAR 512

struct list_files {
    char file_name[MAX_FILE_NAME_SIZE];
    struct list_files* next;
};

typedef struct _hash_md5 {
    char content[MAX_CHAR];
    struct list_files *fl;
    struct _hash_md5 *next;
    int num_files;
}hash_md5;

hash_md5 *fl_md5sum_head = NULL;
 int num_rows = 0;

struct list_files * add_file_to_list(struct list_files **list, char *fname)
{
    struct list_files *node,*n;
    node = *list;

    if (node== NULL) {
        node = (struct list_files*)malloc(sizeof(struct list_files));
        if (node == NULL)
            return NULL;
        strcpy(node->file_name,fname);
        node->next = NULL;
        *list = node;
        return node;
    } else {
        n = node;
        node = (struct list_files*)malloc(sizeof(struct list_files));
        if (node == NULL)
            return NULL;
        node->next = n;
        strcpy(node->file_name,fname);
        *list = node;
        return node;
    }
}

//hash_md5* check_add_md5sum_node (char *dir, char *file)
hash_md5* check_dupfile_file_node (char *dir, char *file, char* fl_content)
{
    char fl_name[MAX_FILE_NAME_SIZE] = {0};
    hash_md5 *node = NULL,*prev = NULL;
    FILE *fp;
    char buffer[512] = {0};

    /*1. Form complete file name*/
    strcpy(fl_name,dir);
    strcat((fl_name+strlen(fl_name)),"/");
    strcat((fl_name+strlen(fl_name)),file);

    /*3. Check if file is duplicate of existing file*/
    node = fl_md5sum_head;
    prev = NULL;
    while(node) {
        if (strcmp(node->content,fl_content) == 0) {
            if (node->num_files == 1) {
                num_rows++;
            }
            node->num_files++;
            add_file_to_list(&(node->fl),fl_name);
           /*printf("\nDup file:%s in node:0x%x numfiles:%d\n",
                  fl_name,node,node->num_files);*/
            return node;
        }
        prev = node;
        node = node->next;
    }
    
    node = (hash_md5 *) malloc(sizeof(hash_md5));
    if (node == NULL) {
        return NULL;
    }

    strcpy(node->content,fl_content);
    node->num_files = 1;
    node->next = NULL;
    node->fl = NULL;
    add_file_to_list(&(node->fl),fl_name);
    //printf("\nFisrt file:%s in node:0x%x\n",fl_name,node);
    if(prev) {
        prev->next = node;
    } else {
        fl_md5sum_head = node;
    }
    return node;
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** findDuplicate(char ** paths, int pathsSize, int* returnSize, int** returnColumnSizes){
    
    char *file_list = NULL,*ptr_path;
    char *dir = NULL, *file,*file_content = NULL,*content = NULL;    
    hash_md5 *node = NULL;
    struct list_files *dup_file = NULL;
    char ***pp_ptr,**p_ptr,*str;
    int i,j,off,*columnsizes;   
   
    fl_md5sum_head = NULL;   
    *returnSize = 0;
    num_rows = 0;
    
    for(i=0; i < pathsSize; i++) {
        //Search in directory        
       // printf("Path:%s\n",paths[i]);
        ptr_path = strdup(paths[i]);
        file_list = ptr_path;
        dir = strtok_r(file_list," ",&file_list);
        file_content = strtok_r(file_list," ",&file_list);        
        while(file_content != NULL) {
            file = strtok_r(file_content,"()",&file_content);
            content = strtok_r(file_content,"()",&file_content);
         //   printf("\ndir:%s file:%s %s\n",dir,file,content);             
            check_dupfile_file_node(dir,file,content);            
            file_content = strtok_r(file_list," ",&file_list); 
    
        }
        free(ptr_path);
    }
    
    node = fl_md5sum_head;
    /*while (node) {
        if (node->num_files > 1) {
            num_rows++;
        }
        node = node->next;
    }*/
    *returnSize = num_rows;    
    pp_ptr = (char ***)calloc(1,(sizeof(char **) * num_rows));    
    columnsizes = (int *)calloc(1,(sizeof(int) * num_rows));
    *returnColumnSizes = columnsizes;
    
    i = 0;
    node = fl_md5sum_head;
    pp_ptr;
    struct list_files *fl,*tfl;
    hash_md5 *tnode;
    while(node) {
        if (node->num_files > 1) {
            p_ptr = (char **) malloc(sizeof(char *) * node->num_files);
            pp_ptr[i] = p_ptr;
            columnsizes[i] = node->num_files;
            dup_file = node->fl;            
            j = 0;
            while(dup_file) {
                str = (char *)malloc(strlen(dup_file->file_name) + 1);          
                memcpy(str,dup_file->file_name,strlen(dup_file->file_name)+1);
                p_ptr[j] = str;
                j++;
                tfl = dup_file;
                dup_file = dup_file->next;
                free(tfl);
            }
            i++;
                
        }
        else {
            free(node->fl);
        }
        tnode = node;
        node = node->next;
        free(tnode);        
    }     
  /*for(i=0;i<*returnSize;i++) {
        printf("Duplicate files :%d\n",*returnSize);
        printf("column size :%d\n",(*returnColumnSizes)[0]);
        for (j=0;j < (*returnColumnSizes)[i]; j++) {
            printf("pp_ptr[%d][%d]:%s\n",i,j,pp_ptr[i][j]);
        }
    }*/    
    return pp_ptr;
}

int main (int argc, char *argv[])
{

    char ***ppp = NULL;
    int *p_colsize = NULL,retsize=0;
    int pathsize = 0;

    if (argc < 3) {
        printf("\nenter inumber of pathsize and list of file paths\n");
        exit(1);
    }

    ppp = findDuplicate((argv+2),pathsize,&retsize,&p_colsize);
    return 0;
}
