//Vaibhav Arora
//27th Oct,2020
//Code contains all functions needed to meet the specified conditions and print output
//1st extra credit part has been done by skipping words which are invalid (worth +5 pts)
//

#include <stdio.h>
#include <string.h>
#include "crossfunc.h"

#define _GNU_SOURCE 

void setupboards(char solutionboard[15][15],char blankboard[15][15]){
	int i,j;
	for(i=0;i<15;i++){
		for(j=0;j<15;j++){
			solutionboard[i][j]='.';
			blankboard[i][j]='#';
		}
	}
}

void readfile(char filename[],char words[][15]){
	FILE *fp=fopen(filename,"r");
	char line[256];
	int i=0;
	char temp[256];
	if(fp==NULL){
		printf("\nIncorrect File\n");
	}	
	else{
		while(i<20){
			fscanf(fp,"%s",line);
			strcpy(temp,line);
			if(i==19 || temp[0]=='.'){
				return;
			}
			int valid=checkvalid(temp);
			if(valid==1){
				strcpy(words[i],line);
				i++;
			}
		}
	}
}

void touppercase(char word[]){
	int i;
	int length = strlen(word);
	for(i=0;i<length;i++){
		if(word[i]>=65 && word[i]<=90){
		}
		else if(word[i]>=97 && word[i]<=122){
			word[i]=word[i]-32;
		}
		else{
		}
	}
}

int checkvalid(char word[]){
	int validity;
	int length=strlen(word);
	int i;
	int count=0;
	if(length==1 || length>15){
		printf("Invalid Input --> Word too long/short\n");
		return 0;
	}
	for(i=0;i<length;i++){
		if(word[i]>=65 && word[i]<=90){
			count=count+1;
		}		
	}
	if(count==length){
		return 1;
	}
	else{
		printf("Invalid Input --> Words contains more than letters\n");
		return 0;
	}
}

void sort(char words [][15],int count){
	char temp[15];
	int length,length2;
	int i,j;
	for(i=0;i<count-1;i++){
		for(j=0;j<count-i-1;j++){
			length=strlen(words[j]);
			length2=strlen(words[j+1]);
			if(length<length2){
				strcpy(temp,words[j+1]);
				strcpy(words[j+1],words[j]);
				strcpy(words[j],temp);
			}	
		}
	}
}

void jumble(char words[][15],char jumbled[][15],int count){ 
	int length,i,j;
	char tempword[15];
	char *word;
	for(i=0;i<count;i++){
		strcpy(tempword,words[i]);
		strfry(tempword);
		strcpy(jumbled[i],tempword);
	}
}

int createpuzzle(char puzzle[15][15],char words[][15],int count,int xval[],int yval[],char wordreject[][15],char wordaccept[][15],char direction[][15],int *rejects){
	int countacceptedwords=0;
	int length=strlen(words[0]);
	char word1[15];
	int middle=7;
	int row,col;
	int mid=length/2;
	int startpoint=7-mid;
	int position=0;
	int position2=0;
	int *rowpoint=&row;
	int *colpoint=&col;
	int *p=&position;
	int acceptedwordcount=0;
	int rejectedwordcount=0;
	int length2=strlen(words[1]);
	xval[0]=middle;
	yval[0]=startpoint;
	strcpy(direction[0],"Across");
	int i,j,reject,temp;
	strcpy(wordaccept[0],words[0]);
	for(i=0;i<length;i++){
		puzzle[middle][startpoint+i]=words[0][i];
	}
	countacceptedwords++;
	acceptedwordcount++;

	int rejected=findcommon(words[1],puzzle,p,rowpoint,colpoint);
	int startpoint2=row-position;
	xval[1]=row;
	yval[1]=col;
	strcpy(direction[1],"Down");

	if(rejected>0){
		strcpy(wordaccept[1],words[1]);
		countacceptedwords++;
		acceptedwordcount++;
		for(i=0;i<length2;i++){
			puzzle[startpoint2+i][col]=words[1][i];
		}
	}

	if(count>2){
		for(i=2;i<count;i++){
			strcpy(word1,words[i]);
			int reject=findcommon(word1,puzzle,p,&row,colpoint);
			if(reject==2){ //print vertical
				printvert(puzzle,word1,position,row,col,xval,yval,direction,i,wordaccept,&acceptedwordcount,rejects);
				countacceptedwords++;
				temp=*rejects;
				rejectedwordcount=rejectedwordcount+temp;
			}
			else if(reject==1){ //print horizontal
				printhorizon(puzzle,word1,position,row,col,xval,yval,direction,i,wordaccept,&acceptedwordcount,rejects);
				temp=*rejects;
				rejectedwordcount=rejectedwordcount+temp;
				countacceptedwords++;
			}
			else{
				printf("Reached here");
				strcpy(wordreject[rejectedwordcount],word1);
			}	
		}
	}

	*rejects=rejectedwordcount;
	return acceptedwordcount;
}

