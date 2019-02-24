//
//  JSON_lib.cpp
//  JSON_lib
//


#include "JSON_lib.hpp"
void Json::StopParse() {
    err_parse = true;
    Jason_obj.clear();
    Jason_array.clear();
    return;
}

bool Json::check_hooks(std::istringstream & stream, std::string & mainstr,char first_char,char end_char) {
    int figure_hook = 0;
    int square_hook = 0;
    
    if (first_char == '{') figure_hook = 1;
    if (first_char == '[') square_hook = 1;
    
    bool delim_hook = ( end_char == '}' || end_char == ']' );
    char buf_symb = '0';
    bool inside_hooks = false;
    while (stream >> buf_symb) {
        std::string buf_str(1, buf_symb);
        
        if (buf_symb == '"') inside_hooks = !inside_hooks;
        if (buf_symb == '{' && !inside_hooks) figure_hook++;
        if (buf_symb == '}' && !inside_hooks) figure_hook--;
        if (buf_symb == '[' && !inside_hooks) square_hook++;
        if (buf_symb == ']' && !inside_hooks) square_hook--;
        
        if (figure_hook < 0) return false;
        if (square_hook<0)   return false;
        if (figure_hook == 0 && square_hook == 0 && buf_symb == end_char) return true;
        if (!(figure_hook == 0 && square_hook == 0) && buf_symb == end_char && !delim_hook) return false;
        mainstr += buf_str;
    }
    if (figure_hook == 0 && square_hook == 0)  return true;
    return false;
}


