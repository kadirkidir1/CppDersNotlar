#include <iostream>

// Ders'in 2. kismi degil, ilk kisimda cok kod oldugundan ve karmasiklastigindan buraya gectim. BOLUM 2

class A {
public:

};

class B {
public:
    B();
    B(A); // B sinifinin A parametreli bir degeri olduguna gore A'dan  B'ye ortulu bir donusum var demektir.
};

class C {
public:
    C();
    C(B);
};

int main_001(){
    A ax;
    B bx;

    bx = ax; // bu kod nasil oluyor da gecerli olabiliyor?
    // Cunku B sinifinin A turunden parametreye sahip bir constructor'i oldugu icin B sinifinin A parametreli
    // constructor'i bir constructor conversion.
}

int main_002(){
    A ax;
    C cx;

    // cx = ax; yorum kaldirilirsa gorulecektir ki bu bir syntax hatasidir. Peki neden derleyici donusum yapmadi??
    // hatanin sebebi 2 tane ortulu user-defined conversion varsa bunlar arka arkaya cagirilamaz!!! Ders13 klasor
    // notlarinda detayli olarak anlatiliyor. Peki ben bu donusumun kesinlikle olmasini istiyorsam
    // ne yapmaliyim? Ortulu donusum yerine kendim static cast edebilirim!
    cx = static_cast<C>(ax); // herhangi bir hata olmadi cunku 2 tane ortulu degil!

}

/* bir donusum acikca bir operator kullanilmadan derleyicinin durumdan vazife cikarmasiyla yapiliyorsa
 * boyle donusumlere implicit conversion deniyor.
 * Ama bir donusum tur donusturme operatorlerinden biri kullanildigi icin yapiliyorsa explicit conversion
 * deniyor.
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 class Myclass{
 public:
     Myclass() = default;
     Myclass(int);
 };

 void func(Myclass);    // Bir fonksiyonun parametresi Myclass ise ve ben bunu int turden bir parametre ile cagirrsam!
 void foo(const Myclass&);

int main_003(){
    func(12);           // int turden bir parametre ile cagiriyorum. Ya da int'e donusturulebilecek bir parametre ile
                        // cagirsam standart conversion ile!!
    func(1.2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Myclass bar()
{
    return 10;     // bilerek ya da bilmeyerek return degerine class yerine int turden bir ifade kullandim.
                   // normalde syntax hatasi olmasi gerekirken burada yok cunku burada da constuctor conversion
                   // kurallari gecerli
}

int main_004(){
    Myclass mi;
    int i = 10;

    func(10>5); // Burada farz edelim kodlama sirasinda hatali bir sey gonderdim ama bu syntax olarak hatali degil!!!
    // Burada bool'dan int'e standart conversion yapilacak, ardindan da implicitly conversion ile islem legal bir
    // sekilde devam edecek.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main_005(){
    Myclass m1 = 10;
    Myclass m2(20);
    Myclass m3{39}; // Bunlarin 3'u de gecerli.

    // eger fonksiyonun turu Myclass ise int turunden ya da int'e donusebilecek bir parametre ile de bu islemi
    // gerceklestirebilirim.

    func(10);
    foo(29); // const class& ifadesi prvalue kabul ettigi icin sorunsuz bir sekilde bu islemi gerceklestirdik.

    int ival{72};
    func(static_cast<Myclass>(ival)); // Simdi soyle bir kod gordugunuzde programcinin bunu yanlislikla
    // yazmis oldugunu dusunebilir misiniz? Boyle bir kod cok daha anlasilir.  Bu donusumu explicit olarak yapıyorum.

    // Necati hocanın onerisi: Eger tur donusturmek gerekiyorsa bunu implicit olarak degil explicit olarak yap.
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EXPLICIT: Yeni bir altbaslik
// explicit constructor

class Myclass0 {
public:
    Myclass0() = default;
    explicit Myclass0(int); // bu ctor'in explicit oldugunu gosteriyor. Explicit keywoard'u sadece tanimlamada
                            // olacak kullanimda olmayacak!!!
};

// bu constructor diyor ki ben donusumde kullanilabilirim AMA ne şartla? Donusumun explicit yapilmasi
// sartiyla. Artik implicit conversion yapilamaz diyor.

/*
 Bu constructor'i Cpp icerisinde cagirirken explicit keyword'unu cagirirsak syntax hatasi olur.
 Cagirmamiza gerek yok. Yani
 explicit Myclass0::Myclass0(int x){} --> HATALI
 Myclass0::Myclass0(int x){} --> Dogru
 */

