#include <iostream>

class kdr_1{
public:
    operator bool()const;
};

void main_1()
{
    kdr_1 m1,m2;
//    auto x = m1 + m2;
    // burada + isaretinin overload'i olmasa bile calisir. Cunku bool overload'i ile int'e donusturur.
    // a
}

// enumlar sinif olmadigindan yalnizca operator global overloading edilebilir.


//NAMESPACE'lere giris yapiyoruz artik.
// namespace icerisine isim koyabilecegimiz bir scope!!!
// c ve c++ arasindaki scope kurallarinin iki dilde farkli kategorilere ayrilir.

// c de file scope, block scope, function prototype scope ve function scope
// c++'ta file scope yok, file scope'u da icine alan namespace scope var ve ekstradan class scope var
namespace kdr1{
    // sonunda noktaki virgul yok class'lardaki gibi!
    // global alan icerisindeki olusturulabilecek tum isimleri burada da tanimlayabiliriz.
    // amac, isim cakismasinin onune gecmek.

    // namespace'ler blok içinde tanimlanamazlar.
    // ya global namespace'te ya da namespace icerisinde tanimlanabilirler.
    // namespace'lerde public private protected yok!!!

    namespace kdr2{
        int x;
    }
}

int z = kdr1::kdr2::x;

class kdr_2{
public:


};

// ayni namespace'leri iki farkli sekilde kullanirsak bunlar syntax hatasi vermez.
// bunlar otomatik olarak birlestirilir.

namespace hl{
    int x,y,z;
}

namespace hl{
    int a,b;
}

int asd23 = hl::a;
int asd24 = hl::y;  // goruldugu gibi bir syntax hatasi olusmaz ve birlestirilir!!!

// namespace icerisinde :: ile ayni namescope icerisndekileri belirtmeye gerek yok ornekin!!!
namespace nms1{

    void func(){}

