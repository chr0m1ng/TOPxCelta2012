#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>

#define h 14
#define p 6

using namespace std;

typedef struct
{
    int i;
    int j;
}tPos;

typedef struct
{
    int sim;
    int nao;
    int total;
    float prob;
    string nome;
}tAtributo;

typedef struct
{
    string valor;
    bool checar;
    string pergunta;
}tCampo;

tCampo tabela[h][p];
vector<string> questoes;
tAtributo atributos[p][2];

vector<string> quebra(string input, char div)
{
    stringstream test;
    test << input;
    string segment;
    vector<string> seglist;

    while(getline(test, segment, div))
        seglist.push_back(segment);

    return seglist;
}

void criaAtributos()
{
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            atributos[i][j].sim = 0;
            atributos[i][j].nao = 0;
            atributos[i][j].total = 0;
            atributos[i][j].prob = 0.0;
        }
    }
    for(int j = 0; j < p; j++)
    {
        atributos[j][0].nome = tabela[0][j].valor;
        for(int i = 0; i < h; i++)
        {
            if(atributos[j][0].nome != tabela[i][j].valor)
            {
                atributos[j][1].nome = tabela[i][j].valor;
                break;
            }
        }
    }
}

tPos achaAttPos(string nome)
{
    tPos out;
    out.i = 0;
    out.j = 0;
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(atributos[i][j].nome == nome)
            {
                out.i = i;
                out.j = j;
                return out;
            }

        }
    }
}

int achaQuesDoAttNaTabela(string nome)
{
    for(int i = 0; i < h; i++)
        for(int j = 0; j < p; j++)
            if(tabela[i][j].valor == nome)
                return j;
}

void zeraAtributos()
{
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            atributos[i][j].sim = 0;
            atributos[i][j].nao = 0;
            atributos[i][j].total = 0;
            atributos[i][j].prob = 0.0;
        }
    }
}


void printaAtributos()
{
    for(int i = 0; i < p; i++)
    {
        cout << questoes[i] << endl << endl;

        cout << "\t\t\t\t Sim \t\t\t\t Nao \t\t\t\t Total" << endl;
        cout << atributos[i][0].nome << "\t\t\t\t" << atributos[i][0].sim << "\t\t\t\t" << atributos[i][0].nao << "\t\t\t\t" << atributos[i][0].total << endl;
        cout << atributos[i][1].nome << "\t\t\t\t" << atributos[i][1].sim << "\t\t\t\t" << atributos[i][1].nao << "\t\t\t\t" << atributos[i][1].total << endl;

        cout << endl << endl; 
    }
}


tPos achaMaiorProbAtt()
{
    tPos maior;
    maior.i = 0;
    maior.j = 0;
    for(int i = 1; i < p - 1; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(atributos[i][j].prob > atributos[maior.i][maior.j].prob)
            {
                maior.i = i;
                maior.j = j;
            }
        }
    }

    return maior;
}

void calcAtt(int maior)
{
    /*
    for(int i = 0; i < p; i++)
        cout << atributos[i][0].nome << "\t" << atributos[i][1].nome << endl;
    cout << endl;

    cout << achaAttPos("muito").i << "\t" << achaAttPos("muito").j << endl; 
    */
    zeraAtributos();
    for(int i = 0; i < h; i++)
    {
        if(tabela[i][0].checar)
        {
            for(int j = 0; j < p - 1; j++)
            {   
                tPos att = achaAttPos(tabela[i][j].valor); 
                if(tabela[i][p - 1].valor == atributos[p - 1][0].nome)
                {
                    atributos[att.i][att.j].sim++;
                    atributos[att.i][att.j].total++;
                }
                else
                {
                    atributos[att.i][att.j].nao++;
                    atributos[att.i][att.j].total++;
                }

            }
            if(tabela[i][p - 1].valor == atributos[p - 1][0].nome)
            {
                atributos[p - 1][0].sim++;
                atributos[p - 1][0].total++;
                atributos[p - 1][1].total++;
            }
            else
            {
                atributos[p - 1][1].sim++;
                atributos[p - 1][0].total++;
                atributos[p - 1][1].total++;
            }
        }
    }
    
    //printaAtributos();

    for(int i = 0; i < p - 1; i++)
    {
        if(maior == -1)
        {
            if(atributos[p - 1][0].sim >= atributos[p - 1][1].sim)
            {
                for(int j = 0; j < 2; j++)
                {
                    if(atributos[i][j].total)
                        atributos[i][j].prob = (float)atributos[i][j].sim / (float)atributos[i][j].total;
                    else
                        atributos[i][j].prob = 0.0;
                }
            }
            else
            {
                for(int j = 0; j < 2; j++)
                {
                    if(atributos[i][j].total)
                        atributos[i][j].prob = (float)atributos[i][j].nao / (float)atributos[i][j].total;
                    else
                        atributos[i][j].prob = 0.0;
                }
            }
        }
        else
        {
            if(!maior)
            {
                for(int j = 0; j < 2; j++)
                {
                    if(atributos[i][j].total)
                        atributos[i][j].prob = (float)atributos[i][j].sim / (float)atributos[i][j].total;
                    else
                        atributos[i][j].prob = 0.0;
                }
            }
            else
            {
                for(int j = 0; j < 2; j++)
                {
                    if(atributos[i][j].total)
                        atributos[i][j].prob = (float)atributos[i][j].nao / (float)atributos[i][j].total;
                    else
                        atributos[i][j].prob = 0.0;
                }
            }
        }
    }

    //for(int i = 0; i < p - 1; i++)
    //    cout << "prob[" << i << "][0] = " << atributos[i][0].prob << endl << "prob[" << i << "][1] = " << atributos[i][1].prob << endl;
}

