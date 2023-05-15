#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LEN 200
#define TABLE_SIZE 1000
#define MAX_CHOICE 8
typedef struct Node Node;

int nums[TABLE_SIZE];
int numberOfWords=0;// so luong tu trong tu dien
struct Node{
    char vocab[MAX_LEN];
    char meaning[MAX_LEN];
    char type[MAX_LEN];
    Node *next;
};
Node * hashTable[TABLE_SIZE];

Node *CreateNode(char[], char[], char[]);
int HashFunction( char[]);
void InsertNodeToHashTable(Node *);
void ReadFile();
void WriteFile();
bool DeleteNode(char[]);
void Update(char[]);
Node* Search(char[]);
void PrintHashTable();
void PlayGame(int);
void DeleteNewlineCharacter(char[]);
void Input(char[]);
void swap(int &, int &);
// Do khi nhập từ mới từ bàn phím, chúng bị lưu lẫn cả kí tự xuống dòng

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
        printf("\t4.   Tra nghia cua tu\n");
        printf("\t5.   In danh sach tu vung \n");
        printf("\t6.   Sao luu du lieu ra file\n");
        printf("\t7.   Tro choi do chu\n");
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
            printf("Hay nhap tu moi: ");
            Input(vocab);

            if (Search(vocab) != NULL ){
                printf("Tu nay da co trong tu dien!\n");
                break;
            }

            printf("Nhap nghia cua tu: ");
            Input(meaning);
            printf("Nhap kieu cua tu: ");
            Input(type);
            Node *node= CreateNode(vocab,meaning,type);
            InsertNodeToHashTable(node);
            printf("\n\nBan da them tu THANH CONG!\n\n");
            break;
        }
        case 2:
            printf("Hay nhap tu can xoa : ");
            Input(word);
            if (DeleteNode(word))
                printf("DA XOA TU THANH CONG !\n"); 
            else
                printf("KHONG CO TU NAY TRONG TU DIEN !\n");
            break;
        case 3:
            printf("Hay nhap tu can thay doi: ");
            Input(word);
            Update(word);
            break;
        case 4:{
            printf("Hay nhap tu can tra nghia: ");
            Input(word);
            printf("\n");
            Node* res= Search(word);

            if (res != NULL)
            printf("--->  %-20s: %-20s %-10s \n", res->vocab, res->meaning, res->type);
            else
            printf("---> KHONG CO TU NAY TRONG TU DIEN\n");
            break;
        }
        case 5:
            PrintHashTable();
            break;
        case 6:
            WriteFile();
            break;
        case 7:
            printf("\n Level 1: 5 cau\n Level 2: 10 cau\n Level 3: 20 cau\n");
            int level; 
            do{
            printf("\tHay chon level tro choi: ");
            scanf("%d",&level);
            }
            while (level <0 || level >3);
            PlayGame(level*5);
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
    
    unsigned long hash = 5381;
    int c,i=0;

    while (newword[i] != '\0'){
        c = newword[i];
        hash = (((hash << 5) + hash) + c)%1000; // hash * 33 + c 
        i++;
    }

    return hash;

}

void ReadFile(){
    FILE *p= fopen("./input.txt","r");

    if (p)
    while ( !feof(p) )
    {
            char line[MAX_LEN],vocab[MAX_LEN],meaning[MAX_LEN],type[MAX_LEN];
            Node *temp = (Node *)malloc(sizeof *temp);
            // Đọc vào 1 line
            fgets(line, MAX_LEN, p);

            // if (line[1]!='\0'){
                // Tách phần từ vựng
                int i=0,j=0;
                while (line[i] != ';')
                    vocab[j++]= line[i++];

                strncpy(temp->vocab, vocab,j--);

                // Tách phần nghĩa
                i++; j=0;
                while (line[i] != ';')
                    meaning[j++]= line[i++];
                
                strncpy(temp->meaning, meaning,j--);

                // Tách phần từ loại
                i++; j=0;
                while (line[i] != '\n')
                    type[j++]= line[i++];
                strncpy(temp->type, type,j--);

                numberOfWords++;
                InsertNodeToHashTable(temp);
            // }
           
    }

    fclose(p);
}

