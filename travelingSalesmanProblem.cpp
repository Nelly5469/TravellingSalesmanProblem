#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

struct Node {
    string name; // Nombre de la ciudad
    vector<Node*> childrenNodes; // Ciudades donde hay viajes directos desde la ciudad actual
    vector<Node*> parentNodes; // Ciudades donde hay viajes directos hacia la ciudad actual

    Node(string cityName) : name(cityName) {} // Constructor para inicializar el nombre de la ciudad
};

class Graph {
public:
    vector<Node*> nodes; // Almacena los nodos del grafo

    void addNode(const string& cityName) {
        nodes.push_back(new Node(cityName)); // Agrega un nuevo nodo al grafo
    }

    void addEdge(const string& fromCity, const string& toCity) {
        Node* fromNode = findNode(fromCity);
        Node* toNode = findNode(toCity);
        if (fromNode && toNode) {
            fromNode->childrenNodes.push_back(toNode); // Establece la conexión entre las ciudades
            toNode->parentNodes.push_back(fromNode);
        }
    }

    Node* findNode(const string& cityName) {
        for (Node* node : nodes) {
            if (node->name == cityName) {
                return node; // Devuelve el nodo si se encuentra
            }
        }
        return nullptr; // Devuelve nullptr si no se encuentra
    }

    void displayGraph() {
        for (Node* node : nodes) {
            cout << "Ciudad: " << node->name << " -> ";
            for (Node* child : node->childrenNodes) {
                cout << child->name << " ";
            }
            cout << endl;
        }
    }

    ~Graph() {
        for (Node* node : nodes) {
            delete node; // Libera la memoria de los nodos
        }
    }
};

int main() {
    Graph graph;

    // Inicializa las ciudades
    const vector<string> CITIES = {"NY", "CHI", "DEN", "HOU", "URB", "LA", "TOR", "CALG"};

    // Agrega nodos al grafo
    for (const string& city : CITIES) {
        graph.addNode(city);
    }

    // Establece conexiones entre las ciudades (aristas)
    graph.addEdge("NY", "CHI");
    graph.addEdge("NY", "TOR");
    graph.addEdge("NY", "DEN");
    graph.addEdge("CHI", "DEN");
    graph.addEdge("TOR", "LA");
    graph.addEdge("DEN", "HOU");
    graph.addEdge("DEN", "LA");
    graph.addEdge("HOU", "URB");
    graph.addEdge("HOU", "LA");
    graph.addEdge("TOR", "CALG");
    graph.addEdge("CALG", "LA");

    // Muestra el grafo
    graph.displayGraph();

    const Node* INIT_STATE = graph.findNode("NY");
    const Node* FINAL_STATE = graph.findNode("LA");
    //1. Lista abierta contiene el edo. inicial
    stack<Node*> openList.push(INIT_STATE);
    //2. Lista cerrada vacia
    stack<Node*> closedList;

    Node* currentNode;
    unsigned int i;

    //3. Lista abierta vacia?
    while(!openList.empty()){
        //3.1 No
        currentNode = openList.top(); //3.1.1 Nodo actual en lista abierta
        //3.1.2 Nodo actual en lista cerrada (extraer de lista cerrada)
        closedList.push(currentNode);
        openList.pop();
        if(closedList.top() != FINAL_STATE){ //3.1.3
            //3.1.3.1
            for(Node *children : currenNode.childrenNodes){ //3.1.3.1.1
                openList.push(children);//3.1.3.1.2
                ////3.1.3.1.3 Establecer apuntadores desde descendientes incorporado hacia padre en lista cerrada (creo que ya se hace)
            }
        }
    }

    return 0;
}
