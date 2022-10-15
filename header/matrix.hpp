#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>
#include <vector>
#include "vp.hpp"

class matrix{
    private: 
        std::vector<std::vector<double>> M;
    
    public:
        matrix(int n, int m);

        int row();                          //quantity of rows
        int col();                          //quantity of cols
        vp matrix_to_vp();                  //transform matrix to vp
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

        static matrix vp_to_matrix(vp v, bool R3=false){
            matrix V(4-R3, 1);
            V.M[0][0] = v.get_x();
            V.M[1][0] = v.get_y();
            V.M[2][0] = v.get_z();
            if(!R3) V.M[3][0] = 1;
            return V;
        }

        static matrix translation_matrix(vp t){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[0][3] = t.get_x();
            T.M[1][3] = t.get_y();
            T.M[2][3] = t.get_z();
            return T;
        }
    
        static matrix rotationX_matrix(double angle){
            matrix T(4, 4);
            T.M[0][0]  = T.M[3][3] = 1;
            T.M[1][1] = cos(angle);
            T.M[1][2] = -sin(angle);
            T.M[2][1] = sin(angle);
            T.M[2][2] = cos(angle);
            return T;
        }
    
        static matrix rotationY_matrix(double angle){
            matrix T(4, 4);
            T.M[1][1]  = T.M[3][3] = 1;
            T.M[0][0] = cos(angle);
            T.M[0][2] = sin(angle);
            T.M[2][0] = -sin(angle);
            T.M[2][2] = cos(angle);
            return T;
        }
    
        static matrix rotationZ_matrix(double angle){
            matrix T(4, 4);
            T.M[2][2]  = T.M[3][3] = 1;
            T.M[0][0] = cos(angle);
            T.M[0][1] = -sin(angle);
            T.M[1][0] = sin(angle);
            T.M[1][1] = cos(angle);
            return T;
        }
    
        static matrix scaling_matrix(vp S){
            matrix T(4, 4);
            T.M[0][0] = S.get_x();
            T.M[1][1] = S.get_y();
            T.M[2][2] = S.get_z();
            T.M[3][3] = 1;
            return T;
        }
    
        static matrix shear_xy(double angle){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[0][1] = tan(angle) ;
            return T;
        }
    
        static matrix shear_yx(double angle){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[1][0] = tan(angle) ;
            return T;
        }
    
        static matrix shear_xz(double angle){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[0][2] = tan(angle) ;
            return T;
        }
    
        static matrix shear_zx(double angle){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[2][0] = tan(angle) ;
            return T;
        }
        static matrix shear_yz(double angle){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[1][2] = tan(angle) ;
            return T;
        }
    
        static matrix shear_zy(double angle){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[2][1] = tan(angle) ;
            return T;
        }

        static matrix mirroringXY_matrix(){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[2][2] = -1;
            return T;
        }
    
        static matrix mirroringXZ_matrix(){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[1][1] = -1;
            return T;
        }
    
        static matrix mirroringYZ_matrix(){
            matrix T(4, 4);
            T.M[0][0] = T.M[1][1] = T.M[2][2] = T.M[3][3] = 1;
            T.M[0][0] = -1;
            return T;
        }
};

#endif
