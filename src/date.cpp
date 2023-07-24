// SYSTEM INCLUDES
#include<iostream>
#include<stdlib.h>

// USER INCLUDES
#include "date.h"

// NAMESPACES
using namespace std;

// CONSTRUCTORES
Date::Date() {
    cout << "Ingrese el dia: ";
    cin >> day;
    cout << "Ingrese el mes: ";
    cin >> month;
    cout << "Ingrese el anio: ";
    cin >> year;
}

Date::Date(int _date) {
    day = _date / 1000000;
    month = (_date / 10000) % 100;
    year = _date % 10000;
}

Date::Date(int _day, int _month, int _year) {
    day = _day;
    month = _month;
    year = _year;
}

// GETTERS
int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }

int main() {
    Date date(22052023);

    cout << "Fecha: " << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << endl;
    
    return 0;
}
