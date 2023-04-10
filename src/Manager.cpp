#include "Manager.h"

#ifdef _WIN32
const std::string file_path = "..\\data\\";
#else
const std::string file_path = "data/";
#endif

using namespace std;

Manager::Manager() = default;

/**
 * Reads a field from a cvs file
 * @param line istringstream variable
 * @param delim until which character should the line be read
 */
std::string getField(std::istringstream &line,char delim){
    std::string string1,string2;
    getline(line,string1,delim);
    if(string1.front() == '"' && string1.back() != '"'){
        getline(line,string2,'"');
        string1 += string2;
        getline(line,string2,',');
        return string1.substr(1);
    }else return string1;
}

/**
 * Reads both cvs files and adds the data to the graph
 */
void Manager::readFiles() {
    bool f = true;

    std::ifstream files (file_path + "stations.csv");

    std::string entry;
    std::string first, second, third, fourth, fifth;
    
    while(getline(files, entry)) {
        if(f) {
            f = false;
        } else {
            std::istringstream station(entry);

            first = getField(station,',');
            second = getField(station,',');
            third = getField(station,',');
            fourth = getField(station,',');
            fifth = getField(station, '\n');
            graph.addStation(first, second, third, fourth, fifth);
        }
    }

    f = true;
    std::ifstream filen (file_path + "network.csv");
    while(getline(filen, entry)) {
        if(f) {
            f = false;
        } else {
            std::istringstream station(entry);

            first = getField(station,',');
            second = getField(station,',');
            third = getField(station,',');
            fourth = getField(station, '\n');
            graph.addNetwork(first, second, stoi(third), fourth);
        }
    }
}


void Manager::mainMenu(){
    int i = 0, n;
    while(i != 5){
        cout << "------------MENU PRINCIPAL----------" << endl;
        cout << "Selecione a opcao: \n";
        cout << "1: Ler ficheiros\n";
        cout << "2: Metricas basicas de servico \n";
        cout << "3: Obter percurso de custo otimo \n";
        cout << "4: Testar falhas em linhas \n";
        cout << "5: Sair \n";
        n = (int) this->graph.getStationSet().size();
        cout << "Numero de estacoes carregadas: " << n << endl;
        cout << "opcao: ";
        cin >> i;
        switch (i) {
            case 1:
                this->readFiles();
                break;
            case 2:
                this->basicMetricsMenu();
                break;
            case 3:
                this->costOptmization();
                break;
            case 4:
                this->lineFailuresMenu();
                break;
            case 5:
                cout << "A sair..." << endl;
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
        }
    }
}

void Manager::basicMetricsMenu() {
    std::pair<int, std::vector<Vertex *>> p;
    vector<Vertex *> r;
    Vertex *m = nullptr, *orig = nullptr, *dest = nullptr;
    int i = 0;
    while(i != 5){
        cout << "------------MENU METRICAS BASICAS DE SERVICO----------" << endl;
        cout << "Selecione a opcao: \n";
        cout << "1: Calcular fluxo maximo entre duas estacoes \n";
        cout << "2: Identificar pares de estacoes com maior fluxo \n";
        cout << "3: Identificar prioridades de investimento \n";
        cout << "4: Calcular numero maximo de trens que podem chegar numa estacao \n";
        cout << "5: Sair \n";
        cout << "opcao: ";
        cin >> i;
        switch (i) {
            case 1:
                if((orig = inputStation("Insira a estacao de origem")) == nullptr){
                    cout << "Operacao cancelada" << endl;
                    continue;
                }
                if((dest = inputStation("Insira a estacao de destino")) == nullptr){
                    cout << "Operacao cancelada" << endl;
                    continue;
                }

                cout << "O fluxo maximo partindo de " << orig->getName() << " com destino a " << dest->getName()
                << " e: " << this->graph.maxFlowPair(orig,dest) << endl << endl;
                break;
            case 2:
                p = this->graph.getPairsWithMaxFlow();
                r = p.second;
                cout << "Os trajetos com maior fluxo( " << p.first << " )sao: " << endl;
                for(int k = 0; k < r.size(); k+=2){
                    cout << r.at(k)->getName() << "->" << r.at(k+1)->getName() << endl;
                }
                cout << endl;
                break;
            case 3:
                i = 0;
                while(i != 3) {
                    cout << "Quer saber a classificacao por municipalidades ou distritos?" << endl;
                    cout << "1: Municipalidades" << endl;
                    cout << "2: Distritos" << endl;
                    cout << "3: Sair" << endl;
                    cout << "opcao: ";
                    cin >> i;
                    std::vector<std::pair<std::string, int>> x;
                    bool MorD = i == 2;
                    int k;
                    if(i <= 2 && i >= 1){
                        cout << "Quantos " << (MorD?"distritos":"municipios") << " quer ver? ";
                        cin >> k;
                        if(k < 1) continue;
                        printPriorities(this->graph.getBudgetPriorities(MorD, k),MorD);
                    }else if(i == 3) cout << "A sair..." << endl;
                    else cout << "Selecione uma opcao valida!" << endl;
                }
                break;
            case 4:
                if((m = inputStation("Insira a estacao que deseja saber o fluxo maximo de entrada: ")) == nullptr){
                    cout << "Operação cancelada" << endl;
                    continue;
                }
                cout << "O fluxo maximo para essa estacao tendo em conta toda a rede de trens e: "
                << this->graph.maxStationFlow(m) << endl << endl;
                break;
            case 5:
                cout << "A sair..." << endl;
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
                break;
        }
    }
}

