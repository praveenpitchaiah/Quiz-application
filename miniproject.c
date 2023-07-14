#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
struct user{
	char uid[50];
	char name[50];
	char password[50];
	int highscore;
	int totscore;
	struct user *left;
	struct user *right;	
};
struct user1{
	char uid[50];
	char name[50];
	char password[50];
	int highscore;
	int totscore;
};
struct userq{
	char name[50];
	int totscore;
	struct userq* next;
};
struct question{
	char qn[200];
	char choice1[50];
	char choice2[50];
	char choice3[50];
	char choice4[50];
	int crtans;
	struct question *next;
};
struct qun{
	char qn[200];
	char choice1[50];
	char choice2[50];
	char choice3[50];
	char choice4[50];
	int crtans;
};
struct userq *front=NULL;
struct userq *rear=NULL;

struct question *head=NULL;
struct user *root = NULL;
struct user preorder[150];
int nouser=0;
int inds;
void insertq(char ele[],int pri){
	struct userq *temp=(struct userq*)malloc(sizeof(struct userq));
    strcpy(temp->name,ele);
    temp->totscore=pri;
	if(front==NULL){
		front = temp;
		rear = temp;
		temp->next=NULL;
	}
	else{
	struct userq *t=front;
	if(temp->totscore>=front->totscore){
		temp->next=front;
		
		front=temp;
		return;
	}
	struct userq *pre;
	
	while(t->next!=NULL&&t->totscore>temp->totscore){
		pre=t;
		t=t->next;
	}	
	if(t->next==NULL&&t->totscore<temp->totscore){
		pre->next=temp;
		temp->next=t;
	}
	else if(t->next==NULL){
		t->next=temp;
		temp->next=NULL;
	}
	else if(t->totscore>temp->totscore){
		pre->next=temp;
		temp->next=t;
	}
	}
}
struct user* create(char username[],char name[],char pass[],int score){
	struct user* ptr = (struct user *)malloc(sizeof(struct user));
    strcpy(ptr->uid,username);
    strcpy(ptr->name,name);
    strcpy(ptr->password,pass);
    ptr->highscore=score;
    ptr->left=NULL;
    ptr->right=NULL;
    ptr->totscore=0;
    nouser++;
    return ptr;
}
struct user* insertion(struct user *root1,char username[],char name[],char password[],int score){
	if(root1==NULL){
		return create(username,name,password,score);
	}
	if(0<strcmp(root1->uid,username)){
		root1->left=insertion(root1->left,username,name,password,score);
	}
	else{ 
		root1->right=insertion(root1->right,username,name,password,score);
	}
}
struct user* search(struct user *root1,char key[])
{
	if(root1==NULL){
		return root1;
	}
	if(!strcmp(root1->uid,key)){
		return root1;
	}
	if(strcmp(root1->uid,key)<0)
	    {
	    	return search(root1->right,key);
		}
	return search(root1->left,key);
}

void writeuser(struct user *root1){
	if(root1==NULL){
	
	       return;
	   }
	strcpy(preorder[inds].name,root1->name);
	strcpy(preorder[inds].uid,root1->uid);
	strcpy(preorder[inds].password,root1->password);
	preorder[inds].highscore=root1->highscore;
	preorder[inds].totscore=root1->totscore;
	inds++;
	writeuser(root1->left);
	writeuser(root1->right);
}

