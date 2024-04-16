#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

typedef int keytype;
typedef float othertype;

typedef struct {
	keytype key;
	othertype otherfields;
} recordtype;

void swap(recordtype *a, recordtype *b){
	recordtype tmp = *a;
	*a = *b;
	*b = tmp;
}

void selection_sort(recordtype *a, int n){
	int i, j;
	for(i = 0; i < n - 1; i++){
		int min_i = i;
		int min_key = a[i].key;
		for(j = i + 1; j < n; j++){
			if(a[j].key < min_key) {
				min_i = j;
				min_key = a[j].key;
			}
		}
		swap(&a[i], &a[min_i]);
	}
}

void read_file(recordtype *a, int *n){
	FILE *f = fopen("data.txt", "r");
	if(f == NULL){
		printf("Error\n");
		return;
	}
	
	int i = 0;
	while(fscanf(f, "%d %f", &a[i].key, &a[i].otherfields) > 0){
		i++;
	}
	fclose(f);
	*n = i;
}

void print_data(recordtype *a, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%3d %5d  %8.2f\n", i, a[i].key, a[i].otherfields);
	}
}

int main(){
	recordtype a[100];
	int n ;
	
	printf("---Selection Sort---\n");
	read_file(a, &n);
	
	printf("* Truoc khi sap xep:\n");
	print_data(a, n);
	
	selection_sort(a, n);
	
	printf("* Sau khi sap xep:\n");
	print_data(a, n);
	
	return 0;
}
