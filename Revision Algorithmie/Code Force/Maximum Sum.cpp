/*# include <iostream>
using namespace std;

int tableau2 [100][100];
void kadane2D (int longueur);
int Tampon [100];
int main ()
{

    //  on remplit le tableau qu'on vas traiter.
    // le tableau est ok !
    int nb = 0;
    cin >> nb ;
    
    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < nb; j++)
        {
            int entre = 0;
            cin >> entre;
            tableau2[i][j] = entre;
        }
    }
    
    
    for (int i = 0; i < nb ; i++)
    {
        for (int j = 0; j < nb; j++)
        {
            cout << tableau2[i][j] << " ";
        } cout << endl;
    }

    kadane2D (nb);
    return 0;
}
    



// realisation de la methode KADANE 2D

void kadane2D (int longueur)
{
    // initialisation des variables nous servant dans l'algorithme.
    int maxSum = 0;
    int Debut= 0;
    int fin = 0;
    int droite = 0;
    int gauche = 0;
    
    for (int r1 = 0; r1 < longueur; r1++)
    {
        for (int i=0; i< longueur; i++)
        Tampon[i] = 0;
        
        for (int r2 = r1; r2 < longueur; r2++)
        {
            for (int c = 0; c < longueur; c++)
            {
// ---------ici nous avons notre tableau 1D necessaire à la methode de kadane1D
                Tampon [c] += tableau2[c][r2];
            }
// ----------il nous reste à effectuer la methode kadane 1D  sur le tableau Tampon
            int CurrentSomme = 0;
            int c1 = 0;
            for (int c = 0; c < longueur ; c++)
            {
                CurrentSomme = Tampon[c] + CurrentSomme;
                if (CurrentSomme <= 0)
                {
                    CurrentSomme = 0;
                    c1 = c + 1;
                }
                if (CurrentSomme > maxSum)
                {
                    maxSum = CurrentSomme;
                    gauche = r1;
                    droite = r2;
                    Debut = c1;
                    fin = c;
                }
            }
        }
    }
    
    
    cout << maxSum << endl;
    for (int i = Debut ; i <= fin ; i++)
    {
        for (int j = gauche; j <= droite; j++)
        {
           cout << tableau2[i][j] << " ";
        } cout << endl;
    }
    
    
} */

        // O(N^4) !!!
 /*       public static void dynamicProgammingSolution(int[][] a) {
            int[][][][] dynTable = new int[LENGTH][LENGTH][LENGTH + 1][LENGTH + 1]; // [row][col][height][width]
            int maxSum = Integer.MIN_VALUE;
            int maxRowStart = -1;
            int maxColStart = -1;
            int maxRowEnd = -1;
            int maxColEnd = -1;
            
            for (int r = 0; r < LENGTH; r++) {
                for (int c = 0; c < LENGTH; c++) {
                    for (int h = 0; h < LENGTH + 1; h++) {
                        for (int w = 0; w < LENGTH + 1; w++) {
                            dynTable[r][c][h][w] = 0;
                        }
                    }
                }
            }
            
            for (int r = 0; r < LENGTH; r++) {
                for (int c = 0; c < LENGTH; c++) {
                    for (int h = 1; h <= LENGTH - r; h++) {
                        int rowTotal = 0;
                        for (int w = 1; w <= LENGTH - c; w++) {
                            rowTotal += a[r + h - 1][c + w - 1];
                            dynTable[r][c][h][w] = rowTotal + dynTable[r][c][h - 1][w];
                        }
                    }
                }
            }
            
            for (int r = 0; r < LENGTH; r++) {
                for (int c = 0; c < LENGTH; c++) {
                    for (int h = 0; h < LENGTH + 1; h++) {
                        for (int w = 0; w < LENGTH + 1; w++) {
                            if (dynTable[r][c][h][w] > maxSum) {
                                maxSum = dynTable[r][c][h][w];
                                maxRowStart = r;
                                maxColStart = c;
                                maxRowEnd = r + h - 1;
                                maxColEnd = c + w - 1;
                            }
                        }
                    }
                }
            }
            
            System.out.print("    DP SOLUTION |   Max sum: " + maxSum);
            System.out.print("   Start: (" + maxRowStart + ", " + maxColStart +
                             ")   End: (" + maxRowEnd + ", " + maxColEnd + ")");
        }
        
        
        // O(N^6) !!!
        public static void naiveSolution(int[][] a) {
            int maxSum = Integer.MIN_VALUE;
            int maxRowStart = -1;
            int maxColStart = -1;
            int maxRowEnd = -1;
            int maxColEnd = -1;
            
            for (int rowStart = 0; rowStart < LENGTH; rowStart++) {
                for (int colStart = 0; colStart < LENGTH; colStart++) {
                    for (int rowEnd = 0; rowEnd < LENGTH; rowEnd++) {
                        for (int colEnd = 0; colEnd < LENGTH; colEnd++) {
                            int sum = 0;
                            for (int row = rowStart; row <= rowEnd; row++) {
                                for (int col = colStart; col <= colEnd; col++) {
                                    sum += a[row][col];
                                }
                            }
                            if (sum > maxSum) {
                                maxSum = sum;
                                maxRowStart = rowStart;
                                maxColStart = colStart;
                                maxRowEnd = rowEnd;
                                maxColEnd = colEnd;
                            }
                        }
                    }
                }
            }
            
            System.out.print(" NAIVE SOLUTION |   Max sum: " + maxSum);
            System.out.print("   Start: (" + maxRowStart + ", " + maxColStart +
                             ")   End: (" + maxRowEnd + ", " + maxColEnd + ")");
        }
  */

    
