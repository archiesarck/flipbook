// #include "includes.h"
#include "runtime.h"
using namespace std;

bool generate_tokens(string line, vector<string> &tokens){
    if(line.empty()) return false;
    if(line[0]=='\n') return false;
    string token = "";
    for(int i = 0; i<line.size(); i++){
        if(line[i]==' '){
            if(!token.empty()) tokens.push_back(token);
            token = "";
        }
        else token += line[i];
    }
    if(!token.empty()) tokens.push_back(token);
    return true;
}

bool invalid_token(string token){
    if(token=="List" || token=="Folder" || token=="GeneratePDF" || token=="GenerateVideo") return true;
    return false;
}

bool generate_video(Runtime *proc, vector<string> tokens){
    string folder_name;
    vector<vector<string>> frames;
    if(tokens[2]=="nil") folder_name = "./";
    else{
        folder_name = proc->get_folder_name(tokens[2]);
        if(folder_name.empty()){
            cout << "Can not find variable " << folder_name << endl;
            return false;
        }
    }
    if(tokens[3]=="nil") frames = {};
    else{
        frames = proc->get_frame_variable(tokens[3]);
        if(frames.empty()){
            cout << "Can not find variable " << tokens[3] << endl;
            return false;
        }
    }
    ofstream to_python("_images_");
    to_python << "VIDEO\n";
    to_python << tokens[1] + "\n";
    to_python << folder_name + "\n";
    for(int i = 0; i<frames.size(); i++){
        for(int j = 0; j<frames[i].size(); j++){
            to_python << frames[i][j];
            if(j!=frames[i].size()-1) to_python << "$";
        }
        if(i!=frames.size()-1) to_python << "\n";
    }
    if(frames.empty()) to_python << "nil";
    to_python.close();
    system("python main.py");
    // system("rm _images_");
    return true;
}
bool generate_pdf(Runtime *proc, vector<string> tokens){
    string folder_name;
    vector<vector<string>> frames;
    if(tokens[2]=="nil") folder_name = "./";
    else{
        folder_name = proc->get_folder_name(tokens[2]);
        if(folder_name.empty()){
            cout << "Can not find variable " << folder_name << endl;
            return false;
        }
    }
    if(tokens[3]=="nil") frames = {};
    else{
        frames = proc->get_frame_variable(tokens[3]);
        if(frames.empty()){
            cout << "Can not find variable " << tokens[3] << endl;
            return false;
        }
    }
    ofstream to_python("_images_");
    to_python << "PDF\n";
    to_python << tokens[1] + "\n";
    to_python << folder_name + "\n";
    for(int i = 0; i<frames.size(); i++){
        for(int j = 0; j<frames[i].size(); j++){
            to_python << frames[i][j];
            if(j!=frames[i].size()-1) to_python << "$";
        }
        if(i!=frames.size()-1) to_python << "\n";
    }
    if(frames.empty()) to_python << "nil";
    to_python.close();
    system("python main.py");
    // system("rm _images_");
    return true;
}
