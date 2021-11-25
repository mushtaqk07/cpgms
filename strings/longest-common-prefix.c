#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_common_str(char *str,char *cmn_str, int *size) {
    int i=0;
    char *s1=cmn_str, *s2 = str;
    
    if(s1[i] != s2[i]) {
        *size = 0;
        return ;
    }
    
    for(i=0; i < *size; i++) {
        if(s1[i] != s2[i]) {
            *size = i;
            return ;
        }
    }
    
    return ;
}

char * longestCommonPrefix(char ** strs, int strsSize){
    char *cmn_str = NULL;
    char *str = NULL;
    int  i,cnt,size = 0;
    
    if (strsSize == 0) {
        return "";
    } else if (strsSize == 1) {
        return strs[0];
    }
    
    cmn_str = strs[0];
    /*printf("str[0]:%s addr:%u\n",strs[0],(strs+0));
    printf("str[1]:%s addr:%u\n",strs[1],(strs+1));
    printf("str[2]:%s addr:%u\n",strs[2],(strs+2));*/
    //return "";
    size = strlen(cmn_str);
    i = 1;
    str = strs[1];
    cnt = 1;
    while (cnt < strsSize) {
        str = strs[i];
        find_common_str(str,cmn_str,&size);
        //printf("size:%d\n",size);
        if (size == 0) {            
            return "";
        }
        i++;        
        cnt++;   
    }
    
    cmn_str[size] = '\0';
    return cmn_str;
}

int main (int argc, char *argv[])
{
    int size=0;
    char **strings = NULL;
    char *cmn_str = NULL;

    if (argc < 2) {
	printf("Usage pgm string-list\n");
	return 0;
    }
	

    strings = argv+1;


    printf("%s\n",strings[0]);

	cmn_str = longestCommonPrefix(strings, (argc - 1));
	printf("%s\n",cmn_str);

	return 0;
}
