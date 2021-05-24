#include<windows.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#define PI 3.14159265358979323846
#define N 12
#include <stdbool.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[]="Лабораторна робота 6";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName=ProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;


    hWnd=CreateWindow(ProgName,
        "Лабораторна робота 6. Виконала Саніна А. М.",
        WS_OVERLAPPEDWINDOW,
        400,
        100,
        1000,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    return(lpMsg.wParam);
    }

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc;
    PAINTSTRUCT ps;
    void mulmr(int* matrix[N][N], double coef) {
    int el;
    double num;
    srand(0421);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            num = (rand() / (double)RAND_MAX * 2) * coef;
            if (num < 1) el = 0;
            else el = 1;
            matrix[i][j] = el;
        }
    }
}

    void symmetricalMatrix(int A[N][N], int* symMatrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j]) {
                symMatrix[j][i] = A[i][j];
                symMatrix[i][j] = A[i][j];
            }
        }
    }
}

    void linesOfGraph(HDC hdc, int matrix[N][N], int nx[N], int ny[N], int i, int j) {
       if (matrix[i][j] == 1){
                            if (i == j){
                                    if(i <= (12-1)/4){
                                Arc(hdc, nx[j], ny[j], nx[j]+40, ny[j]+40,    nx[j], ny[j], nx[j], ny[j]);
                                }
                                    else if(i > (12-1)/4 && i <= (12-1)/2  ){
                                        Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]+40,    nx[j], ny[j], nx[j], ny[j]);
                                    }
                                    else if(i > (12-1)/2 && i <= (3*(12-1))/4 ){
                                        Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40,    nx[j], ny[j], nx[j], ny[j]);
                                    }
                                     else {
                                        Arc(hdc, nx[j], ny[j], nx[j]+40, ny[j]-40,    nx[j], ny[j], nx[j], ny[j]);
                                    }
                           }
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        LineTo(hdc, nx[j], ny[j]);
                    }
    }

    void vertexOfGraph(HDC hdc, int nx[N], int ny[N], char* numVerticle[N], int n) {
     int dx = 16, dy = 16, dtx = 5;
     Ellipse(hdc, nx[n]-dx,ny[n]-dy,nx[n]+dx,ny[n]+dy);
     TextOut(hdc, nx[n]-dtx,ny[n]-dy/2,  numVerticle[n], 2);
    }
    void linesWeight(HDC hdc, int matrix[N][N], int nx[N], int ny[N], int i, int j){
        char text[5];
        sprintf_s(text, sizeof(text)+2, "%d", matrix[i][j]);
      if (matrix[i][j]>0) {
        if (i == j) {
            MoveToEx(hdc, nx[j], ny[j], NULL);
            TextOutA(hdc, nx[j] -30, ny[j] - 45, text, 3);
        } else {
           MoveToEx(hdc, nx[i], ny[i], NULL);
           TextOutA(hdc, (nx[i] + nx[j]) * 0.5-9, (ny[i] + ny[j]) * 0.5-9, text, 3);
        }
    }

    }

int algorythmPrima(int W[12][12],int nx[N], int ny[N],char* numVerticle[N]){
  int matrixofTree[12][12]={};
  int vertNum;
  int currentVert[12];
  int allWeights[12];
  memset (currentVert, false, sizeof (currentVert));
  vertNum = 0;
  currentVert[0] = true;

  int first=0;
  int last=0;
  int sum=0;
  while (vertNum < N - 1) {

      int min = 9999999;

      for (int i = 0; i < N; i++) {
        if (currentVert[i]) {
            for (int j = 0; j < N; j++) {
              if (W[i][j] && !currentVert[j]) {
                  if (min > W[i][j]) {
                      min = W[i][j];
                      first = i;
                      last = j;
                  }
              }
          }
        }
      }
      printf("%d -> %d, weight = %d \n", first+1, last+1, W[first][last]);
      matrixofTree[first][last] = 1;
      int i=0;
      Sleep(2000);
       linesOfGraph(hdc, matrixofTree, nx, ny, first, last);
       vertexOfGraph(hdc, nx, ny, numVerticle, i);
       i++;
      sum+=W[first][last];
      currentVert[last] = true;
      vertNum++;
    }
    printf("Total sum = %d \n", sum);
    for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                printf("%i ", matrixofTree[i][j]);
            }
            printf("\n");
        }

}
    void matrixW(HDC hdc,int matrix[N][N], int* W[N][N]) {
    int B[N][N];
    int C[N][N];
    int D[N][N];
    int Wt[N][N];
    int Tr[N][N]={
            {0,1,1,1,1,1,1,1,1,1,1,1},
            {0,0,1,1,1,1,1,1,1,1,1,1},
            {0,0,0,1,1,1,1,1,1,1,1,1},
            {0,0,0,0,1,1,1,1,1,1,1,1},
            {0,0,0,0,0,1,1,1,1,1,1,1},
            {0,0,0,0,0,0,1,1,1,1,1,1},
            {0,0,0,0,0,0,0,1,1,1,1,1},
            {0,0,0,0,0,0,0,0,1,1,1,1},
            {0,0,0,0,0,0,0,0,0,1,1,1},
            {0,0,0,0,0,0,0,0,0,0,1,1},
            {0,0,0,0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,0,0,0,0}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Wt[i][j] = roundf((rand() / (float)RAND_MAX * 2) * 100) * matrix[i][j];
            if (Wt[i][j] == 0) B[i][j] = 0;
            else B[i][j] = 1;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (B[i][j] != B[j][i]) C[i][j] = 1;
            else C[i][j] = 0;

            if (B[i][j] == B[j][i] && B[i][j] == 1 && j <= i) D[i][j] = 1;
            else D[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Wt[i][j] = (C[i][j] + (D[i][j])) * Wt[i][j];
        }
    }
    symmetricalMatrix(Wt, W); //making final matrix W
}

    switch(messg){
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);

            int n=12;
            char *nn[12] = {"1","2","3","4","5","6","7","8","9","10",
                       "11", "12"};
            int nx[12] = {};
            int ny[12] = {};
            int dx = 16, dy = 16, dtx = 5;
            int i, j;
            int radius = 200;
            int centreX = 400;
            int centreY = 200;
            for (int i = 0; i < n; i++){
                nx[i] = centreX + radius * cos(2*PI*i/(n));
                ny[i] = centreY + radius * sin(2*PI*i/(n));
            }

            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            HPEN RPen = CreatePen(PS_SOLID, 2, RGB(250, 0, 0));


        int W[12][12] = {};
        int symMatrix[N][N] = {};
        double coef=1.0 - 2 * 0.01 - 1 * 0.005 - 0.05;
        int A[12][12];
        int treeMatrix[12][12] = { };
        mulmr(A, coef);
             for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%i ", A[i][j]);
            }
            printf("\n");
        }
        symmetricalMatrix(A, symMatrix);
        printf("\nSymmetrical matrix\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%i ", symMatrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        matrixW(hdc,A,W);
         for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%i ", W[i][j]);
            }
            printf("\n");
        }

SelectObject(hdc, KPen);

   for(int i=0;i < n; i++){
            for(int j=0; j < n; j++) {
            linesOfGraph(hdc, symMatrix, nx,  ny,  i,  j);
            linesWeight(hdc, W, nx,  ny,  i,  j);
            }
            }
        SelectObject(hdc, BPen);

           for(i=0;i < n;i++){
              vertexOfGraph(hdc, nx,  ny,  nn,  i);
            }
        //Prima's algorythm

         algorythmPrima(W,nx,ny,nn);

            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
