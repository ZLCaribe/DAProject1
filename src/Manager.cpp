#include "Manager.h"

#ifdef _WIN32
const std::string file_path = "..\\data\\";
#else
const std::string file_path = "data/";
#endif

using namespace std;

Manager::Manager() = default;

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
                //TODO
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
    vector<Vertex*> toRemove;

    while (!done) {
        if((s = inputStation("Insira a estacao de origem da edge a remover")) == nullptr) {
            cout << "Operação cancelada" << endl;
            done = true;
            continue;
        }
        if((t = inputStation("Insira a estacao de destino da edge a remover")) == nullptr) {
            cout << "Operação cancelada" << endl;
            done = true;
            continue;
        }

        toRemove.push_back(s);
        toRemove.push_back(t);
    }

    Graph subgraph = this->graph.generateSubGraph(toRemove);
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
                << " e: " << subgraph.maxFlowPair(s,t) << endl << endl;
                break;
            case 2:
                break;
            default:
                cout << "Selecione uma opcao valida!" << endl;
                break;
        }
    }

    /*
    int k;
    cout << "Insira o top-k estacoes afetadas que pretende ver: ";
    cin >> k;
    auto report = this->graph.mostAffectedStations(subgraph,k);
    int j = 1;
    cout << "Top " << k << " estacoes mais afetadas pelas falhas:" << endl;
    for(auto x : report){
        cout << "Top " << j++ << ":" << x.first.getName() << endl;
        cout << "Reducao no fluxo" << x.second << endl << endl;
    }*/
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
