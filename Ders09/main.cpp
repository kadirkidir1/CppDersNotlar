#include <iostream>
#include "forInline.h"

// int sum_square(int,int); // c2cpp_ex.c dosyasındaki fonksiyonla isimleri aynı. C dosyasından geldiği için bunun
                            // C'den geldigini belirtmemiz gerekir. Bunun için aşağıdaki gibi kullanmamız gerekir.

extern "C" int sum_square(int,int); // Artık hata almayız ve kodumuz da çalışır.
// C'de çalışan kodları Cpp'de çalıştırmak için extern "C" kullanılmak zorunda. Bunun da birden fazla yolu mevcuttur.


/*  extern "C" nin başka bir alternatifi olarak .h dosyasında aşağıdaki yöntem de kullanılabilir. Tavsiye edilir.
#ifdef  __cplusplus
extern "C"{
#endif
    void f1(int);
    void f2(int);
    void f3(int);
    void f4(int,int);
#ifdef  __cplusplus
}
#endif
*/
/*
    ali.h

    extern "C" void f1();
    extern "C" void f2();

    2. olacak

    extern "C"{
        void f1();
        void f2();
        void f3();
    }
 */

/*
 __LINE__
 __FILE__ Bunlar pre-defined symbol const
 __STDC__ --> C'de default kabul ediliyor.
 __cplusplus --> Bu da C++'ta defined kabul ediliyor.
 */

/*
int main() {
    std::cout << "Hello, World!" << std::endl;
    x++;
    std::cout << x << "\n";
    std::cout << showX()<<"\n";

    int hx  = sum_square(3,6);
    std::cout << hx << "\n";

    std::cout << __cplusplus << "\n"; // cppreference sayfasina gidip bakildiginde 202002 degerinin C**20 standartı
                                      // oldugu gorulmekte.


    for (int i = 0; i < 10; ++i) {
        foo();

    }


    return 0;
}
 */

// Bir fonksiyonun inline olması başka bir şey, inline expand edilmesi başka bir şey.

inline int foo1(int x, int y){
    ///code
    return x*y +3;
    // Bu fonksiyon inline expand edilebilir veya edilmeyebilir. Hakeza inline anahtar sözcüğü olmasaydı bile
    // inline expand edilmeyecek anlamı çıkarılamazdı.

    // Inline fonksiyonların asıl önemli özelliği ODR'yi çiğnemiyor oluşları.
    // Eğer bir fonksiyonun tanımını bir başlık dosyasına koymak istiyorsanız o fonksiyon inline olmak  zorunda. Inline
    // olmayan bir fonksiyon tanımını başlık dosyaSINA koyarsanız ODR ihlal edilmiş olmaz.

    // Eğer bir başlık dosyasındaki tüm fonksiyonlar ilgili başlık dosyasında inline olarak tanımlanmışlarsa bu durumda
    // bu başlık dosyasına eşlik eden  bir cpp dosyası olmadanbir modul oluşturulabilir. Böyle modüllere ve böyle
    // modüllerden oluşan kütüphanelere header-only library denir. Cpp'nin stl kütüphanesi bir header-only library'dir.

    // Cpp17'ye kadar inline fonksiyonlar vardı. İlk standartlarından önce bile vardı, C'ye daha sonradan eklendi.
    // Ama C ve Cpp'deki inline'lar farklı kurallara tabii.
    // Cpp17 ile ile inline variable eklendi.

    // ODR için kullanılır yine inline variable.

    // Sınıfların tanımlamaları başlık dosyalarında yer alır tipik olarak. Class definition'lar ODR'yi ihlal etmez.
    // Class definition'lar token by token olmak üzere ODR ihlal edilmemiş olur.

    // Dikkat!! global fonksiyonlarda olduğu gibi sınıfın üye fonksiyonları da inline olarak başlık dosyasında
    // tanımlanabilir ve yine bu durum ODR'yi ihlal etmez.

    // Birçok projede Cpp kaynak dosyalarından C dilinde derlenmiş fonksiyonları çağırmamız gerekebilir. Cpp ve C
    // birlikte iş görebiliyor. Bu durumda programcılar ilk böyle bir senaryoyla karşılaştıklarında link aşamasında hata
    // alıyorlar ama hatayı başta anlamıyorlar. // Yeni bir C kaynak dosyası oluşturuyoruz örnek için Dikkat!!!
}

