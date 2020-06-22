#include "Quiz.h"

Quiz::Quiz() : number_of_pages(0), current_page(0), view_quest(0), number_of_questions(0),
               number_of_answered_questions(0), number_of_correct_questions(0) {
}

Quiz::~Quiz() = default;


void Quiz::update() {
    number_of_questions = 0;
    number_of_answered_questions = 0;
    //Loop through pages and get the number of quests in them
    for (const auto &page: pages) {
        number_of_questions += page->getQuestionsOnPage();
        number_of_answered_questions += page->getNumberOfAnsweredQuestions();
    }
    number_of_pages = pages.size();
}


std::shared_ptr<Quiz> Quiz::CreateQuiz() {
    int page_limit;
    auto quiz = std::make_shared<Quiz>();
    std::string tmp;
    clearScreen();
    printBorder();
    std::cout
            << "Enter the name of your quiz:" << std::endl <<
            "(If you are creating a sequential quiz name the quiz's after the answers to the sequential question)"
            << std::endl;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good() || tmp == "") return nullptr;
    quiz->name = tmp;
    printDivider();
    std::cout << "Enter how many questions should be viewed on one page:" << std::endl;
    printDivider();
    page_limit = IntegerEnter();
    if (page_limit == 0 || page_limit == INT32_MAX) {
        std::cout << "NO." << std::endl;
        Wait(2000);
        return nullptr;
    }
    quiz->view_quest = page_limit;
    int option = -1;
    //Create the first page
    auto new_page = std::make_shared<Page>(0, page_limit);
    quiz->pages.push_back(new_page);
    quiz->number_of_pages++;

    while (true) {
        clearScreen();
        printBorder();
        //Updating after creating or deleting questions
        quiz->update();
        auto it = quiz->pages.begin() + quiz->current_page;
        if (quiz->current_page >= int(quiz->pages.size())) {
            std::cout << "Creating a new page" << std::endl;
            auto new_page = std::make_shared<Page>(0, page_limit);
            quiz->pages.insert(it, new_page);
            quiz->number_of_pages++;
        }
        auto &current_page = quiz->pages.at(quiz->current_page);
        std::cout << "Name:" << quiz->getName() << std::endl;
        std::cout << "Number of Questions:"
                  << quiz->number_of_questions
                  << " " << "Number of Pages :" << quiz->number_of_pages << std::endl;
        std::cout << " Current page:" << (quiz->current_page + 1) << std::endl;
        printRepeating();
        std::cout << "     5) Done" << std::endl;

        if (quiz->current_page > 0 && quiz->current_page == (quiz->number_of_pages - 1)) {
            std::cout << "     6) Delete this page" << std::endl;
            std::cout << "     0) Back" << std::endl << std::endl;
            printDivider();
            std::cout << "     Enter your choice (0/1/2/3/4/5/6)  " << std::endl;
        } else {
            std::cout << "     0) Back" << std::endl << std::endl;
            printDivider();
            std::cout << "     Enter your choice (0/1/2/3/4/5)  " << std::endl;
        }
        option = IntegerEnter();
        if (option == INT32_MAX) return nullptr;
        switch (option) {
            case (2):
                //Move one position forward in the pages vector
                quiz->current_page++;
                break;
            case (3):
                //Move one position backwards in the pages vector
                if (quiz->current_page == 0) {
                    quiz->current_page = 1;
                }
                quiz->current_page--;
                break;
            case (1):
                //Will select questions on current page
                current_page->QuestionSelector();
                break;
            case (4):
                current_page->ShowQuestions();
                continueByEnter();
                break;
            case (6):
                it = quiz->pages.begin() + quiz->current_page;
                if (it == quiz->pages.begin()) {
                    std::cout << "You cant just delete this one and only page." << std::endl;
                    Wait(1000);
                    break;
                }
                quiz->pages.erase(it);
                quiz->number_of_pages--;
                quiz->current_page--;
                break;
            case (5):
                if (current_page->getQuestionsOnPage() == 0 || quiz->number_of_questions == 0) {
                    std::cout << "The Quiz is incomplete please finish filling it." << std::endl;
                    Wait(2000);
                    break;
                }
                clearScreen();
                printBorder();
                std::cout << "Exiting  with successfully  with a new Quiz." << std::endl;
                quiz->current_page = 0;
                for (int i = 0; i < quiz->number_of_pages; i++) {
                    quiz->pages[i]->setCurrentQuestion(0);
                }
                Wait(2000);
                return quiz;
            case (0):
                clearScreen();
                std::cout << "Are you sure about that? Your progress will be lost and nothing will be created."
                          << std::endl << "Answer yes or y if you are sure." << std::endl;
                getline(std::cin, tmp);
                if (CaseInsensitiveEquals(tmp, "yes") || CaseInsensitiveEquals(tmp, "y") || !std::cin.good()) {
                    return nullptr; // Returns to the main menu without creating anything
                }
                break; // If not sure shows the page menu again
            default:
                //Wrong input handling
                clearScreen();
                printBorder();
                printWrong();
                Wait(1000);
                break;
        }
    }

}


