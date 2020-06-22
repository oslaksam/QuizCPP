#pragma once

#include "Question.h"

class Page {
public:
    /**
     * Getter function for the number of answered questions on the page
     * @return number_of_answered_questions
     */
    int getNumberOfAnsweredQuestions() const;

    /**
     * Getter function for the vector of questions on the page
     * @return & to questions vector
     */
    std::vector<std::shared_ptr<Question>> &getQuestions();

    /**
     * Setter function for the current question index
     * @param currentQuestion - index of the current question in the vector of questions
     */
    void setCurrentQuestion(const int &currentQuestion);

    /**
     * Getter function for number of questions on the Page
     * @return int (index of the current quest )
     */
    int getQuestionsOnPage() const;

    /**
     * Function that return maximum amount of questions on the page
     * @return maximum pages allowed on this page
     */
    int getMaxQuestionOnPage() const;

    /**
     * Setter for questions_on_page
     * @param questionsOnPage
     */
    void setQuestionsOnPage(const int &questionsOnPage);

    /**
     * Setter for max_question_on_page
     * @param maxQuestionOnPage
     */
    void setMaxQuestionOnPage(const int &maxQuestionOnPage);

    /**
     * Page object default constructor
     */
    Page();

    /**
     * Page object constructor with number of number_of_question and the max_number_of questions as parameters
     * @param number_of_questions
     * @param max_num_question
     */
    Page(const int &number_of_questions, const int &max_num_question);

    /**
     * Destructor for the page object
     */
    ~Page();

    /**
     * Copy constructor for the page object
     * @param other
     */
    Page(const Page &other);

    /*
     * Overloaded =operator
     */
    Page &operator=(const Page &other);

    /**
     * Function for printing questions on this page to stdout
     */
    void ShowQuestions();

    /**
     * Selection menu for creating or deleting or viewing the correct answer that is stored in the questions vector at provided index
     * @param index
     */
    void SelectMenu(const int &index);

    /**
     * Function that creates a question on the current question index in the questions vector
     */
    void CreateQuestion();

    /**
     * Function that deletes the question at the provided index
     * @param index
     */
    void DeleteQuestion(const int &index);

    /**
     * Function that prints the question stored in the questions vector at provided index to stdout
     * @param index
     */
    void ShowQuestion(const int &index);

    /**
     * Selection menu for selecting questions on the page
     * @param type - 0 = create/edit menu , 1 = answer menu
     */
    void QuestionSelector(const int &type = 0);

    /**
     * Menu for answering the question in the questions vector on the index provided in the argument
     * @param index
     */
    void AnswerMenu(const int &index);

    /**
     * Deletes the answer for the question in the vector of questions on the index provided in the argument
     * @param index
     */
    void DeleteAnswer(const int &index);

    /**
     * Function that deletes the user's answer to the question in the vector of questions on the index provided in the argument
     * @param index
     */
    void Answer(const int &index);

    /**
     * Function that prints the user's answer to the question (in the vector of questions on the index provided in the argument) to stdout
     * @param index
     */
    void ShowAnswer(const int &index);

    /**
     * Function that prints the correct answer to the question (in the vector of questions on the index provided in the argument) to stdout
     * @param index
     */
    void ShowCorrectAnswer(const int &index);

private:
    /**
     * Stores the maximum amount of question on the page
     */
    int max_question_on_page;
    /**
     * Stores the current number of questions on the page
     */
    int questions_on_page;
    /**
     * Stores the number of answered questions by the user
     */
    int number_of_answered_quest;
    /**
     * Stores the index of the currently selected question in the vector of questions
     */
    int current_question;
    /**
     * Vector for storing the Question objects
     */
    std::vector<std::shared_ptr<Question>> questions;
};





