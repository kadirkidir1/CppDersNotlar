#include <iostream>
#include <string>
#include <random>

#include "Car.h"
#include <exception>      
#include <stdlib.h>

// std::exception, std::terminate
//Bu derste cok onemli olan exeption handling'ten bahsedilecek.
// Her C++ programcisinin hakim olmasi gereken cok muhim bir konudur kendileri.

// 1. run time'da isini yapmasi gereken bir kod isini yapamiyor cunku kodu yanlis yazilmis. boyle hatalara programlama hatasi deniyor genel olarak.
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
// !!!!! Mudahale etmeyeceginiz bir exception'i yakalamaya calisin. 

// 3 onemli keywoard vardir. Throw, try ve catch
// exception throw etmek ne demek. fonksiyon isini yapamadiginda bir nesnse olusturuyor bu nesnenin varlik nedeni daha ust katmandaki kodlara fonksiyonun isini yapamadigini anlatmak olan bir nesne
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
    throw 1;
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
// her zaman catch parametrelerini referans yapiyoruz. Ve eger bir sey degistirmeyeceksek const'a dikkat edelim. Seyrek karsimiza cikar degistirmek.

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


int main() 
{   
    fmain_6();
    return 0;
}

 