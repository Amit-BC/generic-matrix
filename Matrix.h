//
//  main.cpp
//  Matrix
//
//  Created by Amit Ben shitrit on 25/06/2020.
//  Copyright © 2020 Amit Ben shitrit. All rights reserved.
//
/*
 This file exports Matrix class which provides generic type matrix object.
*/
#ifndef Matrix_h
#define Matrix_h
#include <iostream>
#include <string>
#include "Auxiliaries.h"
namespace mtm{

/**
* Class: Matrix<ValueType>
* ------------------------
* This class stores 2d Array (aka matrix), and its dimension.
*/
template<typename T>
class Matrix{
private:
    Dimensions m_Dims;
    T** m_Array;
    
public:
    /**
    * Constructor: Matrix
    * Usage: Matrix<T> mat(mtm::Dimensions dims);
    *        Matrix<T> mat(mtm::Dimensions dims, T initializer);
    * ---------------------------------------
    @param dims the dimensions of the matrix to construct, must be 2 positive numbers.
    @param initializer a specific value to initialize all matrix element, if not given will get default value - 0 for numeric types, "" (empty string) for std::string.
    @exception IllegalInitializtion - the constructor will throw this error if illegal dimensions were passed (row or col >=0)
    @exception bad_alloc - will be thrown if memory allocation failed (by new)
    */
    Matrix(mtm::Dimensions dims,const T& initializer = T());

    /**
    * Destructor: ~Matrix
    * -------------------
    * Frees any heap storage allocated by this matrix.
    */
    ~Matrix();
    
    /**
    * Copy constructor: Matrix
    * Usage: Matrix<T>(Matrix<T> &mat)
    *---------------------------------------
    @param other reference to the matrix to copy.
    @exception bad_alloc - will be thrown if memory allocation failed (by new)
    */
        
    Matrix(const Matrix &other);

    /**
    * operator=
    * Usage: matrix =  other
    *---------------------------------------
    * The operator is assigning the matrix, dealing with realese of current menmory and copying into the object.
    *can be used to initialize new matrix and or reassigning an exisiting one.
    @param other reference to the matrix to copy.
    @exception bad_alloc - will be thrown if memory allocation failed (by new)
    */
    
    Matrix& operator=(Matrix const &other);
    
    /**
    * Method: height
    * Usage: mat.height()
    * -----------------------------
    @returns height (number of row) of this matrix.
    */
        
    int height() const;
        
        
    /**
    * Method: width
    * Usage: mat.width()
    * -----------------------------
     @return width (number of columns) of this matrix.
    */
        
    int width() const;
        
        
    /**
    * Method: size
    * Usage: mat.size()
    * -----------------------------
     @return size (number of elemnts) of this matrix.
    */

    int size() const;

    
    /**
    * static function: Diagonal
    * Usage: Diagonal(size,init)
    * -----------------------------
    * This static function creates new diagonal matrix with init value in the diagonal and default value elsewhere.
    @param size number of rows and columns of the diagonal matrix.
    @param init initialization value for diagonal elements.
    @return new diagonal matrix.
    @exception IllegalInitializtion - the constructor will throw this error
    if illegal dimensions were passed (size >=0).
    @exception bad_alloc - will be thrown if memory allocation failed (by new).
    */
        
    static Matrix<T> Diagonal(int size, T init);
    
    
    /**
    * method: transpose
    * Usage: mat.transpost()
    * -----------------------------
    * This method create a new transposed object of this matrix. (swapped rows and cols).
    @return new transposed matrix.
    @exception bad_alloc - will be thrown if memory allocation failed (by new).
    */
        
    Matrix transpose() const;
    
    
    /**
    * operator +
    * Usage: mat1 + mat2
    * -----------------------------
    * This operator creates a new matrix in which each element is the sum of the specified matrices elements in the same position. The matrices needs to be of the same dimensions for this operator to work.
    @return new sum matrix.
    @param mat1 the matrix to add.
    @exception bad_alloc - will be thrown if memory allocation failed (by new).
    @exception DimensionMismatch if the given matrices are not of the same dimensions.
    */
    Matrix operator+(const Matrix &mat1) const;
    
    
    /**
    * operator - (unary)
    * Usage: -mat1
    * -----------------------------
    *This operator creates a new matrix in which each element has swapped sign.
    @return new swapped signs matrix.
    @exception bad_alloc - will be thrown if memory allocation failed (by new).
    @remarks numeric types only,
    */
    Matrix operator-() const;
    
    
    /**
    * operator - (binary)
    * Usage: mat1-mat2
    * -----------------------------
    *This operator creates new matrix object which is the substraction two matrices 'element by element'.
    @return new substracted matrix
    @param mat the matrix to substract.
    @exception bad_alloc - will be thrown if memory allocation failed (by new).
    @exception DimensionMismatch if the given matrices are not of the same dimensions.
    @remarks numeric types only. matrices need to have same dimensions.
    */
    Matrix operator-(const Matrix mat) const;
    
    
    
