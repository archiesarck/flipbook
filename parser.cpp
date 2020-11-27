#include "utils/handlers.h"
#include "utils/generator_functions.h"
using namespace std;

int main(int argc, char **argv){
    if(argc<1){
        cout << "No filename provided" << endl;
        return 0;
    }
    ifstream fin(argv[1]);
    if(!fin.good()){
        cout << "No such file found" << endl;
        return 0;
    }
    string line;
    vector<string> tokens;
    unsigned int line_number = 0;
    Runtime *current_process = new Runtime;
    while(true){
        if(fin.eof()) break;
        getline(fin, line);
        line_number++;
        if(!generate_tokens(line, tokens)) continue;
        if(tokens[0]=="TList"){
            if(!handleTimedList(fin, current_process, line_number, tokens[1])){
                cout << "Error occured while timed handling List" << endl;
                break;
            }
        }
        else if(tokens[0]=="UList"){
            if(!handleUntimedList(fin, current_process, line_number, tokens[1])){
                cout << "Error occured while untimed handling List" << endl;
                break;
            }
        }
        else if(tokens[0]=="Folder"){
            if(!handleFolder(tokens, current_process)){
                cout << "Error occured while handling Folder" << endl;
                break;
            }
        }
        else if(tokens[0]=="GenerateVideo"){
            if(!generate_video(current_process, tokens)){
                cout << "Error occured while generating video" << endl;
                break;
            }
        }
        else if(tokens[0]=="GeneratePDF"){
            if(!generate_pdf(current_process, tokens)){
                cout << "Error occured while generating pdf" << endl;
                break;
            }
        }
        else if(tokens[0].front()=='#'){}
        else if(tokens[0]=="Frames"){
            if(!handleFrames(fin, current_process, line_number, tokens[1])){
                cout << "Error handling frames" << endl;
                break;
            }
        }
        else if(tokens[0]=="AppendUList"){
            if(!appendUList(current_process, tokens)){
                cout << "Error handling frames" << endl;
                break;
            }
        }
        else if(tokens[0]=="AppendTList"){
            if(!appendTList(current_process, tokens)){
                cout << "Error handling frames" << endl;
                break;
            }
        }
        else if(tokens[0]=="AppendFrames"){
            if(!appendFrames(current_process, tokens)){
                cout << "Error handling frames" << endl;
                break;
            }
        }
        else if(tokens[0]=="AccessFrames"){
            
        }
        else if(tokens[0]=="AccessUList"){
            string str = accessUList(current_process, tokens);
            // cout << str << endl;
        }
        else if(tokens[0]=="AccessTList"){
            
        }
        else if(tokens[0]=="TList2UList"){
            if(!TList2UList(current_process, tokens)){
                cout << "Error in TList2UList" << endl;
                break;
            }
        }
        else if(tokens[0]=="UList2Frames"){
            if(!UList2Frames(current_process, tokens)){
                cout << "Error in UList2Frames" << endl;
                break;
            }
        }
        else if(tokens[0]=="Position"){
            if(!handlePosition(current_process, tokens)){
                cout << "Error in position" << endl;
                break;
            }
        }
        else if(tokens[0]=="LoopBegin"){
            if(!handleLoops(fin, current_process, line_number, tokens)){
                cout << "Error occurred in loops" << endl;
                break;
            }
        }
        else{
            cout << "Unknown command at line: " << tokens[0] << endl;
            break;
        }
        tokens = {};
    }
    fin.close();
    return 0;
}