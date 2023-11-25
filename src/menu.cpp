#include "menu.h"
#include "../rlutil/rlutil.h"
#define setYellow rlutil::setColor(rlutil::YELLOW)
#define setLightRed rlutil::setColor(rlutil::LIGHTRED)
#define setGreen rlutil::setColor(rlutil::GREEN)
    string Menu:: currentDateTime(){
        time_t     now = time(nullptr);
        struct tm  tstruct{};
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }
    void Menu::printMenuFRONT(){
        setYellow;
        std::cout << currentDateTime() << std::endl;
        std::cout << "***********************************************" << std::endl;
        std::cout << "\tWELCOME TO OUR BOOKING SYSTEM" << std::endl;
        std::cout << "***********************************************" << std::endl;
        std::cout << "1.---Add customer data---" << std::endl;
        std::cout << "2.---Modify customer data---" << std::endl;
        std::cout << "3.---Search customer---" << std::endl;
        std::cout << "4.---Remove customer data---" << std::endl;
        std::cout << "5.---Print customer data---" << std::endl;
        setGreen;
        std::cout << "6.---Book a hotel(next page)---" << std::endl;
        setLightRed;
        std::cout << "7.---Log out---" << std::endl;
        std::cout << "8.---Exit program---" << std::endl;
        rlutil::resetColor();
    }
    void Menu::printMenuHOTEL(){
        setYellow;
        std::cout << currentDateTime() << std::endl;
        std::cout << "***********************************************" << std::endl;
        std::cout << "\tWELCOME TO OUR BOOKING SYSTEM" << std::endl;
        std::cout << "***********************************************" << std::endl;
        setGreen;
        std::cout << "1.---Book a hotel---" << std::endl;
        std::cout << "2.---Show all hotels---" << std::endl;
        std::cout << "3.---Search hotel---" << std::endl;
        std::cout << "4.---Leave recension---" << std::endl;
        setLightRed;
        std::cout << "5.---go back---" << std::endl;
        rlutil::resetColor();
    }
    void Menu::printRegisterLoginWindow(){
        setYellow;
        std::cout << currentDateTime() << std::endl;
        std::cout << "***********************************************" << std::endl;
        std::cout << "\tWELCOME TO OUR BOOKING SYSTEM" << std::endl;
        std::cout << "***********************************************" << std::endl;
        std::cout << "1.---Register---" << std::endl;
        std::cout << "2.---Login---" << std::endl;
        std::cout << "3.---Forgot password---" << std::endl;
        setLightRed;
        std::cout << "4.---EXIT---" << std::endl;
        rlutil::resetColor();
    }

    void Menu::ProgramReadyBar() {
        indicators::IndeterminateProgressBar bar{
            indicators::option::BarWidth{40},
            indicators::option::Start{"["},
            indicators::option::Fill{"·"},
            indicators::option::Lead{"<==>"},
            indicators::option::End{"]"},
            indicators::option::PostfixText{"Checking for Updates"},
            indicators::option::ForegroundColor{indicators::Color::yellow},
            indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
        };

        indicators::show_console_cursor(false);
        auto job = [&bar]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            bar.mark_as_completed();
            std::cout << termcolor::bold << termcolor::green
                      << "Program loaded and up to date!\n" << termcolor::reset;
        };
        std::thread job_completion_thread(job);

        // Update bar state
        while (!bar.is_completed()) {
            bar.tick();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        job_completion_thread.join();

        indicators::show_console_cursor(true);
    }

    void Menu::ProgressBarExit() {
        indicators::IndeterminateProgressBar bar{
                indicators::option::BarWidth{40},
                indicators::option::Start{"["},
                indicators::option::Fill{"·"},
                indicators::option::Lead{"<==>"},
                indicators::option::End{"]"},
                indicators::option::PostfixText{"Exiting program"},
                indicators::option::ForegroundColor{indicators::Color::red},
                indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
        };

        indicators::show_console_cursor(false);
        auto job = [&bar]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            bar.mark_as_completed();
            std::cout << termcolor::bold << termcolor::green
                      << "Program exited!\n" << termcolor::reset;
        };
        std::thread job_completion_thread(job);

        // Update bar state
        while (!bar.is_completed()) {
            bar.tick();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        job_completion_thread.join();

        indicators::show_console_cursor(true);
    }

    void Menu::SpinnerInTerminal() {
    using namespace indicators;
        indicators::ProgressSpinner spinner{
                option::PostfixText{"Checking credentials"},
                option::ForegroundColor{Color::yellow},
                option::SpinnerStates{std::vector<std::string>{"⠈", "⠐", "⠠", "⢀", "⡀", "⠄", "⠂", "⠁"}},
                option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
        };

        // Update spinner state
        auto job = [&spinner]() {
            while (true) {
                if (spinner.is_completed()) {
                    spinner.set_option(option::ForegroundColor{Color::green});
                    spinner.set_option(option::PrefixText{"✔"});
                    spinner.set_option(option::ShowSpinner{false});
                    spinner.set_option(option::ShowPercentage{false});
                    spinner.set_option(option::PostfixText{"Authenticated!"});
                    spinner.mark_as_completed();
                    break;
                } else
                    spinner.tick();
                std::this_thread::sleep_for(std::chrono::milliseconds(40));
            }
        };
        std::thread thread(job);
        thread.join();

    }