void display(struct user *root1){
	if(root1==NULL)
	    return;
	 display(root1->left);
	 printf("\n");
	 printf("\nName:%s",root1->name);
	 printf("\nUser name:%s",root1->uid);
	 printf("\nHigh score:%d",root1->highscore);
	 printf("\nTot score:%d",root->totscore);
	 printf("\n");
	 display(root1->right);
	
}
struct user* newNode(struct user u){
	struct user* temp=(struct user*)malloc(sizeof(struct user));
	temp->highscore=u.highscore;
	strcpy(temp->name,u.name);
	strcpy(temp->password,u.password);
	strcpy(temp->uid,u.uid);
	temp->totscore = u.totscore;
	temp->right=NULL;
	temp->left=NULL;
	return temp;
}
struct user* constree(struct user pre[],int *preindex,int low,int high,int size){
	if(*preindex>=size||low>high){
		return NULL;
	}
	struct user* root1=newNode(pre[*preindex]);
	*preindex=*preindex + 1;
	if(low == high){
		return root1;
	}
	int i;
	for(i=low;i<=high;++i){
		if((strcmp(pre[i].uid,root1->uid))>0)
		    break;
		    
	    
	}
	root1->left=constree(pre,preindex,*preindex,i-1,size);
	root1->right=constree(pre,preindex,i,high,size);
	return root1;
	
}
struct user* createbst(struct user pre[],int size){
	int preindex=0;
	return constree(pre,&preindex,0,size-1,size);
}
void leaderboard(struct user *root1){
	if (root1 == NULL)
        return;
    leaderboard(root1->right);
    insertq(root1->name,root1->totscore);
    leaderboard(root1->left);
}
void insert(struct qun *qn1){
	struct question *temp=(struct question *)malloc(sizeof(struct question));
    strcpy(temp->choice1,qn1->choice1);
    strcpy(temp->choice2,qn1->choice2);
    strcpy(temp->choice3,qn1->choice3);
    strcpy(temp->choice4,qn1->choice4);
    temp->crtans=qn1->crtans;
    strcpy(temp->qn,qn1->qn);
	struct question *t;
	if(head==NULL){
		head = temp;
		temp->next=head;
		
	}
	else{
		t=head;
		while(t->next!=head)
		     t = t->next;
		temp->next=head;
		t->next=temp;
		head=temp;
	}
}
int quiz(){
	FILE *fp;
	fp=fopen("question.txt","r");
	struct qun qt,*qtp;
	qtp=&qt;
	int n=0;
	while(!feof(fp)){
		fread(qtp,sizeof(qt),1,fp);
		n++;
	}
	rewind(fp);
	int k=0;
	while(!feof(fp)){
		if(k==n-1){
      			    break;
				}
		fread(qtp,sizeof(qt),1,fp);
		insert(qtp);
		k++;
	}
	fclose(fp);
	
	int score=0;
	struct question *temp;
	int x=0;
	int choice;
	while(1){
		if(head==NULL){
			printf("\n\nSorry No questions available\nTry Later!!!");
			break;
		}
		if(x==5){
			break;
		}
		else{
			printf("\n%s",head->qn);
			printf("\n\n1.%s",head->choice1);
			printf("\t2.%s",head->choice2);
			printf("\t3.%s",head->choice3);
			printf("\t4.%s",head->choice4);
		    printf("\nEnter the option:");
		    scanf("%d",&choice);
		    if(choice==head->crtans){
		    	score++;
			}
			head=head->next;
		}
		x++;
	}
	printf("\nYour score %d/5 !!!",score);
	struct question *tem=head;
	fp=fopen("question.txt","w");
	struct qun qn1;
	struct qun *qtp1=&qn1;
	struct qun q;
	
	
	while(tem->next!=head){
		strcpy(qtp1->choice1,tem->choice1);
		strcpy(qtp1->choice2,tem->choice2);
		strcpy(qtp1->choice4,tem->choice4);
		strcpy(qtp1->choice3,tem->choice3);
		qtp1->crtans=tem->crtans;
		strcpy(qtp1->qn,tem->qn);
		fwrite(qtp1,sizeof(q),1,fp);
		tem=tem->next;
	}
	strcpy(qtp1->choice1,tem->choice1);
	strcpy(qtp1->choice2,tem->choice2);
	strcpy(qtp1->choice4,tem->choice4);
	strcpy(qtp1->choice3,tem->choice3);
	qtp->crtans=tem->crtans;
	strcpy(qtp1->qn,tem->qn);
	fwrite(qtp1,sizeof(q),1,fp);
	fclose(fp);
	return score;
}
void user_login(){
	char userid[50];
	printf("\nEnter your user name:");
	scanf("%s",userid);
	struct user *temp =  search(root,userid);
	if(!temp){
		printf("\nUser not exits");
		return;
	}
	printf("\nWelcome:%s",temp->name);
	int choice;
	do{
	printf("\nChoose your choice:");	
	printf("\n1.Attend quiz");
	printf("\n2.View leader board");
	printf("\n3.Logout");
	scanf("%d",&choice);
	switch(choice){
		case 1:{
			int score=quiz();
			temp->totscore=temp->totscore+score;
			if(temp->highscore<score){
				temp->highscore=score;
			}
			break;
		}
		case 2:{
			printf("\nLeader board");
			printf("\nName\tscore");
			front=NULL;
			rear=NULL;
			leaderboard(root);
			if(front==NULL){
				printf("\nThe queue is empty");
			}
			else{
				struct userq *temp=front;
				while(temp->next!=NULL){
					printf("\n%s\t%d",temp->name,temp->totscore);
					temp=temp->next;
				}
				printf("\n%s\t%d",temp->name,temp->totscore);
			}
			break;
		}
		case 3:{
			break;
		}
		default:{
			printf("\nWrong choice");
			break;
		}
	}
	}while(choice!=3);
	
}
int main(){
	printf("*****************General quiz******************");
	int choice;
	char username[50];
	char na[50];
	char pass[50];
	int score=0;
	FILE *fp;
	FILE *f;
	struct user1 u,*utp;
	int n=0;
	utp=&u;
	f=fopen("user.txt","r");
	while(!feof(f)){
		fread(utp,sizeof(u),1,f);
		n++;
	}
	rewind(f);
	int k=0;
	while(!feof(f)){
		if(k==n-1){
			break;
		}
		
		fread(utp,sizeof(u),1,f);
		preorder[k].highscore=utp->highscore;
		strcpy(preorder[k].name,utp->name);
		strcpy(preorder[k].uid,utp->uid);
		strcpy(preorder[k].password,utp->password);
		preorder[k].totscore=utp->totscore;
		k++;
	}
	nouser=k;
	fclose(f);
    root=createbst(preorder,n-1);
	do{
		printf("\n1.USER LOGIN");
		printf("\n3.CREATE USER");
		printf("\n5.EXIT");
		printf("\nEnter your choice:");
		scanf("%d",&choice);
		switch(choice){
			case 1:{
				user_login();
				break;
			}
			case 3:{
				
				printf("\nEnter user name:");
				scanf("%s",username);
				printf("\nEnter Your name:");
				scanf("%s",na);
				printf("\nEnter login password:");
				scanf("%s",pass); 
				
				struct user *res=search(root,username);
				if(!res){
				root=insertion(root,username,na,pass,score);
				inds=0;
				writeuser(root);
				}
				else{
					printf("\nusername already taken");
				}
				printf("\nUser created");
				break;
			}
			case 5:{
				
				break;
			}
			default:{
				printf("\nwrong choice");
				break;
			}
		}
		
	}while(choice!=5);
	struct user1 fpre[nouser];
	int po;
	for(po=0;po<nouser;po++){
		fpre[po].highscore=preorder[po].highscore;
		strcpy(fpre[po].name,preorder[po].name);
		strcpy(fpre[po].uid,preorder[po].uid);
		strcpy(fpre[po].password,preorder[po].password);
		fpre[po].totscore=preorder[po].totscore;
	}
	FILE *fp1;
	fp1=fopen("user.txt","w");
	struct user1 *s1=fpre;
	struct user1 s2;
	fwrite(s1,sizeof(s2),nouser,fp1);
	fclose(fp1);
	return 0;
}