Json::Json(const std::string& str) {
    std::istringstream stream(str);
    char symb;
    char buf_symbol;
    std::string map_key;
    std::string value;
    std::string valuebool;
    int value_number;
    bool value_b;
    
    if (stream >> buf_symbol) {
        if (buf_symbol == '{') {
            this->itArray = false;
        }
        else if (buf_symbol == '[') {
            this->itArray = true;
        }
        else {
            StopParse();
            return;
        }
        
    }
    else { StopParse();
        return;
    }
    if (!itArray) {
        std::string jsonStr = "";
        if (!check_hooks(stream, jsonStr, '{', '}')) {
            StopParse();
            return;
        }
        
        std::istringstream stream_obj (jsonStr);
        while (stream_obj >> buf_symbol) {
            value = "";
            if (buf_symbol != '"') { StopParse(); return; }
            std::getline(stream_obj, map_key, '"');
            char delim;
            if (!(stream_obj >> delim)) { StopParse(); return; }
            if (delim != ':') { StopParse(); return; }
            
            char JsObj;
            
            if (!(stream_obj >> JsObj)) { StopParse();
                return;
            }
            
            if (JsObj == '{') {
                if (!check_hooks(stream_obj, value, '{', '}')) { StopParse(); return; }
                value = '{' + value + '}';
                char end_el;
                if (stream_obj >> end_el) {
                    if (end_el != ',') {
                        StopParse(); return;
                        
                    }
                    if (!(stream_obj >> end_el)) {
                        StopParse(); return;
                    }
                    stream_obj.seekg(-1, std::ios_base::cur);
                }
            }
            if (JsObj == '[') {
                if (!check_hooks(stream_obj, value, '[', ']')) { StopParse(); return; }
                value = '[' + value + ']';
                char end_el;
                if (stream_obj >> end_el) {
                    if (end_el != ',') {
                        StopParse();
                        return;
                    }
                    if (!(stream_obj >> end_el)) {
                        StopParse(); return;
                    }
                    stream_obj.seekg(-1, std::ios_base::cur);
                }
            }
            if (!(JsObj == '{' || JsObj == '[')) {
                stream_obj.seekg(-1, std::ios_base::cur);
                check_hooks(stream_obj, value, 0, ',');
            }
            std::istringstream streamvalue(value);
            if (streamvalue >> symb) {
                if (symb == '"') {
                    std::getline(streamvalue, value, '"');
                    Jason_obj.insert(std::make_pair(map_key, std::make_any<decltype(value)>(value)));
                    
                }
                if (symb == '1' || symb == '2' || symb == '3' || symb == '4' || symb == '5' || symb == '6' || symb == '7' || symb == '8' || symb == '9' || symb == '0') {
                    streamvalue.seekg(-1, std::ios_base::cur);
                    streamvalue >> value_number;
                    Jason_obj.insert(std::make_pair(map_key, std::make_any<decltype(value_number)>(value_number)));
                }
                if (symb == 't' || symb == 'f') {
                    streamvalue.seekg(-1, std::ios_base::cur);
                    streamvalue >> valuebool;
                    if (valuebool == "true") {
                        value_b = true;
                    }
                    if (valuebool == "false") {
                        value_b = false;
                    }
                    Jason_obj.insert(std::make_pair(map_key, std::make_any<decltype(value_b)>(value_b)));
                    
                }
                
                if (symb == '{') {
                    std::string childJson;
                    std::getline(streamvalue, childJson);
                    childJson = "{" + childJson;
                    Json chjs(childJson);
                    Jason_obj.insert(std::make_pair(map_key, std::make_any<decltype(chjs)>(chjs)));
                }
                if (symb == '[') {
                    std::string childJson;
                    std::getline(streamvalue, childJson);
                    childJson = "[" + childJson;
                    Json chjs (childJson);
                    Jason_obj.insert(std::make_pair(map_key, std::make_any<decltype(chjs)>(chjs)));
                }
            }
            else {
                StopParse(); return;
            }
        }
        
    }
    if (itArray) {
        std::string jsonStr = "";
        
        if (!check_hooks(stream, jsonStr, '[', ']')) {
            StopParse();
            return;
        }
        
        std::istringstream stream_array (jsonStr);
        while (stream_array >> buf_symbol) {
            value = "";
            if (buf_symbol == '{') {
                if (!check_hooks(stream_array, value, '{', '}')) { StopParse(); return; }
                value = '{' + value + '}';
                char end_el;
                if (stream_array >> end_el) {
                    if (end_el != ',') {
                        StopParse(); return;
                        
                    }
                    if (!(stream_array >> end_el)) {
                        StopParse(); return;
                    }
                    stream_array.seekg(-1, std::ios_base::cur);
                }
            }
            if (buf_symbol == '[') {
                if (!check_hooks(stream_array, value, '[', ']')) { StopParse(); return; }
                value = '[' + value + ']';
                char endelement;
                if (stream_array >> endelement) {
                    if (endelement != ',') {
                        StopParse(); return;
                        
                    }
                    if (!(stream_array >> endelement)) {
                        StopParse(); return;
                    }
                    stream_array.seekg(-1, std::ios_base::cur);
                }
            }
            if (!(buf_symbol == '{' || buf_symbol == '[')) {
                stream_array.seekg(-1, std::ios_base::cur);
                check_hooks(stream_array, value, 0 , ',');
            }
            std::istringstream streamvalue(value);
            if (streamvalue >> symb) {
                if (symb == '"') {
                    std::getline(streamvalue, value, '"');
                    Jason_array.push_back(std::make_any<decltype(value)>(value));
                    
                }
                if (symb == '1' || symb == '2' || symb == '3' || symb == '4' || symb == '5' || symb == '6' || symb == '7' || symb == '8' || symb == '9' || symb == '0') {
                    streamvalue.seekg(-1, std::ios_base::cur);
                    streamvalue >> value_number;
                    Jason_array.push_back(std::make_any<decltype(value_number)>(value_number));
                }
                if (symb == 't' || symb == 'f') {
                    streamvalue.seekg(-1, std::ios_base::cur);
                    streamvalue >> valuebool;
                    if (valuebool == "true") {
                        value_b = true;
                    }
                    if (valuebool == "false") {
                        value_b = false;
                    }
                    Jason_array.push_back(std::make_any<decltype(value_b)>(value_b));
                    
                }
                
                if (symb == '{') {
                    
                    std::string childJson;
                    std::getline(streamvalue, childJson);
                    childJson = "{" + childJson;
                    Json chjs(childJson);
                    Jason_array.push_back(std::make_any<decltype(chjs)>(chjs));
                }
                if (symb == '[') {
                    
                    std::string childJson;
                    std::getline(streamvalue, childJson);
                    childJson = "[" + childJson;
                    Json chjs(childJson);
                    Jason_array.push_back(std::make_any<decltype(chjs)>(chjs));
                }
            }
            else {
                StopParse(); return;
            }
        }
        
    }
}

bool Json::is_array() const {
    if (err_parse) {
        throw "Err parsing";
    } return itArray;
}

bool Json::is_object() const {
    if (err_parse) {
        throw "Err parsing";
    }
    return !itArray;
}
std::any& Json::operator[](const std::string& key) {
    if (err_parse) {
        throw "Err parsing";
    }
    if (itArray) {
        throw "No json obj";
    }
    return Jason_obj[key];
}
std::any& Json::operator[](int index) {
    if (err_parse) {
        throw "Err parsing";
    }
    if (!itArray) {
        throw "No json arr";
    }
    return  Jason_array[index];
}

Json Json::parse(const std::string& s) {
    Json js(s);
    return js;
};

Json Json::parseFile(const std::string& path_to_file) {
    std::ifstream fs(path_to_file);
    std::string to_parse;
    std::string tmp_string;
    while (!fs.eof()) {
        std::getline(fs, tmp_string);
        to_parse += tmp_string;
    }
    Json js(to_parse);
    return js;
}


