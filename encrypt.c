#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

/*
Hash function to from the password, create a hash value.
*/

unsigned long FNVHash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void main(){
	
    char fpassword[30]; //password to modife the file
	char fname[20]; //name of the file
    char ch; //character that will be modife
    char choice; //
	FILE *fps, *fpt; //Call of the files
    unsigned long hash; //hash value that we will use to make the encrypt

	printf("Enter file name to encrypt, pls : ");
    scanf("%s",&fname);
	fps=fopen(fname, "r");

	if(fps==NULL){
		printf("Error in opening file..!!");
		printf("\nPress any key to exit...");
		getch();
		exit(1);
	}

	fpt=fopen("temp.txt", "w");

	if(fpt==NULL){
		printf("Error in creating temp.txt file..!!");
		fclose(fps);
		printf("\nPress any key to exit...");
		getch();
		exit(2);
	}

    printf("Give the password for the file, pls: ");
    scanf("%s",&fpassword);

    hash = FNVHash(fpassword);

	while(1){

		ch=fgetc(fps);

		if(ch==EOF){
			break;
		}

		else{
			ch=ch+hash;
			fputc(ch, fpt);
		}
	}

	fclose(fps);
	fclose(fpt);
	fps=fopen(fname, "w");

	if(fps==NULL){

		printf("Error in opening source file..!!");
		printf("\nPress any key to exit...");
		getch();
		exit(3);

	}

	fpt=fopen("temp.txt", "r");

	if(fpt==NULL){
		printf("Error in opening temp.txt file...!!");
		fclose(fps);
		printf("\nPress any key to exit...");
		getch();
		exit(4);
	}

	while(1){
		ch=fgetc(fpt);
		if(ch==EOF){
			break;
		}
		else{
			fputc(ch, fps);
		}
	}

	printf("File %s encrypted successfully..!!", fname);
	printf("\nPress any key to exit...");
	fclose(fps);
	fclose(fpt);
	getch();
}