/*
CS 302 Assignment 4

Name: Keith Beauvais, 5005338658, CS 302 Assignment 4
*/
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>

std::vector <std::vector<int> > matrix1;
std::vector <std::vector<int> > matrix2;
std::vector <std::vector<int> > matrixProduct;

void const multiplyVectors(int, int, int);
std::mutex t_lock;

int main(){
    std::string filename;
    std::ifstream infile;
    int n1, m1, n2, m2, userInteger, dim, maxThreads;


    std::cout<< "Enter filename: ";
    std::cin >> filename;
    // Reads in file

    infile.open(filename);
    // reads in matrix 1 info
    // reads in top header for size of matrix
    infile >> userInteger;
    n1 = userInteger;
    infile >> userInteger;
    m1 = userInteger;


    infile >> userInteger;

    //Matrix 1 work 
    matrix1.resize(n1);
    
    for(int i = 0; i<matrix1.size(); i++){
            matrix1[i].resize(m1);
    }
    for(int i = 0; i < matrix1.size(); i++){
        for (int j = 0; j < matrix1[i].size(); j++){
            matrix1[i][j] = userInteger;
            infile >> userInteger;
        } 
    }

    // reads in matrix 2 info
    // reads in top header for size of matrix
    n2 = userInteger;
    infile >> userInteger;
    m2 = userInteger;


    infile >> userInteger;
    //Matrix 2 work 
    matrix2.resize(n2);
    for(int i = 0; i<matrix2.size(); i++){
            matrix2[i].resize(m2);
    }
    for(int i = 0; i < matrix2.size(); i++){
        for (int j = 0; j < matrix2[i].size(); j++){
            matrix2[i][j] = userInteger;
            infile >> userInteger;
        } 
    }

     matrixProduct.resize(n1);
    
    // initialize the product matrix
    for(int i = 0; i<matrixProduct.size(); i++){
            matrixProduct[i].resize(m2);
    }
    for(int i = 0; i < matrixProduct.size(); i++){
        for (int j = 0; j < matrixProduct[i].size(); j++){
            matrixProduct[i][j] = 0;
        } 
    }
  
    std::vector< std::thread > threadPool;

    maxThreads = std::thread::hardware_concurrency();
   
    for(int i = 0; i<n1; i++){
        for(int j = 0; j<m2; j++ ){
            for(int k = 0; k< m1; k++ ){

                threadPool.push_back(std::thread(multiplyVectors, i, k, j));

                if (threadPool.size() % maxThreads == 0){

                    for (int l = 0; l < threadPool.size(); l++){
                        threadPool[l].join();
                    }
                    
                    threadPool.clear(); 
                }
            }
        }
    }
   

    for(int i = 0; i< n1; i++){
        for (int j = 0; j <m2; j++){
            std::cout<<matrixProduct[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    

    return 0;

}
/* 
void const multiplyVectors(int row, int col1, int col2)- Multiplies the matrix 1 and matrix 2
as it passes in row, column 1 and column 2

return value - returns true or false bases on parameters listed above
*/
void const multiplyVectors(int row, int col1, int col2){

    t_lock.lock(); //lock this section

    matrixProduct[row][col2] += matrix1[row][col1]*matrix2[col1][col2];

    t_lock.unlock(); //unlock this section
    

}