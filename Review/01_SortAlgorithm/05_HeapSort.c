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

void pushDown(recordtype *a, int first, int last){
	int r = first;
	while(r <= (last - 1) / 2){
		int L = 2 * r + 1;
		int R = 2 * r + 2;

		if(L == last){
			if(a[r].key > a[L].key) swap(&a[r], &a[L]);
			r = L;
		}
		else if(a[r].key > a[L].key && a[L].key <= a[R].key){
			swap(&a[r], &a[L]);
			r = L;
		}
		else if(a[r].key > a[R].key && a[R].key < a[L].key){
			swap(&a[r], &a[R]);
			r = R;
		}
		else r =last;
	}
}

void HeapSort(recordtype *a, int n){
	int i;
	for(i = (n - 1) / 2; i >= 0; i--){
		pushDown(a, i, n - 1);
	}
	for(i = n - 1; i > 1; i--){
		swap(&a[0], &a[i]);
		pushDown(a, 0, i - 1);
	}
	swap(&a[0], &a[1]);
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

	HeapSort(a, n);

	printf("----------Danh Dach Sau Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}

	return 0;
}