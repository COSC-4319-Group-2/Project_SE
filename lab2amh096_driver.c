#include <stdio.h>
#include <stdlib.h>

float calculateGross(float, float);
float calculateFICA(float, float);
void newPage(FILE*, float, float, float, int);

int main(){

	//Open Cover File for Report - Supply Directory and File Location
	FILE *coverFile;
	coverFile = fopen("/home/amh096/cs2347/Lab2/CoverPage.txt","w");

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
	fprintf(coverFile, "%20s", "Lab 2\n");
	fprintf(coverFile, "%22s", "Allyn Heft\n");
	fprintf(coverFile, "%27s", "Due: March 26, 2021\n");
	fprintf(coverFile, "%31s", "Submitted: March 26, 2021\n");
	fprintf(coverFile, "%27s", "Option Completed 'B'");

	/*Create Files for Report
		- inFile = Holds the input information for the employees
		- outFile = The final output report for printing
	*/
	FILE *inFile;
	FILE *outFile;

	char fileInName[50];
	char fileOutName[50];
	char response;

	int pageCount = 1;
	int lineCount = 0;
	int maxLines = 4;


	//Get User Input - for Data File
	printf("Please enter the input file name for the data.\n");
	scanf("%s", fileInName);
	//Check to see if file exists in directory
	inFile = fopen(fileInName, "r");
	if(inFile == NULL){
		printf("File not created. Program Terminating.\n");
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

	//Print Heading 1st Page
	if(pageCount == 1){
		fprintf(outFile, "\t\t\t\tACME Sports Inc.\t\t\t\t\n");
		fprintf(outFile, "\t\t\tWe are the best, you use the best!\t\t\t\n");
		fprintf(outFile, "\n----------------------------------------------------------------\n");
	}

	//Initialize Page Totals
	float pGross, pFICA, pNet = 0.0;
	//Initialize Report Totals
	float rGross, rFICA, rNet = 0.0;

	//Read Raw Data in from Input File
	int employeeNumber;
	char given[15], surname[15];
	char department[6];
	float ytd, payrate, hours;
	float gross, fica, net;

	//Title/Headings on Top of Pages
	fprintf(outFile, "Emp # \t\t\t Name \t\t\t Dept. \t New YTD \t\t Gross \t\t FICA \t\t Net\n");

	/* While !EOF read the data from the input file.
	   - Assign variables to data
	   - Use assigned variables to calculate payroll and information.
	   - Print the results to the output file. 
	*/
	while((fscanf(inFile, "%d%s%s%s", &employeeNumber, surname, given, department))!= EOF){
		fscanf(inFile, "%f", &ytd);
		fscanf(inFile, "%f", &payrate);
		fscanf(inFile, "%f", &hours);

		//Call Functions to Calculate Payroll
		float gross = calculateGross(hours, payrate);
		float fica = calculateFICA(ytd, gross);
		float net = ((ytd+gross) - fica);

		//Max Lines is set to 4 to show newPage() functionality 
		if(lineCount < maxLines){
			fprintf(outFile, "%5d\t%10s %10s\t %6s\t%10.2f\t%10.2f\t%10.2f\t%10.2f\t\n", employeeNumber, surname, given, department, ytd, gross, fica, net);

			pGross += gross;
			pFICA += fica;
			pNet += net;

			rGross += pGross;
			rFICA += pFICA;
			rNet += pNet;
			lineCount++;
		}
		else{ 
			newPage(outFile, pGross, pFICA, pNet, pageCount);
			lineCount = 0;
			pageCount++;
			lineCount++;
			fprintf(outFile, "Emp # \t\t\t Name \t\t\t Dept. \t New YTD \t\t Gross \t\t FICA \t\t Net\n");
		}
	}

	//Print the Report Summary
	newPage(outFile, rGross, rFICA, rNet,pageCount++);
	fprintf(outFile, "\n----------------------------------------------------------------\n");
	fprintf(outFile, "\n\t\t\t\tReport Summary\t\t\t\t\n");
	fprintf(outFile, "\nTotal Gross: $%10.2f\n", rGross+gross);
	fprintf(outFile, "Total FICA: $%10.2f\n", rFICA+fica);
	fprintf(outFile, "Total Net: $%10.2f\n", rNet+net);
	fprintf(outFile, "\t\t\t\t\t\tPage %d\n", pageCount);

	//Close Files
	fclose(coverFile);
	fclose(inFile);
	fclose(outFile);

	return 0;
}
/* 
	Function CalculateGross calculates the gross for each worker using hours worked and payrate.
	If they worked 40 hours - gross = hours * payrate.
	If they worked 40+ hours - gross = 40 hours * normal payrate then overtime hours time 1.5 payrate.
*/
float calculateGross(float hoursWorked, float pRate){
	float calGross;
	if(hoursWorked <= 40)
		calGross = (hoursWorked*pRate);
	else
		calGross = ((hoursWorked-40) * (pRate*1.5));
	return calGross;
}
/*
	Function CalculateFICA calculates the FICA tax for each worker using their year to date and gross above.
	A FICA tax rate of 7.1 is being used.
	If the employee's ytd to more than $110,100 they pay no FICA tax.
	If the employee's ytd is less than $110,100 but, their gross + ytd is > 110,100 they pay a FICA Tax on the gross.
	If the employee's net is less than $110,100 they pay a FICA tax on 110,100 - ytd * the FICA tax rate.
*/
float calculateFICA(float yearToDate, float fGross){
	float ficaTax;
	float ficaRate = 7.1;

	if(yearToDate >= 110100){
		ficaTax = 0.0;
	}
	else if((yearToDate + fGross) <= 110100){
		ficaTax = (fGross*ficaRate);
	}
	else
	{
		ficaTax = (110100.00 - yearToDate) * ficaRate;
	}

	return ficaTax;
}
/*
	Function newPage creates a new page based off:
	-Output File and Number of max lines in reports
*/
void newPage(FILE* outputFile, float pageGross, float pageFICA, float pageNet, int countPage){
	fprintf(outputFile, "Page Totals:\t\t\t$%10.2f\t\t$%10.2f\t\t$%10.2f\n", pageGross, pageFICA, pageNet);
	fprintf(outputFile, "\n\t\t\t\t\t\tPage %d", countPage);
	fprintf(outputFile, "\n----------------------------------------------------------------\n");
}