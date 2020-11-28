#ifndef RUNTIME_H
#define RUNTIME_H

#include "includes.h"

class List {
public:
    bool timed;
    std::vector<std::string> file_names;
    std::vector<std::pair<int, int>> intervals;
    List(bool isTimed){
        timed = isTimed;
        file_names = {};
        intervals = {};
    }
    void assign_timed(std::vector<std::string> files, std::vector<std::pair<int, int>> _intervals){
        if(!timed){
            std::cout << "This is a timed list: ";
            return;
        }
        file_names = files;
        intervals = _intervals;
    }
    bool insert_timed(std::string file_name, std::pair<int, int> interval){
        if(!timed){
            std::cout << "This is a timed list: ";
            return false;
        }
        file_names.push_back(file_name);
        intervals.push_back(interval);
        return true;
    }

    bool assign_untimed(std::vector<std::string> files){
        if(timed){
            std::cout << "This is a untimed list: ";
            return false;
        }
        file_names = files;
        return true;
    }
    bool insert_untimed(std::string file_name){
        if(timed){
            std::cout << "This is a untimed list: ";
            return false;
        }
        file_names.push_back(file_name);
        return true;
    }
    std::vector<std::string> convert_to_ulist(int start, int end, int fps){
        if(end==-1) end = file_names.size();
        if(end>file_names.size()){
            std::cout << "out of bound" << std::endl;
            return {};
        }
        if(fps<0) fps = 1;
        std::vector<std::string> _frames;
        for(int i = start; i<end; i++){
            if(timed){
                for(int j = fps*intervals[i].first; j<fps*intervals[i].second; j++){
                    _frames.push_back({file_names[i]});
                }
            }
            else _frames.push_back(file_names[i]);
        }
        return _frames;
    }
    std::vector<std::vector<std::string>> convert_to_frames(int start, int end, int quantum){
        if(end==-1) end = file_names.size();
        if(end>file_names.size()){
            std::cout << "out of bound" << std::endl;
            return {};
        }
        std::vector<std::vector<std::string>> _frames;
        for(int i = start; i<end; i++){
            if(timed){
                for(int j = intervals[i].first; j<intervals[i].second; j++){
                    _frames.push_back({file_names[i]});
                }
            }
            else _frames.push_back({file_names[i]});
        }
        return _frames;
    }
    std::vector<std::string> convert_to_frame(){
        if(timed){
            std::cout << "Cannot convert timed list to frames" << std::endl;
            return {};
        }
        return file_names;
    }
};


class Frames {
private:
    std::vector<std::vector<std::string>> _frames_;
    std::vector<int> time_stamps;
    int quantum = 1;
public:
    void set_quantum(int q){
        quantum = q;
    }
    void add_frame(std::vector<std::string> frame){
        _frames_.push_back(frame);
        if(time_stamps.empty()) time_stamps.push_back(0);
        else time_stamps.push_back(time_stamps.back()+quantum);
    }
    void assign_frame(std::vector<std::vector<std::string>> _frames){
        _frames_ = _frames;
    }
    std::vector<std::vector<std::string>> get_frames(){
        return _frames_;
    }
};



