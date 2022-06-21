#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Vigenere
{
public:
    string k;

    Vigenere(string k)
    {
        for (int i = 0; i < k.size(); i++)
        {
            if (k[i] >= 'A' && k[i] <= 'Z')
            {
                this->k += k[i];
            }
            else if (k[i] >= 'a' && k[i] <= 'z')
            {
                this->k += k[i] + 'A' - 'a';
            }
        }
    }

    string encryption(string t)
    {
        string result;

        for (int i = 0, j = 0; i < t.length(); i++)
        {
            char c = t[i];

            if (c >= 'a' && c <= 'z')
            {
                c += 'A' - 'a';
            }
            else if (c < 'A' || c > 'Z')
            {
                continue;
            }

            result += (c + k[j] - 2 * 'A') % 26 + 'A';
            j = (j + 1) % k.length();
        }
        return result;
    }

    string decryption(string t)
    {
        string result;

        for (int i = 0, j = 0; i < t.length(); i++)
        {
            char c = t[i];

            if (c >= 'a' && c <= 'z')
            {
                c += 'A' - 'a';
            }
            else if (c < 'A' || c > 'Z')
            {
                continue;
            }

            result += (c - k[j] + 26) % 26 + 'A';
            j = (j + 1) % k.length();
        }
        return result;
    }
};

int main()
{
    while (true)
    {
        char cypher;
        cout << "1 - Szyfr Cezara - szyfrowanie\n";
        cout << "2 - Szyfr Cezara - deszyfrowanie\n";
        cout << "3 - Homofoniczny szyfr podstawieniowy\n";
        cout << "4 - Wieloalfabetowy szyfr podstawieniowy\n";
        cout << "0 - EXIT\n";

        cypher = _getch();

        switch (cypher)
        {
        case '1':
        {
            system("cls");
            string msg;
            int key;
            char tmp;

            cout << "Wprowadz wiadomosc do zaszyfrowania: ";
            getline(cin, msg);

            cout << "Wprowadz przesuniecie: ";
            cin >> key;
            cin.ignore();

            for (int i = 0; i < msg.length(); i++)
            {
                if (msg[i] >= 'a' && msg[i] <= 'z')
                {
                    tmp = msg[i] + key;

                    if (tmp > 'z')
                    {
                        tmp = tmp - 'z' + 'a';
                    }
                    msg[i] = tmp;
                }
                else if (msg[i] >= 'A' && msg[i] <= 'Z')
                {
                    tmp = msg[i] + key;

                    if (tmp > 'Z')
                    {
                        tmp = tmp - 'Z' + 'A';
                    }
                    msg[i] = tmp;
                }
            }
            cout << "Twoja zaszyfrowana wiadomosc: " << msg << "\n";
            system("pause");
            system("cls");
            break;
        }

        case '2':
        {
            system("cls");
            string msg;
            int key;
            char tmp;

            cout << "Wprowadz wiadomosc do odszyfrowania: ";
            getline(cin, msg);

            cout << "Wprowadz przesuniecie: ";
            cin >> key;
            cin.ignore();

            for (int i = 0; i < msg.length(); i++)
            {
                if (msg[i] >= 'a' && msg[i] <= 'z')
                {
                    tmp = msg[i] - key;

                    if (tmp < 'a')
                    {
                        tmp = tmp + 'z' - 'a';
                    }
                    msg[i] = tmp;
                }
                else if (msg[i] >= 'A' && msg[i] <= 'Z')
                {
                    tmp = msg[i] - key;

                    if (tmp < 'A')
                    {
                        tmp = tmp + 'Z' - 'A';
                    }
                    msg[i] = tmp;
                }
            }
            cout << "Twoja odszyfrowa wiadomosc: " << msg << "\n";
            system("pause");
            system("cls");
            break;
        }

        case '3':
        {
            system("cls");
            char tab[2][26];
            string text;
            fstream key("key.txt");

            cout << "Wprowadz napis do zaszyfrowania: ";
            getline(cin, text);
            transform(text.begin(), text.end(), text.begin(), ::tolower);

            cout << "Zamiana tekstu na male litery: " << text << "\n\n";

            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j <= 26; j++)
                {
                    tab[i][j] = key.get();
                }
            }

            for (int i = 0; i < text.length(); i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    if (text[i] == tab[0][j])
                    {
                        text[i] = tab[1][j];
                        break;
                    }
                }
            }

            cout << "Zaszyfrowana wiadomosc: " << text << "\n\n";

            for (int i = 0; i < text.length(); i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    if (text[i] == tab[1][j])
                    {
                        text[i] = tab[0][j];
                        break;
                    }
                }
            }

            cout << "Odszyfrowana wiadomosc: " << text << "\n\n";

            //Wyświetlenie alfabetu angielskiego oraz poniżej klucza dla sprawdzenia poprawności kodowania - zakomentowane domyślnie
            /*for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    cout << tab[i][j];
                }
                cout << "\n";
            }*/

            key.close();

            system("pause");
            system("cls");
            break;
        }

        case '4':
        {
            system("cls");
            fstream key("key2.txt");
            string klucz, text, encode, decode;
            klucz = string((istreambuf_iterator<char>(key)), istreambuf_iterator<char>());
            Vigenere v(klucz);
            cout << "Wprowadz napis do zaszyfrowania: ";
            getline(cin, text);

            encode = v.encryption(text);
            cout << "Zaszyfrowana wiadomosc: " << encode << "\n\n";

            decode = v.decryption(encode);
            cout << "Odszyfrowana wiadomosc: " << decode << "\n\n";

            key.close();

            system("pause");
            system("cls");
            break;
        }

        case '0':
        {
            exit(0);
            break;
        }

        default:
        {
            system("cls");
            cout << "ERROR 404\n" << "PAGE NOT FOUND\n";
            system("pause");
            system("cls");
            cout << "PLEASE SELECT ANOTHER LETTER OR NUMBER\n";
            system("pause");
            break;
        }
        system("cls");
        }
        system("cls");
    }
    return 0;
}