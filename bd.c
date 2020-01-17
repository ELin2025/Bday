#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


int compare(time_t, time_t, time_t);
char* readLine(FILE* f);
main(){
	time_t currentTime = time(NULL);
	char ch;
	int count=0;
	int counter =0;	
	FILE *fp = fopen("Data.txt", "r");
	while((ch = fgetc(fp)) != EOF){
		while(ch != '\n'){
			ch = fgetc(fp);
		}
		counter++;
		if(counter==8){
			count++;
			counter =0;
		}
	}
	fclose(fp);
	int isName = 1;
	char* names[count];
	struct tm prepare[count];
	time_t bday[count];
	int byear[count];
	FILE* f = fopen("Data.txt", "r");
	for(int i = 0; i< 3; i++){
		char temp = fgetc(f);
	}
	int counte = 0;
	while((ch = fgetc(f)) != EOF){
		char* h = (char*)malloc(1000);
		char* cha = (char*)malloc(sizeof(&ch));
		while(ch != '\n'){
			cha = &ch;
			*(cha+1) = *("");
			strcat(h, cha);
			ch = fgetc(f);
		}
		ch = fgetc(f);
		if(isName==1){	
			names[counte] = h;
			while(ch != '\n'){
				ch = fgetc(f);
			}
			isName = 0;
		}
		else{
			char* day = (char*)malloc(sizeof(h));
			day = h + 8;
			char* year= (char*)malloc(sizeof(h));
			for(int i = 0; i< 4; i++){
				*(year+i) =*(h);
				h++;
			}
			h++;
			char*month =(char*)malloc(sizeof(h));
			for(int i = 0; i< 2; i++){
				*(month+i) = *(h);
				h++;
			}
			sscanf(day, "%d", &prepare[counte].tm_mday);
			sscanf(month, "%d", &prepare[counte].tm_mon);
			sscanf(year, "%d", &byear[counte]);
			struct tm* now = localtime(&currentTime);
			prepare[counte].tm_year = now->tm_year;
			prepare[counte].tm_mon = prepare[counte].tm_mon - 1;
			prepare[counte].tm_sec = 59;
			prepare[counte].tm_min = 59;
			prepare[counte].tm_hour = 23;
			for(int i =0; i< 5;i++){
				while(ch != '\n'){
					ch = fgetc(f);
				}
				if(i==4){
					break;
				}
				ch = fgetc(f);
			}	
			isName = 1;
			counte++;
		}
		h = "";
	}
	int b = 0;
	for(int i = 0; i< count;i++){

		bday[i] = mktime(&prepare[i]);
		if(difftime(bday[i], currentTime) >= 0){
			b++;
		}
	}
	int isBirthday = 0;
	int age[b];
	time_t valid[b];
	char* validName[b];
	time_t final[b];
	char* finalName[b];
	int finalAge[b];
	int a = 0;
	for(int i = 0; i<count; i++){
		if(difftime(bday[i], currentTime)>=0){
			valid[a] = bday[i];
			validName[a] = names[i];
			age[a] =prepare->tm_year-  (byear[i]- 1900) ;
			a++;
		}
	}
	char* string;
	int in = -1;
	while(true){
		time_t recent;
		currentTime = time(NULL);
		recent = valid[0];
		for(int i  = 0; i< b; i++){
			if(difftime(valid[i], currentTime) >= 0){
				if(compare(valid[i], recent, currentTime) <=0){
					recent= valid[i];
				}
			}
		}
		int an = 0;
		struct tm *cur = localtime(&currentTime);
		cur->tm_hour =23;
		cur->tm_min = 59;
		cur->tm_sec = 59;
		time_t current = mktime(cur);
		if(compare(recent, current, currentTime)==0){
			isBirthday = 1;
		}
		int d = difftime(recent, current)/3600/24;
		for(int i = 0; i< b; i++){
			if(compare(valid[i], recent, currentTime) == 0 ){
				final[an] = valid[i];
				finalName[an] = validName[i];	
				finalAge[an] = age[i];
				an++;
			}
		}
		finalName[an] = "done";
		for(int i = 0; i< b; i++){
			if(finalName[i] == "done"){
				break;
			}
			if(isBirthday == 1){
			printf("%s is %d years old today. HAPPY BIRTHDAY!!!!\n", finalName[i], finalAge[i]);
			}
			else{
				char* edit = (char*)malloc(sizeof(ctime(&final[i])));
				char* temp = (char*)malloc(sizeof(edit));
				temp = ctime(&final[i]);
				for(int i = 0; i<10;i++){
					*(edit + i) = *(temp);
					temp++;
				}
				*(edit+10) = *("");
				printf("%s is going to be %d years old in %d days\n", finalName[i], finalAge[i], d);
			}
		}
		string = ctime(&currentTime);
		printf("%s\n", string);
		sleep(1);
		system("cls");
	}
}
int compare(time_t y, time_t n, time_t current){
	if(difftime(y, current)>difftime(n, current)){
		return 1;
	}
	else if(difftime(y, current)==difftime(n,current)){
		return 0;
	}
	else{
		return -1;
	}
}	
