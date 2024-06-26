#include <iostream>
#include <string>
#include <random>

#include "Car.h"
#include <exception>      
#include <stdlib.h>

// std::exception, std::terminate
//Bu derste cok onemli olan exeption handling'ten bahsedilecek.
// Her C++ programcisinin hakim olmasi gereken cok muhim bir konudur kendileri.

// 1. run time'da isini yapmasi gereken bir kod isini yapamiyor cunku kodu yanlis yazilmis. boyle hatalara programlama hatasi deniyor
// genel olarak.
// Assertions. Runtime assertion ve static assertions'lar var. Kodlama hatasini bulmaya yonelik kurallar.

// 2. bir fonksiyonun isinin beklenmeyen bir sekilde yapamadiginda ne yapilabilecegiyle ilgili. Yani exeption. Turkcesi "istisna" demek. 

// Geleneksel hata isleme teknikleri! C'de var ama C++'ta istemiyoruz.
// fonksiyonun geri donus degerini alip buna gore hata degerlendirmesi yapmak. 

// ortada ne kadar if varsa kodu test etme imkani o kadar zor olur
// ortada ne kadar if varsa kodda hata yapilma ihtimali o kadar artar.

// Cok cok kisa surede tepki vermesi isenen durumlarda exception handling islemleri vakit aldigi icin kullanilamamakta. Bu gibi durumlarda 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ctor'larin hayata gecirilmesi Exeption'larin kullaniminda cok onemlidir.
//  Demekki class olustururken try-catch'leri kullanmak onemli.
// !!!!! Mudahale etmeyeceginiz bir exception'i yakalamaya calismayin.

// 3 onemli keywoard vardir. Throw, try ve catch
// exception throw etmek ne demek. fonksiyon isini yapamadiginda bir nesnse olusturuyor bu nesnenin varlik nedeni
// daha ust katmandaki kodlara fonksiyonun isini yapamadigini anlatmak olan bir nesne
// fonksiyonumuz bu nesneyi yukariya firlatiyor. Kim mudahale etmek isterse bu nesneyi yakalasin ve mudahale etsin.
// ex. throw etmek için ex. object gerekiyor.

// throw ile bir "throw statement" olusturuyor.
// eger hatayi hicbir kod yakalamazsa buna "uncaught exception" deniyor.

 // corotine --> C++20 ile dile eklenen, dilin neredeyse en karisik arac setlerinden bir tanesidir.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f4()
{
    std::cout << "f4 cagirildi \n";
    throw;
    std::cout << "f4'ten cikiliyor \n";
}

void f3()
{
    std::cout << "f3 cagirildi \n";
    f4();
    std::cout << "f3'ten cikiliyor \n";
}
void f2()
{
    std::cout << "f2 cagirildi \n";
    f3();
    std::cout << "f2'ten cikiliyor \n";
}
void f1()
{
    std::cout << "f1 cagirildi \n";
    f2();
    std::cout << "f1'ten cikiliyor \n";
}

void kdrfunc_1()
{
    std::cout << "kdrfunc_1 fonksiyonuna geldi \n";
    std::exit(EXIT_FAILURE);
}

