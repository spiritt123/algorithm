
# Описание интерфейса

* **_project/include/matrix.h_** - интерфейс.
* **_project/include/exception.h_** - исключения, используемые в библиотеке.

* `class Matrix` - основной класс.

### Конструкторы

* `Matrix::Matrix(size_t rows = 0, size_t cols = 0)` - создать пустую матрицу
 размера `<rows>*<cols>`.
* `Matrix::Matrix(std::istream& is)` - создание матрицы из потока. В случае
 проблем чтения бросает исключение `InvalidMatrixStream`.

### Базовые методы

* `size_t Matrix::getRows() const` - получить количество строк.
* `size_t Matrix::getCols() const` - получить количество столбцов.

* `double Matrix::operator()(size_t i, size_t j) const` - получить значение
 элемента на позиции `[<i>, <j>]`.
* `double& Matrix::operator()(size_t i, size_t j)` - получить **элемент** на
 позиции `[<i>, <j>]` для присваивания.

В случае выхода за границы матрицы бросают исключение `OutOfRange`.

Операторы сравнения:
* `bool Matrix::operator==(const Matrix& matrix) const` 
* `bool Matrix::operator!=(const Matrix& matrix) const`

**_NB_** Для неточного сравнения `double` пригодится
 `std::numeric_limits<double>::epsilon()`. **UPD** В тестах все значения имеют
  точность `1e-07`.

* `Matrix Matrix::operator+(const Matrix& matrix) const` - сложение матриц.
* `Matrix Matrix::operator-(const Matrix& matrix) const` - вычитание матриц.
* `Matrix Matrix::operator*(const Matrix& matrix) const` - умножение матриц.

В случае несоответствия размерностей бросают исключение `DimensionMismatch`.

* `Matrix Matrix::transp() const` - транспонирование матрицы.

Умножение матрицы на скаляр:
* `Matrix Matrix::operator*(double val) const` - правостороннее.
* `Matrix operator*(double val, const Matrix& matrix)` - левостороннее.
 

* `double det() const` - определитель матрицы.
* `Matrix adj() const` - присоединенная матрица.
* `Matrix inv() const` - обратная матрица. Брасает `SingularMatrix`.

Брасают исключения `DimensionMismatch`.

