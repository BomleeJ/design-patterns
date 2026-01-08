#include <iostream>
#include <string>
#include <fstream>

class Logger {
  
private:
    std::ofstream os;
    
    Logger(const std::string& filename)
    {
        os.open(filename);
    }
    
    ~Logger()
    {
        os.close();
    }
    
    Logger() = delete;
    Logger& operator=(const Logger& rhs) = delete;
    Logger& operator=(Logger&& rhs) = delete;
    Logger(const Logger& rhs) = delete;
    Logger(Logger&& rhs) = delete;
    
    
public:
    static Logger& get() {
        static Logger lg("app.txt");
        return lg;
    }
    
    void log(const std::string& val) {
        os << val << std::endl;
    }
};

int main() {
    Logger::get().log("App started");
    Logger::get().log("Processing data");
    Logger::get().log("App finished");
    return 0;
}
