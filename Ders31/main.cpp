#include <iostream>
#include <string>
#include <random>

#include <exception>      
#include <stdlib.h>
#include <array>

template <typename T, typename U>
T sum(T x, U y)
{
    return x + y;
}

void main_a()
{
    int ival = 3;
    double dval = 3.14;

    auto result = sum(ival, dval);
    std::cout << result << "\n";

    // Bu durumda bir donusum olur ama, bir veri kaybi soz konusu olur! Bu veri kaybinin
    // onune gecebilmek icin c++'ta belli metotlar var.
}

// Bunlardan ilki asagida anlatilmistir. Explicitly olarak turun de template'i belirtilir.

template <typename R, typename T, typename U>
R sum(T x, U y)
{
    return x + y;
}

void main_b()
{
    int ival = 3;
    double dval = 3.14;

    auto result = sum<double>(ival, dval);
    std::cout << result << "\n";

    // Bu durumda explicitly olarak belirttigim icin, veri kaybi soz konusu olmaz.
    // Bu yollardan bir tanesidir!
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Modern c++ ile iki farkli arac dile eklendi yukaridaki sorun icin.
// 1. trailing return type
// 2. auto return type
// Her ikisi de function template ile kullanilsa da agirlikli olarak, normal template'lerde de
// kullaniliyor.

///// Trailing Return type
/// fonksiyonun geri donus degeri yerine, auto keyword'u yazilir.

int func_1(int x, int y)
{
    return x + y;
}

auto func_2(int x, int y)->int
{
    return x + y;
}

// Yukaridaki iki metot arasinda bir fark yok.
// Araya giriyor ve bir soru soruyor, int parametre alan veri return type'i int olan func'in
// adresini donduren metot yazin dedi. Once typedef ile yapin, sonra typedef olmadan yapin dedi

int foo_pellegrino(int, int);
typedef int(*Fptr)(int, int);

Fptr func_pellegrino()
{
    return &foo_pellegrino;
}
// typedef kullanarak bu sekilde yapabilirim!!

int (*func_pell())(int,int)
{
    return &foo_pellegrino;
}
// typedef kullanmadan da yukaridaki sekilde yapabilirim!!
// Bunu yapmanin 3. bir yolu da, trailing return type kullanmak!

auto func_pelleg()->int (*)(int,int)
{
    return &foo_pellegrino;
}
// typedef kullanmadan en kolay yapma yolu bu aslinda!
// Yukaridakiler marijinal ornekler, anlatilmasinin sebebi template'lerde kullanimi pekistirmek!

template <typename T, typename U>
//decltype(t+u)sum(T t, U u) // Bu sekilde yapamamamin nedeni, hata vermesinin nedeni, t ve u'nun
                             //henuz tanimlanmamis olmasi. Ama trailing'de bu sorun asilmistir.
auto sum(T t, U u)->decltype(t+u) // Bu sekilde sorunsuz bir sekilde yapabilirim!
{

}

// C++14 ile dile eklenen, auto return type
// trailing return type'ta yalnizca fonksiyon bildirimi yapilabilir

auto func(int x, double y)
{
    return x + y;
}

////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename U>
auto func_b(T x, U y)
{
    return x+y;
}

// c++14 sonrasi bu sekilde kullanabilirim.
////////////////////////////////////////////////////////////////////////////////////
// Soru geldi.
void func_c(auto x)
{
    // Buradaki auto keyword'u soruldu. Bu dile c++20 ile eklendi.
    // template ile birebir ayni, template'lerin daha kolay yazilmasini
    // saglamak icin dile eklendi! boyle yazmak ile
//    template <typename T>
//    void func_c(T x) {} boyle yazmak arasinda bir fark. C++20 ile dile eklendi.

}
////////////////////////////////////////////////////////////////////////////////////
// Ic ice 7 8 tane template kullanilabilir. Mesela algoritmalari dusunun dedi Necati?
// mesela bir template'te std::swap kullanabilirim, halbuki swap metodu da bir template!

// PR Value         T
// L Value          T&
// X value          T&&

void deneme1()
{
    int x = 5;
    decltype(x + 5) a; // x + 5 ifadesi PR value oldugundan, int turu

    decltype(x) b = 10; // Burada b int turu iken
//    decltype((x)) c = 12; // Parantez icerisinden dolayi lValue oldugundan elde edilen tur int& olacak

    // PluralSight gibi bir yerde sorulan mulakat sorusu!
    int xy = 120;
    int *p = &xy;

    decltype(*p)y = x;
    //y int& turden

    decltype(std::move(x))ya = 10;
    // Buradan ya'nin turu sag taraf referansindan dolayi int&&
}

void deneme2()
{
    // decltype(auto) --> Ilk deger veren ifadenin turunden elde edilecek ama decltype'in kurallari ile

    int x = 4;

    decltype(auto) y = x; // Burada y'nin turu int olur
    decltype(auto) z = (x); // Burada z'nin turu int& olur.
}

////////////////////////////////////////////////////////////////////////////////////
// Kafa karisikliklari olmasi normal. Asagidaki ornekler, farki biraz acikliyor.

template <typename T>
decltype(auto) func_mor(T& x)
{
    return x;
}

template <typename T>
auto func_sari(T& x)
{
    return x;
}

void main_c()
{
    int ival = 56;
    auto x = func_mor(ival);
    // Burada x'in turu int& iken

    auto z = func_sari(ival);
    // Burada z'nin turu int olacaktir.
}

////////////////////////////////////////////////////////////////////////////////////
// Sınıf sablonu

template <typename T>
class Kdr{
  // bu bir class degil, bir class sablonu

public:
    void foo()
    {
        T x{}, y{};
        auto z = x + y;
        // Burada fark edelim ki, T turu class turu olarak geliyor ve class'lari
        // toplayabilecegim bir mekanizma yok. Cagirmadigim muddetce derlenir ve hata
        // almam! Bu Bir avantaj, ayrica kullanmadigim seyler derlenmez ve bu da
        // zaman ve boyut acisindan avantajli
    }

    // Eger sinif sablonunun kendisini kullaniyorsam asagidaki gibi kullanabilirim
    void foo2()
    {
        Kdr<T> xa;
        Kdr xb;     // Burada ikisi de ayni anlama gelir.
    }

    void foo3(T x);
    void foo4(T& x);

    Kdr();
    Kdr(T);
};

// Ilgili class'in metotlarinin tanimlamasi da birazcik normale gore farkli. Basinda, template
// ile belirtmek gerekiyor.

template <typename T>
void Kdr<T>::foo3(T x)
{

}

template <typename T>
void Kdr<T>::foo4(T& x)
{

}

//CTAD --> clas template argument dedection, C++17 ile dile eklendi. Class sablonlarinda
// tur cikarimi yapmaya yariyor.
void main_d()
{
    Kdr<int> myakdr(45); // CTAD yokken boyle explicitly olarak turu belirtmeliydim.
    Kdr mykdr(45); // Bu sekilde cagirmami CTAD sagliyor.
    // Ama dile c++17 ile eklendi maalesef

#include <vector>
    std::vector<int> ivec{1,4,5,6}; // CTAD yokken, c++17 oncesi
    std::vector ivec2{1,5,6,7}; // CTAD VARKEN



    Kdr<int> kidir(Kdr<int>&); // boyle degisik seyler bile calisiyor, Neco ornek verdi kisaca


}

////////////////////////////////////////////////////////////////////////////////////////////////
// Fonksiyon template ile class template'ler birlikte kullanilabilir.
template <typename T>
void func_i(Kdr<T>);

template <typename T>
bool operator<(const Kdr<T>&,const Kdr<T>& );
// Bu sekilde operator overload'lar tanimlanabilir.

void main_e()
{
    Kdr<int> x;
    func_i(x); // Goruldugu gibi parametre olarak class template'i girdik.

}

// Burada en onemli araclardan biri template argumani olarak yine bir sinifin sinif sablonundan elde
// edilen bir specilization'i kullanabilirsiniz.

template <typename T>
class A{

};

#include <list>

void main_f()
{
    std::list<std::vector<A<int>>> a; // Bu sekilde yapabilirim
}

// Function template'te default arguman kullandigimizda parametresiz bir cagrim yapamayiz.
// Asagidaki ornekte gorulebilir.

template <typename T>
void func_isi(T = 0)
{

}

void main_isi()
{
    func_isi(1); // bu sekilde cagirabilirim
//    func_isi(); // Bu sekilde bir cagrim hataya sebebiyet verir
}

//////////////////////
// C++20 oncesi, tamsayi turleri haricinde, non-type parametre olarak kullanilamazdi.

template <double d>
class Myclas1 {
  // Mesela su an hata vermiyor cunku 20 standartlarinda, ama 20den oncesinde hata verir.
    // int parametre, int*, int& gibi bir tamsayi turu istiyor. Ama c++20 sonrasi bu sorun yok.
};

template <auto T>
class Myclass2{
  // Function template'deki auto'dan farkli olarak duz auto gibi davranir.
};

void main_g()
{
    Myclass2<7> x; // Buradan T turu int olacaktir
}

///////////////////////////////////////////////////////////////////////////////////////
template <typename T = int>
class Myclassa{

};

void main_pg()
{
    Myclassa a;     // Bu c++17 ile mevcut. c++17 oncesi, <> yazmak zorunlu ama bos birakilabilir.
    Myclassa<> b;// Bu da c++17 oncesi. Modern c++ oncesinde yok tabi!
}


template <typename T = int, typename U = double>
class Myclassb{

};

void main_pb()
{
    Myclassb<int, long> x;     // int, long
    Myclassb<int> y;           // int, int
    Myclassb<> b;              // int, double
}

/////////////////////////////////////////////////////
template <int x = 20, int y = 59>
class Myclassc{
    // Bu sekilde de kullanimi mumkundur!
};

////////////////////////////////////////////////////
template <typename T, typename U = T>
class Myclassd{
    // Bu sekilde de yogun bir bicimde kullanimi mevcuttur!
};

////////////////////////////////////////////////////
template <typename T>
class Nec {

};

template <typename T, typename U = Nec<T>>
class Neco{
  // Bu sekilde bir onceki template class'i de default parametre olarak kullanabiliriz!
};

void main_asd()
{
#include <string>
    using namespace std;
    string str1;
    basic_string<char,char_traits<char>,allocator<char>> str2;

    // Yukarida str1 ve str2 ayni aslinda. string diyerekten tanimladigimiz sey
    // alttaki gibi bir seye donusuyor. Bu kolayligi bize default template Argument
    // sagliyor.
}

// Function template'lerin overload edilmesi
// gercek ve sablon fonksiyonlariyla overload edilebilirler.

template <typename T>
void funcaaa(T x);

void funcaaa(int x);
// Yukaridaki iki fonksiyon overload'dur.

// Eger explicitly olarak belirtmezsem, gercek fonksiyonu kullanir!

void main_aaa()
{
    funcaaa(15); // Gercek fonksiyona gider, template'e gitmez!
    funcaaa(12u); // Burada template function cagrilacaktir!
    funcaaa('A'); // Burada template function cagirilacaktir!
    funcaaa<int>(16); // Burada da template function cagirilacaktir! Bu onemli
}

////////////////////////////////////////////////////////////////

template <typename T>
void funcxxx(T) = delete;

void funcxxx2(auto) = delete; // Bu da c++20 ile gelen bi ozellik!

void funcxxx(unsigned int);
// c++17 ile bu sekilde yaptigimda, funcxxx yalnizca unsigned int ile cagirilabilir.
// Diger cagirimlarda error verecektir!

///////////////////////////////////////////////////////////////
// Ayni isimde birden fazla function template olabilir!

template <typename T>
void funcd(T x)
{
    std::cout <<" AKK WAS HERE 1\n";
}

template <typename T,typename U = T>
void funcd(T x, U y)
{
    std::cout <<" AKK WAS HERE 2\n";
}

void maind()
{
    funcd(12);
    // Bu durumda, ilk function'da olan tek parametreli kurali yazdirdi
}

///////////////////////////////////////////////////////////////
// Partial Ordering Rules!!

template <typename T>
void funca(T)
{

}

template <typename T>
void funca(T*)
{

}

void maine()
{
    int x = 10;
    funca(&x);
    // Necati hoca temel düzeyde soyle dedi -> POR'a gore, daha fazla parametreli olan
    // secilir dedi. T*, T'e gore daha fazla parametre barindirdigindan T* olan metot
    // cagirilacaktir!
}

///////////////////////////////////////////////////////////////
// explicit specialization: populer terim, full specialization'dur. Ikisi de ayni anlamda!
// Derleyiciye sunu diyebiliyoruz, "derleyici bak bu specialization'u yazman gerektiginde
// sen yazmayacaksın, onun kodunu ben sana veriyorum!" --> exp. specialization

// fonksiyon ve sinif sablonlarinda da kullanbiliyor ama genellikle sinif sablonlarinda kullaniliyor.

// Neden boyle yapayim?
// Oyle durumlar varki, belli turler icin ana template kod'lar bizim isimize gelmiyor.
// mesela int, double icin isime yariyorsun ama string icin isime yaramiyorsun gibi!

template <typename T>
T Max(T x, T y)
{
    return x > y ? x : y;
}

#include <cstring>
template <>
const char* Max(const char* p1, const char* p2)
{
    // explicit specialization
    using namespace std;
    return strcmp(p1,p2) > 0 ? p1 : p2;
}


//template <>
//const char* Max<const char*>(const char* p1, const char* p2)
//{
//    // Boyle de yazabilirim ama zorunda degilim
//}


void mainf()
{
    std::cout << Max(12,56) << "\n"; // 56 geri donus olur.
    std::cout << Max(1.2,5.6) << "\n"; // 5.6 geri doner.

    {
        using namespace std;
        std::cout << Max("yesim"s,"belgin"s) << "\n";
        // burasi konudan bagimsiz. Tirnagin sonuna s koydugumda, bunun bir
        // string oldugunu belirtiyorum. Necati ornek arasinda verdi!
    }

    std::cout << Max("yesim","belgin") << "\n"; // --> burada yesim geri doner. Exp. Spec yazilmadan once
    std::cout << Max("belgin","yesim") << "\n"; // --> burada belgin deri doner. Exp. Spec yazilmadan once

    // Burada bu sekilde geri donmesinin sebebi, yani alfabetik siralamaya bakmadan
    // donmesinin sebebi, yesim ve belgin yazildiginda, T'nin turu string degil de
    // const char* olur. Burada da ilk gelenin adresi pointer olarak daha buyuk oldugundan,
    // ilk gelen Max olarak yazar! Yani biz burada adresleri karsilastirdik!

    // Burada alfabetik karsilastirmak icin 2 yolum var.
    // 1. Overload yazarim
    // 2. explicit specialization kullanirim.
    // Explicit specialization bir template degildir!!!

}

// <> buyuktur kucuktur isaretlerinin icerisine bir sey yazildiginda bunlara angular bracket denir
// Ama yazilmadiginda buna genel olarak diamond deniyor. Teknik bir terim degildir!
// Exp. Spec'te diamond kullanilir

template <typename T>
struct name
{
    name()
    {
        std::cout << "primary template T: is " << typeid(T).name() << "\n";
    }
};

template <>
struct name<int>
{
    name()
    {
        std::cout << "Exp. sPEC int T: is \n";
    }
};

template <>
struct name<double>
{
    name()
    {
        std::cout << "Exp. sPEC double T: is \n";
    }
};

void maing()
{
    name<unsigned> m1; // Primary template olusur.
    name<int> m2;   // int parametreli class olusur
    name<double> m3; // double parametreli class olusur
}

int main()
{
    maind();
    return 0;
}





















































