#include <iostream>
#include <string>
#include <random>

#include "Car.h"

 class base1{
 public:
    virtual ~base1() = default;
    void func(int);
    void func(char);
    void func(long);
 };

 class der1 : public base1{
    public:
    using base1::func;
    void func(int,int);
 };

 // yukaridaki durumda, using bildirimi ile func fonksiyonu der class'ta bildirildigi icin, bu durum overload gibi davranir.
 // fakat imza tamamen ayniysa, der'in func fonksiyonu cagirilir!!! Ambiguity yok!!! Bu garanti altinda. 

/********************************************************************************************************************************/
/********************************************************************************************************************************/
// Inherited Constructor --> using bildiriminin daha once olmayan bicimde constructor'a uygulanmasi.
// son derece pratik ve bazi yerlerde son derece onemli bir syntax.
// ozellikle generic programlamada!


// Taban sinifin constructor'lari der class icin direkt gorulebilir degil! 
class base2{
public:
    base2() = default;
    base2(int,int);    
};

class der2 : public base2{
    public:

};
 
void f1()
{
    der2 a; // bu sekilde cagri yapabilirim cunku base class'in def ctor'u mevcut.
    // der2 a(2,3);    // bu sekilde cagri yapamam, base class'in ctor'unda bu sekilde parametreli ctor olsa da der class'ta yok!!! Hata veriyor.
}

// inherited ctor dile modern c++ ile eklenmistir.

/********************************************************************************************************************************/
/********************************************************************************************************************************/
// Yukaridaki sorunu asmanin yollarindan birisi asagida!

class base3{
public:
    base3() = default;
    base3(int){}
    base3(int,int){}
};

class der3 : public base3{
    public:
        der3(int x) : base3(x) {}
};
 
void f2()
{
    der3 a(5); // goruldugu uzre bu sekilde cagri yapabiliyorum. 
}

// ama bunun bir yolu daha ver, ve kesinlikle daha kolay. ASAGIDA

/********************************************************************************************************************************/
/********************************************************************************************************************************/
// Yukaridaki sorunu asmanin yollarindan birisi asagida!

class base4{
public:
    base4() = default;
    base4(int)
    {}
    base4(int,int){}
};

class der4 : public base4{
    public:
       using base4::base4;  // bu sekilde kullanim ile base class'in tum constructor'larina erisebilmek mumkun. 
};
 
void f3()
{
    der4 myder4(23); // Der class'in boyle bir ctor olmamasina ragmen bu sekilde bildirim ile kolaylik saglanmis.  
}

// Inherited constructor icin base class'in ctor'larinin public tarafta olmasi gerekmekte. Normalde using bildirimi 
// protected siniftaki fonksiyonlari kullanmamiza olanak saglasa da, using base::base; kullanimi icin public tarafta olma sarti var!.

/********************************************************************************************************************************/
/********************************************************************************************************************************/
// Ek bilgi : Kalitim yerine compesition kullanabiliyorsaniz, compesition cok daha iyi bir secenek! 
// final -- contextial keywoard.
// final class/ final override nedir?
// bazi durumlarda 
    // a) bir sinifin kalitim yoluyla kullanilmasini istemiyorsunuzdur
    // b) bu sinif kalitilmak icin olusturulmadi, bu sinifin kalitilmasini onermiyorum demek icin final keywoard'unu kullanabiliriz!

class kdr1 final{ 

};

// class kdr2 : public kdr1{ }; // yorum satirlari kaldirilirsa hata gorulur. Burada hatanin sebebi kdr1 class'inin  
 
/********************************************************************************************************************************/
/********************************************************************************************************************************/
class base5{};

class der5 final : public base5 {};

// class der51 : public der5{};    // yorum kaldirilirsa burada da final'den dolayi sorun oldugu gorulecektir. 

/********************************************************************************************************************************/
/********************************************************************************************************************************/
// final class baska, final override baska.
class ovFinal1{
    public:
        virtual void foo()
        {
            
        }

        virtual void foon()final
        {

        }
};

