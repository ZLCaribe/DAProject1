#include "Manager.h"

#include <iostream>

using namespace std;

void Manager::mainMenu(){
    int i = 0;
    while(i != 5){
        cout << "------------MENU PRINCIPAL----------" << endl;
        cout << "Selecione a opcao: \n";
        cout << "1: Ler ficheiros\n";
        cout << "2: Métricas básicas de serviço \n";
        cout << "3: Obter percurso de custo ótimo \n";
        cout << "4: Testar falhas em linhas \n";
        cout << "5: Sair \n";
        cout << "Número de estações carregadas: " << this->graph.getStationSet().size() << endl;
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
    std::vector<Station *> r;
    int i = 0;
    while(i != 5){
        cout << "------------MENU MÉTRICAS BÁSICAS DE SERVIÇO----------" << endl;
        cout << "Selecione a opcao: \n";
        cout << "1: Calcular fluxo máximo entre duas estações \n";
        cout << "2: Identificar pares de estações com maior fluxo \n";
        cout << "3: Identificar prioridades de investimento \n";
        cout << "4: Calcular número máximo de trens que podem chegar numa estação \n";
        cout << "5: Sair \n";
        cout << "opcao: ";
        cin >> i;
        switch (i) {
            case 1:
                Station *orig,*dest;
                if(inputStation(orig,"Insira a estação de origem") != 0){
                    cout << "Operação cancelada" << endl;
                    continue;
                }
                if(inputStation(dest,"Insira a estação de destine") != 0){
                    cout << "Operação cancelada" << endl;
                    continue;
                }
                cout << "O fluxo máximo partindo de " << orig->getName() << " com destino a " << dest->getName()
                << "é: " << this->graph.maxFlowPair(orig,dest) << endl << endl;
                break;
            case 2:
                r = this->graph.getPairsWithMaxFlow();
                cout << "Os trajetos com maior fluxo são: " << endl;
                for(int k = 0; k < r.size(); k+=2){
                    cout << r.at(k)->getName() << "->" << r.at(k+1) << endl;
                }
                cout << endl;
                break;
            case 3:
                //TODO
                break;
            case 4:
                Station *m;
                if(inputStation(m,"Insira a estação que deseja saber o fluxo máximo de entrada: ") != 0){
                    cout << "Operação cancelada" << endl;
                    continue;
                }
                cout << "O fluxo máximo para essa estação tendo em conta toda a rede de trens é: "
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
    Station *s, *t;
    if(inputStation(s,"Insira a estação de origem") != 0){
        cout << "Operação cancelada" << endl;
        return;
    }
    if(inputStation(t,"Insira a estação de destine") != 0){
        cout << "Operação cancelada" << endl;
        return;
    }
    double cost = this->graph.costOptmizationMaxFlowPair(s,t);
    cout << "O custo mínimo para fazer esse percurso é: " << cost << endl;
}

void Manager::testLineFailures() {
    Graph subgraph = this->graph.generateSubGraph();
    int k;
    cout << "Insira o top-k estações afetadas que pretende ver: ";
    cin >> k;
    auto report = this->graph.mostAffectedStations(subgraph,k);
    int i = 1;
    cout << "Top" << k << "estações mais afetadas pelas falhas:" << endl;
    for(auto x : report){
        cout << "Top " << i++ << ":" << x.first.getName() << endl;
        cout << "Redução no fluxo" << x.second << endl << endl;
    }
}

int Manager::inputStation(Station *station, string message) {
    int flag = 1;
    string i;
    Station *temp;
    cout << message << endl;
    while(flag > 0){
        cout << "Nome da estação: ";
        cin >> i;
        if(i == "sair"){
            station = nullptr;
            break;
        }
        station = this->graph.findStation(i);
        if(temp != nullptr){
            flag = 0;
        }
        else cout << "Estação não encontrada insira um nome diferente" << endl;
    }
    return flag;
}
