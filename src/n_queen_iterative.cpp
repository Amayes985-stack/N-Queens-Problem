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

//fonction itérative pour la résolution du problème
void solve_nqueens_iterative(int N) {

    vector<vector<int>> board(N, vector<int>(N, 0)); //échiquer de taille N*N
    vector<pair<int, int>> stack; //pile 

    int col = 0;
    int row = 0;

    //On rentre dans une boucle infinie pour explorer toutes les possbilités 
    while (true) {

        while (row < N) {
            // Si la position dans laquelle je suis est valide 
            if (is_safe(board, row, col, N)) {
                stack.emplace_back(row, col); //j'empile les coordonnées de la position 
                board[row][col] = 1; // Je place ma reine dans cette position 
                col += 1; // Je passe à la prochaine colonne 
                row = 0;
            } else {
                row += 1; //Sinon je passe directement à la prochaine ligne pour exploiter les possibilités
            }
        }

        if (col == N) {
            // Une solution a été trouvée, on l'affiche 
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        // Si ma pile est vide -> Aucune configuration possible 
        if (stack.empty()) {
            cout << "Aucune configuration possible." << endl;
            break;
        }

        // Backtrack
        col -= 1;
        row = stack.back().first;
        col = stack.back().second;
        stack.pop_back();
        board[row][col] = 0;
        row += 1;
    }
}

// Fonction pour mesurer le temps d'exécution
double measure_execution_time(const function<void(int)>& function, int N) {
    auto start_time = high_resolution_clock::now();
    function(N); // Exécution de la fonction
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    return duration.count() / 1000.0; // Convertir en secondes
}

int main() {
    // Exemple d'utilisation avec N=8
    int N = 8;
    double execution_time = measure_execution_time(solve_nqueens_iterative, N);

    cout << "Temps d'exécution : " << execution_time << " secondes." << endl;

    return 0;
}