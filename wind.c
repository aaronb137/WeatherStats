//Name: Aaron Bartee
//Date: 11-16-2020
//Purpose: Create a system that manages inputted wind data

#include <stdio.h>
#define FILE_NAME "wind.txt"
#define ARRAY_MAC 500

int getMenuChoice();
int addWindData(FILE*, int, double windSpeeds[], char windDirection[]);
int loadWindData(FILE*, double windSpeeds[], char windDirection[]);
void displayWindData(int, double windSpeeds[], char windDirection[]);
void calcWindStats(int, double windSpeeds[], char windDirection[], double*, char*);

int main()
{
	FILE* fp;
	int userChoice, itemNum, newItemNum;
	double windSpeeds[ARRAY_MAC], avgSpeed;
	char windDirection[ARRAY_MAC], topDirection;

	do {
		userChoice = getMenuChoice();
		switch (userChoice)
		{
		//input 1, load wind data
		case 1: 
			fp = fopen(FILE_NAME, "r");
			if (fp == NULL){
				printf("Could not find file\n");
			}
			else{
				itemNum = loadWindData(fp, windSpeeds, windDirection);
				fclose(fp);	
			}
			break;
		//input 2, display wind data		
		case 2: displayWindData(itemNum, windSpeeds, windDirection);
			break;
		//input 3, analyze data
		case 3: calcWindStats(itemNum, windSpeeds, windDirection, &avgSpeed, &topDirection);
			if (topDirection != 'N' && topDirection != 'W' && topDirection != 'E' && topDirection != 'S') {
				printf("Wind averages %.2lf mph but there is no direction that is most prominent.\n", avgSpeed);
			}
			else {
				printf("Wind averages %.2lf mph, mostly in the %c direction.\n", avgSpeed, topDirection);
			}
			break;
		//input 4, add wind data
		case 4: 
			fp = fopen(FILE_NAME, "a");
			if (fp == NULL){
				printf("Could not find file\n");
			}
			else{
				newItemNum = addWindData(fp, itemNum, windSpeeds, windDirection);
				itemNum += newItemNum;
				fclose(fp);	
			}
			
			break;
		//input 0, exit program
		case 0:  return 0;
	
		//if none of these, prompt user to enter valid option and end program
		default: printf("Please enter a valid option!\n\n");
			break;
			}
	  	} while (userChoice != 0);
	
	return 0;
}

int getMenuChoice()
{
	//variable declaration
	int userChoice;
	
	//display menu
	printf("**WIND DATA**\n");
	printf("1. Load Wind Data\n");
	printf("2. Display Wind Data\n");
	printf("3. Analyze Wind Data\n");
	printf("4. Add Wind Data\n");
	printf("0. EXIT\n");
	//user inputs choice
	printf("Enter your choice: ");
	scanf(" %d", &userChoice);
	return userChoice;
}

int addWindData(FILE *fp, int itemNum, double windSpeeds[], char windDirection[])
{
	int count, newItemNum;

	printf("How many data items would you like to add? ");
	scanf(" %d", &newItemNum);
	
	for (count = 0; count < newItemNum; count++)
	{
		printf("Wind speed? ");
		scanf(" %lf", &windSpeeds[count]);
		
		printf("Wind direction? ");
		scanf(" %c", &windDirection[count]);

		fprintf(fp, "%lf %c\n", windSpeeds[count], windDirection[count]);
	}
	printf("New items added: %d\n", newItemNum);
	newItemNum += itemNum;
	printf("New total: %d\n", newItemNum);
	return newItemNum;
	
}

int loadWindData(FILE *fp, double windSpeeds[], char windDirection[])
{
	int index;
	index = 0;	
	
	while(fscanf(fp, "%lf %c\n", &windSpeeds[index], &windDirection[index]) == 2) 
	{
		index++;
	}

	return index;
}

void displayWindData(int itemNum, double windSpeeds[], char windDirection[])
{
	int itemCount, index;
	index = 0;
		
	printf("\n WIND DATA\n");
	printf("=================================================\n");
	printf("||Item #      |    Wind Speed    |  Direction  ||\n");
	printf("||=============================================||\n");
	printf("||------------|------------------|-------------||\n");
	for (itemCount = 1; itemCount <= itemNum; itemCount++) {
		printf("||%9d   |%9.2lf         |  %-11c||\n", itemCount, windSpeeds[index], windDirection[index]);
		printf("||------------|------------------|-------------||\n");
		index++;
	}
	printf("=================================================\n");
}

void calcWindStats(int itemNum, double windSpeeds[], char windDirection[], double *avgSpeed, char *topDirection)
{
	int index, N, W, E, S;
	double sum;
	
	N = 0;
	W = 0;
	E = 0;
	S = 0;

	for (index = 0; index < itemNum; index++) {
		
		sum += windSpeeds[index];
		
		if (windDirection[index] == 'N') {
			N++;
		}
		else if (windDirection[index] == 'W') {
			W++;
		}
		else if (windDirection[index] == 'E') {
			E++;
		}
		else if (windDirection[index] == 'S') {
			S++;
		}
	}
	*avgSpeed = sum/itemNum;
	
	if (N > W && N > E && N > S) {
		*topDirection = 'N';
	}
	else if (W > N && W > E && W > S) {
		*topDirection = 'W';
	}
	else if (E > N && E > W && E > S) {
		*topDirection = 'E';
	}
	else if (S > N && S > W && S > E) {
		*topDirection = 'S';
	}
}
