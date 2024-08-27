#include<iostream>
#include<string>
#include<regex>
class clsValidations
{
public:
    static bool isValidISBN(const std::string& str,bool allowEmpty) {
     std::regex pattern(allowEmpty ? "^(\\d{13})?$" : "^\\d{13}$");
    return std::regex_match(str, pattern);
}
};