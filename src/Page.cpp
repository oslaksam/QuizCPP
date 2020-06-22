#include "Page.h"

Page::Page() {
    questions_on_page = 0;
    max_question_on_page = 0;
    current_question = 0;
    number_of_answered_quest = 0;
}


Page::Page(const int &number_of_questions, const int &max_num_question) {
    questions_on_page = number_of_questions;
    max_question_on_page = max_num_question;
    current_question = 0;
    number_of_answered_quest = 0;
    for (int i = 0; i < max_num_question; i++) {
        //Initialization of dummy questions preventing memory crashes
        auto q = std::make_shared<Question>();
        questions.push_back(q);
    }
}

Page::~Page() = default;

Page::Page(const Page &other) {
    max_question_on_page = other.max_question_on_page;
    questions_on_page = other.questions_on_page;
    current_question = other.current_question;
    number_of_answered_quest = other.number_of_answered_quest;
    questions = other.questions;
}

Page &Page::operator=(const Page &other) {
    this->max_question_on_page = other.max_question_on_page;
    this->questions_on_page = other.questions_on_page;
    this->current_question = other.current_question;
    this->questions = other.questions;
    number_of_answered_quest = other.number_of_answered_quest;
    return (*this);
}

void Page::ShowQuestions() {
    for (int i = 0; i < max_question_on_page; i++) {
        std::cout << R"(/__\/__\/__\/__\ )" << "Questions number: " << (i + 1) << R"( /__\/__\/__\/__\)"
                  << std::endl;
        ShowQuestion(i);
    }

}


void Page::CreateQuestion() {
    int option = -1;
    while (true) {
        clearScreen();
        printBorder();
        printOptions();
        std::cout << "     1) Multiple choice Question " << std::endl;
        std::cout << "     2) ABCD Question" << std::endl;
        std::cout << "     3) YES or NO Question" << std::endl;
        std::cout << "     4) Sort Question" << std::endl;
        std::cout << "     5) Text answer Question" << std::endl;
        std::cout << "     6) Solve Question" << std::endl;
        printDivider();
        std::cout << "     Enter your choice (0/1/2/3/4/5/6)  " << std::endl;
        printDivider();
        option = IntegerEnter();
        if (option == INT32_MAX) return;
        auto it = questions.begin() + current_question;
        std::cout << "Current question " << current_question << std::endl;
        if (option == 1) {
            auto question = std::make_shared<MultipleChoice_Question>();
            question->Create();
            questions.insert(it, question);
        } else if (option == 2) {
            auto question = std::make_shared<ABCD_Question>();
            question->Create();
            questions.insert(it, question);
        } else if (option == 3) {
            auto question = std::make_shared<YES_NO_Question>();
            question->Create();
            questions.insert(it, question);
        } else if (option == 4) {
            auto question = std::make_shared<SortQuestion>();
            question->Create();
            questions.insert(it, question);
        } else if (option == 5) {
            auto question = std::make_shared<TextAnswerQuestion>();
            question->Create();
            questions.insert(it, question);
        } else if (option == 6) {
            auto question = std::make_shared<SolveQuestion>();
            question->Create();
            questions.insert(it, question);
        } else {
            printWrong();
            Wait(2000);
            continue;
        }
        std::cout << "Question created " << std::endl;
        questions_on_page++;
        Wait(1000);
        return;
    }
}

void Page::DeleteQuestion(const int &index) {
    //Dummy questions in order for the program not to crash for touching uninitialized memory
    auto question = std::make_shared<Question>();
    //Replace the old value with an empty value
    questions.at(index) = question;
    questions_on_page--;
}

void Page::ShowQuestion(const int &index) {
    questions.at(index)->Print();
}


void Page::SelectMenu(const int &index) {
    int option = -1;
    while (true) {
        clearScreen();
        printBorder();
        std::cout << "Question:" << std::endl;
        ShowQuestion(index);
        printDivider();
        printOptions();
        if (!questions[index]->getQuestionText().empty()) {
            //This will be shown if the question on this index is already created
            std::cout << "     1) Show the correct answer " << std::endl;
            std::cout << "     2) Delete question" << std::endl;
            std::cout << "     0) Back" << std::endl << std::endl;
            printDivider();
            std::cout << "     Enter your choice (0/1/2)  " << std::endl;
            printDivider();
            option = IntegerEnter();
            if (option == INT32_MAX) return;
            switch (option) {
                case (1):
                    ShowCorrectAnswer(index);
                    break;
                case (2):
                    DeleteQuestion(index);
                    break;
                case (0):
                    return; // returns to the main menu
                default:
                    printWrong();
                    break;
            }
        } else {
            //This will show if the question on this index is not yet created
            std::cout << "     1) Create Question" << std::endl;
            std::cout << "     0) Back" << std::endl << std::endl;
            printDivider();
            std::cout << "     Enter your choice (0/1)  " << std::endl;
            printDivider();
            option = IntegerEnter();
            if (option == INT32_MAX) return;
            switch (option) {
                case (1):
                    CreateQuestion();
                    break;
                case (0):
                    return; // Returns to the question selection menu
                default:
                    //Wrong input handling
                    printWrong();
                    Wait(1000);
                    break;
            }
        }

    }

}

void Page::DeleteAnswer(const int &index) {
    //int parameterA = getQuestions()[index]->getParameterA();
    getQuestions()[index]->getAnswer()->Clear();

    getQuestions()[index]->setAnswered(false);
    number_of_answered_quest--;
}