void Quiz::SaveQuiz(bool seq, const std::string &pathway) {
    std::ofstream file;
    std::string filename;
    //Boolean seq - true if it carries the pathway from the sequential quiz
    //It will save every individual Quiz into that file one by one
    if (seq) {
        filename = pathway;
    } else {
        filename = "examples/saves/";
        if (!std::filesystem::exists(filename)) {
            std::cout << "The folder does not exist" << std::endl;
            Wait(1000);
            return;
        }
        filename.append(name);
        AppendTime(filename);
        filename.append(".txt");
    }
    // Prints various components of the structure.
    file.open(filename, std::ios_base::app);
    file << name << std::endl;
    file << current_page << std::endl;
    file << number_of_questions << std::endl;
    file << number_of_pages << std::endl;
    file << view_quest << std::endl;
    for (int i = 0; i < number_of_pages; ++i) {
        file << "-|" << std::endl;
        //Info about pages
        file << pages[i]->getQuestionsOnPage() << std::endl;
        file << pages[i]->getMaxQuestionOnPage() << std::endl;
        for (int j = 0; j < view_quest; ++j) {
            file << "--|" << std::endl;
            file << pages[i]->getQuestions()[j]->getParameterA() << std::endl;
            if (pages[i]->getQuestions()[j]->getParameterA() == 1) {
                //This will save the size of the content
                file << pages[i]->getQuestions()[j]->getQuestionText().size() << std::endl;
                for (const auto &text : pages[i]->getQuestions()[j]->getQuestionText()) {
                    file << text << std::endl;
                }
                //Print parameterB
                file << pages[i]->getQuestions()[j]->getParameterB() << std::endl;
                if (pages[i]->getQuestions()[j]->getParameterB() == 1) {
                    //This will print the size of the set
                    file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswers().size() << std::endl;
                    for (const auto &ans : pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswers()) {
                        file << ans << std::endl;
                    }
                } else {
                    file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswerText()[0] << std::endl;
                }
            }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
            else if (pages[i]->getQuestions()[j]->getParameterA() == 2) {
                //5 lines
                for (const auto &text :
                        pages[i]->getQuestions()[j]->getQuestionText()) {
                    file << text << std::endl;
                }
                file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswerText()[0] << std::endl;
            }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
            else if (pages[i]->getQuestions()[j]->getParameterA() == 3) {
                //one line
                for (const auto &text :
                        pages[i]->getQuestions()[j]->getQuestionText()) {
                    file << text << std::endl;
                }
                file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswerText()[0] << std::endl;
            }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
            else if (pages[i]->getQuestions()[j]->getParameterA() == 4) {
                //This will save the size of the content
                file << pages[i]->getQuestions()[j]->getQuestionText().size() << std::endl;
                for (const auto &text : pages[i]->getQuestions()[j]->getQuestionText()) {
                    file << text << std::endl;
                }
                //This will print the size of the answer text
                file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswerText().size() << std::endl;
                for (const auto &ans : pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswerText()) {
                    file << ans << std::endl;
                }
            }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
            else if (pages[i]->getQuestions()[j]->getParameterA() == 5) {
                for (const auto &text : pages[i]->getQuestions()[j]->getQuestionText()) {
                    file << text << std::endl;
                }
                //This will print the parameter
                file << pages[i]->getQuestions()[j]->getParameterB() << std::endl;
                if (pages[i]->getQuestions()[j]->getParameterB() == 1) {
                    file << (pages[i]->getQuestions()[j]->getCorrectAnswer())->getAnswerText()[0] << std::endl;
                } else if (pages[i]->getQuestions()[j]->getParameterB() == 2) {
                    //This will the size of the set
                    file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswers().size() << std::endl;
                    for (const auto &ans: pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswers()) {
                        file << ans << std::endl;
                    }
                } else {
                    file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswerText()[0] << std::endl;
                }
            }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
            else if (pages[i]->getQuestions()[j]->getParameterA() == 6) {
                //one line
                for (const auto &text : pages[i]->getQuestions()[j]->getQuestionText()) {
                    file << text << std::endl;
                }
                //This will print the parameter
                file << pages[i]->getQuestions()[j]->getParameterB() << std::endl;
                //This will decide how to load the answer
                if (pages[i]->getQuestions()[j]->getParameterB() == 1) {
                    file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswerText()[0] << std::endl;
                } else {
                    file << pages[i]->getQuestions()[j]->getCorrectAnswer()->getResult() << std::endl;
                }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
            } else {
                //Emtpy question do nothing
            }

        }
    }
    file.close();
}

