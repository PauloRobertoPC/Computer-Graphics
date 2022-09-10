#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include "vp.hpp"

class matrix{
    private: 
        std::vector<std::vector<double>> M;
    
    public:
        matrix(int n, int m);

        int row();                          //quantity of rows
        int col();                          //quantity of cols
        double matrix_to_scalar();          //return scalar of matrix 1x1(that is a number)
        void print();                       //print matrix in standard output
        
        matrix operator+(matrix A);         //sum of matrix
        matrix operator-(matrix A);         //subtraction of matrix
        matrix operator-();                 //-matrix
        matrix operator*(double alp);       //matrix multiplication by a scalar
        matrix operator*(matrix A);         //multiplication between matrix
        matrix operator~();                 //transposed matrix
        
        static matrix identity(int n){
            matrix A(n, n);
            for(int i = 0; i < n; i++) A.M[i][i] = 1.0;
            return A;
        }

        static matrix vector_to_matrix(vp v){
            matrix V(3, 1);
            V.M[0][0] = v.get_x();
            V.M[1][0] = v.get_y();
            V.M[2][0] = v.get_z();
            return V;
        }
};

#endif
