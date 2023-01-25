#include "header.h"


std::vector<std::string> parse_sampels(const std::string &data) {
    std::vector<std::string> lines;
    std::stringstream ss(data);
    std::string line;
    while (std::getline(ss, line, '\n')) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<double> parse_test(const std::string &s) {
    
    std::vector<double> numbers;
    std::stringstream ss(s);
    std::string number;
    while (std::getline(ss, number, ',')) {
        numbers.push_back(std::stod(number));
    }
    return numbers;
}


std::string get_classification(int type, int subtype) {
    if (type == 1) {
      if(subtype == 0) { return "Iris-setosa"; }
      if(subtype == 1) { return "Iris-versicolor"; }
      if(subtype == 2) { return "Iris-virginica"; }
    }

    if (type == 2) {
      if(subtype == 0) { return "red wine"; }
      if(subtype == 1) { return "white wine"; }
      if(subtype == 2) { return "Sparkling wine"; }
    }

    if (type == 3) {
      if(subtype == 0) { return "SEKER"; }
      if(subtype == 1) { return "BARBUNYA"; }
      if(subtype == 2) { return "BOMBAY"; }
      if(subtype == 3) { return "CALI"; }
      if(subtype == 4) { return "HOROZ"; }
      if(subtype == 5) { return "SIRA"; }
      if(subtype == 6) { return "DERMASON"; }
    }
    
    return "500";
}


int get_type(const std::string &s) {
    if (s.find("Iris-setosa") != std::string::npos) {
        return 1;
    } else if (s.find("white wine") != std::string::npos) {
        return 2;
    } else if (s.find("SEKER") != std::string::npos) {
        return 3;
    } else {
        return -1;
    }
}


int check_valid_string(const std::string& str) {
  int num;
  try { num = std::stoi(str); }
  catch (...) { return false; }

  if (num >= 1 && num <= 5) { return num; }
  else if (num == 8) { return 8; }
  else { return -1; }
}

int get_type_amount(int type) {
  if (type == 1) {return 3;}
  if (type == 2) {return 3;}
  if (type == 3) {return 6;}
  return -1;
}

std::vector<double> parser(std::string string_Vector, int stop_idx) {
    std::vector<double> Vector;
    std::string current;

    for(int i = 0; i <= stop_idx; i++)
    {
        if(string_Vector[i] == ',' || string_Vector[i] == '\0') 
        {
            try { Vector.push_back(stod(current)); current = ""; } 
            catch (...) { }
        }
        else { current += string_Vector[i]; }
    }
    return Vector;
}

void create_split(std::string line, std::vector<double>& vec, int& label_num) {
    if(line != "") {
        int line_length = line.size(); 
        int i = line_length;
        std::string label = "";
        int idx_of_split;
        for(i; i > 0; i--) {
            if(line[i] == ',') { idx_of_split = i; break; }
            else{ label += line[i]; }
        }
        std::string r = reverse(label);
        label_num = get_label_number(r);
        vec = parser(line, idx_of_split);
    }
}

void generate_data(const std::string& data, std::vector<std::vector<double> >& x_train, std::vector<int>& y_train) {
    std::stringstream inputStream(data);
    std::string line;
    std::vector<double> current_vec;
    int label;
    while(std::getline(inputStream, line)) {
        create_split(line , current_vec, label);
        line = ""; 
        x_train.push_back(current_vec);
        y_train.push_back(label);
    } 
}

std::string reverse(std::string str) {
    int i = str.size() - 1;
    std::string true_label;
    for(i; i > 0; i--) { true_label += str[i]; }
    return true_label;
}

int get_label_number(std::string label) {
    
    if(label == "Iris-setosa") { return 0; }
    if(label == "Iris-versicolor") { return 1; }
    if(label == "Iris-virginica") { return 2; }

    if(label == "red wine") { return 0; }
    if(label == "white wine") { return 1; }
    if(label == "Sparkling wine") { return 2; }

    if(label == "SEKER") { return 0; }
    if(label == "BARBUNYA") { return 1; }
    if(label == "BOMBAY") { return 2; }
    if(label == "CALI") { return 3; }
    if(label == "HOROZ") { return 4; }
    if(label == "SIRA") { return 5; }
    if(label == "DERMASON") { return 6; }
    
    return -1;
}