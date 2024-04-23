#include <stdio.h>
#define size 30

typedef struct {
	float do_dai;
	int dau, cuoi;
	int da_dung;
} canh;

void ReadFromFile(canh a[][size], int *n){
	int i, j;
	FILE *f = fopen("data_TSP.txt", "r");
	if(f == NULL){
		printf("Error\n");
		return;
	}
	
	fscanf(f, "%d", n);
	
	for(i = 0; i < *n; i++){
		for(j = 0; j < *n; j++){
			fscanf(f, "%f", &a[i][j].do_dai);
			a[i][j].dau = i;
			a[i][j].cuoi = j;
			a[i][j].da_dung = 0;
		}
	}

	fclose(f);
}

float canh_NN(canh a[][size], int n){
	float Cmin = 3.40282e+38;
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(i != j && !a[i][j].da_dung && a[i][j].do_dai < Cmin){
				Cmin = a[i][j].do_dai;
			}
		}
	}
	return Cmin;
}

float can_duoi(canh a[][size], float TGT, int n, int i){
	return TGT + (n - i) * canh_NN(a, n);
}

void Cap_Nhat_PA_TNTT(canh a[][size], int n, float TGT, float *GNNTT, canh x[], canh PA[]){
	int i;
	x[n - 1] = a[x[n - 2].cuoi][x[0].dau];
	TGT += x[n - 1].do_dai;
	if(*GNNTT > TGT){
		*GNNTT = TGT;		
		for(i = 0; i < n; i++){
			PA[i] = x[i];
		}
	}
}

int co_chu_trinh(canh x[], int k, int ke_tiep){
	int i = 0, co_CT = 0;
	while(i < k && !co_CT){
		if(ke_tiep == x[i].dau) co_CT = 1;
		else i++;
	}
	return co_CT;
}


void Nhanh_Can(canh a[][size], int n, int i, int dau, float *TGT, float *CD, float *GNNTT, canh x[], canh PA[]){
	int j;
	for(j = 0; j < n; j++){
		if(dau != j && !a[dau][j].da_dung && !co_chu_trinh(x, i, j)) {

			*TGT += a[dau][j].do_dai;
			*CD = can_duoi(a, *TGT, n, i + 1);

			if(*CD < *GNNTT){

				x[i] = a[dau][j];
				a[dau][j].da_dung = 1;
				a[j][dau].da_dung = 1;
				
				if(i == n - 2) Cap_Nhat_PA_TNTT(a, n, *TGT, GNNTT, x, PA);
				else Nhanh_Can(a, n, i + 1, j, TGT, CD, GNNTT, x, PA);	
			}

			*TGT -= a[dau][j].do_dai;
			a[dau][j].da_dung = 0;
			a[j][dau].da_dung = 0;
		}
	}	
}

void in_PA(canh PA[], int n){
	int i;
	float sum = 0;
	printf("----------Phuong An Tim Duoc La----------\n");
	for(i = 0; i < n; i++){
		sum += PA[i].do_dai;
		printf("Canh %c%c = %5.2f\n", PA[i].dau + 97, PA[i].cuoi + 97, PA[i].do_dai);
	}
	printf("Chu Trinh: ");
	for(i = 0; i < n; i++){
		printf("%c -> ", PA[i].dau + 97);
	}
	printf("%c", PA[0].dau + 97);
	printf("\nTong Do Dai: %.2f", sum);
}

int main(){
	
	canh a[size][size];
	int n;
	ReadFromFile(a, &n);
	
	int i, j;
	printf("----------Ma tran TSP---------\n");
	printf("%d\n", n);
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%.2f ", a[i][j].do_dai);
		}
		printf("\n");
	}
	
	canh PA[n];
	canh x[n];
	char tpxp;
	
	float TGT = 0, CD = 0, GNNTT = 3.40282e+38;
	printf("Chon thanh pho xuat phat: ");
	scanf("%c", &tpxp);
	Nhanh_Can(a, n, 0, tpxp - 97, &TGT, &CD, &GNNTT, x, PA);
	in_PA(PA, n);
	
	return 0;
}
