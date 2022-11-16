#include <iostream>

//// nested namespace tanimlamanin onceden tek yolu ic ice yazmakti ama modern c++'ya
//// bir kolaylik saglandi.
//
//namespace kdr1::kdr2::kdr3{
//    // daha onceden kullanilmamis olsalar da tum namespace'leri tanimis oluyor.
//    int x;
//}
//
//namespace kdr1::kdr2{
//    int y;
//}
//
//namespace kdr1{
//    int z;
//}
//
//namespace kdr0 = kdr1::kdr2::kdr3;
//
//void f_1(){
//    kdr1::z = 5;
//    kdr1::kdr2::y = 3;
//    kdr1::kdr2::kdr3::x = 7;
//
//}
//
////////////////////////////////////////////////////////////////////////////////////
//
//// inline namespaces: bir namespace'i inline keyword'uyle tanimladigimizda o
//// namespace icerisindeki isimler dogrudan onu kapsayan namespace icerisinde
//// gorunur oluyorlar.
//
//namespace kdr4{
//    namespace kdr5{
//        int x,y;
//    }
//}
//
//void f_2(){
//    kdr4::kdr5::x = 23;
//    // kdr4::x kullaniminin legal olmasini istiyorsam ne yapabilirim???
//    // 1. Using bildirimi kullanabilirim.
//    // 2. using namespace kullanabilirim.
//    // 3. En yenisi ise inline namespace.
//}
//
////////////////////////////////////////////////////////////////////////////////////
//
//namespace kdr6{
//    inline namespace kdr7{
//        int x1,y1;
//    }
//}
//
//void f_3(){
//    // Inline namespace ornegini goruyoruz.
//    // artik dogrudan kdr6'nin x'i diyebilecegim cunku kdr7'yi inline kullandim.
//    kdr6::x1 = 18;
//    kdr6::y1 = 43;
//}
//
////////////////////////////////////////////////////////////////////////////////////
//
//// C++20 standartlari ile asagidaki gibi tanim geldi.
//namespace kdr8::kdr9:: inline kdr10{
//    int x = 10;
//    // kdr10 ns'i kdr9'un icinde inline ns
//}
//
//void f_4(){
//// inline olmasaydi
//    kdr8::kdr9::kdr10::x = 15;  // yazacakken inline oldugu icin
//    kdr8::kdr9::x = 23;         // yazabiliyorum.
//}
//
////////////////////////////////////////////////////////////////////////////////////
//
//// bu biraz karmasik!
//namespace kdr11{
//    namespace Nested{
//        class C{
//            //..
//        };
//    }
//    using namespace Nested;
//    void func(Nested::C);
//}
//
//void f_5(){
//    kdr11::Nested::C x;
//    // func(x);    // hatali bir kullanim. Inline anahtar sozcugunden once bu durum
//                // hatali durumlardan bir tanesi idi. Bu hatayi gidermek icin asagidak
//                // cozumu uyguluyorum. Yani using bildirimini kaldirip inline anahtar
//                // sozcugunu kullanacagim.
//}
//
//namespace kdr12{
//    inline namespace Nested1{
//        class C1{
//            //..
//        };
//    }
//    void func(Nested1::C1);
//}
//
//void f_6() {
//    kdr12::Nested1::C1 x;
//    func(x);    // Bu sekilde kullanimda hata durumu ortadan kalkar. ADL devreye
//                // girdi.
//}
////////////////////////////////////////////////////////////////////////////////////
//// Nested Types, type members, members types
//// bir sinif taniminin icinde bir turu tanimlayabiliriz ya da bildirebiliriz.
//// 1. neden bir sinifin icerisinde bir tur bildirimi yapalim?
//// 2. bu sekilde bir tur bildirimi yaptigimda bu ture kullanimina erisim kurallar neler???
//// Ve 3.su hangi turleri varliklari bir sinif iceirsinde tanimlayabiliriz!!!
//
//
//
//class ckdr1{
//    using Word = int;   // bunu sinifin icerisinde ve disarinda yapmak arasinda fark var!
//                        // sinifi degistigi gibi kontrol erisimi de degisiyor.
//
//    typedef int Word1;
//    enum class Color {white,black}; // boyle de olabilir
//
//    class nested{
//        // boyle de olabilir!!!
//    };
//
//    Word1 mx;   // bu sekilde tanimlama yapabilirim
//};
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////// MULAKAT SORUSU /////// MULAKAT SORUSU /////// MULAKAT SORUSU /////// MULAKAT SORUSU //////
//
//struct Word{
//    short x,y;
//};
//
//class ckdr2{
//    Word m_a;           // bu yukaridaki struct'in turunden
//    typedef int Word;   // bu int turunden
//    Word m_b;
//};
//
///////// MULAKAT SORUSU /////// MULAKAT SORUSU /////// MULAKAT SORUSU /////// MULAKAT SORUSU //////
//
//class kdr3{
//    void func();
//
//    typedef int Word;
//};
//
//void kdr3::func() {
//    Word wx;        // class icinde arandigindan turu int turunden olur.
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//class kdr13{
//public:
//
//    class Nested {
//        friend class kdr13;
//    private:
//        void func();
//    };
//
//    void foo(){
//        n.func();   // Neco, bu sekilde yazmak da hata olur muydu diye bir soru sordu. // kaldirildigi
//        // takdirde hata ile karsilasilir. bunun nedeni, sinif Nested type'in private bolumune erisemiyor!!!
//        // ama bu durumu cozmek icin friend bildirimi kullanirsak bu hatadan kurtuluruz.
//        // friend bildirimi kaldirilirsa hata geldigi gorulur. Friend bildirimi yokken hata gelir.
//        // aslinda cok basit, sirf bir class, bir class'in icerisinde yani nested diye private bolumu
//        // ana class'in kullanimina acilmaz!!!!!
//    }
//
//private:
//    Nested n;
//};
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//// yukaridaki durumun tam dersi durumu ele alalim.
//class kdr14{
//private:
//    static int x;
//public:
//    class Nested{
//        void foo()
//        {
//            x = 5;  // bunda bir sorun olmaz.
//        }
//    };
//};
//// Dikkat Modern C++ oıncesi nested type'in enclosing type'in private bolumune erismesi gecerli degildi.
//// Modern C++'ta kural degisikligine gidildi.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class encloser{
//     struct Nested{
//         std::size_t get_sizeof_x()const{
//             return sizeof(mx);             // Bu Gecerli. Unavaluated context
//         }
//
////         int get_x()const{
////             return mx;                     // bu gecersiz!!! Cunku bir class'a ihtiyac duyuyor.
////                                            // hata ulasim hatasi degil. Asagidaki ornekle anlasilabilir.
////         }
//
//     int get_x2(encloser& enc){
//             return enc.mx;                 // eskiden gecersizdi Modern C++ ile gecerli hale geldi.
//         }
//     };
//     int mx;
// };
//
// // Nested type'a sahip olan sinif nested type'in private bolumune erisemiyor ama nested type'in kendi
// // fonksiyonlari enclosing type'in private bolumune erisebeiliyor.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//class kdr16{
//private:
//    class Nested{
//
//    };
//
//public:
//    static Nested foo();
//};
//
//void f_kdr16(){
////    kdr16::nested x = kdr16::foo(); // bu sekilde kullanim erisim hatasi.
//    auto x = kdr16::foo();     // bu sekilde erisim ise hata degil. Auto kullanimi erisim hatasini ortadan kaldiriyor.
////    decltype(kdr16::foo()) y = kdr16::foo();    // ya da bu sekilde kullanabilirim.
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//class kdr17{
//public:
//
//    class Nested2{
//    public:
//        void foo2(Nested2);
//    private:
//        int mx;
//    };
//private:
//    int m_x,m_y;
//};
//
//void kdr17::Nested2::foo2(Nested2 m){
//    // Fonksiyon parametresine bakilirsa, detayli tanimlanmadan kullanildi. Yani
//    // kdr17::Nested2 yerine direkt olarak Nested2 kullanildi.
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//// composition ( containment )
//
//// farkli siniflar arasindaki iliski bicimlerinden birine OOP'de composition deniyor.
//// Iki sinif arasinda eger bu iki sinif turunden nesneler bir araya gelerek bir is gerceklestiriyorlarsa
//// bu siniflar arasinda assaciation iliskisi var denir.
//// Eger bir nesne bir nesnenin sahibi durumundaysa yani bu sekilde bir association kurulmussa buna
//// aggregation deniyor.
//
//// insan beyin ornegi tamamen composition. Birinin omru bittiginde oburunun de omru bitiyor cunku.
//// Omursel bir birliktelik var.
//
//// futbol klubu - futbolcu - aggregation ornegidir. Cunku futbolcular transfer olabilirler.
//
//// Bir sinifin baska bir sinif turunden veri elemanina sahip olmasina containment deniyor.
//
//class kdr18{
//
//private:
//    kdr17 kdr17x;
//};
//// her kdr18 class'i tanimlandiginda icerisinde kdr17 class'i da create edilmis olacak!
//// Bu bir containment ornegi.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//class Engine{
//public:
//    void start();
//    void stop();
//};
//
//class Car{
//public:
//    void start(){
//        eng.start();    //
//    }
//    void stop(){
//        eng.stop();    //
//    }
//private:
//    Engine eng; // her araba nesnesinin iceirsinde bir engine class'i var. Bu tur iliskiye
//    // has a relationship denir. Sahiplik iliskisi!!
//};
//
//// Bir sinifa sahip olmam, onun tum public functionlarini istedigim gibi kullanabilecegim anlamina gelmiyor.
//// Ama bunu da yapabilirim. Yukarida start fonksiyonunun icerisine start fonksiyonunun yerlestirildigini
//// gorebiliriz.
/////////////////////////////////////////////////////////////////////////////////////////////////////
//// stack , queue ve privaty queue. Bunlarin ucu container.
//
//class Engine2{
//private:
//    void set_xyz();
//};
//
//class Car2{
//    void carfunc()
//    {
//        // eng.set_xyz();  // bu ismi kullandiginda syntax hatasi olacak!!!
//        // elemani sahip oldugum icin onun private bolumune sahip olmus olmuyorum
//        // Ama friend'lik verirsem tabiki private bolumune erisebilirim1!!!
//        // bu hatayi asagida friend bildiri
//    }
//private:
//    Engine2 eng;
//};
//     // *********************************************************************************** //
//class Engine3{
//private:
//    void set_xyz();
//    friend class Car3;
//};
//
//class Car3{
//    void carfunc()
//    {
//        eng.set_xyz();  // bu ismi kullandiginda syntax hatasi olacak!!!
//        // elemani sahip oldugum icin onun private bolumune sahip olmus olmuyorum
//        // Ama friend'lik verirsem tabiki private bolumune erisebilirim1!!!
//    }
//private:
//    Engine3 eng;
//};
//// birbaska sinif turunden nesneye hsahip olmaniz onun private bolumune erisim hakkina sahip oldugunuz
//// anlamina gelmiyor.
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//class Engine4{
//public:
//    Engine4(){
//        std::cout <<" Engine Def Ctor\n";
//    }
//
//     ~Engine4(){
//        std::cout <<" Engine destructor\n";
//    }
//
//private:
//
//};
//// Burada sirasiyla once Engine4 sinifinin constructor'i cagirilmis olur.
//// ardindan car4 sinifinin contructor'i
//// ardindan car4 sinifinin destructor'i ve
//// en son olarak engine4 sinifinin destructor'i cagirilmis olur.
//class Car4{
//public:
//    Car4(){// Burada sinifin contructor'ina gelmeden sinifin veri elemanlari create edilmis olur. Cunku aslinda tam
//            // olarak burasi contructor init lis!!! HATIRLA
//        std::cout <<" Car4 Def Ctor \n";
//    }
//    ~Car4(){
//        std::cout <<" Car destructor \n";
//    }
//
//private:
//    Engine4 eng4;
//};
//
//void f_car4(){
//    std::cout << "Hello, World!" << std::endl;//
//    {
//        Car4 mycar4;
//    }
//    std::cout << "Good Bye, World!" << std::endl;
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//class Member{
//public:
//    Member(int);    // def ctor degil!!!
//};
//
//class Owner {
//public:
////    Owner()   // eger def ctor'u kendim tanimlarsam burada hata olmus olur cunku derleyicinin default olarak
////    {         // kendi silmis oldugu def ctor'u kendim tanimlamaya calisiyorum.
////
////    }
//private:
//    Member mx;  // Owner class'inin def ctor'i derleyici tarafindan delete edilmistir!
//                // ama derlesek dahi hata vermez bu sekilde. AMA Owner tipinden bir class tanimlarsak
//                // asagida goruldugu gibi, hata aliriz. Member mx{20}; Bu sekilde cagirirsam hata olmaz.
//};
//
// void f_MemberEx(){
////     Owner x;   // default ctor'i delete edildigi icin error verecektir!!!
// }
//
// // Yukaridaki default ctor sorunundan kurtulmak icin CIL kullanilabilir.
// // Yani def ctor'u manuel yazdigimizda syntax hatasi ama def Ctor'u su sekilde yazarsak
// // Owner() : mx{10}{}  --> Burada herhangi bir syntax hatasiyla karsilasmayiz ve def ctor'u da tanimlayabiliriz.
//
// // Bir diger yolu da in-class init.
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//class kdr19{
// public:
//     kdr19(const char *pname, const char *psurname)
//     {
//         m_name = pname;
//         m_surname = psurname;
//         // Bu sekilde tanimlamak ile Constructor Init list ile tanimlamak arasinda arada daglar kadar
//         // fark var. Yeni baslayan yazilimcilar genelde bu sekilde tanimlama ile CIL'in ayni ise
//         // yaradigini dusunuyor.
//
//     }
// private:
//     std::string m_name,m_surname;
// };
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

