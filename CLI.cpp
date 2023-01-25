
#include "header.h"

std::string generate_welcome_msg() {
std::string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n 1. Upload an unclassified csv data file\n 2. Algorithm settings\n 3. Classify data\n 4. Display results\n 5. Download results\n 8. Exit";
return menu;
}

CLI::CLI(int socket, ClientInfo& client_info) : socketIO(socket), client_info(client_info) {
  commands.push_back(std::make_unique<UploadFileCommand>(client_info));
  commands.push_back(std::make_unique<AlgorithmSettingsCommand>(client_info));
  commands.push_back(std::make_unique<ClassifyDataCommand>(client_info));
  commands.push_back(std::make_unique<DisplayResultsCommand>(client_info));
  commands.push_back(std::make_unique<DownloadResultsCommand>(client_info));
  commands.push_back(std::make_unique<ExitCommand>(client_info));
}



void CLI::analysis_choice(std::string choice) {
     int i = check_valid_string(choice); 
    if(i != -1 && i != 8){
      this->commands[i-1]->execute(this->socketIO);
      // if (i == 1) {
      //   std::cout << std::get<0>(this->client_info.tuple_csv_CLI) << std::endl;
      // }
    }
    if (i == 8) {
      this->commands[5]->execute(this->socketIO);
    }
}


void CLI::start() {
  std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
  std::string choice;
  while (true) {
    this->socketIO.Write(generate_welcome_msg());
    choice = this->socketIO.Read();
    analysis_choice(choice);
    if(choice == "8"){ break; }
  }
}
