#pragma once

#include "Answer.h"

class Question {
public:
    /**
     * Setter for the state of the answered question (false = not answered)/(true = answered)
     * @param answered
     */
    void setAnswered(const bool &answered);

    /**
     * Getter for the answered bool
     * @return answered
     */
    const bool &isAnswered() const;

    /**
     * Constructor for the Question object
     */
    Question();

    /**
     * Destructor for the Question object
     */
    virtual ~Question();

    /**
     * Function that loads user's input into the Question object
     */
    virtual void Create();

    /**
     * Function that prints the contents of the Question onto stdout
     */
    virtual void Print() const;

    /**
     * Getter for the question text vector
     * @return question text
     */
    std::vector<std::string> &getQuestionText();

    /**
     * Getter for the parameterA
     * @return parameterA
     */
    const int &getParameterA() const;

    /**
     * Getter for the parameterB
     * @return parameterB
     */
    const int &getParameterB() const;

    /**
     * Setter for the parameterB
     * @param parameterB
     */
    void setParameterB(const int &parameterB);

    /**
    * Getter for the correct answer
    * @return correct_answer
    */
    std::shared_ptr<Answer> getCorrectAnswer();

    /**
     * Getter for the user's answer
     * @return answer
     */
    std::shared_ptr<Answer> getAnswer();


protected:
    /**
     * Stores the the text of the question. Either just the question or the question with multiple options
     */
    std::vector<std::string> question_text;
    /**
     * This parameter will help with saving the questions | Determines the type of the Question
     */
    int parameterA;
    /**
     * This parameter will help with saving the answers to the questions | Determines the type of answer to the Question
     */
    int parameterB;
    /**
     * Stores the state of the question (false = not answered)/(true = answered)
     */
    bool answered;

    std::shared_ptr<Answer> correct_answer;

    std::shared_ptr<Answer> answer;

};


class MultipleChoice_Question : public Question {
public:
    /**
    * Constructor for the MultipleChoice_Question object
    */
    MultipleChoice_Question();

    /**
     * Copy constructor for the MultipleChoice_Question object
     * @param MultipleChoice_Question
     */
    MultipleChoice_Question(const MultipleChoice_Question &MultipleChoice_Question);

    /**
     * Destructor for the MultipleChoice_Question object
     */
    ~MultipleChoice_Question() override;

    /**
     * Function that loads user's input into the Question object
     */
    void Create() override;

    /**
     * Function that prints the contents of the Question onto stdout
     */
    void Print() const override;


};

class ABCD_Question : public Question {
public:
    /**
    * Constructor for the ABCD_Question object
    */
    ABCD_Question();

    /**
     * Copy constructor for the ABCD_Question object
     * @param other
     */
    ABCD_Question(const ABCD_Question &other);


    /**
     * Destructor or the ABCD_Question object
     */
    ~ABCD_Question() override;

    /**
     * Function that loads user's input into the Question object
     */
    void Create() override;

    /**
     * Function that prints the contents of the Question onto stdout
     */
    void Print() const override;



};

class YES_NO_Question : public Question {
public:
    /**
    * Constructor for the YES_NO_Question object
    */
    YES_NO_Question();

    /**
     * Copy constructor for the YES_NO_Question object
     * @param other
     */
    YES_NO_Question(const YES_NO_Question &other);


    /**
     * Destructor for the YES_NO_Question object
     */
    ~YES_NO_Question() override;

    /**
     * Function that loads user's input into the Question object
     */
    void Create() override;

    /**
     * Function that prints the contents of the Question onto stdout
     */
    void Print() const override;

};


class SortQuestion : public Question {
public:
    /**
    * Constructor for the SortQuestion object
    */
    SortQuestion();

    /**
     * Copy constructor for the SortQuestion object
     * @param other
     */
    SortQuestion(const SortQuestion &other);


    /**
     * Destructor for the SortQuestion object
     */
    ~SortQuestion() override;


    /**
     * Function that loads user's input into the Question object
     */
    void Create() override;

    /**
     * Function that prints the contents of the Question onto stdout
     */
    void Print() const override;


};


class TextAnswerQuestion : public Question {
public:
    /**
    * Constructor for the TextAnswerQuestion object
    */
    TextAnswerQuestion();

    /**
     * Copy constructor for the TextAnswerQuestion object
     * @param TextAnswerQuestion
     */
    TextAnswerQuestion(const TextAnswerQuestion &TextAnswerQuestion);

    /**
    * Destructor for the TextAnswerQuestion object
    */
    ~TextAnswerQuestion() override;


    /**
     * Function that loads user's input into the Question object
     */
    void Create() override;

    /**
     * Function that prints the contents of the Question onto stdout
     */
    void Print() const override;



};


class SolveQuestion : public Question {
public:
    /**
     * Constructor for the SolveQuestion object
     */
    SolveQuestion();

    /**
     * Copy constructor for the SolveQuestion object
     * @param SolveQuestion
     */
    SolveQuestion(const SolveQuestion &SolveQuestion);


    /**
     * Destructor for the SolveQuestion object
     */
    ~SolveQuestion() override;

    /**
      * Function that loads user's input into the Question object
      */
    void Create() override;

    /**
     * Function that prints the contents of the Question onto stdout
     */
    void Print() const override;


};
