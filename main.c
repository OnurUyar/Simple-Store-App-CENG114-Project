#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int x;

// Declaring functions before main function
void menu(void);
void pref(int data[][4], int choice);
void read(int data[][4], int *p1);
void sorter1(int data[][4]);
void sorter2(int data[][4]);
void updater(int data[][4], int *p1);
void updatefile(int data[][4]);
void cheap(int data[][4]);
void compare1(int data[][4]);
void compare2(int data[][4]);
void stock(int data[][4]);

int main(void){
	int data[100][4], a;
	
	printf("Welcome to the ABC Mobile Store App\n");
	
	do{
		menu();           // Displaying menu until user chooses to quit
		scanf("%d", &a);
		pref(data, a);
	} while (a != 10);

	return 0;
}

// Printing the Menu
void menu(void){
	printf("\n\n*-*-*-*-*-*-*-*-*-*-*- MENU -*-*-*-*-*-*-*-*-*-*-*");
	printf("\nPlease choose one:\n");
	printf("1. Load phone data from text file\n2. Order data based on phone quantity\n3. Update phone quantity for a store\n4. View ordered phone quantity of a store\n5. Find cheapest price of a phone type\n");
	printf("6. Compare two stores to find different phone types\n7. Compare two stores to find common phone types\n8. View total quantity of each phone type\n9. Update text file\n10. Quit\n");
	printf("\nYour Choice: ");
}

// Calling functions with Switch-Case
void pref(int data[][4], int choice){
	int counter = 0, i, j;

	switch (choice){
	case 1:
		read(data, &counter);
		x = counter;
		printf("Data is read from text file!");
		break;
	case 2:
		printf("Sorted array based on phone quantity:\n");
		printf("Store_ID    Phone_Type    Quantity    Price\n");
		sorter1(data);
		for (i = 0; i < x; i++){
			for (j = 0; j < 4; j++)
				printf("%d            ", data[i][j]);
			printf("\n");
		}
		break;
	case 3:
		updater(data, &x);
		printf("Updated!");
		break;
	case 4:
		sorter2(data);
		break;
	case 5:
		cheap(data);
		break;
	case 6:
		compare1(data);
		break;
	case 7:
		compare2(data);
		break;
	case 8:
		stock(data);
		break;
	case 9:;
		updatefile(data);
		printf("Text file updated!");
		break;
	case 10:
		printf("\n*-*-*-*-*-*-*-*-*-*-*- Goodbye -*-*-*-*-*-*-*-*-*-*-*");
		break;
	default:
		printf("Please choose from 1 to 10 only!");
	}
}

// Reading the data from phonedata.txt file
void read(int data[][4], int *p1){
	int i, j;

	FILE *fread;
	fread = fopen("phonedata.txt", "r");

	for (i = 0; !feof(fread); i++){
		for (j = 0; j < 4; j++){
			fscanf(fread, "%d", &data[i][j]);
		}
	}
	fclose(fread);
	*p1 = i;
}

// Sorting the data based on quantity
void sorter1(int data[][4]){
	int i, j, k, temp[4], min, minloc;

	for (i = 0; i < x; i++){
		min = data[i][2];
		minloc = i;

		for (j = i; j < x; j++){
			if (data[j][2] < min){
				min = data[j][2];
				minloc = j;
			}
		}

		if (min < data[i][2]){
			for (k = 0; k < 4; k++){
				temp[k] = data[i][k];
				data[i][k] = data[minloc][k];
				data[minloc][k] = temp[k];
			}
		}
	}
}

// Sorting the phone quantity and prices of a specific store
void sorter2(int data[][4]){
	int i, j, l, k = 0, tempa[100][4], tempx[4], max, maxloc, store;
	
	printf("Enter the store ID: ");
	scanf("%d", &store);
	
	for (i = 0; i < x; i++){
		if(data[i][0] == store){
			for(j = 0; j < 4; j++)
				tempa[k][j] = data[i][j];
			k++;
		}
	}
	
	for (i = 0; i < k; i++){
		max = tempa[i][2];
		maxloc = i;

		if (max > tempa[i+1][2]){
			for (l = 0; l < 4; l++){
				tempx[l] = tempa[i][l];
				tempa[i][l] = tempa[maxloc][l];
				tempa[maxloc][l] = tempx[l];
			}
		}
	}
	
	printf("Phone quantity and prices of the Store %d: \n\n", store);
	printf("Phone_Type    Quantity    Price\n");
	
	for (i = 0; i < k; i++){
		for (j = 1; j < 4; j++)
			printf("%d            ", tempa[i][j]);
		printf("\n");
	}
}

