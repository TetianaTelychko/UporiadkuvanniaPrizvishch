#include <iostream>
#include <vector>
using namespace std;
void fillingOrderedVectors(wstring &, vector<int> &, int, vector<wstring> &, vector<vector<int>> &);

void printSurnames(const vector<wstring>& surnames){
    for(int i = 0; i < surnames.size(); i++){
        for(int j = 0; j < surnames[i].length(); ++j){
            printf("%C", surnames[i][j]);
        }
        cout << ' ';
    }
    cout << '\n';
}


int getPriority(wchar_t character){
    wchar_t alphabet[] = {
            U'А', U'Б', U'В', U'Г', U'Ґ', U'Д',
            U'Е', U'Є', U'Ж', U'З', U'И', U'І',
            U'Ї', U'Й', U'К', U'Л', U'М', U'Н',
            U'О', U'П', U'Р', U'С', U'Т', U'У',
            U'Ф', U'Х', U'Ц', U'Ч', U'Ш', U'Щ',
            U'Ю', U'Я',
            U'а', U'б', U'в', U'г', U'ґ',U'д',
            U'е', U'є', U'ж', U'з',U'и', U'і',
            U'ї', U'й', U'к',U'л', U'м', U'н',
            U'о', U'п',U'р', U'с', U'т', U'у',
            U'ф',U'х', U'ц', U'ч', U'ш', U'щ',
            U'ь', U'ю', U'я'};
    for(int i = 0; i < (sizeof(alphabet) / sizeof(wchar_t)); ++i){
        if(character == alphabet[i]){
            return i;
        }
    }
    return 65;
}

void fillVectorWithPriorities(vector<vector<int>> &priorities, vector<wstring> &surnames){
    priorities.resize(surnames.size());
    int i = 0;
    for(auto & surname : surnames){
        priorities[i].resize(surname.length());
        for(int j = 0; j < surname.length(); ++j){
            int a = getPriority(surname[j]);
            priorities[i][j] = a;
        }
        ++i;
    }
}

void additionalCheck(wstring &name, vector<int> &priority,
                     int index, vector<wstring> &orderedSurnames,
                     vector<vector<int>> &orderedPriorities){
    auto iterator1 = orderedPriorities.begin();
    auto iterator2 = orderedSurnames.begin();

    while(index < orderedPriorities.size() && priority[0] == orderedPriorities[index][0]){
        int j = 1;
        wstring name2 = orderedSurnames[index];
        bool secondPosition = false;

        while(j <= name.length() && j <= name2.length()){
            if(j == name.length() || j == name2.length()){
                if(name.length() < name2.length() || name.length() == name2.length()){
                    orderedPriorities.insert(iterator1 + index, priority);
                    orderedSurnames.insert(iterator2 + index, name);
                }
                else{
                    secondPosition = true;
                }
                break;
            }
            else if(getPriority(name[j]) < getPriority(name2[j])){
                orderedPriorities.insert(iterator1 + index, priority);
                orderedSurnames.insert(iterator2 + index, name);
                break;
            }
            else if(getPriority(name[j]) > getPriority(name2[j])){
                secondPosition = true;
                break;
            }
            else{
                ++j;
            }
        }


        if(secondPosition){
            ++index;
            fillingOrderedVectors(name, priority, index, orderedSurnames, orderedPriorities);
        }
        break;
    }
}

void fillingOrderedVectors(wstring &name, vector<int> &priority, int index, vector<wstring> &orderedSurnames, vector<vector<int>> &orderedPriorities){
    auto iterator1 = orderedPriorities.begin();
    auto iterator2 = orderedSurnames.begin();


    if(index == orderedPriorities.size()){
        orderedSurnames.push_back(name);
        orderedPriorities.push_back(priority);
    }
    else if(priority[0] < orderedPriorities[index][0]){
        orderedPriorities.insert(iterator1 + index, priority);
        orderedSurnames.insert(iterator2 + index, name);
    }
    else if(priority[0] == orderedPriorities[index][0]){
        additionalCheck(name, priority, index, orderedSurnames, orderedPriorities);
    }
}

void ordering(vector<wstring> &surnames){

    vector<vector<int>> priorities;
    fillVectorWithPriorities(priorities, surnames);


    vector<vector<int>> orderedPriorities;
    orderedPriorities.reserve(surnames.size());

    vector<wstring> orderedSurnames;
    orderedSurnames.reserve(surnames.size());


    for(int i = 0; i < surnames.size(); ++i){
        if(orderedSurnames.empty()){
            orderedSurnames.push_back(surnames[i]);
            orderedPriorities.push_back(priorities[i]);
        }
        else{
            vector<int> priority = priorities[i];
            wstring name = surnames[i];
            int newIndex = 0;
            while((newIndex < orderedPriorities.size()) && (priority[0] > orderedPriorities[newIndex][0])){
                ++newIndex;
            }
            fillingOrderedVectors(name, priority, newIndex, orderedSurnames, orderedPriorities);
        }
    }

    surnames = orderedSurnames;
}

int main(){
    std::locale::global(std::locale(""));

    cout << "Вектор прізвищ до сортування : \n";
    vector<wstring> surnames = {L"Їжаченко", L"Баб'як", L"Атанасів Д.", L"Іларій",
                                L"Атанасів А.", L"Єремій", L"Ґудзь", L"Янгель",
                                L"Андрійчук", L"Баб'юк"};
    printSurnames(surnames);

    cout << "Вектор прізвищ після сортування : \n";
    ordering(surnames);
    printSurnames(surnames);
    return 0;
}