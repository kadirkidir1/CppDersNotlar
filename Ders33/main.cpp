#include <iostream>
#include <string>
#include <random>

#include <exception>      
#include <stdlib.h>
#include <array>
#include <type_traits>
#include <memory>

// VARIABLE TEMPLATE

// Her bir instansciation bir variable!

//cppreference'da verilen ornek!

template <class T>
constexpr T pi = T(3.141592); // degiskene ilk deger veriyoruz

template <class T>
T circular_area(T r) // function template
{
    return pi<T> *r*r; // pi<T> is a variable template instantion
}

void main_isPointer()
{
    auto b = std::is_pointer<int *>::value; // Ilgili deger pointer ise true, degil ise false doner
    // Bu sekilde yazmak biraz karisik, oncden boyle yaziliyordu ama dile yeni ozellikler eklendi
}

template <typename T>
constexpr bool IsPointer_v = std::is_pointer<T>::value;

void main_isPointerv2()
{
    auto a = std::is_pointer<int>::value;
    auto b = IsPointer_v<int>;

    // Yukarida ikisi de ayni isi yapiyor. Variable template kullanimiyla daha kolay kod yazabildik.
}

//
template <typename T>
void func(T x)
{
    std::is_pointer<T>::value;
    std::is_pointer_v<T>;

    // iki deger ayni! Her stl'in bir _v'si varmis
}

// Yeni bir zor konu!! Perfect Formarding --> Mukemmel Gonderim
// Programlama ile genel bir teknik. Statik dil kavramına sahip dillerde!

class myc0{

};

void func0(myc0&)
{
    std::cout << "func(myc0&)\n";
}

void call_func0(myc0& x)
{
    func0(x);
}

void func0(const myc0&)
{
    std::cout << "func(const myc0&)\n";
}

void call_func0(const myc0& x)
{
    func0(x);
}

void func0(myc0&&)
{
    std::cout << "func(myc0&&)\n";
}

void call_func0(myc0&& x)
{
    func0(std::move(x));
}

void main_myc()
{
    myc0 m;
    const myc0 cm;

    func0(m);
    call_func0(m);
    func0(cm);
    call_func0(cm);
    func0(myc0{});
    call_func0(myc0{});
}

// Simdi yukaridaki senaryoda, 3 farkli deger, 3 farkli overload'a yoneliyor. Buraya kadar her sey normal!
// Sonrasinda Neco soyle diyor, bir tane call_func() olusturun ve bu func0()'lardan dogru olanlari bulsun!
// Ilk iki degerde sorun yok aslinda, call_func'in da overload'lari yazilabilir ama 3. deger sag taraf
// referansi oldugundan, std::move ile sag taraf referansi elde etmeliyiz

// Istedigimizi elde ettik ama cok fazla zahmet gerektirdi! Ya func fonksiyonunun 3,4,5 vb. daha çok
/// parametresi olsaydi!
/// Onun yerine 1 tane call_func yazalim ve onu da derleyiciye yazdiralim! Bu islem derleme zamaninda olsun,
/// calisma zamaninda degil!
///
/// Perfect Forwarding de modern c++ ile dile eklendi

/// Eger perfect forwarding yapmak istiyorsak,
/// Parametresi forwarding reference olacak! &&

template <typename T>
void call_func(T&& x)
{
    func0(std::forward<T>(x)); // Bunu ezberleyin dedi necati! ileri c++'de 40dk anlatmis
}

//template <typename T, typename U, typename V, typename W>
//void func(T &&t, U&& u, V&& v,W&&w)
//{
//    ffunc(std::forward(t),std::forward(u),std::forward(v),std::forward(w));
//} // Bu sekilde 4 ve daha fazla parametreli de yapabilirdik.

// stl lib'lerinde emplace_back metotlarinda cok aktif kullaniliyormus.
/// Ornegin bir  vektore push_back ile class'lar ekleyecegim. Copy ctor degil de, adresini
/// gondermek istiyorum. O zaman yapmam gereken sey, push_back yerine emplace_back kullanmak

/// Forwarding reference olabilmesi icin, const ya da volatile ile nitelenmemis olmasi gerekiyor!
/// yalnizc T&&

// Perfect forwarding'e en onemli orneklerden birisi, smart pointer'larin make_unique metodudur!

/// VARIADIC TEMPLATES
#include <tuple>

void main_tuple()
{
    std::tuple<int> x1;
    std::tuple<int,double> x2;
    std::tuple<int,int,std::string> x3;
    std::tuple<int,const char *,std::string, double> x4;

    // Nasil oluyor da, tuple konteyner'i her turu birden fazla parametre ile alabiliyor!
    // Cunku o bir variadic template!

}

