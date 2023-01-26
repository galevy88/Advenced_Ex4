
#include "header.h"


  UploadFileCommand::UploadFileCommand(ClientInfo& client_info) : Command(client_info) {}
  void UploadFileCommand::execute(SocketIO& socketIO) {
  std::string csv_train;
  std::string csv_test;
  std::string upload_train_msg = "Please upload your local train CSV file.";
  socketIO.Write(upload_train_msg);
  std::string line;
  do {
    line = socketIO.Read();
    if(line != "Done.") { csv_train += line + "\n"; }
  }
  while(line != "Done.");
  line = "";

  std::string upload_test_msg = "Please upload your local test CSV file.";
  socketIO.Write(upload_test_msg);
  do {
    line = socketIO.Read();
    if(line != "Done.") { csv_test += line + "\n"; }
    
  }
  while(line != "Done.");

  this->client_info_.tuple_csv_CLI = std::tuple<std::string, std::string>(csv_train, csv_test);
  this->client_info_.type = get_type(std::get<0>(this->client_info_.tuple_csv_CLI));
  this->client_info_.type_amount = get_type_amount(this->client_info_.type);
  generate_data(std::get<0>(this->client_info_.tuple_csv_CLI), this->client_info_.x_train, this->client_info_.y_train);
    
  }
  std::string UploadFileCommand::getDescription() {
    return "Upload an unclassified csv data file";
  }


  AlgorithmSettingsCommand::AlgorithmSettingsCommand(ClientInfo& client_info) : Command(client_info) {}
  void AlgorithmSettingsCommand::execute(SocketIO& socketIO) {

  std::string K = std::get<0>(this->client_info_.tuple_params_CLI);
  std::string Mat = std::get<1>(this->client_info_.tuple_params_CLI);
  std::string params_msg = "The current KNN parameters are: K = " + K + ", distance metric = " + Mat;
  socketIO.Write(params_msg);
  std::string params = socketIO.Read();
  if(!params.empty()) { 
      std::istringstream iss(params);
      iss >> std::get<0>(this->client_info_.tuple_params_CLI) >> std::get<1>(this->client_info_.tuple_params_CLI);
      }
  else{
    std::get<0>(this->client_info_.tuple_params_CLI) = K;
    std::get<1>(this->client_info_.tuple_params_CLI) = Mat;
  }

  }
  std::string AlgorithmSettingsCommand::getDescription() {
    return "Algorithm settings";
  }

  ClassifyDataCommand::ClassifyDataCommand(ClientInfo& client_info) : Command(client_info) {}
  void ClassifyDataCommand::execute(SocketIO& socketIO) {

      std::string sampels_str = std::get<1>(this->client_info_.tuple_csv_CLI);
      std::vector<std::string> sampels = parse_sampels(sampels_str);
      std::string K = std::get<0>(this->client_info_.tuple_params_CLI);
      std::string metric = std::get<1>(this->client_info_.tuple_params_CLI);
      
      int k;
      std::string result;
      int i = 1;
      if (K != "None" && sampels_str != "None") { 
        k = std::stoi(K);
        for(const auto &s: sampels) {
          std::vector<double> vec = parse_test(s);
          int imax = KNN(this->client_info_.x_train, this->client_info_.y_train, vec, k, metric, this->client_info_.type_amount);

          result += std::to_string(i) + " " + get_classification(this->client_info_.type, imax) + "\n";
          i++;
        }
        this->client_info_.has_final_results = true;
        socketIO.Write("classifying data complete");
      }
      else { socketIO.Write("please upload data"); }
      result += "Done.\n";
      this->client_info_.final_results = result;

  }
  std::string ClassifyDataCommand::getDescription() {
    return "Classify data";
  }

  DisplayResultsCommand::DisplayResultsCommand(ClientInfo& client_info) : Command(client_info) {}
  void DisplayResultsCommand::execute(SocketIO& socketIO) {
    if(this->client_info_.has_final_results) {
      socketIO.Write(this->client_info_.final_results);
    }
    else {
      std::string msg = "please classify the data";
      socketIO.Write(msg);
    }
  }
  std::string DisplayResultsCommand::getDescription()  {
    return "Display results";
  }


  DownloadResultsCommand::DownloadResultsCommand(ClientInfo& client_info) : Command(client_info) {}
  void DownloadResultsCommand::execute(SocketIO& socketIO) {
      std::string packet = "Download\n" + this->client_info_.final_results;
      if(this->client_info_.has_final_results) { socketIO.Write(packet); }
      else  {socketIO.Write("No final results yet."); }
  }
  std::string DownloadResultsCommand::getDescription() {
    return "Download results";
  }

  ExitCommand::ExitCommand(ClientInfo& client_info) : Command(client_info) {}
  void ExitCommand::execute(SocketIO& socketIO) {
    std::string msg = "Exiting...";
    socketIO.Write(msg);
    socketIO.Read();
  }
  std::string ExitCommand::getDescription() {
    return "Exit";
  }
