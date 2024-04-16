#include <stdio.h>

typedef struct {
	int MG, PA;
	char tenTien[100];
} Tien;

void ReadFromFile(Tien *dslt, int *n){
	FILE *f = fopen("data_ATM.txt", "r");
	if(f == NULL){
		printf("error!!!\n");
		return;
	}

	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d %[^\n]", &dslt[i].MG, &dslt[i].tenTien);
		dslt[i].PA = 0;
		i++;
	}

	fclose(f);
	*n = i;
}

void sort(Tien *dslt, int n){
	int i, j;
	for(i = 0; i < n - 1; i++){
		for(j = n - 1; j > i; j--){
			if(dslt[j].MG > dslt[j - 1].MG){
				Tien tmp = dslt[j];
				dslt[j] = dslt[j - 1];
				dslt[j - 1] = tmp;
			}
		}
	}
}

void Greedy_ATM(Tien *dslt, int n, int soTienCanRut){
	int i;
	for(i = 0; i < n; i++){
		if(soTienCanRut < 1000) return;
		dslt[i].PA = soTienCanRut / dslt[i].MG;
		soTienCanRut -= dslt[i].PA * dslt[i].MG;
	}
}


int main(){
	Tien dslt[100];
	int n;
	ReadFromFile(dslt , &n);

	int i;
	printf("-----------Danh Sach Tien Truoc Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%6d %s\n", dslt[i].MG, dslt[i].tenTien);
	}

	sort(dslt, n);

	printf("-----------Danh Sach Tien Sau Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%6d %s\n", dslt[i].MG, dslt[i].tenTien);
	}

	printf("Nhap so tien can rut: ");
	int soTienCanRut;
	scanf("%d", &soTienCanRut);

	Greedy_ATM(dslt, n, soTienCanRut);

	printf("----------Phuong An Rut Tien----------\n");
	for(i = 0; i < n; i++){
		if(dslt[i].PA > 0) printf("%6d : %d to\n", dslt[i].MG, dslt[i].PA);
	}

	return 0;
}