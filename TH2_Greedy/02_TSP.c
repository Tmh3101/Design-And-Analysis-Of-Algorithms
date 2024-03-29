#include <stdio.h>

typedef struct {
	int dau, cuoi;
	float do_dai;
} Canh;

void ReadFromFile(Canh a[], int *n){
	FILE *file;
	file = fopen("TSP.txt", "r");
	if(file == NULL){
		printf("Loi mo file");
		return;
	}

	fscanf(file, "%d", n);
	int i, j, k = 0;
	for(i = 1; i <= *n; i++){
		for(j = 1; j <= *n; j++){
			float do_dai;
			fscanf(file, "%f", &do_dai);
			if(j > i){
				a[k].do_dai = do_dai;
				a[k].dau = i;
				a[k++].cuoi = j;
			}
		}
	}

	fclose(file);
}

void bubbleSort(Canh a[], int n){
	int i, j;
	for(i = 0; i < n - 1; i++){
		for(j = n - 1; j > i; j--){
			if(a[j].do_dai < a[j - 1].do_dai){
				Canh tmp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = tmp;
			}
		}
	}
}

int dinhCapBa(Canh PA[], int k, Canh moi){
	int i, dem = 1;
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

void init_forest(int parent[], int n){
	int i;
	for(i = 1; i <= n; i++){
		parent[i] = i;
	}
}

int find_root(int parent[], int u){
	if(parent[u] == u) return u;
	return find_root(parent, parent[u]);
}

int chu_trinh(int r1, int r2){
	return r1 == r2;
}

void update_forest(int parent[], int r1, int r2){
	parent[r2] = r1;
}

void TSP_Greedy(Canh a[], int n, Canh PA[]){
	int i, j = 0, r_dau, r_cuoi;
	int parent[n];
	init_forest(parent, n);

	for(i = 0; i < n * (n - 1) / 2 && j < n - 1; i++){
		r_dau = find_root(parent, a[i].dau);
		r_cuoi = find_root(parent, a[i].cuoi);

		if(!dinhCapBa(PA, j, a[i]) && !chu_trinh(r_dau, r_cuoi)){

			PA[j++] = a[i];
			update_forest(parent, r_dau, r_cuoi);

		}
	}

	for(; i < n * (n - 1) / 2; i++){
		r_dau = find_root(parent, a[i].dau);
		r_cuoi = find_root(parent, a[i].cuoi);
		if(!dinhCapBa(PA, j, a[i]) && chu_trinh(r_dau, r_cuoi)){
			PA[j++] = a[i];
			update_forest(parent, r_dau, r_cuoi);
			break;
		}
	}
}

int main(){
	Canh a[100];
	int n;
	ReadFromFile(a, &n);

	int i;
	printf("----------Danh Sach Truoc Khi Sap Xep--------\n");
	for(i = 0; i < n * (n - 1) / 2; i++){
		printf("(%d, %d): %.2f\n", a[i].dau, a[i].cuoi, a[i].do_dai);
	}

	bubbleSort(a, n * (n - 1) / 2);
	printf("----------Danh Sach Sau Khi Sap Xep--------\n");
	for(i = 0; i < n * (n - 1) / 2; i++){
		printf("(%d, %d): %.2f\n", a[i].dau, a[i].cuoi, a[i].do_dai);
	}

	Canh PA[100];

	TSP_Greedy(a, n, PA);
	printf("---------Danh Sach Phuong An---------\n");
	for(i = 0; i < n - 1; i++){
		printf("(%d, %d): %.2f\n", PA[i].dau, PA[i].cuoi, PA[i].do_dai);
	}

	return 0;
}