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

void SelectionSort(recordtype *a, int n){
	int i, j;
	for(i = 0; i < n - 1; i++){
		int min_key = a[i].key;
		int index = i;
		for(j = i; j < n; j++){
			if(a[j].key < min_key){
				min_key = a[j].key;
				index = j;
			}
		}
		swap(&a[i], &a[index]);
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

	SelectionSort(a, n);

	printf("----------Danh Dach Sau Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%d %.2f\n", a[i].key, a[i].otherfields);
	}

	return 0;
}