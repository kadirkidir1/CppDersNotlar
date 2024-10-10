#include <iostream>
#include <string>
#include <random>

#include <exception>      
#include <stdlib.h>
#include <array>


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///                                 TEMPLATE                                    ///
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/// Derleyiciye kod yazdiran kod
/// Metakod
/// Generic'ten bahsedilen, bir kodun, birden fazla tur ile kullanilabilmesi, ture bagimli olmamasi.
/// Çok sayıda kural var. C++'ı zorlastiran seylerden birisi.
/// STL --> Standart template Library
/// C++'in cogunlugu template'lerden olusuyor.
/// ostream, istream, vector vb. bunlar hep STL
/// smart pointer'lar birer template
/// Her yeni C++ standardi ile generic programlara araclari artiyor, yeni ogeler ekleniyor
/// Standart kutuphane buyuyor
///
/// constexpr if --> c++17 ile eklendi.
/// std::optional
/// std::variant gibi eklenen ogeler var.
///
/// concepts --> c++20 ile eklenen en onemli araclardan biri
/// https://www.amazon.com/C-Templates-Complete-Guide-2nd/dp/0321714121
/// Yukaridaki link, necati hocanın templates'lerle ilgili onerdigi bir kitap.
/// Biraz agir bir kitap, template'ler anlasildiktan sonra bakilabilir. 832 sayfa
///
/// template code --> Asil amaci derleyiciye kod yazdirmak! Template olmasaydi,
///                   o kodu biz yazmak zorunda kalacaktik.
///
/// 1. function template
/// 2. class template
/// Bu ikisi modern c++'tan once de vardi. Ancak modern c++'ta dile cok fazla eklendi.
/// modern c++'tan once template'ler cok fakirdi.
/// 3. variable template --> degisken sablon. Oyle bir metakod ki, farkli farkli degiskenlerin
/// tanimi yapilabiliyor.Modern c++ ile dile eklenen bir arac. c++14
/// 4. alias template --> tur es isim sablonu.
/// 5. variadic template -->
/// 6. concept template --> c++20 ile eklendi.
///
// Template parameters: <> isaretlerinin arasina gelen sey
// 1. type parameters olabilir.
// 2. non-type parameter olabilir.
// 3. template parameter olabilir.

/// template <class T> --> burada anlam class anlaminda degil. Herhangi bir tur anlaminda. int double kullanilabilir.
/// template <typename T>
/// Gunumuzde yukaridaki ikisini kullanmak acisindan bir fark yok. Ikisi ayni anlamda.
///
///

// type parameters ornegi
template <typename T, class U> // Burada T de U da birer tur ifade ederler.
T func(T x, U y)
{

}

// Birisi ileride anlatilacak deduction ile ilgili bir soru sordu. Hoca ileride zaten
// detayli anlatacagini soyledi ama kisaca konuya girdi.

std::vector<int> x; // mesela burada int parametresi alacagini explicitly olarak bildirdim.
std::vector vec{1,3,4,5}; // Burada derleyici templete argumaninin ne olmasi gerektigini anladi.

// non-type parameters ornegi
template<int x>
class myc1 {

};

// STL'in en cok kullanilan parametrelerinden birisi array. c dizilerini sarmalamak icin var. wrapper class
// ama bir sinif sablonu.
std::array<int,10> ax; // birinci parametre type parameter iken ikinci parameter non-type parameter. Yani
                       // template'ini kendimiz yazacak olsak su sekilde olurdu.

template<typename T, std::size_t size>
class Arrayy {

};

Arrayy<double,20> axa; // bu sekilde aciklanabilir std::array Tabi class icerisindeki kodlari yazmadik.

// bitset STL'i ise non-type parameter
#include <bitset>

std::bitset<32> btst; //

// template kodlar cok buyuk cogunlukla baslik dosyalari icerisinde olacaklardir.
// ODR'i ihlal ediyor olmayacak. Baslik dosyasında olmasi sart degil ama genel kani degil!

// Function Template
// Algoritmalar genellikle turden bagimsiz, ama c/c++'ta program ture bagimli!

void swap(int &x, int &y)
{
    int temp{x};
    x = y;
    y = temp;
}

void swap(double &x, double &y)
{
    double temp{x};
    x = y;
    y = temp;
}

//Yukarida ayni algoritmayi yapan iki farkli tur icin iki farkli fonksiyon var.
// Her kod her template icin uygun olmayabilir. Ama hata derleme zamaninda alinacaktir. Mesela!

template <typename T>
void func1(T x)
{
    x.foo();
}

// Mesela yukaridaki fonksiyona bakilirsa, turun foo() adinda bir metodunun olmasi lazim, ortada
// herhangi bir tur olmamasina ragmen ortada bir hata yok! Ben ne zaman template'i kullanip foo()
// icermeyen bir cagrisim yaparsam o zaman hata alirim.

void main1()
{
//    func1<int>; // Mesela yukaridaki func1 template'i bu satir yorumdayken hata vermez. Ama ne zaman yorum
// kaldirilirsa gorulur ki, int turunun foo fonksiyonu yok, o zaman hata verir!!!
}