int findcommon(char word[],char puzzle[][15],int *position,int *row,int *col){
	int i,j,k;
	int length=strlen(word);
	for(i=0;i<length;i++){
		char character=word[i];
		for(j=0;j<15;j++){ //j is row
			for(k=0;k<15;k++){ //k is col
				char puzzleval=puzzle[j][k];
				if(puzzleval==character){
					if(puzzle[j-1][k]==46 && puzzle[j+1][k]==46){
						*position=i;
						*row=j;
						*col=k;
						return 2;
					}	
					else if(puzzle[j][k-1]==46 && puzzle[j][k+1]==46){
						*position=i;
						*row=j;
						*col=k;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void printhorizon(char puzzle[][15],char word[15],int i,int row,int col,int xval[],int yval[],char dir[][15],int wordnumber,char acceptedword[][15],int *acceptedwordcount,int *rejected){
	int length=strlen(word);
	static int rejectedword=0;
	int wordacc=*acceptedwordcount;
	int remain=length-i;
	int pos=i;
	int colcount=-1;
	int count=1;
	int letter=0;
	int start=col-i;
	while(pos<length){
		colcount++;
		if(puzzle[row][start+colcount]==46 && puzzle[row+1][start+colcount]==46 && puzzle[row-1][start+colcount]==46){
			count=count+1;
		}
		pos++;
	}
	
	pos=0;
	if(count==remain){
		strcpy(acceptedword[wordacc],word);
		strcpy(dir[wordacc],"Across");
		xval[wordacc]=row;
		yval[wordacc]=start;
		for(pos=0;pos<length;pos++){
			puzzle[row][start+pos]=word[pos];
		}
		wordacc++;
	}
	else{
		rejectedword++;
	}
	//printf("rejectedwordsinsidefunction=%d",rejectedword);
	*acceptedwordcount=wordacc;
	*rejected=rejectedword;
}
void printvert(char puzzle[][15],char word[15],int i,int row,int col,int xval[],int yval[],char dir[][15],int wordnumber,char acceptedword[][15],int *acceptedwordcount,int *rejected){
	int wordacc=*acceptedwordcount;
	static int rejectedword=0;
	int length=strlen(word);
	int remain=length-i;
	int pos=i;
	int count=1;
	int letter=0;
	int start=row-i;
	int rowcount=-1;
	while(pos<length){
		rowcount++;
		if(puzzle[start+rowcount][col]==46 && puzzle[start+rowcount][col+1]==46 && puzzle[start+rowcount][col-1]==46){
			count=count+1;
		}
		pos++;
	}
	pos=0;
	if(count==remain){
		strcpy(dir[wordacc],"Down");
		strcpy(acceptedword[wordacc],word);
		xval[wordacc]=start;
		yval[wordacc]=col;
		for(pos=0;pos<length;pos++){
			puzzle[start+pos][col]=word[pos];
		}
		wordacc++;
	}
	else{
		rejectedword++;
	}
	*acceptedwordcount=wordacc;
	*rejected=rejectedword;
}
	
void display(char solutionboard[][15],char puzzleboard[][15],char jumbled[][15],int numwords,int xval[],int yval[],char direction[][15],char rejects[][15],int rejectedwordcount){
	printf("\nSolution:\n");
	
	int i,j;
	for(i=-1;i<16;i++){
		if(i==-1 || i==15){
			printf("-----------------\n");
			continue;
		}
		for(j=-1;j<16;j++){
			if(j==-1 || j==15){
				if(i>-1 && i<15){
					printf("|");
				}
			}
			else{
				printf("%c",solutionboard[i][j]);
			}
		}
		printf("\n");
	}

	createblank(solutionboard,puzzleboard);
	int ii,jj;
	printf("\nCrossword puzzle:\n");
	for(ii=-1;ii<16;ii++){
		if(ii==-1 || ii==15){
			printf("-----------------\n");
			continue;
		}
		for(jj=-1;jj<16;jj++){
			if(jj==-1 || jj==15){
				if(ii>-1 && ii<15){
					printf("|");
				}
			}
			else{
				printf("%c",puzzleboard[ii][jj]);
			}
		}
		printf("\n");
	}

	printf("\nClues:\n");
	for(i=0;i<numwords;i++){
			printf("%d,%d\t%s\t%s\n",yval[i],xval[i],direction[i],jumbled[i]);
	}

	printf("\nClues only cover words on the board and do not include any words which could not be placed\n");
}

void createblank(char solutionboard[][15],char puzzle[][15]){
	//ascii value of . is 46
	int i,j;
	
	for(i=0;i<15;i++){
		for(j=0;j<15;j++){
			char c1=solutionboard[i][j];
			if(c1=='.'){
				puzzle[i][j]='#';
			}
			else{
				puzzle[i][j]=32;
			}
		}	
	}
}

void printouttofile(char solution[][15],char puzzle[][15],char jumbled[][15],int numwords,int xloc[],int yloc[],char direction[][15],char rejectword[][15],int rejectwordcount,char filename[]){
	int i,j;
	FILE *fp=fopen(filename,"w");
	fprintf(fp,"Anagran Crossword Puzzle Generator\n");
	fprintf(fp,"-----------------------------------\n");
	fprintf(fp,"\nSolution:\n");
	
	for(i=-1;i<16;i++){
		if(i==-1 || i==15){
			fprintf(fp,"-----------------\n");
			continue;
		}
		for(j=-1;j<16;j++){
			if(j==-1 || j==15){
				if(i>-1 && i<15){
					fprintf(fp,"|");
				}
			}
			else{
					fprintf(fp,"%c",solution[i][j]);
			}
		}
			fprintf(fp,"\n");
	}

	createblank(solution,puzzle);
	
	int ii,jj;
	fprintf(fp,"\nCrossword Puzzle:\n");
	for(ii=-1;ii<16;ii++){
		if(ii==-1 || ii==15){
			fprintf(fp,"-----------------\n");
			continue;
		}
		for(jj=-1;jj<16;jj++){
			if(jj==-1 || jj==15){
				if(ii>-1 && ii<15){
					fprintf(fp,"|");
				}
			}
			else{
				fprintf(fp,"%c",puzzle[ii][jj]);
			}
		}
		fprintf(fp,"\n");
	}	
	
	fprintf(fp,"\nClues:\n");
	for(i=0;i<numwords;i++){
		fprintf(fp,"%d,%d\t%s\t%s\n",yloc[i],xloc[i],direction[i],jumbled[i]);
	}

	fprintf(fp,"\nClues only for words on the board, words which could not be placed are not included\n");
}
