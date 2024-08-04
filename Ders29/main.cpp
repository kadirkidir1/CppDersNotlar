#include <iostream>
#include <string>
#include <random>

#include <exception>      
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////
// try-func bloğu diye bir şey var.
void func_000()
try {

} catch (const std::exception& ex) {

}
// yukarida temel kullanimi gorulur. Yani fonksiyonun koseli parantzleri
// icerisinde try-catch yok. Olsaydi da bu asamada bir fark olmazdi. Ama kullanimini
// onemli kilan bir yer var. O da, constructor!!!
/////////////////////////////////////////////////////////////////////////////

class nai0 {
public:
    nai0(int x) : mx{x}
    {
        if(mx %2 == 0) {
            std::cout << "cift sayi hatasi!!";
            throw std::invalid_argument{"hayirli sabahlar!!!"};
        }
    }
private:
    int mx;

};

class nai1 {
public:
    nai1() = default;

//    nai1(int x) : nx{x}
//    {
//        try {

//        } catch (const std::exception& ex) {
//            std::cout << ex.what()<<"\n";
//        }
//    } // bu sekilde calistirilirsa, constructor icerisinde try catch yakalanamaz.

    nai1(int x) try : nx{x}
    {

    } catch (...) {
        std::cout << " exception yakalandi \n";
    }
 ///////////////////////////////////////////////////////////////////////////////////

private:
    nai0 nx{1};
};

///////////////////////////////////////////////////////////////////////////////////
// exeption ptr? -- nullable ptr sinifinda
// Concurency konusunda geri dönecek
std::exception_ptr gptr{nullptr}; // globalde tanimladik.
void func_0() {
    try {
        throw std::runtime_error{"error in func\n"};
    } catch (...) {
        // exeption ptr bir nevi akilli pointer nesnesi gibi
        // bir exeption yakaladiginizca current_exeption'i cagirirsaniz bu fonksiyon
        // exeption'i sarmalayan bir exeption ptr donduruyor.
        gptr = std::current_exception();
    }
}

void main_0()
{
    func_0();
    //
    if(gptr) {
        std::rethrow_exception(gptr);
        // Bunun asil amaci farkli thread'lerde olmasi. Ileride detayli gorecegiz.
    }
}
///////////////////////////////////////////////////////////////////////////////////
// Private Inheritance
///////////////////////////////////////////////////////////////////////////////////
// public private ya da protected kalitim ne demek?
//

class c1 {
public:
    void foo_public();
protected:
    void foo_protected();

};

class d1 : public c1 {
public:
    void foo() {
        foo_protected();  // Burada bunu kullanabilirim. Cunku ayni class'imin protected'ina eklendi.
    }
};

void main_1()
{
    d1 my_d1;
    my_d1.foo_public(); // foo_public'i kullanabiliyorum lakin
//    my_d1.foo_protected(); // Bunu kullanmam sentax hatasi
}

///////////////////////////////////////////////////////////////////////////////////
// Public KALITIMI
// Taban sinif                  Turemis Sinif
// Public                       Public
// protected                    Protected
// Private                      YOK


// Private KALITIMI
// Taban sinif                  Turemis Sinif
// Public                       Private
// protected                    Protected
// Private                      YOK

class c2  {
public:
    void foo_public();
};

class d2 : private c2 {
public:
    void f() {
        // c2 class'inin public metotlari burada private olacak.
        // yani class icerisinde kullanabilirim, classlarda bildigimiz
        // private public mantigina donuyor
        foo_public();
    }
};

void main_2()
{
    d2 my_d2;
//    my_d2.foo_public(); // Yorum satiri kaldirilirsa hata alinacagi gorulur
}
///////////////////////////////////////////////////////////////////////////////////
///

class c3 {

};

class d3 : public c3 {

};

class d4  : private c3 {

};

void main_3() {
    d3 my_d3;

    c3* c3ptr = &my_d3;
    c3& c3ref = my_d3;
    // Goruldugu gibi public kalitimda yukaridaki gibi kullanabilirim.

    d4 my_d4;
//    c3* c3ptr2  = &my_d4; // Yorum satiri kaldirilirsa hata alinacagi gorulur


}

///
///////////////////////////////////////////////////////////////////////////////////
// Private kalitimda
// 1. turemis sinif nesnesi icinde taban sinif nesnesi var
// 2. turemis sinifin implementasyonu taban sinifin public ve taban sinifin proteted
// islevlerini kullanabilir
// 3. Taban sinifin private bolumune erisemiyoruz
// Taban sinifin public ve protected ogeleri turemis sinifin private bolumune ekleniyor
// Turemis sinifin client'leri taban sinifin public ogelerini gormeyecekler

// private inheritance buyuk cogunlukla containment yoluyla composition'a bir alternatif
// Bu nedemek!!!

///////////////////////////////////////////////////////////////////////////////////

