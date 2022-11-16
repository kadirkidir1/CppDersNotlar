#include <iostream>

void foo1();
void foo2();
void foo3();
void foo4();
void foo5();
void foo6();
void foo7();
void foo8();
int foo9();
void foo13();
void foo14();
void foo15_a();
void foo15(int &x,int &y);
void print_array(int* p, size_t size);

int main()
{
    foo15_a();
}

void foo1()
{
    int x{10};
    int y = 56;
    int& r = x;     // r x ifadesine referans. Artık r ifadesi x'i temsil eder.
    ++r;            // x değeri de artar.
    std::cout << x << std::endl; // Cevap 11'dir.

    r = y;          // x = y anlamına gelir.

    int *p = &r; // yazmak ile
    //int *p = &x; // yazmak arasında herhangi bir fark yoktur.
}

void foo2()
{
 double dval = 2.3;
 double& dr = dval;
}

void foo3()
{
    int x{10};
    int& r1 = x;
    int& r2 = (x);
    int& r3 = {x};       // Bu üç ifade de geçerli.
}

void foo4()
{
    int x = 10;
    int &r1{x};
    int &r2{x};
    int &r3{x};         // Bir nesneyi birden fazla referans refere edebilir.
}

void foo5(){
 int x = 10;
 int* p = &x;
 int a [10];

 // &x bir rValue.
 // *p lValue.
 // a[0] lValue.

 // int &r = 10; Hatalı bir ifadedir çünkü lValue yalnızca lValue değer alabilir. Sol taraf lValue iken
 // ifadenin sağ tarafı rValue olmaktadır. Bu da hataya sebebiyet verir.


}

void foo6()
{
    int x = 10;
    ++x; // C'de rValue iken C++'da lValue.
}

void foo7(){
    int x = 10;
    int y = 25;

    (x,y) = 10;
    // (x,y) = 10; C'de sağdaki ifade lValue olduğundan ifade lValue'dur. rValue ataması yapılamaz.
    // C++'ta ise atama operatörü lValue'dür. Hata vermez.
}

void foo8(){
    int x = 10;
    int& r = ++x; // legal'dir çünkü ++x lValue expression'dır.
}

int foo9(){     // Bu fonksiyon bir prValue expression'dır.
    return 8;
}

int &&foo10(); //--> Bu ifade bir X value.

void foo11(){
    int x = 10;
    int* ptr =&x;

    int*& r = ptr; // r int* türünden bir değişkene referans oluyor.

    ++* r;         // x'in değeri bir artmış olur çünkü burada r'nin gösterdiği değer 1 arttırılıyor.
}

void foo12(){
    int x{24};

    int& r1 = x;    // r1 x'e referans.
    int& r2 = r1;   // r1 x'e referans olduğu için r2 = x olur.

    ++r1; // x = 25;
    ++r2; // x = 26;
}

void foo13(){
    int a[5] = {1,2,3,4,5};
    //öyle bir pointer değişken tanımlayın ki ismi p olsun ve *p ifadesi a dizisinin kendisini versin.

    int (*p)[5] = &a;
}

void foo14(){
    int a[5] = {1,2,3,4,5};
    int(&r)[5] = a;
    // Yukarıdakini yapmak yerine
    // auto& r ferans gerçekleşmiş olur.

    std::cout << r[2] << std::endl;
}

void foo15_a()
{
    int k{15};
    int l{45};
    foo15(k,l);

    std::cout << " k =" << k << std::endl <<"l =" << l << std::endl;
}

void foo15(int &x,int &y){
    int temp = x;
    x = y;
    y = temp;
}

void foo16()
{
    int x = 10;
    //double *ptr = &x; Bu şekilde kullanım C'de otomatik tür dönüştürme olduğu için legal iken
    // C++'da syntax hatasıdır.

    //double& r = x; işlemi de syntax hatası.

}

void foo17(){
    int x = 10;
    int *p = &x; // Ben x'i gösteriyorum beni kullanarak x'i set edebilirsin.
    const int* cp = &x; // Ben x'i gösteriyorum salt okuma amaçlı. Pointer to const
}

void print_array(int* p, size_t size);  // Bu sekilde kullanılmaması gerekiyor. Pointer const'a alınmalı.
                                        // void print_array(const int* p, size_t size); şeklinde olmalı.

void foo18(){
    const int a[5] = {2,3,4,5,6};
    // print_array(a,5); Bu bir syntax hatasıdır çünkü Const T*, T*'a otomatik dönüşmüyor. Bu yüzden yazılan
    // kodda const correctness'a önem verilmeli.
}

void foo19(){
    int x = 10;
    int& const r = x;
}