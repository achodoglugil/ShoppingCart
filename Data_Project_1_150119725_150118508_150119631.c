//Data Structures Project 1
//Enes Sagiroglu 150119725
//Ahmet Cagri Hodoglugil 150118508
//Utku Bayguven 150119631

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Product{
	int id;
	char name[30];
	char category[30];
	int price;
	struct Product* next;
};
typedef struct Product Product;
Product *pbas = NULL;
Product *searchP = NULL;
Product *searchedP = NULL;
int Pid = 1;

void printProduct() {
   Product *ptr = pbas;
   printf("\n");
	if(ptr == NULL){
		printf("There are no products in Product list..\n");
	}
   
   while(ptr != NULL) {
      printf("Product id:%d\tName:%s\tCategory:%s\t\tPrice:$%d\n",ptr->id,ptr->name,ptr->category,ptr->price);
      ptr = ptr->next;
   }
	
}


int findIdP(int givenId) {
   searchP = pbas;
   
   if(pbas == NULL) {
   	  printf("There is no product..\n");
      return 1;
   }

   while(searchP->id != givenId) {

      if(searchP->next == NULL) {
      	 printf("Product not found..");
         return 1;
      } 
	  else {
         searchP = searchP->next;
      }
   }      
   return 0;
}


struct Basket{
	int id;
	int amount;
	struct Basket *next;
	Product *Productlist;
};
typedef struct Basket Basket;
int Bid = 1;


struct Customer{
	int id;
	char name[30];
	char surname[30];
	struct Customer *next;
	Basket *Basketlist;
};
typedef struct Customer Customer;
Customer *cbas = NULL;
Customer *searchC = NULL;
int Cid = 1;

int findIdC(int givenId) {
   searchC = cbas;
   
   if(cbas == NULL) {
   	  printf("There is no customer..\n");
      return 1;
   }

   while(searchC->id != givenId) {

      if(searchC->next == NULL) {
      	 printf("Customer not found..");
         return 1;
      } 
	  else {
         searchC = searchC->next;
      }
   }      
   return 0;
}


void addproduct(int idp,int idc){
	Product *tempp;
	
	findIdC(idc);//searchC
	findIdP(idp);//searchP
	
	if(searchC->Basketlist->Productlist == NULL){
		searchC->Basketlist->Productlist = searchP;
		return; 
	}
	tempp = searchC->Basketlist->Productlist;
	while(tempp->next != NULL){
		tempp = tempp->next;
	}
	tempp->next = searchP;
	
}

void addtobasket(){
	int idc,idp;
	printCustomer();
	printf("Please enter a customer id:");
	scanf("%d",&idc);
	createBasket(idc,0);
	findIdC(idc);
	printProduct();
	
	while(idp != -1){
		printf("(Enter -1 to quit)\n");
		printf("Please enter a product id:");
		scanf("%d",&idp);
		if(idp != -1){
			addproduct(idp,idc);
			searchC->Basketlist->amount += 1;
		}
	}
}
int createBasket(int givenId, int givenAmount){
	Basket *newB, *tempB;
	newB = (Basket*)malloc(sizeof(Basket));
	
	newB->id = Bid;
	newB->amount = givenAmount;
    newB->next = NULL;
    newB->Productlist =NULL;
	Bid++;
	
	findIdC(givenId);
	
	
	
	if(searchC->Basketlist == NULL){
		searchC->Basketlist = newB;
		Bid++;
		return; 
	}
	
	tempB = searchC->Basketlist;
	while(tempB->next != NULL){
		tempB = tempB->next;
	}
	tempB->next = newB;
	return Bid;
	
	
}

int addCustomer(char givenName[30], char givenSurname[30]){
	Customer *newC,*tempC;
	newC = (Customer*)malloc(sizeof(Customer));
	
	newC->id = Cid;
	strcpy(newC->name,givenName);
    strcpy(newC->surname,givenSurname);
    newC->next = NULL;
    newC->Basketlist = NULL;
	
	
	if(cbas == NULL){
		cbas = newC;
		Cid++;
		return; 
	}
	
	tempC = cbas;
	while(tempC->next != NULL){
		tempC = tempC->next;
	}
	tempC->next = newC;
	tempC = tempC->next;
	Cid++;
	return Cid;
}
Customer * deleteCustomer(int givenId) {

   
   Customer * current = cbas;
   Customer * previous = NULL;
	
   
   if(cbas == NULL) {
      return NULL;
   }
   while(current->id != givenId) {
      if(current->next == NULL) {
      	printf("Customer not found..\n");
        return NULL;
      } else {
        
        previous = current;
        current = current->next;
      }
   }
   if(current == cbas) {
    cbas = cbas->next;
   } else {
    previous->next = current->next;
   }    
	
   return current;
}

