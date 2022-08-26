#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void scanItems();
void mainMenu();
void addItems();
void allItems();
void binarySearch();
void searchItems();
void sortItems();
void merge();
void mergeSort();
void deleteItems();
void exit();

struct infoProduk {
	// ID, Nama, Jumlah, Tanggal Expired, Berat Produk
	char ID[100];
	char namaProduk[100];
	int jumlah;
	char expiredDate[100];
	double beratProduk;
	bool isDeleted = false;
};

struct infoProduk produk[500];
int totalProduk = 0;

int main(){
	system("color B");
	srand(time(0));
	scanItems();
	mainMenu();
	return 0;
}

void scanItems(){
	// scan semua barang yang ada di .txt 
	char ID[100]; 
	char namaProduk[100];
	int jumlah;
	char expiredDate[100];
	double beratProduk;
	
	FILE* infoProduk = fopen("infoProduk.txt", "r");
	while(fscanf(infoProduk, "%[^#]#%[^#]#%d#%[^#]#%lf\n", &ID, namaProduk, &jumlah, expiredDate, &beratProduk) != EOF){
		
	strcpy(produk[totalProduk].ID, ID);
	strcpy(produk[totalProduk].namaProduk, namaProduk);
	produk[totalProduk].jumlah = jumlah;
	strcpy(produk[totalProduk].expiredDate, expiredDate);
	produk[totalProduk].beratProduk = beratProduk;
	totalProduk++;;
	}
	
	fclose(infoProduk);
}

void mainMenu(){
	// nambahin barang, liat semua barang, cari barang, edit barang, apus barang, tutup
	char n;
	do{
	system("cls");
	printf("MAIN MENU\n");
	printf("\n\n");
	printf("1. Add Items\n");
	printf("2. All Items\n");
	printf("3. Search Items\n");
	printf("4. Sort Items\n");
	printf("5. Delete Items\n");
	printf("6. Exit\n\n");
	printf("Enter a number: ");
	
	scanf("%c", &n); getchar();
		switch(n){
		case '1':
			addItems(); getchar();
			break;
		case '2':
			allItems();  getchar();
			break;
		case '3':
			searchItems(); getchar();
			break;
		case '4':
			sortItems(); getchar();
			break;
		case '5':
			deleteItems(); getchar();
			break;	
		case '6':
			exit();
			break;
		default:
			system("cls");
			printf("Invalid Enter\n");
			getchar();
		}
	} while(n != '6');
}

void addItems(){
	// buat nambahin barang
	system("cls");
	char ID[100]; 
	float IDNum = rand()%((9999+1)-1000) + 1000;
	char namaProduk[100];
	int jumlah;
	char expiredDate[100];
	double beratProduk;
	
	printf("Name:\t");
	scanf("%[^\n]", namaProduk); getchar();
	
	printf("Total:\t");
	scanf("%d", &jumlah); getchar();
	
	printf("Expiration Date (DD-MM-YYYY):\t");
	scanf("%s", expiredDate); getchar();
	
	printf("Mass (kg):\t");
	scanf("%lf", &beratProduk); getchar(); 
	
	for(int i = 0; i < strlen(namaProduk) ; i++){
		if(namaProduk[i] >= 'A' && namaProduk[i] <= 'Z'){
			namaProduk[i] += 32;
		}
	}

	sprintf(ID, "%c%c-%.0f", namaProduk[0], namaProduk[1], IDNum);
	
	printf("\n");
	FILE *infoProduk = fopen("infoProduk.txt", "a+");
	fprintf(infoProduk, "%s#%s#%d#%s#%.1lf\n", ID, namaProduk, jumlah, expiredDate, beratProduk);
	fclose(infoProduk);
	
	strcpy(produk[totalProduk].ID, ID);
	strcpy(produk[totalProduk].namaProduk, namaProduk);
	produk[totalProduk].jumlah = jumlah;
	strcpy(produk[totalProduk].expiredDate, expiredDate);
	produk[totalProduk].beratProduk = beratProduk;
	totalProduk++;
	
	char confirmation;
	printf("Do you want to add more item? (Y/N)\t");
	scanf("%c", &confirmation); getchar();
	if(confirmation == 'y' || confirmation == 'Y'){
		addItems();
	}
	
	mainMenu();
}

void allItems(){
	// buat display semua barang
	system("cls");
	for(int i = 0; i < totalProduk; i++){
	printf("------------------------------------------\n");
		printf("ID              :%s\n", produk[i].ID);
		printf("Name            :%s\n", produk[i].namaProduk);
		printf("Total           :%d\n", produk[i].jumlah);
		printf("Expired date    :%s\n", produk[i].expiredDate);
		printf("Mass            :%lf\n", produk[i].beratProduk);
	printf("------------------------------------------\n\n\n");
	}
	printf("Press enter to go back."); 
	return;
}	

