
#include "SequenceQuiz.h"

/**
 * Prints the main menu of the program
 */
void PrintMenu() {
    printBorder();
    std::cout << " khajiit has quiz if you have coin." << std::endl;
    printDivider();
    printOptions();
    std::cout << "     1) Take a Quiz" << std::endl;
    std::cout << "     2) Create Quiz" << std::endl;
    std::cout << "     3) Edit Quiz" << std::endl;
    std::cout << "     4) Export Quiz" << std::endl;
    std::cout << "     5) Import Quiz" << std::endl;
    std::cout << "     6) Export Results" << std::endl;
    std::cout << "     7) Import Results" << std::endl;
    std::cout << "     8) Show Results" << std::endl;
    std::cout << "     0) Quit" << std::endl << std::endl;
    printDivider();
    std::cout << "     Enter your choice (0/1/2/3/4/5/6/7/8)  " << std::endl;
    printDivider();

}

/**
 * Prints the type of Quiz selection menu
 * @param string (import / export / edit)
 */
void PrintTypeSelection(const std::string &string) {
    printBorder();
    std::cout << "Which type of quiz would you like to " << string << "?" << std::endl;
    printOptions();
    std::cout << "     1) Quiz" << std::endl;
    std::cout << "     2) Sequential Quiz" << std::endl;
    printDivider();
    std::cout << "       Enter your choice (1/2)" << std::endl;
    printDivider();
}

/**
 * Prints the menu for Quiz selection
 * @param string (import / export / edit)
 */
void PrintQuizSelection(const std::string &string) {
    printBorder();
    std::cout << "Enter which quiz would you like to " << string << "?" << std::endl;
    std::cout << "Example: 0. Butterflies" << std::endl;
    std::cout << "Example: 1. Computers" << std::endl;
    std::cout << "Your answer: \"1\"" << std::endl;
    printDivider();
    std::cout << "       Enter your choice (0/1/...)" << std::endl;
    printDivider();
}

/**
 * Prints the menu for Quiz exportation and lets the user select a Quiz to export
 * @param quizes
 */
void ExportQuiz(std::vector<std::shared_ptr<Quiz>> &quizes) {
    int selection_index = 0;
    printBorder();
    PrintQuizSelection("export");
    if (quizes.empty()) {
        std::cout << "Quizes are empty." << std::endl;
        Wait(2000);
        return;
    }
    for (const auto &quiz : quizes) {
        std::cout << selection_index << ". " << quiz->getName() << std::endl;
        selection_index++;
    }
    printDivider();
    selection_index = IntegerEnter();
    if (selection_index > int(quizes.size() - 1)) {
        printWrong();
        printDivider();
        Wait(2000);
        return;
    }
    quizes[selection_index]->SaveQuiz();
}

/**
 * Prints the menu for SequenceQuiz exportation and lets the user select a SequenceQuiz to export
 * @param quizes
 */
void ExportSeq(std::vector<std::shared_ptr<SequenceQuiz>> &sequential_quizes) {
    int selection_index = 0;
    printBorder();
    PrintQuizSelection("export");
    if (sequential_quizes.empty()) {
        std::cout << "Sequential quizes are empty." << std::endl;
        Wait(2000);
        return;
    }
    for (const auto &seq_q:sequential_quizes) {
        std::cout << selection_index << ". " << seq_q->getName() << std::endl;
        selection_index++;
    }
    printDivider();
    selection_index = IntegerEnter();
    if (selection_index > int(sequential_quizes.size() - 1)) {
        printWrong();
        Wait(2000);
        return;
    }
    sequential_quizes[selection_index]->SaveQuiz();

}

/**
 * Print the menu for that lets user select and do a SequenceQuiz
 * @param sequential_quizes
 * @param quizes
 * @param results
 */