void Manager::costOptmization() {
    Vertex *s = nullptr, *t = nullptr;
    if((s = inputStation("Insira a estacao de origem")) == nullptr){
        cout << "Operação cancelada" << endl;
        return;
    }
    if((t = inputStation("Insira a estacao de destino")) == nullptr){
        cout << "Operação cancelada" << endl;
        return;
    }
    std::pair<int,int> result = this->graph.costOptmizationMaxFlowPair(s,t);
    cout << "O custo minimo para fazer esse percurso e: " << result.first << endl;
    cout << "O fluxo maximo para fazer esse percurso e: " << result.second << endl;
}

void Manager::lineFailuresMenu() {
    bool done = false;
    Vertex *s = nullptr, *t = nullptr;
    vector<Vertex*> edges;

     while (!done) {
        if((s = inputStation("Insira a estacao de origem da edge a remover")) == nullptr) {
            cout << "Operação concluida" << endl;
            done = true;
            continue;
        }
        for(auto a : s->getEdges()){
            cout << a->getDest()->getName() << endl;
        }
        if((t = inputStation("Insira a estacao de destino da edge a remover")) == nullptr) {
            cout << "Operação concluida" << endl;
            done = true;
            continue;
        }

        edges.push_back(s);
        edges.push_back(t);
    }
    graph.generateSubGraph(edges);
    int i = 0;

    while(i != 3){
        cout << "-----------MENU FALHAS NA LINHA----------" << endl;
        cout << "Selecione a opcao: \n";
        cout << "1: Calcular fluxo maximo entre duas estacoes \n";
        cout << "2: Estações mais afetadas \n";
        cout << "3: Sair \n";
        cout << "opcao: ";
        cin >> i;
    
        switch(i) {
            case 1:
                if((s = inputStation("Insira a estacao de origem")) == nullptr){
                    cout << "Operacao cancelada" << endl;
                    continue;
                }
                if((t = inputStation("Insira a estacao de destino")) == nullptr){
                    cout << "Operacao cancelada" << endl;
                    continue;
                }

                cout << "O fluxo maximo partindo de " << s->getName() << " com destino a " << t->getName()
                << " e: " << graph.subMaxFlowPair(s,t) << endl << endl;
                break;
            case 2:
                for(auto r : graph.mostAffectedStations(5)){
                    cout << r.first->getName() << " - " << r.second << endl;
                }
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
                break;
        }
    }
}

Vertex *Manager::inputStation(const string& message) {
    int flag = 1;
    string i = "xxx";
    Vertex *temp;
    cout << message << endl;
    while(true){
        cout << "Digite: 'sair' se desejar cancelar a operacao" << endl;
        cout << "Nome da estacao: ";
        getline(std::cin >> std::ws,i);
        if(i == "sair"){
            return nullptr;
        }
        temp = this->graph.findStation(i);
        if(temp != nullptr){
            flag = 0;
            return temp;
        }else cout << "Estacao nao encontrada insira um nome diferente" << endl;
    }
}

void Manager::printPriorities(const vector<pair<string, int>>& v, bool MorD) {
    int i = 1;
    cout << "De acordo com o numero maximo de trens que podem chegar nas estacoes de cada "
    << (MorD?"distrito":"municipio") << endl;
    cout << "O top " << v.size() << (MorD?" distrito":" municipio") << " e: " <<endl;
    for(const auto& item : v){
        cout << i++ << ": " << item.first << " - " << item.second << endl;
    }
}
