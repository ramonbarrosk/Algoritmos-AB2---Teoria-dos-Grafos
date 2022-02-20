#include <bits/stdc++.h>
#include "../grafo.h"

using namespace std;

int custo_total(vector<int> custos){
    int resultado = 0;
    for(int i=0;i<custos.size();i++){
        resultado += custos[i];
    }

    return resultado;
}

pair <vector<int>, int> prim(Grafo g, int orig){
	int V = g.getVertice();
	list<pair<int,int>> *adj = g.getAdjList();
	vector<int> custos;
	vector<int> visitados;
    vector<int> prev;

	priority_queue < pair<int, int>,
						vector<pair<int, int> >, greater<pair<int, int> > > pq;

	for(int i = 0; i < V; i++){
		custos.push_back(INFINITO);
		visitados.push_back(false);
        prev.push_back(-1);
	}

	custos[orig] = 0;

	pq.push(make_pair(custos[orig], orig));

	while(!pq.empty()){
		pair<int, int> p = pq.top();
		int u = p.second;
		pq.pop();

		if(visitados[u] == false){

			visitados[u] = true;

			list<pair<int, int> >::iterator it;

			for(it = adj[u].begin(); it != adj[u].end(); it++){

				int v = it->first;
				int custo_aresta = it->second;

				if(!visitados[v] && custos[v] > custo_aresta){
                    custos[v] = custo_aresta;
                    prev[v] = u;
					pq.push(make_pair(custos[v], v));
				}
			}
		}
	}

	return make_pair(prev, custo_total(custos));
}

void ajuda(){
    printf("Algoritmo de Prim para Árvore Geradora Mínima:\n"
           "Para saber o custo da Árvore Geradora Mínima, Execute o comando: \n./prim -f entrada.in -i x\n"
           "Para visualizar a Árvore Geradora Completa, Execute o comando: \n./prim -f entrada.in -i x -s\n");
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
            pair <vector<int>, int> custos = prim(g, source);
            if(!o) printf("Custo da Árvore Geradora Mínima: %d\n", custos.second);
            else{
                output_file << "Custo da Árvore Geradora Mínima: " << custos.second << endl;
            }
        }
        else{
            pair < vector<int>, int>  par = prim(g, source);
            vector<int> costs = par.first;
            if (!o) printf("Árvore Geradora Mínima: "); 
            else{
                output_file << "Árvore Geradora Mínima: " << endl;
            }
            for (int i = 0; i < costs.size(); i++){  
                if (costs[i] == -1) continue;
                if (!o) printf("(%d,%d)  ", costs[i], i); 
                else{
                    output_file  << "(" << costs[i] << "," << i << ")  ";
                }
            }
            printf("\n");
            output_file << endl;
        }

    }
    output_file.close(); 

	return 0;
}
