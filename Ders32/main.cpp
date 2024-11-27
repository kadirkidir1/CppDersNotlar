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

///////////////////////////////////////////////
/// \brief Mulakat Sorusu
/// \return
///

class A {};

class B {
public:
    B(A){}
};

void main_mulakatSorusu()
{
    B bx(A());
    // Burada istenen B turunde, A nesnesini kullanan bir nesne olusturmak olabilir ama
    // burada farkli bir muhabbet varmis.
    // Burada, bx adında bir fonksiyon tanimladigimizi dusunuyor derleyici

    // Peki nasıl oluyor da bu bir fonksiyon bildirimi oluyor?
    // int(int) bu bir fonksiyon turu
    // int(*)(int) bu bir fonksiyon pointer bildirimi

    // Yani aslında
    B Bx(A(*)()); // Yukarıdaki ile bunun bildirimi arasında herhangi bir fark yok!
    B cx((A())); // Modern c++ oncesi, most vexing'den kurtulmak icin boyle yapiyorduk

    B dx(A{}); // Bu modern c++ ile, A nesnesinin init olacagini gostererk yapiliyor.
    B ex {A()}; // Modern c++
    B fx{ A{}}; // Modern c++
}

#include <string>

class Example {
public:
    Example() {}
    Example(const std::string&) {}
};

int main_CHATGPT() {
    Example obj(Example()); // "Most vexing parse" sorunu
    return 0;
}
//Burada Example obj(Example()); ifadesi geliştirici tarafından obj adında bir Example nesnesi
//tanımlayıp, bir diğer Example nesnesi ile başlatma niyetiyle yazılmıştır. Ancak derleyici
//bunu şu şekilde yorumlar:
//
//obj, dönüş tipi Example olan ve parametre olarak bir Example almayı bekleyen
//bir fonksiyon bildirimidir.
//Yani, Example obj(Example()); aslında bir fonksiyon prototipidir, bir nesne oluşturmaz.
//Bu bir derleme hatasına veya beklenmeyen davranışlara yol açabilir.

class myc1{
public:
    void func()&{} // reference qualifier deniyor.
    void funcb()&&{} // reference qualifier deniyor.
    void funcc()const &{} // reference qualifier deniyor.
};

class myc2{
public:
    void func(){} // Bu sekilde kullanirsam, hem lValue hem rValue olarak cagirilabilir.
};

void main_mulakatSoru2()
{
    myc2 m1;
    m1.func(); // Burada sol taraf cagrisi yapmisiz!

    myc2{}.func(); // Burada bir sag taraf cagrisi yapmisiz


    // oyle durumlar var ki, sinifin bazi oge fonksiyonlarinin sadece lValue exp kategorisindeki
    // nesnelerle cagirilmasini istiyorum.

    // & tek ref kullanirsak, yalnizca lValue exp kullanabiliriz.
    myc1 m2;
    m2.func(); // Goruldugu gibi lValue nesneden cagirabildim.

    // && olan ise yalnizca rValue olarak cagirilabilir.
    myc1{}.funcb();
}

class myc0 {

};

void main_mulakatSoru2_devam()
{
    myc0 m;
    myc0{} = m; // Bu bir hata degil ama cok mantiksiz!! Cunku myc0 classinin atama operator
    // fonksiyonu (=) ref qualifier ile belirtilmemis ve legal!
}

class myc0_2 {
//    myc0_2& operator=(const myc0_2&) = default; // Bu derleyicinin yazdigi kod
    myc0_2& operator=(const myc0_2&)& = default;
};

void main_mulakatSoru2_devam2()
{
    myc0_2 m;
//    myc0_2{} = m; // Artik bu bir hata!
}

/////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

class myc3{
public:
    void func()&
    {
        cout << "lValue exp\n";
    }

    void func()const &
    {
        cout << "const Value exp\n";
    }

    void func()&&
    {
        cout << "rValue exp\n";
    }
};

void main_1()
{
    myc3 m;
    m.func(); // Burada lValue exp ciktisini basacak.

    myc3{}.func(); // burada rValue exp ciktisini basacak!!

    const myc3 cm;
    cm.func(); // const Value exp ciktisi basilacak
}

// Explicit spec'e devam ediyoruz!

template <int x>
class kdr1 {
public:
    kdr1()
    {
        std::cout << "primary template\n";
    }
};

template <>
class kdr1<5> {
public:
    kdr1()
    {
        std::cout << "explicit spec. template\n";
    }
};

// Yukaridaki ornekte bir explicit spec ornegi verilmistir ama bu template'lerin bir
// non-type specialization oldugu dikkat edilmelidir!