// TEMPLATE INSTANSCIATION --> Derleyicinin o kodu yazmasi demek!
// TEMPLATE SPECILIZATION --> Necati buna template açılımı diyor.

// 41. dakikada kaldık.

// Template tarafinda bir kere tanimladigimiz typename'i birden fazla kullanamayiz. YANI

template <typename T>
void f_kdr(T x){

}


//void f_kdr2(T y) {
    // Yorum kaldirilirsa bu metodun dogru olmadigi gozukur. Her metot'ta typename ile tur tanimlamak
    // gerekir.
//}

template <typename T>
void f_kdr2(T y)
{
    // Dogru kullanimi bu sekildedir.! Dk 45'te kaldik
}

// function template'ler overload edilebilir.

template <typename T>
void func_x(T x)
{

}

void f1()
{
    func_x<int>(10); // boyle de yapabilirim explicitly

    func_x(3.4); // Template argument deduction --> Otomatik olarak double cagirir!

}

// Template argument Deduction //
// auto type deduction ile arasinda hicbir fark yok birkac istisna disinda!

// Kurallar!

template<typename T>
void func_11(T x)
{

}

template<typename T>
void func_12(T& x)
{

}

template<typename T>
void func_13(T&& x)
{

}
// Yukaridaki ucunun de kurallari farkli.

void main_2()
{
    func_11(12); // --> func<int> burada direkt int acilimi. Herhangi bir referans olmadigindan turun
                 // aynisi gidiyor. Necati digerlerinde onu anlatacak!


}

template<typename T>
class TypeTeller; // Neco bunu turu ogrenmek icin kullaniyor.

template<typename T>
void func_14(T x)
{
    TypeTeller<T> t; // TypeTeller hata verecek, ama hatada hangi tur oldugunu derleyici bize gosterecek
}

void main_3()
{
    const int ival{15};
//    func_14(ival); // Yorum kaldirilip hataya bakilirsa, turun <int> oldugunu gosterir bize!
    int a[]{1,5,7};
//    func_14(a); // Yorum kaldirilirsa turun int* oldugu gozlemlenir.
}

// int& bir turdur. int&& de bir turdur!!
// Br fonksiyona const ve & gonderilirse const ve & duser. Zaten bildigimiz bir sey.
// int a[]{1,2,3,4};
// func(a); // Diye cagirdigimde, TypeTeller hatasi icerisinde, Array decay'den dolayi a array'inin
            // ilk nesnesinin adresini gonderir ve tur int* olur. Denenebilir!

template<typename T>
void func_15(T& x)
{
    TypeTeller<T> t;
    // Bu template'de & var. Ref olmayandan tek farki const'luk dusmuyor.
}

void main_4()
{
    int x = 1;
//    func_15(x); // yorum satiri kaldirilinca turun int oldugu gorulur

    const int y = 5;
//    func_15(y); // burada turun const int oldugu gorulur.

    // const'lugun yaninda, array decay yoktur!
    int fa[3]{1,2,5};
//    func_15(fa); // burada tur, int[3] olur. Ilk nesnenin adresi olmaz!

}

///////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void func_7(T&x, T&y){

}

