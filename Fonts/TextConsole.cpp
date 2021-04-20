#include "TextConsole.h"

#include <SDL.h>

#include <algorithm>
#include <iterator>
#include <sstream>

#include "TextRenderer.h"

namespace cgl {

TextConsole::TextConsole() {
  m_consoleTimer = 0.0;

  m_commands.push_back("help");
  m_commandDescriptions.push_back("help [commandName]");
}

void TextConsole::AddText(std::string text) { m_currentLine += text; }

void TextConsole::showHelp() {
  m_lines.push_back("List of commands:");
  for (uint32_t i = 0; i < m_commands.size(); i++) {
    std::stringstream ss;
    ss << " - " << m_commands[i];
    m_lines.push_back(ss.str());
  }
}

void TextConsole::showHelp(std::string inputCommand) {
  if (std::find(m_commands.begin(), m_commands.end(), inputCommand) !=
      m_commands.end()) {
    if (inputCommand.compare("help") == 0) {
      m_lines.push_back(" - help : lists all commands");
      m_lines.push_back(" - help [command] : finds help for \"command\"");
    }
  } else {
    std::stringstream ss;
    ss << "Invalid Command: " << inputCommand;
    m_lines.push_back(ss.str());
    m_lines.push_back("Type \"help\" for commands.");
  }
}

void TextConsole::choosePreviousCommand() {
  int maxCommandIndex = m_previousEnteredCommands.size() - 1;
  m_currentPreviousCommand =
      glm::clamp(m_currentPreviousCommand, -1, maxCommandIndex);

  if (m_currentPreviousCommand >= 0) {
    m_currentLine =
        m_previousEnteredCommands[maxCommandIndex - m_currentPreviousCommand];
  } else {
    m_currentLine = "";
  }
}

void TextConsole::Up() {
  m_currentPreviousCommand++;
  choosePreviousCommand();
}
void TextConsole::Down() {
  m_currentPreviousCommand--;
  choosePreviousCommand();
}

void TextConsole::Tab() {
  std::vector<std::string> foundStrings;
  uint32_t strSize = m_currentLine.length();

  for (uint32_t i = 0; i < m_commands.size(); i++) {
    if (m_commands[i].compare(0, strSize, m_currentLine) == 0) {
      foundStrings.push_back(m_commands[i]);
    }
  }

  // if only found command, replace current line
  if (foundStrings.size() == 1) {
    m_currentLine = foundStrings[0];
  } else if (foundStrings.size() > 1) {
    m_lines.push_back("Matching commands:");
    for (uint32_t i = 0; i < foundStrings.size(); i++) {
      std::stringstream ss;
      ss << " - " << foundStrings[i];
      m_lines.push_back(ss.str());
    }
  }
}

void TextConsole::Return() {
  std::stringstream ss;
  ss << ">> " << m_currentLine;
  m_lines.push_back(ss.str());

  m_previousEnteredCommands.push_back(m_currentLine);
  m_currentPreviousCommand = -1;

  using namespace std;

  if (!m_currentLine.empty()) {
    istringstream iss(m_currentLine);

    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};

    string inputCommand = tokens[0];

    if (find(m_commands.begin(), m_commands.end(), inputCommand) !=
        m_commands.end()) {
      if (inputCommand.compare("help") == 0 && tokens.size() == 1) {
        showHelp();
      }
      if (inputCommand.compare("help") == 0 && tokens.size() == 2) {
        showHelp(tokens[1]);
      }

    } else {
      stringstream ss;
      ss << "Invalid Command: " << inputCommand;
      m_lines.push_back(ss.str());
      m_lines.push_back("Type \"help\" for commands.");
    }
  }

  m_currentLine = "";
}

void TextConsole::Backspace() {
  if (!m_currentLine.empty()) {
    m_currentLine.erase(m_currentLine.size() - 1, 1);
  }
}

std::string TextConsole::ToString() {
  std::stringstream ss;
  for (uint32_t i = 0; i < m_lines.size(); i++) {
    ss << m_lines[i] << std::endl;
  }

  ss << ">> " << m_currentLine << std::endl;

  return ss.str();
}

void TextConsole::Display(double dt) {
  m_consoleTimer += dt;
  bool showCursor = false;

  double halfSecond = 0.5;
  double oneSecond = 1.0;

  if (m_consoleTimer > halfSecond) {
    showCursor = true;
  }
  if (m_consoleTimer > oneSecond) {
    m_consoleTimer -= oneSecond;
  }

  float fontSize = static_cast<float>(TextRenderer::FontSize());

  float fontPos = 0;

  std::stringstream ss;
  ss << ">> " << m_currentLine;
  if (showCursor) {
    ss << "_";
  }

  TextRenderer::RenderText(glm::vec2(0, fontPos), ss.str().c_str());
  fontPos += fontSize;

  for (uint32_t i = m_lines.size(); i-- > 0;) {
    if (!m_lines[i].empty()) {
      TextRenderer::RenderText(glm::vec2(0, fontPos), m_lines[i].c_str());
    }

    fontPos += fontSize;
  }
}

}  // namespace cgl