void FillSeq(std::vector<std::shared_ptr<SequenceQuiz>> &sequential_quizes, std::vector<std::shared_ptr<Quiz>> &quizes,
             std::vector<std::string> &results) {
    int selection_index = 0;
    std::string tmp;
    std::vector<std::string> tmp_vector;
    printBorder();
    PrintQuizSelection("fill");
    if (sequential_quizes.empty()) {
        std::cout << "Sequential quizes are empty." << std::endl;
        Wait(2000);
        return;
    }
    for (const auto &seq_q:sequential_quizes) {
        std::cout << selection_index << ". " << seq_q->getName() << std::endl;
        selection_index++;
    }
    printDivider();
    selection_index = IntegerEnter();
    if (selection_index > int(sequential_quizes.size() - 1)) {
        printWrong();
        Wait(2000);
        return;
    }

    clearScreen();
    printBorder();
    std::cout << sequential_quizes[selection_index]->getQuestion() << std::endl;
    printOptions();
    for (const auto &pair: sequential_quizes[selection_index]->getOptions()) {
        std::cout << pair.first << std::endl;
    }
    printDivider();
    getline(std::cin, tmp);
    if (!std::cin.good()) return;
    if (sequential_quizes[selection_index]->getOptions().count(tmp)) {
        sequential_quizes[selection_index]->getQuizes()[sequential_quizes[selection_index]->getOptions().at(
                tmp)]->FillQuiz();
        tmp_vector = quizes[selection_index]->RateQuiz();
        for (const auto &item: tmp_vector) {
            results.push_back(item);
        }
    } else {
        printWrong();
        Wait(2000);
        return;
    }

}

/**
 * Calls the function for loading the SequenceQuiz
 * @param sequential_quizes
 */
void ImportSeq(std::vector<std::shared_ptr<SequenceQuiz>> &sequential_quizes) {
    printBorder();
    std::shared_ptr<SequenceQuiz> load_seq = SequenceQuiz::LoadQuiz();
    if (load_seq != nullptr) {
        sequential_quizes.push_back(load_seq);
    }

}

/**
 *
 * @param quizes
 * @param results
 */
void FillQuiz(std::vector<std::shared_ptr<Quiz>> &quizes, std::vector<std::string> &results) {
    printBorder();
    int selection_index = 0;
    std::vector<std::string> tmp_vector;
    PrintQuizSelection("fill");
    if (quizes.empty()) {
        std::cout << "Quizes are empty." << std::endl;
        Wait(2000);
        return;
    }
    for (const auto &quiz : quizes) {
        std::cout << selection_index << ". " << quiz->getName() << std::endl;
        selection_index++;
    }
    printDivider();
    selection_index = IntegerEnter();
    if (selection_index > int(quizes.size() - 1)) {
        printWrong();
        Wait(2000);
        return;
    }
    quizes[selection_index]->FillQuiz();
    tmp_vector = quizes[selection_index]->RateQuiz();
    for (const auto &item: tmp_vector) {
        results.push_back(item);
    }
}

/**
 * Prints the menu for creating a Quiz
 * @param sequential_quizes
 * @param quizes
 */
void
CreateQuiz(std::vector<std::shared_ptr<SequenceQuiz>> &sequential_quizes, std::vector<std::shared_ptr<Quiz>> &quizes) {
    std::string tmp;
    std::shared_ptr<Quiz> new_quiz;
    std::shared_ptr<SequenceQuiz> new_sequece_quiz;
    printBorder();
    std::cout
            << "Would you like to have a sequential question in your quiz?" << std::endl
            << "(which would split your quiz into other quiz's depending on the options)"
            << std::endl
            << "Type yes/y or anything else if no." << std::endl;
    printDivider();
    std::getline(std::cin, tmp);
    if (!std::cin.good()) return;
    if (CaseInsensitiveEquals(tmp, "yes") || CaseInsensitiveEquals(tmp, "y")) {
        new_sequece_quiz = SequenceQuiz::Create();
        if (new_sequece_quiz == nullptr) {
            std::cout << "Quiz not created" << std::endl;
            Wait(2000);
            return;
        }
        sequential_quizes.push_back(new_sequece_quiz);
    } else {
        new_quiz = Quiz::CreateQuiz();
        if (new_quiz == nullptr) {
            std::cout << "Quiz not created" << std::endl;
            Wait(2000);
            return;
        }
        quizes.push_back(new_quiz);
    }

}

/**
 * Calls the function that loads the Quiz and inserts it into quizes vector
 * @param quizes
 */
void ImportQuiz(std::vector<std::shared_ptr<Quiz>> &quizes) {
    printBorder();
    std::shared_ptr<Quiz> load_quiz = Quiz::LoadQuiz();
    if (load_quiz != nullptr) {
        quizes.push_back(load_quiz);
    }
}

