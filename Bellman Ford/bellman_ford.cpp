#include <bits/stdc++.h>
#include "../grafo.h"

using namespace std;

int* bellman_ford(Grafo g, int orig, int *distancia){
	int V = g.getVertice();
	list<pair<int,int>> *adj = g.getAdjList();
	distancia[V];

	int visitados[V];

	priority_queue < pair<int, int>,
						vector<pair<int, int> >, greater<pair<int, int> > > pq;

	for(int i = 0; i < V; i++){
		distancia[i] = INFINITO;
		visitados[i] = false;
	}

	distancia[orig] = 0;

	pq.push(make_pair(distancia[orig], orig));

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

				if(distancia[u] + custo_aresta < distancia[v] && distancia[u] != INFINITO){

					distancia[v] = distancia[u] + custo_aresta;
					pq.push(make_pair(distancia[v], v));
				}
			}
		}
	}

	return distancia;
}


void ajuda(){
    printf("Algoritmo de Bellman-Ford para caminho com menor custo, incluindo pesos negativo:\n"
					 "Para saber o menor custo de um vértice x para os outros, Execute o comando: \n./bellman-ford -f entrada.in -i x\n"
    			 "Para saber o menor custo de um vértice x para y, Execute o comando: \n./bellman-ford -f entrada.in -i x -l y\n");
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
        
        if (in && l){
						int v = g.getVertice();
						int arr[v];
            int* distancia = bellman_ford(g, source, arr);
            if (!o) printf("Distância do vértice %d para o vértice %d = %d\n", source, dest, distancia[dest]);
            else{
                output_file << "Distância do vértice " << source << " para o vértice: " << dest <<" = " << distancia[dest] << endl;
            }    
        }
				else if(s || in){
					int v = g.getVertice();
					int arr[v];
          int* dist = bellman_ford(g, source, arr);
					if(!o) printf("Distãncia do vértice %d para todos os demais vértices:\n", source);
					else{
						output_file << "Distância do vértice " << source << " para todos os demais vértices:" << endl;
					}
					for (int i = 0; i < v; i++){
                if (!o) printf("%d:%d  ", i, dist[i]);
                else{
                    output_file << i << ":" << dist[i] << "  ";
                }
            }
            printf("\n");
            output_file << endl;
				}

    }
    output_file.close(); 

	return 0;
}
