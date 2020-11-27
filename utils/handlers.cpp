// #include "includes.h"
#include "generator_functions.h"
// #include "runtime.h"
using namespace std;

bool handleTimedList(ifstream &fin, Runtime *proc, unsigned int &line_number, string variable_name){
    string line;
    vector<string> file_names;
    vector<pair<int, int>> intervals;
    vector<string> tokens;
    while(fin){
        getline(fin, line);
        // cout << line << endl;
        if(line=="end"){
            proc->add_timed_image_list(variable_name, file_names, intervals);
            return true;
        }
        if(!generate_tokens(line, tokens)) continue;
        if(tokens.size()!=3){
            cout << "Timed list will take 3 arguments <name> <start> <end>" << endl;
            return false;
        }
        if(invalid_token(tokens[0])){
            cout << "Error at line " << line_number << endl;
            return false;
        }
        if(tokens.size()!=3){
            cout << "Parsing error at line: " << line_number << endl;
            return false;
        }
        int start = stof(tokens[1]), end = stof(tokens[2]);
        if(start > end){
            cout << "Start time cannot be greater than end time" << endl;
            return false;
        }
        file_names.push_back(tokens[0]);
        intervals.push_back(make_pair(stoi(tokens[1]), stoi(tokens[2])));
        // TODO: Sanity check for start_time <= end_time
        tokens = {};
        line_number++;
    }
    return false;
}


bool handleUntimedList(ifstream &fin, Runtime *proc, unsigned int &line_number, string variable_name){
    string line;
    vector<string> file_names;
    vector<string> tokens;
    while(fin){
        getline(fin, line);
        // cout << line << endl;
        if(line=="end"){
            proc->add_untimed_image_list(variable_name, file_names);
            return true;
        }
        if(!generate_tokens(line, tokens)) continue;
        if(tokens.size()!=1){
            cout << "Untimed list takes one argument: <name>" << endl;
            return false;
        }
        if(invalid_token(tokens[0])){
            cout << "Error at line " << line_number << endl;
            return false;
        }
        file_names.push_back(tokens[0]);
        // TODO: Sanity check for start_time <= end_time
        tokens = {};
        line_number++;
    }
    return false;
}

bool handleFolder(vector<string> tokens, Runtime *proc){
    if(tokens.size()<4){
        cout << "Error in statement" << endl;
        return false;
    }
    string folder_name = "";
    for(int i = 3; i<tokens.size(); i++) folder_name += (tokens[i] + " ");
    folder_name.pop_back();
    proc->add_folder_variable(tokens[1], folder_name);
    // cout << folder_name << endl;
    return true;
}


bool handleFrames(ifstream &fin, Runtime *proc, unsigned int &line_number, string variable_name){
    string line;
    vector<string> list_names;
    vector<string> tokens;
    while(fin){
        getline(fin, line);
        // cout << line << endl;
        if(line=="end"){
            proc->add_frame_variable(variable_name, list_names);
            return true;
        }
        if(!generate_tokens(line, tokens)) continue;
        if(tokens.size()!=1){
            cout << "Frame takes one input of UList type" << endl;
            return false;
        }
        if(invalid_token(tokens[0])){
            cout << "Error at line " << line_number << endl;
            return false;
        }
        list_names.push_back(tokens[0]);
        // TODO: Sanity check for start_time <= end_time
        tokens = {};
        line_number++;
    }
    return false;
}

bool appendUList(Runtime *proc, vector<string> tokens){
    if(tokens.size()<3){
        cout << "Args does not match" << endl;
        return false;
    }
    if(tokens.size()>3){
        cout << "Args does not match" << endl;
        return false;
    }
    return proc->append_ulist(tokens[1], tokens[2]);
}
bool appendTList(Runtime *proc, vector<string> tokens){
    if(tokens.size()<5){
        cout << "Args does not match" << endl;
        return false;
    }
    if(tokens.size()>5){
        cout << "Args does not match" << endl;
        return false;
    }
    return proc->append_tlist(tokens[1], tokens[2], make_pair(stoi(tokens[3]), stoi(tokens[4])));
}
bool appendFrames(Runtime *proc, vector<string> tokens){
    if(tokens.size()<3){
        cout << "Args does not match" << endl;
        return false;
    }
    if(tokens.size()>3){
        cout << "Args does not match" << endl;
        return false;
    }
    return proc->append_frames(tokens[1], tokens[2]);
}

bool TList2UList(Runtime *proc, vector<string> tokens){
    if(tokens.size()<3){
        cout << "Args does not match" << endl;
        return false;
    }
    if(tokens.size()>3){
        cout << "Args does not match" << endl;
        return false;
    }
    return proc->tlist_to_ulist(tokens[1], tokens[2]);
};
bool UList2Frames();

bool accessFrames(){}
bool accessUList(){}
bool accessTList(){}