/**
 * Function that prints the menu for editing a Quiz
 * @param quizes
 */
void EditQuiz(std::vector<std::shared_ptr<Quiz>> &quizes) {
    printBorder();
    int selection_index = 0;
    PrintQuizSelection("edit");
    if (quizes.empty()) {
        std::cout << "Quizes are empty." << std::endl;
        Wait(2000);
        return;
    }
    for (const auto &quiz : quizes) {
        std::cout << selection_index << ". " << quiz->getName() << std::endl;
        selection_index++;
    }
    printDivider();
    selection_index = IntegerEnter();
    if (selection_index > int(quizes.size() - 1)) {
        printWrong();
        Wait(2000);
        return;
    }
    quizes[selection_index]->EditQuiz();
}

/**
 * Function that prints the menu for editing a SequenceQuiz
 * @param sequential_quizes
 */
void EditSeq(std::vector<std::shared_ptr<SequenceQuiz>> &sequential_quizes) {
    printBorder();
    int selection_index = 0;
    PrintQuizSelection("edit");
    if (sequential_quizes.empty()) {
        std::cout << "Sequential quizes are empty." << std::endl;
        Wait(2000);
        return;
    }
    for (const auto &seq_q:sequential_quizes) {
        std::cout << selection_index << ". " << seq_q->getName() << std::endl;
        selection_index++;
    }
    printDivider();
    selection_index = IntegerEnter();
    if (selection_index > int(sequential_quizes.size() - 1)) {
        printWrong();
        Wait(2000);
        return;
    }

    clearScreen();
    printDivider();
    std::cout << "Enter which quiz would you like to edit the whole quiz or only a part of it?" << std::endl;
    printOptions();
    std::cout << "     1) Whole" << std::endl;
    std::cout << "     2) Just a certain part" << std::endl;
    std::cout << "       Enter your choice (1/2)" << std::endl;
    printDivider();
    int choice = IntegerEnter();
    if (choice == INT32_MAX) return;
    if (choice == 1) {
        for (const auto &quiz: sequential_quizes[selection_index]->getQuizes()) {
            quiz->EditQuiz();
        }
    } else {
        clearScreen();
        printBorder();
        PrintQuizSelection("edit");
        for (const auto &pair: sequential_quizes[selection_index]->getOptions()) {
            std::cout << pair.second << ". " << pair.first << std::endl;
        }
        printDivider();
        choice = IntegerEnter();
        if (choice == INT32_MAX) return;
        if (choice > int(sequential_quizes[selection_index]->getQuizes().size() - 1)) {
            printWrong();
            Wait(2000);
            return;
        }
        sequential_quizes[selection_index]->getQuizes()[choice]->EditQuiz();
    }

}

/**
 * Function that imports the results from a text file
 * @param results <- inserts the results from a text file into this vector
 */
void ImportResults(std::vector<std::string> &results) {
    std::string results_path = "examples/results/";
    std::ifstream ifile;
    std::map<int, std::string> files;
    int index_res = 0;
    clearScreen();
    printBorder();
    printDivider();
    std::cout << "Choose the file that you need to load" <<
              std::endl;
    printOptions();
    if (!std::experimental::filesystem::exists(results_path)) {
        std::cout << "The folder does not exist" << std::endl;
        Wait(1000);
        return;
    }
    for (const auto &entry : std::experimental::filesystem::directory_iterator(results_path)) {
        std::cout << index_res << ". " << entry.path() << std::endl;
        std::string tmp;
        tmp.append(entry.path());
        files.insert(std::make_pair(index_res, tmp));
        index_res++;
    }
    if (files.empty()) {
        std::cout << "The folder with results is empty." << std::endl;
        Wait(2000);
        return;
    }
    printDivider();
    std::cout << "       Enter your choice (0/1/...)" << std::endl;
    printDivider();
    int choice = IntegerEnter();
    if (choice == INT32_MAX) return;
    if (choice > index_res) {
        printDivider();
        std::cout << "Pick from the list :)" << std::endl;
        printWrong();
        Wait(2000);
        return;
    }
    //Open the selected file
    ifile.open(files.at(choice));
    //Load the whole file
    for (std::string line; getline(ifile, line);) {
        results.push_back(line);
    }
    ifile.close();
    std::cout << "Imported." << std::endl;
    Wait(1000);

}

