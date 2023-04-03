
#include<iostream>
#include<string>
using namespace std;

/*
* This algorithm converts given plainText to CipherText using Ceaser Cipher substitution method also known as
* substitution cipher.
* This algorithm also receives 'K' as a parameter, according to which we shift characters to right or left.
*/
string ceaserCipherEncryption(string plainText, int k)
{
    string cipherText = "";            //stores cipher text(Text obtained after encryption)
    //obtaining each character from string
    for (int i = 0; i < plainText.length(); i++)
    {
        //checking each character, if character belongs to upper case or lower case letters
        if (plainText[i] >= 65 && plainText[i] <= 90)         //checking for upper case letters
        {
            int tempResult = (plainText[i] - 65) + k;
            if (tempResult < 0)
            {
                tempResult = 26 + tempResult;
            }
            char temp = char(65 + (tempResult) % 26);
            cipherText += temp;
        }
        else if (plainText[i] >= 97 && plainText[i] <= 122)   //checking for lower case letters
        {
            int tempResult = (plainText[i] - 97) + k;
            if (tempResult < 0)
            {
                tempResult = 26 + tempResult;
            }
            char temp = char(97 + (tempResult) % 26);
            cipherText += temp;
        }
        else                                                  //other punctuation marks,spaces,special characters are
        {                                                     //added as it is without encryption
            cipherText += plainText[i];
        }
    }
    return cipherText;                                        //returning the cipher text
}


/*
* This function converts given plainText to cipherText using block cipher substitution method.
* It receives 'plainText' and 'key' as parameters. Plaintext is converted into cipherText according to 
* that key provided.
*/
string blockCipherEncryption(string plainText, string key)
{
    string cipherText = "";                                       //stores cipherText(Text after encryption)
    int currentIndexOfKey = -1;                                   //stores index of key character
    for (int i = 0; i < plainText.length(); i++)                  //iterating through each character of plainText
    {
        char tempKey = key[(currentIndexOfKey + 1) % key.length()];   //getting character from key
        currentIndexOfKey = (currentIndexOfKey + 1) % key.length();   //updating current index of key value
        char temp = 32 + (plainText[i] + tempKey) % 96;               //obtaining encrypted character
        cipherText += temp;                                           //adding this encrypted character to final cipherText
    }
    return cipherText;                                            //returning cipherText
}


/*
* This function checks if character is present in given string or not.
* It returns boolean value (True/False)
*/
bool contains(string sample, char ch)
{
    if (sample.find(ch) != string::npos)      //if found, return true
    {
        return true;
    } 
    else                                      //else, return false
    {
        return false;
    }
}

/*
* This function converts given plaintext to cipher text using encryption occurrences algorithm.
* It receives plainText as parameter and returns cipherText(encryptedText)
*/
string encryptionOccurrences(string plainText)
{
    //checking if length of plaintext is greater than 2 or not, because then we can ecrypt second character first and then first
    //character
    if (plainText.length() < 2)
    {
        cout << "Encryption Occurrence algorithm works for atleast 2 characters!!" << endl << endl;
        return "-1";
    }

    string cipherText = "";                                  //stores final encrypted text
    string occurrenceString = "";                            //stores occurrences of a character in whole plainText
    string checked = "";                                     //contains characters which are checked already from plaintext

    //first of all checking second character of plain text
    occurrenceString.push_back(plainText[1]);        
    for (int j = 0; j < plainText.length(); j++)
    {
        if (plainText[j] == plainText[1])
        {
            occurrenceString.append("-");
            occurrenceString.append(to_string(j + 1));
        }
    }

    //cipherText.append(" ");                                //adding occurrence string to ciphertext
    cipherText.append(occurrenceString);                
    occurrenceString = "";                                 //making occurrence string again null
    checked.push_back(plainText[1]);                       //putting checked character in checked string

    //now checking all the other characters from plain text and counting its occurrences
    for (int i = 0; i < plainText.length(); i++)
    {
        char toCheck = plainText[i];                             //character to be checked now
        if (contains(checked, toCheck) == false)                 //checking if it is already checked or not
        {
            occurrenceString.push_back(toCheck);
            for (int j = 0; j < plainText.length(); j++)         //checking the occurrences of this character in plainText
            {
                if (plainText[j] == toCheck)                     //if found in plainText, simply add its position to
                {                                                //occurrence string
                    occurrenceString.append("-");
                    occurrenceString.append(to_string(j+1));
                }
            }
            checked.push_back(toCheck);
            cipherText.append(" ");
            cipherText.append(occurrenceString);                 //adding occurrence string to cipherText string    
            occurrenceString = "";                               //making occurrence string null
        }
    } 
    return cipherText;                                           //returns the final cipher text
}