class ovFinal2 : public ovFinal1
{
    public:
        void foo()override final
        {

        }

        // void foon()override {} // yorum kaldirilirsa gorulecek ki base class'taki foon fonksiyonu final keywoard'u ile 
                                  // tanimlandigi icin bu fonksiyon override edilemez.

};

class ovFinal3 : public ovFinal2
{
    public:
    // void foo()override{}       // yorum kaldirilirsa gorulecek ki base class'taki foon fonksiyonu final keywoard'u ile 
                                  // tanimlandigi icin bu fonksiyon override edilemez.
};

/********************************************************************************************************************************/
/********************************************************************************************************************************/
// En az bir pure virtual function'i olan class'lara abstract class deniyor. Abstract class'lar ile nesne olusturulamaz.
// Abstract olmayan siniflar concrete siniflar. Concrete class'lar ile nesne olusturulabilir!!!
// Ama abstract class'lar referans ya da pointer vasitasiyla kullanilabiliyorlar. 

// C++'in thread library'i modern c++ ile dile eklendi. Bu sayede internal edilen pthread gibi library'lerin kullanimina gerek kalmadi.
// global fonksiyonlar virtual olamaz! parametrik yapisinin ne oldugundan bagimsiz

// virtual void f_global_func();    // dogrudan bu bir hatadir. Yorum satiri kaldirilirsa gorulebilir.

/********************************************************************************************************************************/
/********************************************************************************************************************************/
// Hoca interesting bir sey yapiyor. tekrar'dan car sinifina donuyor. Oraya operator overload ile ilgili bir seyler ekleyip, car
// sinifina da printf fonksiyonu gibi bir seyler yaziyor. Farkli yapilar da kullaniyor fakat yalnizca ilerisi icin hazirlik olsun diye
// her seyi cok detayli islemiyor.
#include <thread>
#include <chrono>
std::ostream& operator<<(std::ostream& os, const car4& other);
void f_interesting()
{
    using namespace std::literals;

    for (int i = 0; i < 100; i++)
    {
        car4* cp = create_random_car3();
        std::cout << *cp;   // Aslinda her sey bunu yazdirmak ile alakali. Bunu yazdirmak istiyor ama operator left shift (<<) global
                            // bir fonksiyon oldugundan virtual edilemiyor. car.h icerisindeki Operator overload fonksiyonlari yoruma 
                            // alinirsa bu satirin error verdigi gorulebilir. 

                            // operator overload islemi ile kod legal kilinir ama calisma kismi henuz gerceklenmemistir.
                            // bunun icin bir virtual bir print fonksiyonu yazilip overload edilmelidir.

                            // Car.h sinifina eklenen print fonksiyonlari ve car.h sinifina eklenen << overload'u incelenebilir. Onlar incelenmeden
                            // bu ornegin pek bir anlami olmayabilir.

        cp->start();
        cp->run();
        cp->stop();
        std::cout <<"\n";
        delete cp;
        std::this_thread::sleep_for(100ms); // buraya ms yazabiliyoruz,  orasi da literals ile ilgili, ileride dahaa detayli anlatacak imis. 
    }
}

/********************************************************************************************************************************/
/********************************************************************************************************************************/
//Covariance
// bir sinifin sanal fonksiyonunu override edebilmeniz icin hem imzasi ayni hem de geri donus degeri turu ayni turemis sinifin bir
// fonksiyonu bildirilmesi gerekiyor. eger imzada bir farklilik olursa o override olmaz.
// for example
class kdr14{
    public: 
    virtual int foo(){}

    virtual int fook(int){}

    virtual int fooz(){}
};

class dkdr1 : public kdr14{
    public:
    virtual int foo(){} // override yazmamasina ve yanina virtual yazmasina ragmen alttaki fonksiyon ustteki fonksiyonun override'idir.

    virtual int fook(unsigned int){} // ustteki fonksiyon alttaki fonksiyonun override'i degildir cunki aldigi parametreler farklidir.
    // virtual int fook(unsigned int)override{} // eger override keywoard'unu yazarsam hata verecektir cunku override'i olamaz.