// Updating the phone quantity for a store
void updater(int data[][4], int *p1){
	int store, phone, quantity, i, j;

	printf("Enter the Store ID: ");
	scanf("%d", &store);
	printf("Enter the Phone Type: ");
	scanf("%d", &phone);

	printf("Enter the New Quantity: ");
	scanf("%d", &quantity);

	for (i = 0; i < (*p1); i++){
		if (data[i][0] == store && data[i][1] == phone)
			data[i][2] = quantity;
	}
}

// Updating the file
void updatefile(int data[][4]){
	FILE *fupdate;
	fupdate = fopen("phonedata.txt", "w");

	int i, j;

	for (i = 0; i < x; i++){
		for (j = 0; j < 4; j++){
			fprintf(fupdate, "%d ", data[i][j]);
		}
		fprintf(fupdate, "\n");
	}

	fclose(fupdate);
}

// Finding cheapest phone type
void cheap(int data[][4]){
	int type, i, cheapest, price, tmp = 0;

    printf("Enter phone type: ");
    scanf("%d", &type);

	price = data[0][3];
	cheapest = 0;

	for (i = 1; i < x; i++){
        if (data[i][1] == type){
            if (data[i][3] < price){
                price = data[i][3];
                cheapest = i;
            }
        }
    }
    printf("Cheapest Phone %d is at the Store %d (It's price: %d)", type, data[cheapest][0], price);
}

// Comparing two store to find different phone types
void compare1(int data[][4]){
	int a1[100], a2[100], id1, id2, i, j, k, l;

    printf("Enter the ID of store 1: ");
    scanf("%d", &id1);

 	printf("Enter the ID of store 2: ");
    scanf("%d", &id2);

	for (i = 0, j = 0, k = 0; i < x; i++){
        
		if (data[i][0] == id1){
            a1[j] = data[i][1];
            j++;
        }
        
        if (data[i][0] == id2){
            a2[k] = data[i][1];
            k++;
        }
    }
    for (i = 0; i < j; i++){
        for (l = 0; l < k; l++){
            if (a1[i] == a2[l])
           		 a1[i] = -1;
        }
    }

	printf("Phone types available in store 1 and not in store 2: ");
    for (i = 0; i < j; i++){
        if (a1[i] > 0)
            printf("%d ", a1[i]);
    }
}

// Comparing two stores to find common phone types
void compare2(int data[][4]){
	int b1[100], b2[100], id1, id2, i, j, k, l;

    printf("Enter the ID of store 1: ");
    scanf("%d", &id1);

 	printf("Enter the ID of store 2: ");
    scanf("%d", &id2);
    printf("Phone types available in store 1 and store 2: ");

	for (i = 0, j = 0, k = 0; i < x; i++){
        
		if (data[i][0] == id1){
            b1[j] = data[i][1];
            j++;
        }
        
        if (data[i][0] == id2){
            b2[k] = data[i][1];
            k++;
        }
    }
    for (i = 0; i < j; i++){
        for (l = 0; l < k; l++){
            if (b1[i] == b2[l])
           		 printf("%d ", b1[i]);
        }
    }
}

// Finding all phone stock on every store
void stock(int data[][4]){
	int i, j, s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0, s7 = 0, s8 = 0, type;
	
	for(i = 0; i < x ; i++){
		switch(data[i][1]){
			case 1:
				s1 += data[i][2];
				break;
			case 2:
				s2 += data[i][2];
				break;
			case 3:
				s3 += data[i][2];
				break;
			case 4:
				s4 += data[i][2];
				break;
			case 5:
				s5 += data[i][2];
				break;
			case 6:
				s6 += data[i][2];
				break;
			case 7:
				s7 += data[i][2];
				break;
			case 8:
				s8 += data[i][2];
				break;
		}
	}
	
	printf("Stock of Phone type 1 is: %d\n", s1);
	printf("Stock of Phone type 2 is: %d\n", s2);
	printf("Stock of Phone type 3 is: %d\n", s3);
	printf("Stock of Phone type 4 is: %d\n", s4);
	printf("Stock of Phone type 5 is: %d\n", s5);
	printf("Stock of Phone type 6 is: %d\n", s6);
	printf("Stock of Phone type 7 is: %d\n", s7);
	printf("Stock of Phone type 8 is: %d", s8);
}
