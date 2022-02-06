#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

struct Reading {
    int hour_;
    double temperature_;
    Reading(int h, double t)
        : hour_(h), temperature_(t) {}
    friend std::ostream& operator<<(std::ostream& os, const Reading& d) {
        os << d.hour_ << ' ' << d.temperature_ << " ";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Reading& d) {
        is >> d.hour_ >> d.temperature_;
        return is;
    }
};

int main() {
    std::cout << "Podaj nazwe pliku z ktorego chcesz odczytac: \n";
    std::string fileName = "";
    std::cin >> fileName;
    std::fstream ist(fileName, ist.in);
    if (!ist.is_open()) {
        std::cout << "File reading is close!!\n";
    }

    std::cout << "Podaj nazwe pliku do ktorego chcesz zapisac: \n";
    std::cin >> fileName;
    std::fstream ost(fileName, ost.out | ost.trunc);
    if (!ost.is_open()) {
        std::cout << "File writing is close!!\n";
    }

    std::vector<Reading> temps;
    int hour = 0;
    double teperature = 0.0;
    while (ist >> hour >> teperature) {
        if (hour < 0 || hour > 23) {
            std::cerr << "Nie poprawna godzina.";
        }
        temps.push_back(Reading(hour, teperature));
    }
    ist.close();

    std::cout << "wielkosc vector: " << temps.size() << '\n';
    for (int i = 0; i < temps.size(); i++) {
        temps[i].temperature_ += 3;
    }

    if (ost.is_open()) {
        for (auto& el : temps) {
            ost << el << '\n';
        }
    }
    ost.close();

    // std::fstream diary("Day1.txt", diary.out | diary.trunc);
    // // or longer -> std::ifstream::out | std::ifstream::app
    // if (diary.is_open()) {
    //     std::cout << "OPENED!\n";
    //     diary << "Today is my first day on ship, with my crew\n";
    //     diary << "I'm a little scared!\n";
    //     diary << "Hope it will be a marvelous adventure.\n";
    //     // don't need to call diary.close() - RAII
    // }
    // diary.close();
    // diary.open("Day1.txt");
    // if (diary.is_open()) {
    //     std::string str;
    //     while (!getline(diary, str, '\n').eof()) {
    //         std::cout << str << '\n';
    //     }
    // }

    return 0;
}