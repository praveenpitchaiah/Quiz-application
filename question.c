#include<stdio.h>
#include<conio.h>
#include<string.h>
struct question{
	char qn[200];
	char choice1[50];
	char choice2[50];
	char choice3[50];
	char choice4[50];
	int crtans;
};
struct qutionuser{
	char name[50];
	char username[50];
	char password[50];
};
void add_question(){
	struct question qn1;
fflush(stdin);
	printf("\nEnter the question:");
	scanf("%[^\n]s",&qn1.qn);
	printf("\nEnter choice1:");
	scanf("%s",qn1.choice1);
	printf("\nEnter choice2:");
	scanf("%s",qn1.choice2);
	printf("\nEnter choice3:");
	scanf("%s",qn1.choice3);
	printf("\nEnter choice4:");
	scanf("%s",qn1.choice4);
	printf("\nEnter crt choice number:");
	scanf("%d",&qn1.crtans);
	FILE *fp;
	fp=fopen("question.txt","a");
	struct question *qt=&qn1;
	struct question q;
	fwrite(qt,sizeof(q),1,fp);
	fclose(fp);
	
	
}
void view_question(){
	FILE *fp;
	struct question qt,*qtp;
	fp=fopen("question.txt","r");
	qtp=&qt;
	while(!feof(fp)){
		fread(qtp,sizeof(qt),1,fp);
		printf("\nQuestion:%s",qtp->qn);
	}
	fclose(fp);
}
int main(){
char username[50];
char password[50];
printf("\nEnter user id:");
scanf("%s",username);
printf("\nEnter password:");
scanf("%s",password);
FILE *fp;
fp=fopen("quser.txt","r");
struct qutionuser qt,*qtp;
int flag=0;
qtp=&qt;
while(!feof(fp)){
	fread(qtp,sizeof(qt),1,fp);
	if(!strcmp(username,qtp->username)){
		flag=1;
		break;
	}
}
if(flag==0){
	printf("\nINVALID USER NAME OR PASSWORD");
	return 0;
}
else{
	printf("\nWelcome %s",qtp->name);
	int choice;
	do{
	printf("\nEnter your choice");
	printf("\n1.See the questions");
	printf("\n2.Add a question");
	printf("\n3.logout");	
	scanf("%d",&choice);
	switch(choice){
		case 1:{
			view_question();
			break;
		}
		case 2:{
			add_question();
			break;
		}
		case 3:{
			
			break;
		}
		default:{
			printf("\nwrong choice");
			break;
		}
	}
	}while(choice!=3);
	
}


	return 0;
}
