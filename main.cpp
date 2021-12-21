// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include "csvstream.h"

using namespace std;

bool validate_cmdline_args(const int argc, char* const argv[]);
set<string> unique_words(const string &str);
bool validate_filenames(const string &train, const string &test);

class Classifier {
public:
    // default ctor 
    // initialize num_post, num_word, and test_size to 0
    // the other elements are initialized to default values 
    Classifier():
    num_post(0), vocab_size(0), test_size(0), debug(false) {}

    // setter function to allow modifying the debug 
    // member variable from main function
    void set_debug(bool debug_in) {
        debug = debug_in;
    }

    // use csvstream to read the training dataset
    // store each row into the post_label map
    // populate num_post_with_label map here
    void read_csv(csvstream &train_in) {
        vector<pair<string, string>> row;

        if (debug) {
            cout << "training data:" << endl;
        }

        while (train_in >> row) {
            string label;
            string post;

            for (size_t i = 0; i < row.size(); i++) {
                if (row[i].first == "tag") {
                    label = row[i].second;
                }
                if (row[i].first == "content") {
                    post = row[i].second;
                }
            }
            
            // post_label: <string, string>
            post_label.push_back(make_pair(post, label));

            if (debug) {
                cout << "  label = " << label << ", content = " << post << endl;
            }

            // num_post_with_label: <string, int>
            num_post_with_label[label] += 1;
            num_post += 1;
        }
    }

    // process each post into a set of unique words
    // populate the post_unique_words map 
    // also find the vocabulary size here 
    void find_post_unique_words() {
        
        // iterate through the post_label map
        // the keys are the posts
        for (size_t i = 0; i < post_label.size(); i++) {
            string content = post_label[i].first;

            // find the unique words in the current post
            set<string> unique_word = unique_words(content);

            // post_unique_words: <string, string>
            // post_unique_words[content] = unique_word;
            post_unique_words.push_back(make_pair(content, unique_word));
            
            // iterate through the unique word set 
            // and try inserting each word into the vocab set
            // do nothing if word is already counted in vocab
            for (auto const &word: unique_word) {
                vocab.insert(word);
            }
        }

        vocab_size = vocab.size();
    }

    // go through the set of unique words for each post 
    // populate num_post_contain word map 
    // and num_label_contain_word map 
    void process_posts() {

        // post_unique_words: <string, set<string>>
        // the keys are posts and the values are
        // the set of unique words in the posts
        for (size_t i = 0; i < post_unique_words.size(); i++) {
            string post = post_unique_words[i].first;
            string label = post_label[i].second;

            // if (post == "" || post == " ") {
            //     cout << "Accessed empty string" << label;
            // }

            set<string> unique_words = post_unique_words[i].second;

            for (auto const &word: unique_words) {

                // num_post_contain_word: <string, int>
                num_post_contain_word[word] += 1;

                // num_label_contain_word:
                // <string, map<string, int>>
                num_label_contain_word[label][word] += 1;
            }
        }
    }

    // collect data on the training set
    void fit(csvstream &train_in) {
        read_csv(train_in);
        find_post_unique_words();
        process_posts();
    }

    // find the log-likelihood of a word given a label
    double word_proba(const string &word, const string &label) {
        
        // check if the word is in the vocabulary of the training set
        // set::count would return 0 in such cases
        if (vocab.count(word) == 0) {
            return log((double)1/(double)num_post);
        }
        
        // check if the word is contained in any post with the
        // current label
        if (num_label_contain_word[label][word] == 0) {
            return log((double)num_post_contain_word[word]/(double)num_post);
        } 

        return log((double)num_label_contain_word[label][word]/
                   (double)num_post_with_label[label]);
    }

    // find the log-probability score of a post given a label
    double post_proba(const string &post, const string &label) {
        set<string> unique = unique_words(post);

        double score = log((double)num_post_with_label[label]/(double)num_post);

        // iterate through the set of unique words
        // add the score for each word to the overall post score
        for (auto i: unique) {
            score += word_proba(i, label);
        }

        return score;
    }

    // use the num_post_with_label map to iterate over labels in alphabetical order
    // find and return the label that yields the highest log-probability score
    // return value: <label, log-probability score>
    pair<string, double> classify_post(const string &post) {
        double max_score = -10000;
        string classification;

        for (auto i: num_post_with_label) {
            string label = i.first;

            // call post_proba for each label
            double current_score = post_proba(post, label);

            if (current_score > max_score) {
                max_score = current_score;
                classification = label;
            }
        }
        
        return {classification, max_score};
    }