void main_kdr1()
{
    kdr1<2> k1;
    kdr1<5> k2;
}

// Template meta programming! Ileri c++ kursunda daha detayli anlatacakmis.

// populer kullanilan terim: meta function
// meta func denmesinin nedeni, compiler time'da deger uretmek icin ya da bir tur
// bilgisi etmek icin siniflari kullaniyorum. Siniflari kullanarak bir deger ya da tur
// hesaplamaya yonelik olusturulan siniflara meta function deniyor.

// compile time'da faktoriyel hesaplayan meta kod yazacagiz

template <long long n>
struct Factorial {
    // eger sinifin static veri elemani const ise, sinif icerisinde ilk deger verebiliriz.
    const static long long value = n * Factorial<n-1>::value;

    // Burada bir recursive durumu vardir. Mesela kod'da 5'in faktoriyelini cagirdik.
    // 5* 4 , , 3, 2,1,0,-1 ... gibi gibi sonsuza gidecek. Bunu durdurmanın yolu da,
    // explicit specialization yazmak!!!
};

template<>
struct Factorial<1>
{
    const static long long value = 1;
};

void main_kdr2()
{
    const long long a = Factorial<19>::value;
    std::cout << "a degeri:" << a;
}

///////////////////////////////////////////////////////////////////
// Mulakat sorusu!
// Biraz saka yollu bir soru. 0'dan 100'e kadar ekrana sayılari yazin ama
// dongu kullanmayin dedi NECO!

template <int n>
struct Nec : public Nec<n - 1> {

    Nec() {
        std::cout << n << "\n";
    }
};

template <>
struct Nec<0>
{
    Nec() {
        std::cout << 0 << "\n";
    }
};

void main_nec()
{
    Nec<100> x;
}

///////////////////////////////////////////////////////////////////

template<typename T>
void func(const T&)
{
    std::cout << "primary template\n";
}

template<>
void func(const int&)
{
    std::cout << "explicit specialization\n";
}

void func(double)
{
    std::cout << "ordinary function\n";
}

void main_kdr3()
{
     func(10); // explicit Spec
     func(0.42); // ordinary function
     func('A'); // primary template
     func("10"); // primate template
}

// Necatinin iyi seviye mulakat sorusu!

template<typename T>
void funcs(T)
{
     std::cout << "1";
}

template<>
void funcs(int*)
{
     std::cout << "2";
}

template<typename T>
void funcs(T*)
{
     std::cout << "3";
}

void main_kdr4()
{
     int* p = nullptr;
     funcs(p);

     // Bu durumda program ciktisi 3 olur. Cunku 2. siradaki exp. spec 1. template'in
     // exp spec'i oldugundan boyle davranir. Ama siralama degisirse???
}

template<typename T>
void funcf(T)
{
     std::cout << "1";
}

template<typename T>
void funcf(T*)
{
     std::cout << "2";
}

template<>
void funcf(int*)
{
     std::cout << "3";
}

void main_kdr5()
{
     int* p = nullptr;
     funcs(p);

     // Onceden exp. spec 1. template'e aitti ama simdi 2'ye ait.
}

///////////////////////////////////////////////////////////////////
template<typename T>
struct Necf {
     void func()
     {
        std::cout << "primary template\n";
     }
};

template<>
void Necf<double>::func()
{
     std::cout << "explicit spec. for Nec<double>\n";
}

void main_kdr6()
{
     Necf<int>{}.func();
     Necf<double>{}.func();

     // Bu ornekte, explicit spec'in yalnizca global fonksiyonlar icin degil,
     // sinif uye fonksiyonlarinda da kullanilabildigi gosterilmistir.
}

/////////////////// MULAKAT SORUSU
/// Normalde static degiskenler, class icerisinde tek olarak tutulur. Mesela

class f_kdr {
 public:
     inline static int x{};
};

void main_kdr7()
{
     std::cout << f_kdr::x++ << "\n";
     f_kdr a;
     f_kdr aa;
     f_kdr aaa;

     std::cout << a.x++ << "\n";
     std::cout << aa.x++ << "\n";
     std::cout << aaa.x++ << "\n";

     /// Cikti 0
     ///       1
     ///       2
     ///       3 olacaktir. Ama template'lerde olay degisir, her bir farkli tur icin
     ///                    farkli bir static olusturulur. Asagidaki ornekte detayli
     ///                    aciklanmistir.

}

template <typename T>
class myc4 {
 public:
     inline static int x{};
};