std::shared_ptr<Quiz> Quiz::load_file(std::ifstream &file) {
    std::shared_ptr<Quiz> new_quiz = std::make_shared<Quiz>();
    if (file.is_open()) {
        try {
            std::string line;
            std::getline(file, line);
            new_quiz->name = line;
            std::getline(file, line);
            new_quiz->current_page = std::stoi(line);
            std::getline(file, line);
            new_quiz->number_of_questions = std::stoi(line);
            std::getline(file, line);
            new_quiz->number_of_pages = std::stoi(line);
            std::getline(file, line);
            new_quiz->view_quest = std::stoi(line);
            int index_page = 0;
            //Loading of pages
            while (index_page < new_quiz->number_of_pages) {
                std::getline(file, line);
                if (line != "-|") {
                    std::cout << "Error while loading the file." << line << std::endl;
                    Wait(2000);
                    return nullptr;
                }
                //This is where the fun begins
                new_quiz->pages.push_back(std::make_shared<Page>());
                //Read info about the page
                std::getline(file, line);
                new_quiz->pages[index_page]->setQuestionsOnPage(std::stoi(line));
                std::getline(file, line);
                new_quiz->pages[index_page]->setMaxQuestionOnPage(std::stoi(line));
                int index_question = 0;

                while (new_quiz->view_quest > index_question) {
                    std::getline(file, line);
                    if (line != "--|") {
                        std::cout << "Error while loading the file. " << line << std::endl;
                        Wait(2000);
                        return nullptr;
                    }

                    std::getline(file, line);
                    int type = std::stoi(line);

                    if (type == 0) {
                        auto question = std::make_shared<Question>();
                        new_quiz->pages[index_page]->getQuestions().push_back(question);
                    }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
                    else if (type == 1) {
                        auto question = std::make_shared<MultipleChoice_Question>();
                        int size; // size of question text
                        int parameter; // parameterB answer type
                        getline(file, line);
                        size = std::stoi(line);
                        for (int i = 0; i < size; ++i) {
                            getline(file, line);
                            question->getQuestionText().push_back(line);
                        }
                        getline(file, line);
                        parameter = std::stoi(line);
                        question->setParameterB(parameter);
                        getline(file, line);
                        if (parameter == 0) {
                            question->getCorrectAnswer()->getAnswerText().push_back(line);
                        } else {
                            int set_size;
                            set_size = std::stoi(line);
                            for (int a = 0; a < set_size; ++a) {
                                getline(file, line);
                                question->getCorrectAnswer()->getAnswers().insert(line);
                            }
                        }
                        new_quiz->pages[index_page]->getQuestions().push_back(question);
                    }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
                    else if (type == 2) {
                        auto question = std::make_shared<ABCD_Question>();
                        for (int a = 0; a < 5; ++a) {
                            getline(file, line);
                            question->getQuestionText().push_back(line);
                        }
                        getline(file, line);
                        question->getCorrectAnswer()->getAnswerText().push_back(line);
                        new_quiz->pages[index_page]->getQuestions().push_back(question);
                    }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
                    else if (type == 3) {
                        auto question = std::make_shared<YES_NO_Question>();
                        getline(file, line);
                        question->getQuestionText().push_back(line);
                        getline(file, line);
                        question->getCorrectAnswer()->getAnswerText().push_back(line);
                        new_quiz->pages[index_page]->getQuestions().push_back(question);

                    }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
                    else if (type == 4) {
                        auto question = std::make_shared<SortQuestion>();

                        int size; // size of question text
                        getline(file, line);
                        size = std::stoi(line);
                        for (int i = 0; i < size; ++i) {
                            getline(file, line);
                            question->getQuestionText().push_back(line);
                        }
                        //size answer
                        getline(file, line);
                        size = std::stoi(line);
                        for (int i = 0; i < size; ++i) {
                            getline(file, line);
                            question->getCorrectAnswer()->getAnswerText().push_back(line);
                        }
                        new_quiz->pages[index_page]->getQuestions().push_back(question);
                    }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
                    else if (type == 5) {
                        auto question = std::make_shared<TextAnswerQuestion>();
                        int parameter; // parameterB answer type
                        getline(file, line);
                        question->getQuestionText().push_back(line);
                        getline(file, line);
                        parameter = std::stoi(line);
                        question->setParameterB(parameter);
                        getline(file, line);
                        if (parameter == 0) {
                            question->getCorrectAnswer()->getAnswerText().push_back(line);
                        } else if (parameter == 1) {
                            question->getCorrectAnswer()->getAnswerText().push_back(line);
                        } else {
                            int set_size;
                            set_size = std::stoi(line);
                            for (int a = 0; a < set_size; ++a) {
                                getline(file, line);
                                question->getCorrectAnswer()->getAnswers().insert(line);
                            }
                        }
                        new_quiz->pages[index_page]->getQuestions().push_back(question);
                    }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
                    else {
                        auto question = std::make_shared<SolveQuestion>();
                        int parameter; // parameterB answer type
                        getline(file, line);
                        question->getQuestionText().push_back(line);
                        getline(file, line);
                        parameter = std::stoi(line);
                        question->setParameterB(parameter);
                        getline(file, line);
                        if (parameter == 1) {
                            question->getCorrectAnswer()->getAnswerText().push_back(line);
                        } else {
                            question->getCorrectAnswer()->setResult(std::stod(line));
                        }
                        new_quiz->pages[index_page]->getQuestions().push_back(question);
                    }
                    index_question++;
                }
                index_page++;
            }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
        } catch (std::invalid_argument &) {
            std::cout << "Error with the file." << std::endl;
            Wait(2000);
            return nullptr;
        }
    }
    return new_quiz;
}