void WriteFile(){
    FILE *p= fopen("./input.txt","w");
    for (int i = 0; i < TABLE_SIZE; ++i){
        if (hashTable[i] == NULL)
            continue;

        else{
            Node *temp=hashTable[i];
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
    numberOfWords++;
    
    return temp;
}

void InsertNodeToHashTable(Node *newword){

    int index = HashFunction(newword->vocab);

    if (hashTable[index] != NULL)
        newword->next= hashTable[index];
    else
        nums[numberOfWords]=index; // Thong ke nhung hashCode da duoc su dung
    
    // Connect this new Node to the front of the chain
    // Update the chain
    hashTable[index]= newword;

}

Node* Search(char word[]){
    int index = HashFunction(word);

    if (hashTable[index] != NULL){
        Node *temp = hashTable[index];
        // Nếu chưa tìm được từ -> trỏ temp đến Node tiếp theo 
        while (temp != NULL && strcmp(temp->vocab, word) != 0){
            temp = temp->next;
        }
        // Nếu tìm được từ -> trả về từ đó
        if (temp != NULL){
            return temp;
        }
    }
    // Nếu không tìm được từ -> trả về NULL
    return NULL;
}

void Update(char editWord[]){

    Node *changeNode= (Node *)malloc(sizeof (*changeNode));
    if (Search(editWord) == NULL ){
        printf("Khong co tu nay trong tu dien\n");
        return;
    }
    else
    changeNode= Search(editWord);
    
    
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
    switch (choice){

    case 1:
        fgets(word,MAX_LEN,stdin);
        DeleteNewlineCharacter(word);
        strcpy(changeNode->meaning, word);
        break;
    case 2:
        fgets(word,MAX_LEN,stdin);
        DeleteNewlineCharacter(word);
        strcpy(changeNode->type, word);
        break;
    }
    printf("\nCap nhap lai tu dien THANH CONG !\n");
    return;
}

bool DeleteNode(char word[]){
    int index= HashFunction(word);

    if (hashTable[index]==NULL){
        return false;
    }

    Node *temp= hashTable[index];
    Node *pre= NULL;

    // Neu tu dau tien la tu can xoa
    if ( strcmp(temp->vocab, word) ==0){
        hashTable[index] = temp->next;
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
    numberOfWords--;  
    return true;
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

        if (hashTable[i] == NULL)
            continue;

        else{
            Node *temp=hashTable[i];
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

void swap(int &a, int &b){
    int temp= a;
    a=b;
    b= temp;
}

void PlayGame(int numberOfQuestions){

    srand(time(NULL));
    printf("\t\tTRO CHOI BAT DAU!\n\n\n");
    int cnt=1, right=0;

    while (cnt <= numberOfQuestions){
        // Lấy các từ ngãu nhiên không lặp lại
        int x = rand() % (numberOfWords - cnt + 1) + cnt;
        Node *temp = hashTable[nums[x]];
        swap(nums[x], nums[cnt]); // So ngau nhien da su dung thi dua toi truoc (de lan sau ko lay trung)
        cnt++; // số lượng số đã lấy

        char answer[MAX_LEN];
        char askedWord[MAX_LEN];
        strcpy(askedWord, temp->vocab);
        strcpy(answer, temp->vocab);

        // Chọn 1 vị trí ngẫu nhiên để ẩn đi
        int random_index= rand() %strlen(askedWord);
        printf("\t");
        for (int k = 0; k < strlen(askedWord); ++k){
            if (k == random_index)
                printf("_");
            else
                printf("%c", askedWord[k]);
        }

        fflush(stdin);
        printf("\nDien tu con thieu: ");
        answer[random_index] = getchar();

        if (Search(answer) != NULL){
            printf("\t---> BAN TRA LOI DUNG!\n\n\n");
            right++;
        }
        else
            printf("\t---> BAN TRA LOI SAI!\n\n\n");
        
    }

    printf("\nBAN DA TRA LOI DUNG %d/%d CAU!\n",right,numberOfQuestions);
}

void DeleteNewlineCharacter(char word[]){
    int i=0;
    while (word[i] != '\n') i++;
    word[i]='\0';
}

void Input(char word[]){
    fflush(stdin); 
    fgets(word,MAX_LEN,stdin);
    DeleteNewlineCharacter(word);
}