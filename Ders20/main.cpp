#include <iostream>

// String sinifini inceliyoruz.
// Bu sinifi ogrenmek zorundayiz. String sinifi dilin bircok aracini kullaniyor.
// overloading gibi vb...
// String'i ogrenmemiz, STL'e de giris olacak.
// ODEV icin hatali tarih durumlarinda exception throw edebilirmisiz!!!

// Cpp check

// exception handling
// no except anahtar sozcugunu henuz gormedik!

// No discard attribute --> ileride detayli olarak anlatilacak. Ama odevde kullanmak gerekebilir.
// Geri donus degeri olan fonksiyonlarin geri donus degerini kullanmayaak isek bu idiomu kullanmak gerekir!

// Odevde 9 10 11 12 25 26'nin no discard olmasi lazim kesnlikle.

bool Isprime(int){
    return true;
}

[[nodiscard]] bool IIsprime(int){
    return true;
}

void f_asdfg(){
    int x = 2353;
    Isprime(x); // eger no discard olmazsa warning vermez ama olursa uyari alirim.
    IIsprime(x); // Burada ise warning ile karsilasilir.
}

//============================================================================================================//
// String'lere basliyoruz.
// string en sik kullanilan seylerden birisi.
// Dynamic array sinifidir. Dynamic dizi veri yapisin iyi anlamaliyiz.

// Capacity'i size'den buyuk tutmak gerekir dynamic array'lerde.
// Size capacity'e esit olursa ve yeni bir insertion talebi gelirse artik allocate edilmis bellek blogunda yer olmadigi
// icin arka planda reallocation yapilacak.

// Dynamic bellek kullanirken en dikkat etmemiz gereken yerlerden br tanesi reallocation'dan olabildigince kacinmak.
// Cunku reallocation ciddi bir maliyet iceriyor. Realloc durumunda bazi derleyiciler x2 kullanirken bazilari x1.5 gibi
// bir carpan kullaniyorlar.

// reallocation edildiginde eski bellik alani free ediliyor ve oradaki ogeler yeni alana tasiniyor.
// reallocation zaman alir, pointer ve referanslari invalid&dangling hale getirir.

//============================================================================================================//
// string aslinda bir class template. Yani burada generic bir kod var.
#include <string>
void f_string(){
    using string = std::basic_string<char, std::char_traits<char>,std::allocator<char>>;
    // yani ben string library'sini include ettigimde ve string cagirdigimda yukaridaki template'i cagirmis olurum.
    std::string s1;     // boyle yazmam ile
    std::basic_string<char, std::char_traits<char>,std::allocator<char>> s2;    // yazmam arasinda bir fark yok!

    // string ve wstring cok kullaniliyor. wchar_t acilimidir. wide'in w'su.
    // STL'de container diye bir yapi var. Veri yapilarini temsil eden boyle yapilara container denir.
    // string is an stl container.
    // string sinifi %100 uyumlu stl container'idir.

}
// vector, deque, list, forward_list, array, string                     --> sequential containers
// set, multiset, map_ multimap -->                                     --> assosiative containters
// unordered_set, unordered_multiset, unordered_map, unordered_multimap --> unordered assosiative containters

// operator overloading ve function overloading'ten sonuna kadar faydalaniyor string sinifi.

/*
 a) string sinifi turunden bir nesne
 b) genel olarak bir yazi
 c) ntbs (sonunda null karakter olan bir yazi adresi)
 */

// cstring parametre demek parametrenin const char * olmasi demek.
// Eger sinifin cstring parametreli bir elemani varsa bu su demek, constructor'a bir adres gondereceksiniz, o constructor
// o adresten baslayarak null karakter gorene kadar yazinin butun karakterleri ustunde islemini yapacak. Dolayısıyla
// cstring parametre isteyen bir fonksiyona arguman gectiginizde gectiginiz arguman olan adresteki yazinin sonunda
// null karakter olmasindan siz sorumlusunuz. Null karakter olmazsa UB olur.



void f_str1(){
    char str[199];
    str[0] = 'o';
    str[1] = 'k';
    // Dİzinin sonunda null karakter olmadigi icin bu bir cstring parametre degildir.
    std::string s(str); // Bu UB'dir. Cunku NTBS gecmek zorundayiz.
    // Null terminated byte stream. NTBS
}

// 1. Cstring           === const char *
// 2. data              === const char *, std::size_type n
// 3. range             === [konum1 konum2] --> konum1 dahil konum2 haric aralik belirtir Konum1 konum2'den buyukse UB.
// 4. fill              === std::size_type, char === bu kadar tane bu karakterden
                        // string s(20, 'A');       // 20 tane AAAAAAAAAAAAAA karakter basar bu sekil.
// 5. char              === char    // bizden tek bir karakter istiyor
// 6. substring         === const string&, size_type idk
                        // fonksiyon sizden bir sitring isteyecek bir de tam sayi isteyecek. Ilgili string'in bu idk
                        // indeksinden baslayarak geriye kalan karakterlerin tamami.
