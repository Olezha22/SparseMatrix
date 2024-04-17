#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestAddElement)
        {
            SparseMatrix<int> matrix(3, 3);
            matrix.addElement(0, 0, 1);
            matrix.addElement(0, 1, 2);
            matrix.addElement(0, 2, 3);

            Assert::AreEqual(1, matrix.getElement(0, 0));
            Assert::AreEqual(2, matrix.getElement(0, 1));
            Assert::AreEqual(3, matrix.getElement(0, 2));
        }

        TEST_METHOD(TestGetElement)
        {
            SparseMatrix<int> matrix(3, 3);
            matrix.addElement(1, 1, 5);
            matrix.addElement(2, 2, 10);

            Assert::AreEqual(5, matrix.getElement(1, 1));
            Assert::AreEqual(10, matrix.getElement(2, 2));
        }

        TEST_METHOD(TestMatrixAddition)
        {
            SparseMatrix<int> matrix1(2, 2);
            matrix1.addElement(0, 0, 1);
            matrix1.addElement(0, 1, 2);
            matrix1.addElement(1, 0, 3);
            matrix1.addElement(1, 1, 4);

            SparseMatrix<int> matrix2(2, 2);
            matrix2.addElement(0, 0, 5);
            matrix2.addElement(0, 1, 6);
            matrix2.addElement(1, 0, 7);
            matrix2.addElement(1, 1, 8);

            SparseMatrix<int> sum = matrix1 + matrix2;

            Assert::AreEqual(6, sum.getElement(0, 0));
            Assert::AreEqual(8, sum.getElement(0, 1));
            Assert::AreEqual(10, sum.getElement(1, 0));
            Assert::AreEqual(12, sum.getElement(1, 1));
        }

		TEST_METHOD(TestSubtractionTest)
		{
			SparseMatrix<int> matrix1(2, 2);
			SparseMatrix<int> matrix2(2, 2);

			matrix1.addElement(0, 0, 1);
			matrix1.addElement(0, 1, 2);
			matrix1.addElement(1, 0, 3);
			matrix1.addElement(1, 1, 4);

			matrix2.addElement(0, 0, 2);
			matrix2.addElement(0, 1, 3);
			matrix2.addElement(1, 0, 4);
			matrix2.addElement(1, 1, 5);

			SparseMatrix<int> difference = matrix1 - matrix2;

			Assert::AreEqual(-1, difference.getElement(0, 0));
			Assert::AreEqual(-1, difference.getElement(0, 1));
			Assert::AreEqual(-1, difference.getElement(1, 0));
			Assert::AreEqual(-1, difference.getElement(1, 1));
		}

		TEST_METHOD(ScalarMultiplicationTest)
		{
			SparseMatrix<int> matrix(2, 2);

			matrix.addElement(0, 0, 1);
			matrix.addElement(0, 1, 2);
			matrix.addElement(1, 0, 3);
			matrix.addElement(1, 1, 4);

			SparseMatrix<int> scalarProduct = matrix * 2;

			Assert::AreEqual(2, scalarProduct.getElement(0, 0));
			Assert::AreEqual(4, scalarProduct.getElement(0, 1));
			Assert::AreEqual(6, scalarProduct.getElement(1, 0));
			Assert::AreEqual(8, scalarProduct.getElement(1, 1));
		}

		TEST_METHOD(MatrixMultiplicationTest)
		{
			SparseMatrix<int> matrix1(2, 2);
			SparseMatrix<int> matrix2(2, 2);

			matrix1.addElement(0, 0, 1);
			matrix1.addElement(0, 1, 2);
			matrix1.addElement(1, 0, 3);
			matrix1.addElement(1, 1, 4);

			matrix2.addElement(0, 0, 2);
			matrix2.addElement(0, 1, 3);
			matrix2.addElement(1, 0, 4);
			matrix2.addElement(1, 1, 5);

			SparseMatrix<int> product = matrix1 * matrix2;

			Assert::AreEqual(10, product.getElement(0, 0));
			Assert::AreEqual(13, product.getElement(0, 1));
			Assert::AreEqual(22, product.getElement(1, 0));
			Assert::AreEqual(29, product.getElement(1, 1));
		}
	};
}
