#include <iostream>

int main() {

    unsigned int key;
    std::string text;
    std::string encryptedText; 
    std::cout << "Enter encryption key" << std::endl;
    std::cin >> key;
    std::cout << "Enter text you want decrypted" << std::endl;
    std::cin >> text;

    int n = text.length();
    

    for(int i = 0; i < n; i++){
        
        char compareNew = text[i] - key;

        if (compareNew < 'A'){
            int b = 'A' % compareNew;
            char aNew = 'Z' + 1 - b; 
            encryptedText = encryptedText + aNew;
        }else {
            encryptedText = encryptedText + compareNew;
        }
    }
    std::cout << encryptedText << std::endl;

}
