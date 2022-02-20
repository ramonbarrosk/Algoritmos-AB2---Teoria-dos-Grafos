#include <bits/stdc++.h>
#include "../grafo.h"

using namespace std;

int buscar(int subset[], int i){
    if(subset[i] == -1)
			return i;
		return buscar(subset, subset[i]);
}

void unir(int subset[], int v1, int v2){
		int v1_set = buscar(subset, v1);
		int v2_set = buscar(subset, v2);
		subset[v1_set] = v2_set;
}

vector<Aresta> kruskal(Grafo g){
    vector<Aresta> arvore;

    vector<Aresta> arestas = g.getVectorArestas();
    int tamanho_arestas = g.quantidadeArestas();
    int V = g.getVertice();

    sort(arestas.begin(), arestas.end());

    int * subset = new int[V];

    memset(subset, -1, sizeof(int) * V);

    for(int i = 0; i < tamanho_arestas; i++)
		{
			int v1 = buscar(subset, arestas[i].getVertice1());
			int v2 = buscar(subset, arestas[i].getVertice2());

			if(v1 != v2)
			{
				arvore.push_back(arestas[i]);
				unir(subset, v1, v2);
			}
		}

    int tamanho_arvore = arvore.size();
 
    return arvore;
}

int custoArvore(vector<Aresta> arvore){
    int resultado = 0;

    for(int i = 0; i < arvore.size(); i++){
        resultado += arvore[i].getPeso();
    }

    return resultado;
}

void ajuda(){
    printf("Algoritmo de Kruskal para Árvore Geradora Mínima:\n"
           "Para saber o custo da Árvore Geradora Mínima:, Execute o comando: \n./kruskal -f entrada.in\n"
           "Para visualizar a Árvore Geradora Mínima, Execute o comando: \n./kruskal -f entrada.in -s\n");
}

int main(int argc, char* argv[]){
   int f = 0, o = 0, s = 0, in = 0, l = 0;
    int source, dest;
    char* input_name;
    char* output_name;

    for (int i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-h")) ajuda();
        if(!strcmp(argv[i], "-o")){o++; output_name = argv[i+1]; }
        if(!strcmp(argv[i], "-f")){f++; input_name = argv[i+1]; }
        if(!strcmp(argv[i], "-i")){ in++; source = stoi(argv[i+1]); }
        if(!strcmp(argv[i], "-l")){ l++; dest = stoi(argv[i+1]); }
        if(!strcmp(argv[i], "-s")) s++;
    }
    ofstream output_file;
    output_file.open(output_name);
    
    if(f){
        Grafo g = leitura_arquivo(input_name);
        if (!s){
            vector<Aresta> arvore = kruskal(g);
            int resultado = custoArvore(arvore);
            if(!o) printf("Custo da Árvore Geradora Mínima: %d\n", resultado);
            else{
                output_file << "Custo da Árvore Geradora Mínima: " << resultado << endl; 
            }
        }
        
        if (s){
            vector<Aresta> arvore = kruskal(g);
            if (!o){
                   for(int i = 0; i < arvore.size(); i++)
                    {
                        int v1 = arvore[i].getVertice1();
                        int v2 = arvore[i].getVertice2();
                        cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].getPeso() << endl;
                    }
            }
            else{
                output_file << "Árvore Geradora Mínima:"<< endl;
                for (int i = 0; i < arvore.size(); i++){
                output_file << "(" << arvore[i].getVertice1() << "," << arvore[i].getVertice2() << ") = "<< arvore[i].getPeso() << endl;
                }
                printf("\n");
                output_file << endl;
            }
        }
    }
    output_file.close(); 

	return 0;
}