    /**
    * operator+= (with object of type T)
    * Usage: mat1 += obj
    * -----------------------------
    *This operator adds an object of type T to each of the matrix elements.
    @param obj - the T type object we want to add to the matrix.
    @remarks change the matrix itself, not creating a new copy.
    */
        
    Matrix& operator+=(T obj);
    
    
    /**
    * friend operator+ (with object of type T)
    * Usage: mat1 + obj
           obj + mat1
    * -----------------------------
    *This operator create a copy of the matrix and adds the object of type T to each of the matrix elements.
    @param obj - the T type object we want to add to the matrix.
    @param mat - the matrix we want to copy and add obj to.
    @remarks creates a new matrix.
    @exception bad_alloc - will be thrown if memory allocation failed (by new).
    */
        
    template<typename U>
    friend Matrix<U> operator+(U obj, const Matrix<U> mat);
    template<typename U>
    friend Matrix<U> operator+(const Matrix<U> mat, U obj);
    
    
    /**
    * operator() (row_index, col_index)
    * Usage: mat(row_index, col_index)
    * -----------------------------
    *This operator gives access to the actual elements in the matrix, and enable to change them as well.
    @param row_index an integer representing the row index
    @param col_index an integer representing the column index
    @remarks can be used to change element value.
    @return - reference to the matrix element in the given position.
    @exception AccessIllegalElement is thrown if the given indices are out of the scope of the matrix.
    */
     T &operator()(int row_index, int col_index) const;
    

    
    /**
    *Comparison operators < > <= >= == !=
    * Usage: mat @ compare (@ is the wanted operator)
    * -----------------------------
    *These operators are used to compare T object to each element of the matrix and create a bollean matrix of the same size that represent the result.
    @param compare the object to compare each item in the matrix to.
    @remarks  non commutative - one sided only - matrix on left , compare on the right.
                         types that support the logical comparison operators only.
    @return boolean matrix in which each element is true or false based on the comparison in the same position.
    @exception bad_alloc will be thrown if memory allocation failed (by new).
    */

    Matrix<bool> operator<(T compare) const;
    Matrix<bool> operator>(T compare) const;
    Matrix<bool> operator>=(T compare) const;
    Matrix<bool> operator<=(T compare) const;
    Matrix<bool> operator==(T compare) const;
    Matrix<bool> operator!=(T compare) const;
        
    /**
    *Boolean functions
    * all - checks if all elements in matrix are not 0.
    * Usage: all(mat)
    * -----------------------------
     @param mat - the matrix to be checked.
     @return true - iff all elements are not 0
    *                   false - if there is at least one element equal to 0
     @remarks (assumption) U is numeric type.
    *-----------------------------
     */
        
    template <typename U>
    friend bool any(Matrix<U> mat);
        
    /** any - return true if at least one element that is not 0 exists.
    * Usage: any(mat)
    * -----------------------------
    @param mat - the matrix to be checked.
    @return true if at least one element in the matrix is not 0.
    *                 false if all elements in matrix are equal to 0.
     @remarks (assumptions) U is numeric  type.
     
    */
    template <typename U>
    friend bool all(Matrix<U> mat);


    /** method apply - applying a class operator() on each matrix element.
    * Usage: any(mat)
    * -----------------------------
    @param operation - class object that supports operator()
    @return new matrix object in which each element is the result of applying the class () operator on each element.
    @remarks (assumptions) the operator() of the class is well defined on T type of the matrix elements.
    @exception bad_alloc will be thrown if memory allocation failed (by new).
    */
    template <typename U>
    Matrix<T> apply(U operation) const;

        
    /**
    *operator<<
    * Usage: <<mat
    * -----------------------------
     The function uses the aux function printMatrix in Auxiliaries.h in order to print matrix objects in a specific way.
    @param stream - reference to the output stream (std::cout)
    @param matrix - the matrix we want to print.
    @return reference to the stream we make.
    @remarks toString function works.
    */
    template <typename U>
    friend std::ostream &operator<<(std::string &stream, const Matrix<U> &matrix);
    
    
    /**
    * Class: iterator
    * ------------------------
    * Matrix<T> class has inner iterator type that points to an element in the matrix and let you move forward in the matrix, read and write to each element.
     the members are:
     pointer to matrix element.
     dimensions information.
     position of the indices of the pointer to track the position in the matrix
     the class consists of:
     constructor - creates a new iterator given matrix and indices. private.
     default destructor, copy constructor and operator=.
     supports ++it and it++.
     operator* dereferncing - iterator can rewrite value, const_iterator can read only.
     basic boolean comparison operators == !=.
     if trying to access an element out of the scope of the matrix an AccessIllegalElement will be thrown.
    */
        class iterator
        {
        private:
            T **matrix;
            int row_index, col_index;
            int row_num, col_num;
            
