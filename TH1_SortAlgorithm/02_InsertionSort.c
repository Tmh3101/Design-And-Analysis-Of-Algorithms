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

void insertionSort(recordtype a[], int n){
	int i, j;
	for(i = 1; i < n; i++){
		j = i;
		while(j > 0 && a[j].key < a[j - 1].key){
			swap(&a[j], &a[j - 1]);
			j--;
		}
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

	insertionSort(a, n);

	int i;
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}
	
	return 0;
}