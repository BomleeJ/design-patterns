#include <iostream>
#include <chrono>
#include <vector>
struct Timer {
    using clock = std::chrono::steady_clock;

    clock::time_point m_StartTime;
    clock::time_point m_EndTime;

    void start() {
        m_StartTime = clock::now();
    }

    void stop() {
        m_EndTime = clock::now();
    }

    double elapsedMilliseconds() const {
        return std::chrono::duration<double, std::milli>(
            m_EndTime - m_StartTime
        ).count();
    }
};

template<typename Derived>
class Logger {
    public:
        void log() {
            static_cast<Derived*>(this)->implementation();
        }
    private:
        void implementation() { }
};

class ConsoleLogger : public Logger<ConsoleLogger> {
    public:
    void implementation() {
        std::cout << "LOG: Hello There\n";
    }
};

class ErrorLogger : public Logger<ErrorLogger> {
    public:
    void implementation() {
        std::cout << "ERROR: Hello There\n";
    }
};

template<typename Derived>
class Base {
    public:
    void interface() {
        static_cast<Derived*>(this)->impl();
    }

    virtual void vimpl() = 0;
};

class C : public Base<C> {
    public:
    void impl() {
        std::vector<int> vec{};
        for (int i = 0; i < 100000; i++) {
            vec.push_back(i);
        }
    }
    
    void vimpl() override {
        std::vector<int> vec{};
        for (int i = 0; i < 100000; i++) {
            vec.push_back(i);
        }
    }
};

int main() {

    ErrorLogger e;
    ConsoleLogger c;
    e.log();
    c.log();

    C timeTest; 

    Timer t; 

    std::cout << "CRTP method\n";

    t.start();

    for (int i = 0; i < 100; i++)
    {
        timeTest.interface();
    }

    t.stop();
    std::cout << t.elapsedMilliseconds() << std::endl;

    t.start();

    for (int i = 0; i < 100; i++)
    {
        timeTest.vimpl();
    }

    t.stop();
    std::cout << t.elapsedMilliseconds() << std::endl;


}