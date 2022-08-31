
#include <stdio.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h> 


#define plithos_high_scores 10
#define arxeio_high_scores "highscore_file.txt"
#define arxeio_words "words.txt"

typedef struct
{
	char player[10];
	int hs;	
}highscore;


void fill_highscore_array(highscore[], char*);
int playgame(char*, char**);
char** fill_word_array(char*);
void update_and_print_highscore(highscore[], char*, int);
void update_highscore_file(char*, highscore[]);

int main ()
{
	int x, score;
	char username[50];
	char** word_array;
	highscore highscore_array[plithos_high_scores]; 
	
	word_array = fill_word_array(arxeio_words);
	fill_highscore_array(highscore_array, arxeio_high_scores);

	printf("Insert name: "); scanf("%s", username);

	score = playgame(username, word_array);
	update_and_print_highscore(highscore_array, username, score);
	update_highscore_file(arxeio_high_scores, highscore_array);
	

	return 0 ;
}


//anoigei to arxeio keimenou fileName kai gemizei ton pinaka domwn array me ta 10 high scores
void fill_highscore_array(highscore array[], char* fileName)
{
   	int i;
	FILE*fp;
	fp=fopen(fileName,"r");
	//arxikopoihsh pinaka 
    for(i=0;i<10;i++)
    {
    	strcpy(array[i].player,"NULL");
    	array[i].hs=-1;
	}
	//gemisma pinaka
	for(i=0;i<10;i++)
    {
	    fscanf(fp,"%s %d",array[i].player,&array[i].hs);
    }
fclose(fp);	
	
}

//dexetai to onoma tou player kai ton pinaka leksewn, ylopoiei to paixnidi kai epistrefei to score tou xristi (lekseis pou vrike)
int playgame(char* u, char** words)
{
int i,length,r,check=0,score=0,lifes=10,perfect=1;
r = rand() % 2243;
char word[20],hidden_word[20],letter[2];
printf("Welcome %s!!\n",u);
printf("Get ready...\n");

//arxi paixnidiou
while(lifes>=0)
{

	srand(time(0));	
    r = rand() % 2243;
    strcpy(word,words[r]);
 
//uncomment thn 86 gia cheat sto paixnidi
//	printf("%s",word);

//kataskeuh krifhs lekshs
    strcpy(hidden_word,word);
    length=strlen(word);
    for(i=0;i<length;i++){
	    hidden_word[i]='-';
	}




//elegxos zwn h an brethike h leksh meta apo kathe gramma	
    while(lifes>=0 && strcmp (word, hidden_word)!=0)
    {
//diabasma neo grammatos    	
	    printf("\n Word %d \t %d lifes\n\n\n",score+1,lifes);
////	    uncomment to enable cheat mode
//	    printf("%s\n",word);
	    printf("   %s\n",hidden_word);
	    printf("Insert letter:");
		check=0;
	    scanf("%s",&letter[0]);
//antikatastash grammatos an uparxei 
	    for(i=0;i<length;i++){
		    if(letter[0]==word[i] && letter[0]!=hidden_word[i]){
			    hidden_word[i]=word[i];
			     check=1;
		    }
	    }
//ama den hparei to gramma to check einai 0 kai aferountai oi zwes analoga kai to perfect ginete 0
	    if (check==0){
		perfect=0;
		    if (letter[0]=='u' ||letter[0]=='i' || letter[0]=='e' ||letter[0]=='o' ||letter[0]=='a'){
		    lifes=lifes-2;
		    }
		    else{
		    lifes--;
	        }
	    }
    }
//analogos thn katastash tou perfect ananaionontai 5 h 3 zwes
    if (lifes>=0)
    {	
    	score++;
	    if (perfect==1)
	    lifes=lifes+5;
	    else
	    lifes=lifes+2;
    perfect=1;	
    puts(hidden_word);
    printf("\nCongratulations %s!!\n\n twra exete %d!!lifes\n",u,lifes);
    }
}
printf("\nGAME OVER\n");
printf("\n Your score is %d\n\n",score);
return score; // tha to allaksete
}

//dexetai to onoma tou arxeiou pinaka leksewn, kai epistrefei ton pinaka (strings) me tis lekseis
char** fill_word_array(char* fileName)
{FILE * fp;
fp = fopen(fileName,"r");
char ** wordsarray;
int i,j,height=2243,width=30;
wordsarray=(char**)malloc(height*sizeof(char*));
for(i=0;i<height;i++)
	wordsarray[i]=(char*)malloc(width*sizeof(char*));

//gemisma pinaka
while(!feof(fp)){
    for(i=0;i<2243;i++){
       fscanf(fp,"%s",wordsarray[i]);
       }
 }
fclose(fp);
return wordsarray;  
}


//dexetai to onoma tou player tou telautaiou paixnidiou, kathws kai to score tou kai kanei update ton pinaka town highscore (an prepei)
// kai ektypwnei ta highscores (osa yparxoun)
void update_and_print_highscore(highscore array[], char* u, int sc)
{
int i,temp=11;	
//ebresh theshs neoy score
for(i=0;i<10;i++){
    if (sc>array[i].hs){
	    temp=i;
   	    break;
        }

}
// metakinisei score gia na mpei to neo		
for(i=0;i<9-temp;i++){
	strcpy(array[9-i].player,array[8-i].player);
	array[9-i].hs=array[8-i].hs;
}
strcpy(array[temp].player,u);
array[temp].hs=sc;
	
printf(" -----HIGHSCORES-----\n\n");
printf( " USER\t\tSCORE\n\n");
for(i=0;i<10;i++){
   	//score -1 exoun oi kenes eggrafes toy pinaka
   	if(array[i].hs!=-1){
	    printf(" %s \t\t %d\n",array[i].player,array[i].hs);
    }	
}	

}

//kanei update to highscore file
void update_highscore_file(char* fileName, highscore array[])
{
int i=0;
FILE *fp;
fp=fopen(fileName,"w");
	while( array[i].hs!=-1 && i <10){
	fprintf( fp," %s \t %d\n",array[i].player,array[i].hs);
    i++;
    }
}
