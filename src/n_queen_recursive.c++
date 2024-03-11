#include <iostream>
#include <vector>
#include <chrono>
#include <functional>


using namespace std;
using namespace chrono;

//fonction pour vérifier si je peux placer une reine à la position (ligne, colonne)
bool is_safe(vector<vector<int>>& board, int row, int col, int N) {

    // Je vérifie la rangée à gauche
    for (int i = 0; i < col; ++i) {
        if (board[row][i] == 1) {
            return false;
        }
    }

    // Je vérifie la diagonale supérieure à gauche
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Je vérifie la diagonale inférieure à gauche
    for (int i = row, j = col; i < N && j >= 0; ++i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

//fonction récursive pour la résolution du problème des N-Reines 
bool solve_nqueens_util(vector<vector<int>>& board, int col, int N) {
    // Cas de base : toutes les reines sont placées
    if (col >= N) {
        return true;
    }

    for (int i = 0; i < N; ++i) {
        // Je vérifie si la reine peut être placée à la position (i, col)
        if (is_safe(board, i, col, N)) {
            // Je place ma reine 
            board[i][col] = 1;

            // Appel récursif pour la prochaine itération 
            if (solve_nqueens_util(board, col + 1, N)) {
                return true;
            }

            // Si je ne peu pas placer la reine à cette position, backtrack
            board[i][col] = 0;
        }
    }

    // Si aucune position valide n'a été trouvée -> aucun résultat 
    return false;
}

//fonction d'affichage des résultats 

void solve_nqueens(int N) {
    // On prends un échiquier vide
    vector<vector<int>> board(N, vector<int>(N, 0));

    // J'appelle la fonction de résolution
    if (!solve_nqueens_util(board, 0, N)) {
        cout << "Aucune solution n'existe." << endl;
        return;
    }

    // J'affiche la solution
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Fonction pour mesurer le temps d'exécution
double measure_execution_time_recursive(const function<void(int)>& function, int N) {
    auto start_time = high_resolution_clock::now();
    function(N); // Exécution de la fonction
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    return duration.count() / 1000.0; // Convertir en secondes
}

int main() {
    // Exemple d'utilisation avec N=8
    int N = 8;

    // Mesure du temps d'exécution du programme récursif
    double execution_time_recursive = measure_execution_time_recursive(solve_nqueens, N);

    cout << "Temps d'exécution du programme récursif : " << execution_time_recursive << " secondes." << endl;

    return 0;
}
