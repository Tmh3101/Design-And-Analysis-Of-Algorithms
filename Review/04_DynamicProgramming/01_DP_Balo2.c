#include <stdio.h>

typedef struct {
	char tenDV[50];
	int TL, GT, SL, PA;
} DoVat;

typedef int Bang[50][100];

void ReadFromFile(DoVat *dsdv, int *n, int *W){
	FILE *f = fopen("data_Balo2.txt", "r");
	if(f == NULL) {
		printf("error!!!");
		return;
	}

	fscanf(f, "%d", W);

	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].tenDV);
		dsdv[i].PA = 0;
		i++;
	}

	*n = i;
}

void TaoBang(DoVat *dsdv, int n, int W, Bang X, Bang F){
	int V;
	for(V = 0; V <= W; V++){
		X[0][V] = ((V / dsdv[0].TL) < dsdv[0].SL) ? (V / dsdv[0].TL) : dsdv[0].SL;
		F[0][V] = X[0][V] * dsdv[0].GT;
	}

	int k;
	for(k = 1; k < n; k++){
		for(V = 0; V <= W; V++){

			int FMax = F[k - 1][V];
			int XMax = 0;

			int xk, yk = ((V / dsdv[k].TL) < dsdv[k].SL) ? (V / dsdv[k].TL) : dsdv[k].SL;
			for(xk = 0; xk <= yk; xk++){
				if(F[k - 1][V - xk * dsdv[k].TL] + xk * dsdv[k].GT > FMax){
					FMax = F[k - 1][V - xk * dsdv[k].TL] + xk * dsdv[k].GT;
					XMax = xk;
				}
			}

			F[k][V] = FMax;
			X[k][V] = XMax;
		}
	}
}

void TraBang(DoVat *dsdv, int n, int W, Bang X){
	int i;
	for(i = n - 1; i >= 0; i--){
		dsdv[i].PA = X[i][W];
		W -= dsdv[i].PA * dsdv[i].TL;
	}
}


int main(){

	DoVat dsdv[50];
	int n, W;

	ReadFromFile(dsdv, &n, &W);

	int i, j;
	printf("W: %d\n", W);
	printf("----------Danh Sach Do Vat----------\n");
	for(i = 0; i < n; i++){
		printf("%5d %5d %5d %s\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].tenDV);
	}

	Bang X, F;
	TaoBang(dsdv, n, W, X, F);

	printf("----------Tao Bang-----------\n");
	for(i = 0; i < n; i++){
		for(j = 0; j <= W; j++){
			printf("%2d|%-2d ", F[i][j], X[i][j]);
		}
		printf("\n");
	}

	TraBang(dsdv, n, W, X);
	printf("----------Tra Bang-----------\n");
	for(i = 0; i < n; i++){
		printf("%5d %5d %5d %-20s %d\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].tenDV, dsdv[i].PA);
	}

	int sum_TL = dsdv[0].PA * dsdv[0].TL;
	int sum_GT = dsdv[0].PA * dsdv[0].GT;
	printf("Phuong An: (%d", dsdv[0].PA);
	for(i = 1; i < n; i++){
		printf(", %d", dsdv[i].PA);
		sum_TL += dsdv[i].PA * dsdv[i].TL;
		sum_GT += dsdv[i].PA * dsdv[i].GT;
	}

	printf(")\nTong TL: %d\nTong GT: %d", sum_TL, sum_GT);

	return 0;
}