//Vaibhav Arora
//27th Oct 2020
//Contains the main function which calls all the required functions based on the user input.

#include <stdio.h>
#include <string.h>
#include "crossfunc.h"

int main(int argc,char *argv[]){
	if(argc>3){
		printf("\nInvalid Input\n");
		return 0;
	}
	system("clear");
	if(argc==1 || argc==2){
		printf("\nAnagram Crossword Puzzle Generator");
		printf("\n----------------------------------");
	}
	char words[20][15];
	char jumbled[20][15];
	char end[1];
	strcpy(end,".");
	int i=0;
	char filename[256],fileout[256];
	int condition,count,countacceptedwords;
	char solutionboard[15][15];
	char blankboard[15][15];
	int xlocation[20];
	int ylocation[20];
	int direction[20];
	char rejectedwords[20][15];
	char directions[20][15];
	char acceptedwords[20][15];
	int rejectwordcount=0;
	int *rejects=&rejectwordcount;
	setupboards(solutionboard,blankboard);

	if(argc==1){
		printf("\nEnter a list of words:\n");
		while(i<20){
			scanf("%s",words[i]);
			getchar();
			if(strcmp(words[i],".")==0){
				printf("\nThank you !\n");
				break;
			}
			count=count+1;
			touppercase(words[i]);
			condition=checkvalid(words[i]);
			if(condition==0){
				i=i-1;
				count=count-1;
			}
			i++;
		}
	}

	else if(argc==2){
		printf("Filename=%s -->Input\n",argv[1]);
		strcpy(filename,argv[1]);
		printf("%s",filename);
		readfile(filename,words);
	}

	else if(argc==3){
		strcpy(filename,argv[1]);
		strcpy(fileout,argv[2]);
		readfile(filename,words);
		sort(words,count);
		countacceptedwords=createpuzzle(solutionboard,words,count,xlocation,ylocation,rejectedwords,acceptedwords,directions,rejects);
		jumble(acceptedwords,jumbled,countacceptedwords);
		printouttofile(solutionboard,blankboard,jumbled,countacceptedwords,xlocation,ylocation,directions,rejectedwords,rejectwordcount,fileout);;
		return;
	}

	sort(words,count);
	countacceptedwords=createpuzzle(solutionboard,words,count,xlocation,ylocation,rejectedwords,acceptedwords,directions,rejects);
	jumble(acceptedwords,jumbled,countacceptedwords);
	display(solutionboard,blankboard,jumbled,countacceptedwords,xlocation,ylocation,directions,rejectedwords,rejectwordcount);

	return 0;
}
	
