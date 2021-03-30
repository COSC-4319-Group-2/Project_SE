#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	//Open Cover File for Report - Supply Directory and File Location
	FILE *coverFile;
	coverFile = fopen("/home/amh096/cs2347/Lab1/CoverPage.txt","w");

	//If the file is not in above directory exit program with error. 
	if(coverFile == NULL){
		printf("Cover Page file does not exist. Program Terminating.\n");
		exit(1);
	}

	/*If file exists write to the Cover Page:
		- Lab Number
		- Name
		- Due Date
		- Submission Date
		- Option Completed
	*/
	fprintf(coverFile, "%20s", "Lab 1\n");
	fprintf(coverFile, "%22s", "Allyn Heft\n");
	fprintf(coverFile, "%27s", "Due: March 12, 2021\n");
	fprintf(coverFile, "%31s", "Submitted: March 3, 2021\n");
	fprintf(coverFile, "%27s", "Option Completed 'A'");

	/*Create Files for Report
		- inFile = Holds the input information for the employees
		- outFile = The final output report for printing
	*/
	FILE *inFile;
	FILE *outFile;

	char fileOutName[21];
	char response;

	inFile = fopen("/home/amh096/cs2347/Lab1/lab1SampleData.txt", "r");
	//Check to see if file exists in directory
	if(inFile == NULL){
		printf("Data file does not exist. Program Terminating.\n");
		exit(1);
	}

	//Prompt user to enter report file name
	printf("Please enter the output file name for the report (Max 20 Characters): \n");
	scanf("%s", fileOutName);

	//Check to see if file exists - if so ask for overwrite
	if((outFile = fopen(fileOutName, "r"))!= NULL){
		printf("\n%s file already exists.\n", fileOutName);
		printf("Would you like to overwrite the file? (Y or N): \n");
		scanf("%*c%c", &response);

		if((response =='n') || (response == 'N')){
			fclose(outFile);
			printf("\nFile not overwritten. Program Terminating.\n");
			exit(1);
		}
	}
	outFile = fopen(fileOutName, "w");
	if(outFile == NULL){
		printf("File not created. Program Terminating.\n");
		exit(1);
	}

	/* Begin Calculation from inFile
		Get Users Data - Data Needed:
	  - Employee's Name (given and surname)
	  - Employee's Number
	  - Year-to-Date
	  - Gross Pay
	*/
	char given[11], surname[11];
	int employeeNumber, lineCounter;
	int width = 8; 
	float ytd, grossPay, total, grossTotal, ficaTotal;
	float ficaTax = 4.2;
	double fixedTotal;

	/*Date Feature
	  Using time.h there is a struct for time features.
	  - time_t = clock time of the system in integer format
	  - time() & localtime() are functions that return the calendar 
	  - and local time of the system
	*/
	struct tm* ptr;
	time_t local;
	local = time(NULL);
	ptr = localtime(&local);

	//Title Line in output file
	fprintf(outFile, "%32s\t\t\t%s\n\n", "ACME", asctime(ptr));
	fprintf(outFile, "%s%8s%8s%12s%12s%12s%14s", "Line No.","Emp. No", "Given", "Surname", "YTD ($)", "GROSS($)", "FICA Tax\n\n");

	/*Perform Calculations for:
	  - FICA Tax
	  - Total Gross pay
	  - Total FICA pay
	  Using a while statement, read specified input data.
	  Using nested if-else statments filter out different YTDs
	  Using specified YTDs calculate the total/FICA payments
	*/
	while((fscanf(inFile, "%d%d%s%s", &lineCounter, &employeeNumber, given, surname))!= EOF){
		fscanf(inFile, "%f", &ytd);
		fscanf(inFile, "%f", &grossPay);

		if(ytd >= 110100){
			total = ytd + grossPay;
			grossTotal += grossPay;
		}
		else
			if(ytd + grossPay <= 110100){
				total = grossPay - (grossPay * (ficaTax/100));
				grossTotal += grossPay;
				ficaTotal += total;
			}
			else{
				float subTotal;
				subTotal = (110100 - ytd);
				total = subTotal - (subTotal * (ficaTax/100));
				grossTotal += grossPay;
				ficaTotal += total;
			}

		//Write the results to output file
		fprintf(outFile, "%4d\t", lineCounter);
		fprintf(outFile, "%6d\t", employeeNumber);
		fprintf(outFile, "%8s\t", given);
		fprintf(outFile, "%8s\t", surname);
		fprintf(outFile, "%s%10.2f\t", "$", ytd);
		fprintf(outFile, "%s%10.2f\t\t", "$", grossPay);
		fprintf(outFile, "%s%10.2f\n", "$", total);


	}
	fprintf(outFile, "\n\t\t\t\t%s%.2f\t%s%.2f", "Gross Total: $", grossTotal, "FICA Total: $", ficaTotal);

	//Close Files
	fclose(coverFile);
	fclose(inFile);
	fclose(outFile);
	return 0;

}