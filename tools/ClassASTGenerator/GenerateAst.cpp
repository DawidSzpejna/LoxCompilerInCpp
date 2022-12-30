#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <cstring>


void defineType(std::ofstream& outdata, std::string baseName, std::string className, std::string fieldList);
void defineAst(std::string outputDir, std::string baseName, std::list<std::string> types);
void defineVisitor(std::ofstream& outdata, std::string baseName, std::list<std::string> types);


class Spliter
{
public:
    std::string* splited;
    int real_range;

    Spliter(std::string text, char delimeter){
        int range = 1;
        real_range = 0;
        for (int i = 0; i < text.length(); i++){
            if (text[i] == delimeter) range++;
        }

        splited = new std::string[range];

        int current = 0;
        int prev = 0;
        for (int i = 0; i < text.length(); i++){
            if (text[i] == delimeter) {
                if (current - prev == 0) {
                    current = i + 1;
                    prev = i + 1;
                    continue;
                }
                splited[real_range] = text.substr(prev, current - prev);

                real_range++;
                current = i + 1;
                prev = i + 1;
            } 
            else
            {
                current++;
            }
        }

        splited[real_range] = text.substr(prev, current - prev);
        real_range++;
    }

    std::string operator [](int i) const {return splited[i];}
    std::string& operator [](int i) {return splited[i];}

    ~Spliter() {
        delete[] splited;
    }
};


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: generate_ast <output directory>" << std::endl;
        std::exit(64);
    }

    std::string outputDir = argv[1];
    defineAst(outputDir, "Expr", std::list<std::string> {
        "Assign : Token name, Expr value",
        "Binary : Expr left, Token this_operator, Expr right",
        "Call : Expr callee, Token paren, List<Expr> arguments",
        "Get      : Expr object, Token name",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Logical  : Expr left, Token this_operator, Expr right",
        "Set      : Expr object, Token name, Expr value",
        "This     : Token keyword",
        "Unary : Token this_operator, Expr right",
        "Variable : Token name"
        });
    
    defineAst(outputDir, "Stmt", std::list<std::string> {
        "Block : std::vector<Stmt *> *statements",
        "Class      : Token name, List<Stmt.Function> methods",
        "Expression : Expr expression",
        "Function   : Token name, List<Token> params, List<Stmt> body",
        "If         : Expr condition, Stmt thenBranch, Stmt elseBranch",
        "Print      : Expr expression",
        "Return     : Token keyword, Expr value",
        "Var : Token name, Expr initializer",
        "While      : Expr condition, Stmt body"
    });
}


void defineAst(std::string outputDir, std::string baseName, std::list<std::string> types)
{
    std::string path =outputDir + "/" + baseName + ".cpp";
    std::ofstream outdata(path);

    if (!outdata.is_open()) {
        std::cerr << "Error: file could not be opended" << std::endl;
        std::exit(64);
    }

    {
        outdata << "class " + baseName + " {\n";
        outdata << "};\n";

        std::list<std::string>::iterator it;
        for (it = types.begin(); it != types.end(); it++) {
            Spliter spl = Spliter(*it, ':');

            std::string className = spl[0];
            std::string fields = spl[1];
            defineType(outdata, baseName, className, fields);
        }

    }

    outdata.close();
}


void defineType(std::ofstream& outdata, std::string baseName, std::string className, std::string fieldList)
{
    outdata << "class " + className + ": public " + baseName + " {\n";
    outdata << "public: \n";

    // Constructor
    outdata << "    " + className + "(" + fieldList + ") {\n";

    Spliter spl_fileds = Spliter(fieldList, ',');
    for (int i = 0; i < spl_fileds.real_range; i++) {
        Spliter spl_name = Spliter(spl_fileds[i], ' ');
        outdata << "    this->" + spl_name[1] + " = " + spl_name[1] + ";\n";
    }

    outdata << "}\n";

    // Fileds
    for (int i = 0; i < spl_fileds.real_range; i++) {
        outdata << "   " + spl_fileds[i] + ";\n";
    }

    outdata << "};\n";
}


void defineVisitor(std::ofstream& outdata, std::string baseName, std::list<std::string> types)
{
    outdata << "";
}