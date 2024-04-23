#include <stdio.h>

typedef struct {
	char tenDV[50];
	int TL, GT, PA;
} DoVat;

typedef int Bang[50][100];

void ReadFromFile(DoVat *dsdv, int *n, int *W){
	FILE *f = fopen("data_Balo3.txt", "r");
	if(f == NULL) {
		printf("error!!!");
		return;
	}

	fscanf(f, "%d", W);

	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
		dsdv[i].PA = 0;
		i++;
	}

	fclose(f);
	*n = i;
}

void TaoBang(DoVat *dsdv, int n, int W, Bang X, Bang F){
	int V;

	for(V = 0; V <= W; V++){
		X[0][V] = ((V / dsdv[0].TL) < 1) ? (V / dsdv[0].TL) : 1;
		F[0][V] = X[0][V] * dsdv[0].GT;
	}

	int k, FMax, XMax, xk, yk;
	for(k = 1; k < n; k++){
		for(V = 0; V <= W; V++){
			
			FMax = F[k - 1][V];
			XMax = 0;

			yk = ((V / dsdv[k].TL) < 1) ? (V / dsdv[k].TL) : 1;
			for(xk = 1; xk <= yk; xk++){
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
	int k, V;
	V = W;
	for(k = n - 1; k >= 0; k--){
		dsdv[k].PA = X[k][V];
		V -= dsdv[k].PA * dsdv[k].TL;
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
		printf("%5d %5d %-20s\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].tenDV);
	}

	Bang X, F;
	TaoBang(dsdv, n, W, X, F);

	printf("----------Tao Bang----------\n");
	for(i = 0; i < n; i++){
		for(j = 0; j <= W; j++){
			printf("%2d|%-2d ", F[i][j], X[i][j]);
		}
		printf("\n");
	}


	printf("-----------Tra Bang----------\n");
	TraBang(dsdv, n, W, X);

	for(i = 0; i < n; i++){
		printf("%5d %5d %-20s %5d\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].tenDV, dsdv[i].PA);
	}

	int sum_TL = dsdv[0].PA * dsdv[0].TL;
	int sum_GT = dsdv[0].PA * dsdv[0].GT;

	printf("Phuong An: (%d", dsdv[0].PA);
	for(i = 1; i < n; i++){
		printf(", %d", dsdv[i].PA);
		sum_TL += dsdv[i].PA * dsdv[i].TL;
		sum_GT += dsdv[i].PA * dsdv[i].GT;
	}

	printf(")\nSum TL: %d\nSum GT: %d", sum_TL, sum_GT);
	



	return 0;
}