void main_kdr8()
{
     std::cout << myc4<int>::x++ << "\n";
     std::cout << myc4<double>::x++ << "\n";
     std::cout << myc4<string>::x++ << "\n";
     std::cout << myc4<int>::x++ << "\n";

     ///
     /// 0
     /// 0
     /// 0
     /// 1
     /// Cikti bu sekilde olacaktir. Her tur icin farkli yani!
}

/// Partial Specialization: Sadece sinif sablonlari icin var

template <typename T>
class myc5{
 public:
     myc5()
     {
        std::cout << "primary template\n";
     }
};

template <typename T>
class myc5<T*> {
 public:
     myc5()
     {
        std::cout << "Partial spec template\n";
     }
};

void main_kdr9()
{
     /// Partial Spec., turleri degil de,daha genis ifadeleri kumelemek icin kullanilir.
     /// Yani ornegin tum pointer turlerini, ya da referanslari vb. Yukaridaki ornekte
     /// goruluyor ki, ilk template bizim normal klasik bir template'imiz iken, asagidaki ise,
     /// yalnizca pointer turleri alir.
     ///

     myc5<int> a; // primary template
     myc5<int*> b; // Partial spec template
     myc5<int**> c; // Partial spec template
     myc5<int[]> d; // primary template
     myc5<int&&> e; // primary template
     myc5<int&> f; // primary template
}

/////////////////////////////////////////////////////////////////////////

template <typename T,typename U>
class myc6{
 public:
     myc6()
     {
        std::cout << "primary template\n";
     }
};

template <typename T>
class myc6<T, T> {
 public:
     myc6()
     {
        std::cout << "Partial spec template\n";
     }
};

/// Yukaridaki durumlarda, iki parametrenin de ayni tur oldugu durumlarda,
/// partial Spec kullanilacak.

void main_kdr10()
{
     myc6<int,int> a; // Partial
     myc6<int, int&> b; // Primary
}

///////////////////////////////////////////////////////////
template <typename T>
class myc7 {
 public:
     myc7()
     {
        std::cout << "primary spec!\n";
     }
};

template <typename T, typename U>
class myc7<std::pair<T,U>> {
 public:
     myc7()
     {
        std::cout << "partial spec!\n";
     }
};

void main_kdr11()
{
     myc7<const int&&> b; // primary template
     myc7<std::pair<int,double>> a; // partial spec
}

/// Constructor'da template olabilir!

class mycb{
 public:
     template <typename T>
     mycb(T) {

     }

     template <typename T>
     void func(T x) {} // Bu bir member template
};

// Zorlanilan bir kisim!
template <typename T>
class mycc{
 public:
     void func(mycc){} // func'in içerisindeki parametre aslinda, mycc(T) seklindedir.
                       // Yazmasak da o sekilde tanimlandigini bilmek gerekiyor.
};

void main_cc()
{
     mycc<int> m1,m2;
     mycc<double> m3;

     // Yukaridakileri tanimladiktan sonra soru soruyor!
//     m3.func(m1); // Bu gecerli mi diye soruyor. Cevap HAYIR! Nedeni su, mycc'in int acilimi
                    // ayri bir sinif, double'i ayri bir sinif!

     m1.func(m2); // Bunda bir sorun yok ama!
     // Peki
//     m3.func(m1); Bunu legal kilacak bir sentaks var mi?

}

template <typename T>
class myccc{
 public:
     template <typename U>
     void funccc(myccc<U>){}
};

void main_ccc()
{
     myccc<int> m1,m2;
     myccc<double> m3;

    m3.funccc(m1); // Yukaridaki soruun cevabı bu sekilde cozulur!

}

///////////////////////////////////////////////////////////////////////////
template <typename T, typename U>
struct Pair {
    // stl'de kullanilan en cok tiplerden biri, bunun orijinali
  // iki tane degeri bir arada tutan bir sinif. Nicin boyle bir sinif kullanalim?
    //pair'de ilk ogeyi tutan first keyword'u, ikinci ogeyi tutan ise second keyword'u

    //  std::pair<int,string> p;
    // Bu sekilde bir pair olusturdugumuzda ilk degerleri value init edilecek! Yani 0 olacak
    /// Garbage bir deger almayacagi garanti!

    /// std::pair'in = operatoru, iki farkli turu esitleyebiliyor. asagida gorulur.
    void func()
    {
        std::pair<int, int> p1;
        std::pair<double, double> p2;
        p1 = p2; // Goruldugu gibi std::pair class'inde atama islemi yapilabiliyor.
                 // Bunu yapabilmemizin sebebi, bir ustteki ornekteki gibi

        // Asagida = operatorunun overload'i yapilmistir
    }

