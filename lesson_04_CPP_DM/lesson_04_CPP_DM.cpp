//============================================================================
// Name        : lesson_04_CPP_DM.cpp
// Author      : andry antonenko
// IDE         : Qt Creator 4.14.2 based on Qt 5.15.2
// Description : lesson 04 of the C++: difficult moments course
//============================================================================
#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <codecvt>
#include <list>
#include <functional>
#include <iterator>
//----------------------------------------------------------------------------
int getRandomNum(int min, int max)
{
  const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937_64 generator(seed);
  std::uniform_int_distribution<int> dis(min, max);
  return dis(generator);
}
//----------------------------------------------------------------------------
/*
1. Имеется отсортированный массив целых чисел.
Необходимо разработать функцию insert_sorted,
которая принимает вектор и новое число и
вставляет новое число в определенную позицию в векторе,
чтобы упорядоченность контейнера сохранялась.
Реализуйте шаблонную функцию insert_sorted,
которая сможет аналогично работать с любым контейнером,
содержащим любой тип значения.
//*/

template<typename Container, typename T>
void insert_sorted(Container& cont,const T &d) {
    auto it = std::begin(cont);

    it = std::find_if(it,end(cont),[&d](T t){
      return t >= d;
    });

    std::vector<T> ins_vec {d};

    std::copy(ins_vec.begin(),ins_vec.end(),
              std::insert_iterator<Container>(cont,it));
}

template<typename Container>
void printContainer(const Container& cont)
{
  for(const auto& a: cont)
    std::cout << a << " ";
  std::cout << std::endl;
}

void task_1()
{
  std::cout << "Task 1\n" << std::endl;

  std::vector<int> v{2,3,6,8,9,10};

  std::cout << "Print of the vector:" << std::endl;
  printContainer(v);

  std::cout << "Added the element 4:" << std::endl;
  insert_sorted(v,4);
  printContainer(v);

  std::cout << "Added the element 1:" << std::endl;
  insert_sorted(v,1);
  printContainer(v);

  std::cout << "Added the element 11:" << std::endl;
  insert_sorted(v,11);
  printContainer(v);

  std::cout << "Added element 4 again:" << std::endl;
  insert_sorted(v,4);
  printContainer(v);

  std::cout << std::endl;
}
//----------------------------------------------------------------------------
/*
2. Сгенерируйте вектор a, состоящий из 100 вещественный чисел,
представляющий собой значения аналогового сигнала.
На основе этого массива чисел создайте другой вектор целых чисел b,
представляющий цифровой сигнал, в котором будут откинуты дробные части чисел.
Выведите получившиеся массивы чисел.
Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым по формуле:
сумма по i=0..N-1(ai - bi)^2,
где:
N - количество элементов в векторе,
a - элемент вектора с дробными числами,
b - элемент вектора с целыми числами
//*/

void task_2()
{
  std::cout << "\nTask 2\n" << std::endl;

  const size_t NUMBER_OF_ELEMENTS = 100;
  const size_t MIN = 0;
  const size_t MAX = 1000;

  std::vector<double> vecDouble(NUMBER_OF_ELEMENTS);

  std::cout << "Generate " << NUMBER_OF_ELEMENTS <<
            " elements of the double float type:" << std::endl;
  generate (vecDouble.begin(), vecDouble.end(),
            []()
      {
        return static_cast<double>(getRandomNum(MIN,MAX))/10.0;
      });

  printContainer(vecDouble);

  std::vector<int> vecInt;

  auto toInt = [](double d){
      return static_cast<int>(d);
  };

  std::cout << "\nGitting " << NUMBER_OF_ELEMENTS <<
            " elements of the interger type:" << std::endl;
  transform(vecDouble.begin(), vecDouble.end(),
            back_inserter(vecInt), toInt);

  printContainer(vecInt);

  std::cout << "\nCalculating the difference and exponentiation:" << std::endl;

  auto subAndPowTwo = [](double d, int i){
      return std::pow(d - static_cast<double>(i),2);
  };

  std::vector<double> subs(NUMBER_OF_ELEMENTS);
  transform(vecDouble.begin(), vecDouble.end(),
            vecInt.begin(), subs.begin(), subAndPowTwo);

  printContainer(subs);

  std::cout << "\nCalculating the sum:" << std::endl;

  double sum = 0;
  //Почему-то данная форма вызова возвращает 0
  sum = accumulate(subs.begin(),subs.end(),0);
  std::cout << sum << std::endl;

  sum = 0;
  //При этом в таком виде вызов возвращает требуемое значение
  sum = accumulate(subs.begin(),subs.end(),sum);
  std::cout << sum << std::endl;

  //Вычисляю циклом для сравнения результата
  sum = 0;
  for(const double& d: subs)
  {
      sum += d;
  }
  std::cout << sum << std::endl;

  std::cout << std::endl;
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  //--------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
  //--------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
  //--------------------------------------------------------------------------
  return a.exec();
}
