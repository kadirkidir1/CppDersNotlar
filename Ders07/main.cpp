#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

/*
 Bir header file içerisinde

 int x = 10;                --> Kesinlikle problemli. Asla böyle bir şey tanımlama. ODR'i ihlal etmiş oluruz.
 static int y = 10;         --> Tanımsız davranış değil ama tercih edilen bir kullanım değil.
 inline int z = 30;         --> Hiçbir hata yok C++17 standartlarıyla dile eklendi inline variable'lar.
 namespace{                 --> Eskiden beri var, unnamed namespace deniyor. Static int y'nin yeni biçimi.
 int t = 40;
 }

 const int k = 10;          --> Bir hata yok, global const nesneler internel linkage'da.

 */

// SINIFLAR

// C'deki yapılar da class artık. C++'da ister struct data yaz istersen de Class data yaz. Aynı şey.
// Hiçbir fark yok değil, bazı küçük farklılıklar var. Bunların sınıf olması açısından fark yok.
// C++ nesne yönelimli bir programla dili değil, multiparadigme bir dil.
/*
  class Myclass{
    //Myclass'ı doğrudan kullanabilirim.
    // Yani tanımlama yaparken
    // class Myclass m; --> Diye tanımlamama gerek yok.
    // class definition ile class declaration farklı şeyler.
    // Class declaration -- class Myclass; şeklinde yalnızca sınıfı ve adını yazmak. Forward decleration
    // class'lar genelde header file'da olur. Ama her zaman değil.
    // Bir sınıfın hiç member'ı olmayabilir. Geçerlidir. Buna empty class denir.

    // 1. Data member
    // 2. Member function
    // 3. Type member - nested type -member type(tür elemanı)
    int mx; // Data member
    void func(int); // Member function
    typedef int Word; // type member
  }
 */

/*
 // Class içerisindeki static değişkenler global tanımlı değişkenler gibidir???
 örneğin

 class Myclass {
 int x;
 int y;
 int z;
 static int a;
 static double b;

 sizeof(Myclass); --> Cevap 12'dir çünkü staticler sayılmaz.
 */
// Bildirim isınıf tanımı içinde yapılan (bir istsna hariç) isimler sınıfların elemanlarıdır ve
// bu isimlerin tüm isimlerde olduğu gibi bir kapsamı(scope) vardır.

// namespace scope
// class scope
// block scope
// function scope

/*
 * Dikkat
 * Bir ismin bir sınıfın tanımı içinde aranması için şu koşullardan
 * İsim nokta operatörünün (member selection) dot operator sağ operandı olarak kullanılmış ise
 *
 * İsim ok operatörünün (member selection) arrow operator sağ operandı olarak kullanılmış ise
 *
 * İsim scope resolution operatörünün sağ operandı olarak kullanılmış ise ( sol operand bir sınıf ismi ise)
 *
 *
 */

/*
 * 1 Free function
 * 1 global function
 * 3 stand-alone function
 */


/*
 * Control---
 * 1) Name lookup
 * 2) Context control
 * 3) Access control
 */

/*
 class myclass{
    int mx; --> Bu değişken private bir değişken. Default olarak private tanımlar.
 };

 struct mystruct{
    int a,b,c; --> Default olarak public.
 };

 */

// Sınıflaın üye fonksiyonları aynı scope'ta oldukları için overload edilebilirler.
// Bir sınıfın üye fnksiyonunu yeniden bildiremezsiniz!!!

/*
class Myclass{
public:
    void func(int);
    void func(double); // --> Overload
    //void func(int); // --> Doğrudan syntax hatasıdır.
};
*/


/*
class Myclass1{
public:
    void func(int);
    //void func(int); // --> Doğrudan syntax hatasıdır.
private:
    void func(double); // --> Overload geçerli.
};

 int main(){
    Myclass1 m;
    m.func(1.3); --> syntax hatası. Function Overload'ı kazanıyor çünkü access kontrolü sonradan geliyor.!!!
 }

 */

/*
 * Bir üye fonksiyonun Cpp dosyasında başlık dosyasına eşlik eden dosyasında tanımlanmasıyla,
 * sınıfın içinde tanımlanması aynı şey değil.
 class Myclass{
public:
    void func(double);
 };
 */

// Hangi durumlarda global fonksiyon tanımlamalıyım, hangi zamanlarda o fonksiyonu sınıfın içerisinde tanımlamalıyım?
//

/*
 Header dosyasında
 #ifndef MYCLASS_H
 #define MYCLASS_H
 #endif // işlemi ile

 #pragma once // işlemleri aynı anlama gelmektedir ama Necati hoca bunu tavsiye etmiyor ve üretimde de kullanmıyor.
              // Yukarıdaki gibi kullanmayı tercih ediyor.
 */

// .h ile .hpp arasında herhangi bir farklılık yok.

// Bir fonksiyon içerinde bir değişken aranınca önce fonksiyon içindeki scope'larda, sonrasında ise global scope'ta
// aranır.
// Fakat class fonksiyonunda önce fonksiyon içerindeki scope'larda, sonra class scope'ta, sonrasında global scope'ta
// aranır.

// üye fonksiyon içinde kullanılmış nitelenmemiş bir ismin aranması ( x.a değil, x->a değil, x::a değil, direkt a)
// önce kullanıldığı blok içerisinde(kullanıldığı yere kadar), bulunamaz ise(bulunursa isim arama biter)  kapyasan
// bloklarda, bulunamazsa Class scope'ta, orada da bulunamazda global scope'ta.

