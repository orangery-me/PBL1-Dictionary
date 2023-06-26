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

        printf("\n\n\t\t   TU DIEN TIENG ANH\n\n\t+");
        for (int i=1; i<=40; ++i)
        printf("-");
        printf("+\n\t|%40s|\n"," ");
        printf("\t| 1.   Them tu moi                       |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 2.   Xoa di mot tu                     |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 3.   Sua thong tin tu vung             |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 4.   Tra nghia cua tu                  |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 5.   In danh sach tu vung              |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 6.   Sao luu du lieu ra file           |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 7.   Tro choi do chu                   |\n");
        printf("\t|%40s|\n"," ");
        printf("\t| 0.   Ket thuc chuong trinh             |\n");
        printf("\t|%40s|\n\t+"," ");
        for (int i=1; i<=40; ++i)
        printf("-");
        printf("+\n\nHay nhap lua chon tren menu: ");
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
            printf("\n\n\t LEVEL 1: 5 cau\n\n\t LEVEL 2: 10 cau\n\n\t LEVEL 3: 15 cau\n\n");
            int level; 
            do{
                printf("Hay chon level tro choi: ");
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