std::shared_ptr<Quiz> Quiz::LoadQuiz() {
    printBorder();
    std::ifstream file;
    std::shared_ptr<Quiz> new_quiz = std::make_shared<Quiz>();
    std::string path = "examples/saves/";
    if (!std::filesystem::exists(path)) {
        std::cout << "The folder does not exist" << std::endl;
        Wait(1000);
        return nullptr;
    }
    std::map<int, std::string> files;
    int index = 0;
    clearScreen();
    printBorder();
    std::cout << "Choose your quiz that needs to load" <<
              std::endl;
    printOptions();
    printDivider();
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::cout << index << ". " << entry.path() << std::endl;
        std::string tmp;
        tmp.append(entry.path());
        files.insert(std::make_pair(index, tmp));
        index++;
    }
    index--;
    printDivider();
    if (files.empty()) {
        std::cout << "The folder with saves is empty." << std::endl;
        Wait(2000);
        return nullptr;
    }
    printDivider();
    std::cout << "       Enter your choice (0/1/...)" << std::endl;
    printDivider();
    int choice = IntegerEnter();
    if (choice == INT32_MAX) return nullptr;
    if (choice > index) {
        clearScreen();
        printBorder();
        std::cout << "Pick from the list :)" << std::endl;
        printWrong();
        Wait(2000);
        return nullptr;
    }
    //Open the selected file
    file.open(files.at(choice));
    new_quiz = load_file(file);
    file.close();
    if (new_quiz) {
        std::cout << "Successfully loaded." << std::endl;
    }
    Wait(2000);
    return new_quiz;
}


