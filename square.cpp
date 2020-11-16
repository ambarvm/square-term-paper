#include<iostream>
#include<vector>

using namespace std;


vector<vector<int>> matrix_multiply(vector<vector<int>> A, vector<vector<int>> B)
{
    int i, j, k;
    vector<vector<int>> res(A.size(), vector<int>(B[1].size(), 0));
    vector<int> row;
    for(i = 0; i < A.size(); i++)
    {
        for(j = 0; j < B[0].size(); j++)
        {
            for(k = 0; k < B.size(); k++)
                res[i][j] += A[i][k]*B[k][j];
        }
    }
    return res;
}


vector<vector<int>> theta(vector<vector<int>> matrix)
{
    vector<vector<int>> M = {{2, 3, 1, 1},
                            {1, 2, 3, 1},
                            {1, 1, 2, 3},
                            {3, 1, 1, 2}};
    return (matrix_multiply(matrix, M));
}


vector<vector<int>> gamma(vector<vector<int>> matrix)
{
    int i, j;
    // sbox not set up
    vector<int> sbox (16, 0);
    for(i = 0; i < matrix.size(); i++)
        for(j = 0; j < matrix[0].size(); j++)
            matrix[i][j] = sbox[matrix[i][j]];
    return matrix;
}


vector<vector<int>> pi(vector<vector<int>> matrix)
{
    vector<vector<int>> res;
    int i, j;
    for(i = 0; i < matrix.size(); i++)
        for(j = 0; j < matrix[0].size(); j++)
            res[i][j] = res[j][i];
    return res;
}

vector<vector<int>> sigma(vector<vector<int>> key, vector<vector<int>> matrix)
{
    int i, j;
    for(i = 0; i < matrix.size(); i++)
        for(j = 0; j < matrix[1].size(); j++)
            matrix[i][j] ^= key[i][j];
    return matrix;
}

int main()
{
    
}