/*
* This function converts given plaintext to ciphertext by using dictionary rules as described in question.
* It just receives plainText as parameter and returns ciphertext
*/
string dictionaryEncryption(string plainText)
{
    string cipherText = "";                                     //stores final encrypted text
    for (int i = 0; i < plainText.length(); i++)
    {
        if (plainText[i] >= 65 && plainText[i] <= 90)           //if current character is upper case
        {
            int alphabetIndex = plainText[i] - 65;
            char requiredAlphabet = 90 - alphabetIndex;
            requiredAlphabet += 32;                             //converting this required alphabet to lower case
            cipherText.push_back(requiredAlphabet);             //appending this alphabet to cipherText
        }
        else if (plainText[i] >= 97 && plainText[i] <= 122)     //if current character is lower case
        {
            int alphabetIndex = plainText[i] - 97;
            char requiredAlphabet = 122 - alphabetIndex;
            requiredAlphabet -= 32;
            cipherText.push_back(requiredAlphabet);
        }
        else if (plainText[i] >= 48 && plainText[i] <= 57)      //if current character is a number
        {
            char requiredAlphabet = (57 - plainText[i])+48;     //subtracating ascii(num) from ascii(9) 
            cipherText.push_back(requiredAlphabet);             //appending this character to cipher text
        }
        else                                                    //if current character is some other special character
        {
            cipherText.push_back(plainText[i]);                 //then append character as it is to cipher text
        }
    }
    return cipherText;                                          //returning final ecnrypted text
}  


/*
* This function converts plaintext to ciphertext according to inversion encryption method.
* It just receives plainText as parameter and returns cipherText
*/
string invertedEncryption(string plainText)
{
    string cipherText = "";                                     //stores final encrypted text

    //iterating through the plainText in reverse order and appending
    //the characters to final cipherText string
    for (int i = plainText.length() - 1; i >= 0; i--)           
    {
        cipherText.push_back(plainText[i]);
    }
    return cipherText;                                          //returning final encrypted text
}



/*
* This function converts cipherText to plain text according to the key provided.
* It receives cipherText and key and returns the corresponding plainText
*/
string ceaserCipherDecryption(string cipherText, int k)
{
    string plainText = "";            //stores plain text(Text obtained before encryption)
    //obtaining each character from string
    for (int i = 0; i < cipherText.length(); i++)
    {
        //checking each character, if character belongs to upper case or lower case letters
        if (cipherText[i] >= 65 && cipherText[i] <= 90)         //checking for upper case letters
        {
            int tempResult = (cipherText[i] - 65) - k;
            if (tempResult < 0)
            {
                tempResult = 26 + tempResult;
            }
            char temp = char(65 + (tempResult) % 26);
            plainText += temp;
        }
        else if (cipherText[i] >= 97 && cipherText[i] <= 122)   //checking for lower case letters
        {
            int tempResult = (cipherText[i] - 97) - k;
            if (tempResult < 0)
            {
                tempResult = 26 + tempResult;
            }
            char temp = char(97 + (tempResult) % 26);
            plainText += temp;
        }
        else                                                  //other punctuation marks,spaces,special characters are
        {                                                     //added as it is without decryption
            plainText += cipherText[i];
        }
    } 
    return plainText;                                         //returning the plain text
}


/*
* This function receives cipherText and converts it into plainText.
* It receives plaintext alongwith the key that was used to once encrypt a text.
*/
string blockCipherDecryption(string cipherText, string key)
{
    string plainText = "";                                         //stores plainText(Text before encryption)
    int currentIndexOfKey = -1;                                    //stores index of key character
    for (int i = 0; i < cipherText.length(); i++)                  //iterating through each character of plainText
    {
        char tempKey = key[(currentIndexOfKey + 1) % key.length()];   //getting character from key
        currentIndexOfKey = (currentIndexOfKey + 1) % key.length();   //updating current index of key value
        char temp = ((cipherText[i] - tempKey)+96) - 32;              //obtaining encrypted character
        plainText += temp;                                            //adding this encrypted character to final cipherText
    }
    return plainText;                                              //returning plainText
}


