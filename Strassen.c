#include <stdio.h>
#include <stdlib.h>

void MatriksleriTopla(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void MatriksleriCikar(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void StrassensAlgorithm(int n, int A[][n], int B[][n], int C[][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half_n = n / 2;
    int A11[half_n][half_n], A12[half_n][half_n], A21[half_n][half_n], A22[half_n][half_n];
    int B11[half_n][half_n], B12[half_n][half_n], B21[half_n][half_n], B22[half_n][half_n];
    int M1[half_n][half_n], M2[half_n][half_n], M3[half_n][half_n], M4[half_n][half_n], M5[half_n][half_n], M6[half_n][half_n], M7[half_n][half_n];
    int P1[half_n][half_n], P2[half_n][half_n], P3[half_n][half_n], P4[half_n][half_n];
    int temp1[half_n][half_n], temp2[half_n][half_n];

    // A ve B matrislerini dört eşit boyutta alt matrise böl
    for (int i = 0; i < half_n; i++) {
        for (int j = 0; j < half_n; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half_n];
            A21[i][j] = A[i + half_n][j];
            A22[i][j] = A[i + half_n][j + half_n];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half_n];
            B21[i][j] = B[i + half_n][j];
            B22[i][j] = B[i + half_n][j + half_n];
        }
    }

    // M1-M7 hesaplamaları
    MatriksleriTopla(half_n, A11, A22, temp1);
    MatriksleriTopla(half_n, B11, B22, temp2);
    StrassensAlgorithm(half_n, temp1, temp2, M1);

    MatriksleriTopla(half_n, A21, A22, temp1);
    StrassensAlgorithm(half_n, temp1, B11, M2);

    MatriksleriCikar(half_n, B12, B22, temp1);
    StrassensAlgorithm(half_n, A11, temp1, M3);

    MatriksleriCikar(half_n, B21, B11, temp1);
    StrassensAlgorithm(half_n, A22, temp1, M4);

    MatriksleriTopla(half_n, A11, A12, temp1);
    StrassensAlgorithm(half_n, temp1, B22, M5);

    MatriksleriCikar(half_n, A21, A11, temp1);
    MatriksleriTopla(half_n, B11, B12, temp2);
    StrassensAlgorithm(half_n, temp1, temp2, M6);

    MatriksleriCikar(half_n, A12, A22, temp1);
    MatriksleriTopla(half_n, B21, B22, temp2);
    StrassensAlgorithm(half_n, temp1, temp2, M7);

    // P1-P4 hesaplamaları
    MatriksleriTopla(half_n, M1, M4, temp1);
    MatriksleriCikar(half_n, temp1, M5, temp2);
    MatriksleriTopla(half_n, temp2, M7, P1);

    MatriksleriTopla(half_n, M3, M5, P2);

    MatriksleriTopla(half_n, M2, M4, P3);

    MatriksleriTopla(half_n, M1, M3, temp1);
    MatriksleriTopla(half_n, temp1, M2, temp2);
    MatriksleriTopla(half_n, temp2, M6, P4);

    // Sonuç matrisini birleştir
    for (int i = 0; i < half_n; i++) {
        for (int j = 0; j < half_n; j++) {
            C[i][j] = P1[i][j];
            C[i][j + half_n] = P2[i][j];
            C[i + half_n][j] = P3[i][j];
            C[i + half_n][j + half_n] = P4[i][j];
        }
    }
}

// Matrisi yazdırma
void MatrixYazdir(int n, int A[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int A[4][4] = {{1, 2, 3, 4},
                   {5, 6, 7, 8},
                   {9, 10, 11, 12},
                   {13, 14, 15, 16}};

    int B[4][4] = {{17, 18, 19, 20},
                   {21, 22, 23, 24},
                   {25, 26, 27, 28},
                   {29, 30, 31, 32}};

    int C[4][4];

    StrassensAlgorithm(4, A, B, C);
    printf("Sonuc:\n");
    MatrixYazdir(4, C);
    return 0;
}