    // double fooz(){} // Bu override olmadigi gibi direkt olarak syntax hatasidir.
};

/********************************************************************************************************************************/
/********************************************************************************************************************************/
// eğer taban sinifin sanal fonksiyonununun geri dous degeri turu T bir sinif turu olmak uzere T* ya da T& ise normalde bu durumda turemis
// sinifin override edebilmesi icin T* ise T*, T& ise T& olmasi grekiyor AMA
// Turemis sinif override ederken T* yerine D* dondurebiliyor eger D, T sinifindan public kalitimiyla elde edilmis bir sinifsa!!!

class B{

};

class D : public B{
    // su an her D nesnesi bir B nesnesidir.
};

class b1{
    public:
    virtual B* foo(){}
    virtual D& foox(){}
    virtual B foos(){}
};

class b2 : public b1{
    public:
    D* foo()override{}   // goruldugu gibi geri donus degerleri farkli olmasina ragmen bir hata olusmamistir.
    D& foox()override{}
    // D foos()override{}  // bunu  kabul etmez. Yorum kaldirilirsa hata gorulur cunku kovaryans yalnizca T* ve T& icin
                        // gecerlidir.  
};
/********************************************************************************************************************************/
/********************************************************************************************************************************/
 // kovaryans ornegi

 void f_dnyrm()
 {
    Bmw3* p1 = new Bmw3;
    Bmw3* p2 = p1->clone(); // su an icin buna hata veriyor. cunku baslangic icin bunun geri donus degeri car4*. Cast edebilirim 
                            // ya da clone fonksiyonunun geri donus degerini Bmw3 ile degistirebilirim. İkincisini yapmak daha mantikli.
                            // su an icin hata kalkti. Asagida ise baska bir class'i kovaryans olarak deneyecegim ama hata verecek cunku
                            // clone fonksiyonunun geri donus degeri Car4 olarak birakilmistir.

    Toyota3* t1 = new Toyota3;
    // Toyota3* t2 = t1->clone();  // yorum kaldirilirsa gorulecektir ki burada bir hata mevcuttur.
 }
/********************************************************************************************************************************/
/********************************************************************************************************************************/
// Run time polimorfizminin en sik kullanildigi yerlerden birisi de polimorfik listelerdir.
// C++'ta konteynir'lar ve C dizileri referans tutamazlar!!! 
// yani elemanlari referans olan bir dizi tutamayiz. Pointer tutabilriiz ama referans tutamayiz!
// poly. list oluysturmanın 3 yolu var
// 1. Pointer dizisi olusturmak. Bu hic tavsiye edilen bir yontem degil. 
// 2. smart pointer'larla yonetmek. Suan gormedigimiz icin anlatmiyor.
// 3. Referance wrappers'lari kullanabiliriz. Referansi dogrudan kullanmak yerine wrapper edebliriz. Kendisi bir sinif.

void poly_list(){
    car4* a[100];

    // for (int i = 0; i < 100; i++)
    // {
    //     a[i] = create_random_car3(); //  burada pek tabi olarak herhangi bir hata yoktur.
    // }
        // yukaridaki durumu kullanabilecegim gibi asagidakini de kullanabilirim ve kesinlikle daha mantiklidir. Kullanilmasi
        // tavsiye edilir.

    for(car4 *p :a){
    }
}

/*
 */
    class asdfg{ 

    };

    void funci(asdfg&&){
        // bu fonksiyonun parametresi sag taraf referansi.
    } 
