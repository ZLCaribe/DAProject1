#include "Manager.h"

using namespace std;

Manager::Manager() = default;

void Manager::readFiles() {
    bool f = true;
    std::ifstream files ("data/stations.csv");

    std::string entry, temp;
    std::string first, second, third, fourth, fifth;
    
    while(getline(files, entry)) {
        if(f) {
            f = false;
        } else {
            std::stringstream station(entry);

            getline(station, first, ',');
            getline(station, second, ',');
            getline(station, third, ',');
            getline(station, fourth, ',');

            //este codigo esta feio, depois melhoro
            if(fourth.size()>0){
                if(fourth.at(0)=='\"'){
                    getline(station, temp, '\"');
                    fourth += temp;
                    getline(station, temp, ',');
                    fourth += temp;
                    fourth.erase(0, 1);
                }
            }

            getline(station, fifth, '\n');
            graph.addStation(first, second, third, fourth, fifth);
        }
    }

    f = true;
    std::ifstream filen ("data/network.csv");
    while(getline(filen, entry)) {
        if(f) {
            f = false;
        } else {
            std::stringstream station(entry);

            getline(station, first, ',');
            getline(station, second, ',');
            getline(station, third, ',');
            getline(station, fourth, '\n');

            graph.addNetwork(first, second, stoi(third), fourth);
        }
    }
}


void Manager::mainMenu(){
    int i = 0, n;
    this->readFiles();
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
                this->testLineFailures();
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
    std::vector<Vertex *> r;
    Vertex *m = nullptr, *orig = nullptr, *dest = nullptr;
    int i = 0;
    while(i != 5){
        cout << "------------MENU METRICAS BASICAS DE SERVIÇO----------" << endl;
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
                if(inputStation(orig,"Insira a estacao de origem") != 0){
                    cout << "Operacao cancelada" << endl;
                    continue;
                }
                if(inputStation(dest,"Insira a estacao de destino") != 0){
                    cout << "Operacao cancelada" << endl;
                    continue;
                }
                cout << "O fluxo maximo partindo de " << orig->getName() << " com destino a " << dest->getName()
                << "e: " << this->graph.maxFlowPair(orig,dest) << endl << endl;
                break;
            case 2:
                r = this->graph.getPairsWithMaxFlow();
                cout << "Os trajetos com maior fluxo sao: " << endl;
                for(int k = 0; k < r.size(); k+=2){
                    cout << r.at(k)->getName() << "->" << r.at(k+1) << endl;
                }
                cout << endl;
                break;
            case 3:
                //TODO
                break;
            case 4:
                if(inputStation(m,"Insira a estacao que deseja saber o fluxo maximo de entrada: ") != 0){
                    cout << "Operação cancelada" << endl;
                    continue;
                }
                cout << "O fluxo maximo para essa estação tendo em conta toda a rede de trens e: "
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
    if(inputStation(s,"Insira a estacao de origem") != 0){
        cout << "Operação cancelada" << endl;
        return;
    }
    if(inputStation(t,"Insira a estacao de destino") != 0){
        cout << "Operação cancelada" << endl;
        return;
    }
    double cost = this->graph.costOptmizationMaxFlowPair(s,t);
    cout << "O custo minimo para fazer esse percurso e: " << cost << endl;
}

void Manager::testLineFailures() {
    Graph subgraph = this->graph.generateSubGraph();
    int k;
    cout << "Insira o top-k estacoes afetadas que pretende ver: ";
    cin >> k;
    auto report = this->graph.mostAffectedStations(subgraph,k);
    int i = 1;
    cout << "Top" << k << "estacoes mais afetadas pelas falhas:" << endl;
    for(auto x : report){
        cout << "Top " << i++ << ":" << x.first.getName() << endl;
        cout << "Reducao no fluxo" << x.second << endl << endl;
    }
}

int Manager::inputStation(Vertex *station, const string& message) {
    int flag = 1;
    string i;
    Vertex *temp;
    cout << message << endl;
    while(flag > 0){
        cout << "Digite: 'sair' se desejar cancelar a operação" << endl;
        cout << "Nome da estacao: ";
        cin >> i;
        if(i == "sair"){
            station = nullptr;
            break;
        }
        temp = this->graph.findStation(i);
        if(temp != nullptr){
            flag = 0;
            station = temp;
        }else cout << "Estacao nao encontrada insira um nome diferente" << endl;
    }
    return flag;
}
