#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ios>
#include <cmath>
#include <fstream>
#include <sstream>
#include <list>
#include <functional>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include <cstring>
#include <thread>
#include <mutex>
#include <tuple>
#include <queue>
#include <condition_variable>

// KNN moudle functions
std::vector< std::pair<double, int> > bubbleSort(std::vector< std::pair<double, int> > v, int size);
int KNN(std::vector< std::vector<double> > x_train, std::vector<int> y_train, std::vector<double> sample, int k, std::string func, int labels_number);

// Calculator moudle functions
double euclidian_distance_function(std::vector<double> vec1, std::vector<double> vec2);
double manheten_distance_function(std::vector<double> vec1, std::vector<double> vec2);
double chebyshev_distance_function(std::vector<double> vec1, std::vector<double> vec2);
double canberra_distance_function(std::vector<double> vec1, std::vector<double> vec2);
double minkowski_distance_function(std::vector<double> vec1, std::vector<double> vec2);

// main moudle functions
bool check_size(int size, std::string csv_type);
bool check_args(int size, std::string csv_type, std::string dist_func);
std::string fetch_path(std::string input);
//std::vector<double> parser(std::string string_Vector);
std::string get_label_classify(int label);
void print_vec(std::vector<std::vector<double> > x_train);
int get_labels_number(std::string csv_type);
std::string handle_process(int k, std::string csv_type, std::string distance_function, std::string vec);

// client moudle functions
bool is_ip(const char* str);
bool is_port(int p);
int client_request(char* ip, int port);

// server moudle functions
bool is_port(int p);
void check_csv_arg(std::string csv_type);
std::string normalize_csv_input(std::string csv);
bool extract_regions(const std::string& str, std::string& numbers, std::string& distance_function, int& integer);
int server_response();


class SocketIO
{
    int socket_;

    public:
    SocketIO(int socket);

    std::string Read();
    void Write(const std::string &message);
};


struct ClientInfo {
  std::tuple<std::string, std::string> tuple_csv_CLI = {"None", "None"};
  std::tuple<std::string, std::string> tuple_params_CLI = {"None", "None"};;
  std::vector<std::vector<double> > x_train;
  std::vector<int> y_train;
  int type;
  int type_amount;
  std::string final_results;
  bool has_final_results = false;
};

class Command {
 public:
  Command(ClientInfo& client_info) : client_info_(client_info) {}
  virtual ~Command() = default;
  virtual void execute(SocketIO& socketIO) = 0;
  virtual std::string getDescription() = 0;

  ClientInfo& client_info_;
};

class UploadFileCommand : public Command { 
 public:
  UploadFileCommand(ClientInfo& client_info);
  void execute(SocketIO& socketIO);
  std::string getDescription();
};

class AlgorithmSettingsCommand : public Command {
 public:
  AlgorithmSettingsCommand(ClientInfo& client_info);
  void execute(SocketIO& socketIO);
  std::string getDescription();
};

class ClassifyDataCommand : public Command {
 public:
  ClassifyDataCommand(ClientInfo& client_info);
  void execute(SocketIO& socketIO);
  std::string getDescription();

};

class DisplayResultsCommand : public Command {
 public:
  DisplayResultsCommand(ClientInfo& client_info);
  void execute(SocketIO& socketIO);
  std::string getDescription();
};

class DownloadResultsCommand : public Command {
 public:
  DownloadResultsCommand(ClientInfo& client_info);
  void execute(SocketIO& socketIO);
  std::string getDescription();
};

class ExitCommand : public Command {
 public:
  ExitCommand(ClientInfo& client_info);
  void execute(SocketIO& socketIO);
  std::string getDescription();
};



std::string generate_welcome_msg();

class CLI {

private:
SocketIO socketIO;
ClientInfo& client_info;
std::vector<std::unique_ptr <Command> > commands;

public:
CLI(int socket, ClientInfo& client_info);
std::vector<std::vector<double>> get_x_train();
std::vector<int> get_y_train();

void analysis_choice(std::string choice);
void start();

};

void handle_response(SocketIO& socketIO);
std::string get_type_train_test(std::string path);

void parseInput(const std::string &input);


std::vector<std::string> parse_sampels(const std::string &data);
std::vector<double> parse_test(const std::string &s);
std::string get_classification(int type, int subtype);
int get_type(const std::string &s);
int check_valid_string(const std::string& str);
int get_type_amount(int type);
std::vector<double> parser(std::string string_Vector, int stop_idx);
void create_split(std::string line, std::vector<double>& vec, int& label_num);
void generate_data(const std::string& data, std::vector<std::vector<double> >& x_train, std::vector<int>& y_train);
std::string reverse(std::string str);
int get_label_number(std::string label);