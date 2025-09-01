#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "sistemalogistico.hpp"
#include "evento.hpp"

using namespace std;

// Função auxiliar para converter string de tipo de evento para enum tipo_evento
TipoEvento stringTotipo_evento(const string& tipoStr) {
    if (tipoStr == "RG") return RG;
    if (tipoStr == "AR") return AR;
    if (tipoStr == "RM") return RM;
    if (tipoStr == "UR") return UR;
    if (tipoStr == "TR") return TR;
    if (tipoStr == "EN") return EN;
    return RG; // valor padrão para evitar erro
}

int main(int argc, char* argv[]) {
    SistemaLogistico sistema;
    string line;
    bool primeira_consulta = true; // Foi útil para garantir um endl entre consultas

    if (argc < 2) {
        cerr << "É preciso passar o nome do arquivo como argumento" << endl;
        return 1;
    }

    ifstream arquivo(argv[1]);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    while (getline(arquivo, line)) {
        stringstream ss(line);
        double data_hora;
        string tipo_operacao;

        ss >> data_hora >> tipo_operacao;

        if (tipo_operacao == "EV") {
            string tipo_eventoStr;
            int idPacote;
            ss >> tipo_eventoStr >> idPacote;
            TipoEvento tipo_evento = stringTotipo_evento(tipo_eventoStr);

            // Variáveis para dados específicos do evento
            string remetente, destinatario;
            int campo1 = -1, campo2 = -1;

            if (tipo_evento == RG) {
                ss >> remetente >> destinatario >> campo1 >> campo2;
                sistema.processarEvento(Evento(data_hora, tipo_evento, idPacote, remetente, destinatario, campo1, campo2));
            } else if (tipo_evento == AR || tipo_evento == RM || tipo_evento == UR || tipo_evento == TR) {
                ss >> campo1 >> campo2;
                sistema.processarEvento(Evento(data_hora, tipo_evento, idPacote, campo1, campo2));
            } else if (tipo_evento == EN) {
                ss >> campo1;
                sistema.processarEvento(Evento(data_hora, tipo_evento, idPacote, campo1));
            }

        } else if (tipo_operacao == "CL") {
            string nome_cliente;
            ss >> nome_cliente;

            if (!primeira_consulta) std::cout << endl; // Para garantir um endl entre consultas
            sistema.consultarHistoricoCliente(data_hora, nome_cliente);
            primeira_consulta = false;

        } else if (tipo_operacao == "PC") {
            int idPacote;
            ss >> idPacote;

            if (!primeira_consulta) std::cout << endl;
            sistema.consultarHistoricoPacote(data_hora, idPacote);
            primeira_consulta = false;
        }
    }

    arquivo.close();

    return 0;
}