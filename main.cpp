//
// Created by antonio on 17-10-25.
//

/**
 * 作业3-3细胞个数统计
[ 发布人： 曲超   截止时间：2017-10-26 23:59:59  ]
一矩形阵列由数字0到9组成，数字1到9代表细胞，细胞的定义为沿细胞数字上下左右还是相同数字则为同一细胞，如:阵列
0 1 0 0 0 0 0
0 1 0 0 4 0 0
0 1 1 0 4 0 0
0 1 8 0 0 0 0
0 0 8 5 5 5 0
0 8 8 8 0 0 0
0 0 8 0 0 0 1
有5个细胞，编写程序求给定矩形阵列的细胞个数。
 */

//作业3-3辅助代码
#include <queue>
#include <iostream>
#include <iomanip>

#define maxsize 8 //培养皿的大小8*8
#define type 5 //可出现的细胞种类,即4中不同颜色

using namespace std ;

int ** init_matrix(int n, int m)//随机生成显微镜图像
{
    int **area = new int *[n] ;
    srand(time(NULL)) ;

    for(int i = 0; i < n; i++)
        area[i] = new int[n] ;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            area[i][j] = rand() % (m + 1) ;
    }

    return area;
}

void out_put_matrix(int **area, int n)//输出图像
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {

            cout << setw(4) << area[i][j];
        }
        cout<<endl ;
    }
}

void BFS(int **area, int n, int raw, int col, int cell){

    int x[] = {1, 0, -1, 0}, y[] = {0, 1, 0, -1} ;//利用数组模拟二维坐标,上下左右

    for (int i = 0; i < 4; i++) {
        if(raw + x[i] >=0 && raw + x[i] < maxsize && col + y[i] >= 0 && col + y[i] < maxsize && area[raw+x[i]][col+y[i]] == cell){
            //确保从该点出发四周各点都在范围内,且属于同一细胞
          area[raw + x[i]][col + y[i]] = 0 ;//找到目标位置后,赋0
            BFS(area, n, raw+x[i], col+y[i], cell) ;//递给循环,下一个坐标
        }


    }
}

int count(int **area, int n){//统计细胞数量；area 二维数组，n 数组阶数
    //补充此函数即可
    int num = 0 ;//记录细胞的数目
    int cell = 0 ;//记录细胞所代的值

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(area[i][j] != 0){
                cell = area[i][j] ;
                area[i][j] = 0 ;
                BFS(area, n, i, j, cell) ;
                num++ ;
            }


        }
    }

    return num ;
}



int main()
{
    int ** area;
    area = init_matrix(maxsize, type) ;

    out_put_matrix(area,maxsize) ;

    int a = count(area, maxsize) ;
    cout << a << endl ;

    return 0 ;
}