#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ContaBancaria
{

private:
    int conta;
    string titular;
    double saldo;

public:
    ContaBancaria() : conta(0), titular(""), saldo(0.0) {}

    ContaBancaria(int conta, string &titular, double saldo)
    {
        this->conta = conta;
        this->titular = titular;
        this->saldo = saldo;
    }

    void Depositar(double quantia)
    {
        saldo += quantia;
        cout << "Deposito de R$" << quantia << " realizado com sucesso." << endl;
    }

    void Sacar(double quantia)
    {
        if (quantia <= saldo)
        {
            saldo -= quantia;
            cout << "Saque de R$" << quantia << " realizado com sucesso." << endl;
        }
        else
        {
            cout << "Saldo insuficiente para realizar o saque." << endl;
        }
    }

    double ConsultarSaldo() const
    {
        return saldo;
    }

    int getNumeroConta() const
    {
        return conta;
    }
};

void exibirMenu()
{
    cout << "\nMENU:" << endl;
    cout << "1 - Registrar novo usuario" << endl;
    cout << "2 - Realizar operacao em uma conta existente" << endl;
    cout << "3 - Sair" << endl;
}

void consultarSaldo(const ContaBancaria &conta)
{
    cout << "Saldo atual da conta " << conta.getNumeroConta() << ": R$" << conta.ConsultarSaldo() << endl;
}

void registrarNovoUsuario(ContaBancaria *usuarios, int &totalUsuarios, int capacidadeMaxima)
{
    if (totalUsuarios < capacidadeMaxima)
    {
        int numeroConta;
        string titular;

        cout << "Digite o numero da conta: ";
        cin >> numeroConta;
        cout << "Digite o nome do titular: ";
        cin.ignore();
        getline(cin, titular);

        usuarios[totalUsuarios] = ContaBancaria(numeroConta, titular, 0.0);
        totalUsuarios++;
        cout << "Usuario registrado com sucesso." << endl;
    }
    else
    {
        cout << "Limite maximo de usuarios atingido (" << capacidadeMaxima << ")" << endl;
    }
}

void realizarOperacoes(ContaBancaria *usuarios, int totalUsuarios)
{
    int numeroConta;
    cout << "Digite o numero da conta: ";
    cin >> numeroConta;

    auto it = find_if(usuarios, usuarios + totalUsuarios, [numeroConta](const ContaBancaria &conta){ 
        return conta.getNumeroConta() == numeroConta;
    });

    if (it != usuarios + totalUsuarios)
    {
        int operacao;
        cout << "\nOperacao disponiveis:" << endl;
        cout << "1 - Depositar" << endl;
        cout << "2 - Sacar" << endl;
        cout << "3 - Consultar saldo" << endl;
        cout << "Escolha uma operacao: ";
        cin >> operacao;

        switch (operacao)
        {
        case 1:
        {
            double quantia;
            cout << "Digite a quantia a depositar: ";
            cin >> quantia;
            it->Depositar(quantia);
            break;
        }
        case 2:
        {
            double quantia;
            cout << "Digite a quantia a sacar: ";
            cin >> quantia;
            it->Sacar(quantia);
            break;
        }
        case 3:
        {
            consultarSaldo(*it);
            break;
        }
        default:
            cout << "Opcao invalida." << endl;
            break;
        }
    }
    else
    {
        cout << "Conta nao encontrada." << endl;
    }
}

int main()
{
    const int capacidadeMaxima = 100;
    ContaBancaria *usuarios = new ContaBancaria[capacidadeMaxima];
    int totalUsuarios = 0;

    int escolha;

    do
    {
        exibirMenu();
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            registrarNovoUsuario(usuarios, totalUsuarios, capacidadeMaxima);
            break;
        case 2:
            realizarOperacoes(usuarios, totalUsuarios);
            break;
        case 3:
            cout << "Saindo do programa." << endl;
            break;
        default:
            cout << "Opcao invalida" << endl;
        }
    } while (escolha != 3);

    delete[] usuarios;

    return 0;
}