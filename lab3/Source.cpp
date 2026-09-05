#include "booleanvector.h"

#include <memory>
#include <fstream>

#define rus setlocale(LC_ALL, "rus");

// Класс, реализующий автоматический указатель и предназначенный для демонстрации RAII
template<typename Type>
class Pointer
{
public:

    Pointer(Type* pointer) : pointer_(pointer)
    {

    }

    ~Pointer()
    {
        delete pointer_;
    }

private:

    Type* pointer_;
};

// Частичная специализация шаблонного класса, определённого выше, для массивов
template<typename Type>
class Pointer<Type[]>
{
public:

    Pointer(Type* pointer) : pointer_(pointer)
    {

    }

    ~Pointer()
    {
        delete[] pointer_;
    }

private:

    Type* pointer_;
};

// Класс, предназначенный для отладочного вывода на консоль при работе специальных методов
class TestClass1
{
public:

    TestClass1()
    {
        std::cout << "TestClass1::TestClass1() was called." << std::endl;
    }

    ~TestClass1()
    {
        std::cout << "TestClass1::~TestClass1() was called." << std::endl;
    }
};

// RAII-обёртка над файлами CRT.
class FileRAIIWrapper
{
public:

    FileRAIIWrapper(const char* FileName, const char* FileOpenMode)
    {
        //filePtr_ = fopen(FileName, FileOpenMode);
    }

    ~FileRAIIWrapper()
    {
        fclose(filePtr_);
    }

private:

    FILE* filePtr_;
};

// Функция, демонстрирующая важность использования RAII и деструктуров для освобождения ресурсов при наличии исключений.
int testFunc1(const int a, const int b)
{
    // Возможна утечка памяти, если будет выброшено исключение
    //TestClass1 *testClass1 = new TestClass1();
    // Деструктор будет вызван независимо от того, будет ли возбуждено исключение => динамически выделенная память будет освобождена в любом случае
    Pointer<TestClass1> testClass1(new TestClass1());
    Pointer<TestClass1[]> testClass1Array(new TestClass1[7]);

    // Возможна утечка файлового хендла, если будет выброшено исключение
    //FILE *file1 = fopen("test.txt", "r");
    // Деструктор будет вызван независимо от того, будет ли возбуждено исключение => файл будет закрыт в любом случае
    FileRAIIWrapper File1("test.txt", "r");

    // В C++ есть большое количество классов, реализующих идиому RAII и облегчающих написание Exception Safe-кода.
    //std::unique_ptr<TestClass1> ptr(new TestClass1());
    //std::unique_ptr<TestClass1[]> ptr2(new TestClass1[12]);
    //std::fstream fileStream("test.txt", std::ios::in);

    std::cout << "Entering testFunc1..." << std::endl;

    int c = a + b;

    throw std::runtime_error("Test exception 3.");

    std::cout << "Leaving testFunc1..." << std::endl;

    // При выбросе исключения эти операторы не будут вызваны => утечка ресурсов
    //delete testClass1;
    //fclose(file1);

    return c;
}

int main()
{
#if 0
    try
    {
        int res = testFunc1(5, 12);

        std::cout << res << std::endl;
    }
    catch (...)
    {
        std::cout << "Unhandled exception caught." << std::endl;
    }
#endif


    BooleanVector testVector1(10, true);
    BooleanVector testVector2(20, false);

    std::cout << testVector1.getWeight() << std::endl;
    std::cout << testVector2.getWeight() << std::endl;

    try
    {
        std::cout << testVector2[23] << std::endl;
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }

    testVector1[2] = false;
    testVector2[4] = true;
    testVector2[13] = true;

    std::cout << testVector1.getWeight() << std::endl;
    std::cout << testVector2.getWeight() << std::endl;

    std::cout << testVector1[0] << std::endl;
    std::cout << testVector1[2] << std::endl;
    std::cout << testVector1[9] << std::endl;
    std::cout << testVector2[0] << std::endl;
    std::cout << testVector2[4] << std::endl;
    std::cout << testVector2[10] << std::endl;
    std::cout << testVector2[13] << std::endl;
    std::cout << testVector2[19] << std::endl;

    std::cout << std::endl;

    BooleanVector testVector3(10, true);
    BooleanVector testVector4(10, true);

    std::cout << (testVector3 == testVector4) << std::endl;

    BooleanVector testVector5(10, true);
    BooleanVector testVector6(15, true);

    std::cout << (testVector5 == testVector6) << std::endl;

    BooleanVector testVector7(10, true);
    BooleanVector testVector8(10, false);

    std::cout << (testVector7 == testVector8) << std::endl;

    return 0;
}