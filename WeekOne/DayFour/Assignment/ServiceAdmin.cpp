//#include "ServiceRecord.h"
#include <iostream>
#include <vector>

enum PaymentMethod {Card, Swish, Cash};
enum ServiceMethod{OilChange, TireChange, Cleaning};

class date{
    private:
    
    public:
    int day, month, year;
    date()=default;
    date(int _day, int _month, int _year):day(_day),month(_month),year(_year){}
};

class part{
    public:
    int partNumber;
    part() = default;
    part(int _partNumber):partNumber(_partNumber){}
    void printPartnumber(){
        std::cout << "Part number: " << partNumber << std::endl;
    }
};

class service{
    public:
    std::string serviceType;
    service() = default;
    service(std::string _serviceType): serviceType(_serviceType){}
    void  printServiceType(){
        std::cout << "Service method: " << serviceType << std::endl;;
    }
    
};

class record {
    public:
    PaymentMethod payMeth;
    date serviceDate;
    int recordId;
    std::vector<part> changedParts;
    std::vector<service> servicesPerformed;

    record(int _recordId):recordId(_recordId){}

    void setPaymentMethod(PaymentMethod _payMeth){
        this->payMeth = _payMeth;
    }
    void setDate(date _serviceDate){
        this-> serviceDate = _serviceDate;
    }
    void addPartChanged(part _part){
        this->changedParts.push_back(_part);

    }
    void addServicePerformed(service _service){
        this->servicesPerformed.push_back(_service);
    }
    void getPartsChanged(){
        int n = this->changedParts.size();
            for(int i = 0; i < n; i++){
                changedParts[i].printPartnumber();
            }
    }
    void getServicesPerformed(){
        int n = this->servicesPerformed.size();
        for(int i = 0; i<n; i++){
            servicesPerformed[i].printServiceType();
        }
    }
    void getPaymentMethod(){
        if(payMeth == PaymentMethod::Card){
            std::cout << "Paymentmethod is Card" << std::endl;
        }

        if(payMeth == PaymentMethod::Swish){
            std::cout << "Paymentmethod is Swish" << std::endl;
        }
        if(payMeth == PaymentMethod::Cash){
            std::cout << "Paymentmethod is cash" << std::endl;
        }
    }
};


int main(){
    int day = 1;
    int month = 12;
    int year = 2004;
    int iD = 986521;
    date d(day, month, year);
    record firstRecord(iD);
    PaymentMethod c = PaymentMethod::Swish;
    firstRecord.setPaymentMethod(c); 
    firstRecord.setDate(d);
    std::cout << "Year of date: " << d.year << std::endl;
    part firstPart(2829);
    part secondPart(2728);
    service oil("OilChange");
    service tire("TireChange");
    firstRecord.addPartChanged(firstPart);
    firstRecord.addPartChanged(secondPart);
    firstRecord.addServicePerformed(oil);
    firstRecord.addServicePerformed(tire);
    firstRecord.getPartsChanged();
    firstRecord.getServicesPerformed();
    firstRecord.getPaymentMethod();

}