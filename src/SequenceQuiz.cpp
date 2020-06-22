#include "SequenceQuiz.h"


SequenceQuiz::SequenceQuiz() = default;

SequenceQuiz::~SequenceQuiz() = default;

std::shared_ptr<SequenceQuiz> SequenceQuiz::Create() {
    clearScreen();
    printBorder();
    int index = 0; // index for inserting Quiz objects into the quizes vector of SequenceQuiz object
    auto seq_quiz = std::make_shared<SequenceQuiz>();
    std::string tmp;
    std::cout
            << "Enter the name of your Sequential quiz:" << std::endl;
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return nullptr;
    seq_quiz->name = tmp;
    printDivider();
    std::cout << "Enter the sequence question" << std::endl << "Example: Are you a student or a teacher?" << std::endl;
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return nullptr;
    seq_quiz->question = tmp;
    printDivider();
    std::cout << "Enter the first choice of sequence." << std::endl << "Example: Are you a student or a teacher?"
              << std::endl << "Your answer: student" << std::endl;
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return nullptr;
    seq_quiz->options.insert(std::make_pair(tmp, index));
    index++;
    printDivider();
    std::cout << "Enter the second choice of sequence" << std::endl << "Example: Are you a student or a teacher?"
              << std::endl << "Your answer: teacher" << std::endl;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return nullptr;
    seq_quiz->options.insert(std::make_pair(tmp, index));
    index++;
    while (true) {
        printDivider();
        std::cout << "Enter the " << (index + 1) << ". choice of sequence or end by entering a blank line" << std::endl;
        std::getline(std::cin, tmp);
        if (!std::cin.good()) return nullptr;
        if (tmp == "") break;
        seq_quiz->options.insert(std::make_pair(tmp, index));
        index++;
    }
    for (int i = 0; i < index; i++) {
        auto quiz = Quiz::CreateQuiz();
        if (quiz == nullptr) {
            clearScreen();
            printBorder();
            std::cout << "Well this is your fault." << std::endl;
            printWrong();
            Wait(2000);
            return nullptr;
        }
        seq_quiz->quizes.push_back(quiz);
    }
    clearScreen();
    printBorder();
    std::cout << "Sequential quiz created." << std::endl;
    printDivider();
    Wait(1000);
    return seq_quiz;
}

const std::string &SequenceQuiz::getQuestion() const {
    return question;
}


const std::map<std::string, int> &SequenceQuiz::getOptions() const {
    return options;
}


std::vector<std::shared_ptr<Quiz>> &SequenceQuiz::getQuizes() {
    return quizes;
}


std::shared_ptr<SequenceQuiz> SequenceQuiz::LoadQuiz() {
    std::ifstream file;
    std::shared_ptr<SequenceQuiz> new_seq = std::make_shared<SequenceQuiz>();
    std::string path = "examples/ssaves/";
    if (!std::experimental::filesystem::exists(path)) {
        std::cout << "The folder does not exist" << std::endl;
        Wait(1000);
        return nullptr;
    }
    std::map<int, std::string> files;
    int index = 0;
    clearScreen();
    printBorder();
    std::cout << "Choose the SequenceQuiz that you want to load" <<
              std::endl;
    printOptions();
    printDivider();
    for (const auto &entry : std::experimental::filesystem::directory_iterator(path)) {
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
        Wait(1000);
        return nullptr;
    }
    std::cout << "       Enter your choice (0/1/...)" << std::endl;
    int choice = IntegerEnter();
    if (choice == INT32_MAX) return nullptr;
    if (choice > index) {
        printDivider();
        std::cout << "Pick from the list :)" << std::endl;
        printWrong();
        Wait(1000);
        return nullptr;
    }
    //Open the selected file
    file.open(files.at(choice));
    if (file.is_open()) {
        try {
            std::string line;
            int size;
            std::getline(file, line);
            new_seq->question = line;
            std::getline(file, line);
            new_seq->name = line;
            std::getline(file, line);
            size = std::stoi(line);
            for (int j = 0; j < size; ++j) {
                std::string string;
                int index;
                std::getline(file, line);
                string = line;
                std::getline(file, line);
                index = std::stoi(line);
                new_seq->options.insert(std::make_pair(string, index));
            }
            std::getline(file, line);
            if (line != "|-|-|") {
                return nullptr;
            }
            std::getline(file, line);
            //size of quizes
            size = std::stoi(line);
            for (int i = 0; i < size; ++i) {
                std::shared_ptr<Quiz> new_quiz = std::make_shared<Quiz>();
                new_quiz = Quiz::load_file(file);
                std::getline(file, line);
                if (line != "|--|") {
                    return nullptr;
                }
                if (!new_quiz) {
                    std::cout << "Error." << std::endl;
                    return nullptr;
                }
                new_seq->quizes.push_back(new_quiz);
            }

        } catch (std::invalid_argument &) {
            std::cout << "Error." << std::endl;
            Wait(1000);
            return nullptr;
        }

    }
    std::cout << "Successfully loaded the Sequential Quiz." << std::endl;
    Wait(2000);
    return new_seq;

}

void SequenceQuiz::SaveQuiz() {
    printBorder();
    std::ofstream file;
    std::string filename = "examples/ssaves/";
    if (!std::experimental::filesystem::exists(filename)) {
        std::cout << "The folder does not exist" << std::endl;
        Wait(1000);
        return;
    }
    filename.append(name);
    AppendTime(filename);
    // print various components of the structure.
    filename.append(".txt");
    file.open(filename, std::ios_base::app);
    file << question << std::endl;
    file << name << std::endl;
    file << options.size() << std::endl;
    for (const auto &i : options) {
        file << i.first << std::endl;
        file << i.second << std::endl;
    }
    file << "|-|-|" << std::endl;
    file << quizes.size() << std::endl;
    for (const auto &quiz: quizes) {
        quiz->SaveQuiz(true, filename);
        file << "|--|" << std::endl;
    }
}
