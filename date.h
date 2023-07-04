#ifndef DATE_H
#define DATE_H

class Date {
    private:
        int day, month, year;
    public:
        // CONSTRUCTORES
        Date();
        Date(int);
        Date(int, int, int);

        // GETTERS
        int getDay();
        int getMonth();
        int getYear();

        // SETTERS
        void setDay(int);
        void setMonth(int);
        void setYear(int);
};

#endif