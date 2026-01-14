#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Fly weight is used when we use tricks to reduce memory consumption ig (in this scenario we don't want to modify original text)
struct TextRange; 
using namespace std;
struct TextRange {
    size_t start, end;
    bool capitalize;
    TextRange(size_t start_, size_t end_): 
        start(start_), 
        end(end_) 
    { }

    bool contains(size_t idx) const {
        return start <= idx && idx <= end;
    }
};

struct NaiveTextFormatter {
    bool* isCapital; 
    std::string txt; 
    NaiveTextFormatter(std::string txt_):txt{txt_}  {
        isCapital = new bool[txt_.size()];
        
    }

    void capitalize(size_t start, size_t end) {
        for (size_t i = start; i <= end; i++) {
            isCapital[i] = true;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const NaiveTextFormatter& obj) {
        string s = "";
        for (size_t i = 0; i < obj.txt.size(); i++)
        {
            char c = obj.txt.at(i);
            if (obj.isCapital[i])
            {
                s += toupper(c);
            }
            else 
            {
                s += c;
            }

        }
        cout << "HERE\n";
        return os << s;
    }


    ~NaiveTextFormatter() {
        delete[] isCapital;
    }

};

struct TextFormatter {
    std::string_view txt; 
    std::vector<TextRange> ranges;
    
    TextFormatter(std::string_view txt_): 
        txt(txt_), ranges {} 
    { std::cout << txt << std::endl; }

    TextRange& get_range(size_t start, size_t end) {
        ranges.emplace_back(TextRange{start, end});
        return *ranges.rbegin();
    }

    friend std::ostream& operator<<(std::ostream& os, const TextFormatter obj) {
        std::string s = "";
        for (int i = 0; i < obj.txt.size(); i++) 
        {
            char c = obj.txt.at(i);
            for (const auto& range : obj.ranges) 
            {
                if (range.contains(i) && range.capitalize)
                {
                    c = std::toupper(c);
                }
            }
            s += c;
        }
        return os << s;
    }

};

int main() {
    TextFormatter tf("I am testing my sentence capitalizer");
    tf.get_range(2, 3).capitalize = true;
    tf.get_range(25, 35).capitalize = true;

    std::cout << tf << std::endl;
    std::cout << sizeof(tf) << std::endl;
    
    NaiveTextFormatter ntf {"I am testing my sentence capitalizer the naive version in the REAL way"};

    ntf.capitalize(2, 3);
    ntf.capitalize(25, 35);
    
    cout << ntf;
    cout << sizeof(ntf);

    return 0;

}