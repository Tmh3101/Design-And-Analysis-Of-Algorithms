#include <stdio.h>

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

int find_pivot(recordtype *a, int L, int R){
	keytype firstkey = a[L].key;
	int k = L + 1;

	while(k <= R && a[k].key == firstkey) k++;

	if(k > R) return -1;
	return (firstkey < a[k].key) ? k : L;
}

int partition(recordtype *a, int L, int R, int p){
	while(L <= R){

		while(a[L].key < p) L++;
		while(a[R].key >= p) R--;

		if(L < R) swap(&a[L], &a[R]);
	}
	return L;
}

void quick_sort(recordtype *a, int L, int R){
	int pivot_index = find_pivot(a, L, R);
	if(pivot_index == -1) return;

	keytype p = a[pivot_index].key;
	int k = partition(a, L, R, p);
	quick_sort(a, L, k - 1);
	quick_sort(a, k, R);
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
	
	printf("---Quick Sort---\n");
	read_file(a, &n);
	
	printf("* Truoc khi sap xep:\n");
	print_data(a, n);
	
	quick_sort(a, 0, n - 1);
	
	printf("* Sau khi sap xep:\n");
	print_data(a, n);
	
	return 0;
}
