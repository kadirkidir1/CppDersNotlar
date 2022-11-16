#include <iostream>
#include <string>

// Sinifin static veri elemanlari ve Static uye fonksiyonlari
// Sinifin static veri elamanlari sinif icin bir tane ama sinifin her non-static veri elemani icin
// sinifin storage ihtiyaci artar.


 class kdr_001{
 public:
    int y;
    static int x;   // Decleration
    // Yani bu deklere edildiginde bunun icin bellekte bir yer ayrilmiyor,
    // Eger kullanirsak o zaman bellekte yer tahsis ediliyor.
};

int func_001()
{
    //kdr_001::x = 50;    // static oldugu icin bu sekilde erisebilirim.
                        // ama bu sekilde derlersem hata alirim cunku su an icin bu class'a
                        // bellek ayirmadim. programin tanimini da yapmamiz gerekir. Bunu tekrar
                        // tanimlamam gerekiyor.
    return 0;
}

int kdr_001::x; // burada tanimlamam gerekiyor. Main blogu icerisinde bu sekilde tanimlama yapamam!!!
                // bu bir definition.!! Mutlaka ve mutlaka bir degiskenin kullanilmasi icin bir yerde
                // taniminin olmasi gerekiyor.

 // C++17 oncesi static bir sinif degerine default deger verebilmek icin
 // 1. Const olacak // const olmazsa ilk deger vermek her zaman syntax hatasi.
 // 2. integral olacak. Tamsayi turleri yani

 class kdr_002{
 public:
     // static int z = 20;  // yorum kaldirildiginda hatalar gorulur
     const static int z = 20; // Hata ortadan kalkar
     // const static float z1 = 45.3; // non-integral type hatasi

 };

 // Siralama turleri de tamsayi turlerinin alt kategorisi oldugu icin enum'lari da kllanabiliriz.

 enum Color{black, white};

 class kdr_003{
 public:
     const static Color ckdr = black;   // Bir hata meydana gelmez!!!
 };

 // C++17 ile gelen ozellik inline ozelligidir.!!

 class kdr_004{
 public:
     inline static int h = 5;   // inline oldugu zaman tamsayi olmasi ya da const olmasi
                                // zorunda degil.
 };

 // Constructor init list ile siz sinifin sadece non-static elemanlarini init edeblirisniz.
 // Static bir veri elamanini kullanirsaniz syntax hatasi olur.

 class kdr_005{
 public:
     // kdr_005() : a8{10} {}   // yorumlar kaldirildiginda hata gorulebilir.
 private:
     static int a8;
 };

 int func_002(){
     // std::string::npos , npos'un ustune imleci getirip baktigimizda static const oldugu gorulur.
     // std::ios_base::beg, ayni sekilde static const
 }

 class kdr_006{
 public:
     void func(){
         h1 = 10;
         kdr_006::h1 = 15;
         this->h1 = 20;
     }
 private:
     static int h1;
 };

// C'de --> complete type nedir incomplete type nedir?

struct Data{
    // struct Data x;  // gecersiz. Su an da bu incomplete type durumunda. C'de de C++'ta da hatali.
    struct Data* dptr; // bunda hata yok. Self referancial pointer
};

class kdr_007{
    // kdr_007 x;  // syntax hatasi
    kdr_007* x;    // syntax hatasi degil.
    // Sinfin kendi turunden elemani olamaz ama kendi turunden pointer ya da referansi olabilir.
};

class kdr_008{
    static kdr_008 x;  // Bu bir bildirim oldugundan syntax hatasi soz konusu degil.
};

// global degiskenlerin biraz OOPYe uyarlanmis halleri ise siniflarin static fonksiyonlari
// global fonksiyonlara bir alternatif.

// diyelim ki bir banka ornegimiz var musteriler icin. Sinif burada acoount'u ifade ediyor.
// BU durumda her musteri icin ayni faiz orani uygulanacaksa yani parametre hep sabit ise
// faiz oranini static kullanabilirim ama faiz orani her musteri icin farkli olacaksa
// bu durumda non-static kullanmaliyim.

// SINIFLARIN STATIC UYE FONKSIYONLARI
class kdr_009{
public:
    static void func() {
        // static sinif fonksiyonlarinin this pointeri olmaz.
        // mx = 5; //Yorum kaldirilirsa hatali olur. Bu name lookup hatasi degildir.
        // hatanin sebebi mx static oldugu icin classi ile cagirmam gerekirdi.
        kdr_009 asd;
        asd.mx = 5;
    }

private:
    int mx, my;
};

class kdr_010{
public:
    static void foo43();
};

// degiskenlerde oldugu gibi fonksiyonlar da Cpp dosyasinda tanimlandigi zaman static keywoard'u
// kullanilmayacak.

//static void kdr_010::foo();     // bu bir syntax hatasidir cunku static olamaz.
void kdr_010::foo43(){}           // syntax hatasi degil.


class try1{
    static void k85();

    void t(){
        mc = 4;
    }
private:
    int mc,kare;
};

void try1::k85(){
    int asdsadsad;
}

