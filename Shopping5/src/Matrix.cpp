/* 
 * File:   matrix.cpp
 * Author: MP-team 
 * @warning To be implemented by students. Follow the instructions given in the headers
 */


#include "Matrix.h"
#include <fstream>
#include <assert.h>

using namespace std;

//External functions
void Matrix::save(const string & nf) const {
    ofstream fsal(nf);
    if (fsal.is_open()) {
        fsal << "#matrix ";
        if (_rowLabels.size() == 0)
            fsal << "unlabeled" << endl;
        else fsal << "labeled" << endl;
        fsal << *this;
        fsal.close();
    } else cerr << "Fail creating " << nf << " file" << endl;
}

void Matrix::load(const string & nf) {
    ifstream fent(nf);
    string labeled, cad;
    clear();
    if (fent.is_open()) {
        fent >> cad >> labeled;
        fent >> nfil >> ncol;
        if (labeled == "labeled") {
            for (int i = 0; i < nfil; i++) {
                fent >> cad;
                _rowLabels.add(Pair(cad, i));
            }
            for (int i = 0; i < ncol; i++) {
                fent >> cad;
                _colLabels.add(Pair(cad, i));
            }
        }
        m = allocate(nfil, ncol);
        for (int i = 0; i < nfil; i++) {
            for (int j = 0; j < ncol; j++) {
                fent >> m[i][j];
            }
        }
        fent.close();
    } else cerr << "Fail reading " << nf << " file" << endl;
}

// Private and memory methods:

double ** Matrix::allocate(size_t r, size_t c) {
    double ** block;
    // allocate memory into block

    block = new double*[r];
    block[0] = new double [r * c];

    for (int i = 1; i < r; ++i)
        block[i] = block[i - 1] + c;
    return block;
}

void Matrix::deallocate() {

    if (m != nullptr) {
        delete[] m[0];
        delete[] m;
    }
}

void Matrix::copy(double **dest, double **org, size_t nrows, size_t ncols) {
    double access;

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            access = org[i][j];
            dest[i][j] = access;
        }
    }
}

void Matrix::clear() {
    nfil = 0;
    ncol = 0;
    deallocate();
}

void Matrix::setLabels(Index & idx, const string * labels, int nlabels) {
    idx.clear();
    int lb, ub;
    for (int i = 0; i < nlabels; i++) {
        lb = idx.lower_bound(labels[i]);
        ub = idx.upper_bound(labels[i]);
        if (lb == ub) { // it is NOT in the set
            idx.add(Pair(labels[i], i));
        } else {
            idx.clear();
        }
    }
}

int Matrix::getLabels(const Index & idx, string * labels) const {
    if (idx.size() > 0) {
        for (int i = 0; i < idx.size(); i++) {
            labels[i] = idx.at(i).getKey();
        }
    }
    return idx.size();
}

void Matrix::setValues(double valor) {
    for (int i = 0; i < nfil; i++)
        for (int j = 0; j < ncol; j++)
            at(i,j) = valor;
}

//Public methods: Contructores y Destructor

Matrix::Matrix() {
    nfil = 0;
    ncol = 0;
    _hasLabels = false;
}

Matrix::Matrix(size_t f, size_t c, double vdef) {
    if (f >= 1 && c >= 1) {   
        m = allocate(f, c);
        nfil = f;
        ncol = c;
        setValues(vdef);
        _hasLabels = false;
    }else Matrix();
}

Matrix::Matrix(const std::string *rowLabels, size_t f, const std::string * colsLabels, size_t c, double value) {
    if (f >= 1 && c >= 1) {
        m = allocate(f, c);
        nfil = f;
        ncol = c;
        setValues(value);
        setLabels(_rowLabels, rowLabels, f);
        setLabels(_colLabels, colsLabels, c);
        _hasLabels = true; 
    } else Matrix();
}

Matrix::Matrix(const Matrix& orig) {
    
    resize(orig.rows(),orig.columns()); 
    copy(m, orig.m, nfil, ncol);

    if (orig.hasLabels()) {
        _hasLabels = true;
        _rowLabels = orig._rowLabels;
        _colLabels = orig._colLabels;
    } else {
        _hasLabels = false;
    }
}

Matrix::~Matrix() {
    deallocate();
}

// Public methods: Consultors

size_t Matrix::columns() const {
    return ncol;
}

size_t Matrix::rows() const {
    return nfil;
}

bool Matrix::hasLabels() const {
    return _hasLabels;
}

int Matrix::getRowLabels(string * labels) const {
    return getLabels(_rowLabels, labels);
}

int Matrix::getColLabels(string *labels) const {
    return getLabels(_colLabels, labels);
}

int Matrix::rowIndexOf(const std::string & label) const {
    int posrow;
    bool found = false;
    for (int i = 0; i < _rowLabels.size() && !found; i++) {
        if (_rowLabels.at(i).getKey() == label) {
            posrow = _rowLabels.at(i).getPos();
            found = true;
        }
    }
    return posrow;
}

int Matrix::colIndexOf(const std::string & label) const {
    int poscol;
    bool found = false;
    for (int i = 0; i < _colLabels.size() && !found; i++) {
        if (_colLabels.at(i).getKey() == label) {
            poscol = _colLabels.at(i).getPos();
            found = true;
        }
    }

    return poscol;
}

/**
 * @brief In this method, given an index idx it returns the key in the position i, 
 * such that i is the first position in the index such that idx.at(i).getPos()== p
 * @param idx the input index
 * @param p number of 
 * @return the key for first position i in the index such that idx.at(i).getPos()==p
 */
