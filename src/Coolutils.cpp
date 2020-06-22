
#include "Coolutils.h"

std::string StringToUpper(const std::string &string) {
    std::string upper;
    transform(string.begin(), string.end(), std::back_inserter(upper), toupper);
    return upper;
}

std::string::size_type FindSubstring(const std::string &string, const std::string &substring) {
    return StringToUpper(string).find(StringToUpper(substring));
}


bool Parse(const std::string &str_input, int &output) {
    try {
        output = std::stoi(str_input);
    } catch (std::invalid_argument &) {
        return false;
    }
    return true;
}

bool ParseDouble(const std::string &str_input, double &output) {
    try {
        output = std::stod(str_input);

    } catch (std::invalid_argument &) {
        return false;
    }
    return true;
}


int IntegerEnter() {
    try {
        std::string input;
        int tmp;
        if (!std::cin.good()) {
            throw std::exception();
        }
        getline(std::cin, input);
        if (!std::cin.good()) {
            throw std::exception();
        }
        while (!Parse(input, tmp) || tmp < 0) {
            std::cout << "This is not the correct input. Please try again " << std::endl;
            if (!std::cin.good()) {
                throw std::exception();
            }
            getline(std::cin, input);
        }
        return tmp;
    }
    catch (std::exception &) {
        std::cout << R"((╯°□°）╯︵ ┻━┻)" << std::endl;
        return INT32_MAX;
    }
}

int DoubleEnter() {
    try {
        std::string input;
        double tmp;
        if (!std::cin.good()) {
            throw std::exception();
        }
        getline(std::cin, input);
        if (!std::cin.good()) {
            throw std::exception();
        }
        while (!ParseDouble(input, tmp)) {
            std::cout << "This is not the correct input. Please try again " << std::endl;
            if (!std::cin.good()) {
                throw std::exception();
            }
            getline(std::cin, input);
            if (!std::cin.good()) {
                throw std::exception();
            }
        }
        return tmp;
    }
    catch (std::exception &) {
        std::cout << R"((╯°□°）╯︵ ┻━┻)" << std::endl;
        return INT32_MAX;
    }
}


bool CaseInsensitiveEquals(const std::string &str1, const std::string &str2) {
    return std::equal(str1.begin(), str1.end(),
                      str2.begin(), str2.end(),
                      [](char str1, char str2) {
                          return tolower(str1) == tolower(str2);
                      });
}

bool startsWith(const std::string &string, const std::string &starts) {
    // std::string::find returns 0 if toMatch is found at starting
    return string.find(starts) == 0;
}

void Wait(const int &millisecond) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
}

void continueByEnter() {
    try {
        std::string tmp;
        std::cout << "Continue by pressing anything:" << std::endl;
        if (!std::cin.good()) {
            throw std::exception();
        }
        std::getline(std::cin, tmp);
        if (!std::cin.good()) {
            throw std::exception();
        }
    }
    catch (std::exception &) {
        std::cout << R"((╯°□°）╯︵ ┻━┻)" << std::endl;
        return;
    }

}

void AppendTime(std::string &string) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string.append(" ");
    string.append(std::to_string(1900 + ltm->tm_year));
    string.append("|");
    string.append(std::to_string(1 + ltm->tm_mon));
    string.append("|");
    string.append(std::to_string(ltm->tm_mday));
    string.append(" ");
    string.append(std::to_string(1 + ltm->tm_hour));
    string.append("|");
    string.append(std::to_string(1 + ltm->tm_min));
    string.append("|");
    string.append(std::to_string(1 + ltm->tm_sec));
}

void clearScreen() {
    system("clear");
}

void printBorder() {
    std::cout << R"(##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=####=##=##=##=##=##=##=##=##=##)"
              << std::endl;
    std::cout << R"(_,.-'~'-.,__,.-'~'-.,__,.-'~'-.,__,.-'~'-.,__,.-'~'-.,_,.-'~'-.,__,.-'~'-.,__,.-'~'-.,__,.-)"
              << std::endl;
    std::cout << R"(##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=##=####=##=##=##=##=##=##=##=##=##)"
              << std::endl;
}

void printDivider() {
    std::cout << R"(<>================================<>================================<>)" << std::endl;
}

void printWrong() {
    std::cout << "WRONG choice bucko ! Please try again." << std::endl;
    printDivider();
    std::cout << R"(........................................................................)" << std::endl;
    std::cout << R"(:      ,~~.          ,~~.          ,~~.          ,~~.          ,~~.    :)" << std::endl;
    std::cout << R"(:     (  6 )-_,     (  6 )-_,     (  6 )-_,     (  6 )-_,     (  6 )-_,:)" << std::endl;
    std::cout << R"(:(\___ )=='-'  (\___ )=='-'  (\___ )=='-'  (\___ )=='-'  (\___ )=='-'  :)" << std::endl;
    std::cout << R"(: \ .   ) )     \ .   ) )     \ .   ) )     \ .   ) )     \ .   ) )    :)" << std::endl;
    std::cout << R"(:  \ `-' /       \ `-' /       \ `-' /       \ `-' /       \ `-' /     :)" << std::endl;
    std::cout << R"(: ~'`~'`~'`~`~'`~'`~'`~'`~`~'`~'`~'`~'`~`~'`~'`~'`~'`~'`~`~'`~'`~'`~'` :)" << std::endl;
}


void printOptions() {
    std::cout << "     Options" << std::endl;
    std::cout << "     ||.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.|| " << std::endl << std::endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//