void Page::Answer(const int &index) {
    int parameterA = questions[index]->getParameterA();
    int parameterB = questions[index]->getParameterB();
    if (parameterA == 0) {
        std::cout << "There is no question here for you to answer :)." << std::endl;
        Wait(1000);
        return;
    } else if (parameterA == 1) {
        if (parameterB == 0) {
            const auto &argument = getQuestions()[index]->getQuestionText().size() - 1;
            getQuestions()[index]->getAnswer()->Answering(0, argument);
        } else {
            const auto &argument =
                    getQuestions()[index]->getQuestionText().size() - 1;
            getQuestions()[index]->getAnswer()->Answering(
                    argument, 0);
        }

    } else if (parameterA == 2 || parameterA == 3) {
        getQuestions()[index]->getAnswer()->Answering(0);
    } else if (parameterA == 4) {
        const auto &argument = getQuestions()[index]->getCorrectAnswer()->getAnswerText().size();
        getQuestions()[index]->getAnswer()->Answering(argument);
    } else if (parameterA == 5) {
        if (parameterB == 0) {
            getQuestions()[index]->getAnswer()->Answering(0);
        } else if (parameterB == 1) {
            getQuestions()[index]->getAnswer()->Answering(1);
        } else {
            const auto &argument = getQuestions()[index]->getCorrectAnswer()->getAnswers().size();
            getQuestions()[index]->getAnswer()->Answering(argument);
        }
    } else {
        if (parameterB == 0) {
            getQuestions()[index]->getAnswer()->Answering(0);
        } else {
            getQuestions()[index]->getAnswer()->Answering(1);
        }
    }
    getQuestions()[index]->setAnswered(true);
    number_of_answered_quest++;
}


void Page::ShowAnswer(const int &index) {
    int parameterA = questions[index]->getParameterA();
    int parameterB = questions[index]->getParameterB();
    printDivider();
    std::cout << "Your answer:" << std::endl;
    printDivider();
    if (parameterA == 0) return;
    getQuestions()[index]->getAnswer()->Print(parameterB);
    printDivider();
    continueByEnter();
}


void Page::AnswerMenu(const int &index) {
    int option = -1;
    while (true) {
        clearScreen();
        printBorder();
        ShowQuestion(index);
        printDivider();
        printOptions();
        if (questions[index]->isAnswered()) {
            //This will be shown if the question on this index is already created
            std::cout << "     1) Show answer " << std::endl;
            std::cout << "     2) Delete answer" << std::endl;
            std::cout << "     0) Back" << std::endl << std::endl;
            printDivider();
            std::cout << "     Enter your choice (0/1/2)  " << std::endl;
            printDivider();
            option = IntegerEnter();
            if (option == INT32_MAX) return;
            switch (option) {
                case (1):
                    ShowAnswer(index);
                    break;
                case (2):
                    DeleteAnswer(index);
                    break;
                case (0):
                    return; // returns to the main menu
                default:
                    printWrong();
                    Wait(2000);
                    break;
            }
        } else {
            //This will show if the question on this index is not yet created
            std::cout << "     1) Answer the question" << std::endl;
            std::cout << "     0) Back" << std::endl << std::endl;
            printDivider();
            std::cout << "     Enter your choice (0/1)  " << std::endl;
            printDivider();
            option = IntegerEnter();
            if (option == INT32_MAX) return;
            switch (option) {
                case (1):
                    Answer(index);
                    break;
                case (0):
                    return; // Returns to the question selection menu
                default:
                    //Wrong input handling
                    printWrong();
                    Wait(2000);
                    break;
            }
        }

    }

}

/**
 * This function will Select the question on current page to be created or edited
 */
void Page::QuestionSelector(const int &type) {
    int option = -1;
    while (true) {
        clearScreen();
        std::cout << " Current Question: " << (current_question + 1) << std::endl;
        printDivider();
        printOptions();
        std::cout << "     1) Select Question" << std::endl;
        std::cout << "     2) Next Question " << std::endl;
        std::cout << "     3) Previous Question" << std::endl;
        std::cout << "     0) Back" << std::endl << std::endl;
        printDivider();
        std::cout << "     Enter your choice (0/1/2/3)  " << std::endl;
        printDivider();
        option = IntegerEnter();
        if (option == INT32_MAX) return;
        switch (option) {
            case (1):
                if (type == 0) {
                    SelectMenu(current_question);
                } else {
                    AnswerMenu(current_question);
                }
                break;
            case (2):
                if (current_question == (max_question_on_page - 1))
                    break; // Does not increment the current question at this point
                current_question++;
                break;
            case (3):
                if (current_question == 0) break; // Does not decrement at this point
                current_question--;
                break;
            case (0):
                return; // returns to the main menu
            default:
                clearScreen();
                printWrong();
                Wait(2000);
                break;
        }

    }


}

void Page::setQuestionsOnPage(const int &questionsOnPage) {
    questions_on_page = questionsOnPage;
}

void Page::setMaxQuestionOnPage(const int &maxQuestionOnPage) {
    max_question_on_page = maxQuestionOnPage;
}

int Page::getQuestionsOnPage() const {
    return questions_on_page;
}

int Page::getMaxQuestionOnPage() const {
    return max_question_on_page;
}

void Page::setCurrentQuestion(const int &currentQuestion) {
    current_question = currentQuestion;
}

std::vector<std::shared_ptr<Question>> &Page::getQuestions() {
    return questions;
}

int Page::getNumberOfAnsweredQuestions() const {
    return number_of_answered_quest;
}

void Page::ShowCorrectAnswer(const int &index) {
    int parameterA = questions[index]->getParameterA();
    int parameterB = questions[index]->getParameterB();
    printDivider();
    std::cout << "The correct answer:" << std::endl;
    if (parameterA == 0) return;
    getQuestions()[index]->getCorrectAnswer()->Print(parameterB);
    printDivider();
    continueByEnter();
}
















