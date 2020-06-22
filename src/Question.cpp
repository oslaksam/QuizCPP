#include "Question.h"


Question::~Question() = default;

void Question::Create() {

}

void Question::Print() const {

}

Question::Question() {
    parameterA = 0;
    parameterB = 0;
    answered = false;
    correct_answer = std::make_shared<Answer>();
    answer = std::make_shared<Answer>();
}

std::vector<std::string> &Question::getQuestionText() {
    return question_text;
}


const int &Question::getParameterA() const {
    return parameterA;
}


const int &Question::getParameterB() const {
    return parameterB;
}

void Question::setParameterB(const int &parameterB) {
    Question::parameterB = parameterB;
}

const bool &Question::isAnswered() const {
    return answered;
}

void Question::setAnswered(const bool &answered) {
    Question::answered = answered;
}

std::shared_ptr<Answer> Question::getCorrectAnswer() {
    return correct_answer;
}

std::shared_ptr<Answer> Question::getAnswer() {
    return answer;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
MultipleChoice_Question::MultipleChoice_Question() {
    parameterA = 1;
    parameterB = 0;
    answered = false;
    correct_answer = std::make_shared<MultipleChoice_Answer>();
    answer = std::make_shared<MultipleChoice_Answer>();

}

MultipleChoice_Question::~MultipleChoice_Question() = default;


void MultipleChoice_Question::Create() {
    clearScreen();
    printBorder();
    std::cout << "Enter your question:" << std::endl << "Example: What is the currency of the UK?" << std::endl;
    std::string tmp;
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    printDivider();
    std::cout << "Enter the first choice" << std::endl << "Example: What is the currency of the UK?" << std::endl
              << "Your answer:\"1.Euro\"" << std::endl;
    while (true) {
        printDivider();
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return;
        if (!startsWith(tmp, "1.")) {
            std::cout << "Please enter the answer with the correct syntax." << std::endl;
            Wait(1000);
            continue;
        }
        break;
    }
    question_text.push_back(tmp);
    printDivider();
    std::cout << "Enter the second choice" << std::endl << "Example: What is the currency of the UK?" << std::endl
              << "Your answer:\"2.Pound\"" << std::endl;
    while (true) {
        printDivider();
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return;
        if (!startsWith(tmp, "2.")) {
            std::cout << "Please enter the answer with the correct syntax." << std::endl;
            Wait(1000);
            continue;
        }
        break;
    }
    question_text.push_back(tmp);
    int index = 3;
    while (true) {
        printDivider();
        std::cout << "Enter the " << index << ". choice or end by entering a blank line" << std::endl;
        while (true) {
            printDivider();
            std::getline(std::cin, tmp);
            if (!std::cin.good()) return;
            if (tmp == "") break;
            std::string dmp;
            dmp.append(std::to_string(index));
            dmp.append(".");
            if (!startsWith(tmp, dmp)) {
                std::cout << "Please enter the answer with the correct syntax." << std::endl;
                Wait(1000);
                continue;
            }
            break;
        }
        if (tmp == "") break;
        question_text.push_back(tmp);
        index++;
    }
    int max = int(question_text.size() - 1);
    int option = -1;
    while (true) {
        printDivider();
        std::cout << "Select how many answers do you want to have: " << std::endl;
        printOptions();
        std::cout << "1)One correct answer" << std::endl
                  << "2)More correct answers" << std::endl;
        printDivider();
        std::cout << "  Enter your choice (1/2)  " << std::endl;
        printDivider();
        option = IntegerEnter();
        if (option == INT32_MAX) return;
        if (option == 1 || option == 2) break;
        printWrong();
        Wait(1000);
    }
    printDivider();
    correct_answer = std::make_shared<MultipleChoice_Answer>();
    if (option == 1) {
        correct_answer->LoadAnswer(max);
    } else {
        parameterB = 1;
        int index = 1;
        int input;
        minijump:
        printDivider();
        std::cout << "Enter the " << index << ". answer." << std::endl;
        printDivider();
        input = IntegerEnter();
        if (input == INT32_MAX) return;
        if (input == 0 || input > max) {
            std::cout << "This is not the correct input. Please try again " << std::endl;
            goto minijump;
        }
        correct_answer->getAnswers().insert(std::to_string(input));
        index++;
        while (true) {
            printDivider();
            std::cout << "Enter the " << index
                      << ". answer or end by entering blank line." << std::endl;
            printDivider();
            getline(std::cin, tmp);
            if (!std::cin.good()) return;
            while (!Parse(tmp, input) || input <= 0 || input > max ||
                   (std::count(correct_answer->getAnswers().begin(), correct_answer->getAnswers().end(),
                               std::to_string(input)))) {
                if (tmp == "") break;
                std::cout << "This is not the correct input. Please try again " << std::endl;
                if (!std::cin.good()) return;
                getline(std::cin, tmp);
                if (!std::cin.good()) return;
            }
            if (tmp == "") break;
            correct_answer->getAnswers().insert(std::to_string(input));
            index++;
        }
    }
}

void MultipleChoice_Question::Print() const {
    std::cout << question_text[0] << std::endl;
    for (long unsigned int i = 1; i < question_text.size(); ++i) {
        std::cout << "-=x=-=x=->>> " << question_text[i] << std::endl;
    }
}


MultipleChoice_Question::MultipleChoice_Question(const MultipleChoice_Question &MultipleChoice_Question) {
    answer = MultipleChoice_Question.answer;
    correct_answer = MultipleChoice_Question.correct_answer;
    question_text = MultipleChoice_Question.question_text;

}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
ABCD_Question::ABCD_Question() {
    parameterA = 2;
    parameterB = 0;
    answered = false;
    correct_answer = std::make_shared<ABCD_Answer>();
    answer = std::make_shared<ABCD_Answer>();
}

ABCD_Question::~ABCD_Question() = default;


void ABCD_Question::Create() {
    clearScreen();
    printBorder();
    std::cout << "Enter your question:" << std::endl << "Example: What is the currency of the UK?" << std::endl;
    printDivider();
    std::string tmp;
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    printDivider();
    std::cout << "Enter choice A" << std::endl << "Example: What is the currency of the UK?" << std::endl
              << "Your answer:\"Euro\"" << std::endl;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    printDivider();
    std::cout << "Enter choice B" << std::endl << "Example: What is the currency of the UK?" << std::endl
              << "Your answer:\"Pound\"" << std::endl;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    printDivider();
    std::cout << "Enter choice C" << std::endl << "Example: What is the currency of the UK?" << std::endl
              << "Your answer:\"Shekel\"" << std::endl;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    printDivider();
    std::cout << "Enter choice D" << std::endl << "Example: What is the currency of the UK?" << std::endl
              << "Your answer:\"DingDongBingBong\"" << std::endl;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    printDivider();
    correct_answer = std::make_shared<ABCD_Answer>();
    correct_answer->LoadAnswer();
}

ABCD_Question::ABCD_Question(const ABCD_Question &other) {
    answer = other.answer;
    correct_answer = other.correct_answer;
    question_text = other.question_text;
}


void ABCD_Question::Print() const {
    std::cout << question_text[0] << std::endl;
    std::cout << ".:*~*:. A .:*~*:.: " << question_text[1] << std::endl;
    std::cout << ".:*~*:. B .:*~*:.: " << question_text[2] << std::endl;
    std::cout << ".:*~*:. C .:*~*:.: " << question_text[3] << std::endl;
    std::cout << ".:*~*:. D .:*~*:.: " << question_text[4] << std::endl;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
YES_NO_Question::YES_NO_Question() {
    parameterA = 3;
    parameterB = 0;
    answered = false;
    correct_answer = std::make_shared<YES_NO_Answer>();
    answer = std::make_shared<YES_NO_Answer>();
}

YES_NO_Question::~YES_NO_Question() = default;


void YES_NO_Question::Create() {
    clearScreen();
    printBorder();
    std::cout << "Enter your question:" << std::endl;
    printDivider();
    std::string tmp;
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    printDivider();
    correct_answer = std::make_shared<YES_NO_Answer>();
    correct_answer->LoadAnswer();
}


YES_NO_Question::YES_NO_Question(const YES_NO_Question &other) {
    answer = other.answer;
    correct_answer = other.correct_answer;
    question_text = other.question_text;
}

void YES_NO_Question::Print() const {
    std::cout << question_text[0] << std::endl;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
SortQuestion::SortQuestion() {
    parameterA = 4;
    parameterB = 0;
    answered = false;
    correct_answer = std::make_shared<SortAnswer>();
    answer = std::make_shared<SortAnswer>();
}

SortQuestion::~SortQuestion() = default;

void SortQuestion::Create() {
    clearScreen();
    printBorder();
    std::cout << "Enter your question." << std::endl
              << "Example: How are these inventions ordered from the oldest to the newest?" << std::endl;
    printDivider();
    std::string tmp;
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    printBorder();
    std::cout << "Enter the first choice" << std::endl
              << "How are these inventions ordered from the oldest to the newest?" << std::endl
              << "Your answer:\"1.Internet\"" << std::endl;
    while (true) {
        printDivider();
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return;
        if (!startsWith(tmp, "1.")) {
            std::cout << "Please enter the answer with the correct syntax." << std::endl;
            Wait(1000);
            continue;
        }
        break;
    }
    question_text.push_back(tmp);
    printDivider();
    std::cout << "Enter the second choice" << std::endl << "Example: What is the currency of the UK?" << std::endl
              << "Your answer:\"2.Light bulb\"" << std::endl;
    while (true) {
        printDivider();
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return;
        if (!startsWith(tmp, "2.")) {
            std::cout << "Please enter the answer with the correct syntax." << std::endl;
            Wait(1000);
            continue;
        }
        break;
    }
    question_text.push_back(tmp);
    int index = 3;
    while (true) {
        printDivider();
        std::cout << "Enter the " << index << ". choice or end by entering a blank line" << std::endl;
        while (true) {
            printDivider();
            std::getline(std::cin, tmp);
            if (!std::cin.good()) return;
            if (tmp == "") break;
            std::string dmp;
            dmp.append(std::to_string(index));
            dmp.append(".");
            if (!startsWith(tmp, dmp)) {
                std::cout << "Please enter the answer with the correct syntax." << std::endl;
                Wait(1000);
                continue;
            }
            break;
        }
        if (tmp == "") break;
        question_text.push_back(tmp);
        index++;
    }
    int max = int(question_text.size()) - 1;
    printDivider();
    correct_answer = std::make_shared<SortAnswer>();
    correct_answer->LoadAnswer(max);
}

SortQuestion::SortQuestion(const SortQuestion &other) {
    answer = other.correct_answer;
    correct_answer = other.correct_answer;
    question_text = other.question_text;

}

void SortQuestion::Print() const {
    std::cout << question_text[0] << std::endl;
    for (long unsigned int i = 1; i < question_text.size(); ++i) {
        std::cout << "_.--.__.-'->>> " << question_text[i] << std::endl;
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
TextAnswerQuestion::TextAnswerQuestion() {
    parameterA = 5;
    parameterB = 0;
    answered = false;
    correct_answer = std::make_shared<TextAnswer>();
    answer = std::make_shared<TextAnswer>();
}

TextAnswerQuestion::~TextAnswerQuestion() = default;


void TextAnswerQuestion::Create() {
    clearScreen();
    printBorder();
    std::cout << "Enter your question." << std::endl << "Example: In what year was the dishwasher invented?"
              << std::endl;
    printDivider();
    std::string tmp;
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);
    int option = -1;
    while (true) {
        printDivider();
        std::cout << "Select the type of answer:" << std::endl;
        printOptions();
        std::cout << "  1) One correct answer." << std::endl <<
                  "  2) Word that the answer needs to contain." << std::endl <<
                  "  3) Set of answers." << std::endl;
        printDivider();
        option = IntegerEnter();
        if (option == INT32_MAX) return;
        if (option == 1 || option == 2 || option == 3) {
            break;
        }
        printWrong();
        Wait(1000);
    }
    correct_answer = std::make_shared<TextAnswer>();
    printDivider();
    if (option == 1) {
        correct_answer->LoadAnswer();
    } else if (option == 2) {
        parameterB = 1;
        std::cout << "Enter the word that the answer needs to contain." << std::endl;
        std::string tmp;
        printDivider();
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return;
        printDivider();
        correct_answer->getAnswerText().push_back(tmp);
    } else {
        parameterB = 2;
        int index = 1;
        std::cout << "Enter the " << index << ". answer." << std::endl;
        printDivider();
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return;
        printDivider();
        correct_answer->getAnswers().insert(tmp);
        index++;
        while (true) {
            printDivider();
            std::cout << "Enter the " << index
                      << ". answer or end by entering blank line." << std::endl;
            printDivider();
            std::getline(std::cin, tmp);
            if (!std::cin.good()) return;
            if (tmp == "") break;
            correct_answer->getAnswers().insert(tmp);
            index++;
        }
    }

}

TextAnswerQuestion::TextAnswerQuestion(const TextAnswerQuestion &TextAnswerQuestion) {
    answer = TextAnswerQuestion.answer;
    correct_answer = TextAnswerQuestion.correct_answer;
    question_text = TextAnswerQuestion.question_text;

}

void TextAnswerQuestion::Print() const {
    std::cout << question_text[0] << std::endl;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
SolveQuestion::SolveQuestion() {
    parameterA = 6;
    parameterB = 0;
    answered = false;
    correct_answer = std::make_shared<SolveAnswer>();
    answer = std::make_shared<SolveAnswer>();
}

SolveQuestion::~SolveQuestion() = default;


void SolveQuestion::Create() {
    clearScreen();
    printBorder();
    std::cout << "Enter your question." << std::endl << "Example: 1+25/546+9999999-55555+420 is equal to?" << std::endl;
    std::string tmp;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    question_text.push_back(tmp);

    int option = -1;
    while (true) {
        printBorder();
        std::cout << "Select the type of answer:" << std::endl;
        printOptions();
        std::cout << "  1) Numerical " << "Example: \"42.1\"" << std::endl <<
                  "  2) Text answer " << "Example: \"x=(5y-1)/2\"" << std::endl;
        printDivider();
        std::cout << "  Enter your choice (1/2)  " << std::endl;
        printDivider();
        option = IntegerEnter();
        if (option == INT32_MAX) return;
        if (option == 1 || option == 2) {
            break;
        }
        printWrong();
        Wait(1000);
    }
    correct_answer = std::make_shared<SolveAnswer>();
    printDivider();
    if (option == 1) {
        std::cout << "Enter the numerical result." << std::endl;
        double res = DoubleEnter();
        if (res == INT32_MAX) return;
        correct_answer->setResult(res);
    } else {
        parameterB = 1;
        correct_answer->LoadAnswer();
    }
}


SolveQuestion::SolveQuestion(const SolveQuestion &SolveQuestion) {
    answer = SolveQuestion.answer;
    correct_answer = SolveQuestion.correct_answer;
    question_text = SolveQuestion.question_text;

}


void SolveQuestion::Print() const {
    std::cout << question_text[0] << std::endl;
}
