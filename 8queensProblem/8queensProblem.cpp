#include <iostream>
#include <vector>
#include <chrono>

struct point2d {
    int x, y;
};

struct queen {
    point2d pos;
};

void printBoard(std::vector<queen> queens) {
    static bool board[8][8];
    for (int i = 0; i < 64; i++) board[i % 8][i / 8] = 0;

    for (queen& q : queens) {
        board[q.pos.y][q.pos.x] = true;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << (board[i][j] ? "Q " : "- ");
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n";
}

// \ diagonals
int dia0(point2d p) {
    return (7-p.x) + p.y;
}
// / diagonals
int dia1(point2d p) {
    return p.x + p.y;
}

bool isValid(std::vector<queen> queens) {
    static bool all[46];
    //offsets
    static bool *h = all, *v = all + 8, *d0 = all + 16, *d1 = all + 31;
    
    //clears the checks
    for (int i = 0; i < 46; i++)
        all[i] = false;
    
    for (queen q : queens) {
        if (h[q.pos.x]) return false;
        else h[q.pos.x] = true;
        if (v[q.pos.y]) return false;
        else v[q.pos.y] = true;
        if (d0[dia0(q.pos)]) return false;
        else d0[dia0(q.pos)] = true;
        if (d1[dia1(q.pos)]) return false;
        else d1[dia1(q.pos)] = true;
    }

    return true;
}

void solve() {
    int solutions = 0;

    int modofq[8] = {
        8, 8 * 8, 8 * 8 * 8, 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8 * 8 * 8 * 8
    };
    int divofq[8] = {
        1, 8, 8 * 8, 8 * 8 * 8, 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8 * 8 * 8
    };

    std::vector<queen> queens;
    for (int i = 0; i < 8; i++) {
        queens.push_back(queen{i, 0});
    }

    for (int i = 0; i < pow(8, 8); i++) {
        int j = 0;
        for (queen& q : queens) {
            q.pos.y = (i % modofq[j]) / divofq[j];
            j++;
        }
        if (isValid(queens)) {
            solutions++;
            printBoard(queens);
        }
    }

    std::cout << solutions << "solutions!!!\n";
}


int main()
{
    auto start_t = std::chrono::system_clock::now();

    solve();
    auto end_t = std::chrono::system_clock::now();
    std::cout << "solved in " << (double)(((std::chrono::nanoseconds)(end_t - start_t)).count()) * 0.000001 << " milliseconds \n";

    getchar();
}