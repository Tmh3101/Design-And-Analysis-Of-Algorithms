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

void BubbleSort(recordtype *a, int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = n - 1; j > i; j--){
			if(a[j].key < a[j - 1].key) swap(&a[j], &a[j - 1]);
		}
	}
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

	BubbleSort(a, n);

	printf("----------Danh Dach Sau Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}

	return 0;
}