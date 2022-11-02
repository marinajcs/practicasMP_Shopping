
/* 
 * File:   matrix.h
 * @author estudiante1: Carranza Sánchez, Marina Jun
 * @author estudiante2: Plaza Montes, Alberto
 * @warning To be implemented by students. Follow the instructions given in the headers
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <cassert>
#include "Index.h"

class Matrix {
private:

    double ** m = nullptr; //array of double
    Index _rowLabels; //index for row labels
    Index _colLabels; //index for col labels
    bool _hasLabels; //bool to know if the matrix has labels.    
    size_t nfil; //number of rows of the matrix
    size_t ncol; //number of columns of the matrix

    // Private and memory methods:
    
    /** 
     * @brief this method reserve memory to allocate a 2D matrix of size r x c.
     * @param r number of rows
     * @param c number of cols
     * @return the pointer to the memory block containing the data
     */
    double ** allocate(size_t r, size_t c);

    /**
     * @brief Free the memory allocated for the matrix, i.e., pointed by _data.
     * @post _data is set to nullptr 
     */
    void deallocate();

    /**
     * @brief Copies the values in a 2D matrix org with nrows and ncols to an also 2D matrix dest.
     * It is assumed that org and dest have the memory properly allocated 
     * @param dest destination matrix
     * @param org  source matrix
     * @param nrows number of rows
     * @param ncols number of cols
     */
    void copy(double **dest, double **org, size_t nrows, size_t ncols);

    /**
     * @brief Set the matrix to the default values
     */
    void clear();

    /**
     * @brief Set the set of values in labels in an index in such a way that 
     * idx.at(i).getKey() == labels[i], idx.at(i).getPos()== i
     * It is also checked that there is no repeated values in labels, in this case idx is empty.
     * @param idx The destination index
     * @param labels the source set of labels
     * @param nlabels the number of labels in labels
     * 
     */
    void setLabels(Index & idx, const std::string *labels, int nlabels);

    /**
     * @brief Get a set of labels from an Index (the set of keys stored in the index)
     * labels[0] = idx.at(0).getKey(), labels[1] = idx.at(1).getKey(), ...
     * @param idx the source index
     * @param labels the destination array of string 
     * @return the number of labels inserted
     * @prec It is assumed that labels has enough memory allocated to store idx.size() labels
     */
    int getLabels(const Index & idx, std::string *labels)const;

    /**
     * @brief Set all the values in the matrix to the value (by default 0.0)
     * @param value
     */
    void setValues(double value = 0.0);


