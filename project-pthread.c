#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 102400
#define NUM_THREADS 20

int n1,n2;
char *s1,*s2;
FILE *fp;
int countArray[NUM_THREADS]={0};

int totalNum;


int readf(FILE *fp)
{
	if((fp=fopen("emoji.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1=fgets(s1, MAX, fp);
	s2=fgets(s2, MAX, fp);
	n1=strlen(s1);  /*length of s1*/
	n2=strlen(s2)-1; /*length of s2*/

	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;
	return 0;
}




int num_substring(int start, int end)
{
int count = 0;
for (int i = start; i <= end; i++)
{
int a, b;
for (a = i, b = 0; b < n2; a++, b++)
{
if (*(s1 + a) != *(s2 + b))
{
break;
}
}
if (b == n2)
{
count++;
}
}
return count;
}


void *calSubStringThread(void *threadid){
    long tid;
    tid = (long)threadid;
  int start = (n1 / NUM_THREADS) * tid;
int end = (tid == NUM_THREADS - 1) ? n1 - 1 : start + (n1 / NUM_THREADS) - 1;
    int num = num_substring(start,end);
    printf("This is thread %ld, num of substring %s is %d\n", tid, s2, num);
  totalNum+=num;
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int t, rc;
    

	readf(fp);

	for(t=0; t<NUM_THREADS; t++){
        rc = pthread_create(&threads[t], NULL, calSubStringThread, (void *) (size_t)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(t=0; t<NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
    }

 	printf("The number of substrings is: %d\n", totalNum);

  
	return 1;
}