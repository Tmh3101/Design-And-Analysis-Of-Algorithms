#include <stdio.h>

typedef struct {
	int key;
	float otherfields;
} recordtype;

void ReadFromFile(recordtype *a, int *n){
	FILE *f = fopen("data.txt", "r");
	if(f == NULL){
		printf("error!!!\n");
		return;
	}

	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d %f", &a[i].key, &a[i].otherfields);
		i++;
	}

	fclose(f);
	*n = i;
}

void swap(recordtype *a, recordtype *b){
	recordtype tmp = *a;
	*a = *b;
	*b = tmp;
}

int findPivot(recordtype *a, int L, int R){
	int firstkey = a[L].key;
	int k = L + 1;
	while(k <= R && a[k].key == firstkey) k++;
	if(k > R) return -1;
	return (firstkey < a[k].key) ? k : L;
}

int partition(recordtype *a, int L, int R, int p){
	while(L <= R){
		while(a[L].key < p) L++;
		while(a[R].key >= p) R--;
		if(L < R){
			swap(&a[L], &a[R]);
		}
	}
	return L;
}

void QuickSort(recordtype *a, int L, int R){
	int v = findPivot(a, L, R);
	if(v == -1) return;
	int p = a[v].key;
	int k = partition(a, L, R, p);
	QuickSort(a, L, k - 1);
	QuickSort(a, k, R);
}

int main(){

	recordtype a[100];
	int n;

	ReadFromFile(a, &n);

	int i;

	printf("----------Danh Dach Truoc Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}

	QuickSort(a, 0, n - 1);

	printf("----------Danh Dach Sau Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}

	return 0;
}