//
// Created by Xavier VINCENT on 24/12/2023.
//

#include "RTypeClient.hpp"

void logMessage(Message *message, const int width)
{
  std::stringstream ss;
  ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
  ss << GREEN
     << "Server message - Worker Thread: " << std::this_thread::get_id()
     << RESET << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET
     << message->header.command << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET
     << message->header.dataLength << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET
     << message->header.clientId << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  std::cout << ss.str();
}

void logResponse(Response *response, const int width)
{
  std::stringstream ss;
  ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
  ss << GREEN
     << "Server response - Worker Thread: " << std::this_thread::get_id()
     << RESET << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET
     << response->header.command << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET
     << response->header.dataLength << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET
     << response->header.clientId << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Status:" << RESET
     << response->header.status << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Status Message:" << RESET
     << response->header.statusMessage << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  std::cout << ss.str();
}
