#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LEN 200
#define TABLE_SIZE 26
#define MAX_CHOICE 8
typedef struct Node Node;


int NumberOfWords=0;// so luong tu trong tu dien - global variable
struct Node{
    char vocab[MAX_LEN];
    char meaning[MAX_LEN];
    char type[MAX_LEN];
    Node *next;
};
void DeleteBuff(char word[]){
    int i=0;
    while (word[i] != '\n') i++;
    word[i]='\0';
}
Node * HashTable[TABLE_SIZE];
Node *CreateNode(char[], char[], char[]);
int HashFunction( char[]);
void ReadFile();
void WriteFile();
void InsertNodeToHashTable(Node *);
bool DeleteNode(char[]);
void Change(char[]);
Node* FindAWord(char[]);
void Searching(char[]);
void PrintHashTable();
void PlayGame();

int main(){
    
    int choice;
    char word[MAX_LEN];
    ReadFile();

    do
    {
        choice=-1;
        system("clear");
        printf("\n\n\t\tTU DIEN TIENG ANH\n\n");
        printf("\t1.   Them tu moi \n");
        printf("\t2.   Xoa di mot tu\n");
        printf("\t3.   Sua thong tin tu vung\n");
        printf("\t4.   In danh sach tu vung \n");
        printf("\t5.   Tra nghia cua tu\n");
        printf("\t6.   Tro choi do chu\n");
        printf("\t7.   Sao luu du lieu ra file\n");
        printf("\t8.   Tim tu trong tu dien\n");
        printf("\t0.   Ket thuc chuong trinh \n\n");
        printf("Hay nhap lua chon tren menu: ");
        scanf("%d",&choice);
        
        while (choice < 0 || choice > MAX_CHOICE)
        {
            fflush(stdin);
            printf("Vui long chon lai so phu hop voi menu: ");
            scanf("%d",&choice);

        }

        switch (choice){
        case 0:
            break;
        case 1:{
            char vocab[MAX_LEN], meaning[MAX_LEN], type[MAX_LEN];
            fflush(stdin);
            printf("Nhap tu moi: ");
            fgets(vocab,MAX_LEN,stdin);
            DeleteBuff(vocab);
            if (FindAWord(vocab) != NULL ){
                printf("Tu nay da co trong tu dien!\n");
                break;
            }

            printf("Nhap nghia cua tu: ");
            fgets(meaning,MAX_LEN,stdin);
            DeleteBuff(meaning);

            printf("Nhap kieu cua tu: ");
            fgets(type,MAX_LEN,stdin);
            DeleteBuff(type);

            InsertNodeToHashTable(CreateNode(vocab,meaning,type));
            printf("\n\nBan da them tu THANH CONG!\n\n");
            break;
        }
        case 2:
            fflush(stdin);
            printf("Nhap tu can xoa: ");
            fgets(word,MAX_LEN,stdin);
            DeleteBuff(word);
            if (DeleteNode(word)){
            printf("DA XOA TU THANH CONG !\n");
            }
            else{
            printf("KHONG CO TU NAY TRONG TU DIEN !\n");
            }
            break;
        case 3:
            fflush(stdin); 
            char editWord[MAX_LEN];
            printf("Hay nhap tu can thay doi thong tin: ");
            fgets(editWord,MAX_LEN,stdin);
            DeleteBuff(editWord);
            Change(editWord);
            break;
        case 4:
            PrintHashTable();
            break;
        case 5:{
            fflush(stdin);
            printf("Nhap tu can tra nghia: ");
            fgets(word,MAX_LEN,stdin);
            DeleteBuff(word);
            printf("\n");
            Node* res= FindAWord(word);

            if (res != NULL)
            printf("--->  %-20s: %-20s %-10s \n", res->vocab, res->meaning, res->type);
            else
            printf("---> KHONG CO TU NAY TRONG TU DIEN\n");
            break;
        }
        case 6:
            PlayGame();
            break;
        case 7:
            WriteFile();
            break;
        case 8:
            fflush(stdin);
            printf("Nhap cum tu can tim kiem: ");
            char phrase[MAX_LEN];
            fgets(phrase,MAX_LEN,stdin);
            DeleteBuff(phrase);
            printf("Cac tu vung chua cum tu tren la:\n");
            Searching(phrase);
            break;
        }

        if (choice !=0){
            fflush(stdin);
            printf("\nVui long nhan phim Enter de tiep tuc! ");
            getchar();
        }
        
    } 
    while (choice != false);
}

