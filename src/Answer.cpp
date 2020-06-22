#include "Answer.h"


void Answer::LoadAnswer() {

}

Answer::~Answer() = default;


std::vector<std::string> &Answer::getAnswerText() {
    return answer_text;
}


void Answer::Answering(const int &parameter) {
    std::to_string(parameter);
}

void Answer::setResult(const double &result) {
    this->result = result;
}

void Answer::Clear() {
    answer_text.clear();
    result = 0;
    answers.clear();

}

double Answer::getResult() const {
    return result;
}

std::set<std::string> &Answer::getAnswers() {
    return answers;
}

void Answer::LoadAnswer(const int &max) {
    std::cout << "Loading default" << max << std::endl;
    std::to_string(max);
}


void Answer::Answering(const int &parameter, const int &parameterB) {
    printDivider();
    if (parameter == 0) LoadAnswer(parameterB);
    else {
        std::cout << "Enter your answer: " << std::endl;
        std::string tmp;
        int input;
        int index = 1;
        while ((index - 1) < parameter) {
            printDivider();
            std::cout << "Enter the " << index
                      << ". answer or end by entering blank line." << std::endl;
            getline(std::cin, tmp);
            printDivider();
            if (!std::cin.good()) return;
            while (!Parse(tmp, input) || input <= 0 || input > parameter ||
                   (std::count(answers.begin(), answers.end(), std::to_string(input)))) {
                if (tmp == "") break;
                std::cout << "This is not the correct input. Please try again " << std::endl;
                getline(std::cin, tmp);
                if (!std::cin.good()) return;
            }
            if (tmp == "") break;
            answers.insert(std::to_string(input));
            index++;
        }
    }

}

void Answer::Print(const int &parameter) const {
    std::cout << "Printing  default" << parameter << std::endl;
    std::to_string(parameter);
}

bool Answer::areEqual(std::shared_ptr<Answer> object) {
    return answer_text == object->answer_text && answers == object->answers && object->result && object->result;
}

Answer::Answer() = default;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MultipleChoice_Answer::LoadAnswer(const int &max) {
    std::cout << "Enter the answer" << std::endl << "Example:\"2\" (Pound)" << std::endl;
    int input;
    while (true) {
        printDivider();
        input = IntegerEnter();
        if (input == INT32_MAX) return;
        if (input < 1 || input > max || (std::count(answer_text.begin(), answer_text.end(), std::to_string(input)))) {
            std::cout << "Please select the answer within the correct bounds." << std::endl;
            continue;
        }
        break;
    }
    answer_text.push_back(std::to_string(input));
}

MultipleChoice_Answer::MultipleChoice_Answer() = default;


MultipleChoice_Answer::~MultipleChoice_Answer() = default;

void MultipleChoice_Answer::LoadAnswer() {

}


void MultipleChoice_Answer::Answering(const int &parameter) {
    //Basically nothing
    Answer::Answering(parameter);
}

void MultipleChoice_Answer::Print(const int &parameter) const {
    if (parameter == 0) {
        std::cout << answer_text[0] << std::endl;
    } else {
        for (const auto &item :answers)
            std::cout << item << std::endl;
    }
}

