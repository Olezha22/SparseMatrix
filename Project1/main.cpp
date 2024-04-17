#include <iostream>
#include <stdexcept>
#include <map>

using namespace std;

template<typename T>
struct MatrixNode {
    int col;
    T data;
    MatrixNode<T>* next;

    MatrixNode(int c, const T& d) : col(c), data(d), next(nullptr) {}
};

template<typename T>
class SparseMatrix {
private:
    int rows, cols;
    MatrixNode<T>** rowHeads; 

public:
    SparseMatrix(int rows, int cols) : rows(rows  ), cols(cols  ) {
        if (rows <= 0 || cols <= 0) {
            throw invalid_argument("Invalid matrix size");
        }
        rowHeads = new MatrixNode<T>*[rows];
        for (int i = 0; i < rows; ++i) {
            rowHeads[i] = nullptr;
        }
    }


    ~SparseMatrix() {
    }

    void addElement(int row, int col, const T& data) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Index out of range");
        }
        MatrixNode<T>* newNode = new MatrixNode<T>(col, data);
        newNode->next = rowHeads[row];
        rowHeads[row] = newNode;
    }

    T getElement(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Index out of range");
        }

        MatrixNode<T>* current = rowHeads[row];
        while (current != nullptr) {
            if (current->col == col) {
                return current->data;
            }
            current = current->next;
        }
        return 0;
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                    cout << getElement(i, j) << " ";
            }
            cout << endl;
        }
    }

    


    SparseMatrix<int> operator+(const SparseMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrices must have the same dimensions for subtraction");
        }

        SparseMatrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.addElement(i, j, getElement(i, j) + other.getElement(i, j));
            }
        }
        return result;
    }

    SparseMatrix operator-(const SparseMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrices must have the same dimensions for subtraction");
        }

        SparseMatrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.addElement(i, j, getElement(i, j) - other.getElement(i, j));
            }
        }
        return result;
    }

    SparseMatrix operator*(const T& scalar) const {
        SparseMatrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.addElement(i, j, getElement(i, j) * scalar);
            }
        }
        return result;
    }

    SparseMatrix operator*(const SparseMatrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix for multiplication");
        }

        SparseMatrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                T sum = 0;
                for (int k = 0; k < cols; ++k) {
                    sum += getElement(i, k) * other.getElement(k, j);
                }
                result.addElement(i, j, sum);
            }
        }
        return result;
    }

    map<int, int> getPosition(const T& value) const {
        for (int i = 0; i < rows; ++i) {
            MatrixNode<T>* current = rowHeads[i];
            while (current != nullptr) {
                if (current->data == value) {
                    map<int, int> position;
                    position[i] = current->col;
                    return position;
                }
                current = current->next;
            }
        }
        throw logic_error("Value not found in matrix");
    }


};

int main() {
    SparseMatrix<int> matrix(3, 3);
    try {
        matrix.addElement(0, 0, 1);
        matrix.addElement(0, 1, 2);
        matrix.addElement(0, 2, 3);
        matrix.addElement(1, 0, 1);
        matrix.addElement(1, 1, 2);
        matrix.addElement(1, 2, 3);
        matrix.addElement(2, 0, 4);
        matrix.addElement(2, 2, 6);
    }
    catch (const out_of_range& e) {
        cerr << "Error in adding: " << e.what() << endl;
    }


    

    try {
        map<int, int> position = matrix.getPosition(6);
        cout << "Position of value 5: (" << position.begin()->first << ", " << position.begin()->second << ")" << endl;
        cout << "Element at (2, 1): " << matrix.getElement(2, 1) << endl;
        cout << "Element at (1, 1): " << matrix.getElement(1, 1) << endl;
        cout << "Element at (2, 2): " << matrix.getElement(2, 2) << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Error in getting: " << e.what() << endl;
    }

    cout << "Matrix: \n";
    matrix.print();

    SparseMatrix<int> matrixSecond(3, 3);
    try {
        matrixSecond.addElement(0, 0, 6);
        matrixSecond.addElement(0, 1, 8);
        matrixSecond.addElement(0, 2, 10);
        matrixSecond.addElement(1, 0, 1);
        matrixSecond.addElement(1, 1, 5);
        matrixSecond.addElement(1, 2, 3);
        matrixSecond.addElement(2, 0, 4);
        matrixSecond.addElement(2, 1, 7);
        matrixSecond.addElement(2, 2, 6);
    }
    catch (const out_of_range& e) {
        cerr << "Error in adding: " << e.what() << endl;
    }

    cout << "Matrix Second : \n";
    matrixSecond.print();


    try {
        cout << "Addition:" << endl;
        SparseMatrix<int> sum = matrix + matrixSecond;
        sum.print();

        cout << "\nSubtraction:" << endl;
        SparseMatrix<int> difference = matrix - matrixSecond;
        difference.print();

        
        cout << "\nMultiplication by scalar 2" << endl;
        SparseMatrix<int> scalarProduct = matrix * 2;
        scalarProduct.print();


        cout << "\nMultiplication of matrices:" << endl;
        SparseMatrix<int> product = matrix * matrixSecond;
        product.print();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }





    return 0;
}