            iterator(const Matrix<T> &mat, int row = 0, int col = 0);
            friend class Matrix<T>;

        public:
            T &operator*() const;
            iterator &operator++();
            iterator operator++(int);

            bool operator==(const iterator &it) const;
            bool operator!=(const iterator &it) const;

            iterator(const iterator &) = default;
            ~iterator() = default;
            iterator operator=(const iterator &it);
        };
        
        
    /**
    * Class: const_iterator
    * ------------------------
    * Matrix<T> class has inner const_iterator type that points to an element in the matrix and let you move forward in the matrix, and read only, cannot mute the matrix.
    */
        

        class const_iterator
        {
        private:
            Matrix<T>::iterator it;

            const_iterator(Matrix<T>::iterator init);
            friend class Matrix<T>::iterator;

        public:
            T operator*() const;
            const_iterator &operator++();
            const_iterator operator++(int);

            bool operator==(const const_iterator &other) const;
            bool operator!=(const const_iterator &other) const;

            const_iterator(const const_iterator &) = default;
            ~const_iterator() = default;
            const_iterator operator=(const const_iterator &it);
            friend const_iterator Matrix<T>::begin() const;
            friend const_iterator Matrix<T>::end() const;
        };
    
    
    /** method begin
    * Usage: mat.begin()
    * -----------------------------
    The function creates a new iterator type that points to the first element of the matrix.
    @return iterator/const_iterator to the first element of the matrix..
    */
        
    iterator begin();
    const_iterator begin() const;
        
    /** method end
    * Usage: mat.end()
    * -----------------------------
    The function creates a new iterator type that points to the element after the last one of the matrix.
    @return iterator/const_iterator to one passed the last element of the matrix..
    */
        
    iterator end();
    const_iterator end() const;
        
    
    /**
     Exceptions for the class:
     */
    
    /**
    * Exception: DimensionMismatch
    thrown when trying to use two matrices with different dimension for certain operations such as matrix addition.
    *--------------------------------------
     members are the dimensions of the two matrices and a string that will be sent as const char*, so that the information it points to won't be deleted.
    */
    struct DimensionMismatch : public std::exception
    {
    private:
        mtm::Dimensions m_Dims1, m_Dims2;
        std::string error_str;

    public:
        DimensionMismatch(mtm::Dimensions dims1, mtm::Dimensions dims2);
        const char *what() const throw();
    };
    
    /**
       * Exception: IllegalInitialization
       thrown when trying to initialize matrix with illegal dimension - negative or size 0.
    */
    struct IllegalInitialization : public std::exception
    {
        const char *what() const throw();
    };
    /**
        * Exception: AccessIllegalElement
        thrown when trying to access matrix element out of the array range - negative index, or indices the pass the dimensions of the matrix.
    */
    
    struct AccessIllegalElement : public std::exception
    {
        const char *what() const throw();
    };
    
};

//friends functions declaration
template<typename T>
Matrix<T> operator+(T obj, const Matrix<T> mat);

template<typename T>
Matrix<T> operator+(const Matrix<T> mat, T obj);

template <typename T>
bool all(Matrix<T> mat);

template <typename T>
bool any(Matrix<T> mat);

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix);



//Constructor allocating memory and creates a new matrix object, initializng its element to init or the default T class value.
template<typename T>
Matrix<T>::Matrix(Dimensions dims, const T& init):
m_Dims(dims.getRow(), dims.getCol())
{
    if(m_Dims.getRow() <= 0 || m_Dims.getCol() <= 0)
    {
        Matrix<T>::IllegalInitialization error;
        throw error;
    }

    
    m_Array = new T *[m_Dims.getRow()];

    for (int i = 0; i < m_Dims.getRow(); i++)
    {
        try{
            m_Array[i] = new T[m_Dims.getCol()];
        
        
            for (int j = 0; j < m_Dims.getCol(); j++)
            {
                m_Array[i][j] = init;
            }
            
        }catch(std::bad_alloc& e){
            for(int k = 0; k < i; k++){
                delete[] m_Array[k];
            }
            delete[] m_Array;
            throw e;
        }
    }
}


