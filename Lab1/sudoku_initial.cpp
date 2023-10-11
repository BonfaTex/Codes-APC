/*
 * Check sudoku matrix
 */

#include <iostream>
#include <cmath>
#include <chrono>
#include <unistd.h>

using std::cout;
using std::cin;
using std::endl;

const size_t SIZE = 9;
const size_t SIDE = sqrt(SIZE);

/*  Function that returns 1 if key is contained in the array v,
    0 otherwise, is given */
int search_key (const unsigned v[], unsigned n_elements, unsigned key);

/* Function that returns 1 if all numbers from 1 to 9 are
   contained in v, 0 otherwise */
int basic_search (const unsigned v[], unsigned n_elements);

/* Functions that returns 1 if all the rows, columns and subregions
   (respectively) of the Sudoku matrix comply with the rules, 0 otherwise */
int check_rows (const unsigned sudoku[][SIZE]);
int check_cols (const unsigned sudoku[][SIZE]);
int check_regions_M (const unsigned sudoku[][SIZE]);
int check_regions_L (const unsigned sudoku[][SIZE]);
int check_regions_C (const unsigned sudoku[][SIZE]);
int check_regions_D (const unsigned sudoku[][SIZE]);

/* Function that returns:
         1 if sudoku matrix complies to all Sudoku rules
        -1 if a row violates the game rules
        -2 if a column violates the game rules
        -3 if a region violates the game rules */
int check_sudoku (const unsigned sudoku[][SIZE], unsigned choose);

/* Function that create a Sudoku matrix by Lewis' Algorithm
   (https://en.wikipedia.org/wiki/Sudoku_solving_algorithms) */
void generate_sudoku (unsigned sudoku[][SIZE]);

/* Function that shows on output the sudoku matrix */
void show_sudoku (unsigned sudoku[][SIZE]);

int main ()
{
    // initialize a sudoku matrix
    unsigned sudoku[SIZE][SIZE] = {
            {1,2,3,4,5,6,7,8,9},
            {2,3,4,5,6,7,8,9,1},
            {3,4,5,6,7,8,9,1,2},
            {4,5,6,7,8,9,1,2,3},
            {5,6,7,8,9,1,2,3,4},
            {6,7,8,9,1,2,3,4,5},
            {7,8,9,1,2,3,4,5,6},
            {8,9,1,2,3,4,5,6,7},
            {9,1,2,3,4,5,6,7,8}
    };
    show_sudoku(sudoku);

    cout << "\n";

    // check
    int res = check_sudoku(sudoku,1);
    cout << "check_sudoku returns: " <<  res << "\n\n\n";

    cout << "\n";

    // initialize another sudoku matrix
    unsigned sudoku2[SIZE][SIZE];
    generate_sudoku(sudoku2);
    show_sudoku(sudoku2);

    cout << "\n";

    // check
    res = check_sudoku(sudoku2,1);
    res = check_sudoku(sudoku2,2);
    res = check_sudoku(sudoku2,3);
    res = check_sudoku(sudoku2,4);
    cout << "check_sudoku returns: " <<  res << endl;

    return 0;
}

// =================================================================================
//     FUNCTIONS
// =================================================================================

int search_key (const unsigned v[], unsigned n_elements, unsigned key)
{
    int key_found = 0;

    for (size_t i=0; i<n_elements; ++i)
        if (v[i] == key)
            key_found = 1;

    return key_found;
}

int basic_search (const unsigned v[], unsigned n_elements)
{
    for (size_t i=1; i<=n_elements; ++i)
    {
        if (search_key(v, n_elements, i)==0)
        {
            return 0;
        }
    }
    return 1;
}

int check_rows (const unsigned sudoku[][SIZE])
{
    unsigned R[SIZE];

    for (size_t i=0; i<SIZE; ++i)
    {
        for (size_t j=0; j<SIZE; ++j)
        {
            R[j] = sudoku[i][j];
        }
        // RMK: you can do better, sudoku[j] is already the j-th row
        if (basic_search(R,SIZE)==0)
        {
            return 0;
        }
    }
    return 1;
}

int check_cols (const unsigned sudoku[][SIZE])
{
    unsigned C[SIZE];

    for (size_t i=0; i<SIZE; ++i)
    {
        for (size_t j=0; j<SIZE; ++j)
        {
            C[j] = sudoku[j][i];
        }
        if (basic_search(C,SIZE)==0)
        {
            return 0;
        }
    }
    return 1;
}

