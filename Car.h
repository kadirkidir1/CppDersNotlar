//
// Created by test2 on 8/4/2022.
//

#ifndef DERS26_CAR_H
#define DERS26_CAR_H

#include <iostream>
#include <string>
#include <random>

class car4{
public:
    virtual void print(std::ostream&)const = 0;
    virtual car4* clone() = 0;
    virtual void start() = 0;   // taban sinif fonksiyonlari pure virtual yapildi.
    virtual void run() = 0;
    virtual void stop() = 0;
};

class Bmw3 : public car4{
public:
    virtual void print(std::ostream& os)const override
    {
        os << " I Am BMW\n";
    }

    Bmw3* clone()override{
        //return new Bmw3;    // boyle yapsaydim def ctor ile init edecektim.
        return new Bmw3(*this); // boyle yapinca ise oncekinin aynisini kopyaladim cunku copy ctor.
    }

    void start()override{
        std::cout << " bmw3 start cagirildi \n";
    }
    void run()override{
        std::cout << " bmw3 run cagirildi \n";
    }
    void stop()override{
        std::cout << " bmw3 stop cagirildi \n";
    }
};

class Fiat3 : public car4{
public:
    virtual void print(std::ostream& os)const override
    {
        os << " I Am fiat\n";
    }
    car4* clone()override{
        //return new Bmw3;    // boyle yapsaydim def ctor ile init edecektim.
        return new Fiat3(*this); // boyle yapinca ise oncekinin aynisini kopyaladim cunku copy ctor.
    }
    void start()override{
        std::cout << " fiat3 start cagirildi \n";
    }
    void run()override{
        std::cout << " fiat3 run cagirildi \n";
    }
    void stop()override{
        std::cout << " fiat3 stop cagirildi \n";
    }
};

class Volvo3 : public car4{
public:
    void open_sunroof(){
        std::cout << " volvo3 cam tavani acildi \n";
    }
    virtual void print(std::ostream& os)const override
    {
        os << " I Am volvo\n";
    }
    car4* clone()override{
        //return new Bmw3;    // boyle yapsaydim def ctor ile init edecektim.
        return new Volvo3(*this); // boyle yapinca ise oncekinin aynisini kopyaladim cunku copy ctor.
    }

    void start()override{
        std::cout << " volvo3 start cagirildi \n";
    }
    void run()override{
        std::cout << " volv03 run cagirildi \n";
    }
    void stop()override{
        std::cout << " volvo3 stop cagirildi \n";
    }
};

class VolvoS80 : public Volvo3{
public:
    virtual void print(std::ostream&os)const override
    {
        os << " I Am volvos80\n";
    }
    car4* clone()override{
        //return new Bmw3;    // boyle yapsaydim def ctor ile init edecektim.
        return new VolvoS80(*this); // boyle yapinca ise oncekinin aynisini kopyaladim cunku copy ctor.
    }

    void start()override{
        std::cout << " volvoS80 start cagirildi \n";
    }
    void run()override{
        std::cout << " volvoS80 run cagirildi \n";
    }
    void stop()override{
        std::cout << " volvoS80 stop cagirildi \n";
    }
};

class Toyota3 : public car4{
public:
    virtual void print(std::ostream& os)const override
    {
        os << " I Am toyota\n";
    }
    car4* clone()override{
        //return new Bmw3;    // boyle yapsaydim def ctor ile init edecektim.
        return new Toyota3(*this); // boyle yapinca ise oncekinin aynisini kopyaladim cunku copy ctor.
    }

    void start()override{
        std::cout << " Toyota3 start cagirildi \n";
    }
    void run()override{
        std::cout << " Toyota3 run cagirildi \n";
    }
    void stop()override{
        std::cout << " Toyota3 stop cagirildi \n";
    }
};

class Dacia3 : public car4{
public:
    virtual void print(std::ostream& os)const override
    {
        os << " I Am Dacia\n";
    }
    car4* clone()override{
        //return new Bmw3;    // boyle yapsaydim def ctor ile init edecektim.
        return new Dacia3(*this); // boyle yapinca ise oncekinin aynisini kopyaladim cunku copy ctor.
    }

    void start()override{
        std::cout << " Dacia3 start cagirildi \n";
    }
    void run()override{
        std::cout << " Dacia3 run cagirildi \n";
    }
    void stop()override{
        std::cout << " Dacia3 stop cagirildi \n";
    }
};

car4* create_random_car3()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution dist{1,6};

    switch (dist(eng)){
        case 1: std::cout << " BMW olusturuldu\n"; return new Bmw3;
        case 2: std::cout << " Fiat olusturuldu\n"; return new Fiat3;
        case 3: std::cout << " Volvo olusturuldu\n"; return new Volvo3;
        case 4: std::cout << " Toyota olusturuldu\n"; return new Toyota3;
        case 5: std::cout << " Dacia olusturuldu\n"; return new Dacia3;
        case 6: std::cout << " VolvoS60 olusturuldu\n"; return new VolvoS80;
    }
}

std::ostream& operator<<(std::ostream& os, const car4& other)
{
    other.print(os); // isin icinde os da var.
    return os;
}

#endif //DERS26_CAR_H
