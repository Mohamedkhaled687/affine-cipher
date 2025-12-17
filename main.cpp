/**********************
 * Discrete Mathematics Task
 * Author: Mohamed Khaled
 * Date: 2025-12-05
 * Description: This is the main file for Implementation of task3 Affine Cipher
 * It contains the main function and the main logic of the task.
 */


/******************** Affine Cipher ********************/

// Is an encryption technique that uses a mathematical function to encrypt and decrypt messages.
// It is a type of substitution cipher where each symbol (space and letters) is replaced by a number (0-17) in Somoan Alphabet.
// The alphabet consists of 18 symbols: space (index 0) and 17 letters (indices 1-17).
// The encryption function is: E(x) = (ax + b) % 18
// The decryption function is : D(x) = a^-1 * (x - b) % 18
// where a and b are the key of the cipher.
// a and 18 must be coprime (gcd (a , 18 ) = 1) this is because every element in Z_18 has a multiplicative inverse .
/************ Proof of that a and 18 must be coprime ************/
// let y after applying the encryption function is: y ≡ (ax + b) (mod 18)
// ax ≡ y - b (mod 18)
// x ≡ a^-1 * (y - b) (mod 18)
// where a^-1 is the multiplicative inverse of a in Z_18.
// This operation is valid only if a^-1 is exists.
// Mathmeticly , a ^ -1 defined as number k 
// a . k ≡ 1 (mod 18)
// can writen a . k = 18.t + 1 for some integer t.
// Bezout's Identity states that for an equation of the form Ax+By=C to have integer solutions, gcd(A,B) must divide C.
// In our case, A = a, B = 18, and C = 1.
// Therefore, gcd(a, 18) must divide 1.
// The only positive integer that divides 1 is 1 itself.
// Therefore, a and 18 must be coprime.
/************ End of Proof of that a and 18 must be coprime ************/

/************ Implementation of the Affine Cipher ************/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Mapping of the Somoan Alphabet to numbers (0-17: space=0, letters=1-17)

int somoan_alphabet_to_number(char letter){
    // Space character is index 0
    if(letter == ' '){
        return 0;
    }
    int lower_letter = tolower(letter);
    switch(lower_letter){
        case 'a' :
            return 1;
        case 'e' :
            return 2;
        case 'i' :
            return 3;
        case 'o' :
            return 4;
        case 'u' :
            return 5;
        case 'f' :
            return 6;
        case 'g' :
            return 7;
        case 'l' :
            return 8;
        case 'm' :
            return 9;
        case 'n' :
            return 10;
        case 'p' :
            return 11;
        case 's' : 
            return 12;
        case 't' : 
            return 13;
        case 'v' :
            return 14;
        case 'h' : 
            return 15;
        case 'k' : 
            return 16;
        case 'r' : 
            return 17;
        default :
            throw invalid_argument("Invalid letter");
    }
}

// Mapping of numbers (0-17) to Somoan Alphabet (0=space, 1-17=letters)
char number_to_somoan_alphabet(int number){
    switch(number){
        case 0 :
            return ' ';
        case 1 :
            return 'a';
        case 2 :
            return 'e';
        case 3 :
            return 'i';
        case 4 :
            return 'o';
        case 5 :
            return 'u';
        case 6 :
            return 'f';
        case 7 :
            return 'g';
        case 8 :
            return 'l';
        case 9 :
            return 'm';
        case 10 :
            return 'n';
        case 11 :
            return 'p';
        case 12 : 
            return 's';
        case 13 : 
            return 't';
        case 14 :
            return 'v';
        case 15 : 
            return 'h';
        case 16 : 
            return 'k';
        case 17 : 
            return 'r';
        default :
            throw invalid_argument("Invalid number");
    }
}

// Function to get the modulo of a number
int get_modulo(int number, int modulus){
    return (number % modulus + modulus) % modulus;
}

// Function to get the inverse of the key (a) 