//Calcula os atributos com as restriçoes em atts
void calcAtt(int maior, vector<string> atts)
{
    /*
    for(int i = 0; i < p; i++)
        cout << atributos[i][0].nome << "\t" << atributos[i][1].nome << endl;
    cout << endl;

    cout << achaAttPos("muito").i << "\t" << achaAttPos("muito").j << endl; 
    */

    zeraAtributos();
    for(int i = 0; i < h; i++)
    {   
        if(tabela[i][0].checar)
        {
            bool passa = false;
            for(int z = 0; z < atts.size(); z++)
            {
                int y = achaQuesDoAttNaTabela(atts[z]);
                if(tabela[i][y].valor != atts[z])
                    passa = true;
            }
            if(passa)
                continue;
            
            for(int j = 0; j < p - 1; j++)
            {   
                tPos att = achaAttPos(tabela[i][j].valor); 
                if(tabela[i][p - 1].valor == atributos[p - 1][0].nome)
                {
                    atributos[att.i][att.j].sim++;
                    atributos[att.i][att.j].total++;
                }
                else
                {
                    atributos[att.i][att.j].nao++;
                    atributos[att.i][att.j].total++;
                }

            }
            if(tabela[i][p - 1].valor == atributos[p - 1][0].nome)
            {
                atributos[p - 1][0].sim++;
                atributos[p - 1][0].total++;
                atributos[p - 1][1].total++;
            }
            else
            {
                atributos[p - 1][1].sim++;
                atributos[p - 1][0].total++;
                atributos[p - 1][1].total++;
            }
        }
    }
    
    //printaAtributos();

    for(int i = 0; i < p - 1; i++)
    {
        if(maior == -1)
        {
            if(atributos[p - 1][0].sim >= atributos[p - 1][1].sim)
            {
                for(int j = 0; j < 2; j++)
                {
                    if(atributos[i][j].total)
                        atributos[i][j].prob = (float)atributos[i][j].sim / (float)atributos[i][j].total;
                    else
                        atributos[i][j].prob = 0.0;
                }
            }
            else
            {
                for(int j = 0; j < 2; j++)
                {
                    if(atributos[i][j].total)
                        atributos[i][j].prob = (float)atributos[i][j].nao / (float)atributos[i][j].total;
                    else
                        atributos[i][j].prob = 0.0;
                }
            }
        }
        else
        {
            if(!maior)
            {
                for(int j = 0; j < 2; j++)
                {
                    if(atributos[i][j].total)
                        atributos[i][j].prob = (float)atributos[i][j].sim / (float)atributos[i][j].total;
                    else
                        atributos[i][j].prob = 0.0;
                }
            }
            else
            {
                for(int j = 0; j < 2; j++)
                {
                    if(atributos[i][j].total)
                        atributos[i][j].prob = (float)atributos[i][j].nao / (float)atributos[i][j].total;
                    else
                        atributos[i][j].prob = 0.0;
                }
            }
        }
    }

    //for(int i = 0; i < p - 1; i++)
    //    cout << "prob[" << i << "][0] = " << atributos[i][0].prob << endl << "prob[" << i << "][1] = " << atributos[i][1].prob << endl;
}

void cortarDaTabela(vector<string> atts)
{
    for(int i = 0; i < h; i++)
    {
        if(tabela[i][0].checar)
        {
            int comparacoes = 0;
            for(int j = 0; j < atts.size(); j++)
            {   
                int w = achaQuesDoAttNaTabela(atts[j]);
                if(tabela[i][w].valor == atts[j])
                    comparacoes++;
                //cout << "comparando " << atts[j] << endl;
                //cout << atts.size() << endl;
            }
            if(comparacoes == atts.size())
            {
                tabela[i][0].checar = false;
                //cout << "cortou " << i << endl;
            }
        }
    }
}


