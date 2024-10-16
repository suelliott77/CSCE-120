// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    double exams = 0;
    double num_exams = 0;
    double final_exam = 0;
    double num_final = 1;
    double hw = 0;
    double num_hw = 0;
    double lw = 0;
    double num_lw = 0;
    double reading = 0;
    double num_reading = 0;
    double engagement = 0;
    double num_engagement = 0;

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            exams += score;
            num_exams++;
        } else if (category == "final-exam") {
            final_exam += score;
        } else if (category == "hw") {
            hw += score;
            num_hw++;
        } else if (category == "lw") {
            lw += score;
            num_lw++;
        } else if (category == "reading") {
            reading += score;
            num_reading++;
        } else if (category == "engagement") {
            engagement += score;
            num_engagement++;
        }else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    double exam_average = (exams + final_exam) / (num_exams + num_final);  ///////////////
        if (final_exam > (exams / 2)) {
            if (num_exams == 2) {
                exam_average = final_exam;
            }
            else if (exams == 0) {
                exam_average = final_exam;
            }
            else {
                exam_average = (exams + final_exam) / 2;
            }
        }
    double hw_average;  ////////////////////////////
    if (num_hw >= 1) {
         hw_average= hw / num_hw;
    }
    else {
        hw_average= 0;
    }

    double lw_average;  ///////////////////////////
    if (num_lw >=1) {
        lw_average = (lw / num_lw) * 100;
    }
    else {
        lw_average = 0;
    }

    double reading_average; ////////////////////////
    if (num_reading >= 1) {
        reading_average  = (reading / num_reading) + 15;
        if (reading_average > 100) {
        reading_average = 100;
    }
    }
    else {
        reading_average = 0;
    }

    double engagement_average; 
    if (num_engagement >= 1) {
        engagement_average = (engagement / num_engagement) + 15;
        if (engagement_average > 100) {
        engagement_average = 100;
    }
    }
    else {
        engagement_average = 0;
    }

    // TODO(student): compute weighted total of components
    double weighted_total = (exam_average * .4) + (hw_average * .4) + (lw_average * .1) + (reading_average * .05) + (engagement_average * .05);

    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';
    if ((weighted_total <= 100) && (weighted_total >= 90)) {
        final_letter_grade = 'A';
    }
    else if ((weighted_total <= 90) && (weighted_total >= 80)) {
        final_letter_grade = 'B';
    }
    else if ((weighted_total <= 80) && (weighted_total >= 70)) {
        final_letter_grade = 'C';
    }
    else if ((weighted_total <= 70) && (weighted_total >= 60)) {
        final_letter_grade = 'D';
    }
    else {
        final_letter_grade = 'F';
    }
    

    print_results(
        exam_average, hw_average, lw_average, reading_average, engagement_average,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