string OccurrencesDecryption(string cipherText)
{
    char plainText[200];                    // to be returned
    string tempWord = "";
    cipherText.push_back(' ');
    int max = 0;
    for (int i = 0; i < cipherText.length(); i++)
    {

        if (i == 0)
        {
            tempWord.push_back(cipherText[i]);
        }
        else
        {
            if (cipherText[i] == ' ' && cipherText[i - 1] != ' ')
            {
                char alphabet = tempWord[0];
                int j = 2;
                string location;
                while (tempWord[j] != '\0')
                {
                    if (tempWord[j] != '-')
                    {
                        char num = tempWord[j];
                        location += num;
                    }
                    else
                    {
                        int index = stoi(location) - 1;
                        plainText[index] = alphabet;
                        max = index > max ? index : max;
                        location = "";
                    }
                    j++;
                }
                int index = stoi(location) - 1;
                plainText[index] = alphabet;
                max = index > max ? index : max;
                tempWord = "";
            }
            else
            {
                tempWord.push_back(cipherText[i]);
            }
        }
    }

    string finalString = "";
    for (int i = 0; i < max + 1; i++)
    {
        finalString.push_back(plainText[i]);
    }
    return finalString;
}


/*
* This function receives cipherText and converts it into corresponding plainText.
*/
string dictionaryDecryption(string cipherText)
{
    string plainText = "";                                        //stores plaintext
    for (int i = 0; i < cipherText.length(); i++)
    {
        if (cipherText[i] >= 65 && cipherText[i] <= 90)           //if current character is upper case
        {
            int alphabetIndex = 90 - cipherText[i];
            char requiredAlphabet = alphabetIndex + 65; 
            requiredAlphabet += 32;                             //converting this required alphabet to lower case
            plainText.push_back(requiredAlphabet);             //appending this alphabet to cipherText
        }
        else if (cipherText[i] >= 97 && cipherText[i] <= 122)     //if current character is lower case
        {
            int alphabetIndex = 122 - cipherText[i];
            char requiredAlphabet = alphabetIndex + 97;
            requiredAlphabet -= 32;
            plainText.push_back(requiredAlphabet);
        }
        else if (cipherText[i] >= 48 && cipherText[i] <= 57)      //if current character is a number
        {
            char requiredAlphabet = 105 - cipherText[i];     
            plainText.push_back(requiredAlphabet);                //appending this character to plain text
        }
        else                                                      //if current character is some other special character
        {
            plainText.push_back(cipherText[i]);                   //then append character as it is to plain text
        }
    }
    return plainText ;                                            //returning the final plainText
}

/*
* This function receives ciphertext and converts it into plaintext according to inversion algorithm.
*/
string inversionDecryption(string cipherText)
{
    string plainText = "";                                     //stores final plaintext

    //iterating through the plainText in reverse order and appending
    //the characters to final plainText string
    for (int i = cipherText.length() - 1; i >= 0; i--)
    {
        plainText.push_back(cipherText[i]);
    }
    return plainText;                                          //returning final plaintext
}

int main()
{
    //#################### TESTING ALL ENCRYPTION AND DECRYPTION ALGORITHMS ###############
    string originalMessage = "ALI SALEEM is my name.";
    cout << "ORIGINAL MESSAGE = " << originalMessage << endl << endl << endl;

    string e1 = blockCipherEncryption(originalMessage, "ABC");
    cout << "BlockCipher CipherText: " << e1 << endl << endl;

    string e2 = ceaserCipherEncryption(e1, 4);
    cout << "Ceaser Cipher CipherText: " << e2 << endl << endl;

    string e3 = encryptionOccurrences(e2);
    cout << "Encryption Occurrences CipherText: " << e3 << endl << endl;

    string e4 = dictionaryEncryption(e3);
    cout << "Dictionary Encryption CipherText: " << e4 << endl << endl;

    string e5 = invertedEncryption(e4);
    cout << "Inverted Encryption CipherText: " << e5 << endl << endl;
    

    string d1 = inversionDecryption(e5);
    cout << "Inverted Decryption plainText: " << d1 << endl << endl;

    string d2 = dictionaryDecryption(d1);
    cout << "Dictionary Decryption plainText: " << d2 << endl << endl;

    string d3 = OccurrencesDecryption(d2);
    cout << "Occurrences Decryption plainText: " << d3 << endl << endl;

    string d4 = ceaserCipherDecryption(d3, 4);
    cout << "Ceaser Cipher Decryption plainText: " << d4 << endl << endl;

    string d5 = blockCipherDecryption(d4, "ABC");
    cout << "Block Cipher Decryption plainText: " << d5 << endl << endl;

    return  0;
}
