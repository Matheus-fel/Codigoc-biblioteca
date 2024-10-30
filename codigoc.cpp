#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct emprestimo {
    int data_emp, data_dev;
    char user[100];
};

struct catalogo {
    int codigo, num_pag;
    char titulo[100];
    char autores[100];
    char editora[100];
    char area[50];       // (Exatas, Humanas, Saúde)
    struct emprestimo emp;
    bool disponivel;
};

catalogo livros[50];
int total_livros = 0;  // Conta o número de livros cadastrados.

// Função para não precisar ficar repetindo esse salvamento de dados no programa.
void salvar_dados(FILE* dados_biblioteca){
  fseek(dados_biblioteca, 0, SEEK_SET);
  
  fwrite(&total_livros, sizeof(int), 1, dados_biblioteca);
  
  fwrite(livros, sizeof(catalogo), total_livros, dados_biblioteca);
}

int main() {

    FILE *dados_biblioteca;

    // Tenta abrir o arquivo existente
    dados_biblioteca = fopen("Biblioteca.dat", "rb+");
    if (dados_biblioteca == NULL) {
        // Caso o arquivo não exista, cria um novo
        dados_biblioteca = fopen("Biblioteca.dat", "wb+");
        if (dados_biblioteca == NULL) {
            cout << "Erro ao abrir o arquivo!";
            return 1;
        }
    } else {
        // Carrega o número total de livros cadastrados
        fread(&total_livros, sizeof(int), 1, dados_biblioteca);

        // Carrega os dados dos livros a partir do arquivo
        fread(livros, sizeof(catalogo), total_livros, dados_biblioteca);
    }

    int i, menu;
    bool encontrado = false;

    do {
        
        cout << "Selecione uma opção no menu abaixo para prosseguir." << endl << endl;
        cout << "1 - Cadastro" << endl;
        cout << "2 - Alteração" << endl;
        cout << "3 - Exclusão" << endl;
        cout << "4 - Empréstimo" << endl;
        cout << "5 - Devolução" << endl;
        cout << "6 - Consulta de livro" << endl;
        cout << "7 - Livros disponíveis" << endl;
        cout << "8 - Listagem de todos os livros" << endl;
        cout << "9 - Sair" << endl << endl;
        cout << "Opção: ";
        cin >> menu;

        switch (menu) {
            case 1: {
                // Verifica se ainda tem espaço para armazenar mais livros.
                if (total_livros < 50) {
                    catalogo *novo_livro = &livros[total_livros];  // Usando ponteiro para o novo livro cadastrado.

                    cout << endl << "Digite abaixo as seguintes informações para o livro ser registrado." << endl << endl;

                    cout << "Código do livro: ";
                    cin >> novo_livro->codigo;

                    cout << "Área científica (Exatas, Humanas, Saúde): ";
                    cin.ignore(); // Ignora a quebra de linha após o cin anterior
                    cin.getline(novo_livro->area, 50);

                    cout << "Título da obra: ";
                    cin.getline(novo_livro->titulo, 100);

                    cout << "Autor(es) da obra: ";
                    cin.getline(novo_livro->autores, 100);

                    cout << "Editora de publicação: ";
                    cin.getline(novo_livro->editora, 100);

                    cout << "Número de páginas: ";
                    cin >> novo_livro->num_pag;

                    novo_livro->disponivel = true;  // Marca que o livro está disponível para empréstimo.
                    total_livros++;

                    // Salvar os dados após o cadastro
                    salvar_dados(dados_biblioteca);

                    cout << endl << "O cadastro do livro foi realizado com sucesso!" << endl << endl;
                } else {
                    cout << endl << "Desculpe, o limite de livros foi atingido." << endl << endl;
                }
                cin.ignore();
                cin.get();
                break;
            }
            
            case 2: {
              int code_search, alterar;
              
              cout << endl << "Digite o código do livro que deseja fazer a alteração dos dados: ";
              cin >> code_search;
              
              for (i=0; i < total_livros; i++){
                if (livros[i].codigo == code_search){
                  encontrado = true;
                  
                  do {
                    
                    cout << endl <<"Escolha qual dado do livro deseja alterar:" << endl << endl;
                    
                    cout << "1 - Código" << endl;
                    cout << "2 - Área Científica" << endl;
                    cout << "3 - Título" << endl;
                    cout << "4 - Autores" << endl;
                    cout << "5 - Editora" << endl;
                    cout << "6 - Número de páginas" << endl;
                    cout << "7 - Salvar e sair" << endl << endl;
                    cout << "Opção: ";
                    cin >> alterar;
                    
                    cin.ignore();
                    
                    switch (alterar){
                            case 1:{
                              int new_code;
                              
                              cout << endl << "Insira o novo código:";
                              cin >> new_code;
                              livros[i].codigo = new_code;
                              
                              cin.ignore();
                              cin.get();
                              break;
                            }
                            
                            case 2:{
                              char new_area[50];
                              
                              cout << endl << "Insira a área científica: ";
                              cin.getline(new_area, 50);
                              strcpy(livros[i].area, new_area); //strcpy é um comando da biblioteca <cstring> que serve pra poder atribuir um char a outro.
                              
                              cin.ignore();
                              cin.get();
                              break;
                            }
                            
                            case 3:{
                              char new_titulo[100];
                              
                              cout << endl << "Insira o novo título do livro: ";
                              cin.getline(new_titulo, 100);
                              strcpy(livros[i].titulo, new_titulo);
                              
                              cin.ignore();
                              cin.get();
                              break;
                            }
                            
                            case 4:{
                              char new_autores[100];
                              
                              cout << endl << "Informe os autores do livro: ";
                              cin.getline(new_autores, 100);
                              strcpy(livros[i].autores, new_autores);
                              
                              cin.ignore();
                              cin.get();
                              break;
                            }
                            
                            case 5:{
                              char new_editora[100];
                              
                              cout << endl << "Digite a editora de publicação do livro: ";
                              cin.getline(new_editora, 100);
                              strcpy(livros[i].editora, new_editora);
                              
                              cin.ignore();
                              cin.get();
                              break;
                            }
                            
                            case 6:{
                              int new_num_pag;
                              
                              cout << endl << "Digite a quantidade de páginas presente no livro: ";
                              cin >> new_num_pag;
                              livros[i].num_pag = new_num_pag;
                              
                              cin.ignore();
                              cin.get();
                              break;
                            }
                    }
                    
                    salvar_dados(dados_biblioteca);
                    
                    }while (alterar != 7);
                    cin.get();
                }
              }
              
              if(!encontrado){
                cout << endl << "Livro não encontrado." << endl;
                cin.ignore();
                cin.get();
              }
              
              break;
            }
            
            case 3: {
              int code_search;
              encontrado = false;
              
              cout << endl << "Digite o código do livro que deseja excluir: ";
              cin >> code_search;
              
              for (i = 0; i < total_livros; i++){
                if(livros[i].codigo == code_search){
                  encontrado = true;
                  
                  /*Essa parte serve para deslocar todos os livros depois do excluído uma posição para trás.
                  
                  Por exemplo, se o livro da posição 2 ser excluído, o que estava na posição 2 recebe os dados da posição 3, o 3 recebe do 4, até só o último livro ser vazio, depois esse último espaço vazio é apagado.*/
                  for (int j = i; j < total_livros - 1; j++){
                   livros[j] = livros[j + 1];
                  }
                  
                  total_livros--; // Diminui a quantidade de livros cadastrados
                  
                  // Salvar os dados após a exclusão
                  salvar_dados(dados_biblioteca);
                  
                  cout << endl << "Livro excluído com sucesso!" << endl << endl;
                  
                  break; // Encerrar o loop quando ele encontrar o livro
                }
              }
              
              if(!encontrado){
                cout << endl << "Livro não encontrado no catálogo" << endl << endl;
              }
              
              cin.ignore();
              cin.get();
              break;
            }

            case 4: {
                int code_search;
                encontrado = false;

                cout << endl << "Digite o código do livro que será realizado o empréstimo: ";
                cin >> code_search;

                for (i = 0; i < total_livros; i++) {
                    if (livros[i].codigo == code_search) {
                        encontrado = true;

                        if (livros[i].disponivel) {
                            cout << "Digite a data do empréstimo (somente números): ";
                            cin >> livros[i].emp.data_emp;

                            cout << "Digite a data de devolução (somente números): ";
                            cin >> livros[i].emp.data_dev;
                            cin.ignore();

                            cout << "Digite o nome do usuário: ";
                            cin.getline(livros[i].emp.user, 100);

                            livros[i].disponivel = false;  // Marca como indisponível para empréstimo.

                            // Salvar os dados após o empréstimo
                            salvar_dados(dados_biblioteca);

                            cout << endl << "O empréstimo do livro foi realizado com sucesso!" << endl << endl;
                        } else {
                            cout << endl << "O livro está indisponível para empréstimo." << endl << endl;
                        }
                        break;  // Encerrar o loop
                    }
                }
                if (!encontrado) {
                    cout << endl << "Livro não encontrado no catálogo." << endl << endl;
                }
                
                cin.ignore();
                cin.get();
                break;
            }

            case 5: {
                int code_search;
                encontrado = false;

                cout << endl << "Digite o código do livro que será realizada a devolução: ";
                cin >> code_search;

                for (i = 0; i < total_livros; i++) {
                    if (livros[i].codigo == code_search) {
                        encontrado = true;

                        if (!livros[i].disponivel) {
                            livros[i].emp = {};  // Limpa os dados do empréstimo.
                            livros[i].disponivel = true;

                            // Salvar os dados após a devolução
                            salvar_dados(dados_biblioteca);

                            cout << endl << "A devolução do livro foi realizada com sucesso!" << endl << endl;
                        } else {
                            cout << endl << "O livro mencionado não está sob empréstimo." << endl << endl;
                        }
                        
                        break;
                    }
                }
                if (!encontrado) {
                    cout << endl << "Livro não encontrado no catálogo." << endl << endl;
                }
                
                cin.ignore();
                cin.get();
                break;
            }

            case 6: {
                int code_search;
                encontrado = false;

                cout << endl << "Digite o código do livro: ";
                cin >> code_search;

                for (i = 0; i < total_livros; i++) {
                    if (livros[i].codigo == code_search) {
                        encontrado = true;

                        cout << endl;
                        cout << "Código: " << livros[i].codigo << endl;
                        cout << "Título: " << livros[i].titulo << endl;
                        cout << "Autor(es): " << livros[i].autores << endl;
                        cout << "Editora: " << livros[i].editora << endl;
                        cout << "Categoria: " << livros[i].area << endl;
                        cout << "Disponível: " << (livros[i].disponivel ? "Sim" : "Não") << endl << endl;

                        if (!livros[i].disponivel) {
                            cout << "O empréstimo foi realizado por: " << livros[i].emp.user << endl;
                            cout << "Data do empréstimo: " << livros[i].emp.data_emp << endl;
                            cout << "Data da devolução: " << livros[i].emp.data_dev << endl << endl;
                        }
                        break;
                    }
                }
                if (!encontrado) {
                    cout << endl << "Livro não encontrado." << endl << endl;
                }
                
                cin.ignore();
                cin.get();
                break;
            }

            case 7: {
                cout << endl << "Livros disponíveis para empréstimo: " << endl << endl;
                bool disponibilidade = false;  // Verificar se há algum livro disponível

                for (i = 0; i < total_livros; i++) {
                    if (livros[i].disponivel) {
                        cout << "Código: " << livros[i].codigo << ", Título: " << livros[i].titulo << endl << endl;
                        disponibilidade = true;
                    }
                }
                if (!disponibilidade) {
                    cout << "Nenhum livro disponível para empréstimo no momento." << endl << endl;
                }
                
                cin.ignore();
                cin.get();
                break;
            }
            
            case 8:{
              cout << endl << "Lista de todos os livros no sistema: " << endl << endl;
              
              if(total_livros == 0){
                
                cout << "Não há livros cadastrados no sistema." << endl;
              } else {
                for(i = 0; i < total_livros; i++){
                  cout << "Código: " << livros[i].codigo << endl;
                  cout << "Título: " << livros[i].titulo << endl;
                  cout << "Autor(es): " << livros[i].autores << endl;
                  cout << "Editora: " << livros[i].editora << endl;
                  cout << "Categoria: " << livros[i].area << endl;
                  cout << "Número de páginas: " << livros[i].num_pag << endl;
                  cout << "Disponível: " << (livros[i].disponivel ? "Sim" : "Não") << endl << endl;
                  
                  if(!livros[i].disponivel){
                    cout << "Empréstimo realizado por: " << livros[i].emp.user << endl;
                    cout << "Data do empréstimo: " << livros[i].emp.data_emp << endl;
                    cout << "Data da devolução: " << livros[i].emp.data_dev << endl << endl;
                  }
                  
                }
              }
              
              cin.ignore();
              cin.get();
              break;
            }
        }
        
        if (menu > 9) {
          cout << endl << "Opção inválida no menu. Tente novamente" << endl << endl;
          
          cin.ignore();
          cin.get();
        }
        
    } while (menu!= 9);  // Continuar até escolher a opção 9

    // Salva os dados antes de fechar o arquivo
    salvar_dados(dados_biblioteca);

    fclose(dados_biblioteca);  // Fecha o arquivo ao final do programa

    return 0;
}