    void foo(){
        func(); // ayni namespace icerisindeki fonksiyonu cagirirken :: ile belirtmedim!!!
                // global namespace icin de ayni aslinda!!!
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// using declaration
// using namesspace directive (declaration)
// ADL (argument dependent lookup) ( koenig lookup)

namespace kbr{
    int x,y,z;
}

using kbr::x;   // bu using declaration! Inject ediyoruz. Yani sanki buradaa tanimlaniyor gibi.
                // kullanildigi yerde blok icerisinde tanimlama yapiyor!

// using bildirimi bir bildirimdir ve her bildirim gibi bu bildirimin de bir scope'u vardir.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace hk1{
    int x;
}

namespace hk2{
    using hk1::x;
}

void nmspc(){
    int z = hk2::x; // burada ne yaptigini anlamak muhim. x degiskeni hk2'de using ile bildirildigi icin
                    // artik hk2'nin x elamani gibi sayilabilir!
}

// using bildirimi ile bildirilmis ise bildirimin yapildigi scope'a enjekte edilir.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int gsf = 10;

namespace fgh{
    using ::gsf;
    int k;  // k burada statik omurlu degisken
    int y,za,l;
    void foo(){
        int y = 19; // otomatik omurlu degisken
    }
}

void gsff()
{
    fgh::gsf = 23;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Modern C++ oncesi asagidaki gibi bir kullanim yoktu!!!
using fgh::y , fgh::za , fgh::l;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// using namespace bildirimi de bir bildirimdir. Tum bildirimlerde oldugu gibi bu bildirimin de bir kapsami
// vardir.
// using namespace bildirimi, bildirime konu isim alani icindeki isimleri bildirimin yapildigi isim alanina
// enjekte etmez. digerine gore hayati onem arz eden bir farklilik.

 namespace hly1{
     int a,b,c;

     namespace hly11{
         int k,l,m;
     }
 }

 void f_hly1()
 {
     using namespace hly1;
     int a; // hly1 namespace'inde a olmasina ragmen a'yi burada tanimladim.
            // ama using hly1::a yapsaydim bu sekilde tanimlayamazdim. Bu onemli bir fark!
 }

 void f_hly11()
 {
      using namespace hly1::hly11;
      int k = 20; // legaldir, bir hataya sebebiyet vermez!
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace hly2{
     int ah2,bh2,ch2;
 }

using namespace hly2;

int ah2;   // namescope'ta da ayni isimde tanimlandi.

void f_hly2(){
//    ah2 = 5;  // Bunu yazdigimda error veriyor. Ambiguity hatasi!
//     cunku hangi ah2'den bahsettigini ben anlayamiyorum diyor!!!
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace hly3{
    int ah2,bh2,ch2;
}

using namespace hly3;

void f_hly3(){
//    ah2 = 5;  // Bunu yazdigimda error veriyor. Ambiguity hatasi!
//     cunku hangi ah2'den bahsettigini ben anlayamiyorum diyor!!!
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

 namespace hly4{
    void foo();
}

namespace hly41
{
    int foo = 5;
}

using namespace hly4;
using namespace hly41;

void f_hly4()
{
//    foo();  // bu sekilde cagiramam cunku foo ismi iki farkli yerde de kullaniliyor!
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace hly6{
    int vhly6 = 20;
}



void f_hly6(){
    using namespace hly6;   // burada olsa da hata olmazdi!
    std::cout << vhly6 << std::endl;    // ilk basta bunu yazdirir cunku alttaki data tanimlanmamis. Hata vermez.
    int vhly6 = 10;

    std::cout << vhly6 << std::endl;    // yazdiracagi deger 10 olacaktir!!! Ister iceride tanimla ister
                                        // disarida tanimla hic fark etmez.
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace hly7{
    class c_hly1{

    };

    void f_hly7(int);
    void f_hly72();
    void f_hly73(c_hly1);

}

void f_hly71(){
//    f_hly7(10); // syntax error
//    f_hly72();  // syntax error

hly7::c_hly1 hx;

f_hly73(hx);    // burada olaylar karisiyor.
                // ortada using direktifi olmadan, nitelemeden kullanmak syntax error olusturmadi.
                // Buna da ADL diyorlar

// Eger bir fonksiyona yapilan cagrida fonkisyonun ismi bir namespace ile nitelenmemis olmasina karsin
// eger fonksiyona gonderilen argumanlardan herhangi biri bir namespace icinde tnaimlanan bir ture iliskinse
// bu isim o turu icine alan namespace icinde de aranir.

// AMAA yalnizca hly7 space'inde aramiycam, hly7 space'inde de arayacagim!!!



}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////// MULAKAT SORUSU ///////// MULAKAT SORUSU ///////// MULAKAT SORUSU ///////// MULAKAT SORUSU /////////

namespace hly8{
    enum Color{blue,black,white};

    void func(Color);
}

void f_hly8(){
    func(hly8::blue);   // burada ADL yine devreye girecek. ADL devreye girmesi icin o ture ait olmasi yeterli.

}

///////// MULAKAT SORUSU ///////// MULAKAT SORUSU ///////// MULAKAT SORUSU ///////// MULAKAT SORUSU /////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f_hly100()
{
    std::operator<<(std::cout, "hello world");  //
    operator<<(std::cout, "hello world");  // std'u operator<< icin silmeme ragmen hata vermedi.
        // Halbuki operator<< de std namespace'inde AMA ADL oldugu icin calisabiliyor!!!
        // ADL yalnizca bu ise yaramiyor ama en onemli neden bu olabilir.
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace hly9{
    class  c_hly9{
        //...
    };

    void f_hly90(c_hly9)
    {
        std::cout << " hly9::f_hly90\n";
    }
}

void f_hly90(hly9::c_hly9){
    std::cout << " global func\n";
}

void f_hly9(){
    hly9::c_hly9 ornek_class;

//    f_hly90(ornek_class);     Burada ambiguity vardir!!! ERROR!!!!!!!!!!!!!!!
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

namespace hly10{
    class X{};

    void func(std::vector<X>);
}

void f_hly10(){
    std::vector<hly10::X> myhly10;

    func(myhly10);
    // goruldugu uzere tamamen legal!!!

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ADL'nin friend fonksiyonlarla da iliskisi var.

class hly11{
public:
    friend void f_hly101(int);
};

void f_hl11(){
   // f_hly101(10);   // bu hata sebebidir. Burada fonksiyon aranip bulunamiyor!!!
}

// Kodu biraz degistirelim ve ADL'e uygun hale getirelim!!!

class hly12{
public:
    friend void f_hly102(class hly12);
};

void f_hl12(){
    hly12 hlyt12;
     f_hly102(hlyt12);   // burada hata olmasinin sebebi ADL.
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    1. Anonymous namespace , unnamed namespaces
//    2. inline namespace (modern c++ ile dile eklendi)
//    3. nested namespace
//    4. namespace alias

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Bir kaynak dosyada namespace olusturup buna isim vermezseniz bu ayri bir nitelikte ozel kurallara tabii
// bir namespace ve boyle namespacelere ananoymous namespace deniyor. Isimsiz isim alani!!!

namespace{
    int a,b,c;  // diledigim gibi isimleri bildirebiliyorum.
}

void f_hly13(){
    a = 45; // peki bu sekilde direkt olarak kullaniyorsam neden namespace ile ugrasiyorum!!!
            // C'deki static anahtar sozcuguyle tanimlanan global degiskenlere bir alternatif!!!

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////


// linkage : eger bir isim projeyi olusturan birden fazla kaynak dosyada kullaniyor olsun.

// ali.c
// x = 5;
// veli.c
// x = 10;
// hasan.c bunlarin hepsi bir kaynak dosya!!!
// x = 20;
// burada x'lerin hepsi ayni x. Cunku birbirlerine extern yani external olarak bagli yani external linkage11!!!

// Eger ali.c dosyasinda bir degiskeni static anahtar sozcuguyle tanimlarsak bu artik diger kaynak dossyalarda
// kesinlikle kullanilamaz YANI bu artik internal linkage olur!!!
// external, internal ve no linkage olmak uzere 3 baglanti turu var!!

// Eger internal linkage yapmak istiyorsak static yerine bunu unnamed namespace'te tanimlamamiz daha dogru ve
// avantajli.

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Namespaces Alias
// bir tur ismi yerine gececekse type alias diyormusuz!
// Ozellikle C++'ta en onemli araclardan bir tanesi!
// C'de type alias sadece typedef ile olusturulerken modern C++'te using ile de bildirebiliyoruz ama
// burada ogrendigimiz using bizim ogrendigimiz using'le alakasiz. Yani using keyword'u overload edilmis.

typedef int Word;

using word = int;
// Yukaridaki ikisi es anlamli!!! Usingi kullanin typedef'i kullanmayin!!!

// Neden typedef varken using eklendi.
// typedef bildirimleri template olarak kullanilmiyor yani generic programlamada kullanamiyorum ama using
// bildirimleri template haline getirilebiliyor!!
// 2. faydasi ise kafa karistirmanin onune gecmesi!!

// Ornekin
typedef int (*fcmp)(const void *,const void *);    // bunun yerine
using fcmp = int (*)(const void *,const void *);   // bu sekilde yapabiliriz.

// namespace'e es isim vermeye namespaces alias deniyor.
// 1. nedeni

namespace a1{
    namespace a2{
        namespace a3{
            int x;
        }
    }
}

namespace project = a1::a2::a3;
#define procekt a1::a2::a3

void f_hly12(){
    // std::ranges::view goruldugu gibi bir yazim zorlugu var!
    // hele hele namespace derinligi daha fazla olursa yani ic ice namespace'ler girerse hos olmaz!
    //
a1::a2::a3::x = 45; // her defasinda bunu yazmak yerine
project::x = 5;      // bu sekilde kullanabilirim
procekt::x = 12;    // bunu necati vermedi ben yaptim oylesine. Mantikli degil, olsaydi necati verirdi.
}

// bu versiyon kontrolunde de kullanilabiliyordu!!!

namespace hly14{

    namespace oldVersion{
        class Myclass{

        };
    }

    namespace newVersion{
        class Myclass{

        };
    }
}

namespace Current = hly14::oldVersion;

void f_hly14(){
    Current::Myclass x; // Hangi sinifi kullandimi bu sekilde kullanabilirim!!!
}

// namespace kullandigim zaman isim cakismasini tamamen engelleyemem.
// %99.999 engellerim ama %100 degil. Cunku namespace'in ismi de cakismaya tabi! Cunku namespace'in
// ismi de cakismaya tabi!

int main() {

    return 0;
}
