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

void push_down(recordtype *a, int first, int last){
	int r = first;
	while(r <= (last - 1) / 2){
		int L = 2 * r + 1;
		int R = 2 * r + 2;
		
		if(last == L){
			if(a[r].key > a[last].key) swap(&a[r], &a[last]);
			r = last;
		} 
		else if(a[r].key > a[L].key && a[L].key <= a[R].key){
			swap(&a[r], &a[L]);
			r = L;
		}
		else if(a[r].key > a[R].key && a[L].key > a[R].key){
			swap(&a[r], &a[R]);
			r = R;
		}
		else r = last;
		
	}
}

void heap_sort(recordtype *a, int n){
	int i;
	for(i = (n - 2) / 2; i >= 0; i--){
		push_down(a, i, n - 1);
	}
	for(i = n - 1; i >= 2; i--){
		swap(&a[0], &a[i]);
		push_down(a, 0, i - 1);
	}
	swap(&a[0], &a[1]);
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
	for(i = n - 1; i >= 0; i--){
		printf("%3d %5d  %8.2f\n", i, a[i].key, a[i].otherfields);
	}
}

int main(){
	recordtype a[100];
	int n ;
	
	printf("---Heap Sort---\n");
	read_file(a, &n);
	
	printf("* Truoc khi sap xep:\n");
	print_data(a, n);
	
	heap_sort(a, n);
	
	printf("* Sau khi sap xep:\n");
	print_data(a, n);
	
	return 0;
}