int HashFunction( char newword[]){
    
    return ( newword[0] -'a');

}

void ReadFile(){
    FILE *p= fopen("./input.txt","r");

    if (p)
    while ( !feof(p) )
    {
            char line[MAX_LEN],vocab[MAX_LEN],meaning[MAX_LEN],type[MAX_LEN];
            Node *temp = (Node *)malloc(sizeof *temp);

            fgets(line, MAX_LEN, p);
            // tach tu
            int i=0,j=0;
            // Tach vocab
            while (line[i] != ';'){
                vocab[j++]= line[i];
                i++;
            }
            strncpy(temp->vocab, vocab,j--);
            // Tach nghia
            i++; j=0;
            while (line[i] != ';'){
                meaning[j++]= line[i];
                i++;
            }
            strncpy(temp->meaning, meaning,j--);
            // Tách từ loại
            i++; j=0;
            while (line[i] != '\n'){
                type[j++]= line[i];
                i++;
            }
            strncpy(temp->type, type,j--);
            InsertNodeToHashTable(temp);
            NumberOfWords++;

           
    }

    fclose(p);
}

void WriteFile(){
    FILE *p= fopen("./input.txt","w");
    for (int i = 0; i < TABLE_SIZE; ++i){
        if (HashTable[i] == NULL)
            continue;

        else{
            Node *temp=HashTable[i];
            while (temp != NULL){
                fprintf(p, "%s;%s;%s\n", temp->vocab, temp->meaning, temp->type);
                temp = temp->next;
            }
        }
    }
    fclose(p);

}

Node *CreateNode(char vocab[], char meaning[], char type[]){
    // char vocab[MAX_LEN], meaning[MAX_LEN],type[MAX_LEN];
    Node *temp= (Node*)malloc(sizeof *temp);

    strcpy(temp->vocab, vocab);
    strcpy(temp->meaning, meaning);
    strcpy(temp->type, type);

    temp->next = NULL;
    NumberOfWords++;
    
    return temp;
}

void InsertNodeToHashTable(Node *newword){

    int index = HashFunction(newword->vocab);

    if (HashTable[index] != NULL){
        newword->next= HashTable[index];
    }
    // Connect this new Node to the front of the chain
    // Update the chain
    HashTable[index]= newword;

}

Node* FindAWord(char word[]){
    int index = HashFunction(word);
    // printf("%d %s     %s",index,HashTable[index]->vocab,word);

    if (HashTable[index] != NULL)
    {
        Node *temp = HashTable[index];
        // printf("%d",strcmp(temp->vocab, word) );

        while (temp != NULL && strcmp(temp->vocab, word) != 0){
            temp = temp->next;
        }
        // printf("%s\n",temp->vocab);

        if (temp != NULL){
            return temp;
        }
    }
    return NULL;
}

void Change(char editWord[]){

    Node *changeNode= (Node *)malloc(sizeof (*changeNode));
    if (FindAWord(editWord) == NULL ){
        printf("Khong co tu nay trong tu dien\n");
        return;
    }
    else
    changeNode= FindAWord(editWord);
    
    
    printf("%-20s %-20s %-20s\n", changeNode->vocab, changeNode->meaning, changeNode->type);
    printf("\nBan can cap nhap lai noi dung nao cua tu?\n");
    printf("1. Nghia cua tu\n");
    printf("2. Kieu cua tu\n");
    printf("Nhap lua chon: ");

    int choice; 
    scanf("%d", &choice);
    printf("Hay nhap thay doi:  \n");
    char word[MAX_LEN];
    fflush(stdin);
    switch (choice)
    {
    case 1:
        fgets(word,MAX_LEN,stdin);
        DeleteBuff(word);
        strcpy(changeNode->meaning, word);
        break;
    case 2:
        fgets(word,MAX_LEN,stdin);
        DeleteBuff(word);
        strcpy(changeNode->type, word);
        break;
    }
    printf("\nCap nhap lai tu dien THANH CONG !\n");
    return;
}