void printCustomerProduct(int pid){
	
	Customer *temp;
	temp = cbas;
	
	while(1){
		
		if(temp->Basketlist->Productlist->id == pid){
			printf("id:%d\tname:%s\tsurname:%s\n",temp->id,temp->name,temp->surname);
			temp->Basketlist->Productlist = temp->Basketlist->Productlist->next;
			if(temp->Basketlist->Productlist == NULL){
				temp->Basketlist = temp->Basketlist->next;
				if(temp->Basketlist == NULL){
					temp = temp->next;
					if(temp == NULL){
						break;
					}
				}
			}
		}
		
		else if(temp->Basketlist->Productlist->id != pid){
			temp->Basketlist->Productlist = temp->Basketlist->Productlist->next;
			if(temp->Basketlist->Productlist == NULL){
				temp->Basketlist = temp->Basketlist->next;
				if(temp->Basketlist == NULL){
					temp = temp->next;
					if(temp == NULL){
						break;
					}
				}
			}
		}
	}
	
	
}

void printCustomer() {
   Customer *ptr = cbas;
   printf("\n");
   
   if(ptr == NULL){
   	printf("There are no customers in here..\n");
   }
   while(ptr != NULL) {
      printf("id:%d Name:%s\tSurname:%s \n",ptr->id,ptr->name,ptr->surname);
      ptr = ptr->next;
   }
	
}

int addProducts(int givenprice, char givenName[30], char givenCategory[30]){
	Product *newP, *tempP;
	newP = (Product*)malloc(sizeof(Product));
	newP->price = givenprice;
	strcpy(newP->name,givenName);
	strcpy(newP->category,givenCategory);
	newP->next = NULL;
	newP->id = Pid;
	Pid++;
	
	if(pbas == NULL){
		pbas = newP;
		return; 
	}
	
	tempP = pbas;
	while(tempP->next != NULL){
		tempP = tempP->next;
	}
	tempP->next = newP;
	return Pid;
}
void totalAmount(){
	int total = 0;
	Customer *temp;
	temp = cbas;
	
	while(temp != NULL){
		if(temp->Basketlist == NULL){
			printf("id:%d\tname:%s\tsurname:%s\t Did not purchase anything..\n",temp->id,temp->name,temp->surname);
			temp = temp->next;
		}
		while(temp->Basketlist != NULL){
			total += temp->Basketlist->amount;
			temp->Basketlist = temp->Basketlist->next;
			if(temp->Basketlist == NULL){
				printf("id:%d\tname:%s\tsurname:%s\t amount:%d\n",temp->id,temp->name,temp->surname,total);
				temp = temp->next;
				total = 0;
			}
		}
	}
	
}
void menu(){
	int choice;
	printf("-------------\n");
	printf("---WELCOME---\n");
	printf("-------------\n");
	
	printf("[1] Add customer\n");
	printf("[2] Add basket\n");
	printf("[3] Remove customer\n");
	printf("[4] List the customers who bought a specific product\n");
	printf("[5] List the total shopping amounts of each customer\n");
	printf("[6] Exit\n");
	printf("Choice:");
	scanf("%d",&choice);
	
	if(choice == 1){
		char name[30];
		char surname[30];
		
		printCustomer();
		printf("Name:");
		scanf("%s",name);
		printf("Surname:");
		scanf("%s",surname);
		addCustomer(name,surname);
		printCustomer();
		menu();
		
	}
	else if(choice == 2){
		addtobasket();
		menu();
	}
	else if(choice == 3){
		int givenid;
		printCustomer();
		printf("Enter an id:");
		scanf("%d",&givenid);
		deleteCustomer(givenid);
		printCustomer();
		menu();
	}
	else if(choice == 4){
		int givenid;
		printProduct();
		printf("Enter an id:");
		scanf("%d",&givenid);
		printCustomerProduct(givenid);
		menu();
	}
	else if(choice == 5){
		totalAmount();
		menu();
	}
	else if(choice == 6){
		printf("End of the program");
	}
}



int main(){
	addProducts(2,"Milk","Food");
	addProducts(10,"Butter","Food");
	addProducts(15,"Rice","Food");
	addProducts(5,"Salt","Food");
	addProducts(8,"Flour","Food");
	addProducts(16,"Tea","Food");
	addProducts(2,"Pasta","Food");
	addProducts(1,"Water","Food");
	addProducts(2,"Cola","Food");
	addProducts(5,"Coffee","Food");
	addProducts(10,"Egg","Food");
	addProducts(14,"Cheese","Food");
	addProducts(30,"Honey","Food");
	addProducts(22,"Chicken","Food");
	addProducts(3,"Tomatoes","Food");
	addProducts(3,"Potatoes","Food");
	addProducts(5,"Yoghurt","Food");
	addProducts(3,"Carrot","Food");
	addProducts(12,"IceCream","Food");
	addProducts(1,"Bread","Food");
	addProducts(5,"ToothBrush","hygiene");
	addProducts(12,"ToothPaste","hygiene");
	addProducts(1,"Napkin","hygiene");
	addProducts(35,"Detergent","hygiene");
	addProducts(6,"Soap","hygiene");
	addProducts(15,"Shampoo","hygiene");
	addProducts(12,"Deodorant","hygiene");
	addCustomer("Ayhan","Altan");
	menu();

	
}