bool MultipleChoice_Answer::areEqual(std::shared_ptr<Answer> object) {
    return answer_text == object->getAnswerText() && getAnswers() == object->getAnswers();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ABCD_Answer::ABCD_Answer() = default;

ABCD_Answer::~ABCD_Answer() = default;

void ABCD_Answer::LoadAnswer() {
    std::cout << "Enter the answer" << std::endl << "Example:\"B\" (Pound)" << std::endl;
    std::string tmp;
    while (true) {
        printDivider();
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return;
        if (CaseInsensitiveEquals(tmp, "a") || CaseInsensitiveEquals(tmp, "b") || CaseInsensitiveEquals(tmp, "c") ||
            CaseInsensitiveEquals(tmp, "d")) {
            break;
        }
        std::cout << "Please enter the answer with the correct syntax." << std::endl;
    }
    answer_text.push_back(tmp);
}


void ABCD_Answer::Answering(const int &parameter) {
    printDivider();
    std::to_string(parameter);
    LoadAnswer();
}

void ABCD_Answer::LoadAnswer(const int &max) {
    Answer::LoadAnswer(max);
}

void ABCD_Answer::Print(const int &parameter) const {
    if (parameter == 0) std::cout << answer_text[0] << std::endl;
}

bool ABCD_Answer::areEqual(std::shared_ptr<Answer> object) {
    return CaseInsensitiveEquals(getAnswerText()[0], object->getAnswerText()[0]);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
YES_NO_Answer::YES_NO_Answer() = default;

YES_NO_Answer::~YES_NO_Answer() = default;

void YES_NO_Answer::LoadAnswer() {
    std::cout << "Enter the answer" << std::endl << R"(Example:"Yes" or "No")" << std::endl;
    std::string tmp;
    while (true) {
        printDivider();
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return;
        if (CaseInsensitiveEquals(tmp, "yes") || CaseInsensitiveEquals(tmp, "no")) {
            break;
        }
        std::cout << "Please enter the answer with the correct syntax." << std::endl;
    }
    answer_text.push_back(tmp);
}


void YES_NO_Answer::Answering(const int &parameter) {
    printDivider();
    std::to_string(parameter);
    LoadAnswer();
}

void YES_NO_Answer::LoadAnswer(const int &max) {
    Answer::LoadAnswer(max);
}

void YES_NO_Answer::Print(const int &parameter) const {
    if (parameter == 0) std::cout << answer_text[0] << std::endl;
}

bool YES_NO_Answer::areEqual(std::shared_ptr<Answer> object) {
    return CaseInsensitiveEquals(getAnswerText()[0], object->getAnswerText()[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


SortAnswer::SortAnswer() = default;

SortAnswer::~SortAnswer() = default;

void SortAnswer::LoadAnswer(const int &max) {
    std::cout << "Enter the correct order of the items." << std::endl
              << "Example Inventions from the oldest to the newest:" << std::endl
              << "   \"2\" (2.Light bulb)" << std::endl
              << "   \"1\" (1.The internet)" << std::endl
              << "   \"3\" (3.Iphone)" << std::endl;
    int input;
    int kek = max;
    while (kek != 0) {
        printDivider();
        input = IntegerEnter();
        if (input == INT32_MAX) return;
        if (input < 1 || input > max || (std::count(answer_text.begin(), answer_text.end(), std::to_string(input)))) {
            std::cout << "Please select the answer in the correct bounds." << std::endl;
            continue;
        }
        answer_text.push_back(std::to_string(input));
        --kek;
    }

}


void SortAnswer::LoadAnswer() {

}

void SortAnswer::Answering(const int &parameter) {
    printDivider();
    LoadAnswer(parameter);
}

void SortAnswer::Print(const int &parameter) const {
    if (parameter == 0) {
        for (const auto &item :answer_text) {
            std::cout << item << std::endl;
        }
    }
}

bool SortAnswer::areEqual(std::shared_ptr<Answer> object) {
    return getAnswerText() == object->getAnswerText();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextAnswer::TextAnswer() = default;

TextAnswer::~TextAnswer() = default;

void TextAnswer::LoadAnswer() {
    std::cout << "Enter the  answer " << std::endl << R"(Example: "It was invented in the year 1888." || "1888")"
              << std::endl;
    std::string tmp;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    answer_text.push_back(tmp);

}


void TextAnswer::Answering(const int &parameter) {

    if (parameter == 0) {
        printDivider();
        std::cout << "Careful be precise with your answer!" << std::endl;
        printDivider();
        LoadAnswer();
    } else if (parameter == 1) {
        printDivider();
        LoadAnswer();
    } else {
        std::string tmp;
        for (int i = 1; i <= parameter; ++i) {
            printDivider();
            std::cout << "Enter the " << i << ". answer: Out of: " << parameter << std::endl;
            std::getline(std::cin, tmp);
            if (!std::cin.good()) return;
            answers.insert(tmp);
        }

    }
}

void TextAnswer::LoadAnswer(const int &max) {
    Answer::LoadAnswer(max);
}

void TextAnswer::Print(const int &parameter) const {
    if (parameter == 2) {
        for (const auto &item :answers) {
            std::cout << item << std::endl;
        }
    } else {
        std::cout << answer_text[0] << std::endl;
    }
}

bool TextAnswer::areEqual(std::shared_ptr<Answer> object) {
    return getAnswerText() == object->getAnswerText() && getAnswers() == object->getAnswers();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


SolveAnswer::SolveAnswer() {
    result = 0;
}


void SolveAnswer::LoadAnswer() {
    std::cout << "Enter the answer:" << std::endl << "Example: \"x=(5y-2)/3\"" << std::endl;
    std::string tmp;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    answer_text.push_back(tmp);
}


void SolveAnswer::Answering(const int &parameter) {
    if (parameter == 1) {
        printDivider();
        LoadAnswer();
    } else {
        printDivider();
        std::cout << "Enter the correct numerical result:" << std::endl;
        printDivider();
        result = DoubleEnter();
    }
}

void SolveAnswer::LoadAnswer(const int &max) {
    Answer::LoadAnswer(max);
}

void SolveAnswer::Print(const int &parameter) const {
    if (parameter == 0) {
        std::cout.precision(6);
        std::cout << std::fixed << result << std::endl;

    } else {
        std::cout << answer_text[0] << std::endl;
    }
}

bool SolveAnswer::areEqual(std::shared_ptr<Answer> object) {
    return getAnswerText() == object->getAnswerText() && getResult() == object->getResult();
}


SolveAnswer::~SolveAnswer() = default;
