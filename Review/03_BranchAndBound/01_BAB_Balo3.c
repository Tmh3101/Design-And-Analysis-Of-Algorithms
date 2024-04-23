#include <stdio.h>

typedef struct {
	char tenDV[50];
	float TL, GT, DG;
	int PA;
} DoVat;

void ReadFromFile(DoVat *dsdv, int *n, float *W){
	FILE *f = fopen("data_Balo1.txt", "r");
	if(f == NULL) {
		printf("error!!!");
		return;
	}

	fscanf(f, "%f", W);

	int i = 0;
	while(!feof(f)){
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
	}

	fclose(f);
	*n = i;
}

void sort(DoVat *dsdv, int n){
	int i, j;
	for(i = 0; i < n - 1; i++){
		for(j = n - 1; j > i; j--){
			if(dsdv[j].DG > dsdv[j - 1].DG){
				DoVat tmp = dsdv[j];
				dsdv[j] = dsdv[j - 1];
				dsdv[j - 1] = tmp;
			}
		}
	}
}

void CreateRootNode(float W, float *V, float *TGT, float *CT, float *GLNTT, float DG_Max){
	*V = W;
	*TGT = 0;
	*CT = *V * DG_Max;
	*GLNTT = 0;
}

void UpdateGLNTT(DoVat *dsdv, int n, int *x, float TGT, float *GLNTT) {
	if(TGT > *GLNTT){
		*GLNTT = TGT;
		int i;
		for(i = 0; i < n; i++){
			dsdv[i].PA = x[i];
		} 
	}
}

void BranchAndBound(DoVat *dsdv, int n, int i, float *V, float *TGT, float *CT, float *GLNTT, int *x){
	int yk = ((*V / dsdv[i].TL) < 1) ? (*V / dsdv[i].TL) : 1; // so vat i lon nhat co the cho vao balo
	int j;
	for(j = yk; j >= 0; j--){

		//tinh lai cac gia tr
		*V -= j * dsdv[i].TL;
		*TGT += j * dsdv[i].GT;
		*CT = *TGT + *V * dsdv[i + 1].DG;

		// trường hợp đi tiếp
		if(*CT > *GLNTT){
			x[i] = j;
			if(i == n - 1 || *V == 0) UpdateGLNTT(dsdv, n, x, *TGT, GLNTT);
			else BranchAndBound(dsdv, n, i + 1, V, TGT, CT, GLNTT, x);
		} // trường hợp cắt tỉa

		//quay lui
		*V += j * dsdv[i].TL;
		*TGT -= j * dsdv[i].GT;
		x[i] = 0;
	}
}




int main(){

	DoVat dsdv[50];
	int n;
	float W;

	ReadFromFile(dsdv, &n, &W);

	int i;
	printf("----------Danh Sach Do Vat Truoc Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%5.2f %5.2f %5.2f %-20s\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].tenDV);
	}
	printf("\n");

	sort(dsdv, n);

	printf("----------Danh Sach Do Vat Sau Khi Sap Xep----------\n");
	for(i = 0; i < n; i++){
		printf("%5.2f %5.2f %5.2f %-20s\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].tenDV);
	}

	float CT, TGT, V, GLNTT; //cận trên, tổng giá trị, trọng lượng còn lại của balo, giá lớn nhất tạm thời 
	int x[n]; //lưu PA tạm thời

	CreateRootNode(W, &V, &TGT, &CT, &GLNTT, dsdv[0].DG);
	BranchAndBound(dsdv, n, 0, &V, &TGT, &CT, &GLNTT, x);

	printf("----------Danh Sach Phuong An----------\n");
	for(i = 0; i < n; i++){
		printf("%5.2f %5.2f %5.2f %-20s %5d\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].tenDV, dsdv[i].PA);
	}

	float sum_GT = dsdv[0].GT * dsdv[0].PA;
	float sum_TL = dsdv[0].TL * dsdv[0].PA;
	printf("W: %.2f\n", W);
	printf("--> Phuong An: (%d", dsdv[0].PA);

	for(i = 1; i < n; i++){
		printf(", %d", dsdv[i].PA);
		sum_GT += dsdv[i].GT * dsdv[i].PA;
		sum_TL += dsdv[i].TL * dsdv[i].PA;
	}

	printf(")\nTong Gia Tri: %.2f\nTong Trong Luong: %.2f\n", sum_GT, sum_TL);

	return 0;
}