//Destructor frees all allocated memory, item cannot be accessed afterwards.
template <typename T>
Matrix<T>::~Matrix()
{
    //    std::cout<<"Destructor in action"<<std::endl;
    for (int i = 0; i < m_Dims.getRow(); i++)
    {
        delete[] m_Array[i];
    }
    delete[] m_Array;
}


//Copy constructor provides deep copy by value and not by reference - creates a new identical matrix in differen part of the memory.
template <typename T>
Matrix<T>::Matrix(const Matrix &other):
m_Dims(other.m_Dims),
m_Array(new T* [m_Dims.getRow()])
{
    for (int i = 0; i < m_Dims.getRow(); i++)
    {
        try{
            m_Array[i] = new T[m_Dims.getCol()];
 
        
            for (int j = 0; j < m_Dims.getCol(); j++)
            {
                m_Array[i][j] = other.m_Array[i][j];
            }
        }catch(std::bad_alloc& e){
            for(int k = 0; k < i; k++){
                delete[] m_Array[k];
                
            }
            delete [] m_Array;
            throw e;
        }
    }
}


//assignment operator used to create a new matrix copy or reassignig matrix object. release memory of exisiting object.
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix const &other)
{
    T** ptr = new T* [other.m_Dims.getRow()];

    for (int i = 0; i < other.m_Dims.getRow(); i++)
    {
        try{
                ptr[i] = new T[other.m_Dims.getCol()];
            
                for (int j = 0; j < other.m_Dims.getCol(); j++)
                {
                   ptr[i][j] = other.m_Array[i][j];
                }
           }catch(std::bad_alloc& e){
               
               for(int k = 0; k < i; k++){
                   delete[] ptr[k];
               }
               delete[] ptr;
               throw e;
           }
    }
    
    for (int i = 0; i < m_Dims.getRow(); i++)
    {
        delete[] m_Array[i];
    }
    delete[] m_Array;
    
    m_Dims = other.m_Dims;
    m_Array = ptr;
    return *this;
           
}

//Providing basic dimension information
template <typename T>
int Matrix<T>::height() const
{
    return m_Dims.getRow();
}

template <typename T>
int Matrix<T>::width() const
{
    return m_Dims.getCol();
}

template <typename T>
int Matrix<T>::size() const
{
    return ( m_Dims.getRow() * m_Dims.getCol() );
}


template <typename T>
Matrix<T> Matrix<T>::Diagonal(int size, T init)
{
    mtm::Dimensions dims(size, size);
    Matrix<T> diagonal(dims);
    for (int i = 0; i < size; i++)
    {
        diagonal.m_Array[i][i] = init;
    }
    return diagonal;
}


template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    mtm::Dimensions dims(m_Dims.getCol(),m_Dims.getRow());
    Matrix<T> transposed(dims);
    for (int i = 0; i < m_Dims.getCol(); i++)
    {

        for (int j = 0; j < m_Dims.getRow(); j++)
        {
            transposed.m_Array[i][j] = m_Array[j][i];
        }
    }
    return transposed;
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat) const
{
    if (m_Dims.getCol() != mat.m_Dims.getCol() || m_Dims.getRow() != mat.m_Dims.getRow())
    {
        mtm::Dimensions dims1((*this).height(), (*this).width());
        mtm::Dimensions dims2(mat.height(), mat.width());
        DimensionMismatch error(dims1, dims2);
        throw error;
    }
    
    Matrix<T> sum = *this;
    for (int i = 0; i < m_Dims.getRow(); i++)
    {
        for (int j = 0; j < m_Dims.getCol(); j++)
        {
            sum.m_Array[i][j] += mat.m_Array[i][j];
        }
    }
    
    return sum;
    
}


