//
// Created by Xavier VINCENT on 24/12/2023.
//

#include "RTypeNetwork.hpp"

void logMessage(std::string prefix, Message *message, const int width)
{
  std::stringstream ss;
  ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
  ss << GREEN << prefix << " - Worker Thread: " << std::this_thread::get_id() << RESET << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET << message->header.command << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET << message->header.dataLength
     << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET << message->header.clientId << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  std::cout << ss.str();
}

void logResponse(std::string prefix, Response *response, const int width)
{
  std::stringstream ss;
  ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
  ss << GREEN << prefix << " - Worker Thread: " << std::this_thread::get_id() << RESET << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET << response->header.command << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET << response->header.dataLength
     << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET << response->header.clientId << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Status:" << RESET << response->header.status << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Status Message:" << RESET
     << response->header.statusMessage << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  std::cout << ss.str();
}

void logTimedMessage(std::string prefix, TimedMessage timedMessage, Response response, const int width)
{
  auto end = std::chrono::high_resolution_clock::now();
  auto duration_ns =
    std::chrono::duration_cast<std::chrono::nanoseconds>(end - timedMessage.timestamp).count();
  auto milliseconds = duration_ns / 1000000;
  auto remaining_ns = duration_ns % 1000000;

  std::stringstream ss;
  ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
  ss << GREEN << prefix << " - Worker Thread: " << std::this_thread::get_id() << RESET << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET << response.header.command << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET << response.header.dataLength
     << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET << response.header.clientId << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Status:" << RESET << response.header.status << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Status Message:" << RESET << response.header.statusMessage
     << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Duration:" << milliseconds << "," << remaining_ns
     << " ms\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";

  std::cout << ss.str();
}