class A {
public:
    void f1();
    void f2();
    virtual void vfunc(); // Ikisi arasinda olay burada basliyor
};

class Nec1{
public:
    void f1(){
        ax.f1();
    }

    void f2(){
        ax.f2();
    }
private:
    A ax;
};

class Nec2 :private A{
public:
    using A::f1;
    using A::f2;

    // Nec1 class'inda virtual func'i override etmem mumkun degilken(su anlik)
    // inheritance sayesinde bunu Nec2 class'inda yapabilirim.

    void vfunc()override;

};

// Yukarida iki class'ta da A nesnesi kullanilmis oluyor
// Yani iki turde de, A class'inin public interface'ine ulasamam.
// Ortak noktalara bakarsak, ikisinde de is a relationship yok!

// Fark ise taban sinifin sanal fonksiyonlarini override edebiliyoruz.
// Diger fark ise taban sinifin protected kismina Nec1 ulamasaz ama,
// private inheritance'de taban sinifin protected fonksiyonlarini cagirabiliriz.

// Bir digeri ise turemis sinifin uye fonksiyonlarda ve turemis sinifin friend'lik verdigi
// fonksiyonlarda is a relationship soz konusu

// Private inheritance'nin kullanildigi onemli bir alan daha var, C++20'de dilden cikti
// ama onemli -- EBO end the base optimization
// Ne demek?
// Bazi class'lar empty class. Interfacesi var ama veri ogesi yok.

class Empty {
public:
    void f1();
    void f2();
    void f3();
};

class Kdr {
private:
    Empty m_empty; // Bu class'in boyutu 1 byte.
};

class Kdr_0 {
private:
    int a;         // bunu da ekledigim zaman
    Empty m_empty; // Bu class'in boyutu 8 byte. Padding alignment'tan dolayi! Yani durduk yere
                   // Boyut artmis oluyor.
};

class Kdr_1 : private Empty {
private:
    int a;         // Su an yukaridaki class'la ayni durumda olmama ragmen, class boyutu 4 byte oldu!
};

// Empty class'larin hicbir storage ihtiyaci olmasa da o class'in boyutu 1 byte'dir.
// Cogunlukla empty class'a sahip class'larin baska elemanlari da oluyor.

// C++20'de attribute ekleniyor ve alignment durumunu ortadan kaldiriyor.

class Kdr_2 {
private:
    int a;
    [[no_unique_address]]Empty m_empty; // Bu sekilde kullanirsam boyut 4 byte olur. Ama c++20 ile
                                        // dile eklendigi unutulmamali!!

};
///////////////////////////////////////////////////////////////////////////////////
// Protected Kalitimda neredeyse her sey ayni ama tek fark, protected oldugunda
// taban sinifin public bolumu ve protected bolumu turemis sinifin protected bolumune
// ekleniyor.

class Base {
public:
    void basefunc();
};

class Der : private Base {

};

class sDer : public Der {
    void foo()
    {
//        basefunc();// su an bunu cagiramaz. Cunku base class'in public'i
                     // Der class'inin private'ina dahil oldu.
    }
};

class Der2 : protected Base {

};

class sDer2 : public Der2 {
    void foo()
    {
                basefunc();// su an bunu cagirabilir.
    }
};
//

///////////////////////////////////////////////////////////////////////////////////

class apple {
public:
    void func1(int);
    void func1(int,int);
    void func1(double);
};

class iphone7 : private apple {
public:
    using apple::func1;
};

void main_5()
{
    iphone7 m_iphone7;
    m_iphone7.func1(7); // Using bildirimi olmazsa bu hatali olur.
                        // yukarida inheritance alan class'ta using bildirimi kaldirilip
                        // denenebilir.
}

///////////////////////////////////////////////////////////////////////////////////
/// Private inheritance'nin kullaniminin bir onemli alani daha var.
/// Restricted Polymorphism

class color{
public:
    virtual void vfunc();
    virtual void vfoo();
};


class black : private color {
public:
    friend void red1();
    virtual void vfunc()override;
    virtual void vfoo()override;
};

void gfoo(color& colorref)
{
    colorref.vfoo();
}

void red1()
{
    black m_black;
    gfoo(m_black); // Yukarida friendlik bildirimi vermezsem hata olacakti!!!
}

void red2()
{
    black m_black;
//    gfoo(m_black); // Yorum satiri kaldirilirsa hata oldugu gozukecektir!!!
}

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

// Template parameters: <> isaretlerinin arasina gelen sey
// 1. type parameters olabilir.
// 2. non-type parameter olabilir.
// 3. template parameter olabilir.

/// template <class T> --> burada anlam class anlaminda degil. Herhangi bir tur anlaminda. int double kullanilabilir.
/// template <typename T>
/// Gunumuzde yukaridaki ikisini kullanmak acisindan bir fark yok. Ikisi ayni anlamda.

int main()
{
    nai1 n(12);
    return 0;
}

 
