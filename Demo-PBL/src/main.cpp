#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int main(){
    
    int choice;
    char word[MAX_LEN];
    ReadFile();

    do
    {
        choice=-1;
        system("clear");

        printf("\n\n\t\t\t\t\t\t   HỌC TỪ VỰNG TIẾNG ANH THÔNG QUA TRÒ CHƠI\n\n\t");
        for (int i=1; i<=150; ++i)
        printf("-");
        
        printf("\n\n\t DANH SÁCH THAO TÁC\n\n\t+");
        for (int i=1; i<=40; ++i)
        printf("-");
        printf("+\n\t|%40s|\n"," ");
        printf("\t| 1.   Thêm từ mới                       |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 2.   In danh sách từ vựng              |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 3.   Sửa thông tin từ vựng             |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 4.   Tra nghĩa của từ                  |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 5.   Xóa một từ                        |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 6.   Tìm kiếm                          |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 7.   Trò chơi đố chữ                   |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 8.   Sao lưu dữ liệu ra file           |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 0.   Kết thúc chương trình             |\n");
        printf("\t|%40s|\n\t+"," ");
        for (int i=1; i<=40; ++i)
        printf("-");
        printf("+\n\nHãy nhập lựa chọn trên menu: ");
        scanf("%d",&choice);
        
        while (choice < 0 || choice > MAX_CHOICE)
        {
            fflush(stdin);
            printf("Vui lòng lựa chọn lại số phù hợp với menu: ");
            scanf("%d",&choice);
        }

        switch (choice){
        case 0:
            break;
        case 1:{
            char vocab[MAX_LEN], meaning[MAX_LEN], type[MAX_LEN];
            printf("\n\t** Hãy nhập từ mới: ");
            Input(vocab);

            if (Search(vocab) != NULL ){
                printf("\n\t** Từ này đã có trong danh sách từ điển!\n");
                break;
            }

            printf("\n\t** Hãy nhập nghĩa của từ: ");
            Input(meaning);
            printf("\n\t** Hãy nhập kiểu của từ: ");
            Input(type);
            Node *node= CreateNode(vocab,meaning,type);
            InsertNodeToHashTable(node);
            printf("\n\nBẠN ĐÃ THÊM TỪ ĐÃ THÀNH CÔNG!\n\n");
            break;
        }
        case 2:
            PrintHashTable();
            break;

        case 3:
            printf("\t** Hãy nhập từ cần thay đổi: ");
            Input(word);
            Update(word);
            break;

        case 4:{
            printf("\t** Hãy nhập từ cần tra nghĩa: ");
            Input(word);
            printf("\n");
            Node* res= Search(word);

            if (res != NULL)
            printf("--->  %-20s: %-20s %-10s \n", res->vocab, res->meaning, res->type);
            else
            printf(" KHÔNG CÓ TỪ NÀY TRONG TỪ ĐIỂN\n");
            break;
        }

        case 5:
            printf("\n\t** Hãy nhập từ cần xóa : ");
            Input(word);
            if (DeleteNode(word))
                printf("ĐÃ XÓA TỪ THÀNH CÔNG !\n"); 
            else
                printf("KHÔNG CÓ TỪ NÀY TRONG TỪ ĐIỂN !\n");
            break;

        case 6:
            printf("\t ** Tìm kiếm: "); scanf("%s",word);
            TimKiem(word);
            break;
            
        case 7:
            printf("\n\n\t LEVEL 1: 5 câu\n\n\t LEVEL 2: 10 câu\n\n\t LEVEL 3: 15 câu\n\n");
            int level; 
            do{
                printf("\t** Hãy chọn level trò chơi: ");
                scanf("%d",&level);
            }
            while (level <0 || level >3);
            PlayGame(level*5);
            break;

        case 8:
            WriteFile();
            printf("\t\t** Sao lưu dữ liệu thành công !\n ");
            break;
        }

        if (choice !=0){
            fflush(stdin);
            printf("\nVui lòng nhấn phím Enter để tiếp tục! ");
            getchar();
        }
        
    } 
    while (choice != false);
}
