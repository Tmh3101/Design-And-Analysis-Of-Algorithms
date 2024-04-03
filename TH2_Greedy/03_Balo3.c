#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char tenDV[20];
	float TL, GT, DG;
	int PA;
} DoVat;

DoVat* ReadFromFile(float *W, int *n){
	FILE *f = fopen("data_balo1.txt", "r");
	if(f == NULL){
		printf("error");
		return;
	}
	fscanf(f, "%f", W);
	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f)){
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
		dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat) * (i + 1));
	}
	*n = i - 1;
	fclose(f);
	return dsdv;
}

void swap(DoVat *dv1, DoVat *dv2){
	DoVat tmp = *dv1;
	*dv1 = *dv2;
	*dv2 = tmp;
}

void sort(DoVat *dsdv, int n){
	int i, j;
	for(i = 0; i < n - 1; i++){
		for(j = n - 1; j > i; j--){
			if(dsdv[j].DG > dsdv[j - 1].DG){
				swap(&dsdv[j], &dsdv[j - 1]);
			}
		}
	}
}

void greedy(DoVat *dsdv, int n, float W){
	int i;
	for(i = 0; i < n; i++){
		dsdv[i].PA = ((W / dsdv[i].TL) < 1) ? (W / dsdv[i].TL) : 1;
		W = W - (dsdv[i].PA * dsdv[i].TL);
	}
}
int main(){
	int n;
	float W;
	DoVat *dsdv = ReadFromFile(&W, &n);
	printf("%d %.2f\n", n, W);
	int i;
	printf("---------Danh Sach Do Vat Truoc Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%3d %-18s %5.2f %5.2f %5.2f\n", i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG);
	}
	printf("\n");
	
	sort(dsdv, n);
	printf("---------Danh Sach Do Vat Sau Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%d %-18s %5.2f %5.2f %5.2f\n", i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG);
	}
	printf("\n");
	
	greedy(dsdv, n, W);	
	printf("---------Phuong An----------\n");
	for(i = 0; i < n; i++){
		printf("%d %-18s %5.2f %5.2f %5.2f %d\n", i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
	}
	printf("\n");
	
	float tongGT = 0, tongTL = 0;
	printf("Danh Sach Phuong An (Theo thu tu DG giam dan): (");
	for(i = 0; i < n - 1; i++){
		printf("%d, ", dsdv[i].PA);
		tongGT += dsdv[i].GT * dsdv[i].PA;
		tongTL += dsdv[i].TL * dsdv[i].PA;
	}
	printf("%d)\n", dsdv[i].PA);
	tongGT += dsdv[i].GT * dsdv[i].PA;
	tongTL += dsdv[i].TL * dsdv[i].PA;
	
	printf("Tong TL: %.2f\n", tongTL);
	printf("Tong GT: %.2f\n", tongGT);
	

	return 0;
}