bool DeleteNode(char word[]){
    int index= HashFunction(word);

    if (HashTable[index]==NULL){
        return false;
    }

    Node *temp= HashTable[index];
    Node *pre= NULL;

    // Neu tu dau tien la tu can xoa
    if ( strcmp(temp->vocab, word) ==0){
        HashTable[index] = temp->next;
        free(temp);
    }
    else{ // Duyet cac tu con lai trong chuoi 
        while (temp != NULL && strcmp(temp->vocab, word) !=0 ){
            pre=temp;
            temp=temp->next;
        }

        if (temp == NULL){
            return false;
        }

        pre->next= temp->next;
        free(temp);
    }
    NumberOfWords--;  
    return true;
}

void Searching(char phrase[]){
    printf("+");
    for (int i=0; i<=66; ++i)
    printf("-");
    printf("+");

    printf("\n| %-5s| %-20s| %-20s| %-15s|\n","STT","Tu Vung","Nghia cua tu","Loai tu");
    printf("| %-5s| %-20s| %-20s| %-15s|\n"," "," "," "," ");
    printf("|");
    for (int i=0; i<=66; ++i)
    printf("-");
    printf("|");
    printf("\n");
    int cnt=1;
    for (int i = 0; i < TABLE_SIZE; ++i){
        if (HashTable[i] == NULL)
            continue;

        else{
            Node *temp=HashTable[i];
            while (temp != NULL){
                if (strstr(temp->vocab,phrase) != NULL){
                printf("| %-5d| %-20s| %-20s| %-15s|\n", cnt++,temp->vocab, temp->meaning, temp->type);

                }
                temp = temp->next;
            }
        }
    }
    printf("+");
    for (int i=0; i<=66; ++i)
    printf("-");
    printf("+");
}

void PrintHashTable(){
    printf("+");
    for (int i=0; i<=66; ++i)
    printf("-");
    printf("+");


    printf("\n| %-5s| %-20s| %-20s| %-15s|\n","STT","Tu Vung","Nghia cua tu","Loai tu");
    printf("| %-5s| %-20s| %-20s| %-15s|\n"," "," "," "," ");
    printf("|");
    for (int i=0; i<=66; ++i)
    printf("-");
    printf("|");
    printf("\n");
    int cnt=1;
    for (int i = 0; i < TABLE_SIZE; ++i){

        if (HashTable[i] == NULL)
            continue;

        else{
            Node *temp=HashTable[i];
            while (temp != NULL){

                printf("| %-5d| %-20s| %-20s| %-15s|\n", cnt++,temp->vocab, temp->meaning, temp->type);
                temp = temp->next;

            }
        }
    }
    printf("+");
    for (int i=0; i<=66; ++i)
    printf("-");
    printf("+");
}



void PlayGame(){

    srand(time(NULL));
    printf("\t\tTRO CHOI BAT DAU!\n\n\n");
    int cnt=0;

    for (int i = 0; i < TABLE_SIZE; ++i){

        if (HashTable[i] == NULL)
            continue;

        else{
            Node *temp=HashTable[i];
            while (temp != NULL){
                char YourWord[MAX_LEN]; 
                char AskedWord[MAX_LEN]; strcpy(AskedWord,temp->vocab);

                int x=rand()% strlen(AskedWord);
                printf("\t");
                for (int k=0; k<strlen(AskedWord); ++k){

                    if (k==x){
                    YourWord[k]= '\0';
                    printf("_");
                    }

                    else{
                    YourWord[k]= AskedWord[k];
                    printf("%c",AskedWord[k]);
                    }

                }
                fflush(stdin);
                printf("\nDien tu con thieu: ");
                YourWord[x] = getchar();

                 if (  FindAWord(YourWord) != NULL ){
                    printf("\t---> BAN TRA LOI DUNG!\n\n\n");
                    cnt++;
                }
                else
                printf("\t---> BAN TRA LOI SAI!\n\n\n");

                temp = temp->next;

            }
        }
    }

    printf("\nBAN DA TRA LOI DUNG %d/%d CAU!\n",cnt,NumberOfWords);
}