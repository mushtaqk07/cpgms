/*
 * 3 sum triplets no duplicate numbers
 * https://leetcode.com/problems/3sum/
 * Three solutions shown in this program,
 *
 * 1.Hash based, summation of numbers as hash didn't work.
 *
 * 2. Three-loop soultion, to avoid duplicate numbers,
 * Same number shouldn't repeat in same position
 * morethan once.
 * For this solution first you have sort the numbers,
 * So that number can be skipped if check of previous position
 * number is same as current in same position. Otherwise
 * if not sorted we have check in all previous numbers,
 * more time consuming.
 *
 * 3. Same as soultion 2, sort the numbers and skip 
 * if number is same at previous location. 
 * Instead of two-sub loops use 2-pointers to check for
 * three sum and move either left or right pointer, 
 * this one loop replaces two sub-loops (2nd and 3rd position)
 * in 3-loop solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define pair 3 //triplet
#define false 0
#define true 1

int cnt = 0;

#if HASH_METHOD //Couldn't figureout unique Hash for triplet
int check_hashed (int n1,int n2,int n3, int *hash)
{
    int i;
    int l1,l2,l3;
    int hashnum = 0;
    
    if (n1 > n2) {
        l1=n1;
        l2=n2;
    } else {
        l1=n2;
        l2=n1;
    }
    
    if (n3 > l1) {
        l3 = l2;
        l2 = l1;
        l1 = n3;
    } else if (n3 > l2) {
        l3 = l2;
        l2 = n3;
    } else {
        l3 = n3;
    }
    
    hashnum = (hashnum * 10) + l1;
    hashnum = (hashnum * 10) + l2;
    hashnum = (hashnum * 10) + l3;
    if (hashnum == 945)
                    printf("\n n1:%d n2:%d n3:%d hash:%d",n1,n2,n3,hashnum);
    if(cnt == 0) {
        hash[cnt] = hashnum;
        return false;
    } else {
        for (i = 0; i < cnt; i++) {
            if (hash[i] == hashnum) {
                
                return true;
            }
        }
        hash[cnt] = hashnum;
        return false;
    }
}

/*
 * param[in]  n1,n2,n3 : numbers
 *            hash : array with hash code
 *            cnt : current number of hashed numbers
 * returns size of elements meeting criteria or 0
 */