void fmain_1()
{
    std::set_terminate(&kdrfunc_1);
    std::cout << "fmain_1 cagirildi \n";
    f1();
    std::cout << "fmain_1'den cikiliyor \n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f8()
{
    std::cout << "f8 cagirildi \n";
    throw 1.2f;
    std::cout << "f8'ten cikiliyor \n";
}

void f7()
{
    std::cout << "f7 cagirildi \n";
    f8();
    std::cout << "f7'ten cikiliyor \n";
}
void f6()
{
    std::cout << "f6 cagirildi \n";
    f7();
    std::cout << "f6'ten cikiliyor \n";
}
void f5()
{
    std::cout << "f5 cagirildi \n";
    f6();
    std::cout << "f5'ten cikiliyor \n";
}

void fmain_2()
{
    std::cout << "fmain_2 cagirildi \n";
    try{
        f5();
    }catch(int){
        std::cout << "int catch bloguna giris yapiliyor \n";
    }
    catch(double){
        std::cout << "double catch bloguna giris yapiliyor \n";
    }
    catch(float){
        std::cout << "float catch bloguna giris yapiliyor \n";
    }

    std::cout << "fmain_2'den cikiliyor \n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class c_kdr1a{

};

class c_kdr1b : public c_kdr1a
{

};

void f9()
{
    std::cout << "f9 fonksiyonu cagirildi\n";
    throw c_kdr1b{};    // gecici nesne olusturdum!
}

void fmain_3()
{
    std::cout << "fmain_3 cagirildi \n";
    try{
        f9();
    }catch(const c_kdr1b&){
        std::cout << "const c_kdr1b& catch bloguna giris yapiliyor  \n";
    }
        // bu ornekte bir nesne yakalanmistir. Ama burada asil olay, derivative class yakalandigi gibi burada base class da yakalanabilir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fmain_4()
{
    std::cout << "fmain_4 cagirildi \n";
    try{
        f9();
    }catch(const c_kdr1a&){
        std::cout << "const c_kdr1a& yakalaniyor, throw edilen der class olmasina ragmen base class  yakalaniyor  \n";
    }
        // bu ornekte bir nesne yakalanmistir. Ama burada asil olay, derivative class yakalandigi gibi burada base class da yakalanabilir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Herhangi bir class gonderebilecegimiz gibi burada std::exception class'ini da kullanabiliriz. Bu class bize bir takim seyleri garanti
// etmistir
// her zaman catch parametrelerini referans yapiyoruz. Ve eger bir sey degistirmeyeceksek const'a dikkat edelim. Seyrek karsimiza cikar
// degistirmek.

void f10()
{
    std::string str("kadir kidirov");

    std::size_t idx = 456;
    str.at(idx);    // 'std::out_of_range' hatasi gelecek!
    std::cout << " bu yazi gorulmeyecek \n";
}

void fmain_5a()
{
    try 
    {
        f10();
    }catch(const std::out_of_range& ex){    // out_of_range sinifi kullanildi cunku bu da exception class'inin inheritlerinden bir denesi.
        std::cout <<"Basim donuyor "<< ex.what()<< "\n";
    }
}

void fmain_5b()
{
    try
    {
        f10();
    }catch(const std::logic_error& ex){    // logic_error sinifi kullanildi cunku bu da exception class'inin inheritlerinden bir denesi.
        std::cout <<"Basim donuyor "<< ex.what()<< "\n";
    }
}

void fmain_5()
{
    try
    {
        f10();
    }catch(const std::exception& ex){
        std::cout <<"Basim donuyor "<< ex.what()<< "\n";
    }
}

void fmain_6()
{
    try
    {
        f10();
    }
    catch(const std::out_of_range& ex){
        std::cout <<" "<< ex.what()<< "\n";
    }
    catch(const std::logic_error& ex){
        std::cout <<" "<< ex.what()<< "\n";
    }
    catch(const std::exception& ex){
        std::cout <<" "<< ex.what()<< "\n";
    }
    // Eger coklu kullanim yapilacaksa bu sekilde yapilmalidir cunku exception <-- logic_error <-- out_of_range seklinde inherit edilmistir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// throw exp. lvalue olabilir.
// exception safety cok onemli bir durum. Yapilan islemlerde memory leakage olmayacagi garanti altina alinmalidir.
// exception'i yakaladiktan sonra baska bir exception gondermeye exception translate deniyor. Yapilan bir islem.

// exception'in rethrow edilmesi. gelecek dersin konusu

/*
    try
    {
        
    }
    catch(const std::exception& e)
    {
        throw; // goruldugu gibi buna rethrow deniyor. Daha ust katmanlara gonderebilmek icin yapiliyor.  
    }
*/

//
// * BURADAN USTTEKILER DERS 27 iken buradan sonraki kısım ders28 olacaktır.
// * Exception konusu bölünmemesi için bu şekilde yaptım.
// *

void func()
{
    try
    {
        throw std::out_of_range("range hatasi");
    }
    catch (const std::exception& ex)
    {
        std::cout << "Hata func içinde yakalandı: " << ex.what() << "\n";

        // İki farklı throw statement arasındaki farkı görünüz.
         throw ex;
//        throw;
    }
}

int main_7()
{

    try
    {
        func();
    }
    catch (const std::out_of_range&)
    {
        std::cout << "Hata yakalandı (std::out_of_range)\n";
    }
    catch (const std::exception&)
    {
        std::cout << "Hata yakalandı (std::exception)\n";
    }

    return 0;
}

// burada su anlatilmak isteniyor. direkt olarak throw edersek, mecvut yakalanmis olan exception'i
// throw etmis olacagiz ve bu sebepten oturu out_of_range yakalanmis olacak. Ama bunu yapmazsak, throw ex; seklinde
// yeni bir nesne olusturursak, burada bu sefer, out_of_range exception'ı kaybedilmis olacagindan, exception block'una
// dusecektir.


class NecEx
{
public:
    NecEx() = default;

    NecEx(const NecEx&)
    {
        std::cout << "copy ctor\n";
    }
};

void func_2()
{
    try
    {
        throw NecEx{};
    }
    catch (const NecEx& ex)
    {
        std::cout << "hata func icinde yakalandiii\n";
        throw ex;
    }

    // Eger burada ex'ler kaldirilirsa, copy ctor'a girmedigi gorulur.
    // yani burada asil olay, rethrow etmek ya da etmemek.
}

int main_8()
{
    try
    {
        func_2();
    }
    catch (const NecEx& ex)
    {
        std::cout << "hata main icinde yakalandi\n";
    }

    return 0;
}

//-----------------------------------------------------------------------------//

// rethrow statement'in yalnizca catch blogu icerisinde olmasi gerekmiyor.

void foo() {
    std::cout << "foo cagirildi\n";
    throw;
}

void func_3() {
    try {
        throw std::runtime_error{"kadir kidirov"};
    } catch (const std::exception& ex) {
        foo();
    }
}

void main_9() {
    try {
        func_3();
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }
}

//----------------------------------------------------------------------------//

//exception dispatcher
//önemli bir exception idiyomu
// yani bircok yerde bunlari yazmaktansa, ayni metot ile birden fazla yerde
// handle exception yapabilirim



class NecException {

};

class ErgException {

};

class CSDException {

};

void handle_exception()
{
    try {
        throw;
    }
    catch (NecException& e) {

    }
    catch (ErgException e) {

    }
    catch (CSDException e) {

    }
}

void func_4() {
    try {

    } catch (...) { // boyle uc noktali olunca catch all deniyor.
        handle_exception();
    }
}

// yukarida bir exception idiomu vardir.

//-----------------------------------------------------------------------------//

// Exception class'larinin copy ctor ya da move ctor'lari exception throw etmemeli.

//-----------------------------------------------------------------------------//

struct A {
    A() {
        std::cout << " A Ctor\n";
    }

    ~A() {
        std::cout << " A dtor\n";
    }
};

struct B {
    B() {
        std::cout << " B Ctor\n";
    }

    ~B() {
        std::cout << " B dtor\n";
    }
};

struct C {
    C() {
        std::cout << " C Ctor\n";
    }

    ~C() {
        std::cout << " C dtor\n";
    }
};

void baz() {
    std::cout << "baz cagrildi\n";
    C cx;

    throw std::runtime_error{"kadir kidirov1"};
    std::cout << "baz sona erdi\n";
}

void bar() {
    std::cout << "bar cagrildi\n";
    B bx;
    baz();
    std::cout << "bar sona erdi\n";
}

void foo_4() {
    std::cout << "foo cagrildi\n";
    A ax;
    bar();
    std::cout << "foo sona erdi\n";
}

void main_10() {
    try {
        foo_4();
    } catch (const std::exception& ex) {
        (void)getchar();
        std::cout << ex.what() << "\n";
    }
}

// Burada anlatilmak istenen, otomatik omurlu nesnelerde hata yakalandiginda,
// otomatik omurlu nesnelerin destructor'lari cagirilarak, memory geri verilir.
// buna stack unwinding deniyor.

//---------------------------------------------------------------------------------//

// Garanti seviyeleri

// No guarantee --> exeption gonderilirse basimiza her sey gelebilir
// Basic guarantee --> Bunu anlamak cok onemli. Kabul edilebilir minimal garanti anlaminda.
//                     Eger calisma sirasinda herhangi bir throw olursa, hicbir  kaynak sizdirilmayacak
//                     Bu garanti turune no-leak guarantee de deniyor.


// Strong Guarantee(commit & rollback guarentee) --> exception'la cikildiginda kaynak sizdirilmadigi
//                    gibi, state'inde de bir degisiklik olmayacak. Nesne ya da nesneler, o operasyona
//                    baslamadan onceki durumunu koruyacak. Yani ya isleme devam edecek, edemiyorsa da
//                    exception'dan onceki adima geri donecek. Basic guarantee'de bu yok iste.

// No Throw Guarantee

#include <memory>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Message{

public:
    std::string to_string ()const
    {
        // Throw edebilir ya da etmeyebilir
        return "asdasd";
    }
};

void log(const std::vector<Message>& mvec) {
    std::ofstream log_file;
    log_file.open("log.txt", std::ios_base::app);

    std::string result;

    for (const auto& m : mvec)
        result += m.to_string();

    log_file << result;
}

// Simdi yukaridaki koda bakarsak, vector'den mesajlar alinip result adli string'e
// to_string metodundan donduktan sonra isleniyor. Ama herhangi bir anda, ornegin 5. nesnede
// to_string metodu throw ederse, for'dan cikacak. Result degeri de bos olacak kaynak geri
// verilerecek, ve bu sebepten oturu log_file dosyasina herhangi bir sey yazilmayacak. Iste
// bu strong garanti. Hem memory leak&resource leak yok, hem de dosya, baslangictaki ayni
// state'ine dondu. Strong garanti, ya hep ya hic yasasini benimser. Ama bu sekilde degil de
// asagidaki gibi olsaydi,

    void log_2(const std::vector<Message>& mvec) {
    std::ofstream log_file;
    log_file.open("log.txt", std::ios_base::app);
    
    for (const auto& m : mvec)
        log_file << m.to_string();
}

// log_2 metodunda, herhangi bir throw esnasinda log.txt yine kapanacakti, herhangi bir leak
// meydana gelmeyecekti ama!! ornegin 5. nesneye kadar yazilanlar, dosyaya kaydedilmis olacakti.
// yani baslangictaki durumuna donmeyecekti. Iste bu basic guarantee.

// En son garanti turu ise No Throw Guarantee.

// Destructor'lar no throw garanti vermelidir.
// swap fonksiyonları no throw garanti eder.
// move members(ozellikler move constructor)
// operator delete fonksiyonu gibi kaynak iade eden fonksiyonlar.
// cleanup fonksiyonları


// Asagida modern c++ oncesi anlatilacaktir. Cok dikkate alinmamali, dilden kaldirildi.

void func_t(); // herhangi bir exception throw edebilir.
// void func_t1()throw(std::bad_alloc, std::runtime_error); // hata verdi zaten. C++17 bunu desteklemez diye.
                                                         // Ama kisaca olay su, yalnizca parantez icindeki
                                                         // ex'leri throw edebiliriz.

void func_t2()throw();// Eger ici bos ise, bu da exeption throw etmeme garantisidir.

// NoExcept --> dile eklendikten

///////////////////////////////////////////////////////////////////////////////////
// Modern C++'ta eger NoExcept operator kullaniliyorsa, (dikkat edilirse NoExcept specifier
// degil, NoExceptOperator), bunun anlami herhangi bir exception throw etmeyecek demektir.

 // NoExcept, bildirimde de tanimda da yer almasi gerekiyor!!!
// Yani header'da NoExcept bildirip, Cpp içerisinde bildirmemek olmaz!!!

//// kdr.h
//void knur()noexcept;
//// kdr.cpp
//void knur()noexcept() {

//}
// Bu sekilde olmasi gerekiyor. Direkt olarak, syntax hatasi olur.
// Metot'lardan birisi noexcept ama digeri degil --> Bu sekilde overload edemeyiz.

void funcnur()noexcept;
void funcnur()noexcept(true);
// Yukaridaki iki metot arasinda hicbir fark yok.

void funckdr()noexcept(false);
void funckdr();
// Yukaridaki iki metot arasinda da hicbir fark yok.
//

// Bir fonksiyona noexcept garantisi verdigim halde eger throw ediyorsa,
// bu compile time'da kontrol edilmedigi icin, set_terminate metot'una gidecektir.

void func_072()noexcept{

}

void main_11() {
    try {
        func_072();
    } catch (const std::exception& ex) {
        std::cout << "buraya hic girmeyecek, cunku func_072 noexcept garanti verdi";
        // set_terminate metotuna gidecek!!!
    }
}

//////////////////////////////////////////////////////////////////////////////////////

// special member function'lar noexcept kabul ediliyor. Bu dilin kurali!!!
// destructor kesinlikle noexcept kabul ediliyor ama digerlerinde anladigim
// kadariyla bazen degisebiliyor.

//////////////////////////////////////////////////////////////////////////////////////

// noexcept olup olmadigini compile time'da anlayabildigimiz durumlar var. Bunu ileride
// detayli gorecegimiz type_traits sagliyor!!

#include <type_traits>

class MyClass_000{

};

void main_12() {
    const auto b = is_nothrow_default_constructible_v<MyClass_000>;
    std::cout << "b'nin durumu: " << b << "\n"; // bu sekilde yazdirilirsa, 1 gorulur.
}

//////////////////////////////////////////////////////////////////////////////////////
// Noexcept hayati onem tasiyan bir sey. Cunku STL'lere geldigimizde, derleyicinin
// kod secerek, optimizasyon yapmasini sagliyor.
/// //////////////////////////////////////////////////////////////////////////////////////

#include <vector>

class Sentence {
public:
    Sentence() = default;
    Sentence(const char* ps) : m_s{ ps } {}
    Sentence(const Sentence& other) : m_s{ other.m_s }
    {
        std::cout << "copy ctor\n";
    }
    Sentence(Sentence&& other)
//    Sentence(Sentence&& other)noexcept
        : m_s{ std::move(other.m_s) }
    {
        std::cout << "move ctor\n";
    }

private:
    std::string m_s;
};

void main_13()
{
    std::vector<Sentence> svec{
                               "Consuetudinis magna vis est",
                               "Homines quod volunt credunt",
                               "Hostium munera, non munera" };

    std::cout << "svec.size() = " << svec.size() << "\n";
    std::cout << "svec.capacity() = " << svec.capacity() << "\n";

//    svec.resize(svec.capacity() + 1);
    svec.push_back("Factis ut credam facis");
}

// Yukaridaki durum necatiergin'in github sayfasindan alindi. Kod incelendiginde
// su durum ortaya cikiyor. Eger moveCtor noExcept degilse, pushback fonksiyonu
// strong garanti verdigi icin, copyCtor'u cagirir. Bu da fazla maliyet demek!
// Eger moveCtor noexcept ise, movector'u otomatik olarak cagirarak optimizasyon
// yapmis olur. Yani noexcept oyle yamana atilacak bir konu degildir!!!

/////////////////////////////////////////////////////////////////////////////////////////
// Yukarida hep noexcept specifier anlatildi. Simdi noexcept operator anlatilacak.

class nai{
public:
    nai() = default;
    void nai_000();
    void nai_001()noexcept;
};

void main_14(){
    nai Nai;

    const auto b = noexcept(Nai.nai_000()); // incelenirse b'nin degerinin false oldugu gorulur.
    const auto b1 = noexcept(Nai.nai_001()); // incelenirse b'nin degerinin true oldugu gorulur.
    const auto b2 = noexcept(nai{}); // default Ctor'un noexcept garanti oldugu gorulur. Ama ctor'u biz yazsaydik,
                                     // ve noexcept garanti belirtmeseydik, bu sefer false olacaktı.


}

///////////////////////////////////////////////////////////////////////////////////////////
// unevaluated context --> sonucun degerlendirilmedigi ve etki etmedigi durumlari ifade eder.
// sizeof, decltype ve noexcept operator, unevaluated context sınıfındadır.

void main_15(){
    int x = 15;

    constexpr auto b = noexcept(x+20);
    std::cout << x << "\n";

    std::cout << sizeof(x++) <<"\n";
    std::cout << x << "\n";

    decltype(x++) a;
    std::cout << x <<"\n";
}

///////////////////////////////////////////////////////////////////////////////////////////

class nai_001 {
};

void naif_000(const nai_001& r) noexcept(noexcept(nai_001{}));
// Yukaridaki parantez içindeki noexcept, operator olur. Default ctor oldugundan, true gelir.
// yani void naif_000(const nai_001& r) noexcept(true)); --> bununla aynıdır.

///////////////////////////////////////////////////////////////////////////////////////////


int foo(int); // --> Noexcept garantisi yok!!!

void naif_001()
{
    int (*fp)(int)noexcept; // Bu fonksiyon, noexcept garantisi veren bir fonksiyonu gösterecek.
//    fp = &foo; // Yorum satiri kaldirilirsa gorulecektir ki, foo fonksiyonu noexcept garantisi
    // vermedigi icini, hata vardir.
}

///////////////////////////////////////////////////////////////////////////////////////////

class nai_002 {
public:
    virtual void naif_002()noexcept;
};

class nai_003 : public nai_002 {
public:
//    void naif_002()override; // yorum satırı kaldırırlırsa hata gorulur.
    // kalitim yoluyla alinan metotun  except garantisi çiğnenmiş oluyor çünkü!!!
    void naif_002()noexcept override; // bu sekilde yapilirsa, hata olmadigi gorulur.
};

///////////////////////////////////////////////////////////////////////////////////////////
// Destructor --> destructor nothrow garantisi vermek ZORUNDA.
// Destructor ya hiç exception throw etmeyecek, edecekse de kendi içerisinde yakalayacak!!!

// Constructor --> Exception gondermeye en fazla aday olan fonksiyon ne diye sorsaniz
// cevap kesinlikle constructor'dır.

///////////////////////////////////////////////////////////////////////////////////////////

class nai_004 {
public:
    nai_004() {
        throw 1;
    }

    ~nai_004() {

    }

    unsigned char nai_uc[1024]{};
};

void main_16()
{
    nai_004* nainai = new nai_004;

    // burada constructor exception throw etse bile, unstack unwinding devreye girer ve,
    // kaynaklar geri verilir. Bu açıdan bir sıkıntı yok.
}

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    main_15();
    return 0;
}

 