void Quiz::EditQuiz() {
    std::string tmp;
    int option = -1;
    while (true) {
        clearScreen();
        printBorder();
        //Updating after creating or deleting questions
        update();
        auto it = pages.begin() + current_page;
        if (current_page >= int(pages.size())) {
            std::cout << "Creating a new page" << std::endl;
            auto new_page = std::make_shared<Page>(0, view_quest);
            pages.insert(it, new_page);
            number_of_pages++;
        }
        auto &cur_page = pages.at(current_page);

        std::cout << "Name:" << getName() << std::endl;
        std::cout << "Number of Questions:"
                  << number_of_questions
                  << " " << "Number of Pages :" << number_of_pages << std::endl;
        std::cout << " Current page:" << (current_page + 1) << std::endl;
        printRepeating();
        if (current_page > 0 && current_page == (number_of_pages - 1)) {
            std::cout << "     5) Delete this page" << std::endl;
            std::cout << "     0) Back" << std::endl << std::endl;
            printDivider();
            std::cout << "     Enter your choice (0/1/2/3/4/5)  " << std::endl;
        } else {
            std::cout << "     0) Back" << std::endl << std::endl;
            printDivider();
            std::cout << "     Enter your choice (0/1/2/3/4)  " << std::endl;
        }
        option = IntegerEnter();
        if (option == INT32_MAX) return;
        switch (option) {
            case (2):
                //Move one position forward in the pages vector
                current_page++;
                break;
            case (3):
                //Move one position backwards in the pages vector
                if (current_page == 0) {
                    current_page = 1;
                }
                current_page--;
                break;
            case (1):
                //Will select questions on current page
                cur_page->QuestionSelector();
                break;
            case (4):
                cur_page->ShowQuestions();
                continueByEnter();
                break;
            case (5):
                it = pages.begin() + current_page;
                if (it == pages.begin()) {
                    std::cout << "You can't just delete this one and only page." << std::endl;
                    Wait(1000);
                    break;
                }
                pages.erase(it);
                number_of_pages--;
                current_page--;
                break;
            case (0):
                clearScreen();
                printBorder();
                std::cout << "Are you sure that you are done with editing the quiz?"
                          << std::endl << "Answer yes or y if you are sure." << std::endl;
                getline(std::cin, tmp);
                if (CaseInsensitiveEquals(tmp, "yes") || CaseInsensitiveEquals(tmp, "y") || !std::cin.good()) {
                    current_page = 0;
                    for (int i = 0; i < number_of_pages; i++) {
                        pages[i]->setCurrentQuestion(0);
                    }
                    return; // Returns to the main menu edited the question
                }
                break; // If not sure shows the page menu again
            default:
                //Wrong input handling
                clearScreen();
                printBorder();
                printWrong();
                Wait(1000);
                break;
        }
    }


}

const std::string &Quiz::getName() const {
    return name;
}

void Quiz::FillQuiz() {
    std::string tmp;
    int option = -1;
    while (true) {
        clearScreen();
        printBorder();
        //Updating after creating or deleting questions
        update();
        auto &cur_page = pages.at(current_page);
        std::cout << "Name of the Quiz:" << getName() << std::endl;
        std::cout << "Number of Questions:"
                  << number_of_questions
                  << " " << "Number of Pages :" << number_of_pages << std::endl;
        std::cout << " Number of answered questions:" << number_of_answered_questions << std::endl;
        std::cout << " Current page:" << (current_page + 1) << std::endl;
        printRepeating();
        std::cout << "     5) Finish the Quiz" << std::endl;
        std::cout << "     0) Back" << std::endl << std::endl;
        printDivider();
        std::cout << "     Enter your choice (0/1/2/3/4/5)  " << std::endl;
        option = IntegerEnter();
        if (option == INT32_MAX) return;
        switch (option) {
            case (2):
                //Move one position forward in the pages vector
                current_page++;
                if ((current_page + 1) > number_of_pages) current_page--;
                break;
            case (3):
                //Move one position backwards in the pages vector
                if (current_page == 0) {
                    current_page = 1;
                }
                current_page--;
                break;
            case (1):
                //Will select questions on current page
                cur_page->QuestionSelector(1);
                break;
            case (4):
                cur_page->ShowQuestions();
                continueByEnter();
                break;
            case (5):
                clearScreen();
                printBorder();
                std::cout << "Are you sure that you want to finish the Quiz?"
                          << std::endl << "Answer yes or y if you are sure." << std::endl;
                getline(std::cin, tmp);
                if (CaseInsensitiveEquals(tmp, "yes") || CaseInsensitiveEquals(tmp, "y") || !std::cin.good()) {
                    current_page = 0;
                    for (int i = 0; i < number_of_pages; i++) {
                        pages[i]->setCurrentQuestion(0);
                    }
                    return; // Returns to the main menu edited the question
                }
                break; // If not sure shows the page menu again

                break;
            case (0):
                clearScreen();
                std::cout << "Are you sure that you want to quit all progress will be lost?"
                          << std::endl << "Answer yes or y if you are sure." << std::endl;
                getline(std::cin, tmp);
                if (CaseInsensitiveEquals(tmp, "yes") || CaseInsensitiveEquals(tmp, "y") || !std::cin.good()) {
                    current_page = 0;
                    for (int i = 0; i < number_of_pages; i++) {
                        pages[i]->setCurrentQuestion(0);
                    }
                    return; // Returns to the main menu edited the question
                }
                break; // If not sure shows the page menu again
            default:
                //Wrong input handling
                clearScreen();
                printBorder();
                printWrong();
                Wait(1000);
                break;
        }
    }

}

