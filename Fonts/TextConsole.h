#ifndef TEXT_CONSOLE_H
#define TEXT_CONSOLE_H

/* This is the main class for the text console, which is an interactive
   console to add/remove/save/load scattering simulations */

#include <vector>
#include <string>

namespace cgl {

class TextConsole {
protected:
  std::vector<std::string> m_lines;

  std::string m_currentLine;

  double m_consoleTimer;

  std::vector<std::string> m_commands;
  std::vector<std::string> m_commandDescriptions;

  std::vector<std::string> m_previousEnteredCommands;
  int m_currentPreviousCommand;

  void showHelp();
  void showHelp(std::string);

  void choosePreviousCommand();
public:
    TextConsole();

    ~TextConsole() {

    }

    //input is one key at a time, or enter to complete a command
    void AddText(std::string text);

    void Up();
    void Down();
    void Tab();

    void Return();
    void Backspace();

    void Display(double dt);

    std::string ToString();

};

}

#endif
