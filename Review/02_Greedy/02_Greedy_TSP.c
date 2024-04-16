#include <stdio.h>

typedef struct {
	int dau, cuoi;
	float do_dai;
} Canh;

void ReadFromFile(Canh *a, int *n){
	FILE *f = fopen("data_TSP.txt", "r");
	if(f == NULL) {
		printf("error!!!\n");
		return;
	}

	fscanf(f, "%d", n);
	int i, j, k = 0;
	for(i = 1; i <= *n; i++){
		for(j = 1; j <= *n; j++){
			float tmp;
			fscanf(f, "%f", &tmp);
			if(j > i){
				a[k].dau = i;
				a[k].cuoi = j;
				a[k].do_dai = tmp;
				k++;
			}
		}
	}

	fclose(f);
}

void sort(Canh *a, int m){
	int i, j;
	for(i = 0; i < m - 1; i++){
		for(j = m - 1; j > i; j--){
			if(a[j].do_dai < a[j - 1].do_dai){
				Canh tmp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = tmp;
			}
		}
	}
}


int dinhCapBa(Canh PA[], int k, Canh moi){
	int i = 0, dem = 1;
	for(i = 0; i < k; i++){
		if(moi.dau == PA[i].dau || moi.dau == PA[i].cuoi) dem++;
		if(dem == 3) return 1;
	}

	dem = 1;
	for(i = 0; i < k; i++){
		if(moi.cuoi == PA[i].dau || moi.cuoi == PA[i].cuoi) dem++;
		if(dem == 3) return 1;
	}

	return 0;
}

void initForest(int *p, int n){
	int i;
	for(i = 0; i < n; i++){
		p[i] = i;
	}
}


int findRoot(int *p, int u){
	if(p[u] == u) return u;
	return findRoot(p, p[u]);
}

int chuTrinh(int r1, int r2){
	return r1 == r2;
}

void updateForest(int *p, int r1, int r2){
	p[r2] = r1;
}

void Greedy_TSP(Canh *a, int n, Canh *PA){
	int i, k = 0;
	int p[n];
	initForest(p, n);

	for(i = 0; i < n * (n - 1) / 2 && k < n - 1; i++){
		int r_dau = findRoot(p, a[i].dau);
		int r_cuoi = findRoot(p, a[i].cuoi);

		if(!dinhCapBa(PA, k, a[i]) && !chuTrinh(r_dau, r_cuoi)){
			PA[k++] = a[i];
			updateForest(p, r_dau, r_cuoi);
		}
	}

	for(; i < n * (n - 1) / 2; i++){
		int r_dau = findRoot(p, a[i].dau);
		int r_cuoi = findRoot(p, a[i].cuoi);

		if(!dinhCapBa(PA, k, a[i]) && chuTrinh(r_dau, r_cuoi)){
			PA[k++] = a[i];
			updateForest(p, r_dau, r_cuoi);
			break;
		}
	}
}


int main(){
	Canh a[100];
	int n;
	ReadFromFile(a, &n);

	int i;
	printf("----------Danh Sach Canh Truoc Khi Sap Xep----------\n");
	for(i = 0; i < n * (n - 1) / 2; i++){
		printf("(%d, %d): %.2f\n", a[i].dau, a[i].cuoi, a[i].do_dai);
	}

	sort(a, n * (n - 1) / 2);

	printf("----------Danh Sach Canh Sau Khi Sap Xep----------\n");
	for(i = 0; i < n * (n - 1) / 2; i++){
		printf("(%d, %d): %.2f\n", a[i].dau, a[i].cuoi, a[i].do_dai);
	}

	Canh PA[n - 1];

	Greedy_TSP(a, n, PA);

	printf("----------Danh Sach Phuong An----------\n");
	for(i = 0; i < n - 1; i++){
		printf("(%d, %d): %.2f\n", PA[i].dau, PA[i].cuoi, PA[i].do_dai);
	}

	return 0;
}