void merge(infoProduk arr[], long long int left, long long int mid, long long int right){
    long long int leftSize = mid - left + 1;
    long long int rightSize = (right - (mid+1))+1;
    infoProduk leftArr[leftSize], rightArr[rightSize];

    for(int i = 0; i < leftSize; i++){
        leftArr[i] = arr[left + i];
    }
    for(int i = 0; i < rightSize; i++){
        rightArr[i] = arr[mid + 1 + i];
    }
    int rightIdx = 0, leftIdx = 0, idx = left;

    while(rightIdx < rightSize && leftIdx < leftSize){
        if(strcmp(rightArr[rightIdx].namaProduk, leftArr[leftIdx].namaProduk)<0){
            arr[idx] = rightArr[rightIdx];
            rightIdx++;
            idx++;
        }else{
            arr[idx] = leftArr[leftIdx];
            leftIdx++;
            idx++;
        }
    }

    while(rightIdx < rightSize){
        arr[idx] = rightArr[rightIdx];
        rightIdx++;
        idx++;
    }

    while(leftIdx < leftSize){
        arr[idx] = leftArr[leftIdx];
        leftIdx++;
        idx++;
    }
}

void mergeSort(infoProduk arr[], long long int left, long long int right){
    if(left >= right) return;
    long long int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void binarySearch(infoProduk temp[], int leftIdx, int rightIdx, char input[]){
	while (leftIdx <= rightIdx){
		int middleIdx = leftIdx + (rightIdx - leftIdx) / 2;
		if(strcmp(temp[middleIdx].namaProduk, input) == 0){
            printf("------------------------------------------\n");
            printf("ID              :%s\n", temp[middleIdx].ID);
            printf("Name            :%s\n", temp[middleIdx].namaProduk);
            printf("Total           :%d\n", temp[middleIdx].jumlah);
            printf("Expired date    :%s\n", temp[middleIdx].expiredDate);
            printf("Mass            :%lf\n", temp[middleIdx].beratProduk);
            printf("------------------------------------------\n\n");
            return;
		}
		 else if (strcmp(temp[middleIdx].namaProduk, input) < 0) {
            leftIdx = middleIdx + 1;
        }
        else if (strcmp(temp[middleIdx].namaProduk, input) > 0) {
            rightIdx = middleIdx - 1;
        }
	}
	printf("-----Item Not found-----\n\n");
}

void searchItems(){
	//buat search item yang diinginkan
	system("cls");
	char input[100] = {};
	infoProduk temp[500];
	printf("Type the name that you want to search:\t");
	scanf("%[^\n]", input); getchar();
	printf("\n");
	for(int i = 0; i < totalProduk; i++){
        temp[i] = produk[i];
    }
    mergeSort(temp, 0, totalProduk-1);
	binarySearch(temp, 0, totalProduk-1, input);
	printf("Press enter to go back."); 
}

void sortItems(){
//	 buat sort stock barang
	system("cls");
	infoProduk temp[500];
	printf("Name\t\tTotal\n");
	printf("---------------------------\n");
	for(int i = 0; i < totalProduk; i++){
        temp[i] = produk[i];
    }
    mergeSort(temp, 0, totalProduk-1);
	for(int i = 0; i < totalProduk; i++){
		printf("%-15s:%d\n\n", temp[i].namaProduk, temp[i].jumlah);
	}
	printf("Press enter to go back."); 
	return;
}

void deleteItems(){
	// buat delete item
	system("cls");
	for(int i = 0; i < totalProduk; i++){
		printf("%s\n\n", produk[i].namaProduk);
	}
	char namaProduk[100];
	printf("Type the name that you want to remove:\t");
	scanf("%[^\n]", namaProduk); getchar();
	for(int i = 0; i < totalProduk; i++){
		if(!strcmp(namaProduk, produk[i].namaProduk)){	
			produk[i].isDeleted = true;
			printf("Product has been deleted, press enter to continue.\n");
			FILE *infoProduk = fopen("infoProduk.txt", "w");
			for(int j = 0; j < totalProduk; j++){
				if(produk[j].isDeleted == true){
					continue;
				}
				else {
					fprintf(infoProduk, "%s#%s#%d#%s#%.1lf\n", produk[j].ID, produk[j].namaProduk, produk[j].jumlah, produk[j].expiredDate, produk[j].beratProduk);
				}
			}
			totalProduk = 0;
			fclose(infoProduk);
			break;
		}	
	}
	totalProduk = 0;
    memset(produk, 0, sizeof(produk));
	scanItems();
}

void exit(){
	system("cls");
	printf("Shutting down system, press enter to exit\n"); getchar();
}
