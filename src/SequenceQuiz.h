#pragma once

#include "Quiz.h"


class SequenceQuiz : public Quiz {
public:
    /**
     * Constructor for the SequenceQuiz object
     */
    SequenceQuiz();

    /**
     * Destructor for the SequenceQuiz object
     */
    ~SequenceQuiz();

    /**
     * Function that returns shared pointer to the SequenceQuiz object that will be stored in the vector of SequenceQuiz obects
     * @return
     */
    static std::shared_ptr<SequenceQuiz> Create();

    /**
     * Getter for the map that binds the answers of the sequential question to the quiz in the quizes vector
     * @return maps of answers to indexes
     */
    const std::map<std::string, int> &getOptions() const;

    /**
     * Getter for the vector that contains the Quizes that will be accessed by the user's answer to the sequential question.
     * @return std::vector<std::shared_ptr<Quiz>> & quizes
     */
    std::vector<std::shared_ptr<Quiz>> &getQuizes();

    /**
     * Fuction that loads the SequenceQuiz  from a file and returns a shared pointer to it.
     * @return std::shared_ptr<SequenceQuiz>
     */
    static std::shared_ptr<SequenceQuiz> LoadQuiz();

    /**
     * Function that saves the SequenceQuiz object into a file
     */
    void SaveQuiz();

    /**
     * Getter function for the sequential question
     * @return question
     */
    const std::string &getQuestion() const;

private:
    /**
    * Stores the text of the sequential question
    */
    std::string question;
    /**
     * Maps the answer to the sequential question to the index in quizes vector (used in filling the quiz)
     */
    std::map<std::string, int> options;
    /**
     * Vector of quizes. The user will be filling the one that is mapped by the answer to a certain index in this vector
     */
    std::vector<std::shared_ptr<Quiz>> quizes;
};





