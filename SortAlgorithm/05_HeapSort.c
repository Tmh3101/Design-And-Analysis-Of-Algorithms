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

void pushDown(recordtype a[], int first, int last){
	int r = first;
	while(r <= (last - 1) / 2){
		int L = 2 * r + 1;
		int R = 2 * r + 2;
		if(last == 2 * r + 1){ 		//r chi co con trai
			if(a[r].key < a[last].key) swap(&a[r], &a[last]);
			r = last;
		} else if(a[r].key > a[L].key && a[L].key <= a[R].key){
			swap(&a[r], &a[L]);
			r = L;
		} else if(a[r].key > a[R].key && a[L].key > a[R].key){
			swap(&a[r], &a[R]);
			r = R;
		} else r = last;
	}
}


void heapSort(recordtype a[], int n){
	int i;
	for(i = n - 2; i >= 0; i--){
		pushDown(a, i, n - 1);
	}
	for(i = n - 1; i >= 2; i--){
		swap(&a[0], &a[i]);
		pushDown(a, 0, i - 1);
	}
	swap(&a[0], &a[1]);
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

	heapSort(a, n);

	int i;
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}
	
	return 0;
}