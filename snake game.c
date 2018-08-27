#include<stdio.h>
#include <stdlib.h>
#include<time.h>
struct food{
int row,col;
char value;
};

struct snake{
int row,col;
char value;
struct snake *next;
struct snake *pre;
};

void insertionAtEnd(struct snake **head,struct snake **tail,int r,int c,char value);
void Display(struct snake *ptr);
void move(struct snake **head,struct snake **tail,char w,struct food *arr);
void insertionAtEnd1(struct snake *head,struct snake *tail,int r,int c,char value);
void generate_food(struct snake **head,struct snake **tail,struct food *arr,int c);
void clean_board(char board[][20],struct food *arr);
int main(){

struct snake *start=NULL,*tail=NULL;
insertionAtEnd(&start,&tail,3,2,'A');
insertionAtEnd(&start,&tail,4,2,'B');
insertionAtEnd(&start,&tail,5,2,'C');
insertionAtEnd(&start,&tail,6,2,'D');
insertionAtEnd(&start,&tail,7,2,'E');
insertionAtEnd(&start,&tail,8,2,'F');

///generating food
struct food arr[10];
int i;
    for(i=0;i<10;i++){
       generate_food(&start,&tail,arr,i);
       arr[i].value='G'+i;
    }

char board[20][20];
int j;
///boundary rows
for(i=0;i<20;i++){
    board[0][i]='-';
     board[19][i]='-';
}
///boundary cols
for(i=0;i<20;i++){
    board[i][0]='|';
     board[i][19]='|';
}

clean_board(board,arr);

struct snake *temp=start;
while(temp){
    board[temp->row][temp->col]=temp->value;
    temp=temp->next;
}
for(i=0;i<20;i++){
    for(j=0;j<20;j++){
        printf("%c",board[i][j]);
    }
    printf("\n");
}
int k;
for(k=0;k<1000;k++){
printf("move ");
char n;
scanf("%c",&n);
getchar();
clean_board(board,arr);
move(&start,&tail,n,arr);
system("CLS");
temp=start;
while(temp){
    board[temp->row][temp->col]=temp->value;
    temp=temp->next;
}
 for(i=0;i<20;i++){
    for(j=0;j<20;j++){
        printf("%c",board[i][j]);
    }
    printf("\n");
 }
}
return 0;
}
void insertionAtEnd(struct snake **head,struct snake **tail,int r,int c,char value){
    struct snake *new_node=(struct snake*)malloc(sizeof(struct snake));
    new_node->row=r;
    new_node->col=c;
    new_node->value=value;
    new_node->next=NULL;
    new_node->pre=NULL;
 if(*head==NULL){
    *head=new_node;
    *tail=new_node;
  }else{
     (*tail)->next=new_node;
     new_node->pre=(*tail);
     (*tail)=new_node;
  }

}
void Display(struct snake *ptr){
 while(ptr!=NULL){
   printf("%c",ptr->value);
   ptr=ptr->next;
 }
}

void move(struct snake **head,struct snake **tail,char w,struct food *arr){
    struct snake *temp=*tail;

if(w=='t'){
     temp=(*head)->next;
    while(temp&&(temp->row!=(*head)->row-1||temp->col!=(*head)->col)){
        temp=temp->next;
    }
    if(temp!=NULL){
        printf("\a");
        return ;
    }
    temp=(*tail);

    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
  if((*head)->row-1>=1){
     (*head)->row=(*head)->row-1;
   }else{
     (*head)->row=18;
     if((*head)->col+1<=18)
     (*head)->col=(*head)->col+1;
     else
        (*head)->col=1;
       }
}else if(w=='r'){
    temp=(*head)->next;
    while(temp&&(temp->col!=(*head)->col+1||temp->row!=(*head)->row)){
        temp=temp->next;
    }
    if(temp!=NULL){
        printf("\a");
        return ;
    }
    temp=(*tail);
    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
 if((*head)->col+1<=18){
     (*head)->col=(*head)->col+1;
   }else{
     (*head)->col=1;
     (*head)->row=(*head)->row+1;
       }
    }else if(w=='l'){

    temp=(*head)->next;
    while(temp&&(temp->col!=(*head)->col-1||temp->row!=(*head)->row)){
        temp=temp->next;
    }
    if(temp!=NULL){
        printf("\a");
        return ;
    }
    temp=(*tail);
    ///changing coordinates except of head node
    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
    if((*head)->col-1>=1){
     (*head)->col=(*head)->col-1;
     }else{
     (*head)->col=18;
     (*head)->row=(*head)->row+1;
       }
    }else if(w=='b'){

    temp=(*head)->next;
    while(temp&&(temp->row!=(*head)->row+1||temp->col!=(*head)->col)){
        temp=temp->next;
    }
    if(temp!=NULL){
        printf("\a");
        return ;
    }
    temp=(*tail);

    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
    if((*head)->row+1<=18){
     (*head)->row=(*head)->row+1;
     }else{
     (*head)->row=1;
     (*head)->col=(*head)->col+1;
       }
    }else{
     printf("\a");
    }
    int i,c=-1;

    for(i=0;i<10;i++){
        if(((*head)->row==arr[i].row)&&((*head)->col==arr[i].col)){
            c=i;
            break;
        }
    }

    if(c!=-1){
        if(arr[c].value==((*tail)->value+1))
       insertionAtEnd(head,tail,(*tail)->row+1,(*tail)->col,arr[c].value);
       else{
        temp=(*tail);
        (*tail)=(*tail)->pre;
        (*tail)->next=NULL;
        free(temp);
       }
       generate_food(head,tail,arr,c);
    }

}

void generate_food(struct snake **head,struct snake **tail,struct food *arr,int c){
srand(time(0)*c);
arr[c].value=(*tail)->value+1;//(rand()%((*tail)->value+5-(*tail)->value+1)+(*tail)->value);
again:
arr[c].row=(rand()%(18-1+1)+1);
arr[c].col=(rand()%(18-1+1)+1);
struct snake *temp=(*head);
while(temp){
    if(temp->row==arr[c].row||temp->col==arr[c].col){
        goto again;
    }
    temp=temp->next;
}
}

void clean_board(char board[][20],struct food *arr){
    int i,j;
for(i=1;i<19;i++){
    for(j=1;j<19;j++){
        board[i][j]=' ';
    }
}
for(i=0;i<10;i++){
    board[arr[i].row][arr[i].col]=arr[i].value;
}
}
