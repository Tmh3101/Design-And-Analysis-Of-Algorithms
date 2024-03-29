#include <stdio.h>
#include <string.h>

typedef struct {
    char tenTien[50];
	int MG, PA;
} Tien;

void ReadFromFile(Tien dslt[], int *n){
    FILE *file;
    file = fopen("ATM.txt", "r");
    if (file == NULL) {
        printf("Không thể mở file.");
        return;
    }
    int i = 0;
    while (fscanf(file, "%d%[^\n]", &dslt[i].MG, dslt[i].tenTien) != EOF) {
        dslt[i].PA = 0;
        i++;
    }

    *n = i;
    fclose(file);
}

void swap(Tien *a, Tien *b){
    Tien tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(Tien dslt[], int n){
    int i, j;
    for(i = 0; i < n - 1; i++){
        for(j = n - 1; j > i; j--){
            if(dslt[j].MG > dslt[j - 1].MG)
                swap(&dslt[j], &dslt[j - 1]);
        }
    }
}

void ATM_Greedy(Tien dslt[], int n, int TienCanRut){
    
    if(TienCanRut < 1000){
        printf("So tien rut qua nho (phai lon hon 1000)");
        return;
    }

	int i;
	for(i = 0; i < n; i++){

		if(TienCanRut < dslt[i].MG) continue;
        if(TienCanRut <= 0) break;

		dslt[i].PA = TienCanRut / dslt[i].MG;
		TienCanRut %= dslt[i].MG;

	}
}


int main() {

    Tien dslt[100];
    int n, i;

    ReadFromFile(dslt, &n);

    printf("--------Danh Sach Truoc Khi Sap Xep--------\n");
    for(i = 0; i < n; i++){
        printf("%7d\t%-10s\n", dslt[i].MG, dslt[i].tenTien);
    }

    bubbleSort(dslt, n);

    printf("--------Danh Sach Truoc Khi Sap Xep--------\n");
    for(i = 0; i < n; i++){
        printf("%7d\t%-10s\n", dslt[i].MG, dslt[i].tenTien);
    }

    int TienCanRut;
    printf("Nhap so tien can rut: ");
    scanf("%d", &TienCanRut);

    ATM_Greedy(dslt, n, TienCanRut);

    printf("Phuong an rut tien:\n");
    for(i = 0; i < n; i++){
    	if(dslt[i].PA != 0) printf("MG: %7d\tSo to: %d\n", dslt[i].MG, dslt[i].PA);
    }

    return 0;
}