// Matteo's version
int check_regions_M (const unsigned sudoku[][SIZE])
{
    auto start = std::chrono::steady_clock::now();

    unsigned S[SIZE];

    for (size_t k = 0; k < 3; ++k)
    {
        for (size_t h = 0; h < 3; ++h)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    S[3*i+j] = sudoku[3*k+i][3*h+j];
                }
            }
            if (basic_search(S, SIZE) == 0) {
                return 0;
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    cout << "Elapsed time in nanoseconds: "
         << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
         << " ns (Matteo)" << endl;

    return 1;
}

// Lorenzo's version
int check_regions_L (const unsigned sudoku[][SIZE])
{
    auto start = std::chrono::steady_clock::now();

    unsigned v[SIZE] = {};

    for (size_t i=0; i<3; ++i)
    {
        for (size_t j=0; j<3; ++j)
        {
            unsigned t = 0;

            for(size_t ii=3*i; ii<3*(i+1); ++ii)
            {
                for (size_t jj = 3*j; jj<3*(j+1); ++jj)
                {
                    v[t++] = sudoku[ii][jj];
                }
            }
            if (basic_search(v,SIZE)==0)
            {
                return 0;
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    cout << "Elapsed time in nanoseconds: "
         << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
         << " ns (Lorenzo)" << endl;

    return 1;
}

// Carlotta's version
int check_regions_C (const unsigned sudoku[][SIZE])
{
    auto start = std::chrono::steady_clock::now();

    for (size_t i=0; i<SIZE-3; i=i+3)
    {
        for (size_t j=0; j<SIZE-3; j=j+3)
        {
            unsigned v[SIZE];
            size_t k=0;

            for (size_t m=i; m<i+3; ++m)
            {
                for (size_t n=j; n<j+3; ++n)
                {
                    v[k++]=sudoku[m][n];
                }
            }
            if (basic_search(v,SIZE)==0)
                return 0;
        }
    }
    auto end = std::chrono::steady_clock::now();
    cout << "Elapsed time in nanoseconds: "
         << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
         << " ns (Carlotta)" << endl;

    return 1;
}

// Davide's version
int check_regions_D (const unsigned sudoku[][SIZE])
{
    auto start = std::chrono::steady_clock::now();

    unsigned v[SIZE] = {};

    for (size_t region = 0; region < SIZE; ++region)
    {
        int k = 0;

        for (size_t i = region - (region % SIDE); i < region + SIDE - (region % SIDE); ++i)
        {
            for (size_t j = SIDE * (region % SIDE); j < SIDE * ((region % SIDE) + 1); ++j)
            {
                v[k++] = sudoku[i][j];
            }
        }
        if (basic_search(v,SIZE)==0)
        {
            return 0;
        }
    }
    auto end = std::chrono::steady_clock::now();
    cout << "Elapsed time in nanoseconds: "
         << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
         << " ns (Davide)" << endl;

    return 1;
}

int check_sudoku (const unsigned sudoku[][SIZE], unsigned choose)
{
    if (check_rows(sudoku)==0)
    {
        return -1;
    }
    if (check_cols(sudoku)==0)
    {
        return -2;
    }
    if (choose == 1 && check_regions_M(sudoku)==0)
    {
        return -3;
    }
    else if (choose == 2 && check_regions_L(sudoku)==0)
    {
        return -3;
    }
    else if (choose == 3 && check_regions_C(sudoku)==0)
    {
        return -3;
    }
    else if (choose == 4 && check_regions_D(sudoku)==0)
    {
        return -3;
    }
    return 1;
}

void generate_sudoku (unsigned sudoku[][SIZE])
{
    int x = 0;

    for (size_t i=1; i<=3; ++i)
    {
        for (size_t j=1; j<=3; ++j)
        {
            for (size_t k=1; k<=SIZE; ++k)
            {
                sudoku[3*(i-1)+j-1][k-1] = (x % SIZE) + 1;
                x++;
            }
            x += 3;
        }
        x++;
    }
}

void show_sudoku (unsigned sudoku[][SIZE])
{
    for (size_t r = 0; r<SIZE; r++)
    {
        for (size_t c = 0; c<SIZE; c++)
        {
            if (c == 3 || c == 6)
                cout << " | ";

            cout << sudoku[r][c] << " ";
        }
        if (r == 2 || r == 5)
        {
            cout << endl;

            for (size_t k = 0; k<SIZE; k++)
                cout << "---";
        }
        cout << endl;
    }
}