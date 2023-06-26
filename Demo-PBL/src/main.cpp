#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LEN 200
#define TABLE_SIZE 9997
#define MAX_CHOICE 9
typedef struct Node Node;

int nums[TABLE_SIZE];
int numSize=0;
int numberOfWords=0;// so luong tu trong tu dien
struct Node{
    char vocab[MAX_LEN];
    char meaning[MAX_LEN];
    char type[MAX_LEN];
    Node *next;
};
Node * hashTable[TABLE_SIZE];

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

int HashFunction( char newword[]){

    int c, i=0, base=131, hash=0;

    while (newword[i] != '\0'){
        c = newword[i];
        hash = (hash  *base+ c) % TABLE_SIZE +1; 
        i++;
    }
    return hash;
}
void InsertNodeToHashTable(Node *newword){

    int index = HashFunction(newword->vocab);

    if (hashTable[index] != NULL)
        newword->next= hashTable[index];
    else
        nums[++numSize]=index; // Thong ke nhung hashCode da duoc su dung
    
    hashTable[index]= newword;

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
                    type[j++]= line[i++];
                
                strncpy(temp->type, type,j--);

                // Tách phần từ loại
                i++; j=0;
                while (line[i] != '\n')
                    meaning[j++]= line[i++];
                strncpy(temp->meaning, meaning,j--);

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
                fprintf(p, "%s;%s;%s\n", temp->vocab, temp->type, temp->meaning);
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
    printf("\nBạn cần cập nhập lại nội dung nào của từ?\n");
    printf("1. Nghĩa của từ\n");
    printf("2. Kiểu của từ\n");
    printf("\t** Nhập lựa chọn: ");

    int choice; 
    scanf("%d", &choice);
    printf("\t** Hãy nhập thay đổi:  \n");
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
    printf("\n\tCập nhập lại từ điển THÀNH CÔNG !\n");
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
    for (int i=0; i<=128; ++i)
    printf("-");
    printf("+");


    printf("\n| %-6s| %-30s| %-30s | %-54s |\n","STT","Tu vung","Loai tu","Nghia cua tu");
    printf("| %-6s| %-30s| %-30s | %-54s |\n"," "," "," "," ");
    printf("|");
    for (int i=0; i<=128; ++i)
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

                printf("| %-6d| %-30s| %-30s | %-54s |\n",cnt++, temp->vocab, temp->type, temp->meaning);
                printf("|");
                for (int i=0; i<=6; ++i)
                    printf("-");
                printf("|");
                for (int i=0; i<=30; ++i)
                    printf("-");
                printf("|");
                for (int i=0; i<32; ++i)
                    printf("-");
                printf("|");
                for (int i=0; i<=55; ++i)
                    printf("-");
                printf("|");
                printf("\n");
                temp = temp->next;

            }
        }
    }
    printf("+");
    for (int i=0; i<=128; ++i)
    printf("-");
    printf("+");
}


void swap(int &a, int &b){
    int temp= a;
    a=b;
    b= temp;
}

void PlayGame(int numberOfQuestions){
    if (numberOfQuestions > numSize){
        printf("\tKhông đủ số lượng từ !\n");
        return;
    }

    srand(time(NULL));
    printf("\t\t\n\n** TRÒ CHƠI BẮT ĐẦU **\n\n\n");
    int cnt=1, right=0;

    while (cnt <= numberOfQuestions){

        int x = (rand() % (numSize - cnt + 1)) + cnt;
        Node *temp = hashTable[nums[x]];

        // Lấy chiều dài của linkedList
        int listLen=0;
        while (temp!= NULL){
            listLen++;
            temp= temp-> next;
        }

        int y= rand()%listLen;
        temp = hashTable[nums[x]];
        while (y){
            temp= temp->next;
            y--;
        }

        char answer[MAX_LEN];
        char askedWord[MAX_LEN];
        strcpy(askedWord, temp->vocab);
        strcpy(answer, temp->vocab);

        // Chọn 1 vị trí ngẫu nhiên để ẩn đi
        int random_index= rand() %strlen(askedWord);
        printf("Câu %d:\t\t",cnt);
        for (int k = 0; k < strlen(askedWord); ++k){
            if (k == random_index)
                printf("_");
            else
                printf("%c", askedWord[k]);
        }

        fflush(stdin);
        printf("\n** Điền từ còn thiếu: ");
        answer[random_index]= getchar();

        if (Search(answer) != NULL){
            printf("\n\t BẠN ĐÃ TRẢ LỜI ĐÚNG!\n\n");
            right++;
        }
        else
            printf("\t BẠN ĐÃ TRẢ LỜI SAI!\n\n");

        printf("\t --->  %-20s: %-20s \t (%s) \n\n\n", temp->vocab, temp->meaning, temp->type);

        swap(nums[x], nums[cnt]); // So ngau nhien da su dung thi dua toi truoc (de lan sau ko lay trung)
        cnt++; // số lượng số đã lấy
        
    }

    printf("\nBẠN ĐÃ TRẢ LỜI ĐÚNG %d/%d CÂU!\n",right,numberOfQuestions);
}

void TimKiem(char word[]){
     printf("+");
    for (int i=0; i<=120; ++i)
    printf("-");
    printf("+");


    printf("\n| %-30s| %-30s | %-54s |\n","Tu Vung","Loai tu","Nghia cua tu");
    printf("| %-30s| %-30s | %-54s |\n"," "," "," ");
    printf("|");
    for (int i=0; i<=120; ++i)
    printf("-");
    printf("|");
    printf("\n");

    for (int i = 0; i < TABLE_SIZE; ++i){

        if (hashTable[i] == NULL)
            continue;

        else{
            Node *temp=hashTable[i];
            if (strstr(temp->vocab,word)){

                printf("| %-30s| %-30s | %-54s |\n", temp->vocab, temp->type, temp->meaning);
                printf("|");
                for (int i=0; i<=30; ++i)
                    printf("-");
                printf("|");
                for (int i=0; i<32; ++i)
                    printf("-");
                printf("|");
                for (int i=0; i<=55; ++i)
                    printf("-");
                printf("|");
                printf("\n");
                temp = temp->next;

            }
        }
    }
    printf("+");
    for (int i=0; i<=120; ++i)
    printf("-");
    printf("+");
}
