#include <stdio.h>

typedef struct {
	char tenDV[50];
	float TL, GT, DG;
	int SL, PA;
} DoVat;

void ReadFromFile(DoVat *dsdv, float *W, int *n){
	FILE *f = fopen("data_Balo2.txt", "r");
	if(f == NULL){
		printf("error!!!");
		return;
	}
	fscanf(f, "%f", W);
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].tenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
	}

	fclose(f);
	*n = i;
}

void sort(DoVat *dsdv, int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = n -1; j > i; j--){
			if(dsdv[j].DG > dsdv[j - 1].DG){
				DoVat tmp = dsdv[j];
				dsdv[j] = dsdv[j - 1];
				dsdv[j - 1] = tmp;
			}
		}
	}
}

void Greedy_Balo1(DoVat *dsdv, int n, float W){
	int i;
	for(i = 0; i < n; i++){
		dsdv[i].PA = ((W / dsdv[i].TL) < dsdv[i].SL) ? (W / dsdv[i].TL) : dsdv[i].SL;
		W -= dsdv[i].PA * dsdv[i].TL;
	}
}


int main(){

	DoVat dsdv[50];
	int n;
	float W;
	ReadFromFile(dsdv, &W, &n);

	int i;
	printf("----------Danh Sach Do Vat Truoc Khi Sap Xep----------\n");
	printf(" Ten Do Vat          TL    GT     DG      SL\n");
	for(i = 0; i < n; i++){
		printf("%-20s %5.2f %5.2f %5.2f %5d\n", dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL);
	}

	sort(dsdv, n);

	printf("----------Danh Sach Do Vat Sau Khi Sap Xep----------\n");
	printf(" Ten Do Vat          TL    GT     DG      SL\n");
	for(i = 0; i < n; i++){
		printf("%-20s %5.2f %5.2f %5.2f %5d\n", dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL);
	}

	Greedy_Balo1(dsdv, n, W);

	printf("----------Phuong An----------\n");
	printf("W: %.2f\n", W);
	printf(" Ten Do Vat          TL    GT     DG      SL     PA\n");
	for(i = 0; i < n; i++){
		printf("%-20s %5.2f %5.2f %5.2f %5d %5d\n", dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL, dsdv[i].PA);
	}

	printf("\nPhuong an: (%d", dsdv[0].PA);
	float sum_TL = dsdv[0].PA * dsdv[0].TL;
	float sum_GT = dsdv[0].PA * dsdv[0].GT;
	for(i = 1; i < n; i++){
		printf(", %d", dsdv[i].PA);
		sum_TL += dsdv[i].PA * dsdv[i].TL;
		sum_GT += dsdv[i].PA * dsdv[i].GT;
	}
	printf(")\n");
	printf("Tong TL: %.2f\nTong GT: %.2f", sum_TL, sum_GT);


	return 0;
}