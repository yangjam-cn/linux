/**
 * @copyright: 《剑指offer第二版》
 * @filename: AssignmentOperator.cpp
 * @description: 为CMyString类添加赋值运算符
 * @author: yungjam
 * @version: 1.0
 * @data: 2020.10.30
 * @history:
 */
#include <cstring>
#include <cstdio>

class CMyString
{
    public:
        CMyString(const char *pData = nullptr);
        CMyString(const CMyString &str);
        ~CMyString(void);

        CMyString& operator=(const CMyString &str);

        void Print();

    private:
        char *m_pData;
};

CMyString::CMyString(const char *pData)
{
    if (pData == nullptr)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int length = strlen(pData);
        m_pData = new char[length + 1];
        strcpy(m_pData, pData);
    }
}

CMyString::CMyString(const CMyString &str)
{
    int length = strlen(str.m_pData);
    m_pData = new char[length + 1];
    strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString(void)
{
    delete[] m_pData;
}

CMyString& CMyString::operator=(const CMyString &str)
{
    if (this == &str)
    {
        return *this;
    }

    delete[] m_pData;
    m_pData = nullptr;

    m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(m_pData, str.m_pData);

    return *this;
}

void CMyString::Print()
{
    printf("%s", m_pData);
}

void Test1()
{
    printf("Test1 begins:\n");

    const char *text = "Hello world";

    CMyString str1(text);
    CMyString str2;
    str2 = str1;

    printf("The excepted result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");
}

void Test2()
{
    printf("Test2 begins:\n");

    const char *text = "Hello world";

    CMyString str1(text);
    str1 = str1;

    printf("The excepted result is: %s.\n", text);

    printf("The actual result is: ");
    str1.Print();
    printf(".\n");
}

void Test3()
{
    printf("Test3 begins:\n");

    const char *text = "Hello world";

    CMyString str1(text);
    CMyString str2, str3;
    str3 = str2 = str1;


    printf("The excepted result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");

    printf("The actual result is: ");
    str3.Print();
    printf(".\n");
}

int main(void)
{
    Test1();
    Test2();
    Test3();

    return 0;
}
