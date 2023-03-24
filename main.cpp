/*Juego de los pancakes resuelto con el método de búsqueda AStar.
Se usa una cadena de 9 números y una heuristica que compara los
pancakes con sus vecinos para ver cuántos hay desordenados

Trabajo realizado para la materia de Inteligencia Artificial*/

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node {
    string state;
    int cost;
    int h_score;
    int moves;
};

struct NodeComparator {
    bool operator()(const Node& a, const Node& b) {
        return (a.cost + a.h_score) > (b.cost + b.h_score);
    }
/*Se compara dos nodos (a y b) para saber cuál nodo tiene el menor
costo total y así poder agregarlo a la cola, de manera se ordenan
de menor a mayor costo para que de la cola siempre salga primero el
de menor costo y el programa se centre en ese hasta dar con la solución*/
};

int calculate_h_score(string state) {
    int h = 0;
    /*recorre la cada pancake excepto el último*/
    for (int i = 0; i < state.size() - 1; i++)
    {
        /*se compara la diferencia absoluta entre los valores para ver
        si estan en orden*/
        if (abs(state[i] - state[i+1]) != 1) {
            /*si no están en orden la heuristica aumenta*/
            h++;
        }
    }
    return h;
/*Se calcula la heuristica por medio de la comparacion de cada
pancake con su vecino, contando cuantas veces hay dos pancakes
juntos que no estan en su posición correcta (un 8 encima de un 3,
por ejemplo)*/
}

void print_solution(Node node) {
    cout << "Solucion encontrada en " << node.moves << " movimientos.\n";
    cout << "Se visitaron " << node.cost << " nodos.\n";
    cout << "Cadena arreglada: " << node.state << endl;
}

void astar(string initial_state) {
    priority_queue<Node, vector<Node>, NodeComparator> open_list;
    unordered_map<string, bool> closed_list;
    Node initial_node = {initial_state, 0, calculate_h_score(initial_state), 0};
    open_list.push(initial_node);
    while (!open_list.empty()) {
        Node current_node = open_list.top();
        open_list.pop();
        if (current_node.state == "123456789") {
            print_solution(current_node);
            return;
        }
        if (closed_list[current_node.state]) {
            continue;
        }
        closed_list[current_node.state] = true;
        for (int i = 2; i <= 9; i++) {
            string new_state = current_node.state;
            reverse(new_state.begin(), new_state.begin() + i);
            if (!closed_list[new_state]) {
                Node new_node = {new_state, current_node.moves + 1, calculate_h_score(new_state), current_node.moves + 1};
                open_list.push(new_node);
            }
        }
    }
    cout << "No se encontro la solucion." << endl;
}

int main() {
    string initial_state;
    cout << "Introduzca una cadena de 9 numeros y sin espacios: ";
    cin >> initial_state;
    astar(initial_state);
    return 0;
}


