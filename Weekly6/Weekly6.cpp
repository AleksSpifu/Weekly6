#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//logins.txt is from https://github.com/kennyn510/wpa2-wordlists/tree/master/PlainText
//Bert and Ernie text is from http://www.textfiles.com/stories/berternie.txt

void task1();
void task2();
void task3();
void task4();

int main()
{
    //task1();
    //task2();
    //task3();
    //task4();
    return 0;
}

void task1() 
{
    std::fstream passwordFile("password.txt", std::ios::in);
    std::fstream loginsFile("logins.txt", std::ios::in);
    std::string tempStrLogin{};
    std::string password{};
    std::getline(passwordFile, password);
    bool foundPass = false;
    int counter = 0;
    while (!loginsFile.eof() && !foundPass) {
        counter++;
        std::getline(loginsFile, tempStrLogin);
        if (password == tempStrLogin) {
            foundPass = true;
            break;
        }
    }
    std::cout << "Password is: " << tempStrLogin << ", it was found on line " << counter << " in the document.\n";
    passwordFile.close();
    loginsFile.close();
}

void task2() 
{
    std::fstream testFile("task2TestResults.txt", std::ios::in);
    std::string trashString{};
    
    std::string correctAnswers = "ABDCAB";
    int numberOfStudents{};
    testFile.clear();
    testFile.seekg(0);
    while (!testFile.eof()) {
        std::getline(testFile, trashString);
        numberOfStudents++;
    }
    trashString.clear();
    testFile.clear();
    testFile.seekg(0);
    numberOfStudents = numberOfStudents / 2;
    struct testResults {
        std::string name = "";
        std::string answers = "";
        int score{};
    };
    std::vector <testResults> students(numberOfStudents);
    for (int i = 0; i < students.size(); i++) {
        std::getline(testFile, students[i].name);
        std::getline(testFile, students[i].answers);
        for (int j = 0; j < students[i].answers.size(); j++) {
            if (students[i].answers[j] == correctAnswers[j]) {
                students[i].score++;
            }
        }
        std::cout << students[i].name << " answered: " << students[i].answers << " and got a score of: " << students[i].score << "\n";
    }
    float average = 0;
    int minimum = 6;
    int maximum = 0;
    for (int i = 0; i < students.size(); i++) {
        average += students[i].score;
        if (students[i].score < minimum) {
            minimum = students[i].score;
        }
        if (students[i].score > maximum) {
            maximum = students[i].score;
        }
    }
    average = average / students.size();
    std::cout << "Average: " << average << "\nMax score: " << maximum << "\nMin score: " << minimum << "\n";
    testFile.close();
}

void task3()
{
    std::fstream story("berternie.txt", std::ios::in);
    std::string input = "";
    std::string storyWord = "";
    std::cout << "Please enter a word you'd like to search for:\n";
    std::cin >> input;
    for (int i = 0; i < input.size(); i++) {
        input[i] = tolower(input[i]);
    }
    int occurances = 0;
    int wordsSearched = 0;
    while (!story.eof()) {
        story >> storyWord;
        for (int i = 0; i < storyWord.size(); i++) {
            storyWord[i] = tolower(storyWord[i]);
        }
        if (storyWord.size() >= input.size()) {
            int counter = 0;
            for (int i = 0; i < input.size(); i++) {
                if (input[i] == storyWord[i]) {
                    counter++;
                }
            }
            if (counter == input.size()) {
                occurances++;
            }
            
        }
        wordsSearched++;
    }

    std::cout << "Found " << occurances << " occurances of the word " << input << ", searched a total of " << wordsSearched << "\n";
    story.close();
}

void task4()
{
    std::fstream storyFile("berternie.txt", std::ios::in);
    std::fstream outputFile("emptyFile.txt", std::ios::out);
    std::string tempStr = "";
    while (!storyFile.eof()) {
        std::getline(storyFile, tempStr);
        outputFile << tempStr << std::endl;
    }
    storyFile.close();
    outputFile.close();
}