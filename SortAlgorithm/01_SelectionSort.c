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

void selectionSort(recordtype a[], int n){
	int i, j;
	for(i = 0; i < n - 1; i++){
		int min_index = i;
		int min_key = a[i].key;
		for(j = i + 1; j < n; j++){
			if(a[j].key < min_key) {
				min_index = j;
				min_key = a[j].key;
			}
		}
		swap(&a[i], &a[min_index]);
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

	selectionSort(a, n);

	int i;
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}
	
	return 0;
}