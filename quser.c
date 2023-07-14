#include<stdio.h>
#include<conio.h>
#include<string.h>
struct qutionuser{
	char name[50];
	char username[50];
	char password[50];
};
int main(){
	struct qutionuser sample[3]={{"Sanjeev","user1","user1"},{"Bala","user2","user2"},{"Sriram","user3","user3"}};
	FILE *fp;
	fp=fopen("quser.txt","w");
	struct qutionuser *s1=sample;
	struct qutionuser s2;
	fwrite(s1,sizeof(s2),3,fp);
	fclose(fp);
}