string labelWithValuePosInIndex(const Index & idx, size_t p) {
    string salida;

    bool enc = false;
    for (int i = 0; i < idx.size() && !enc; i++) {
        if (idx.at(i).getPos() == p) {
            salida = idx.at(i).getKey();
            enc = true;
        }
    }
    return salida;
}

const double & Matrix::at(size_t f, size_t c) const {
    assert(Validar(f, c));
    return m[f][c];
}

const double & Matrix::at(const std::string & rowLabel, const std::string & colLabel)const {
    int posrow, poscol;

    posrow = rowIndexOf(rowLabel);
    poscol = rowIndexOf(colLabel);

    assert(Validar(posrow, poscol));
    return m[posrow][poscol];
}

const double & Matrix::operator()(size_t f, size_t c) const {
    return at(f, c);
}

const double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel)const {
    return at(rowLabel, colLabel);
}

std::string Matrix::labelAtRow(size_t row) const {
    return labelWithValuePosInIndex(_rowLabels, row);
}

std::string Matrix::labelAtCol(size_t col) const {
    return labelWithValuePosInIndex(_colLabels, col);
}

bool Matrix::Validar(size_t f, size_t c) const {
    bool ok = false;
    
    if (f < nfil && c < ncol && f >= 0 && c >= 0)
        ok = true;

    return ok;
}

bool Matrix::EsMultiplicable(const Matrix & k) const {
    bool multiplicable = false;

    if (ncol == k.nfil)
        multiplicable = true;

    return multiplicable;
}

// Public methods: modifiers

double & Matrix::at(size_t f, size_t c) {
    return m[f][c];
}

double & Matrix::at(const std::string & rowLabel, const std::string & colLabel) {
    int posrow, poscol;

    posrow = rowIndexOf(rowLabel);
    poscol = rowIndexOf(colLabel);

    return m[posrow][poscol];
}

double & Matrix::operator()(size_t f, size_t c) {
    return at(f, c);
}

double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel) {
    return at(rowLabel, colLabel);
}

void Matrix::resize(size_t nrows, size_t ncols, double value) {
    deallocate();
    m = allocate(nrows, ncols);
    nfil = nrows;
    ncol = ncols;
    setValues(value);
}

void Matrix::resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double value) {
    resize(nrows, ncols, value);
    _rowLabels.clear();
    _colLabels.clear();
    setLabels(_rowLabels, rowLabels, nrows);
    setLabels(_colLabels, colLabels, ncols);
}

Matrix & Matrix::normalize() {
    double unif = 1.0 / nfil;
    double sum_fil[nfil] = {0};

    for (int i = 0; i < nfil; i++)
        for (int j = 0; j < ncol; j++)
            sum_fil[i] += at(i, j);

    for (int i = 0; i < nfil; i++)
        for (int j = 0; j < ncol; j++)
            if (sum_fil[i] == 0.0)
                at(i, j) = unif;
            else
                at(i, j) = at(i, j) / sum_fil[i];

    return *this;

}

// Public methods: arithmetic operators

Matrix & Matrix::operator=(const Matrix& k) {
    if (nfil != k.rows() && ncol != k.columns())
        resize(k.nfil, k.ncol);

    copy(m, k.m, k.nfil, k.ncol);

    if (!k.hasLabels())
        _hasLabels = false;
    else
        _hasLabels = true;

    if (k.hasLabels()) {
        _rowLabels = k._rowLabels;
        _colLabels = k._colLabels;
    }

    return *this;
}

Matrix & Matrix::operator*=(const double val) {
    (*this) = (*this) * val;
    return *this;
}

Matrix & Matrix::operator+=(const double val) {
    (*this) = (*this) + val;
    return *this;
}

Matrix Matrix::operator*(const double val) const {
    for (int i = 0; i < nfil; i++)
        for (int j = 0; j < ncol; j++)
            m[i][j] *= val;

    return *this;
}

Matrix Matrix::operator+(const double val) const {
    for (int i = 0; i < nfil; i++)
        for (int j = 0; j < ncol; j++)
            m[i][j] += val;

    return *this;
}

Matrix Matrix::operator*(const Matrix & k) const {
    assert(EsMultiplicable(k));
    Matrix mult(k);
    mult.resize(nfil, k.columns());

    for (int i = 0; i < nfil; i++) {
        for (int j = 0; j < ncol; j++) {
            double suma = 0;

            for (int h = 0; h < ncol; h++)
                suma += m[i][h] * k.at(h, j);

            mult.at(i, j) = suma;
        }
    }
    return mult;
}

Matrix operator+(double ival, const Matrix & dch) {
    Matrix sum(dch);
    sum.resize(dch.nfil, dch.ncol);

    for (int i = 0; i < dch.nfil; i++)
        for (int j = 0; j < dch.ncol; j++)
            sum.at(i, j) = dch.at(i, j) + ival;

    return sum;
}

Matrix operator*(double ival, const Matrix & dch) {
    Matrix mult(dch);

    for (int i = 0; i < dch.nfil; i++)
        for (int j = 0; j < dch.ncol; j++)
            mult.at(i, j) = dch.at(i, j) * ival;

    return mult;
}


//External function: flow

ostream & operator<<(ostream & flujo, const Matrix& k) {
    flujo << k.nfil << " " << k.ncol << "\n";

    for (int i = 0; i < k._rowLabels.size(); i++)
        flujo << k._rowLabels.at(i).getKey() << "  ";

    flujo << endl;

    for (int j = 0; j < k._colLabels.size(); j++)
        flujo << k._colLabels.at(j).getKey() << "  ";

    flujo << "\n";

    for (int h = 0; h < k.nfil; h++) {
        for (int n = 0; n < k.ncol; n++)
            flujo << k.at(h, n) << "  ";
        flujo << "\n";
    }

    return flujo;
}