/*
 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ders disi calisma alanlari.

class freeTry1{
    public:

        freeTry1(){}
        freeTry1(int){}
        freeTry1(int,int){}

        virtual void b_func() final
        {

        }
        virtual void b_func(int,int)
        {

        }
};

class freeTry2 final : public freeTry1 {
    public:
        void b_func(int,int)override
        {

        }

        // void b_func() override  {}  // Bu hatalidir cunku final

        void c_func()
        {

        }

};

class freeTry3 : public freeTry1
{
    public:
        freeTry3(int x) : freeTry1(x){}
        freeTry3(double x){}
        freeTry3(double,int)
        {
            std::cout << "buraya geliyo\n";
        }
        freeTry3(std::string){}

};

class freeTry4 : public freeTry3
{
    public:
    using freeTry3::freeTry3;
};

void f_trying()
{
    freeTry4(double(43),int(34));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class f_kdr1
{

};


void movefnc(f_kdr1&& x)
{
    f_kdr1 s(std::move(x)); // tasima islemi simdi yapilmis olur cunku move constructor cagirilmis olur.
                            // Bu senaryoda move  constructor cagirilir.

    f_kdr1 y;
    y = std::move(x);       // bu senaryoda da tasima gerceklesir ama move assignment ile gerceklesir.

    f_kdr1 z(x);            // en buyuk yanlislardan biris bu kodun tasima yaptigini dusunmektir!!!
}

void f_func1()
{
    f_kdr1 m;
    movefnc(std::move(m));  // Burada tasima olmaz. Class'in tanimlanmasinda da olmaz burada yalnizca referansa
                            // baglama olur. Tasima islemi movefnc fonksiyonun icinde ola bilir.  

    
}

/*
for (auto &&x : con ){
    // burada type detection oldugu icin 
}

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

constexpr std::size_t size{100};

void f_kdr2()
{
    car4* a[size];

    for (auto &p : a){
        p = create_random_car3();
    }

    ///

        for (auto p : a){
        std::cout << *p;
        p->start(); //
        p->run();
        p->stop();
        delete p;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// multiple inheritance
// virtual inheritance
// RTTI 
// private inheritance
// protected inheritance
// NVI idiom -- non virtual interface idiom
// kalitimin onemli basliklari

// Bunlardan sonra exeption handler konusu var.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void car_game(car4* p)
{
    std::cout << *p;
    p->start();
    p->run();
    // eger araba volvo ise cam tavan acilsin. Sunroof ise yalnizca volvo class'inda var. Peki turu nasil 
    // algilayacagim? Sanirim RTTI ile?
    // Calisma zamaninda dinamik turun algilanmasini RTTI arac setleri saglar. Run Time Type Information
    /*
        dynamic_cast operatoru --> Downcasting ile ilgili. downcasting isleminin basarili bir sekilde yapilip yapilamayacagini siniyor.
        typeid
        type_info 
        Bunlar RTTI'in 3 farkli operatoru
    */

    auto vp = dynamic_cast<Volvo3*>(p);
    if(vp)
        vp->open_sunroof();

    // Eger runtime yazilim kosuyorken yukarida gelen sinif turu volvo ise dynamic_cast islemi bir adres donecek
    // eger volvo degil ise nullptr donecek. Bu sekilde bir kontrol ile RTTI'nin dynamic cast fonksiyonundan
    // yararlanilabilir.

    // Yukaridakinin yerine bunu da kullanabilirim, scope leakage'tan da korunmus olurum.

    if ( auto vpp = dynamic_cast<Volvo3*>(p))
    {
        vp->open_sunroof();
    }

    

    p->stop();

}

void f_kdr3()
{
    for (int i = 0; i<100;i++)
    {
        car4* p = create_random_car3();
        car_game(p);
        delete(p);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Dynamic cast kullanabilmem icin incelenen turun polimorfik bir tur olmasi onemlidir.

class base12
{
    public:
        virtual ~base12(){}
};

class der12 : public base12
{
    public:
        void derfoo(){}
};

void func(base1* baseptr)
{
    if (der12* dp = dynamic_cast<der12*>(baseptr))
    {
        dp->derfoo();
    }   
}

// Yukaridaki ornekte base12 class'inin polimorfik olmasini saglayan tek sey destructor'inin virtual olmasidir.
// 

// Yukaridaki durumda dynamic_cast yerine static_cast kullansaydik da bir compile time'da sorun yaratmnayacakti fakat
// run time'da hata alacaktik yani hata veriyor olmamasi dogru oldugu anlamina gelmiyor. 

int main() {
    f_trying();
    return 0;
}

