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
    void insert_timed(std::string file_name, std::pair<int, int> interval){
        if(!timed){
            std::cout << "This is a timed list: ";
            return;
        }
        file_names.push_back(file_name);
        intervals.push_back(interval);
    }

    void assign_untimed(std::vector<std::string> files){
        if(timed){
            std::cout << "This is a untimed list: ";
            return;
        }
        file_names = files;
    }
    void insert_untimed(std::string file_name){
        if(timed){
            std::cout << "This is a untimed list: ";
            return;
        }
        file_names.push_back(file_name);
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
};

#endif