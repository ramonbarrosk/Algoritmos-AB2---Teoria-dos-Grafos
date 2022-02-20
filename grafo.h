#ifndef GRAFO_H
#define GRAFO_H
#define INFINITO 1000000
#include <bits/stdc++.h>

using namespace std;


class Aresta
{
	int vertice1, vertice2, peso;

public:

	Aresta(int v1, int v2, int peso){
		vertice1 = v1;
		vertice2 = v2;
		this->peso = peso;
	}

	int getVertice1(){
		return vertice1;
	}

	int getVertice2(){
		return vertice2;
	}

	int getPeso()
	{
		return peso;
	}

	bool operator < (const Aresta& aresta2) const
	{
		return (peso < aresta2.peso);
	}
};

class Grafo
{
private:
	int V;

	list<pair<int, int> > * adj;
	vector<Aresta> arestas;

public:
	Grafo(int V){
		this->V = V;

		adj = new list<pair<int, int> >[V];
	}

	void addArestaKruskal(int v1, int v2, int peso){
		Aresta aresta(v1, v2, peso);
		arestas.push_back(aresta);
	}

	void addAresta(int v1, int v2, int custo){
		adj[v1].push_back(make_pair(v2, custo));
	}

	int quantidadeArestas(){
		return arestas.size();
	}

	int getVertice(){
		return V;
	}

	vector<Aresta> getVectorArestas(){
		return arestas;
	}

	list<pair<int,int>>* getAdjList(){
		return adj;
	}


};

void split(string linha, int* origem, int* destino, int* peso){
    string delimitador = " "; 
    size_t pos = 0;
    string t;
    vector <int> valores;
    linha = linha + " ";
    while ((pos = linha.find(delimitador)) != string::npos) {
        t = linha.substr(0, pos);
        valores.push_back(stoi(t));
        linha.erase(0, pos + delimitador.length());
    }

    *origem = valores[0];
    *destino = valores[1];
    
    (valores.size() == 2) ? *peso = 1 : *peso = valores[2];
}

Grafo leitura_arquivo(const char* arquivo){
    int vertices, arestas, temp;
    string line;

    ifstream input_file(arquivo);
    getline(input_file, line);
    split(line, &vertices, &arestas, &temp);
    Grafo grafo(vertices);

    if (input_file.is_open()){
        while (getline(input_file,line))
        {
            int origem, destino, peso;
            split(line, &origem, &destino, &peso);
            grafo.addAresta(origem, destino, peso);
						grafo.addArestaKruskal(origem, destino, peso);
        }
        input_file.close();
    }
    else {
			printf("Erro ao abrir o arquivo\n");
			}

    return grafo;
}

#endif