class Runtime {
private:
    std::vector<List*> image_variables;
    std::unordered_map<std::string, int> image_variable_table;
    std::unordered_map<std::string, std::string> folder_variable_table;
    std::vector<Frames*> frame_variables;
    std::unordered_map<std::string, int> frame_variable_table;
    std::unordered_map<std::string, std::string> position_variables;
public:
    void add_timed_image_list(std::string variable, std::vector<std::string> file_names, std::vector<std::pair<int, int>> intervals){
        image_variables.push_back(new List(true));
        image_variables.back()->assign_timed(file_names, intervals);
        image_variable_table[variable] = image_variables.size();
    }
    void add_untimed_image_list(std::string variable, std::vector<std::string> value){
        image_variables.push_back(new List(false));
        image_variables.back()->assign_untimed(value);
        image_variable_table[variable] = image_variables.size();
        // std::cout << "added " << variable << std::endl;
    }
    void add_folder_variable(std::string variable, std::string value){
        folder_variable_table[variable] = value;
        // std::cout << "added " << variable << std::endl;
    }
    std::string get_folder_name(std::string variable){
        // std::cout << "accessing " << variable << std::endl;
        return folder_variable_table[variable];
    }
    bool add_frame_variable(std::string variable, std::vector<std::string> value){
        // std::cout << "Adding variable " << variable << std::endl;
        if(value.empty()){
            frame_variables.push_back(new Frames);
            frame_variable_table[variable] = frame_variables.size();
            return true;
        }
        for(int i = 0; i<value.size(); i++){
            if(image_variable_table[value[i]]==0){
                std::cout << "No variable named " << value[i] << std::endl;
                return false;
            }
            int location = image_variable_table[value[i]]-1;
            if(image_variables[location]->timed){
                std::cout << "Frames take only UList as argument: " << value[i] << std::endl;
                return false;
            }
        }
        frame_variables.push_back(new Frames);
        for(int i = 0; i<value.size(); i++){
            int location = image_variable_table[value[i]]-1;
            frame_variables.back()->add_frame(image_variables[location]->convert_to_frame());
            frame_variable_table[variable] = frame_variables.size();
            // std::cout << value[i] << std::endl;
        }
        return true;
    }
    std::vector<std::vector<std::string>> get_frame_variable(std::string variable){
        if(frame_variable_table[variable]==0){
            std::cout << "No variable named " << variable << std::endl;
            return {};
        }
        // std::cout << frame_variable_table[variable]-1 << std::endl;
        return frame_variables[frame_variable_table[variable]-1]->get_frames();
    }
    std::pair<std::string, std::pair<int, int>> get_tlist_variable(std::string variable_name, int pos){
        if(image_variable_table[variable_name]==0){
            std::cout << "No variable found with name " << variable_name << std::endl;
            return {};
        }
        int location = image_variable_table[variable_name]-1;
        if(!image_variables[location]->timed){
            std::cout << "Requested list is a UList: " << variable_name << std::endl;
            return {};
        }
        std::vector<std::string> ret_names = image_variables[location]->file_names;
        std::vector<std::pair<int, int>> ret_pairs = image_variables[location]->intervals;
        if(pos>=ret_names.size()){
            std::cout << "Out of bounds for variable " << variable_name << std::endl;
            return {};
        }
        return make_pair(ret_names[pos], ret_pairs[pos]);
    }
    std::string get_ulist_variable(std::string variable_name, std::string pos_var){
        if(image_variable_table[variable_name]==0){
            std::cout << "No variable found with name " << variable_name << std::endl;
            return {};
        }
        int location = image_variable_table[variable_name]-1;
        if(image_variables[location]->timed){
            std::cout << "Requested list is a TList: " << variable_name << std::endl;
            return {};
        }
        std::vector<std::string> ret_names = image_variables[location]->file_names;
        if(position_variables[pos_var]==""){
            std::cout << "Invalid position variable " << variable_name << std::endl;
            return {};
        }
        int pos = stoi(position_variables[pos_var]);
        if(pos>=ret_names.size()){
            std::cout << "Out of bounds for variable " << variable_name << std::endl;
            return {};
        }
        return ret_names[pos];
    }
    bool append_ulist(std::string variable, std::string value){
        if(image_variable_table[variable]==0){
            std::cout << "No varible named " << variable << std::endl;
            return false;
        }
        // std::cout << image_variables[image_variable_table[variable]-1]->file_names.size() << std::endl;
        return image_variables[image_variable_table[variable]-1]->insert_untimed(value);
    }
    bool append_tlist(std::string variable, std::string value, std::pair<int, int> interval){
        if(image_variable_table[variable]==0){
            std::cout << "No varible named " << variable << std::endl;
            return false;
        }
        return image_variables[image_variable_table[variable]-1]->insert_timed(value, interval);
    }
    bool append_frames(std::string variable, std::string value_variable){
        if(frame_variable_table[variable]==0){
            std::cout << "No varible named " << variable << std::endl;
            return false;
        }
        if(image_variable_table[value_variable]==0){
            std::cout << "No varible named " << variable << std::endl;
            return false;
        }
        int image_location = image_variable_table[value_variable]-1;
        if(image_variables[image_location]->timed){
            std::cout << "Cannot add TList to Frames: " << variable << std::endl;
            return false;
        }
        int frame_location = frame_variable_table[variable]-1;
        frame_variables[frame_location]->add_frame(image_variables[image_location]->file_names);
        return true;
    }
    bool ulist_to_frames(std::string ulist, std::string frames){
        if(image_variable_table[ulist]==0){
            std::cout << "No variable named " << ulist << std::endl;
            return false;
        }
        int location = image_variable_table[ulist]-1;
        if(image_variables[location]->timed){
            std::cout << "Given list is timed" << std::endl;
            return false;
        }
        Frames *frame = new Frames;
        frame->assign_frame(image_variables[location]->convert_to_frames(0,-1,1));
        frame_variables.push_back(frame);
        frame_variable_table[frames] = frame_variables.size();
        return true;
    }
    int get_fps(){
        int fps = 1;
        if(position_variables["FPS"]=="") fps = 1;
        else{
            std::string fps_str = position_variables["FPS"];
            int i = 0;
            if(fps_str.size()!=1 && fps_str[i]=='-') i = 1;
            for(; i<fps_str.size(); i++){
                if(fps_str[i]>'9' || fps_str[i]<'0'){
                    std::cout << "FPS should be a number" << std::endl;
                    return 1;
                }
            }
            // std::cout << fps << std::endl;
            fps = stoi(fps_str);
        }
        return fps;
    }
    bool tlist_to_ulist(std::string tlist, std::string ulist){
        if(image_variable_table[tlist]==0){
            std::cout << "No variable named " << tlist << std::endl;
            return false;
        }
        int location = image_variable_table[tlist]-1;
        if(!image_variables[location]->timed){
            std::cout << "Given list is not timed" << std::endl;
            return false;
        }
        List *list = new List(false);
        int fps = get_fps();
        if(!list->assign_untimed(image_variables[location]->convert_to_ulist(0, -1, fps))){
            std::cout << "Error occured while converting" << std::endl;
            return false;
        }
        image_variables.push_back(list);
        image_variable_table[ulist] = image_variables.size();
        return true;
    }
    int get_page_width(){
        int fps = 800;
        if(position_variables["PAGE_WIDTH"]=="") fps = 800;
        else{
            std::string fps_str = position_variables["PAGE_WIDTH"];
            for(int i = 0; i<fps_str.size(); i++){
                if(fps_str[i]>'9' || fps_str[i]<'0'){
                    std::cout << "PAGE_WIDTH should be a number" << std::endl;
                    return 800;
                }
            }
            fps = stoi(fps_str);
        }
        return fps;
    }
    int get_page_height(){
        int fps = 800;
        if(position_variables["PAGE_HEIGHT"]=="") fps = 800;
        else{
            std::string fps_str = position_variables["PAGE_HEIGHT"];
            for(int i = 0; i<fps_str.size(); i++){
                if(fps_str[i]>'9' || fps_str[i]<'0'){
                    std::cout << "PAGE_HEIGHT should be a number" << std::endl;
                    return 800;
                }
            }
            fps = stoi(fps_str);
        }
        return fps;
    }
    void add_position(std::string variable_name, std::string value){
        position_variables[variable_name] = value;
    }
    bool valid_position(std::string variable_name){
        if(position_variables[variable_name]==""){
            std::cout << "No variable named " << variable_name << std::endl;
            return false;
        }
        return true;
    }
    std::string get_position(std::string variable_name){
        return position_variables[variable_name];
    }
};

#endif