// 7. substring         === const string&, size_type idk, string::size_type n
                        // ilgili idk indeksten baslayarak n tane karakter
// 8. string            === const std::string&  -- paramatrenin kendisi referans. const lValue&
// 9. string            === std::string&&  -- paramatrenin kendisi referans. rValue
// initializer_list     === std::initializer_list
                        // initializer_list bir sinif. Bu sinif modern C++ ile dile eklenen bir sinif.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <initializer_list>
void f_initlist(){
    std::initializer_list<int> x{2,5,6,7,3,6};  // initlist sinifi icerisinde 2 tane pointer tutuyor
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f_initlist2(){
    std::initializer_list<int> mylist{1,2,3,4,5,6};
    std::cout << "size : " << mylist.size() << '\n';
    std::cout << "sizeof : " << sizeof(mylist) << '\n';

    auto p = mylist.begin();    // sarmalanan pointerler'dan birincisini cagirmis oluyoruz.
                                         // p'nin degeri const int*

    auto p2 = mylist.end();     // sarmalanan pointerler'dan ikincisini cagirmis oluyoruz.

    for ( auto i : mylist)           // range for baseloop galiba. Ileride cok daha detayli olarak gorecegiz.
    {
        std::cout << i << "\n"; // bu sekilde listedeki tum ogeleri dolasip yazdirmis olurum.
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void finitlist(std::initializer_list<int> x)
{
    std::cout << "x.begin = " << x.begin() << "\n";
    std::cout << "x.end = " << x.end() << "\n";
}

void f_forinitlist(){
    std::initializer_list<int> myliste{1,2,4,6,4,7,3,7};
    finitlist(myliste); // burada fonksiyona tum liste gonderilmedi. Yalnizca 2 tane pointer kopyalandi.
    std::cout << "myliste.begin = " << myliste.begin() << "\n";
    std::cout << "myliste.end = " << myliste.end() << "\n";

    // gorulur ki yukarida yazdirdigim pointerlar ile fonksiyon icerisinde yazdirdigim pointer'larin adresleri
    // aynidir.Shallow Copy

    // *myliste.begin() = 34; // Const bir oge oldugu icin bu hatali bir kullanim.

    auto y = {1,2,3,4,5,6}; // bu sekilde yazmak ile
    std::initializer_list<int> y2{1,2,4,6,4,7,3,7}; // bu sekilde yazmak arasinda bir fark yok.
    // initializer_list'te type_detection olabilmesi icin turlerin hepsinin ayni olmasi gerekiyor Yani
    // auto z = { 1, 2 ,3 ,4 , 5.4 , 6};    // dersek direkt olarak syntax hatasi olur.

    //
    // auto s1 {10,20,30}; // C++11'de bu sekilde kullanim legal idi.
    auto k1 {10};   // k1'in turu int oldu
    auto k3 =  {10};   // k3'in turu initializer list oldu
    auto k2 = {10}; // k2'nin turu initializer list oldu.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MULAKAT SORUSU //// MULAKAT SORUSU //// MULAKAT SORUSU //// MULAKAT SORUSU //// MULAKAT SORUSU //// MULAKAT SORUSU //

class myc1{
public:
    myc1(std::initializer_list<int> x)
    {
        std::cout << "Init List\n";
    }

    myc1(int)
    {
        std::cout << "Int Value\n";
    }
private:
    double m_mean;
};

void f_myc1()
{

    myc1 m1 = {1,2,3,4,5,6};    // Initializer_list constructor'i cagirilir
    myc1 m2{1};                 // Yine Initializer_list constructor'i cagirilir. Burasi onemli
    myc1 m3(15);                    // Burada Int Value olan constructor'a girer.

}
#include <vector>
void f_myc2()
{
    std::vector<int> ivec1(100);    // Burada int constructor calisacagindan size(ivec1) = 100 iken
    std::vector<int> ivec2{100};    // Burada initializer list calisacagindan size(ivec2) = 1 iken

    std::vector<int> ivec3(100,5);    // Burada 100 tane 5 degeri olusturulurken
    std::vector<int> ivec4{100,5};    // Burada 100 ve 5 paramatreli bir initalizer list olusturuluyor.
    // bu durumlarin hepsi string siniflari icin de gecerli.
}

// MULAKAT SORUSU //// MULAKAT SORUSU //// MULAKAT SORUSU //// MULAKAT SORUSU //// MULAKAT SORUSU //// MULAKAT SORUSU //

// small size optimization: string sinifi icerisinde belli bir buffer tutar. String degeri belli bir uzunluğu asarsa
// bellekte alan allocate eder ama belli bir degerin altindaysa buffer'da kullanir.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {
    f_myc1();
//    std::cout   << std::endl;
    return 0;
}
