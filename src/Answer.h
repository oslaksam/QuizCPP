#pragma once

#include "Coolutils.h"

class Answer {
public:
    /**
     * Function for answering the question by the user 
     * @param parameter - determines what kind of answer it will be
     */
    virtual void Answering(const int &parameter);

    /**
     * Function that loads the input from the user into the answer object
     */
    virtual void LoadAnswer();

    /**
     * Destructor for the Answer object
     */
    virtual ~Answer();

    /**
     * Getter function for the answer text vector
     * @return answer_text
     */
    std::vector<std::string> &getAnswerText();

    /**
     * Compares this answer to another answer
     * @param object
     * @return true / false - EQUAL OR NOT
     */
    virtual bool areEqual(std::shared_ptr<Answer> object);

    /**
     * Getter for the numerical result
     * @return result
     */
    double getResult() const;

    /**
     * Setter for the numerical result
     * @param result
     */
    void setResult(const double &result);

    /**
      * Function that prints the answer to std out
      * @param parameter determines what type of answer it will print
      */
    virtual void Print(const int &parameter) const;

    /**
     * Function that clears user's answer
     */
    void Clear();

    /**
     * Getter for the set containing the answers
     * @return
     */
    std::set<std::string> &getAnswers();

    /**
     * Function for loading the answer mostly in create and edit mode sometimes called in fill mode
     * @param max
     */
    virtual void LoadAnswer(const int &max);

    /**
     * Function for answering the question by the user
     * @param parameter - determines what kind of answer it will be
     */
    void Answering(const int &parameter, const int &parameterB);

    /**
     * Constructor for the answer object
     */
    Answer();


protected:
    /**
     * Contains the vector of string that will be interpreted by the answer type
     */
    std::vector<std::string> answer_text;
    /**
     * Stores the result of the numerical answer
     */
    double result;
    /**
    * Set that contains the multiple correct answer's to a multiple choice question
    */
    std::set<std::string> answers;


};


class MultipleChoice_Answer : public Answer {
public:
    /**
     * Function for answering the question by the user 
     * @param parameter - determines what kind of answer it will be
     */
    void Answering(const int &parameter) override;

    /**
     * MultipleChoice_Answer Constructor
     */
    MultipleChoice_Answer();


    /**
    * Function that loads the input from the user into the answer object
    */
    void LoadAnswer(const int &max) override;

    /**
    * Function that loads the input from the user into the answer object
    */
    void LoadAnswer() override;

    /**
     * Destructor for the MultipleChoice_Answer object
     */
    ~MultipleChoice_Answer() override;

    /**
    * Compares this answer to another answer
    * @param object
    * @return true / false - EQUAL OR NOT
    */
    bool areEqual(std::shared_ptr<Answer> object) override;

    /**
      * Function that prints the answer to std out
      * @param parameter determines what type of answer it will print
      */
    void Print(const int &parameter) const override;

};

class ABCD_Answer : public Answer {
public:
    /**
     * Function for answering the question by the user 
     * @param parameter - determines what kind of answer it will be
     */
    void Answering(const int &parameter) override;

    /**
     *  Constructor for the ABCD_Answer object
     */
    ABCD_Answer();

    /**
     * Function that loads the input from the user into the answer object
     */
    void LoadAnswer() override;

    /**
     * Destructor for the Answer object
     */
    ~ABCD_Answer() override;

    /**
    * Compares this answer to another answer
    * @param object
    * @return true / false - EQUAL OR NOT
    */
    bool areEqual(std::shared_ptr<Answer> object) override;

    /**
    * Function that loads the input from the user into the answer object
    */
    void LoadAnswer(const int &max) override;

    /**
      * Function that prints the answer to std out
      * @param parameter determines what type of answer it will print
      */
    void Print(const int &parameter) const override;


};

class YES_NO_Answer : public Answer {
public:
    /**
     * Function for answering the question by the user 
     * @param parameter - determines what kind of answer it will be
     */
    void Answering(const int &parameter) override;

    /**
     *  Constructor for the YES_NO_Answer object
     */
    YES_NO_Answer();

    /**
    * Function that loads the input from the user into the answer object INTO ANSWER
    */
    void LoadAnswer() override;

    /**
    *  Destructor for the YES_NO_Answer object
    */
    ~YES_NO_Answer() override;

    /**
    * Compares this answer to another answer
    * @param object
    * @return true / false - EQUAL OR NOT
    */
    bool areEqual(std::shared_ptr<Answer> object) override;

    /**
    * Function that loads the input from the user into the answer object
    */
    void LoadAnswer(const int &max) override;

    /**
      * Function that prints the answer to std out
      * @param parameter determines what type of answer it will print
      */
    void Print(const int &parameter) const override;


};


class SortAnswer : public Answer {
public:
    /**
     * Function for answering the question by the user 
     * @param parameter - determines what kind of answer it will be
     */
    void Answering(const int &parameter) override;

    /**
     *  Constructor for the SortAnswer object
     */
    SortAnswer();

    /**
     * Function that loads the input from the user into the answer object
     */
    void LoadAnswer() override;

    /**
     * Function that loads the input from the user into the answer object
     */
    void LoadAnswer(const int &max) override;


    /**
     * Destructor for the SortAnswer object
     */
    ~SortAnswer() override;

    /**
     * Compares this answer to another answer
     * @param object
     * @return true / false - EQUAL OR NOT
     */
    bool areEqual(std::shared_ptr<Answer> object) override;

    /**
      * Function that prints the answer to std out
      * @param parameter determines what type of answer it will print
      */
    void Print(const int &parameter) const override;


};


class TextAnswer : public Answer {
public:
    /**
     * Function for answering the question by the user 
     * @param parameter - determines what kind of answer it will be
     */
    void Answering(const int &parameter) override;

    /**
     * Constructor for the TextAnswer object
     */
    TextAnswer();


    /**
    * Function that loads the input from the user into the answer object
    */
    void LoadAnswer() override;

    /**
     * Destructor for the TextAnswer object
     */
    ~TextAnswer() override;

    /**
    * Compares this answer to another answer
    * @param object
    * @return true / false - EQUAL OR NOT
    */
    bool areEqual(std::shared_ptr<Answer> object) override;

    /**
    * Function that loads the input from the user into the answer object
    */
    void LoadAnswer(const int &max) override;

    /**
      * Function that prints the answer to std out
      * @param parameter determines what type of answer it will print
      */
    void Print(const int &parameter) const override;


};


class SolveAnswer : public Answer {
public:
    /**
     * Function for answering the question by the user 
     * @param parameter - determines what kind of answer it will be
     */
    void Answering(const int &parameter) override;

    /**
     * Constructor for the SolveAnswer object
     */
    SolveAnswer();

    /**
     * Function that loads the input from the user into the answer object
     */
    void LoadAnswer() override;

    /**
     * Destructor for the SolveAnswer object
     */
    ~SolveAnswer() override;

    /**
    * Compares this answer to another answer
    * @param object
    * @return true / false - EQUAL OR NOT
    */
    bool areEqual(std::shared_ptr<Answer> object) override;


    /**
    * Function that loads the input from the user into the answer object
    */
    void LoadAnswer(const int &max) override;

    /**
      * Function that prints the answer to std out
      * @param parameter determines what type of answer it will print
      */
    void Print(const int &parameter) const override;


};

