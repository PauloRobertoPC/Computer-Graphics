#include <bits/stdc++.h>
#include "../header/matrix.hpp"

matrix::matrix(int n, int m){
    M.assign(n, std::vector<double>(m, 0.0));
}

int matrix::row(){ return this->M.size(); }
int matrix::col(){ return this->M[0].size(); }
double matrix::matrix_to_scalar(){ return this->M[0][0]; }
vp matrix::matrix_to_vp(){ return vp(this->M[0][0], this->M[1][0], this->M[2][0]); }

void matrix::print(){
    for(int i = 0; i < this->row(); i++){
        for(int j = 0; j < this->col(); j++){
            std::cout << this->M[i][j] << " ";
        }
        std::cout << "\n";
    }
}

matrix matrix::operator+(matrix A){
    if(this->row() != A.row() || this->col() != A.col()) return matrix(1, 1);
    matrix B(A.row(), A.col());
    for(int i = 0; i < this->col(); i++)
        for(int j = 0; j < this->row(); j++)
            B.M[i][j] = this->M[i][j] + A.M[i][j];
    return B;
}

matrix matrix::operator-(matrix A){
    if(this->row() != A.row() || this->col() != A.col()) return matrix(1, 1);
    matrix B(A.row(), A.col());
    for(int i = 0; i < this->col(); i++)
        for(int j = 0; j < this->row(); j++)
            B.M[i][j] = this->M[i][j] - A.M[i][j];
    return B;

}

matrix matrix::operator-(){
    matrix A(this->row(), this->col());
    for(int i = 0; i < this->col(); i++)
        for(int j = 0; j < this->row(); j++)
            A.M[i][j] = -this->M[i][j];
    return A;
}

matrix matrix::operator*(double alp){
    matrix A(this->row(), this->col());
    for(int i = 0; i < this->col(); i++)
        for(int j = 0; j < this->row(); j++)
            A.M[i][j] = this->M[i][j]*alp;
    return A;
}

matrix matrix::operator*(matrix A){
    if(this->col() != A.row()) return matrix(1, 1);
    matrix B(this->row(), A.col());
    for(int i = 0; i < this->row(); i++)
        for(int j = 0; j < A.col(); j++)
            for(int k = 0; k < A.row(); k++)
                B.M[i][j] += this->M[i][k]*A.M[k][j];
    return B;
}

matrix matrix::operator~(){
    matrix A(this->col(), this->row());  
    for(int i = 0; i < this->col(); i++)
        for(int j = 0; j < this->row(); j++)
            A.M[i][j] = this->M[j][i];
    return A; 
}
