#include <stdio.h>
#include <stdlib.h> //rand関数の使用に必要
#include <time.h>   //時刻情報を利用し、乱数の固定化を防ぐ

void output(int *pdeck, char *pname);

int main(void)
{
    int trigger;                        //シールドトリガーの種類数
    int t_number;                       //シールドトリガーの総枚数
    int deck[41] = {0};                 //デッキ内　要素が 0 の時トリガーでないカード、　1 の時を1種類目のトリガーとする
    int *pdeck = &deck[0];              //deck配列を差すアドレス
    char t_name[40][100] = {0};         //トリガーの名前
    int i;                              //ループカウンタ
    int j;                              //ループカウンタ
    int temp;                           //作業領域
    int error_flag;                     //エラーフラッグ　エラーチェックに使用
    int roop_flag;                      //ループ終了を判定するフラグ
    int end_flag;                       //終了フラグ
    double kakuritu;                    //確率
    
    

    srand(time(NULL));                  //乱数の初期化

    printf("デュエルマスター　シールドシュミレーター\n");

    //トリガーの種類数を入力
    do {
        error_flag = 1;
        printf("デッキ内に存在するシールドトリガーの種類数を入力してください\n");
        printf(" ==> ");
        scanf("%d", &trigger);
        if (trigger > 40) {
            printf("エラー　シールドトリガーの種類数がデッキ枚数を超えています。　再入力してください。\n");
            error_flag = 0;
        } else if (trigger < 0) {
            printf("エラー　シールドトリガーの種類数が－になっています。再入力してください。\n");
        }
    } while (error_flag != 1);
    
    //トリガーの種類ごとの枚数と名前を入力
    t_number = 0;
    for (i = 0; i < trigger; i++) {
        printf("シールドトリガー %d 種類目の枚数と名前を入力してください\n", i + 1);
        do {
            error_flag = 1;
            printf("シールドトリガーの枚数 ==> ");
            scanf("%d", &temp);
            if (temp > 4) {
                printf("エラー　シールドトリガーの枚数が４枚以上です。　再入力してください。\n");
                error_flag = 0;
            } else if (temp < 0){
                printf("エラー　シールドトリガーの枚数が－になっています。再入力してください。\n");
                error_flag = 0;
            }
        } while (error_flag != 1);
        t_number += temp;
        for(j = 0; j < temp; j++) {
            *pdeck = i + 1;
            pdeck++;
        }

        printf("シールドトリガー名 ==> ");
        scanf("%s", &t_name[i][0]);
    }

    //確率表示
    for (i = 0; i < 6; i++) {
        kakuritu = 1;
        temp = 40 - t_number;
        for (j = 0; j < 5 - i; j++) {
            kakuritu = kakuritu * temp;
            if (temp == 0) {

                break;
            }
            temp--;
        }
        temp = t_number;
        for (j = 5 - i; j < 5; j ++){
            kakuritu = kakuritu * temp;
            if (temp == 0) {
                break;
            }
            temp--;
        }
        for (j = 0; j < i; j++) {
            kakuritu = kakuritu * (5 - j) / (j + 1);
        }

        kakuritu = kakuritu / (40 * 39 * 38 * 37 * 36) * 100;
        printf("シールドトリガーが %d 枚の確率は %.2f です。\n" , i, kakuritu);
    }
    

    printf("入力お疲れ様です。それではシールドシュミレートを開始します。\n");
    //ランダム かつ 重複がないようにカードを５枚選び表示　選んだカードがシールドなら名前を表示
    do {
        end_flag = 1;
        printf("シールド表示\n");
        for (i = 0; i < 5; i++) {
            printf(" %d 枚目 ", i + 1);
            do {
                roop_flag = 1;
                temp = rand () % 40;
                if (deck[temp] < 100) {
                output(&deck[temp], &t_name[0][0]);
                deck[temp] += 100;
                roop_flag = 0;
                }
            } while (roop_flag == 1);
            printf("\n");
        }

        printf("シュミレートを継続しますか？\n");
        printf("継続する場合は 1 を、終了する場合は 0 を入力してください\n");
        printf(" ==> ");
        scanf("%d", &end_flag);
        
        if (end_flag == 1) {
            for (i = 0; i < 40; i++) {
                if (deck[i] >= 100) {
                    deck[i] = deck[i] - 100;
                }
            }
        }

    } while (end_flag == 1);
    
    return 0;
}

void output(int *pdeck, char *pname)
{
    if (*pdeck == 0) {
        printf("シールドトリガーなし");
    } else {
        printf("シールドトリガー  ");
        for (pname = pname + ((*pdeck - 1) * 100); *pname != 0; pname++) {
            printf("%c", *pname);
        }
    }
}