std::vector<std::string> Quiz::RateQuiz() {
    clearScreen();
    printBorder();
    std::cout << "Enter the your name: " << std::endl;
    std::string tmp;
    std::getline(std::cin, tmp);
    printDivider();
    if (!std::cin.good()) return std::vector<std::string>();
    std::vector<std::string> result;
    result.push_back("Name of the user: " + tmp);
    int index = 1;
    tmp.clear();
    AppendTime(tmp);
    result.push_back("Date: " + tmp);
    result.push_back("Name of the quiz: " + name);
    result.push_back("Results: ");
    for (int i = 0; i < number_of_pages; ++i) {
        for (int j = 0; j < view_quest; ++j) {
            int tmp_num = number_of_correct_questions;
            if (!pages[i]->getQuestions()[j]->isAnswered()) {
                result.push_back("Question." + std::to_string(index) + ": " + " - Empty = Irrelevant");
                continue;
            }
            int parameterA = pages[i]->getQuestions()[j]->getParameterA();
            if (parameterA == 5) {
                int parameterB = pages[i]->getQuestions()[j]->getParameterB();
                if (parameterB == 1) {
                    if (FindSubstring(
                            pages[i]->getQuestions()[j]->getCorrectAnswer()->getAnswerText()[0],
                            pages[i]->getQuestions()[j]->getAnswer()->getAnswerText()[0])) {
                        number_of_correct_questions++;
                    } else if (pages[i]->getQuestions()[j]->getCorrectAnswer()->areEqual(
                            pages[i]->getQuestions()[j]->getAnswer())) {
                        number_of_correct_questions++;
                    }
                }
            } else {
                if (pages[i]->getQuestions()[j]->getCorrectAnswer()->areEqual(
                        pages[i]->getQuestions()[j]->getAnswer())) {
                    number_of_correct_questions++;
                }
            }
            if (tmp_num == number_of_correct_questions) {
                result.push_back("Question." + std::to_string(index) + ": " + " - Wrong");
            } else {
                result.push_back("Question." + std::to_string(index) + ": " + " - OK");
            }
            index++;
            //Deletes the answer from the user
            pages[i]->DeleteAnswer(j);
        }
    }

    double percentage = double(number_of_correct_questions) / double(number_of_questions) * 100;
    result.push_back("Success rate: " + std::to_string(percentage) + "/100");
    for (const auto &item : result) {
        std::cout << item << std::endl;
    }
    result.push_back("<------------------------------------>");
    number_of_correct_questions = 0;
    number_of_answered_questions = 0;
    continueByEnter();
    return result;

}


void Quiz::printRepeating() {
    printOptions();
    std::cout << "     1) Select Questions" << std::endl;
    std::cout << "     2) Next Page " << std::endl;
    std::cout << "     3) Previous Page" << std::endl;
    std::cout << "     4) Show Questions on Current Page" << std::endl;

}