int get_inverse_of_key(int a){
    for(int i = 1; i < 18; i++){
        if((a * i) % 18 == 1){
            return i;
        }
    }
    throw invalid_argument("Invalid key , a and 18 must be coprime (choose another key from)");
}
// Function to encrypt a message using the Affine Cipher

string encrypt_message(string message, int a, int b){
    string encrypted_message = "";
    for(char letter : message){
        // Skip other whitespace characters (tabs, newlines, etc.) but encrypt spaces
        if(isspace(letter) && letter != ' '){
            encrypted_message += letter;
            continue;
        }
        try {
            int mapped_number = somoan_alphabet_to_number(letter);
            int encrypted_number = get_modulo(a * mapped_number + b, 18);
            char encrypted_char = number_to_somoan_alphabet(encrypted_number);
            // Preserve case for letters, but space is always space
            if(encrypted_char == ' '){
                encrypted_message += ' ';
            } else {
                encrypted_message += (isupper(letter) ? toupper(encrypted_char) : encrypted_char);
            }
        } catch (const invalid_argument& e) {
            cout << "Error: The character '" << letter << "' is not in the Somoan Alphabet." << endl;
            throw; // Re-throw to allow caller to handle retry
        }
    }
    return encrypted_message;
}

// Function to decrypt a message using the Affine Cipher

string decrypt_message(string encrypted_message, int a, int b){
    string decrypted_message = "";
    int inverse_of_a = get_inverse_of_key(a);
    for (char letter : encrypted_message){
        // Skip other whitespace characters (tabs, newlines, etc.) but decrypt spaces
        if(isspace(letter) && letter != ' '){
            decrypted_message += letter;
            continue;
        }
        try {
            int mapped_number = somoan_alphabet_to_number(letter);
            int decrypted_number = get_modulo(inverse_of_a * (mapped_number - b), 18);
            char decrypted_char = number_to_somoan_alphabet(decrypted_number);
            // Preserve case for letters, but space is always space
            if(decrypted_char == ' '){
                decrypted_message += ' ';
            } else {
                decrypted_message += isupper(letter) ? toupper(decrypted_char) : decrypted_char;
            }
        } catch (const invalid_argument& e) {
            cout << "Error: The character '" << letter << "' is not in the Somoan Alphabet." << endl;
            throw; // Re-throw to allow caller to handle retry
        }
    }
    return decrypted_message;
}

// Main function to test the Affine Cipher

int main(){
    string message;
    int a, b;
    bool success = false;
    
    while(!success){
        try {
            cout << "Enter the message to encrypt in Somoan Alphabet (a, e, i, o, u, f, g, l, m, n, p, s, t, v, h, k, r) and spaces : ";
            getline(cin, message);
            cout << "Enter the first key (a): ";
            cin >> a;
            cout << "Enter the second key (b): ";
            cin >> b;
            // Clear the input buffer after reading b
            cin.ignore();
            
            // Validate the key before any encryption so we don't print output with a bad key
            get_inverse_of_key(a);
            
            string encrypted_message = encrypt_message(message, a, b);
            cout << "Encrypted message: " << encrypted_message << endl;
            string decrypted_message = decrypt_message(encrypted_message, a, b);
            cout << "Decrypted message: " << decrypted_message << endl;
            success = true;
        } catch (const invalid_argument& e) {
            string error_msg = e.what();
            // Check if it's an invalid key error
            if(error_msg.find("Invalid key") != string::npos){
                cout << "Error: Invalid key!" << endl;
                cout << "The key 'a' must be coprime with 18 (gcd(a, 18) = 1)." << endl;
                cout << "Please enter a different key (a)." << endl << endl;
            }
            // Check if it's an invalid character error
            else if(error_msg.find("Invalid letter") != string::npos || error_msg.find("Invalid number") != string::npos){
                cout << "Please enter a message containing only Somoan alphabet letters (a, e, i, o, u, f, g, l, m, n, p, s, t, v, h, k, r) and spaces." << endl << endl;
            }
            else {
                cout << "Error: " << error_msg << endl;
                cout << "Please try again with correct values." << endl << endl;
            }
        }
    }

    return 0;
}
