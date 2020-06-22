#pragma once

#include "Page.h"

class Quiz {
public:
    /**
     * Getter function for the name of the Quiz
     * @return name
     */
    const std::string &getName() const;

    /**
     * Constructor of the quiz object
     */
    Quiz();

    /**
    * Destructor for the quiz object
    */
    ~Quiz();

    /**
     * This functions will rate the quiz and returns a result as a vector of string containing the results that will be
     * appended to the
     * @return std::vector<std::string>
     */
    std::vector<std::string> RateQuiz();

    /**
     * Function that opens the menu for filling the quiz
     */
    void FillQuiz();

    /**
     * Function that creates the shared pointer to the Quiz object that will be stored in the vector of Quiz objects
     * @return std::shared_ptr<Quiz>
     */
    static std::shared_ptr<Quiz> CreateQuiz();

    /**
     * Saves the quiz into their directories
     * @param seq  - if the quiz is sequential or not (changes the directory in the string pathway)
     * @param pathway - pathway to the directory ssaves
     */
    virtual void SaveQuiz(bool seq = false, const std::string &pathway = "");

    /**
     * Function for quiz editing
     */
    void EditQuiz();

    /**
     * Function that loads the file and returns the quiz both used by the normal Quiz and by SequenceQuiz
     * @param file
     * @return std::shared_ptr<Quiz> loaded quiz from the file
     */
    static std::shared_ptr<Quiz> load_file(std::ifstream &file);

    /**
     * Function that will load the Quiz object from the file used and return the shared pointer to it
     * It calls the load_file function because it is used both by Quiz and SequenceQuiz
     * @return std::shared_ptr<Quiz>
     */
    static std::shared_ptr<Quiz> LoadQuiz();

    /**
     * Function that updates the number of questions and the state of answered questions in the Quiz object
     */
    void update();

    /**
     * Prints the repeating pattern of the menu's
     */
    static void printRepeating();

private:
    /**
     * Stores the number of pages the quiz has
     */
    int number_of_pages;
    /**
     * Stores the index of the current page to access the page in the vector pages
     */
    int current_page;
    /**
     * Stores the number of questions to be viewed on the page
     */
    int view_quest;
    /**
     * Stores the number of question that are created in the quiz
     */
    int number_of_questions;
    /**
     * Stores the number of answered questions in the quiz
     */
    int number_of_answered_questions;
    /**
     * Stores the number of questions that user had answered correctly
     */
    int number_of_correct_questions;
    /**
     * Stores the pages of the quiz so the user can navigate in the quiz properly
     */
    std::vector<std::shared_ptr<Page>> pages;
protected:
    /**
     * Stores the name of the quiz
     */
    std::string name;


};





