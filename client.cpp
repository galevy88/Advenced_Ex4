
#include "header.h"


// const int PORT = 8000;
std::string K_ = "None";
std::string Matric = "None";

int analysis_message(const std::string& message) {
  if (message.find("Welcome to the KNN Classifier Server. Please choose an option:\n 1. Upload an unclassified csv data file\n 2. Algorithm settings\n 3. Classify data\n 4. Display results\n 5. Download results\n 8. Exit") != std::string::npos) { return 1; }
  if (message.find("Please upload your local train CSV file.") != std::string::npos) { return 2; }
  if (message.find("Please upload your local test CSV file.") != std::string::npos) { return 3; }
  if (message.find("The current KNN parameters") != std::string::npos) { return 4; }
  if (message.find("Download") != std::string::npos) { return 5; }
  if (message.find("Exiting...") != std::string::npos) { return 6; }
  return -1;
}

std::string get_type_train_test(std::string path) {
    if (path.find("iris") != std::string::npos) { return "iris"; }
    if (path.find("wine") != std::string::npos) { return "wine"; }
    if (path.find("beans") != std::string::npos) { return "beans"; }
    return "";
}

void upload_csv_train_file(SocketIO& socketIO, std::string message, std::string& type_train) {
    std::string path;
    std::fstream file;
    std::string line;
    
    while (true) {
        std::getline(std::cin, path);
        type_train = get_type_train_test(path);
        file.open(path, std::ios::in);
        if (!file.good()) {
            std::cout << "Please upload your local train CSV file." << std::endl;
            continue;
        }
        break;
    }

    while(std::getline(file, line)) {
      socketIO.Write(line);
    }
    socketIO.Write("Done.");
    file.close();
}


void upload_csv_test_file(SocketIO& socketIO, std::string message, std::string& type_train) {
    std::string path;
    std::string type_test;
    std::fstream file;
    std::string line;

    while (true) {
        std::getline(std::cin, path);
        type_test = get_type_train_test(path);
        if (type_test != type_train) {
            std::cout << "Please upload your local test CSV file." << std::endl;
            continue;
        }
        file.open(path, std::ios::in);
        if (!file.good()) {
            std::cout << "Please upload your local test CSV file." << std::endl;
            continue;
        }
        break;
    }

    while(std::getline(file, line)) {
      socketIO.Write(line);
    }
    socketIO.Write("Done.");
    std::cout << "Upload complete." << std::endl;
    file.close();
}




bool is_string_numeric(const std::string& str) {
    for (const char& c : str) {
        if (!std::isdigit(c)) { return false; } }
    return true;
}


int check_if_valid_input(const std::string& input) {

        if(input.empty()){ return 1; }
        
        std::istringstream iss(input);
        std::string first, second;
        if (iss >> first && iss >> second) {
        
            if (is_string_numeric(first)) {
        
                if (second == "AUC" || second == "MAN" || second == "CHB" || second == "MIN" || second == "CAN") {
                    std::string temp;
                    return 1; 
                } 
                else { std::cout << "Invalid value for metric" << std::endl; return 0;} } 
                else { std::cout << "Invalid value for K" << std::endl; return 0;} }
        else {
                std::cout << "Invalid value" << std::endl;
                return 0;
        }
}


void parseInput(const std::string &input) {
    std::stringstream ss(input);
    ss >> K_ >> Matric;
}

std::string get_params_input() {
    std::string input;
    std::getline(std::cin, input);
    int result = check_if_valid_input(input);
    while(result != 1) { 
      std::getline(std::cin, input); 
      result = check_if_valid_input(input); 
    }
    parseInput(input);
    if(input.empty()) { 
      input = K_ + " " + Matric;
    }
    return input;
}

bool check_for_final_results(std::string& message, std::string& final_results) {
  if (message.find("Done.") != std::string::npos) { final_results = message; return true; }
  return false;
}

void download_results(std::string& final_results) {
  std::cout << "Please enter your download path" << std::endl;
  std::string path;
  std::getline(std::cin, path);
  std::ofstream file(path);
  file << final_results;
  file.close();
}


void handle_response(SocketIO& socketIO) {
  std::string response;
  std::getline(std::cin, response);

    while (response != "1" && response != "2" && response != "3" && response != "4" && response != "5" && response != "8") {
    std::cout << "You have to choose 1 or 2 or 3 or 4 or 5 or 8" << std::endl;
    std::getline(std::cin, response);
  }

  socketIO.Write(response);
}

int main(int argc, char* argv[]) {
  int PORT = atoi(argv[1]);
  // Create a socket
  int socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_ < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Set up the server address and port
  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
  server_address.sin_port = htons(PORT);

  // Connect to the server
  if (connect(socket_, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    return 1;
  }
  
SocketIO socket(socket_);
std::string final_results;
bool has_results = false;

std::string type_train;
while (true) {
    std::string message = socket.Read();
    std::cout << message << std::endl;
    
    int analysis = analysis_message(message);
    if (analysis == 1) { handle_response(socket); }
    if (analysis == 2) { upload_csv_train_file(socket, message, type_train); }
    if (analysis == 3) { upload_csv_test_file(socket, message, type_train); }
    if (analysis == 4) { std::string params = get_params_input(); socket.Write(params); }
    if (analysis == 5) { download_results(message); }
    if (analysis == 6) { break; }
}


  // Close the socket
  close(socket_);
  
  return 0;
}
