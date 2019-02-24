//
//  JSON_lib.hpp
//  JSON_lib


#ifndef JSON_lib_
#define JSON_lib_

/* The classes below are exported */
#pragma GCC visibility push(default)
#include <iostream>
#include <sstream>
#include <map>
#include <any>
#include <vector>
#include <fstream>
class Json {
private:
    std::map<std::string, std::any> Jason_obj;
    std::vector<std::any> Jason_array;
    bool check_hooks(std::istringstream & stream, std::string & dist, char end_char, char first_char);
    bool itArray = false;
    bool err_parse = false;
public:
    //Если введена некорректная строка
    void StopParse();
    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string& s);
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array() const;
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object() const;
    
    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::any& operator[](const std::string& key);
    
    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::any& operator[](int index);
    
    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string& s);
    
    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string& path_to_file);
};
#pragma GCC visibility pop
#endif