class klas{
public:
    void func(){
        foo();  // non-static fonksiyon, static fonksiyonu cagirirken bir hata ile karsilasmaz.
    }

private:
    static void foo(){
        // func();  // static fonksiyon oldugu icin yorum kaldirildiginda hata gorulur.

    }

    static void foo1(klas m){
        m.func();  // bunda bir sorun yok!!
        asd12 = 12;
    }

    static int asd12;
    // sinifin static uye fonksiyonlari sinifin static veri elemanlarini kullanabilir.

    // const static uye fonksiyon olamaz!!

    /*static void func34()const{
        // bu yazilim hatalidir cunku static fonksiyon const olamaz.
    }
     */
};

///////////////////////////////////////////////////////////////////////////////////////////////////

//////MULAKAT SORUSU/////////
//////MULAKAT SORUSU/////////
//////MULAKAT SORUSU/////////
class ksas{
public:
    static int x;
    static int foo457(int x, int y);
};

int foo457();

int ksas::x = foo457(); // gecersiz kod. Cunku 2 tane arguman girilmesi lazim cunku ilk olarak
                        // bu fonksiyon class scope'a bakildi ve orada bulundu.
// static veri elamanina ilk deger veren fonksiyon ilk basta class scope'ta aranir.
// function overloading soz konusu degil.

/*
 * sinifin static veri elemanina ilk deger veren ifadedeki isim(nitelenmemiş ise) once
 * class scope'ta aranir.
 */

//////MULAKAT SORUSU/////////
//////MULAKAT SORUSU/////////
//////MULAKAT SORUSU/////////

// ASLA AMA ASLA MOVE CONSTRUCTOR DELETE EDILMEMELI!!!!!!
// ASLA AMA ASLA MOVE CONSTRUCTOR DELETE EDILMEMELI!!!!!!
// ASLA AMA ASLA MOVE CONSTRUCTOR DELETE EDILMEMELI!!!!!!
// ASLA AMA ASLA MOVE CONSTRUCTOR DELETE EDILMEMELI!!!!!!
// ASLA AMA ASLA MOVE CONSTRUCTOR DELETE EDILMEMELI!!!!!!


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#include <thread>

void foo67();
int func67(){
    std::thread th1{foo67};
    // std::thread th2{th1};    // hata verdi. Hata vermesinin asil sebebi copy constructor'inin
                                // delete edilmis olmasi. Bundan kurtulmak icin
    std::thread th2{ std::move( th1 )}; // yapmam gerekir ve sorun cozulur.
                                // kopyalanamaz ama tasinabilir. Thread sinifi, dosya islemleri
                                // uniqptr sinifi gibi siniflarda boyle islemleri sik sik  yapacaz.

}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#include <fstream>
// ofstream sinifi kopyalamaya karsi kapatilmis tasimaya karsi aciktir.
// otomatik omurlu bir nesneyle nesnenin ismiyle geri donerseniz return ofs ifadesinde
// ofs once
 std::ofstream open_write_file(const std::string& filename)
 {
    std::ofstream ofs{filename};
    if(!ofs) {
        throw std::runtime_error{filename + " cannot be created"};
    }
    return ofs;
 }

 int ofs_func(){
    auto std::ofstream = open_write_file"necati";
    // burada ne yapti neden yapti hicbir sey anlamadim!!
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

class living_object{
public:
    living_object(){
        ++live_count;
        ++lived_count;
    }
    ~living_object(){
        --live_count;
    }

    static int get_live_count(){
        return live_count;
    }

private:
    inline static int live_count{}; // aktif nesne sayisini verir.
    inline static int lived_count{}; // aktif + deaktif tum nesne sayisini verir.
    // yukaridaki private degiskenlere yalnizca class fonksiyonlari erisebilir. Diger client
    // fonksiyonlarinin da ulasabilmesi icin !!!!!! STATIC GET FONKSİYONLARININ!!! yazilmasi gerekir.

};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <algorithm>

class faytir{
public:
    faytir(const std::string& name) : m_name{name}
    {
        m_vec.push_back(this);
    }

    ~faytir(){
        std::erase(m_vec,this); // C++20 ile dile eklendi.

    }

    void ask_help(){
        std::cout << " ben korkusuz savasci " << m_name << "dusmanlar sardi etrafimi\n";

        // range-based for loop
        for (auto ptr : m_vec ) {
            if (ptr != this){
                std::cout << ptr->m_name << " ";
                }
        }
        std::cout << "HELP HELP HELP\n";
    }

private:
    std::string m_name;
    inline static std::vector<faytir*> m_vec;  // sinifin statik veri elemani. Bu bir bildirim.
};


faytir f1{"kadir"};
faytir f2{"ahmet"};
faytir *p1 = new faytir{"huseyin"};
faytir *p2 = new faytir{"mehmet"};
faytir f3{"burak"};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

// NAMED CONSTRUCTOR
// aslinda ctor degil!!! ama ctor gibi kullanilacak cunku amaci nesneyi olusturacak.

class complex{
public:
    complex(double r, double i);
    complex(double distance, double angle);     // redecleration sinif icinde syntax hatasi.
};


int main() {

    std::cout << "x degeri =       " << kdr_001::x      << std::endl;

    return 0;
}