int main_006(){
    Myclass0 m;

    // m = 10; // Burada yorum kaldirilirsa syntax hatasi oldugu gorulecek. Hatanin sebebi explicit ifadesidir.
    // explicit keywoard'u tanimdan kaldirildiginda hatanin kalktigi da gorulur.
}

// TEK PARAMETRELİ CONSTRUCTORLAR AKSI YONDE IKNA EDICI BIR NEDEN OLMADIGI SURECE EXPLICIT OLARAK BILDIRILMELI.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
using namespace std;
vector<int> ivec(100);  // Buradaki 100 size demektir.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void func2(vector<int>);
void func3(string str);

int main_007(){
    int ival{35};

    // func fonksiyonu bizden vector sinifi bekliyor ama biz yanlislikla ival'i koyarsak?
    // func2(ival); // normal ruh sagliginda boyle bir kod yazilmaz!!!
    // Yukariaki func onundeki yorum satirlari kaldirildiginda hata gorulur. Bunun sebebi int turunden
    // vector turune convert isleminin gerceklesememesidir. Standart kutuphanede bir iki yer haric
    // genel olarak explicit kullanim vardir. Ama istisnalar var mesela string

    func3("kadir kidir"); // Hata olmadi cunku string sinifinin const char* parametreli constructor'i
    // explicit degil.


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Myclass1{
public:
    Myclass1(int);
};

int main_008(){
    int x(10);      // direct initialization
    int y = 10;     // copy initialization

    Myclass m = 10;     // Copy initialization.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass2{
public:
    explicit Myclass2(int);
};

int main_009(){

    Myclass2 m = 10;     // Copy initialization. Syntax error because the class constructer is include
                         // explicit keywoard.
                        // Dikkat bir ctor'un explicit olmasinin bir baska etkisi copy init'te kullanilamamasidir.
   Myclass2 m1(10);     // bunda herhangi bir sorun yok, copy init'e kiziyor.
   Myclass2 m2{10};     // bunda herhangi bir sorun yok, copy init'e kiziyor.

   vector<int> ivec = 50;   // explicit oldugu icin vector sinifinda copy init yapamayiz AMA
   vector<int> ivec2{59};   // Bunda bir syntax error yok.

   // C++20 ile dile eklenen cok onemli bir format kutuphanesi.

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass3{
public:
    explicit Myclass3(int);
    Myclass3(double);
};

int main_010(){
    Myclass3 m = 10;    // Burada herhangi bir syntax hatasi yok!
    // Kurala gore constuctor explicit ise copy init yaptiginizda Func Overload Resoluation'daki sete
    // dahil edilmiyor!!!
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass4{
public:
    Myclass4(int , int);
};

int main_011(){
    Myclass4 m = {10,15};    // Burada herhangi bir syntax hatasi yok!

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass5{
public:
   explicit Myclass5();
};

int main_012(){
    Myclass5 m = {};    // Syntax Hatasi. Explicit ctor esittir'in sag tarafina bir sey yazaraktan bir
                        // init edilmesine izin vermiyor.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Siniflarin Static Veri Elemanlari & Siniflarin Static Uye Fonksiyonlari                              ///////
// Operator Overloading                                                                                 ///////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 Member'larda 3 ayri kategoriye ayriliyordu. Siniflarin
 a) data memberlari - Non static/ Static data member olmak uzere 2'ye ayriliyor.
 b) member functionlari - Non static/ Static member functions olmak uzere 2'ye ayriliyor.
 c) member type'lari - ya da nested type'lari
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass6{
public:
    static int x;   // static data member -- Hayatta olan Myclass6 nesnelerinin sayisi ne olursa olsun bi tane
                    // static omurlu x degiskeni. Siniflarin static veri elemanlari C'deki global veri elemanlarina
                    // bir alternatif. Static veri elemanlari yine dil katmaninda bir arac.

    int y;
};

// Global bir degisken ile sinifin static veri elemani arasindaki fark ne?
// Static veri elemani sinifin bir memberi. Yani class scope arama yapmam gerekir. Cozunurluk, ok ya da nokta
// operatoruyle cagirmam gerekir. Global degiskenler Name Lookup scope'tayken static Class degiskenler class
// scope'tadır.

// Access control. Erisim controlu. Namespace'teki global bir degisken erisim kontrolune sahip degil.
// Ama siniflarin statik veri elemanlari public private ya da protected olabilir.

// Son 25 dakikaya tekrar bak.

int main_013(){
    Myclass6 m;

    m.x = 10;   // x burada ne kadar m nesnesinin elemani gibi gozukse de m nesnesi ile bir alakasi yok cunku
                // static bir degisken. Ama :: yerine . ile de erisilebilir ve bir syntax hatasi degildir.
}

int main() {



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