template <typename T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix<T> after_mat(*this);

    for (int i = 0; i < m_Dims.getRow(); i++)
    {
        for (int j = 0; j < m_Dims.getCol(); j++)
        {
            after_mat.m_Array[i][j] = (-1) * m_Array[i][j];
        }
    }

    return after_mat;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix mat) const
{
    return ( (*this)+(-mat) );
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(T obj)
{
    for(int i = 0; i < m_Dims.getRow(); i++){
        
        for(int j = 0; j < m_Dims.getCol(); j++){
            m_Array[i][j] += obj;
        }
    }
    return *this;
}


template<typename T>
Matrix<T> operator+(T obj, const Matrix<T> mat)
{
    Matrix<T> sum(mat);
    for(int i = 0; i < mat.height(); i++){
        for(int j = 0; j < mat.width(); j++){
            sum.m_Array[i][j] = obj + sum.m_Array[i][j];
        }
    }
    return sum;
}

template<typename T>
Matrix<T> operator+(const Matrix<T> mat, T obj)
{
    Matrix<T> sum(mat);
    for(int i = 0; i < mat.height(); i++){
        for(int j = 0; j < mat.width(); j++){
            sum.m_Array[i][j] =sum.m_Array[i][j] + obj;
        }
    }
    return sum;
}


template <typename T>
T &Matrix<T>::operator()(int row_index, int col_index) const
{
    if (row_index >= m_Dims.getRow() || row_index < 0 || col_index >= m_Dims.getCol() || col_index < 0)
    {
        AccessIllegalElement error;
        throw error;
    }
    return m_Array[row_index][col_index];
}


template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
{
    typename Matrix<T>::const_iterator it_begin = matrix.begin();
    typename Matrix<T>::const_iterator it_end = matrix.end();

    return mtm::printMatrix(os, it_begin, it_end, matrix.width());
}


template <typename T>
Matrix<bool> Matrix<T>::operator<(T compare) const
{
    mtm::Dimensions dims(m_Dims.getRow(), m_Dims.getCol());
    Matrix<bool> to_return(dims, false);

    for (int i = 0; i < m_Dims.getRow(); i++)
    {

        for (int j = 0; j < m_Dims.getCol(); j++)
        {

            if ( (m_Array[i][j]) < compare)
            {
                to_return(i,j) = true;
            }
        }
    }
    return to_return;
}

template <typename T>
Matrix<bool> Matrix<T>::operator>(T compare) const
{
    mtm::Dimensions dims(m_Dims.getRow(), m_Dims.getCol());
    Matrix<bool> to_return(dims, false);

    for (int i = 0; i < m_Dims.getRow(); i++)
    {

        for (int j = 0; j < m_Dims.getCol(); j++)
        {

            if ( (m_Array[i][j]) > compare)
            {
                to_return(i,j) = true;
            }
        }
    }
    return to_return;
}

template <typename T>
Matrix<bool> Matrix<T>::operator<=(T compare) const
{
    mtm::Dimensions dims(m_Dims.getRow(), m_Dims.getCol());
    Matrix<bool> to_return(dims, false);

    for (int i = 0; i < m_Dims.getRow(); i++)
    {

        for (int j = 0; j < m_Dims.getCol(); j++)
        {

            if ( (m_Array[i][j]) <= compare)
            {
                to_return(i,j) = true;
            }
        }
    }
    return to_return;
}


template <typename T>
Matrix<bool> Matrix<T>::operator>=(T compare) const
{
    mtm::Dimensions dims(m_Dims.getRow(), m_Dims.getCol());
    Matrix<bool> to_return(dims, false);

    for (int i = 0; i < m_Dims.getRow(); i++)
    {

        for (int j = 0; j < m_Dims.getCol(); j++)
        {

            if ( (m_Array[i][j]) >= compare)
            {
                to_return(i,j) = true;
            }
        }
    }
    return to_return;
}

template <typename T>
Matrix<bool> Matrix<T>::operator==(T compare) const
{
    mtm::Dimensions dims(m_Dims.getRow(), m_Dims.getCol());
    Matrix<bool> to_return(dims, false);

    for (int i = 0; i < m_Dims.getRow(); i++)
    {

        for (int j = 0; j < m_Dims.getCol(); j++)
        {

            if ( (m_Array[i][j]) == compare)
            {
                to_return(i,j) = true;
            }
        }
    }
    return to_return;
}

template <typename T>
Matrix<bool> Matrix<T>::operator!=(T compare) const
{
    mtm::Dimensions dims(m_Dims.getRow(), m_Dims.getCol());
    Matrix<bool> to_return(dims, false);

    for (int i = 0; i < m_Dims.getRow(); i++)
    {

        for (int j = 0; j < m_Dims.getCol(); j++)
        {

            if ( (m_Array[i][j]) != compare)
            {
                to_return(i,j) = true;
            }
        }
    }
    return to_return;
}





template <typename T>
bool all(Matrix<T> mat)
{
    for (int i = 0; i < mat.height(); i++)
    {
        for (int j = 0; j < mat.width(); j++)
        {
            if ( bool(mat.m_Array[i][j]) == false)
            {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool any(Matrix<T> mat)
{
    for (int i = 0; i < mat.height(); i++)
    {
        for (int j = 0; j < mat.width(); j++)
        {
            if ( bool(mat.m_Array[i][j]) == true )
            {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
template <typename U>
Matrix<T> Matrix<T>::apply(U operation) const
{
    Matrix operated = *this;
    for (int i = 0; i < m_Dims.getRow(); i++)
    {
        for (int j = 0; j < m_Dims.getCol(); j++)
        {
            operated.m_Array[i][j] = operation(operated.m_Array[i][j]);
        }
    }
    return operated;
}


template <typename T>
typename Matrix<T>::iterator Matrix<T>::begin()
{
    return iterator(*this);
}

template <typename T>
typename Matrix<T>::iterator Matrix<T>::end()
{
    int row_index = m_Dims.getRow() - 1;
    int col_index = m_Dims.getCol();
    return iterator(*this, row_index, col_index);
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const
{
    return const_iterator(*this);
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::end() const
{
    int row_index = m_Dims.getRow() - 1;
    int col_index = m_Dims.getCol();
    Matrix<T>::iterator init(*this, row_index, col_index);
    return const_iterator(init);
}

//iterator class methods
template <typename T>
Matrix<T>::iterator::iterator(const Matrix<T> &mat, int row, int col)
{
    row_num = mat.height();
    col_num = mat.width();
    row_index = row;
    col_index = col;
    matrix = mat.m_Array;
}

template <typename T>
T &Matrix<T>::iterator::operator*() const
{
    if (row_index >= row_num || col_index >= col_num)
    {
        AccessIllegalElement error;
        throw error;
    }
    return matrix[row_index][col_index];
}

template <typename T>
typename Matrix<T>::iterator &Matrix<T>::iterator::operator++()
{
    col_index++;
    if (col_index == col_num && row_index != row_num - 1)
    {
        col_index = 0;
        row_index++;
    }
    
    return *this;
}

template <typename T>
typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int a)
{
    Matrix<T>::iterator to_return = *this;
    ++(*this);
    return to_return;
}

template <typename T>
bool Matrix<T>::iterator::operator==(const iterator &it) const
{
    if (matrix == it.matrix && row_index == it.row_index && col_index == it.col_index)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Matrix<T>::iterator::operator!=(const iterator &it) const
{
    if (((*this) == it) == true)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <typename T>
typename Matrix<T>::iterator Matrix<T>::iterator::operator=(const iterator &it)
{
    return iterator(it);
}

//const_iterator class methods
template <typename T>
Matrix<T>::const_iterator::const_iterator(Matrix<T>::iterator init) : it(init)
{
}

template <typename T>
T Matrix<T>::const_iterator::operator*() const
{
    return *it;
}

template <typename T>
typename Matrix<T>::const_iterator &Matrix<T>::const_iterator::operator++()
{
    ++it;
    return *this;
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int a)
{
    Matrix<T>::iterator to_return = it;
    ++it;
    return to_return;
}

template <typename T>
bool Matrix<T>::const_iterator::operator==(const const_iterator &other) const
{
    return (it == other.it);
}

template <typename T>
bool Matrix<T>::const_iterator::operator!=(const const_iterator &other) const
{
    return (it != other.it);
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator=(const const_iterator &it)
{
    return const_iterator(it.it);
}

template <typename T>
const char *Matrix<T>::AccessIllegalElement::what() const throw()
{
    return "Mtm matrix error: An attempt to access an illegal element";
}

template <typename T>
const char *Matrix<T>::IllegalInitialization::what() const throw()
{
    return "Mtm matrix error: Illegal initialization values";
}

template<typename T>
Matrix<T>::DimensionMismatch::DimensionMismatch(mtm::Dimensions dims1, mtm::Dimensions dims2) : m_Dims1(dims1), m_Dims2(dims2)
{
    error_str= "Mtm matrix error: Dimension mismatch: ";
    error_str = error_str + m_Dims1.toString() + " " + m_Dims2.toString();
}
template <typename T>
const char *Matrix<T>::DimensionMismatch::what() const throw()
{
    const char* error = error_str.c_str();
    return error;
}
}

#endif /* Matrix_h */