void main_5()
{
    func_7("kdr","nur"); // Burada bir hata yoktur. T'nin turu const char[3]
//    func_7("nur","kadir"); // Burada hata vardir. Turu const char[3] mu [5] alacagini bilemez ve hata verir!

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Farkli orneklere gecti hoca dersin 2. yarisinda
///////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, int size>
void func_v(T(&r)[size])
{
//    TypeTeller<T> t;
    // yorum satiri kaldirilip hata gorulurse, gelen parametrelerin int ve 5 oldugu gorulur.
}

void main_v()
{
    int a[5]{};
    func_v(a);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
void func_j(T (*)(U))
{

}

int foo(double);

void main_j()
{
    func_j(foo);
    // foo fonksiyonunun adresini gonderdim yani function pointer yapisi kullandim.
    // Burada T degeri, geri donus degeri int iken
    // U degeri ise, double turden olacaktir.
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
void func_z(T,U)
{

}

void main_z()
{
    func_z<int>(4,5.4); // Boyle cagirdigim zaman ilk parametre int olacak ama ikincisi int olmayacak!
                        // dedection yapacak. Ikincisini de belirlemek icin onu da belirtmem gerekir!
    func_z<int, double>(5,4); // Bu sekilde!!
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// En fazla zorlayan yere glecegiz dedi hoca!
template <typename T>
T func_a(int)
{

}

void main_a()
{
//    func_a(13);  // Yorum satirlari kaldirilirsa gorulecektir ki, geri donus degerini yani T turunu
                   // derleyici belirleyemedigi icin hata aliniyor.
}

// bazi std metotlari da boyle! Mesela make_unique_pointer kullandigimizda ilk parametrede turu belirtmek
// zorundayiz.

//std::make_unique(int,.....) // bu sekilde!

//////////////////////////////////////////////////////////////////////////////////////////////////
// Default template argument

template <typename T, typename U = T>
void func_t( T,U)
{

}
// metotlardaki default argumentin aynisi, U= int de diyebilirdik!

//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void func_b(T x)
{
    x();
}

int foo_b()
{
    std::cout << "int foo()\n";
    return 1;
}

class myclass {
public:
    void operator()()const
    {
        std::cout << "operator\n";
    }
};

void main_b()
{
    // Yukarida, bir turu metot gibi kullanmis. Yani x() yapmis. Bu hangi durumlarda olabilir?
    // Function pointer olabilir.
    func_b(foo_b);

    // 2. olarak, bir class'in () operator overload'u da cagirilmis olabilir.
    myclass mx;
    func_b(mx);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void func_c(T&& x)
{
    // Burada sag taraf referansi olmuyor. Burada farkli bir kural var
    // forwarding reference deniyor buna.
    // Scout, universal reference diyor buna!

//    TypeTeller<T> a;  // Eger gonderilen ifade lValue expression ise, T bir lValue olur.
                        // Burada yorum satiri kaldirildiginda gorulur ki, T'nin turu T& olur.

}

void main_c()
{
    int x = 10;

    func_c(x); // Normalde eger sag taraf referansi olsaydi hata vermeliydi.
               // cunku x bir l value iken r value'ya atanamazdi. Ama hata vermedi cunku
               // burada olay sag taraf referansi degil!
}


// Normal olarak C++ dilinde reference to reference yoktur.
// Ama type dedection oldugu zaman, reference to reference olabiliyor.

//////////////////////////////////////////////////////////////////////////////////////////////////
// reference collapsing Kurallari
// T&   &   T& --> Sol taraf referansina sol taraf olusursa sonuc sol taraf referansi
// T&&  &   T&
// T&   &&  T&
// T&&  &&  T&&

void main_d()
{
    int y;
    using LRef = int&;
    LRef& x = y; // Burada lValue'ya lValue olacagindan, x lValue olacaktir.

    using RRef = int&&;
    RRef &&n = 15; // Burada rValue'ya rValue olustugundan, rValue deger vermek zorundayiz.
}

//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void func_f(T& x)
{

}

void main_f()
{
    int y = 15;
    func_f<int&>(y); // lvalue'ya lValue atandigindan, yukarida x'in turu lValue int& olacaktir.
}

////////////////////////////////////////////////////
template <typename T>
void func_g(T&& x)
{
//    TypeTeller<T> a;
    // Bu ornekte, T'nin turu int iken, a'nin turu int&& oldugu gorulur.
}

void main_g()
{
    func_g(19);
}

// Eger, const T&& olsaydi, universal reference olmayacakti
// void func_g(const T&& x) // Burada olmazdi
////////////////////////////////////////////////////
// Universal fonksiyondan anladigimiz, bu fonksiyon, her turden parametreyi kabul eder.
// lValue da rValue da, const olan da olmayan da arguman gonderebiliriz!!

template <typename T>
void func_h(T&& x)
{
}

void main_h()
{
    int x = 10;
    const int cx = 20;

    func_h(x);
    func_h(cx);
    func_h(10);

    // her seyi kabul ediyor!
}

// AYrica, bu fonksiyonun turunun referans olmama ihtimali yok! ya lValue ya rValue referans olacak
// ama referans olmama ihtimali yok!

//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void func_i(T&& , T)
{
}

void main_i()
{
    int x = 4;
//    func_i(x,x); // Burada ambiguity olusur!
    // T hem int& hem de int olamayacagindan, ambiguity olusur.
}

template <typename T>
void func_l(T&& , T)
{
}

void main_l()
{
    func_i(3,3); // Burada ambiguity olusmaz. Hata da vermez. Cunku rValue gonderdigimden,
                     // T'nin turu her turlu int olacak.
}

//////////////////////////////////////////////////////////////////////////////////////////
#include <initializer_list>

void main_as()
{
    auto x = {1,2,3,5};
    // x'in turu, initializer_list<int> turunden oluyor.
}

template <typename T>
void func_m(T x)
{

}

void main_m()
{
//    func_m({1,2,3,5});
    // auto ile template type dedection tamamen ayni ama tek fark, initializer list'i template
    // kabul etmiyor. Yorum satirindan cikarilirsa hata aldigi gorulur.

}

//////////////////////////////////////////////////////////////////////////////////////////
// template belirtirken, typename ya da class belirtmemde bir fark yoktu. Ama bir kullanim var ki
// typename keyword'unu kullanmak mecburi! Ama bu yukaridaki tanimda degil de, metot'un icerisinde.
// Asagidaki ornekte detayli gosteriliyor.

template <class T>
void func_n()
{
    typename T::kdr x; // Yani :: ile bir nested type belirteceksem, typename keyword'unu kullanmaliyim!!
    // Bu kural C++20 ile biraz gevsetildi. Burada, typename kullanabilirken, class kullanmak mumkun degil!
}

//////////////////////////////////////////////////////////////////////////////////////////
class myc1a{
public:
    template <typename T>
    void func(T x);
};

void main_c1a()
{
    myc1a x;
    x.func(1);
    x.func(1.2);
}
// bu sekilde de bir kullanimi mumkundur
//////////////////////////////////////////////////////////////////////////////////////////




int main()
{
    main_b();
    return 0;
}





















