int check_combination_zero(int n1,int n2, int n3,int *hash) {
    int exist = 0;
    int sum = 0;
    int i;
    
    sum = n1 + n2 + n3;
    
    if (sum == 0) {
        exist = check_hashed(n1,n2,n3,hash);
        if (exist == true) {
            return 0;
        } else {
            return pair;
        }
    } else {
        return 0;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int max_cmbns = 0;  
    int **arr_sum = NULL;
    int i,j,k,size=0;
    int max_pairs = 0;
    int *hash = NULL;
    
    if (numsSize < 3) {
        *returnSize = 0;
        return NULL;
    }
    /* Max combinations of numbers can be with doublet,
     * Assuming each number with another number (pair) meets the
     * requirement, then max comninations is summation of series 
     * of number-1 ((num-1)+(num-2)+ .......+1)
     * Summation formalua for n-series ∑ = n + (n-1) + (n-2) + --- + 1;
     * the results can also be obtained with formula = n/2 * (e1+en)
     */
    max_pairs = ((numsSize-1) * (1 + (numsSize-1))) / 2;
    max_pairs += 1; //Since division is integral
    
    cnt = 0;
    arr_sum = (int **)calloc(max_pairs, sizeof(int *));
    *returnColumnSizes =  (int *)calloc(max_pairs, sizeof(int));
    hash = (int *)calloc(max_pairs, sizeof(int));
    
    sort_arr(nums,arr,numsSize);
    
    for (i=0;i < (numsSize-2); i++) {
        for (j=i+1; j < (numsSize-1);j++) {
            for (k=j+1;k < numsSize; k++) {
                size = check_combination_zero(nums[i],nums[j],nums[k],hash);
                if (size != 0) {
                    arr_sum[cnt] = (int *)calloc(pair,sizeof(int));
                    (*returnColumnSizes)[cnt] = size;                     
                    arr_sum[cnt][0] = nums[i];
                    arr_sum[cnt][1] = nums[j];
                    arr_sum[cnt][2] = nums[k];
                    cnt++;
                }
            }
        }
    }
    
    *returnSize = cnt;
    return arr_sum;
}
#endif

void swap(int *a,int i1, int i2) {
    int t = a[i1];
    a[i1] = a[i2];
    a[i2] = t;
}
void insert_sort (int *a,int size)
{
    int i,j,key;
    key = 1;
    for (i=1;i<size;i++) {
        key = i;
        for(j = i-1; ((j >= 0) && a[j] > a[key]);j--) {
            swap(a,j,key);
            key = j;
        }
    }
    
    return;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int max_cmbns = 0;
    int *arr = NULL;
    int **arr_sum = NULL;
    int i,j,k,size=0;
    int max_pairs = 0;
    int *hash = NULL;
    
    if (numsSize < 3) {
        *returnSize = 0;
        return NULL;
    }
    /* Max combinations of numbers can be with doublet,
     * Assuming each number with another number (pair) meets the
     * requirement, then max comninations is summation of series 
     * of number-1 ((num-1)+(num-2)+ .......+1)
     * Summation formalua for n-series ∑ = n + (n-1) + (n-2) + --- + 1;
     * the results can also be obtained with formula = n/2 * (e1+en)
     */
    max_pairs = ((numsSize-1) * (1 + (numsSize-1))) / 2;
    max_pairs += 1; //Since division is integral
    
    cnt = 0;
    arr_sum = (int **)calloc(max_pairs, sizeof(int *));
    *returnColumnSizes =  (int *)calloc(max_pairs, sizeof(int));

    arr = (int *)calloc(numsSize, sizeof(int));
    memcpy((void*)arr,(void*)nums,numsSize*sizeof(int));
    insert_sort(arr,numsSize);
    /*for(i=0; i <numsSize; i++) {
        printf("%d ",arr[i]);
    }*/
    for (i = 0; i < numsSize-2; i++) {
        if ((i != 0) && (arr[i] == arr[i-1])) {
            continue;
        } 
        //printf("%d\n",i);
        l = i+1;
        r = numsSize - 1;
        while (l < r) {
            //printf("%d %d\n",l,r);
            if ((arr[i]+arr[l]+arr[r]) == 0) {
                arr_sum[cnt] = (int *)calloc(pair,sizeof(int));
                (*returnColumnSizes)[cnt] = 3;                     
                arr_sum[cnt][0] = arr[i];
                arr_sum[cnt][1] = arr[l];
                arr_sum[cnt][2] = arr[r];
                //printf("\nsum %d:%d %d:%d %d:%d\n",i,arr[i],l,arr[l],r,arr[r]);
                cnt++;
                l++;
                while((l) < r) {
                    if (arr[l] == arr[l-1]) {
                        l++;
                        continue;
                    }
                    else {
                        break;
                    }
                }
                continue;
            } else if ((arr[i]+arr[l]+arr[r]) < 0) {
                 l++;
                while((l) < r) {
                    if (arr[l] == arr[l-1]) {
                        l++;
                        continue;
                    }
                    else {
                        break;
                    }
                }
                continue;
            } else if ((arr[i]+arr[l]+arr[r]) > 0) {
                 r--;
                while((l) < r) {
                    if (arr[r] == arr[r+1]) {
                        r--;
                        continue;
                    }
                    else {
                        break;
                    }
                }
                continue;
            }
        }
    }
#ifdef THREE_LOOP_SOLUTION //Time limit exceeds for large input
    for (i=0;i < (numsSize-2); i++) {
		/*
		 * If Previous number repeats in same position,
		 * skip otherwiese duplicate sequence will be
		 * generated
		 */
        if (i != 0) {	
            if (arr[i] == arr[i-1])
                continue;
        }
        for (j=i+1; j < (numsSize-1);j++) {
			/*
			 * If Previous number repeats in same position,
			 * skip otherwise duplicate sequence will be
			 * generated.
			 * Check only for second positions, if j-1 is equal to i,
			 * then j-1 is of first position, this should not be skipped.
			 */			
            if (i != (j-1)) {
                if (arr[j] == arr[j-1])
                    continue;
            }
	
            for (k=j+1;k < numsSize; k++) {
				/*
				 * If Previous number repeats in same position,
				 * skip otherwise duplicate sequence will be
				 * generated.
				 * Check only for third positions, if k-1 is equal to j,
				 * then k-1 is of second position, this should not be skipped.
				 */						
                if ((k-1) != j) {
                    if (arr[k] == arr[k-1])
                        continue;
                }
                if ((arr[i]+arr[j]+arr[k]) == 0) {
                    arr_sum[cnt] = (int *)calloc(pair,sizeof(int));
                    (*returnColumnSizes)[cnt] = 3;                     
                    arr_sum[cnt][0] = arr[i];
                    arr_sum[cnt][1] = arr[j];
                    arr_sum[cnt][2] = arr[k];
                    cnt++;
                }
            }
        }
    }
#endif
    
    free(arr);
    *returnSize = cnt;
    return arr_sum;
}



int main (int argc, char **argv)
{
	int *num = NULL;
	int numsSize = 0,i,j;
	int *returnColumnSizes;
	int returnSize = 0;
	int **arr_sum;
	
	if(argc < 3) {
		printf("\nUsage: Enter number of elements and elements to check for threeSum\n");
		return(0);
	}
	
	numsSize = atoi(argv[1]);
	num = (int *)calloc(cnt,sizeof(int));
	
	for(i=0;i<numsSize;i++) {
		num[i] = atoi(argv[i+2]);
	}

	arr_sum = threeSum(num,numsSize,&returnSize,&returnColumnSizes);
	
	printf("\n{");
	for(i=0;i<returnSize;i++) {
		if(i != 0) {
			printf(",");
		}
		printf(" {");
		for(j=0;j<returnColumnSizes[i];j++) {
			if (j != 0) {
				printf(",");
			}
			printf("%d",arr_sum[i][j]);
		}
		printf("} ");
	}
	printf("}\n");
}
