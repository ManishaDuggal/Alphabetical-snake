#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include<conio.h>
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
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void insertionAtEnd(struct snake **head,struct snake **tail,int r,int c,char value);
void Display(struct snake *ptr);
void move(struct snake **head,struct snake **tail,char w,struct food *arr);
void insertionAtEnd1(struct snake *head,struct snake *tail,int r,int c,char value);
void generate_food(struct snake **head,struct snake **tail,struct food *arr,int c);
void clean_board(char board[][20],struct food *arr);
void write_in_file(struct snake *head,struct snake *tail,struct food *arr);
void file_handling(struct snake **head,struct snake **tail,struct food *arr);
int main(){
system("COLOR F0");
struct snake *start=NULL,*tail=NULL;
struct food arr[10];
FILE *fp=fopen("snake.c","r");
char check=getc(fp);
fclose(fp);
if(check!=EOF){
    printf("\nDo you wanna continue with existing game y/n?");
    char ch;
    scanf(" %c",&ch);
    if(ch=='y'){
     file_handling(&start,&tail,arr);
    }else{
    insertionAtEnd(&start,&tail,3,2,'A');
    insertionAtEnd(&start,&tail,4,2,'B');
    insertionAtEnd(&start,&tail,5,2,'C');
    insertionAtEnd(&start,&tail,6,2,'D');
    insertionAtEnd(&start,&tail,7,2,'E');
    insertionAtEnd(&start,&tail,8,2,'F');

      int i;
    for(i=0;i<10;i++){
       generate_food(&start,&tail,arr,i);
       arr[i].value='Z'+i;
    }
       }
}else{

    insertionAtEnd(&start,&tail,3,2,'A');
    insertionAtEnd(&start,&tail,4,2,'B');
    insertionAtEnd(&start,&tail,5,2,'C');
    insertionAtEnd(&start,&tail,6,2,'D');
    insertionAtEnd(&start,&tail,7,2,'E');
    insertionAtEnd(&start,&tail,8,2,'F');

      int i;
     for(i=0;i<10;i++){
       generate_food(&start,&tail,arr,i);
       arr[i].value='G'+i;
      }
    }


char board[20][20];

clean_board(board,arr);

struct snake *temp=start;
while(temp){
    board[temp->row][temp->col]=temp->value;
    temp=temp->next;
}
int j,i;
for(i=0;i<20;i++){
    for(j=0;j<20;j++){
        printf("%c",board[i][j]);
    }
    printf("\n");
}
int k;
char n;
n='w';
while(1){
        if(start->next==NULL){
            system("CLS");
            printf("You Lost");
           return 0;
        }
        if(tail->value=='Z'){
            system("CLS");
            printf("Congratulations for winning");
            FILE *filepoint=fopen("snake.c","w");
             fclose(filepoint);
            break;
        }
if(kbhit()){
    n=getch();
}
if(n=='q'){
    printf("\nDo you wanna save state?y/n");
    getchar();
   n=getchar();
   if(n=='y'){
    write_in_file(start,tail,arr);
   }
    return 0;
}
clean_board(board,arr);
delay(459);
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
    struct snake *temp;
    int flag=0;

if(w=='w'){
     temp=(*head)->next;
     if((*head)->row-1>=1){
    while(temp){
        if(temp->row==(*head)->row-1&&temp->col==(*head)->col){
            flag=1;
            break;
        }
        temp=temp->next;
            }

        if(flag==1){
        printf("1\a");
        printf("flag1");
        return ;
                 }

    temp=(*tail);
    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
      (*head)->row=(*head)->row-1;
     }else{
         while(temp){
          if(temp->row==18&&temp->col==(*head)->col){
            flag=1;
            break;
          }
         temp=temp->next;
         }

        if(flag==1){
        printf("2\a");
        printf("flag1");
        return ;
          }

    temp=(*tail);
    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }

    (*head)->row=18;
     if((*head)->col+1<=18)
     (*head)->col=(*head)->col+1;
     else
        (*head)->col=1;
     }

}else if(w=='d'){

 if((*head)->col+1<=18){
        temp=(*head)->next;
    while(temp){
        if(temp->col==(*head)->col+1&&temp->row==(*head)->row){
            flag=1;
            break;
        }
        temp=temp->next;
    }
    if(flag==1){
        printf("3\a");
        return;
    }
    temp=(*tail);
    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
     (*head)->col=(*head)->col+1;
   }else{
       temp=(*head)->next;
    while(temp){
        if(temp->col==1&&temp->row==(*head)->row){
            flag=1;
            break;
        }
        temp=temp->next;
    }
    if(flag==1){
        printf("4\a");
        return;
    }
    temp=(*tail);
    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
     (*head)->col=1;
     (*head)->row=(*head)->row+1;
       }
    }else if(w=='a'){


    if((*head)->col-1>=1){

     temp=(*head)->next;
    while(temp){
        if(temp->col==(*head)->col-1&&temp->row==(*head)->row){
            flag=1;
            break;
        }
        temp=temp->next;
    }
    if(flag==1){
        printf("5\a");
        return;
    }
    temp=(*tail);

    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
     (*head)->col=(*head)->col-1;
     }else{
         temp=(*head)->next;
    while(temp){
        if(temp->col==18&&temp->row==(*head)->row){
            flag=1;
            break;
        }
        temp=temp->next;
    }
    if(flag==1){
        printf("6\a");
        return;
    }
    temp=(*tail);

    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
     (*head)->col=18;
     (*head)->row=(*head)->row+1;
       }
    }else if(w=='s'){

    if((*head)->row+1<=18){
      temp=(*head)->next;
    while(temp){
        if(temp->row==(*head)->row+1&&temp->col==(*head)->col){
            flag=1;
            break;
        }
        temp=temp->next;
    }
    if(flag==1){
        printf("7\a");
        return ;
    }
    temp=(*tail);

    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
     (*head)->row=(*head)->row+1;
     }else{
      temp=(*head)->next;
    while(temp){
        if(temp->row==1&&temp->col==(*head)->col){
            flag=1;
            break;
        }
        temp=temp->next;
    }
    if(flag==1){
        printf("8\a");
        return ;
    }
    temp=(*tail);

    while(temp->pre){
       temp->row=temp->pre->row;
       temp->col=temp->pre->col;
       temp=temp->pre;
    }
     (*head)->row=1;
     (*head)->col=(*head)->col+1;
       }
    }else{
     printf("9\a");
     printf("hello dear");
     return ;
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
arr[c].value=(*tail)->value+1;
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

for(i=1;i<19;i++){
    for(j=1;j<19;j++){
        board[i][j]=' ';
    }
}
for(i=0;i<10;i++){
    board[arr[i].row][arr[i].col]=arr[i].value;
}
}
void write_in_file(struct snake *head,struct snake *tail,struct food *arr){
struct snake *ptr=head;
FILE *fp;
fp=fopen("snake.c","w");
 while(ptr){
   fputc(ptr->row+'0',fp);
   fputc(',',fp);
   fputc(ptr->col+'0',fp);
   fputc(',',fp);
   fputc(ptr->value,fp);
   fputc('|',fp);
   ptr=ptr->next;
 }
 fseek(fp, -1L, SEEK_CUR);
 fputc('$',fp);
 int i=0;
  for(i=0;i<10;i++){
  char buffer[3];
  itoa(arr[i].row,buffer,10);
  fprintf(fp,"%s",buffer);
   fputc(',',fp);
   itoa(arr[i].col,buffer,10);
   fprintf(fp,"%s",buffer);
   fputc(',',fp);
   fputc(arr[i].value,fp);
   fputc('|',fp);
 }
 fseek(fp, -1L, SEEK_CUR);
 fputc(' ',fp);
 fclose(fp);
}
void file_handling(struct snake **head,struct snake **tail,struct food *arr){
FILE *fp;

fp=fopen("snake.c","r");
int no;
char c=getc(fp);
list:
   no=0;
  while(c!=','){
  no=no*10+(c-'0');
  c=getc(fp);
  }
  int x=no;
  c=getc(fp);
  no=0;
  while(c!=','){
  no=no*10+(c-'0');
  c=getc(fp);
  }
 int y=no;
  c=getc(fp);
  char value=c;
  c=getc(fp);
  insertionAtEnd(head,tail,x,y,value);

if(c=='|'){
c=getc(fp);
goto list;
}
if(c=='$'){
int i=0;
c=getc(fp);
food:
   no=0;
  while(c!=','){
  no=no*10+(c-'0');
  c=getc(fp);
  }
  arr[i].row=no;
  c=getc(fp);
  no=0;
  while(c!=','){
  no=no*10+(c-'0');
  c=getc(fp);
  }
  arr[i].col=no;
  c=getc(fp);
  arr[i++].value=c;
  c=getc(fp);

if(c=='|'){
c=getc(fp);
goto food;
}
}
fclose(fp);

}
