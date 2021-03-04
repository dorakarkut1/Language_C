#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

struct client
{
    char name[20];
    char surname[40];
    int id;
    int account_balance;
};


int menu();
struct client find_account(int id);
void display(int id);
void create_account();
void view_details();
int edit_account();
void delete_account();
int transactions();
void view_list();
FILE * open_file(char mode[2]);
int random(int lower, int upper);

int main(){
	
	
   	int choice = 1;
   	while (choice != 0) {
	   choice = menu();
	   }
	
	return 0;
}


int menu(){
	int choice;
	printf(
	"1. Create an account\n"
	"2. View details of account\n"
	"3. Edit account information\n"
	"4. Delete an account\n"
	"5. Make a transfer\n"
	"6. View list of accounts\n"
	"0. Exit\n"
	"What is your decision?\n"
	);
	
	scanf("%d", &choice);
	switch (choice){
		case 1:
		create_account();
		break;	
		case 2:
		view_details();
		break;
		case 3:
		edit_account();
		break;
		case 4:
		delete_account();
		break;
		case 5:
		transactions();
		break;
		case 6:
		view_list();
		break;
	}
	return choice;
}

FILE* open_file(char mode[2]){
	FILE *ptr;
	if (mode == "w")
		ptr = fopen("Bank_info_copy.txt",mode);
	else
		ptr = fopen("Bank_info.txt",mode);
	if(ptr == NULL)
   		{
      		printf("Error!");   
      		exit(1);             
   		}
   	return ptr;


}

void create_account(){
	FILE *ptr;
	struct client new;
	int id_int;
	printf("Enter informations\n");
	printf("Name: ");
	scanf("%s", &new.name);
	printf("Surname: ");
	scanf("%s", &new.surname);
	printf("Account balance: ");
	scanf("%d", &new.account_balance);
	printf(
	"Is this information correct?\n"
	"Name: %s\n"
	"Surname: %s\n"
	"Account balance %d\n", new.name, new.surname, new.account_balance
	);
	srand(time(0));
	new.id = random(100000,999999);
	printf("Your account number is: %d\n", new.id);
	ptr = open_file("a+");
	fprintf(ptr, "%d ", new.id);
	fprintf(ptr, "%s ", new.name);
	fprintf(ptr, "%s ", new.surname);
	fprintf(ptr, "%d\n", new.account_balance);
	fclose(ptr);
}


void view_details(){
    
	int id;
	char str[MAXCHAR];
	char copy[6];
	char id_str[5];
	FILE *ptr;
	ptr = open_file("r");
	printf("Enter your account number: \n");
	scanf("%d", &id);

	itoa(id, id_str, 10);
	while( fgets(str, MAXCHAR, ptr)){
		memcpy(copy, str, 6);
		if (!strcmp(copy,id_str)) printf("%s", str);		
	}
	fclose(ptr);
};
	

