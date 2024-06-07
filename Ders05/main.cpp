#include <iostream>

constexpr int func(int a,int b);
constexpr int foo2(int a,int b);




int main() {
   int x2 = foo2(10,20); // cevap compile timeda elde edilecek.
}

void foo1() {
    constexpr int x = 10;
    constexpr int y = 20;
    constexpr int z = 30;

}

constexpr int foo2(int a,int b)
{
    return a*a + b*b;
}

/*
 *
 * void func(int,...);
 * void func();
 *
 * Yukarıdaki iki function için, variadic olmayan kazanacaktır. Çünkü variadic
 * fonksiyonların önceliği düşüktür.
 *
 */

/*
 *      struct Data{
 *      };
 *
 *      void func(Data);
 *
 *      int main(){
 *          func(12); --> int tipinden Data tipine değişim olmadığı için syntax hatası!!!
 *      }
 *
 */

/*
 *      struct Data{
 *          Data(int); --> Int türünden constructor oluşturuluyor. User-defined Conversion
 *      };
 *
 *      void func(Data);
 *
 *      int main(){
 *          func(12); --> Data struct'ının constructer'ı int olduğu için error vermez.
 *      }
 *
 */

/*
 * array to pointer conversion exact match kabul ediliyor.
 *
 * void func(int*);
 *
 * int main(){
 *      int a[10];
 *      func(a);        --> Array decay olduğundan exatch match kabul ediliyor.
 *
 */

/*
 * array to pointer conversion exact match kabul ediliyor.
 *
 * void func(const int*);
 *
 * int main(){
 *      int a[10];
 *      func(a);        --> Array decay olduğundan exatch match kabul ediliyor. Const olsa da aynı.
 *
 */

/*
 * void func(int (*)(int));
 * int foo(int);
 *
 * int main()
 * {
 *  func(foo); --> Exact match kabul ediliyor. function to pointer conversion
 *  }
 *
 *
 */

/*
 * void func(double);
 * void func(unsigned);
 *
 *  int main()
 *  {
 *      func(10); --> Ambiguity. Çünkü her ikisi de normal conversion.
 *  }
 *
 */

/*
 * void func(int *);
 * void func(const int *); --> Kesinlikle F Overloading'dir. Signaturelar farklı kabul edilir.
 *                             Bu kullanıma genelde const overloading denir.
 *
 * void func(int&);
 * void func(const int &); --> Kesinlikle F Overloading'dir. Signaturelar farklı kabul edilir.
 *
 */

/*
 * void foo(int *p);
 *
 * int main()
 * {
 *  foo(0); --> geçerli, nullptr conversion
 * }
 *
 */

/*
 *  void func(int);
 *  void func(int&);
 *
 *  int main(){
 *  int x = 10;
 *  func(x); --> ambiguity olur.
 *
 */

/*
 *  void func(int);
 *  void func(const int&);
 *
 *  int main(){
 *  func(10); --> ambiguity olur.
 *
 */

/*
 * void func(void *);
 * int main(){
 *  int ival{};                 // Kod geçerlidir. Void * türüne dönüşür.
 *  func(&ival);
 * }
 */

/*
 *
 * void func(bool);
 *
 * int main(){
 *   int ival = 10;     --> Geçerlidir.
 *   func(&ival);
 * }
 */

/*
    void func(bool);
    void func(void *);

    int main()
    {
        int ival = 10;
        func(&ival);            --> Ambiguity yok. 2. fonksiyon çalışır.
    }
 */

/*
    void func(int, int = 8);
    void func(int);

    int main(){
        func(10);       --> F Overloading geçerli ama ambiguity çalışır.
                        // Böyle overloading'lerden kaçınmak gerekiyor.
    }
 */