public:

    static const int npos = -1;

    //Public methods: Contructors and Destructor
    
    /**
     * @brief Default constructor 
     * Creates a matrix with 0 rows and 0 columns
     */
    Matrix();

    /**
     * @briefCreates a 2D unlabeled matrix with size r x c, being all its elements
     * setted to the defValue
     * @param r number of rows
     * @param c number of cols
     * @param defValue value used to initialize all the elements in the matrix
     */
    Matrix(size_t r, size_t c, double defValue = 0.0);

    /** @brief Creates a 2D labeled matrix with size nrows x ncols, being all 
     * its elements setted to the defValue.
     * The rows/columns are labeled using the values in rowLabels/colsLabels in 
     * such a way that the row 0 is labeled with rowLabels[0], the row 1 is labeled 
     * with rowLabel[1] and so on.
     * Analogous criteria is used in columns.
     * In case of error we get the default matrix
     * 
     * @param rowLabels 
     * @param nrows must be >=1
     * @param colsLabels
     * @param ncols must be >=1
     * @param defValue
     * @pre It is assumed that rowLabels/colsLabels have enough memory to store 
     * at least nrows/ncols labels.
     */
    Matrix(const std::string *rowLabels, size_t nrows, const std::string * colsLabels, size_t ncols, double defValue = 0.0);

    /**
     * @brief Copy constructor, makes this matrix a copy of orig
     * @param orig
     */
    Matrix(const Matrix& orig);

    /**
     * @brief Destructor
     */
    virtual ~Matrix();

   // Public methods: Consultors

    /**
     * @brief Number of columns
     * @return number of columnos
     */
    size_t columns()const;

    /**
     * @brief Number of rows
     * @return number of rows
     */
    size_t rows() const;

    /**
     * @brief Says if the matrix it's labeled or not
     * @return true if it's a labeled matrix, not if it's not.
     */
    bool hasLabels() const;
        
    /**
     * @brief Given a label, return its associated row
     * @param the label
     * @return the number of the row
     */
    int getRowLabels(std::string *labels) const;

    /**
     * @brief Given a label, return its associated column
     * @param the label
     * @return the number of the column
     */
    int getColLabels(std::string *labels) const;
    
    /**
     * @brief Return the row number
     * @param label
     * @return row associated to the label. It returns Matrix::npos if the label 
     * is not in the Matrix
     */
    int rowIndexOf(const std::string & label) const;

    /**
     * @brief Return the col number
     * @param label
     * @return col associated to the label. It returns Matrix::npos if the label 
     * is not in the Matrix
     */
    int colIndexOf(const std::string & label) const;
    
    
    /**
     * @brief Element at M[row][col]. 
     * @pre Also check that row and col are valid positions in M ussing assert
     * @param row
     * @param col
     * @return reference to the element at M[row][col]
     */
    const double & at(size_t row, size_t col) const;
    
     /**
     * @brief Element at M[rowLabel][colLabel]. 
     * @pre Also check that row and col are valid positions in M ussing assert
     * @param row
     * @param col
     * @return reference to the element at M[rowLabel][colLabel]
     */
    const double & at(const std::string & rowLabel, const std::string & colLabel) const;

    /**
     * @brief Element at M[row][col].  
     * @param row
     * @param col
     * @return reference to the element at M[row][col]
     */
    const double & operator()(size_t row, size_t col) const;

    /**
     * @brief Element at M[rowLabel][colLabel].  
     * @param row
     * @param col
     * @return reference element at M[rowLabel][colLabel]
     */
    const double & operator()(const std::string & rowLabel, const std::string & colLabel) const;

    /**
     * @brief Gives the label associated to the row in the matrix
     * @param row number of the row
     * @return the associated label
     */
    std::string labelAtRow(size_t row) const;

    /**
     * @brief Gives the label associated to the column col in the matrix
     * @param col number of the column
     * @return the associated label
     */
    std::string labelAtCol(size_t col) const;
    
    /**
     * @brief checks that row and col are valid positions in M
     * @param rows
     * @param cols
     * @return true if row and col are valid positions in M, else false
     */
    bool Validar(size_t f, size_t c) const;
    
    /**
     * @brief checks if m is multipliable with another matrix k.
     * @param the other matrix k.
     * @return true if it's multiploable, not if it's not.
     */
    bool EsMultiplicable(const Matrix & k) const;

