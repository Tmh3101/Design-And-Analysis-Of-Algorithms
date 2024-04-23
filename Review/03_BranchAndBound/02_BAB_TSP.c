#include <stdio.h>
#define size 10

typedef struct {
	float do_dai;
	int dau, cuoi, da_chon;
} Canh;

void ReadFromFile(Canh a[][size], int *n){
	FILE *f = fopen("data_TSP.txt", "r");
	if(f == NULL){
		printf("error!!!");
		return;
	}

	fscanf(f, "%d", n);

	int i, j;
	for(i = 0; i < *n; i++){
		for(j = 0; j < *n; j++){
			fscanf(f, "%f", &a[i][j].do_dai);
			a[i][j].dau = i;
			a[i][j].cuoi = j;
			a[i][j].da_chon = 0;
		}
	}

	fclose(f);
}


int hasCircle(Canh x[], int n, int dinh_ke_tiep){
	int i;
	for(i = 0; i < n; i++){
		if(dinh_ke_tiep == x[i].dau) return 1;
	}
	return 0;
}

float Canh_Min(Canh a[][size], int n){
	int i, j;
	float c_min = 999.9;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(i != j && !a[i][j].da_chon && a[i][j].do_dai < c_min)
				c_min = a[i][j].do_dai;
		}
	}
	return c_min;
}

void UpdateGNNTT(Canh a[][size], int n, float TGT, float *GNNTT, Canh x[], Canh PA[]){

	x[n - 1] = a[x[n - 2].cuoi][x[0].dau];
	TGT += x[n - 1].do_dai;

	if(TGT < *GNNTT){
		*GNNTT = TGT;
		int i;
		for(i = 0; i < n; i++){
			PA[i] = x[i];
		}
	}
}

void BranchAndBound(Canh a[][size], int n, int i, int dau, float *TGT, float *CD, float *GNNTT, Canh x[], Canh PA[]){
	int j;
	for(j = 0; j < n; j++){
		if(j != dau && !a[dau][j].da_chon && !hasCircle(x, i, j)){

			*TGT += a[dau][j].do_dai;
			*CD = *TGT + (n - (i + 1)) * Canh_Min(a, n);

			if(*CD < *GNNTT){
				x[i] = a[dau][j];
				a[dau][j].da_chon = 1;
				a[j][dau].da_chon = 1;

				if(i == n - 2) UpdateGNNTT(a, n, *TGT, GNNTT, x, PA);
				else BranchAndBound(a, n, i + 1, j, TGT, CD, GNNTT, x, PA);

			}

			*TGT -= a[dau][j].do_dai;
			a[dau][j].da_chon = 0;
			a[j][dau].da_chon = 0;
		}
	}
}


int main(){

	Canh a[size][size];
	int n;

	ReadFromFile(a, &n);

	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%-5.2f ", a[i][j].do_dai);
		}
		printf("\n");
	}

	float TGT = 0, CD = 0, GNNTT = 999.9;
	Canh x[n];
	Canh PA[n];

	BranchAndBound(a, n, 0, 0, &TGT, &CD, &GNNTT, x, PA);

	float sum_doDai = 0;
	for(i = 0; i < n; i++){
		printf("(%d, %d): %-5.2f\n", PA[i].dau, PA[i].cuoi, PA[i].do_dai);
		sum_doDai += PA[i].do_dai;
	}

	printf("Tong do dai: %-5.2f", sum_doDai);

	return 0;
}