    // debug only
    void labels_output() {
        cout << "classes:" << endl;

        for (auto i: num_post_with_label) {
            string label = i.first;
            int num_post_label = i.second;

            cout << "  " << label << ", " << num_post_label << " examples, "
                 << "log-prior = " << log((double)num_post_label/num_post) << endl;
        }
    }

    // debug only
    void parameters_output() {
        cout << "classifier parameters:" << endl;

        for (auto i: num_label_contain_word) {
            string label = i.first;
            map<string, int> value = i.second;

            for (auto info: value) {
                string word = info.first;
                int count = info.second;
                double score = word_proba(word, label);

                cout << "  " << label << ":" << word << ", count = " << count
                     << ", log-likelihood = " << score << endl; 
            }
        }
    }

    void test_output(csvstream &test_in) {
        int num_correct = 0; 
        string post, true_label;

        cout << "test data:" << endl;

        vector<pair<string, string>> row;

        while (test_in >> row) {
            
            // get the post contents and their true labels
            // from the csvstream
            for (size_t i = 0; i < row.size(); i++) {
                if (row[i].first == "tag") {
                    true_label = row[i].second;
                }
                if (row[i].first == "content") {
                    post = row[i].second;
                }
            }

            test_size += 1;

            pair<string, double> prediction = classify_post(post);
            string predicted_label = prediction.first;
            double score = prediction.second;

            if (predicted_label == true_label) {
                num_correct += 1;
            }            
           
            cout << "  correct = " << true_label << ", predicted = " << predicted_label
                 << ", log-probability score = " << score << endl
                 << "  content = " << post << endl << endl;
        }

        cout << "performance: " << num_correct << " / " << test_size
             << " posts predicted correctly" << endl;
    }
    
    // no --debug argument
    void normal_output(csvstream &test_in) {
        cout << "trained on " << num_post << " examples" << endl << endl;
        test_output(test_in);
    }

    // --debug argument
    void debug_output(csvstream &test_in) {
        cout << "trained on " << num_post << " examples" << endl;

        cout << "vocabulary size = " << vocab_size << endl << endl;

        labels_output();
        parameters_output();
        cout << endl;

        test_output(test_in);
    }

    void output(csvstream &test_in) {
        if (debug) {
            debug_output(test_in);
        } else {
            normal_output(test_in);
        }
    }

private:
    int num_post;
    int vocab_size;
    int test_size;
    bool debug;

    // for each word w, the number of posts that contain w
    // <word, num_post>
    map<string, int> num_post_contain_word;

    // for each label c, the number of posts with that label
    // <label, num_post>
    map<string, int> num_post_with_label;

    // for each label c and word w, the number of post with label c
    // that contains word w
    // <label, <word, num_post>>
    map<string, map<string, int>> num_label_contain_word;

    // the set of unique words in each post
    // <post, set<unique_words>>
    vector<pair<string, set<string>>> post_unique_words;

    // the label of each post in the dataset
    // <post, label>
    vector<pair<string, string>> post_label;

    // set of unique words in the trainging data
    set<string> vocab;
};


int main(int argc, char* argv[]) {
    cout.precision(3);

    // validate commandline arguments are correctly formatted
    if (!validate_cmdline_args(argc, argv)) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }

    string train_filename = argv[1];
    string test_filename = argv[2];
    
    // finished validating cmdline arguments and opening streams

    if (!validate_filenames(train_filename, test_filename)) {
        return 2;
    }

    // checked that both files open correctly
    csvstream train_in(train_filename);
    csvstream test_in(test_filename);

    Classifier model;

    if (argc == 4) {
        model.set_debug(true);
    }

    model.fit(train_in);
    model.output(test_in);

    return 0;
}


bool validate_cmdline_args(const int argc, char* const argv[]) {
    if (argc != 3 && argc != 4) {
        return false;
    }

    if (argc == 4) {
        string debug = argv[3];
        if (debug != "--debug") {
            return false;
        }
    }

    return true;
}


bool validate_filenames(const string &train, const string &test) {
    try {
        csvstream train_in(train);
        csvstream test_in(test);
    } catch (csvstream_exception &e) {
        cout << e.what() << endl;
        return false;
    }

    return true;
}


set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;

    // Read word by word from the stringstream and insert into the set
    while (source >> word) {
    words.insert(word);
    }
    return words;
}