    template <typename X, typename Y>
    Pair& operator=(const Pair<X,Y>& other) {
        first = other.first;
        second = other.second;

        return *this;
    }

    T first;
    U second;
};

void main_pair()
{
    Pair<int, int> p1;
    Pair<char,char> p2;

    p1 = p2; // Goruldugu gibi bu sekilde, atama yapabilirim ama, turlerin birbirine
    // assignable olmalidir. Yani double'la string'i esitleyemem!
}

/////////////////////////////////////////////////////////////////////////////////
// Simdi c++17 oncesinde, istedigimiz template'tin ya da STL'in parametrelerini belirtmek
// zorundaydik! Ornegin

template <typename T,typename U>
class beforecpp17 {
public:
    beforecpp17(const T&, const U&){}
};


void main_beforeCpp17()
{
//    beforecpp17 a; // bu sekilde zaten yapamam
//    beforecpp17 a(13,23.5); // bu sekilde de yapamam. c++17 oncesi tek yol asagida
    beforecpp17<int,double> a(13,4.5); // Ama bunu asmanin yolu, make gibi bir metot yazmak!

   /// mesela make_unique, make_shared, make_pair gibi!!!
}

//**//

template <typename T,typename U>
class beforecpp17a {
public:
    beforecpp17a(const T&, const U&){}
};

template <typename T, typename U>
beforecpp17a<T,U> make_beforecpp17a(const T& t, const U&u)
{
    return beforecpp17a<T,U>{t,u};
}

void main_beforeCpp17a()
{
    beforecpp17a a = make_beforecpp17a(13,4.5);
    // Goruldugu gibi make metodu ile <> icerisinde tur belirtmeden bunu c++17 oncesinde
    // yapabildim.
    auto m = make_beforecpp17a(3,6.0);
}

void main_useAuto()
{
    auto m = make_pair("kadirkidir",1996);
}

// Make_pair'in bir inserter'i yok. Yani << operator karsiligi yok!
template <typename T, typename U>
std::ostream& operator <<(std::ostream& os, const std::pair<T,U>&p)
{
    return os << "[" << p.first << ", " << p.second << "]";
}
#include <bitset>
void main_ostream()
{
    std::cout << make_pair(12,4.5) << "\n";
    std::cout << make_pair(make_pair(12,4.5),make_pair("ali",bitset<16>(23)));
}

/// 2 tane pair'i karsilastirabilecegimiz arac std lib'te var ama kendimiz de yazabiliriz!

void main_pairDiff()
{
    pair p1{3,4.5}; // CTAD'tan yararlandım
    pair p2{3,1.2};

    cout << (p1 < p2);
}

/// ALIAS TEMPLATE -- Tur es isim sablosu
/// onceden tek yol typedef idi, using de devreye girdi.
/// Neden using'i typedef'e tercih etmeliyiz? Cunku sentaks daha basit

typedef int (*FCMP)(const char *,const char *); // typedef ile function pointer
using FCMP = int (*)(const char *, const char *); // Daha kolay
// Tek yolu kolaylik degil. Typedef C'den geldigi icin template haline getirilmiyor

// Pratikte kullanilmayan ama anlamak icin bir ornek
template <typename T>
using Ptr = T*;

// Ornegin, Ptr<int> acilimi, int*'a esit!

template <typename T, int size>
using Array = T[size];

void main_usingArray()
{
    Array<double, 5> a; // a 5 elemanli bir dizi
}

// ASIL KULLANILDIGI URETIMDE KULLANILAN YERLER

template <typename T, typename U>
class mycaf {
public:

};

template <typename T>
using mycaf2 = mycaf<T,int>;

void main_mycaf2()
{
//    mycaf2<int>
}

template <typename T>
using epair = std::pair<T,T>;

void main_epair()
{
    epair<int>;
}

#include <bitset>
#include <set>

template <typename Key>
using gset = std::set<Key, std::greater<Key>>;

void main_bitset()
{
    gset<int> myset;
}

///////////////////////////////////////////////
#include <stack>
#include <string>

void main_stack()
{
   // string turunden bir stack tanimlamak istiyorsak ve deque'sunun
    // default olarak int degil de vector olmasini stiyorsak boyle
    // yazmaliyiz!
    std::stack<std::string,std::vector<std::string>> s_stack;
}

template <typename T>
using vstack = std::stack<T,std::vector<T>>;

void main_stackk()
{
    vstack<int> a;// yukaridakiyle ayni!!
}



int main()
{
    main_ostream();
    return 0;
}





















