/**
 * Fuction that export the results vector of strings into a text file named by the current timestamp
 * @param results
 */
void ExportResults(std::vector<std::string> &results) {
    printBorder();
    std::ofstream ofile;
    std::string results_path = "examples/results/";
    if (!std::experimental::filesystem::exists(results_path)) {
        std::cout << "The folder does not exist" << std::endl;
        Wait(1000);
        return;
    }
    AppendTime(results_path);
    results_path.append(".txt");
    ofile.open(results_path, std::ios_base::app);
    for (const auto &item: results) {
        ofile << item << std::endl;
    }
    ofile.close();
    std::cout << "Exported." << std::endl;
    Wait(1000);
}

/**
 * This function takes the int input from the user and calls the appropriate function to handle that input
 * @return int - this function will be called in the cycle until the it returns something else than EXIT_FAILURE
 */
int menu(std::vector<std::shared_ptr<Quiz>> &quizes, std::vector<std::shared_ptr<SequenceQuiz>> &sequential_quizes,
         std::vector<std::string> &results) {

    clearScreen(); // clears the output
    PrintMenu();
    int choice;
    choice = IntegerEnter();
    if (choice == INT32_MAX) return choice;
    switch (choice) {
        case (1):
            clearScreen();
            PrintTypeSelection("fill");
            choice = IntegerEnter();
            if (choice == INT32_MAX) return choice;
            clearScreen();
            switch (choice) {
                case (1):
                    FillQuiz(quizes, results);
                    break;
                case (2):
                    FillSeq(sequential_quizes, quizes, results);
                    break;
                default:
                    printWrong();
                    Wait(2000);
                    break;
            }
            break;
        case (2):
            CreateQuiz(sequential_quizes, quizes);
            //If quiz is not created show menu again
            break;
        case (3):
            clearScreen();
            PrintTypeSelection("edit");
            choice = IntegerEnter();
            if (choice == INT32_MAX) return choice;
            clearScreen();

            switch (choice) {
                case (1):
                    EditQuiz(quizes);
                    break;
                case (2):
                    EditSeq(sequential_quizes);
                    break;
                default:
                    printWrong();
                    Wait(2000);

            }
            break;
        case (4):
            clearScreen();
            PrintTypeSelection("export");
            choice = IntegerEnter();
            if (choice == INT32_MAX) return choice;
            clearScreen();
            switch (choice) {
                case (1):
                    ExportQuiz(quizes);
                    break;
                case (2):
                    ExportSeq(sequential_quizes);
                    break;
                default:
                    printWrong();
                    Wait(2000);
                    break;
            }
            break;
        case (5):
            clearScreen();
            PrintTypeSelection("import");
            choice = IntegerEnter();
            if (choice == INT32_MAX) return choice;
            clearScreen();
            switch (choice) {
                case (1):
                    ImportQuiz(quizes);
                    break;
                case (2):
                    ImportSeq(sequential_quizes);
                    break;
                default:
                    printWrong();
                    Wait(2000);
                    break;
            }
            break;
        case (6):
            ExportResults(results);
            break;
        case (7):
            ImportResults(results);
            break;
        case (8):
            for (const auto &item: results) {
                std::cout << item << std::endl;
            }
            continueByEnter();
            break;
        case (0):
            return EXIT_SUCCESS;
        default:
            printWrong();
            Wait(1000);
            break;
    }
    return EXIT_FAILURE;


}

/**
 * Main menu navigate mostly by entering numbers
 * @return return status
 */
int main() {
    /**
     * Vector that stores loaded or created Quiz objects
     */
    std::vector<std::shared_ptr<Quiz>> quizes;
    /**
     * Vector that stores loaded or created SequenceQuiz objects
     */
    std::vector<std::shared_ptr<SequenceQuiz>> sequential_quizes;
    /**
     * Vector that stores loaded or created results
     */
    std::vector<std::string> results;
    int res = EXIT_FAILURE;
    /**
     * Will call the main menu the user selects the exit option or an error occurs
     */
    while (res == EXIT_FAILURE) {
        res = menu(quizes, sequential_quizes, results);
    }
    return res;
}
