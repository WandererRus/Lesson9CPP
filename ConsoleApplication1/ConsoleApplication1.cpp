// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

class StringWorker {
private:
    string txt;
public:
    StringWorker(string text) : txt{ text } {}

    void RemoveSpaces() {

        int firstLetterPos = 0;
        
        while (isspace(txt[txt.size() - 1]))
        {
            txt.pop_back();
        }
        firstLetterPos = txt.find_first_not_of(" ");
        int spacefound = 0;

        while ((spacefound = txt.find("  ", firstLetterPos)) >= 0)
        {
            if (spacefound > firstLetterPos)
            {
                txt.replace(spacefound, 2, " ");
            }
        }
    }

    string GetTxt()
    {
        return txt;
    }

    string RemoveComment()
    {
        cout << txt << endl;
        int startComment = 0;
        int endComment = txt.size();

        while (txt.find("/*", 0) != -1 || txt.find("*/", 0) != -1)
        { 
            startComment = 0;
            endComment = txt.size();

            while (txt.find("/*", startComment+2) > 0)
            {
                if (txt.find("/*", startComment+2) != -1)
                {
                    startComment = txt.find("/*", startComment+2);
                }
                else
                {
                    break;
                }
            }
            while (txt.rfind("*/", endComment-2) > 0)
            {
                if (txt.rfind("*/", endComment-2) != -1 && txt.rfind("*/", endComment - 2) > startComment)
                {
                    endComment = txt.rfind("*/", endComment-2);
                }
                else
                {
                    break;
                }
            }

            if (endComment != -1  && startComment != -1)
            {
                txt.erase(startComment, endComment - startComment + 2);
            }
            else if (startComment != -1)
            {
                txt.erase(startComment, txt.size() - startComment);
            }
        }        

        while (txt.find("//", 0) != -1)
        {
            startComment = txt.find("//", 0);
            endComment = txt.find("\n", startComment);
            txt.erase(startComment, endComment - startComment + 2);
        }
        cout << '\n' << txt << endl;
        return "";
    }
};


int main()
{
    string txt = "       gd      f  fg dfg d      fg df g df   gdf gdf gd g  d      f gd gd   gdf gdf d g  dfegd gd fg dg fg df       f ";
    StringWorker sw{ txt };
    sw.RemoveSpaces();
    txt = sw.GetTxt();

    string defaultTxt = "// int firstLetterPos = 0; \n string txt = 'gd      f  fg dfg d      fg df g df   gdf gdf gd g  d      f gd gd   gdf gdf d g  dfegd gd fg dg fg df       f ';\n /*cout << txt << endl;\n /*cout << txt.length() <<*/ endl; \n */ while (isspace/*(txt[txt.size() - 1]))  {\n */txt.pop_back();\n }\n ";
    StringWorker sw2{ defaultTxt };
    sw2.RemoveComment();

    
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