int edit_account(){
	
	
	FILE *ptr2;
	FILE *ptr;
	ptr2 = open_file("w");
	ptr = open_file("r");
    char new_value[40];
    char new_record[100] = "";
	int id,choice,i=0;
	char str[MAXCHAR];
	char copy[6];
	char id_str[5];
	const char* delim[4];
	char * p;
	printf("Enter your account number: \n");
	scanf("%d", &id);
	printf("What do you want to change? Enter your choice and new value. \n1-name\n2-surname\n");
	scanf("%d %s", &choice, &new_value);
	itoa(id, id_str, 10);
	while ( fgets(str, MAXCHAR, ptr)){
		memcpy(copy, str, 6);

		if (!strcmp(copy,id_str)) {
			p = strtok( str, " ,.-" );
			delim[0] = p;
		    while (p != NULL)
		    {
		        delim[i] = p;
				p = strtok( NULL, " ,.-" );
		        i++;
		    }
			
			switch (choice){
				case 1:
					strcat(new_record, delim[0]);
					strcat(new_record, " ");
					strcat(new_record, new_value);
					strcat(new_record, " ");
					strcat(new_record, delim[2]);
					strcat(new_record, " ");
					strcat(new_record, delim[3]);
					break;
				case 2:
					strcat(new_record, delim[0]);
					strcat(new_record, " ");
					strcat(new_record, delim[1]);
					strcat(new_record, " ");
					strcat(new_record, new_value);
					strcat(new_record, " ");
					strcat(new_record, delim[3]);
					break;		
				}
				
			
			fprintf(ptr2, "%s", new_record);
		}
		else{
			fprintf(ptr2, "%s", str);
			}

	}

	fclose(ptr2);
	fclose(ptr);

	
	if (remove("Bank_info.txt") == 0) 
    	printf("Confirmed\n"); 
    else
        printf("Error\n"); 
    
    rename("Bank_info_copy.txt","Bank_info.txt");
    
	return 0;
};
void delete_account(){
	FILE *ptr2;
	FILE *ptr;
	ptr2 = open_file("w");
	ptr = open_file("r");

	int id;
	char str[MAXCHAR];
	char copy[6];
	char id_str[5];
	printf("Enter your account number: \n");
	scanf("%d", &id);
	itoa(id, id_str, 10);
	while ( fgets(str, MAXCHAR, ptr)){
		memcpy(copy, str, 6);

		if (!strcmp(copy,id_str)) {
		}
		else{
			fprintf(ptr2, "%s", str);
			}

	}
	fclose(ptr2);
	fclose(ptr);

	
	if (remove("Bank_info.txt") == 0) 
    	printf("Confirmed\n"); 
    else
        printf("Error\n"); 
    
    rename("Bank_info_copy.txt","Bank_info.txt");
    

};
int transactions(){
	FILE *ptr2;
	FILE *ptr;
	ptr2 = open_file("w");
	ptr = open_file("r");
    char new_value[40];
    char new_record2[100] = "";
    char new_record[100] = "";
	int id1,id2,money,balance1, balance2,i=0;
	char str[MAXCHAR];
	char copy[6];
	char id1_str[5], id2_str[5];
	char* delim[4],* delim2[4], * p, *p2;
	printf("From: \n");
	scanf("%d", &id1);
	printf("To: \n");
	scanf("%d", &id2);
	printf("How much? ");
	scanf("%d", &money);
	itoa(id1, id1_str, 10);
	itoa(id2, id2_str, 10);
	while ( fgets(str, MAXCHAR, ptr)){
		memcpy(copy, str, 6);
		if (!strcmp(copy,id1_str)) {
			p = strtok( str, " ,.-" );
			delim[0] = p;
		    while (p != NULL)
		    {
		        delim[i] = p;
				p = strtok( NULL, " ,.-" );
		        i++;
		    }
		    balance1 = atoi(delim[3]);
		    if (balance1 > money) {
		    		balance1 = balance1-money;
		    		itoa(balance1, delim[3], 10);
					strcat(new_record, delim[0]);
					strcat(new_record, " ");
					strcat(new_record, delim[1]);
					strcat(new_record, " ");
					strcat(new_record, delim[2]);
					strcat(new_record, " ");
					strcat(new_record, delim[3]);
					fprintf(ptr2, "%s\n", new_record);
				}
			else {
				printf("You dont have enough money!");
				exit(0);
				}		
	    	}
		else{
			fprintf(ptr2, "%s", str);
			}

		}
	
	fclose(ptr2);
	fclose(ptr);
	
	if (remove("Bank_info.txt") == 0) 
    	printf("Confirmed\n"); 
    else
        printf("Error\n"); 
    
    rename("Bank_info_copy.txt","Bank_info.txt");
	
	FILE *ptr4;
	FILE *ptr3;
	ptr4 = open_file("w");
	ptr3 = open_file("r");
	i=0;
	while ( fgets(str, MAXCHAR, ptr3)){
		memcpy(copy, str, 6);
		if (!strcmp(copy,id2_str)) {
			p2 = strtok( str, " ,.-" );
			delim2[0] = p2;
		    while (p2 != NULL)
		    {
		        delim2[i] = p2;
				p2 = strtok( NULL, " ,.-" );
		        i++;
		    }
		    
		    balance2 = atoi(delim2[3]);
		    printf("Dziala3");
		    balance2 = balance2 + money;
		    itoa(balance2, delim2[3] , 10);
		    printf("%s", delim2[3]);
			strcat(new_record2, delim2[0]);
			strcat(new_record2, " ");
			strcat(new_record2, delim2[1]);
			strcat(new_record2, " ");
			strcat(new_record2, delim2[2]);
			strcat(new_record2, " ");
			strcat(new_record2, delim2[3]);

			fprintf(ptr4, "%s\n", new_record2);
		}
		else {
			fprintf(ptr4, "%s", str);
			}

	}
	

	fclose(ptr4);
	fclose(ptr3);
	
	if (remove("Bank_info.txt") == 0) 
    	printf("Confirmed\n"); 
    else
        printf("Error\n"); 
    
    rename("Bank_info_copy.txt","Bank_info.txt");
    
	return 0;

};



void view_list(){
	char str[MAXCHAR];
	FILE *ptr;
	ptr = open_file("a+");
	while ( fgets(str, MAXCHAR, ptr) != NULL){
		printf("%s\n",str);
	}
	fclose(ptr);

};

int random(int lower, int upper) 
{ 
    int i; 
    int num = (rand() % (upper - lower + 1)) + lower; 
    return num; 
}




