//Vaibhav Arora
//27th October,2020
//Code contains the prototypes of all the functions needed in order to run the corssward based on the required conditions

void readfile(char [],char[][15]);
void setupboards(char [][15], char [][15]);
void solution(char [][15],char[][15]);
void puzzle(char [][15],char [][15]);
void display(char [][15],char [][15],char [][15],int,int[],int[],char [][15],char [][15],int);
int checkvalid(char []);
void touppercase(char[]);
void sort(char [][15],int);
void jumble(char [][15],char [][15],int);
int createpuzzle(char [][15],char [][15],int,int [],int [],char [][15],char [][15],char [][15],int *);
int findcommon(char [],char [][15],int *,int *,int *);
void createblank(char [][15],char [][15]);
void printvert(char [][15],char [],int,int,int,int[],int[],char[][15],int,char [][15],int *,int *);
void printhorizon(char [][15],char[],int,int,int,int[],int[],char [][15],int,char [][15],int *,int *);
void printouttofile(char [][15],char [][15],char [][15],int,int[],int[],char [][15],char [][15],int,char []);
