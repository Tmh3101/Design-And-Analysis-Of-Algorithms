#include <stdio.h>
#define size 50

void ReadFromFile(int a[][size], int *n){
	FILE *f = fopen("data_TamGiacSo.txt", "r");
	if(f == NULL){
		printf("error!!!");
		return;
	}
	int i = 0, j;
	while(!feof(f)){
		for(j = 0; j <= i; j++){
			fscanf(f, "%d", &a[i][j]);
		}
		i++;
	}

	fclose(f);
	*n = i;
}

int CS_Max(int F[][size], int i, int j){
	if(j == 0) return (F[i - 1][0] > F[i - 1][1]) ? 0 : 1;
	if(j == i) return j - 1;
	if(j == i - 1) return (F[i - 1][j - 1] > F[i - 1][j]) ? j - 1 : j; 

	if(F[i - 1][j - 1] > F[i - 1][j] && F[i - 1][j - 1] > F[i - 1][j + 1]) return j - 1;
	if(F[i - 1][j] > F[i - 1][j - 1] && F[i - 1][j] > F[i - 1][j + 1]) return j;
	return j + 1;
}

void TaoBang(int a[][size], int n, int F[][size]){
	F[0][0] = a[0][0];
	F[1][0] = F[0][0] + a[1][0];
	F[1][1] = F[0][0] + a[1][1];

	int i, j;
	for(i = 2; i < n; i++){
		for(j = 0; j <= i; j++){
			int k = CS_Max(F, i, j);
			F[i][j] = F[i - 1][k] + a[i][j];
		}
	}
}

int CS_Max_DongCuoi(int F[], int n){
	int i, i_max = 0, max = F[0];
	for(i = 1; i < n; i++){
		if(F[i] > max){
			max = F[i];
			i_max = i;
		}
	}
	return i_max;
}

void TraBang(int a[][size], int n, int F[][size], int PA[]){
	int j = CS_Max_DongCuoi(F[n - 1], n);
	PA[n - 1] = a[n - 1][j];

	int i;
	for(i = n - 1; i >= 1; i--){
		j = CS_Max(F, i, j);
		PA[i - 1] = a[i - 1][j];
	}
}


int main(){
	int a[size][size];
	int n;

	ReadFromFile(a, &n);

	int i, j;

	printf("-----------Tam Giac So----------\n");
	for(i = 0; i < n; i++){
		for(j = 0; j <= i; j++){
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	int F[size][size];
	TaoBang(a, n, F);

	printf("-----------Tao Bang----------\n");
	for(i = 0; i < n; i++){
		for(j = 0; j <= i; j++){
			printf("%d ", F[i][j]);
		}
		printf("\n");
	}

	int PA[size];
	TraBang(a, n, F, PA);

	printf("-----------Phuong An-----------\n");
	int sum = PA[0];
	printf("%d", PA[0]);
	for(i = 1; i < n; i++){
		printf(" -> %d", PA[i]);
		sum += PA[i];
	}
	printf("\nTong: %d", sum);

	return 0;
}