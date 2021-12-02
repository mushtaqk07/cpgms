#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_NAME_SIZE 512
#define MAX_CHAR 512

#define MAX_COULMNS 1000
#define MAX_ROWS 500

struct list_files {
    char *file_name;
    struct list_files* next;
};

typedef struct _hash_md5 {
    char content[MAX_CHAR];
    struct list_files *fl;
    struct _hash_md5 *next;	
    int num_files;
    int idx;
}hash_md5;

char ***pp_ptr;
int *Columnsizes = NULL;
hash_md5 *fl_md5sum_head = NULL;
int num_rows = 0;
int total_num_files = 0;

struct list_files * add_file_to_list(struct list_files **list, char *fname)
{
    struct list_files *node,*n;
    node = *list;
	
    if (node== NULL) {
        node = (struct list_files*)malloc(sizeof(struct list_files));
        if (node == NULL)
            return NULL;
        node->file_name = (char *)malloc(strlen(fname) + 1);
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
        node->file_name = (char *)malloc(strlen(fname) + 1);
        strcpy(node->file_name,fname);
        *list = node;
        return node;
    }
}

hash_md5* check_dupfile_file_node (char *dir, char *file, char* fl_content)
{
    char fl_name[MAX_FILE_NAME_SIZE] = {0};
    hash_md5 *node = NULL,*prev = NULL;
    struct list_files *fl_node = NULL;
    FILE *fp;
    char **p_ptr;
    
    /*1. Form complete file name*/
    strcpy(fl_name,dir);
    strcat((fl_name+strlen(fl_name)),"/");
    strcat((fl_name+strlen(fl_name)),file);
    	
    /*2. Check if file is duplicate of existing file*/
    node = fl_md5sum_head;
	prev = NULL;
    while(node) {
        if (strcmp(node->content,fl_content) == 0) {
            if (node->num_files == 1) {
                p_ptr = (char **) malloc(sizeof(char *) * MAX_COULMNS);
                pp_ptr[num_rows] = p_ptr;
                Columnsizes[num_rows] = 1;
                node->idx = num_rows;                
                num_rows++;
                p_ptr[0] = node->fl->file_name;
                //pp_ptr[node->idx][0] = node->fl->file_name;
            }
            node->num_files++;
            fl_node = add_file_to_list(&(node->fl),fl_name);
            if (fl_node == NULL) {
                exit(1);
            }
            pp_ptr[node->idx][node->num_files-1] = fl_node->file_name;
            Columnsizes[node->idx] += 1; 
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
    node->idx = 0;
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
    int i,j,off;   
    
    fl_md5sum_head = NULL;   
    *returnSize = 0;
    num_rows = 0;
    pp_ptr = NULL;
    Columnsizes = NULL;
    total_num_files = pathsSize;
    
    pp_ptr = (char ***)calloc(1,(sizeof(char **) * MAX_ROWS));
    Columnsizes = (int *)calloc(1,(sizeof(int) * MAX_ROWS));
          
    for(i = 0; i < pathsSize; i++) {
        //printf("Path:%s\n",paths[i]);
        //ptr_path = strdup(paths[i]);
        file_list = paths[i]; //ptr_path;
        dir = strtok(file_list," ");
        //file_content = strtok_r(file_list," ",&file_list);        
        file = strtok(NULL,"(");
        while(file != NULL) {
			content = strtok(NULL,")");
            //printf("\ndir:%s file:%s %s\n",dir,file,content);             
            check_dupfile_file_node(dir,file,content);            
             file = strtok(NULL," (");
        }
        //free(ptr_path);
    }
    
    *returnSize = num_rows;    
    *returnColumnSizes = Columnsizes;         
  /*for(i=0;i<*returnSize;i++) {
        printf("Duplicate files :%d\n",*returnSize);
        printf("column size :%d\n",(*returnColumnSizes)[0]);
        for (j=0;j < (*returnColumnSizes)[i]; j++) {
            printf("pp_ptr[%d][%d]:%s\n",i,j,pp_ptr[i][j]);
        }
    }*/

    /*Hash Nodes, File-list nodes and single files allocated*/
    struct list_files *fl,*tfl;
    hash_md5 *tnode;    
    node = fl_md5sum_head;
    while (node) {
        if (node->num_files == 1) {
            free(node->fl->file_name);
        }
        fl = node->fl;
        while(fl){
            tfl = fl;
            fl = fl->next;
            free(tfl);
        }
        tnode = node;
        node = node->next;
        free(tnode);
    }
    return pp_ptr;
}