void cortarDaTabela(int j)
{
    tPos maior = achaMaiorProbAtt();

    for(int i = 0; i < h; i++)
        if(tabela[i][j].valor == atributos[maior.i][maior.j].nome)
            tabela[i][0].checar = false;
}

void printaTabela()
{
    for(int i = 0; i < p; i++)
        cout << questoes[i] << "\t\t\t";
    cout << endl;
    for(int i = 0; i < h; i++)
    {
        if(tabela[i][0].checar)
            for(int j = 0; j < p; j++)
                cout << tabela[i][j].valor << "\t\t\t\t";
        cout << endl;
    }
}

void resetaTabela()
{
    for(int i = 0; i < h; i++)
        tabela[i][0].checar = true;
}

void resolve()
{
    criaAtributos();
    calcAtt(-1);
    int classe;

    if(atributos[p - 1][0].sim >= atributos[p - 1][1].sim)
        classe = 0;
    else
        classe = 1;

    tPos maior = achaMaiorProbAtt();

    //cout << "Maior = prob[" << maior.i << "][" << maior.j << "]" << endl;
    for(int k = 0; k < 2; k++)
    {
        if(k == 1)
        {
            if(classe)
                classe = 0;
            else
                classe = 1;
            resetaTabela();
            zeraAtributos();
            calcAtt(classe);
            maior = achaMaiorProbAtt();
        }
        while(atributos[p - 1][classe].sim && atributos[maior.i][maior.j].prob)
        {
            int j = achaQuesDoAttNaTabela(atributos[maior.i][maior.j].nome);
            vector<string> atts;
            if(atributos[maior.i][maior.j].prob == 1.0)
            {
                cout << "se " << questoes[j] << " = \'" << atributos[maior.i][maior.j].nome << "\' entao " << questoes[p - 1] << " = \'";
                if(!classe)
                    cout << atributos[p - 1][0].nome << "\'" << endl;
                else
                    cout << atributos[p - 1][1].nome << "\'" << endl;
                
                cortarDaTabela(j);
            }
            else
            {
                string regra = "se ";
                while(atributos[maior.i][maior.j].prob != 1.0)
                {
                    atts.push_back(atributos[maior.i][maior.j].nome);
                    //cout << atributos[maior.i][maior.j].nome << endl;
                    regra += questoes[j];
                    regra += " = \'";
                    regra += atributos[maior.i][maior.j].nome;
                    regra +="\' e ";

                    calcAtt(classe, atts);
                    //printaAtributos();
                    maior = achaMaiorProbAtt();

                    atts.push_back(atributos[maior.i][maior.j].nome);

                    //cout << "Maior = prob[" << maior.i << "][" << maior.j << "]" << endl;
                    j = achaQuesDoAttNaTabela(atributos[maior.i][maior.j].nome);
                }

                regra += questoes[j];
                regra += " = \'";
                regra += atributos[maior.i][maior.j].nome;
                regra += "\' entao \'";
                regra += questoes[p - 1];
                regra += "\' = \'";

                if(!classe)
                {
                    regra += atributos[p - 1][0].nome;
                    regra += "\'";

                }
                else
                {
                    regra += atributos[p - 1][1].nome;
                    regra += "\'";
                }

                cout << regra << endl;
                cortarDaTabela(atts);

            }
            //printaTabela();
            atts.clear();
            calcAtt(classe);
            maior = achaMaiorProbAtt();
        }
    }


    /*
    for(int i = 0; i < p; i++)
        cout << atributos[i][0].nome << "\t" << atributos[i][1].nome << endl;
    cout << endl;
    */
}


int main()
{
    string line;
    string arq;
    string questao;
    ifstream myfile;
    vector<string> linhas;
    
 
    myfile.open("tabela.csv");

    if (myfile.is_open())
    {
        getline (myfile,questao);
        questoes = quebra(questao, ',');

        for (int i = 0; i < h; i++)
        {
            getline(myfile, line);
            linhas = quebra(line, ',');
            for(int j = 0; j < p; j++)
            {
                tabela[i][j].valor = linhas[j];
                tabela[i][j].checar = true;
                tabela[i][j].pergunta = questoes[j];
            }
        }
        myfile.close();
    }
    else 
        cout << "Erro ao abrir arquivo" << endl;
    
    resolve();

    /*
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < p; j++)
            cout << tabela[i][j].valor << "\t";
        cout << endl;
    }
    */

    return 0;
}