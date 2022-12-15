// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
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
        return txt;
    }

    string FindAndReplace(string intxt, string replace)
    {
        int positionFind = 0;
        while ((positionFind = intxt.find(replace,positionFind)) != -1)
        {
           intxt = intxt.replace(intxt.find(replace,positionFind), replace.size(), "(" + replace + ")");
           positionFind += 3;
           if (positionFind >= intxt.size())
               break;
        }
        return intxt;
    }

    string ReplaceActionOnNumber(string intxt)
    {
        int signposition = 0;
        while ((signposition = intxt.find("+", signposition)) != -1)
        {
            int firstnumber = 0;
            int secondnumberend = 0;
            int first = 0;
            int second = 0;
            if (signposition != -1)
            {
                firstnumber = signposition;
                secondnumberend = signposition;
                while (intxt[firstnumber] != ' ')
                {
                    firstnumber--;
                }
                while (intxt[secondnumberend] != ' ')
                {
                    secondnumberend++;
                }
                string fNumber = intxt.substr(firstnumber + 1, signposition);
                istringstream(fNumber) >> first;
                string sNumber = intxt.substr(signposition + 1, secondnumberend);
                istringstream(sNumber) >> second;
                int result = first + second;
                intxt.replace(firstnumber + 1, secondnumberend - firstnumber - 1, to_string(result));
            }
        }
        signposition = 0;
        while ((signposition = intxt.find("-", signposition)) != -1)
        {
            int firstnumber = 0;
            int secondnumberend = 0;
            int first = 0;
            int second = 0;
            if (signposition != -1)
            {
                firstnumber = signposition;
                secondnumberend = signposition;
                while (intxt[firstnumber] != ' ')
                {
                    firstnumber--;
                }
                while (intxt[secondnumberend] != ' ')
                {
                    secondnumberend++;
                }
                string fNumber = intxt.substr(firstnumber + 1, signposition);
                istringstream(fNumber) >> first;
                string sNumber = intxt.substr(signposition + 1, secondnumberend);
                istringstream(sNumber) >> second;
                int result = first - second;
                intxt.replace(firstnumber + 1, secondnumberend - firstnumber - 1, to_string(result));
            }
        }
        
        return intxt;
    }

    string ArabicToRoman()
    {
        string Roman = "";
        int arabic = 0;
        int Mnumber = 0;
        int DNumber = 0;
        int CNumber = 0;
        int LNumber = 0;
        int XNumber = 0;
        int VNumber = 0;
        int INumber = 0;
        istringstream(txt) >> arabic;
        if (arabic <= 4000)
        {
            Mnumber = arabic / 1000; 
            DNumber = (arabic - Mnumber * 1000) / 500; 
            CNumber = (arabic - Mnumber * 1000 - DNumber * 500) / 100; 
            LNumber = (arabic - Mnumber * 1000 - DNumber * 500 - CNumber * 100) / 50; 
            XNumber = (arabic - Mnumber * 1000 - DNumber * 500 - CNumber * 100 - LNumber * 50) / 10; 
            VNumber = (arabic - Mnumber * 1000 - DNumber * 500 - CNumber * 100 - LNumber * 50 - XNumber * 10) / 5; 
            INumber = arabic - Mnumber * 1000 - DNumber * 500 - CNumber * 100 - LNumber * 50 - XNumber * 10 - VNumber * 5;
        }
        else
        {
            Roman = "Число не должно превышать 4000";
        }
        for (int i = 0; i < Mnumber; i++)
            Roman.append("M");
        for (int i = 0; i < DNumber; i++)
            Roman.append("D");
        for (int i = 0; i < CNumber; i++)
            Roman.append("C");
        for (int i = 0; i < LNumber; i++)
            Roman.append("L");
        for (int i = 0; i < XNumber; i++)
            Roman.append("X");
        for (int i = 0; i < VNumber; i++)
            Roman.append("V");
        for (int i = 0; i < INumber; i++)
            Roman.append("I");

        return Roman;
    }


    string GetPathFunction() 
    {
        string simpletxt = txt;
        int positionBeforeFile;
        int positionEndFolder;
        int onlyFile;
        int onlyEndName;
        int onlyName;

        positionBeforeFile = simpletxt.rfind("\\");
        positionEndFolder = simpletxt.rfind("\\", positionBeforeFile-1);
        onlyFile = simpletxt.rfind("\\");
        onlyEndName = simpletxt.rfind(".");
        string result = "";

        result.append("Полный путь: " + simpletxt + "\n");
        result.append("Полный путь к файлу: " + simpletxt.substr(0, positionBeforeFile) + "\n");
        result.append("Последняя папка с файлом: " + simpletxt.substr(positionEndFolder+1, positionBeforeFile - positionEndFolder - 1) + "\n");
        result.append("Полное имя файла: " + simpletxt.substr(onlyFile + 1, simpletxt.size() - onlyFile) + "\n");
        result.append("Расширение файла: " + simpletxt.substr(onlyEndName, simpletxt.size() - onlyEndName) + "\n");
        result.append("Имя файла без расширения: " + simpletxt.substr(onlyFile + 1, simpletxt.size() - onlyEndName+1) + "\n");
        return result;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    string txt = "       gd      f  fg dfg d      fg df g df   gdf gdf gd g  d      f gd gd   gdf gdf d g  dfegd gd fg dg fg df       f ";
    StringWorker sw{ txt };
    sw.RemoveSpaces();
    string defaultTxt = "// int firstLetterPos = 0; \n string txt = 'gd      f  fg dfg d      fg df g df   gdf gdf gd g  d      f gd gd   gdf gdf d g  dfegd gd fg dg fg df       f ';\n /*cout << txt << endl;\n /*cout << txt.length() <<*/ endl; \n */ while (isspace/*(txt[txt.size() - 1]))  {\n */txt.pop_back();\n }\n ";
    StringWorker sw2{ defaultTxt };
    sw2.RemoveComment();
    string defaultTxt2 = "abracadabra";
    string replaceTxt = "ab";
    StringWorker sw3{ defaultTxt2 };
    sw3.FindAndReplace(defaultTxt2, replaceTxt);
    string defTxt = "alpha 5+26 beta 72-35 gamma 32+45 etc";
    StringWorker sw4{ defTxt };
    sw4.ReplaceActionOnNumber(defTxt);
    StringWorker sw5{ "2799" };
    StringWorker sw6{ "C:\\Step\\С++lesson_03\\Docs\\Less03.docx" };
    cout << sw6.GetPathFunction() << endl;
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