// CONSTRUCTOR // DESTRUCTOR //  Her ikisi de sınıfın non-static üye fonksiyonları olmak zorunda.
// 1. Bir sınıfın constructor ve destructor fonksiyonları global function olamaz. Sınıfın static üye fonksiyonu olamaz.
// 2. Constructor, sınıfın ismiyle aynı isme sahip olacak.
// 3. Constructor'ın geri dönüş değeri kavramı yok. Void değil yani, direkt olarak yok.
// 4. Constructor overload edilebilir.
// 5. Default constructor --
    // Bir sınıfın parametresi olmayan ya da tüm parametreleri varsayılan argüman alan yani argüman almadan çağırılabilen
    // constructor'lara default ctor deniyor.
    // Myclass();       --> Default ctor
    // Myclass(int);    --> Default ctor değil
// Special member function -- Derleyicinin bizim yerimize bu kodları yazabilmesi.
    // Default constructor
    // destructor
    // Copy constructor
    // Move constructor
    // Copy assignment
    // move assignment

    // Constructor const keywoard'ü ile tanımlanamaz. Snytax hatası.
    // constructor private olabilir bu bir syntax hatası değil. Ama client kodlarla çağırılması syntax hatası. Neden
    // private olduğu ileriki derslerde anlatılacak.

// destructor
// 1. ismi sınıf ismiyle aynı ~Myclass
// 2. sınıfın non-static üye fonksiyonu olmak zorunda
// 3. global olamaz, static üye fonksiyonu olamaz.
// 4. Const üye fonksiyon olamaz.
// 5. Private ya da protected olabilir. Syntax hatası değildir.
// 6. Constructor'dan önemli bir farkı, overload edilemez. Parametresi olmayan fonksiyon olmak zorunda.
// *  Birçok dilde constuctor varken destructor genelde yoktur, C++'a özgüdür. Bunun nedeni diğer dillerde
//    garbage collector olmasıdır. Cpp'de garbage collector yoktur.

// Farklı kaynak dosyalardaki global değişkenlerinin hangisinin ctor'unun daha önce çağırılacağı belirlenmiş değildir.
// static initialization fiasco --> bu terim ileride daha detaylı ele alinacak. || UB değil.
// Aynı kaynak dosyadaki global değişkenlerin hayata gelme sırası belirli, bildirimdeki sıra.
//

// Otomatik Ömürlü Sınıf Fonksiyonları
// Statik keywoardü olmadan fonksiyonların içinde tanımlanan değişkenler otomatik storage class.

class khk{
public:
    khk(){
        std::cout << "def ctor this = " << this << "\n";
    }
    ~khk(){
        std::cout << "def dstor this = " << this << "\n";
    }
};

void foo1(){
 khk kx;
}

int main(){
    for (int i = 0; i < 10;++i) {
        foo1(); // 10 kez constuctor 10 kez destructor cagirilacak. Çünkü bir fonksiyonla cagiriliyor ve fonksiyon
                // her cagirildiginda nesne hayata geliyor.
    }
}

int foo2(){
    khk kx;         // ctor cagirilir.
    khk& h = kx;    // ctor cagirilmaz cünkü kx zaten bir kere olusturulmustur.

    khk hk[5];      // 5 kere constructor cagirilir. 5 kere destructor    cagirilir.
}

/*
 khk kx;    // --> Default init. Sınıfın default ctor'u çağırılır. Sınıfın default ctor'u yoksa syntax hatası.
            // Sınıfın default ctor'u olmayabilir bu durumda default init yapmamamız lazm.
 khk nx{};  // --> Value init. Yine default ctor çağırılır.
 khk nx();  // --> aslında bu bir fonksiyon bildirimidir. Function declaration - not instantiation
 */

/*
class asd {
public:
    asd(int x)
    {
        /// code
    }
};

int main(){
    asd ax = 10; // Copy init. 10 değeri ilk değer olarak gider.
    asd bx = 20; // direct init.
    asd cx{30};  // uniform init. Brace init. direct list init.
}
 */