// Public methods: modifiers

    /**
     * @brief Element at M[row][col]. No check is done
     * @param row
     * @param col
     * @return reference to the element at M[row][col]
     */
    double & at(size_t row, size_t col);
    
    /**
     * @brief Element at M[rowLabel][colLabel]. No check is done
     * @param row
     * @param col
     * @return reference to the element at M[rowLabel][colLabel]
     */
    double & at(const std::string & rowLabel, const std::string & colLabel);
    
    /**
     * @brief Element at M[row][col]. No check is done
     * @param row
     * @param col
     * @return reference to the element at M[row][col]
     */
    double & operator()(size_t row, size_t col);

    /**
     * Element at M[rowLabel][colLabel]. No check is done
     * @param row
     * @param col
     * @return reference to the element at M[rowLabel][colLabel]
     */
    double & operator()(const std::string & rowLabel, const std::string & colLabel);

    /**
     * @brief Change the size of the matrix to nrows x ncols initializing all its values to defValue
     * @param nrows
     * @param ncols
     * @param defValue by default it is used the value 0.0
     */
    void resize(size_t nrows, size_t ncols, double defValue = 0.0);
    
    /**
     * @brief Change the size of the matrix to nrows x ncols initializing all its 
     * values to vdef. The rows/columns are labeled with rowLabels/colLabels. 
     * In case of error set the default matrix
     * @param nrows must be >=1
     * @param ncols must be >=1
     * @param vdef vauled used  by default it is used the value 0.0
     * 
     * @param rowLabels string array containing the label of the rows (this string 
     * is assumed to have length nrows)
     * @param colLabels string array containing the label of the columns (this 
     * string is assumed to have length ncols)
     */
    void resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double vdef = 0);

    /**
     * @brief Modify the values in the matrix in such a way that for each row, 
     * the sum of all its elements (in the row) is 1.0
     * @return 
     */
    Matrix & normalize();
    
    // Public methods: arithmetic operators
    
    /**
     * @brief Assign new content to the matrix, replacing its current content, 
     * and modifying its size accordingly.
     * @param m the source matrix
     * @return reference to the matrix
     */
    Matrix & operator=(const Matrix & k);

    /**
     * @brief Multiply each element in the matrix by val
     * @param val
     * @return reference to the matrix
     */
    Matrix & operator*=(const double val);

    /**
     * @brief Add a constant value to each element in the matrix
     * @param val
     * @return reference to the matrix
     */
    Matrix & operator+=(const double val);
    
    /**
     * @brief Multiply the matrix by a constant val
     * @param val
     * @return a new matrix with the values M x val
     */
    Matrix operator*(const double val) const;

    /**
     * @brief Add val to each element
     * @param val
     * @return a new matrix with values M+val
     */
    Matrix operator+(const double val) const;

    /**
     * @brief Matrix multiplication. 
     * @pre It check that *this and m have the proper dimensions ussing assert
     * @param m a matrix object  
     * @return a new matrix containing (*this) x M
     */
    Matrix operator*(const Matrix & k) const;

        // INPUT / OUTPUT 
    /**
     * Save the matrix in a file in the following format
     
        #matrix labeled|unlabeled
        number_of_rows number_of_columns
        [labelr1 labelr2 label_nrows]
        [labelc1 labelc2 label_ncols]
        m[0][0]....m[0][ncols]
        m[1][0]....m[1][ncols]
        ...
        m[nrows][0] ...m[nrows][ncols]

     * where the first line uses the magic word "#matrix" and indicates whether 
     * the matrix is labeled or unlabeled
     * in the case the matrix has no labels at rows and columns, the third and four lines are empty
     * 
     * For example:
     * 
        #matrix labeled
        2 2
        A B
        X Y
        1 2
        3 4
 
        #matrix unlabeled
        2 2
        1.2 2.2
        3.2 4.2

     *      
     * @param filename name of the file
     */
    void save(const std::string & filename) const;
    
    /**
     * @brief Load a matrix from the file filename
     * It is assumed that the file has the format above, otherwise the performace is undefined
     * @param filename
     */
    void load(const std::string & filename);
    
    // friend methods, performance defined outside the class
    friend std::ostream & operator<<(std::ostream & os, const Matrix & m);

    friend Matrix operator+(double ival, const Matrix & dch);
    friend Matrix operator*(double ival, const Matrix & dch);
};

//External function: More arithmetic operators
/**
 * @brief Return a new matrix obtained by computing: val + M
 * @param ival
 * @param dch
 * @return resulting matrix
 */
Matrix operator+(double ival, const Matrix & M);

/**
 * @brief Return a new matrix obtained by computing: val * M
 * @param ival
 * @param M
 * @return resulting matrix
 */
Matrix operator*(double ival, const Matrix & M);

//External function: flow

/** @brief Insert the data representing the matrix into the ostream os with the following format
 * 
        number_of_rows number_of_columns
        [labelr1 labelr2 label_nrows]
        [labelc1 labelc2 label_ncols]
        m[0][0]....m[0][ncols]
        m[1][0]....m[1][ncols]
        ...
        m[nrows][0] ...m[nrows][ncols]
 
 * @param os output stream
 * @param m the matrix object
 * @return os the output stream
 */
std::ostream & operator<<(std::ostream & os, const Matrix & m);

#endif /* MATRIX_H */
