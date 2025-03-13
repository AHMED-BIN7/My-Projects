#pragma once
#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;

class clsString
{
private:
    string _String;

public:
    clsString()
    {
        _String = "";
    }
    clsString(string Value)
    {
        _String = Value;
    }

    void setValue(string Value)
    {
        _String = Value;
    }
    string getValue()
    {
        return _String;
    }
    string ReadString()
    {
        string Name;
        cout << "Enter Clinet Accont Number : ";
        getline(cin, Name);
        cout << "\n\n";
        return Name;

    }
    char ReadChractar()
    {
        char Charcter = ' ';
        cout << "Enter Letter : ";
        cin >> Charcter;

        return Charcter;
    }
    void PrintFirstLetter(string S1)
    {
        bool IsFirstletter = true;

        for (int i = 0; i <= S1.length(); i++)
        {
            if (S1[i] != ' ' && IsFirstletter == true)
            {
                cout << S1[i] << endl;
            }

            IsFirstletter = ((S1[i] == ' ') ? true : false);
        }
    }
    string PrintFirstLetterUpper(string S1)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i <= S1.length(); i++)
        {
            if (S1[i] != ' ' && IsFirstLetter == true) {

                S1[i] = toupper(S1[i]);
            }
            IsFirstLetter = ((S1[i] == ' ') ? true : false);
        }

        return S1;
    }
    string PrintFirstLetterLower(string S1)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i <= S1.length(); i++)
        {
            if (S1[i] != ' ' && IsFirstLetter == true)
            {
                S1[i] = tolower(S1[i]);
            }

            IsFirstLetter = (S1[i] == ' ') ? true : false;
        }

        return S1;
    }
    string UpperSentence(string Sentence)
    {
        for (int i = 0; i < Sentence.length(); i++)
        {
            Sentence[i] = toupper(Sentence[i]);
        }
        return Sentence;
    }
    string LowerSentnce(string Sentence)
    {
        for (int i = 0; i < Sentence.length(); i++)
        {
            Sentence[i] = tolower(Sentence[i]);
        }

        return Sentence;
    }
    char Invertcharacter(char S1)
    {
        return isupper(S1) ? tolower(S1) : toupper(S1);
    }
    string InverAllLetter(string S1)
    {
        for (int i = 0; i <= S1.length(); i++)
        {
            S1[i] = Invertcharacter(S1[i]);
        }
        return S1;
    }
    void CountSmallandCapitalLetter(string S1)
    {
        short CountSmallLetter = 0;
        short CountCapitalLetter = 0;

        for (int i = 0; i <= S1.length(); i++)
        {
            if (isupper(S1[i]))
            {
                CountCapitalLetter++;
            }
            else if (islower(S1[i])) {
                CountSmallLetter++;
            }
        }

        cout << "SmallLetters : " << CountSmallLetter << endl;
        cout << "CapitalLetters : " << CountCapitalLetter << endl;
    }
    int ConutOneLetter(string S1, char Charcter)
    {
        short Conut = 0;

        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] == Charcter)
                Conut++;
        }

        return Conut;
    }
    int ConutOneLetter2(string S1, char Charcter, bool Machcase = true)
    {
        short Conut = 0;

        for (int i = 0; i < S1.length(); i++)
        {
            if (Machcase) {
                if (S1[i] == Charcter)
                    Conut++;
            }
            else
            {
                if (tolower(Charcter) == tolower(S1[i]))
                    Conut++;
            }
        }

        return Conut;
    }
    bool IsVowal(char S1)
    {
        char Vaowl[5] = { 'a','i','u','o','e' };
        S1 = tolower(S1);

        for (short i = 0; i < 5; i++)
        {
            if (S1 == Vaowl[i])
            {
                return true;
            }
        }
        return false;
    }
    int ConutVowel(string S1)
    {
        int Conut = 0;

        for (int i = 0; i < S1.length(); i++)
        {
            if (IsVowal(S1[i]))
            {
                Conut++;
            }
        }

        return Conut;
    }
    void PrintAllVowelInString(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            if (IsVowal(S1[i]))
            {
                cout << S1[i] << "\t";
            }
        }
    }
    void PrintEachWordInString2(string S1)
    {
        string delim = " ";
        short pos = 0;
        string sWord;
        int conut = 0;

        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);
            if (sWord != " ")
            {
                cout << sWord << endl;
            }

            S1.erase(0, pos + delim.length());
        }

        if (S1 != " ")
        {
            cout << S1 << endl;
        }
    }
    int ConutWordInSting(string S1)
    {
        string delim = " ";
        string sWord;
        short Conut = 0;
        short pos = 0;

        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);
            if (sWord != " ")
            {
                Conut++;
            }

            S1.erase(0, pos + delim.length());
        }
        if (S1 != " ")
        {
            Conut++;
        }

        return Conut;
    }
    static vector <string> Split(string S1, string delim)
    {
        vector <string> vSplit;

        string sWord;
        short pos = 0;

        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);
            if (sWord != delim)
            {
                vSplit.push_back(sWord);
            }

            S1.erase(0, pos + delim.length());
        }
        if (S1 != delim)
        {
            vSplit.push_back(S1);
        }

        return vSplit;
    }
    vector <string> Split(string delim)
    {
        vector <string> vSplit;

        string sWord;
        short pos = 0;

        while ((pos = _String.find(delim)) != std::string::npos)
        {
            sWord = _String.substr(0, pos);
            if (sWord != delim)
            {
                vSplit.push_back(sWord);
            }

            _String.erase(0, pos + delim.length());
        }
        if (_String != delim)
        {
            vSplit.push_back(_String);
        }

        return vSplit;
    }
    static string TrimLeft(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ') {

                return S1.substr(i, S1.length() - 1);
            }
        }
        return "";
    }
    string TrimLeft()
    {
        for (short i = 0; i < _String.length(); i++)
        {
            if (_String[i] != ' ') {

                return _String.substr(i, _String.length() - 1);
            }
        }
        return "";
    }
    string TrimRight(string S1)
    {
        for (short i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ') {

                return S1.substr(0, i + 1);
            }
        }
        return "";
    }
    string Trim(string S1)
    {
        return TrimLeft(TrimRight(S1));
    }
    string JoinVectorOfString(vector <string> vNames, string delim)
    {
        string S1 = "";

        for (string& Line : vNames)
        {
            S1 += Line + delim;
        }

        return S1.substr(0, S1.length() - delim.length());
    }
    string JoinVectorOfString(string Name[], short Lenght, string delim)
    {
        string S1 = "";

        for (short i = 0; i < Lenght; i++)
        {
            S1 += Name[i] + delim;
        }

        return S1.substr(0, S1.length() - delim.length());
    }
    void ReversWord(string arryWord[20], string S1, string delim = " ")
    {
        string Word = "";
        short pos = 0;
        short Conut = 0;

        while ((pos = S1.find(delim)) != std::string::npos)
        {
            Word = S1.substr(0, pos);
            if (Word != delim)
            {
                arryWord[Conut] = Word;
                Conut++;
            }
            S1.erase(0, pos + delim.length());
        }
        if (S1 != " ")
        {
            arryWord[Conut] = S1;
        }
    }
    void PrintReverseWord(string arryWord[20], short Lenght, string S1)
    {
        for (short i = Lenght - 1; i >= 0; i--)
        {
            if (i == Lenght) {
                cout << arryWord[i];
            }
            cout << arryWord[i] << " ";
        }
        cout << endl;
    }
    string ReversWordInstringbyiterator(string S1)
    {
        vector <string> vWord;
        string S2 = "";
        vWord = Split(S1, " ");

        vector <string>::iterator iter = vWord.end();

        while (iter != vWord.begin())
        {
            --iter;
            S2 += *iter + " ";
        }

        S2 = S2.substr(0, S2.length() - 1);

        return S2;
    }
    string ReplecWords(string S1, string ReplesWord, string ChangingWord, bool Mach = true)
    {
        vector<string>vWord = Split(S1, " ");

        for (string& Line : vWord)
        {
            if (Mach) {

                if (Line == ReplesWord)
                {
                    Line = ChangingWord;
                }
            }
            else {

                if (LowerSentnce(Line) == LowerSentnce(ReplesWord))
                {
                    Line = ChangingWord;
                }
            }
        }

        return JoinVectorOfString(vWord, " ");

        // Other Method ...

        /*short pos = S1.find(ReplesWord);

        while (pos != std::string::npos)
        {
            S1 = S1.replace(pos, ReplesWord.length(), ChangingWord);
            pos = S1.find(ReplesWord);
        }
        return S1;*/


    }
    string RemovePunctuation(string S1)
    {
        short pos = 0;
        string S2 = "";

        for (int i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i])) {

                S2 += S1[i];
            }
        }

        return S2;
    }
    __declspec(property(get = getValue, put = setValue)) string Value;
};