/// template<typename ...Args>
/// Yukaridaki yapiya template parametre paketi deniyor!

template<typename ...Args>
class myc2{

};

void main_myc2()
{
    myc2<int,double,const char*> x; // Variadic sayesinde, 3 parametreli bir template tanimlamadan
    // bu sekilde kullanabildim!
}

template<typename ...Args>
void func(Args ...args)
{
    // variadic function template
}

template <typename T, typename ...Ts>
std::unique_ptr<T> MakeUnique(Ts&& ...args)
{
    // make_unique metodunun mantigi gosterilmistir!
    // Variadic template ama && oldugundan dolayi universal referance, yani perfect
    // forwarding yapabilmeme olanak sagliyor!
}

/// sizeof
template <typename ...Ts>
void func_ts(Ts ...args)
{
    sizeof...(Ts); // Bunun cevabi compile time'de ediliyor ve pakette kac oge oldugunu bize veriyor
    sizeof...(args); // Bu da ayni sekilde
}

template <typename ...Ts>
void func_ts2(Ts ...args)
{
    // Pack expansion
    std::tuple<Ts...> x;
    std::cout << typeid(x).name() << "\n";
}

class nur{

};

void main_ts2()
{
    nur a;
    func_ts2(1 , 2.3,'A',nur{},a);
}

//
template <typename ...Ts>
void funcs(Ts ...args)
{
//    args
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
void print(const T& r)
{
    std::cout << r << "\n";
}

template <typename T, typename ...Ts>
void print(const T& r, const Ts& ...args)
{
//    std::cout << __FUNCSIG__ << "\n"; // FUNCSIG bizim derleyicimizde yok ama fonksiyonlarin
    // imzalarini gosteriyor. GCC deskekli bir sey
    print(r);
    print(args...);
}
// Yukaridaki metodun ilk parametresi variadic degil ama ikinci parametresi variadic!
// 5 prametreli bir print cagrisi yaptigimizi dusunelim. Alttaki template'e bakarsak,
// ilk parametreyi variadic almiyor, ikinci parametresi variadic. Ve ilkini print ediyor,
// variadic olanlarin sayisi 4'e dusuyor. Sonra kendisini tekrar cagiriyor derken 4,3,2,1
// diye hepsini yazdiriyor. Burada bir recursive cagri soz konusu!

void main_Var()
{
    int x = 999;
    double d = 99.9;

    print(x,d,999L,954.3f);
}

///////////////////////////////////////////////////////////////////////////////////////
/// C'deki virgul mekanizmasini iyi anlamamiz gerekiyor bu teknik icin
/// C'deki virgul operatoru, once, virgulun sol tarafini isler. Virgulun urettigi deger,
/// virgulun sagindaki degerdir!
/// Yani 0

#include <initializer_list>

template <typename ...Ts>
void print2(const Ts& ...args)
{
    // int a[] = {(std::cout << args, 0)...}; // Boyle bir diziye atarsan calisir ama
    // gereksiz maaliyet olur. Bunu cozmek icin initializer_list kullanip void ile
    // tanimlasak daha mantikli!
    (void)std::initializer_list<int>{(std::cout << args << " ",0)...};
}

void main_print2()
{
    print2(1,2,3,4,5,'a','b',"asis",34.5);
}

// Dile c++17 ile baska seyler eklenmis ama Necati simdi anlatmiyor. Fold ifadeleri. Ileride anlatacak!

// Compile time if'i zamaninda anlatinca yine buraya donup anlatacakmis!

///////////////////////////////////////////////////////////////////////////////////////

template <typename ...Ts>
void foo(Ts &&...args)
{
    std::tuple<Ts...> x(args...);
}

template <typename ...Ts> // Hem variadic hem perfect forwarding!
void func_varPerfect(Ts && ...args)
{
    foo(std::forward<Ts>(args)...);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/// STANDARD TEMPLATE LIBRARY --
/// KONTEYNER'LAR
/// Sequence Containers
///     std::vector
///     std::deque
///     std::list
///     std::array --> C dizilerini sarmalayan bir wrapper
///     std::forward_list --> c++11 oncesi dile eklendi.
///     std::string --> dinamik dizi,
///
/// ASSOCIATIVE CONTAINERS
///     std::set
///     std::multi_set
///     std::map
///     std::multi_map
///
/// UNORDERED CONTAINERS
///     std::unordered_set C++11
///     std::unordered_multi_set C++11
///     std::unordered_map C++11
///     std::unordered_multi_map C++11
///
///
/// STL genişletilebilir bir yapıda, yeni yapılar iteratorler eklenebilir.
/// STL OOP degil, nesne yönelimli programlama değil.
/// Exception handling yoğun olarak kullanilmiyor.



int main()
{

    main_print2();
    return 0;
}





















































