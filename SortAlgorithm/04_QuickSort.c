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

int findPivot(recordtype a[], int L, int R){
	keytype firstkey = a[L].key;
	int k = L + 1;
	while(k <= R && firstkey == a[k].key) k++;
	if(k > R) return -1;
	if(a[k].key > firstkey) return k;
	return L;
}

int partition(recordtype a[], int L, int R, int p){
	while(L <= R) {
		while(a[L].key < p) L++;
		while(a[R].key >= p) R--;
		if(L < R) swap(&a[L], &a[R]);
	}
	return L;
}

void quickSort(recordtype a[], int L, int R){
	int pivotIndex = findPivot(a, L, R);
	if(pivotIndex != -1) {
		keytype p = a[pivotIndex].key;
		int k = partition(a, L, R, p);
		quickSort(a, L, k - 1);
		quickSort(a, k, R);
	} 
}

int main(){
	recordtype a[100];
	int n = 0;
	int key;
	float otherfields;

	freopen("data.txt", "r", stdin);
	do {
		key = INT_MIN;
		otherfields = FLT_MIN;
		scanf("%d%f", &key, &otherfields);
		if (key != INT_MIN && otherfields != FLT_MIN){
			a[n].key = key;
			a[n].otherfields = otherfields;
			n++;
		}
	} while (key != INT_MIN && otherfields != FLT_MIN);

	quickSort(a, 0, n - 1);

	int i;
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}
	
	return 0;
}