// sinifizin copy ctor'ini derleyici default ederse, derleyicinin default ettigi copy ctor
// member'larin copy ctor'ini cagirir.

class Member_20{

public:
    Member_20() = default;
    Member_20(const Member_20& )
    {
        std::cout << "Member copy ctor \n";
    }
};

class Owner_20{
public:

private:
    Member_20 mx;
};

void f_Owner_20(){
    Owner_20 x;
    Owner_20 y = x; // copy ctor cagirilmasi icin bu hamle yapiliyor.
    // bu fonksiyon cagirildiginda gorulur ki, Owner_20 sinifinin icerisinde Member_20 sinifi init edildigi
    // icin ve Owner_20 sinifi copy ctor yontemiyle cagirildigindan, Member_20 sinifinin copy Ctor'una da girer
    // ve boylece "Member copy ctor" yazisinin yazildigi gorulur.
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Copy ctor ile ilgili yapilan en sik hata da su. Eger bir sinifa copy ctor'u kendimiz yaziyorsak
// veri elemanlarinin artik copy ctor edilmesinden biz sorumluyuz. CIL ile veri elemanlarinin
// copy constructor edilmesini sağlayacak kodu yazmazmasaniz syntax hatasi olmaz default ctor cagirilir
// derleyici tarafindan.

// Asagidaki ornekte Owner sinifi icin copy ctor'un default edilmesi yerine kendim yazacagim.
class Member_21{

public:
    Member_21() {
        std::cout << "Member Def ctor \n";
    }
    Member_21(const Member_21& )
    {
        std::cout << "Member copy ctor \n";
    }
};

class Owner_21{
public:
    Owner_21() = default;
    Owner_21(const Owner_21& other)
    {
        std::cout << "Owner copy ctor \n";
    }
private:
    Member_21 mx;
};

void f_Owner_21(){
    Owner_21 x;
    Owner_21 y = x;
    // Bu fonksiyon cagirildiginda gorulur ki, Owner_21 sinifinin CIL'ini yazmadigimizdan dolayi
    // Member_21 class'inin copy ctor'u cagirilmaz. 2 kez default ctor'u cagirilir.
    //// DIKKAT // Bir sinifa copy ctor yaziyorsaniz elemanlarin hepsinin copy construct edilmesinden
    //// siz sorumlusunuz. Eger herhangi bir elaminin copy construct edilmesini istiyorsaniz fiilen
    //// yazacaginiz copy ctor da CIL ile bunu belirtmelisiniz. Aksi halde derleyici default ctor'a
    //// yapilan cagri kodunu ekleyecek. ve default ctor var ise syntax hatasi da olusmayacak.
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Gelelim copy Assignment'a
// sinifin copy assingment'ini derleyici default ederse derleyici her zaman veri elamanlarinin herbiri
// icin atama operatorunu kullanir.

class Member_22{

public:
    Member_22() {
        std::cout << "Member Def ctor \n";
    }
    Member_22& operator=(const Member_22& )
    {
        std::cout << "Copy Assignment \n";
        return *this;
    }
};

class Owner_22{
public:
    Owner_22() = default;
    Owner_22(const Owner_22& other)
    {
        std::cout << "Owner copy ctor \n";
    }
private:
    Member_22 mx;
};

void f_Owner_22(){
    Owner_22 x,y;
    y = x;
    // Burada bekledigimiz, Copy assingment'in cagirilmasi. ki cagiriliyor :D
    // Burada yine tipik yapilan hatalardan biri programcinin sahip oldugu sinif icin
    // atama operator fonksiyonu yazmasi. Asagida yazalim!!

}

class Owner22{
public:
    Owner22& operator=(const Owner22 &other)
    {
        std::cout << "Owner22::copy assingment \n";
        // Elemanlarin birbirine atanmasi icin
        // mx = other.mx; yazmam gerekiyordu Yukaridaki ornek icin
        return *this;
        // bu durumda hata olmaz.

        // Eger bir sinif icin opearator=() yaziyorsaniz sinifin veri elemanlarinin birbirine
        // atanmasindan siz sorumlusunuz. Dolayisiyla operator atama fonksiyonu icinde eger
        // *this'in elemanlarina diger nesnenin elemanlarini atayacak deyimleri yazmazsaniz
        // syntax hatasi olmaz ama bir atama islemi de yapilmaz.
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Move Ctor ve Move Assingment'a gelelim.

class Member_23{
public:
    Member_23() = default;
    Member_23(const Member_23& other)
    {
        std::cout << " member copy ctor\n";
    }
    Member_23(Member_23&&)
    {
        std::cout << "member move ctor\n";
    }
};

class Owner_23{
public:

//    Owner_23()=default;

    // other special member function here.
    // Owner_23(Owner_23&& other) : mx(other.mx) {} Derleyicinin yazdigi move ctor boyle degil!!!
    // Owner_23(const Owner_23& other) : mx(other.mx){}    // copy constructor boyle
    //Owner_23(Owner_23&& other) : mx(std::move(other.mx))
//    {
//        // Simdi artik CIL'deki ifade bir rValue exp oldugu icin mx'in move ctoru cagirilacak.
//        // eger move ctor  yaziyorsaniz ve yazdiginiz move ctor sinifin veri elemanlari icinde
//        // tasima semantigini implemente etmesini istiyorsaniz siz de move ctor'u derleyicinin
//        // yazdigi gibi yazmalisiniz. Bu ise halis muhlis move ctor
//    }


private:
    Member_23 mx;
};

void f_Owner_23()
{
    Owner_23 x;
    Owner_23 y = std::move(x);
    // Move ctor yazimini derleyiciye biraktigim icin move Ctor sorunsuz bir sekilde calisti.

}

///////////////////////////////////////////////////////////////////////////////////////////////////

class Member_24{
public:
    Member_24() = default;
    Member_24(const Member_24& other)
    {
        std::cout << " member copy ctor\n";
    }
    Member_24(Member_24&&)
    {
        std::cout << "member move ctor\n";
    }
};

class Owner_24{
public:

    Owner_24()=default;

    // other special member function here.
    // Owner_23(Owner_23&& other) : mx(other.mx) {} Derleyicinin yazdigi move ctor boyle degil!!!
     Owner_24(const Owner_24& other) : mx(other.mx){}    // copy constructor boyle
    Owner_24(Owner_24&& other) : mx(std::move(other.mx))
    {
        // Simdi artik CIL'deki ifade bir rValue exp oldugu icin mx'in move ctoru cagirilacak.
        // eger move ctor  yaziyorsaniz ve yazdiginiz move ctor sinifin veri elemanlari icinde
        // tasima semantigini implemente etmesini istiyorsaniz siz de move ctor'u derleyicinin
        // yazdigi gibi yazmalisiniz. Bu ise halis muhlis move ctor

        // Burada rValue oldugu icin derleyici move ctor'u sorunsuz sekilde cagiracak.
    }


private:
    Member_24 mx;
};

void f_Owner_24()
{
    Owner_24 x;
    Owner_24 y = std::move(x);
    // Move ctor yazimini derleyiciye biraktigim icin move Ctor sorunsuz bir sekilde calisti.

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// son olarak move assingment'a bakalim.
class Member_25{
public:
};

class Owner_25{
public:
    // derleyicinin yazdigi move assg kodu
    Owner_25& operator=(Owner_25 &&other)
    {
        mx = std::move(other.mx);
        // eger siz bir sinif icin atama operator fonksiyonu yaziyorsaniz
        // a) tasiyan atama operator fonksiyonu yazarken veri elamanina atama yapacak
        //    kodu hic yazmazsaniz yine veri elemani eski degerde kalir ama kodu yanlislikla
        //    soyle yazarsaniz
        //      mx = other.mx; // bu durumda veri elemanina atama yapilirken tasima semantiginden
        //    faydalanilmis olmaz cunku copy assingment calisir. Elemanlar icinde tasima semantiginden
        //    faydalanmak istiyorsaniz tipki derleyicinin yazdigi mve assingment'ta oldugu gibi
        //    atama operatorunun sag tarafindaki nesneyi std::move fonk'u ile rValue exp'e
        //    donusturmeliyiz.
    }
private:
    Member_25 mx;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Cok sik yapilan hatalardan bir tanesi de sinifin veri elemanlarindan birinin kopyalamaya karsi kapatilmis olmasi.
//

class mmbr{
public:
    mmbr() = default;
    mmbr(const mmbr&) = delete;
    mmbr& operator=(const mmbr&) = delete;
    // hal boyleyken yani copy memberlar delete edilmisken move member'lar bildirilmemis ise
    // bu durumda copy constructable olmadigi gibi move constructable da degil.
    // yani bazi siniflar boyle. Ne kopyalanabiliyor ne tasinabiliyor. ama stl'de de karsimiza cikan
    // bazi siniflar copy constructable degil ama move constructable!!! Copy assngm degil ama move assngm.
    // Bunu yapmanin yolu copy member'lari delete edip move member'lari yazmak.
    mmbr(mmbr&&);
    mmbr& operator=(mmbr&&);

};

class ownr{
public:
    mmbr mx;
};

void f_ownr(){
    ownr x;
//    ownr y = x; // Bu durumda hata cikar cunku copy ctor delete edilmistir.
    ownr y = std::move(x); // Bu durumda hata cikmaz cunku rValue edilerek move Ctor cagirilmasi saglandi.

}

///////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory>
 class kdr11{
 public:
//    kdr11(const kdr11&)
//    {
//        // copy ctor cagirildi. Uniq ptr sinifi icin bazi seyler kapatilmis!!!
//        //
//    }
 private:
    std::unique_ptr<int> uptr;  // bu sinifin copy ctor'u delete edilmistir. Derleyici bu class icin
    // copy ctor yazarsa, yazacagi copy ctor'da hata oldugu icin derleyici bu ctor'u delete edecek.
};

void f_kdr11(){
    kdr11 x;
    kdr11 y = x;
    // fonksiyon bu sekilde cagiildiginda alinan error'a bakildiginda 'kdr11::kdr11(const kdr11&)' is
    // implicitly deleted hatasi aldigi gorulur.
}
////////////////////////////
class kdr12{
public:
    kdr11(const kdr11&)
    {
        // copy ctor cagirildi. Uniq ptr sinifi icin bazi seyler kapatilmis!!!
        // Boyle yapinca uptr icin Copy Ctor cagirilmamis olacak.
    }
private:
    std::unique_ptr<int> uptr;  // bu sinifin copy ctor'u delete edilmistir. Derleyici bu class icin
    // copy ctor yazarsa, yazacagi copy ctor'da hata oldugu icin derleyici bu ctor'u delete edecek.
};

void f_kdr12(){
    kdr12 x;
    kdr12 y = x;
    // fonksiyon bu sekilde cagiildiginda alinan error'a bakildiginda 'kdr11::kdr11(const kdr11&)' is
    // implicitly deleted hatasi aldigi gorulur.
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// sinifin kendi sinifi turunden veri elemani olamayacagini hatirlayalim.
class ylh{
private:
//    ylh x;  // Bu her zaman syntax hatasi. AMA static veri elemani olabilir
    static ylh x;   // bu syntax hatasi degil.
    ylh *p; // incomplete type olarak pointer ya da ref olabilir.
    //
    };

///////////////////////////////////////////////////////////////////////////////////////////////////
// gelecek derslerde 4-5 saat kadar string sinifi anlatilacak.



///////////////////////////////////////////////////////////////////////////////////////////////////


int main() {
    f_kdr11();
    return 0;
}
