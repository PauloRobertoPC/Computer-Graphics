#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>
#include <vector>
#include "comparator.hpp"
#include "vp.hpp"

class matrix{
    private: 
        std::vector<std::vector<double>> M;
    public:
        matrix();
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
        bool operator==(matrix A);          //equality test
        
        static matrix identity(int n){
            matrix A(n, n);
            for(int i = 0; i < n; i++) A.M[i][i] = 1.0;
            return A;
        }

        static matrix vp_to_matrix(vp v, bool point = true){
            matrix V(4, 1);
            V.M[0][0] = v.get_x();
            V.M[1][0] = v.get_y();
            V.M[2][0] = v.get_z();
            V.M[3][0] = point;
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

        static matrix house_holder(vp n){
            matrix normal = matrix::vp_to_matrix(n);
            matrix HH = matrix::identity(4) - normal*(~normal)*2;
            HH.M[0][3] = HH.M[1][3] = HH.M[2][3] = HH.M[3][0] = HH.M[3][1] = HH.M[3][2] = 0;
            HH.M[3][3] = 1;
            return HH;
        }
        
        static matrix mirror_arbitrary_matrix(vp n, vp p){
            return matrix::translation_matrix(p)*matrix::house_holder(n)*matrix::translation_matrix(-p); 
        }

        static matrix new_coordinates_matrix(vp i, vp j, vp k, vp o){ //x' -> x
            matrix T(4, 4);
            T.M[0][0] = i.get_x(); T.M[1][0] = i.get_y(); T.M[2][0] = i.get_z();
            T.M[0][1] = j.get_x(); T.M[1][1] = j.get_y(); T.M[2][1] = j.get_z();
            T.M[0][2] = k.get_x(); T.M[1][2] = k.get_y(); T.M[2][2] = k.get_z();
            T.M[0][3] = o.get_x(); T.M[1][3] = o.get_y(); T.M[2][3] = o.get_z();
            T.M[3][3] = 1;
            return T;
        }
    
        static matrix new_coordinates_inverse_matrix(vp i, vp j, vp k, vp o){ //x -> x'
            matrix T(4, 4);
            T.M[0][0] = i.get_x(); T.M[0][1] = i.get_y(); T.M[0][2] = i.get_z();
            T.M[1][0] = j.get_x(); T.M[1][1] = j.get_y(); T.M[1][2] = j.get_z();
            T.M[2][0] = k.get_x(); T.M[2][1] = k.get_y(); T.M[2][2] = k.get_z();
            T.M[0][3] = -(i*o); T.M[1][3] = -(j*o); T.M[2][3] = -(k*o);
            T.M[3][3] = 1;
            return T;
        }

        static matrix rotation_arbitrary_matrix(vp o, vp direction, double angle){
            direction = direction/(~direction);
            vp aux = direction; aux.set_x(direction.get_x()-1);
            vp j = direction % aux; j = j/(~j);
            vp i = j % direction;
            return matrix::new_coordinates_matrix(i, j, direction, o) *
                   matrix::rotationZ_matrix(angle) *
                   matrix::new_coordinates_inverse_matrix(i, j, direction, o);
        }
};

#endif
